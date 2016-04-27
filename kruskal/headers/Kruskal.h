// -----------------------------------------------------------------------------
// Filename:    Kruskal.h
// Revision:    $Id$
// Description: this file contains the definition of the Kruskal class
// Created:     04/20/2016 01:20:29 PM
// Compiler:    G++
// Author:      Jason Meng (jm), jm652564@sju.edu
//
// Copyright (c) 2016 by Jason Meng, no rights reserved.
// Copyright (c) George J. Grevera, 2016.  All rights reserved.
// -----------------------------------------------------------------------------
//
// 8"""8
// 8   8  eeee eeeee e   e e  eeeee  eeee eeeeeee eeee eeeee eeeee eeeee
// 8eee8e 8    8   8 8   8 8  8   8  8    8  8  8 8    8   8   8   8   "
// 88   8 8eee 8   8 8e  8 8e 8eee8e 8eee 8e 8  8 8eee 8e  8   8e  8eeee
// 88   8 88   8 __8 88  8 88 88   8 88   88 8  8 88   88  8   88     88
// 88   8 88ee 8e888 88ee8 88 88   8 88ee 88 8  8 88ee 88  8   88  8ee88
//
//   desc. :  this file contains the definition of the Kruskal class.
//         an outline of this algorithm from the Cormen book follows:
//         \TODOs:
//             makeSet
//             sameSet
//             vertexSetUnion
//             process
//             getMSTCost
//
//         MST-KRUSKAL ( G, w )
//         1    A = empty-set
//         2    for each vertex . v in G.V
//         3        MAKE-SET( v )
//         4    sort the edges of G.E into nondecreasing order by weight w
//         5    for each edge  in G.E, taken in nondecreasing order by weight
//         6        if (!sameSet(u, v))           //was: if FIND-SET( u ) != FIND-SET( v )
//         7            insert( A,  )        //was:     A = union( A, {} )    //add edge  to MST edge set A
//         8            vertexSetUnion( u, v )    //was:     UNION( u, v )              //union of sets of vertices
//         9    return A
//
//    note: 'union' is a keyword/reserved word in C++
//
//   Copyright (c) George J. Grevera, 2016.  All rights reserved.
// -----------------------------------------------------------------------------

#include <assert.h>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <set>
#include <exception>
#include <vector>
// custom headers
#include "Edge.h"
#include "logging.hpp"


/** include guard */
#ifndef KRUSKAL_H
#define KRUSKAL_H


using std::invalid_argument;
// using std::cerr;
using std::endl;
using std::priority_queue;
using std::vector;
using std::queue;
using std::set;
using std::ifstream;
using std::hex;
using std::dec;
using std::flush;
using std::cout;
using std::to_string;


class Kruskal {

private:
    /** number of nodes/vertices (0..mVertexCount-1) */
    int mVertexCount = 0;
    /** 2d array indicating what is in each set */
    bool ** mVertexSet = nullptr;
    /** type alias for a priority_queue of edges */
    typedef priority_queue < Edge *, vector < Edge * >, Edge > SortedEdges;
    /** edges sorted by weight */
    SortedEdges mSortedEdges;
    /** type alias for the set of edges which stores the min-spanning-tree */
    typedef set < Edge * > MSTEdgeSet;
    /** result set of edges in MST */
    MSTEdgeSet mA;
    /** the cost of the current MST */
    double mCost = 0.;


    /**
     * allocate memory for the 2d array representing sets of vertices.
     *
     * @param vCount    number of vertices
     */
    void initSet(int vCount) {
        mVertexCount = vCount;
        debug(__func__,
              "vCount=" + to_string(vCount) + ", mVertexCount=" +
              to_string(mVertexCount));
        // allocate & init memory for the 2d array
        mVertexSet = new bool *[vCount];
        for (int i = 0; i < vCount; ++i) {
            mVertexSet[i] = new bool[vCount];
            for (int j = 0; j < vCount; ++j)
                mVertexSet[i][j] = false;
        }

        debugPrintVertexSet();
    }


    void debugPrintVertexSet() {
        debug(__func__, "Vertex set ====> ");
        if (mVertexSet == nullptr) {
            debug(__func__, "NULL");
            return;
        }

        string row;
        for (int i = 0; i < mVertexCount; ++i) {
            if (mVertexSet[i] == nullptr) {
                debug(__func__, "NULL");
                continue;
            }

            row = "";
            for (int j = 0; j < mVertexCount; ++j)
                row +=
                    ((true == mVertexSet[i][j])?
                     to_string(true): to_string(false))
                    + ",";
            debug(__func__, row);
        }
    }


