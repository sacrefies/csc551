// -----------------------------------------------------------------------------
// Filename:    Vertex.hpp
// Revision:    $Id$
// Description: this file contains the definition of the Prim class.
//              an outline of this algorithm from the Cormen book follows.
//
//              MST_Prim ( G, w, r )
//                  1 foreach u in V
//                  2     u.key = +infinity
//                  3     u.p   = nil
//                  6 while !empty( Q )
//                  7     u = EXTRACT_MIN( Q )
//                  8     foreach v in G.Adj[ u ]
//                  9         if v in Q and w( u, v ) < v.key
//                 10             v.p = u
//                 11             v.key = w( u, v )
//
// Created:     04/26/2016 01:20:29 PM
// Compiler:    G++, cmake
// Author:      George J. Grevera, Ph.d, Jason Qiao Meng
//
// Copyright (c) 2016 by Jason Meng, no rights reserved.
// Copyright (c) George J. Grevera, 2016.  All rights reserved.
// -----------------------------------------------------------------------------

#ifndef PRIMS_H
#define PRIMS_H

// C include
// C++ include
#include <fstream>      // ifstream
#include <iostream>     // ostream
#include <iomanip>
#include <queue>        // priority_queue
#include <set>          // set
#include <exception>    // invalid_argument
#include <limits>       // numeric_limits
#include <sstream>      // stringstream
#include <string>       // string, to_string()
// home made include
#include "Vertex.h"
#include "logging.h"
#include "debugutils.h"


using std::invalid_argument;
using std::endl;
using std::priority_queue;
using std::vector;
using std::set;
using std::ifstream;
using std::hex;
using std::dec;
using std::flush;
using std::cout;
using std::ostream;
using std::numeric_limits;
using std::setprecision;
using std::setw;
using std::string;
using std::to_string;


/**
 * A class which implements the Prim's MST algorithm
 */
class Prim {

private:
    /// number of nodes/vertices (0..mVertexCount-1)
    int mVertexCount = 0;
    /// matrix of weights:
    /// mWeights[u][v] = mWeights[v][u] = weight value for edge (u,v)
    /// this matrix can be considered as the adjacency matrix too.
    double **mWeights = nullptr;
    /// defines an inner type of a priority queue of vertices
    typedef priority_queue<Vertex *, vector<Vertex *>, Vertex> SortedVertices;
    /// a priority queue which stores all the vertices, sorted by keys
    SortedVertices mQueue;
    //------ the following are subscripted by vertex (one for each vertex): ---//
    /// is it in the q or not?
    bool *mIsInQ = nullptr;
    /// best assigned key value so far
    double *mBestKeyValue = nullptr;
    /// the resulting MST (keep track of best parent)
    int *mBestParent = nullptr;

    /// Get the maximum double value.
    /// \return Returns the maximum double value.
    const double DBL_MAX(void) const {
        return numeric_limits<double>::max();
    }

    /// initialization/allocation
    /// \param vCount The number of vertices
    void init(int vCount) {
        if (vCount < 3) {
            error(__func__, "The number of vertices is less than 3");
            throw invalid_argument("Vertices count is less than 3");
        }

        mVertexCount = vCount;
        debug(__func__, "vertex count: " + to_string(mVertexCount));

        mIsInQ = new bool[mVertexCount];
        mBestKeyValue = new double[mVertexCount];
        mBestParent = new int[mVertexCount];
        for (int i = 0; i < mVertexCount; ++i) {
            mIsInQ[i] = false;
            mBestKeyValue[i] = DBL_MAX();
            mBestParent[i] = -1;
        }

        debug(__func__, "vertex in queue:");
        debugPrintArray<bool>(__func__, mIsInQ, mVertexCount);
        debug(__func__, "best keys:");
        debugPrintArray<double>(__func__, mBestKeyValue, mVertexCount);
        debug(__func__, "best parents:");
        debugPrintArray<int>(__func__, mBestParent, mVertexCount);

        // init 2d matrix of weights
        mWeights = new double *[mVertexCount];
        for (int r = 0; r < mVertexCount; ++r)
            mWeights[r] = new double[mVertexCount];
        for (int r = 0; r < mVertexCount; ++r)
            for (int c = r; c < mVertexCount; ++c)
                mWeights[r][c] = mWeights[c][r] = DBL_MAX();
        debug(__func__, "weights(adj matrix):");
    }

public:
    /// ctor which simply sets the numbers of vertices and puts each one in its
    /// own set.
    /// \param fname The data file name
    Prim(string fname) {
        debug(__func__, "init Prim, file: " + fname);
        // open the input file
        ifstream in(fname);
        if (in.fail()) {
            error(__func__, "error opening file " + fname);
            throw invalid_argument("Failed to open file " + fname);
        }

        // read the number of vertices and edges in the file
        int vertices, edges;
        in >> vertices >> edges;
        info(__func__, "start initialization...");
        init(vertices);
        debug(__func__, "done");
        // load the edges and their weights
        int u, v;
        double w;
        info(__func__, "build the adjacency matrix...");
        for (int i = 0; i < edges; i++) {
            in >> u >> v >> w;
            mWeights[u][v] = mWeights[v][u] = w;
            // print something every once in a while when processing large
            // input files.
            if (i > 0) {
                if (i % 1000000 == 0)
                    cout << "!" << flush;
                else if (i % 100000 == 0)
                    cout << "*" << flush;
                else if (i % 10000 == 0 || i % 1000 == 0 || i % 100 == 0)
                    cout << "." << flush;
                else if (i % 10 == 0)
                    cout << "~" << flush;
            }
        }
        cout << endl;
        in.close();
        debugPrintMatrix(__func__, mWeights, mVertexCount);
        debug(__func__, "done");
        // init root vertex (choice is arbitrary, so we'll choose 0)
        Vertex *r = new Vertex(0, 0.0, -1);
        mQueue.push(r);
        mIsInQ[r->getI()] = true;
        mBestKeyValue[r->getI()] = 0.;
        r = nullptr;
        // init the remaining vertices
        for (int i = 1; i < mVertexCount; ++i) {
            Vertex *vert = new Vertex(i, DBL_MAX(), -1);
            mQueue.push(vert);
            mIsInQ[vert->getI()] = true;
            vert = nullptr;
        }
        info(__func__, "queue of vertices, size=" + to_string(mQueue.size()));
        debug(__func__, "ctor done");
    }

