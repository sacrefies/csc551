// -----------------------------------------------------------------------------
// Filename:    Kruskal.hpp
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
#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <exception>

#include  "edge.hpp"

using namespace std;


class Kruskal {

private:
    int mVertexCount = 0;                 // number of nodes/vertices (0..mVertexCount-1)
    bool **mVertexSet = nullptr;          // 2d array indicating what is in each set

    typedef priority_queue<Edge *, vector<Edge *>, Edge> SortedEdges;
    SortedEdges mSortedEdges;             // edges sorted by weight

    typedef set<Edge *> MSTEdgeSet;
    MSTEdgeSet mA;                        // result set of edges in MST
    // -----------------------------------------------------------------------
    // allocate memory for the 2d array representing sets of vertices.
    void initSet(int vCount) {
        mVertexCount = vCount;
        // allocate & init memory for the 2d array
        mVertexSet = new bool *[vCount];
        for (int i = 0; i < vCount; i++)
            mVertexSet[i] = new bool[vCount];
    }

public:
    // ctor which simply sets the numbers of vertices and puts each one in its
    // own set.  if you use this, you will have to add edges on your own and
    // one at a time.
    Kruskal(int vCount) {
        assert(vCount > 0);
        if (vCount < 1)    return;
        initSet(vCount);
        makeSet(vCount);
    }
    // -----------------------------------------------------------------------
    // ctor which loads vertices and edges (and their weights) from an input
    // file.
    Kruskal(string fname) {
        // open the input file
        ifstream in(fname);
        if (in.fail()) {
            cerr << "error opening file" << endl;
            return;
        }

        // read the number of vetices and edges in the file
        int vertices, edges;
        in >> vertices >> edges;
        // put each vertex in its own separate set
        initSet(vertices);
        makeSet(vertices);

        // load the edges and their weights
        for (int i = 0; i < edges; i++) {
            int u, v;
            double w;
            in >> u >> v >> w;
            addEdge(u, v, w);
            // print something every once in a while when processing large
            // input files.
            if (i > 0) {
                if (i % 1000000 == 0)    cout << "!" << flush;
                else if (i % 100000 == 0)    cout << "*" << flush;
                else if (i % 10000 == 0)    cout << "." << flush;
            }
        }

        in.close();
    }
    // -----------------------------------------------------------------------
    // dtor
    ~Kruskal(void) {
        // prints are useful to determine when dtors are actually called (or not).
        // cout << "Kruskal::~Kruskal()" << endl;

        // free vertex sets
        if (mVertexSet != nullptr) {
            for (int i = 0; i < mVertexCount; i++)
                if (mVertexSet[i] != nullptr) {
                    delete[] mVertexSet[i];
                    mVertexSet[i] = nullptr;
                }
            delete[] mVertexSet;
            mVertexSet = nullptr;
        }

        // free anything left
        while (!mSortedEdges.empty()) {
            Edge *e = mSortedEdges.top();
            mSortedEdges.pop();
            delete e;
        }

        // free anything in the MST
#if 1
        // this is simply a for-each loop over each edge in A (the resulting MST)
        for (auto e : mA)
            // e->getW()
            delete e;

#else
        // this iterates over each element in the edge set
        for (MSTEdgeSet::iterator it = mA.begin(); it != mA.end(); ++it)
            // (*it)->getW()
            delete *it;

#endif
        mA.clear();
    }
    // -----------------------------------------------------------------------
    // add the edge  with its weight to the automagically sorted set of
    // edges.
    void addEdge(int u, int v, double w) {
        if (u < 0 || u >= mVertexCount) {
            cerr << "Kruskal:addEdge(u,v,w): bad u " << u << endl;
            return;
        }
        if (v < 0 || v >= mVertexCount) {
            cerr << "Kruskal:addEdge(u,v,w): bad v " << v << endl;
            return;
        }

        Edge *e = new Edge(u, v, w);
        mSortedEdges.push(e);
    }
    // -----------------------------------------------------------------------
    // (public for testing.)
    // put each vertex in an individual set.
    void makeSet(int vCount) {
        // \TODO
    }
    // -----------------------------------------------------------------------
    // (public for testing.)
    // this function returns true if the vertices specified are in the same set,
    // and false otherwise.
    bool sameSet(int u, int v) {
        // make sure that args are valid.
        assert(0 <= u && u < mVertexCount);
        assert(0 <= v && v < mVertexCount);
        if (u < 0 || u >= mVertexCount || v < 0 || v >= mVertexCount)
            return false;

        // \TODO
        return false;
    }
    // -----------------------------------------------------------------------
    // (public for testing.)
    // create the union of two sets.
    void vertexSetUnion(int u, int v) {
        // \TODO
    }
    // -----------------------------------------------------------------------
    // (public for testing.)
    // implement the algorithm (lines 5 through 9).
    MSTEdgeSet * process(void) {
        // \TODO
        return &mA;
    }
    // -----------------------------------------------------------------------
    // return the cost of the MST (by summing all of the weights of its edges.
    double getMSTCost(void) {
        // \TODO
        return 0;
    }
    // -----------------------------------------------------------------------
    // getter for private vertex count
    int getVertexCount(void) {
        return mVertexCount;
    }
    // -----------------------------------------------------------------------
    // allow one to pretty print the contents of the Kruskal object to an output
    // stream.
    // note: unsigned long casts below should be unsigned long long when building
    // 64-bit versions.
    friend ostream& operator<< (ostream& os, const Kruskal& k) {
        os << "--------------------" << endl;
        os << "Kruskal:" << endl;

        os << "    mVertexCount=" << k.mVertexCount;
        os << "    mVertexSet=0x" << hex << (unsigned long)k.mVertexSet <<
            dec << endl;

        // output contents of vertex sets
        if (k.mVertexSet != nullptr)
            for (int r = 0; r < k.mVertexCount; r++) {
                os << "        " << r << ": ";
                if (k.mVertexSet[r] == nullptr)
                    os << "  null";
                else
                    for (int c = 0; c < k.mVertexCount; c++)
                        os << k.mVertexSet[r][c];




                os << endl;
            }

        // output contents (edges) in A (the MST)
        os << "    mA.length=" << k.mA.size() << endl << " ";
        // either of the following is perfectly fine.
        // the first one uses more "modern" syntax.
#if 1
        // this is simply a for-each loop over each edge in A (the resulting MST)
        for (auto e : k.mA)
            os << "       " << *e << " ";

#else
        // this iterates over each element in the edge set
        for (MSTEdgeSet::iterator it = k.mA.begin(); it != k.mA.end(); ++it)
            os << "       " << **it << " ";

#endif

        // output the contents of the edge set sorted by edge weight.
        // since the only way to traverse a priority queue is to "destroy" it,
        // we'll make a copy of it and destroy the copy.
        os << "   mSortedEdges.size=" << k.mSortedEdges.size();
        os << endl;
        SortedEdges tmp(k.mSortedEdges);     // edges sorted by weight
        while (!tmp.empty()) {
            Edge *e = tmp.top();
            tmp.pop();
            os << "        " << *e;
        }

        os << "--------------------" << endl;
        return os;
    }
};