    void debugPrintSingleVertexSet(int vertex) {
        string msg = "Vertex set ";
        msg += to_string(vertex) + " ====> ";
        debug(__func__, msg);
        msg = "";
        for (int i = 0; i < mVertexCount; ++i)
            msg += to_string(mVertexSet[vertex][i]) + ",";
        debug(__func__, msg);
    }


    /**
     * Check whether an edge exists already in the priority queue by given the edge's
     * both end vertices.
     * Note: This method is resource-consuming because it basically rebuilds the
     * queue to examine each edge in the queue.
     *
     * @param u A vertex which is one end of the edge.
     * @param v A vertex which is one end of the edge.
     *
     * @return Returns true if the edge exists in queue; otherwise returns false.
     */
    bool edgeExistsInQueue(int u, int v) {
        if (true == mSortedEdges.empty()) {
            debug(__func__, "edge queue is empty. nothing in queue");
            return false;
        }

        // save the initial size of the queue
        int size = mSortedEdges.size();
        string msg = "edge queue size: ";
        msg += to_string(size);
        debug(__func__, msg);

        int f = -1, t = -1;
        if (size == 1) {
            Edge * e = mSortedEdges.top();
            f = e->getFrom();
            t = e->getTo();
            e = nullptr; // kill dangling ptr
            msg = "what's in queue: (";
            msg += to_string(f) + "," + to_string(t);
            msg += ")";
            debug(__func__, msg);
            msg = "return: ";
            msg += ((f == u && t == v) || (f == v && t == u))? "true": "false";
            debug(__func__, msg);
            return (f == u && t == v) || (f == v && t == u);
        }

        bool found = false;
        SortedEdges tmp(mSortedEdges);
        while (false == tmp.empty() && false == found) {
            Edge * e = tmp.top();
            tmp.pop();
            f = e->getFrom();
            t = e->getTo();
            e = nullptr;
            found = (f == u && t == v) || (f == v && t == u);
        }
        return found;
    }

public:
    /**
     * ctor which simply sets the numbers of vertices and puts each one in its
     * own set.  if you use this, you will have to add edges on your own and
     * one at a time.
     *
     * @param vCount    number of vertices. this number should be greater than 2
     *                  because 2 vertice has only 1 edge which is a MST natually.
     */
    Kruskal(int vCount) {
        debug(__func__, "init KK");
        // in fact
        if (vCount < 3) {
            // stop it from creation
            warning(__func__,
                    "Vertices are less than 3. Kruskal object is stoped from being created.");
            throw invalid_argument("Number of vertices is less than 3");
        }
        // init the vertex set
        initSet(vCount);
        debug(__func__, "finished init vertex set");
        // make each vertex as one set, the there should be vCount sets
        makeSet(vCount);
        debug(__func__, "finished make vertex set");
    }

    /**
     * ctor which loads vertices and edges (and their weights) from an input
     * file.
     *
     * @param fname The data file path (can be a relative path)
     */
    Kruskal(string fname) {
        debug(__func__, "init KK, file: " + fname);
        // open the input file
        ifstream in(fname);
        // stop it from creation
        if (in.fail()) {
            error(__func__, "Failed to read the file: " + fname);
            throw invalid_argument("Failed to open file: " + fname);
        }

        // read the number of vetices and edges in the file
        int vertices, edges;
        in >> vertices >> edges;
        // put each vertex in its own separate set
        initSet(vertices);
        makeSet(vertices);

        // load the edges and their weights
        int u, v;
        double w;
        for (int i = 0; i < edges; i++) {
            in >> u >> v >> w;
            addEdge(u, v, w);
            // print something every once in a while when processing large
            // input files.
            if (i > 0) {
                if (i % 1000000 == 0) info(__func__, "!");
                else if (i % 100000 == 0) info(__func__, "*");
                else if (i % 10000 == 0) info(__func__, ".");
            }
        }
        in.close();
    }


