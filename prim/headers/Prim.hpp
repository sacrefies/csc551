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
// Compiler:    G++
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
// home made include
#include "Vertex.hpp"
#include "logging.hpp"


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


/**
 * A class which implements the Prim's MST algorithm
 */
class Prim {

private:
    /** number of nodes/vertices (0..mVertexCount-1) */
    int mVertexCount  = 0;
    /**
     * matrix of weights:
     * mWeights[u][v] = mWeights[v][u] = weight value for edge (u,v)
     * this matrix can be considered as the adjacency matrix too
     */
    double ** mWeights = nullptr;
    /** defines an inner type of a priority queue of vertices */
    typedef priority_queue<Vertex *, vector<Vertex *>, Vertex> SortedVertices;
    /** a priority queue which stores all the vertices, sorted by keys */
    SortedVertices mQueue;
    // the following are subscripted by vertex (one for each vertex):
    bool * mIsInQ = nullptr; // is it in the q or not?
    double * mBestKeyValue = nullptr; // best assigned key value so far
    int * mBestParent = nullptr; // the resulting MST (keep track of best parent)


    /** holds a double_max value for convenience */
    const double DBL_MAX(void) const {
        return numeric_limits<double>::max();
    }


    /**
     * Print the specified 1-D array.
     */
    template <typename T>
    void debugPrintArray(T * list, const int size) const {
        stringstream msg;
        for (int i = 0; i < size; ++i) {
            if ((double)list[i] == DBL_MAX()) {
                msg << "MAX,";
                continue;
            }
            msg << list[i] << ",";
        }
        debug(__func__, msg.str());
    }


    /**
     * perform initialization/allocation
     *
     * @param vCount     The number of vertices
     */
    void init(int vCount) {
        if (vCount < 3) {
            error(__func__, "The number of vertices is less than 3");
            throw invalid_argument("Vertices count is less than 3");
        }

        stringstream msg;

        mVertexCount = vCount;
        msg << "vertex count: " << mVertexCount;
        debug(__func__, msg.str());
        msg.clear();
        msg.str("");

        mIsInQ = new bool[mVertexCount];
        mBestKeyValue = new double[mVertexCount];
        mBestParent = new int[mVertexCount];
        for (int i = 0; i < mVertexCount; ++i) {
            mIsInQ[i]  = false;
            mBestKeyValue[i] = DBL_MAX();
            mBestParent[i] = -1;
        }

        msg << "vertex in queue: array@" << hex << mIsInQ << dec;
        info(__func__, msg.str());
        msg.clear();
        msg.str("");
        debugPrintArray<bool>(mIsInQ, mVertexCount);

        msg << "best keys: array@" << hex << mBestKeyValue;
        msg << dec;
        info(__func__, msg.str());
        msg.clear();
        msg.str("");
        debugPrintArray<double>(mBestKeyValue, mVertexCount);

        msg << "best parents: array@" << hex << mBestParent;
        msg << dec;
        info(__func__, msg.str());
        msg.clear();
        msg.str("");
        debugPrintArray<int>(mBestParent, mVertexCount);

        // init 2d matrix of weights
        mWeights = new double *[mVertexCount];
        for (int r = 0; r < mVertexCount; ++r)
            mWeights[r] = new double[mVertexCount];
        for (int r = 0; r < mVertexCount; ++r)
            for (int c = 0; c < mVertexCount; ++c)
                mWeights[r][c] = DBL_MAX();

        msg << "weights(adj matrix): array@" << hex << mWeights;
        msg << dec;
        info(__func__, msg.str());
        msg.clear();
        msg.str("");
    }

public:
    /** ctor which simply sets the numbers of vertices and puts each one in its
     * own set.
     *
     *@param fname   The data file name
     */
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
        info(__func__, "done");

        // load the edges and their weights
        int u, v;
        double w;
        info(__func__, "build up weights and adjacency matrix");
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
        for (int r = 0; r < mVertexCount; ++r)
            debugPrintArray<double>(mWeights[r], mVertexCount);
        info(__func__, "done");

        // init root vertex (choice is arbitrary, so we'll choose 0)
        Vertex * r = new Vertex(0, 0.0, -1);
        mQueue.push(r);
        mIsInQ[r->getI()] = true;
        mBestKeyValue[r->getI()] = 0.;

        // init the remaining vertices
        for (int i = 1; i < mVertexCount; ++i) {
            Vertex * v = new Vertex(i, DBL_MAX(), -1);
            mQueue.push(v);
            mIsInQ[v->getI()] = true;
        }

        stringstream msg;
        msg << "queue of vertices: queue@" << hex << &mQueue << dec;
        msg << ", size: " << mQueue.size();
        info(__func__, msg.str());
        msg.clear();
        msg.str("");
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

        msg << ":::: clear up mQueue" << hex << &mQueue << dec;
        debug(__func__, msg.str());
        msg.clear();
        msg.str("");
        while (false == mQueue.empty()) {
            mQueue.pop();
            debug(__func__, ":::::: pop ==>");
        }