    /**
     * dtor
     */
    ~Prim(void) {
        // prints are useful to determine when dtors are actually called (or not).
        stringstream msg;
        info(__func__, "disposing Prim...");
        msg << ":: Prim@" << hex << this << dec;
        info(__func__, msg.str());
        msg.clear();
        msg.str("");

        msg << ":::: clear up mQueue@" << hex << &mQueue << dec;
        debug(__func__, msg.str());
        msg.clear();
        msg.str("");
        while (false == mQueue.empty()) {
            Vertex *v = mQueue.top();
            mQueue.pop();
            msg << ":::::: pop ==> vertex(" << v->getI() << ",";
            msg << v->getKey() << "," << v->getParent() << ")";
            debug(__func__, msg.str());
            msg.clear();
            msg.str("");
            delete v;
        }
        msg << ":::: clear up mWeights@" << hex << mWeights << dec;
        debug(__func__, msg.str());
        msg.clear();
        msg.str("");
        if (mWeights != nullptr) {
            for (int r = 0; r < mVertexCount; r++) {
                delete[] mWeights[r];
                mWeights[r] = nullptr;
                msg << ":::::: mWeights[" << r << "] ==> NULL";
                debug(__func__, msg.str());
                msg.clear();
                msg.str("");
            }
            mWeights = nullptr;
            debug(__func__, ":::::: mWeights ==> NULL");
        }
        if (mIsInQ != nullptr) {
            delete[] mIsInQ;
            mIsInQ = nullptr;
            debug(__func__, ":::: mIsInQ ==> NULL");
        }
        if (mBestKeyValue != nullptr) {
            delete[] mBestKeyValue;
            mBestKeyValue = nullptr;
            debug(__func__, ":::: mBestKeyValue ==> NULL");
        }
        if (mBestParent != nullptr) {
            delete[] mBestParent;
            mBestParent = nullptr;
            debug(__func__, ":::: mBestParent ==> NULL");
        }
        info(__func__, "dtor done");
    }