    /** dtor */
    ~Kruskal(void) {
        // prints are useful to determine when dtors are actually called (or not).
        debug(__func__, "disposing Kruskal object");
        string msg;
        // free vertex sets
        if (mVertexSet != nullptr) {
            msg = ":: vertex set, vertices count: ";
            msg += to_string(mVertexCount);
            debug(__func__, msg);
            for (int i = 0; i < mVertexCount; ++i)
                if (mVertexSet[i] != nullptr) {
                    delete[] mVertexSet[i];
                    mVertexSet[i] = nullptr;
                    msg = ":::: ";
                    msg += to_string(i) + " ==> NULL";
                    debug(__func__, msg);
                }
            delete[] mVertexSet;
            mVertexSet = nullptr;
            debug(__func__, ":: vertex set ==> NULL");
        }

        // free anything left
        msg = ":: edge set, size: ";
        msg += to_string(mSortedEdges.size());
        debug(__func__, msg);
        while (!mSortedEdges.empty()) {
            Edge * e = mSortedEdges.top();
            mSortedEdges.pop();
            if (mA.end() == mA.find(e)) {
                msg = ":::: ==> (";
                msg += to_string(e->getFrom()) + ", " + to_string(e->getTo());
                msg += ", ";
                msg += to_string(e->getW()) + ") ==> NULL";
                debug(__func__, msg);
                delete e;
            }
            e = nullptr;
        }
        debug(__func__, ":: edge set ==> NULL");

        // free anything in the MST
        msg = ":: MST set, size: ";
        msg += to_string(mA.size());
        debug(__func__, msg);
        // this is simply a for-each loop over each edge in A (the resulting MST)
        for (auto e : mA) {
            msg = ":::: (";
            msg += to_string(e->getFrom()) + ", " + to_string(e->getTo()) + ")";
            msg += " ==> NULL";
            debug(__func__, msg);
            delete e;
        }
        mA.clear();
        debug(__func__, ":: MST set ==> empty");
    }


    /**
     * add the edge  with its weight to the automagically sorted set of
     * edges.
     *
     * @param u A vertex which is one end of the edge.
     * @param v A vertex which is one end of the edge.
     * @param w The weight of the edge
     */
    void addEdge(int u, int v, double w) {
        string msg = "---------------------------------";
        debug(__func__, msg);
        if (u < 0 || u >= mVertexCount) {
            msg = "Kruskal:addEdge(u,v,w): bad u ";
            msg += to_string(u);
            error(__func__, msg);
            return;
        }
        if (v < 0 || v >= mVertexCount) {
            msg = "Kruskal:addEdge(u,v,w): bad v ";
            msg += to_string(v);
            error(__func__, msg);
            return;
        }

        msg = "[BEFORE ADD] edge queue size: ";
        msg += to_string(mSortedEdges.size());
        debug(__func__, msg);
        msg = "try adding edge: (";
        msg += to_string(u) + "," + to_string(v) + "," + to_string(w);
        msg += ")";
        debug(__func__, msg);
        if (false == edgeExistsInQueue(u, v)) {
            Edge * e = new Edge(u, v, w);
            mSortedEdges.push(e);
        } else
            warning(__func__, "No adding. The edge exists.");
        msg = "[AFTER ADD] edge queue size: ";
        msg += to_string(mSortedEdges.size());
        debug(__func__, msg);
    }


    /**
     *(public for testing.)
     * put each vertex in an individual set.
     *
     * @param vCount    Number of the vertices. It also implies individual vertex
     *                  definition: vCount = 3, {V} = {0, 1, 2}
     * @see mVertexSet
     * @see initSet
     */
    void makeSet(int vCount) {
        debug(__func__, "---------------------------------");
        for (int vertex = 0; vertex < vCount; ++vertex)
            mVertexSet[vertex][vertex] = true;
        debugPrintVertexSet();
    }


    /**
     *(public for testing.)
     * this function returns true if the vertices specified are in the same set,
     * and false otherwise.
     *
     * @see mVertexSet
     * @see initSet
     * @see vertexSetUnion
     */
    bool sameSet(int u, int v) {
        debug(__func__, "---------------------------------");
        // make sure that args are valid.
        assert(0 <= u && u < mVertexCount);
        assert(0 <= v && v < mVertexCount);
        if (u < 0 || u >= mVertexCount || v < 0 || v >= mVertexCount)
            return false;

        // check only one row to speed up a bit because if they are in v' set,
        // they are definitely in u's set. (according vertexSetUnion())
        // and if u is chosen, no need to check mVertexSet[v][u] which must be
        // true
        debugPrintSingleVertexSet(u);
        debugPrintSingleVertexSet(v);
        string msg = "same set: ";
        msg += (true == mVertexSet[u][v])? "true": "false";
        debug(__func__, msg);
        return mVertexSet[u][v];
    }


    /**
     * (public for testing.)
     * create the union of two sets.
     *
     * @param u A vertex which is one end of the edge.
     * @param v A vertex which is one end of the edge.
     */
    void vertexSetUnion(int u, int v) {
        debug(__func__, "---------------------------------");
        debug(__func__, "[BEFORE UNION] vertex set:");
        debugPrintVertexSet();
        // already there, do nothing
        if (true == mVertexSet[u][v]) return;
        // union from set(v) to set(u)
        for (int i = 0; i < mVertexCount; ++i)
            // copy true values from v to u
            if (mVertexSet[v][i] != mVertexSet[u][i]) {
                if (true == mVertexSet[v][i])
                    mVertexSet[u][i] = mVertexSet[v][i];
                else
                    mVertexSet[v][i] = mVertexSet[u][i];
            }
        // copy set(u) to other affected sets.
        // i.e: u=0, v=3, set(u) = {0, 2, 3}, v = {0, 2, 3}
        // after union, set(2) needs to be replaced by set(u)
        // -- loop set(u)
        for (int i = 0; i < mVertexCount; ++i)
            if (i != u && i != v && true == mVertexSet[u][i])
                // copy set(u) to set(i)
                memcpy(mVertexSet[i], mVertexSet[u],
                       sizeof(bool) * mVertexCount);
        // for (int j = 0; j < mVertexCount; ++j)
        //    mVertexSet[i][j] = mVertexSet[u][j];

        debug(__func__, "[AFTER UNION] vertex set:");
        debugPrintVertexSet();
    }


