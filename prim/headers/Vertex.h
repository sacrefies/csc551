// -----------------------------------------------------------------------------
// Filename:    Vertex.hpp
// Revision:    $Id$
// Description: this file contains the definition of the Vertex class.
//              a vertex i consists of an i, the value of its parent p, and a key
//              value. the key value is the edge weight between i and p.
//              no changes necessary.
// Created:     04/26/2016 01:20:29 PM
// Compiler:    G++
// Author:      George J. Grevera, Ph.D.
//
// Copyright (c) 2016 by Jason Meng, no rights reserved.
// Copyright (c) George J. Grevera, 2016.  All rights reserved.
// -----------------------------------------------------------------------------


/** include guard */
#ifndef VERTEX_H
#define VERTEX_H


#include <sstream>          // stringstream
#include <limits>           // numeric_limits
#include <iostream>         // os
#include <iomanip>
// home made headers
#include "logging.h"


using std::numeric_limits;
using std::stringstream;
using std::hex;
using std::dec;
using std::endl;
using std::ostream;
using std::setprecision;


/**
 * A class which represents a vertex in Prim's MST algorithm.
 */
class Vertex {

private:
    /** vertex number. -1 means this vertex is not initialized properly */
    int mVert = -1;
    /**parent vertex number (-1 = null, no parent) */
    int mParent = -1;
    /** key value for this entry */
    double mKey = DBL_MAX();

    /** holds a double_max value for convenience */
    const double DBL_MAX(void) const {
        return numeric_limits<double>::max();
    }

public:
    /**
     * Create and initialize an instance of Vertex class.
     *
     * @param vertex     An integer which represents a vertex
     * @param key        The current key value of this vertex
     * @param parent     The parent vertex of this vertex
     */
    Vertex(int vertex, double key, int parent) {
        mVert = vertex;
        mKey = key;
        mParent = parent;
    }

    /**
     * dtor (nothing to do)
     */
    ~Vertex(void) {
        // prints are useful to determine when dtors are actually called
        // (or not).
        stringstream msg;
        msg << "disposing Vertex@" << hex << this << dec;
        debug(__func__, msg.str());
        msg.clear();
        msg.str("");
    }

    /**
     * getter for vertex number
     */
    int getI(void) const {
        return mVert;
    }

    /**
     * Getter for the parent vertex number
     */
    int getParent(void) const {
        return mParent;
    }

    /**
     * Getter for the key value.
     */
    double getKey(void) const {
        return mKey;
    }

    /**
     * allow one to pretty print the contents of the Vertex object to an output
     * stream.
     */
    friend ostream &operator<<(ostream &os, const Vertex &v) {
        os << "vertex: (i=" << v.mVert << ",";
        if (v.mKey == v.DBL_MAX())
            os << "MAX";
        else
            os << setprecision(2) << v.mKey << ",";
        os << "parent=" << v.mParent << ")" << endl;
        return os;
    }

    /// do not use (used for priority queue sorting)
    Vertex(void) {}

    /// do not use (used for priority queue sorting)
    bool operator()(const Vertex *v1, const Vertex *v2) {
        return v2->mKey < v1->mKey;
    }
};

#endif /** end of include guard */