    /**
     * (public for testing.)
     * implement the algorithm (lines 6 through 11):
     *     6 while !empty( Q )
     *     7     u = EXTRACT_MIN( Q )
     *     8     foreach v in G.Adj[ u ]
     *     9         if v in Q and w( u, v ) < v.key
     *    10             v.p = u
     *    11             v.key = w( u, v )
     */
    void process(void) {
        int u;
        double w;
        Vertex *uVert = nullptr;
        Vertex *vVert = nullptr;
        info(__func__, "start processing MST");
        string msg = "";
        SortedVertices tmp(mQueue);
        while (false == tmp.empty()) {
            uVert = tmp.top();
            tmp.pop();
            u = uVert->getI();
            msg = ":: popped ==>  u=" + to_string(u) + " u.key=";
            msg += (DBL_MAX() == uVert->getKey()) ? "MAX" : to_string(uVert->getKey());
            msg += " in_Q=" + to_string(mIsInQ[u]);
            debug(__func__, msg);
            // kill dangling ptr
            uVert = nullptr;
            msg = ":: queue size = " + to_string(tmp.size());
            debug(__func__, msg);
            if (false == mIsInQ[u]) {
                debug(__func__, ":::: skip " + to_string(u) + " because it is not in queue");
                continue;
            }
            // set u is not in queue
            mIsInQ[u] = false;
            debug(__func__, ":: set " + to_string(u) + " in_Q=false");
            debug(__func__, ":: looking for adj[" + to_string(u) + "] ==> ");
            debugPrintArray<double>(__func__, mWeights[u], mVertexCount);
            // search in the adj matrix mWeights
            for (int v = 0; v < mVertexCount; ++v) {
                msg = ":::: get v=" + to_string(v) + " v.bestKey=";
                msg += (mBestKeyValue[v] == DBL_MAX()) ? "MAX" : to_string(mBestKeyValue[v]);
                msg += " v.bestParent=" + to_string(mBestParent[v]);
                msg += " in_Q=" + to_string(mIsInQ[v]);
                debug(__func__, msg);
                // skip if v is not in queue
                if (false == mIsInQ[v]) {
                    debug(__func__, ":::: skip " + to_string(v) + " because it is not in queue");
                    continue;
                }
                w = mWeights[u][v];
                msg = ":::: w(u,v) = ";
                msg += (w == DBL_MAX()) ? "MAX" : to_string(w);
                debug(__func__, msg);
                // skip if u and v are not connected
                if (DBL_MAX() == w) {
                    debug(__func__, ":::: skip " + to_string(v) + " because it is not adjacent");
                    continue;
                }
                // skip if v.key <= w(u, v)
                if (mBestKeyValue[v] <= w) {
                    debug(__func__,
                          ":::: skip " + to_string(v) + " because v.bestKey <= " + to_string(w));
                    continue;
                }
                debug(__func__, ":::: found a better weight: " + to_string(w));
                // create a new vertex with the new key and parent
                msg = ":::: create a new Vertex(";
                msg += to_string(v) + ", " + to_string(w) + ", " + to_string(u) + ")";
                debug(__func__, msg);
                vVert = new Vertex(v, w, u);
                // add this new vertex to both the copied queue and the original queue.
                mQueue.push(vVert);
                tmp.push(vVert);
                // kill dangling ptr
                vVert = nullptr;
                debug(__func__, ":::: added Vertex, queue size= " + to_string(tmp.size()));
                // update best parent and best weight
                debug(__func__, ":::: update best key of " + to_string(v) + " ==>");
                mBestKeyValue[v] = w;
                debugPrintArray<double>(__func__, mBestKeyValue, mVertexCount);
                debug(__func__, ":::: update best parent of " + to_string(v) + " ==>");
                mBestParent[v] = u;
                debugPrintArray<int>(__func__, mBestParent, mVertexCount);
            }
        }
        uVert = vVert = nullptr; // assure no dangling ptrs
        info(__func__, "processing done");
    }

    /**
     * Get the MST total cost (sum of the edge weights).
     */
    double getMSTCost(void) const {
        debug(__func__, "best Keys are ===>");
        debugPrintArray<double>(__func__, mBestKeyValue, mVertexCount);
        double sum = 0.;
        for (int v = 0; v < mVertexCount; ++v)
            sum += mBestKeyValue[v];
        return sum;
    }

    /**
     * allow one to pretty print the contents of the Prim object to an output
     * stream.
     * note: unsigned long casts below should be unsigned long long when building
     * 64-bit versions.
     */
    friend ostream &operator<<(ostream &os, const Prim &p) {
        stringstream tmp;
        os << "--------------------" << endl;
        os << "Prim:" << endl;
        if (p.mVertexCount <= 20) {
            os << ":::: Adjacency Matrix (weights):" << endl;
            for (int r = 0; r < p.mVertexCount; ++r) {
                os << setw(8) << "";
                for (int c = 0; c < p.mVertexCount; ++c) {
                    if (p.DBL_MAX() == p.mWeights[r][c])
                        tmp << setw(6) << "/";
                    else
                        tmp << setw(6) << setprecision(2) << p.mWeights[r][c];
                }
                os << tmp.str() << endl << flush;
                tmp.clear();
                tmp.str("");
            }
        }
        os << ":::: MST edges:" << endl;
        for (int i = 0; i < p.mVertexCount; ++i)
            if (p.mBestParent[i] != -1) {
                tmp << "(" << i << "," << p.mBestParent[i] << ")";
                os << setw(16) << tmp.str();
                tmp.clear();
                tmp.str("");
                os << " w=" << setprecision(2) << p.mBestKeyValue[i] << endl;
            }
        os << ":: MST cost: " << setprecision(5) << p.getMSTCost() << endl;
        return os;
    }
};

#endif /** end of include guard */