    /**
     * (public for testing.)
     * implement the algorithm (lines 5 through 9).
     */
    MSTEdgeSet * process(void) {
        info(__func__, "---------------------------------");
        info(__func__, "Processing MST...");
        debug(__func__, "clear total cost to 0.");
        mCost = 0.;
        int u = -1, v = -1;
        double w = 0.;
        string msg;
        SortedEdges tmp(mSortedEdges);
        while (false == tmp.empty()) {
            Edge * e = tmp.top();
            tmp.pop();
            u = e->getFrom();
            v = e->getTo();
            w = e->getW();
            // e = nullptr;    // kill dangling ptr
            msg = "processing edge: (";
            msg += to_string(u) + ", " + to_string(v) + ", " + to_string(w);
            msg += ")";
            debug(__func__, msg);
            if (false == sameSet(u, v)) {
                msg = "not in same set, this edge is added into MST";
                debug(__func__, msg);
                // we need a copy Edge object other than the ptr, to add
                // into mA, or there will be stack dump when this object
                // is being destroyed.
                // msg = "make a copy of the edge and add the copy into MST";
                // Edge * eCopy = new Edge(u, v, w);
                // mA.insert(eCopy);
                // eCopy = nullptr;    // kill dangling ptr
                mA.insert(e);

                // accumlate the cost
                mCost += w;

                msg = "cost so far: ";
                msg += to_string(mCost);
                debug(__func__, msg);
                vertexSetUnion(u, v);
                msg = "union sets ";
                msg += to_string(u) + " and " + to_string(v);
                debug(__func__, msg);
            }
            e = nullptr;
        }
        msg = "MST has been built, cost: ";
        msg += to_string(mCost);
        info(__func__, msg);
        info(__func__, "Done.");
        return &mA;
    }


    // -----------------------------------------------------------------------
    // return the cost of the MST (by summing all of the weights of its edges.
    double getMSTCost(void) const {
        return mCost;
    }


    // -----------------------------------------------------------------------
    // getter for private vertex count
    int getVertexCount(void) const {
        return mVertexCount;
    }


    // -----------------------------------------------------------------------
    // allow one to pretty print the contents of the Kruskal object to an output
    // stream.
    // note: unsigned long casts below should be unsigned long long when building
    // 64-bit versions.
    friend ostream& operator << (ostream & os, const Kruskal &k) {
        os << endl <<
        "--------------------- MST::Kruskal ---------------------" << endl;
        os << "Vertices: " << k.mVertexCount;
        os << ", Vertex Set: 0x" << hex << (unsigned long)k.mVertexSet;
        os << dec << endl;
        os << "MST Size: " << k.mA.size();
        os << ", Edge Queue Size: " << k.mSortedEdges.size() << endl;
        os << "Cost: " << k.mCost << endl << flush;

        // output contents of vertex sets
        os << ":::: Vertex Set ====>" << endl;
        if (k.mVertexSet != nullptr)
            for (int r = 0; r < k.mVertexCount; ++r) {
                os << "  " << r << ": ";
                if (k.mVertexSet[r] == nullptr)
                    os << "  null";
                else
                    for (int c = 0; c < k.mVertexCount; c++)
                        os << k.mVertexSet[r][c];
                os << endl << flush;
            }

        // output contents (edges) in A (the MST)
        os << ":::: MST ====>" << endl;
        // this is simply a for-each loop over each edge in A (the resulting MST)
        for (auto e : k.mA)
            os << "  " << *e << endl << flush;
        // output the contents of the edge set sorted by edge weight.
        // since the only way to traverse a priority queue is to "destroy" it,
        // we'll make a copy of it and destroy the copy.
        os << ":::: Edges in Graph ====>" << endl;
        SortedEdges tmp(k.mSortedEdges);     // edges sorted by weight
        while (!tmp.empty()) {
            Edge * e = tmp.top();
            tmp.pop();
            os << "  " << *e << endl << flush;
        }
        os << "--------------------------------------------------------";
        os << endl << flush;
        return os;
        }
};
#endif /** end of include guard */
