// -----------------------------------------------------------------------------
// Filename:    Kruskal.hpp
// Revision:    $Id$
// Description: this file contains the definition of the Edge class. An edge
//              consists of a u, a v, and a weight. No changes necessary.
// Created:     04/20/2016 01:20:29 PM
// Compiler:    G++
// Author:      George J. Grevera, Ph.D.
//
// Copyright (c) 2016 by Jason Meng, no rights reserved.
// Copyright (c) George J. Grevera, 2016.  All rights reserved.
// -----------------------------------------------------------------------------

#include <iostream> // for ostream, cout, endl


using std::ostream;


class Edge {
private:
    int mFrom   = -1;     // 'from' vertex (i.e., u in <u,v>)
    int mTo     = -1;     // 'to'   vertex (i.e., v in <u,v>)
    double mWeight = -1;     // weight associated with this edge

public:
    Edge(int from, int to, double weight) {
        mFrom = from;
        mTo = to;
        mWeight = weight;
    }

    // -----------------------------------------------------------------------
    // dtor (nothing to do)
    ~Edge(void) {
        // prints are useful to determine when dtors are actually called (or not).
        // cout << "Edge::~Edge" << endl;
    }

    // -----------------------------------------------------------------------
    // getters:
    double getW(void) {
        return mWeight;
    }

    int getFrom(void) {
        return mFrom;
    }

    int getTo(void) {
        return mTo;
    }

    // -----------------------------------------------------------------------
    // allow one to pretty print the contents of the Kruskal object to an
    // output stream.
    friend ostream& operator<< (ostream& os, const Edge& e) {
        os << "edge: f=" << e.mFrom << " t=" << e.mTo << " w=" << e.mWeight;
        os << endl;
        return os;
    }

    // -----------------------------------------------------------------------
    // do not use (used for priority queue sorting):
    Edge(void) {}
    // -----------------------------------------------------------------------
    // do not use (used for priority queue sorting):
    bool operator() (const Edge *e1, const Edge *e2) {
        return e2->mWeight < e1->mWeight;
    }
};
