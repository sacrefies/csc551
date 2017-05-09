// -----------------------------------------------------------------------------
// Filename:    Edge.h
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
#include "logging.h"

#ifndef EDGE_H
#define EDGE_H


using std::ostream;
using std::endl;


/// A class which represents an edge in a graph.
class Edge {
private:
    int mFrom = -1;     // 'from' vertex (i.e., u in <u,v>)
    int mTo = -1;     // 'to'   vertex (i.e., v in <u,v>)
    double mWeight = -1;     // weight associated with this edge

public:
    /// Create an instance of class \c Edge.
    /// \param from The starting vertex of the edge.
    /// \param to The ending vertex of the edge.
    /// \param weight the weight of this edge.
    Edge(int from, int to, double weight) {
        mFrom = from;
        mTo = to;
        mWeight = weight;
    }

    /// dtor (nothing to do)
    ~Edge(void) {
        // prints are useful to determine when dtors are actually called (or not).
        debug(__func__, "Edge::~Edge");
    }

    /// Get the weight of this edge.
    double getW(void) const {
        return mWeight;
    }

    /// Get the starting vertex of this edge.
    int getFrom(void) const {
        return mFrom;
    }

    /// Get the ending vertex of this edge.
    int getTo(void) const {
        return mTo;
    }

    /// allow one to pretty print the contents of the Kruskal object to an
    /// output stream.
    friend ostream &operator<<(ostream &os, const Edge &e) {
        os << "edge: " << e.mFrom << " --" << e.mWeight << "-- " << e.mTo;
        return os;
    }

    /// do not use (used for priority queue sorting):
    Edge(void) {}

    /// do not use (used for priority queue sorting):
    bool operator()(const Edge *e1, const Edge *e2) {
        return e2->mWeight < e1->mWeight;
    }
};

#endif /** end of include guard */