        if (mWeights != nullptr) {
            for (int r = 0; r < mVertexCount; r++) {
                msg.clear();
                msg.str("");
                delete[] mWeights[r];
                mWeights[r] = nullptr;
                msg << ":::: mVertexCount[" << r << "] ==> NULL";
                debug(__func__, msg.str());
            }
            mWeights = nullptr;
            debug(__func__, ":::: mVertexCount ==> NULL");
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
            debug(__func__, ":::: mBestKeyValue ==> NULL");
        }
        debug(__func__, "dtor done");
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
        Vertex * uVert = nullptr;
        Vertex * vVert = nullptr;

        info(__func__, "start processing MST");
        stringstream msg;
        while (false == mQueue.empty()) {
            uVert = mQueue.top();
            mQueue.pop();
            u = uVert->getI();
            msg << ":: poped ==>  u=" << u << " u.key=";
            if (DBL_MAX() == uVert->getKey())
                msg << "MAX";
            else
                msg << setprecision(2) << uVert->getKey();
            // kill dangling ptr
            uVert = nullptr;

            msg << " in_Q=" << ((mIsInQ[u] == true)? "true": "false");
            info(__func__, msg.str());
            msg.clear();
            msg.str("");
            msg << ":: queue size = " << mQueue.size();
            debug(__func__, msg.str());
            msg.clear();
            msg.str("");

            if (false == mIsInQ[u]) {
                msg << ":::: skip " << u << " because u is not in queue";
                debug(__func__, msg.str());
                msg.clear();
                msg.str("");
                continue;
            }

            // set u is not in queue
            mIsInQ[u] = false;
            msg << ":: set " << u << " in_Q=" << false;
            debug(__func__, msg.str());
            msg.clear();
            msg.str("");

            msg << ":: looking for adj[" << u << "] ==> ";
            info(__func__, msg.str());
            msg.clear();
            msg.str("");
            debugPrintArray<double>(mWeights[u], mVertexCount);
            // search in the adj matrix mWeights
            for (int v = 0; v < mVertexCount; ++v) {
                msg << ":::: get v=" << v << " v.bestkey=";
                if (mBestKeyValue[v] == DBL_MAX())
                    msg << "MAX";
                else
                    msg << mBestKeyValue[v];
                msg << " v.bestparent=" << mBestParent[v] << " in_Q=" <<
                    mIsInQ[v];
                debug(__func__, msg.str());
                msg.clear();
                msg.str("");
                // skip if v is not in queue
                if (false == mIsInQ[v]) {
                    msg << ":::: skip " << v << " because v is not in queue";
                    debug(__func__, msg.str());
                    msg.clear();
                    msg.str("");
                    continue;
                }
                w = mWeights[u][v];
                msg << ":::: w(u,v) = ";
                if (w == DBL_MAX())
                    msg << "MAX";
                else
                    msg << w;
                debug(__func__, msg.str());
                msg.clear();
                msg.str("");
                // skip if u and v are not connected
                if (DBL_MAX() == w) {
                    msg << ":::: skip " << v << " because v is not adjacent";
                    debug(__func__, msg.str());
                    msg.clear();
                    msg.str("");
                    continue;
                }
                // skip if v.key <= w(u, v)
                if (mBestKeyValue[v] <= w) {
                    msg << ":::: skip " << v << " because v.bestkey <= " << w;
                    debug(__func__, msg.str());
                    msg.clear();
                    msg.str("");
                    continue;
                }
                msg << ":::: found a better weight: " << setprecision(2) << w;
                info(__func__, msg.str());
                msg.clear();
                msg.str("");
                // create a new vertex with the new key and parent
                msg << ":::: create new Vertex(";
                msg << v << ", " << setprecision(2) << w << ", " << u << ")";
                info(__func__, msg.str());
                msg.clear();
                msg.str("");

                vVert = new Vertex(v, w, u);
                mQueue.push(vVert);
                // kill dangling ptr
                vVert = nullptr;

                msg << ":::: added Vertex, queue size= " << mQueue.size();
                debug(__func__, msg.str());
                msg.clear();
                msg.str("");

                // update best parent and best weight
                msg << ":::: update best key of " << v << " ==>";
                debug(__func__, msg.str());
                msg.clear();
                msg.str("");
                mBestKeyValue[v] = w;
                debugPrintArray<double>(mBestKeyValue, mVertexCount);
                msg << ":::: update best parent of " << v << " ==>";
                debug(__func__, msg.str());
                msg.clear();
                msg.str("");
                mBestParent[v] = u;
                debugPrintArray<int>(mBestParent, mVertexCount);
            }
        }

        uVert = vVert = nullptr;        // assure no dangling ptrs
        debug(__func__, "::process done");
    }


    /**
     * Get the MST total cost (sum of the edge weights).
     */
    double getMSTCost(void) const {
        debug(__func__, "best Keys are ===>");
        debugPrintArray<double>(mBestKeyValue, mVertexCount);
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
    friend ostream& operator<< (ostream& os, const Prim& p) {
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
