// -----------------------------------------------------------------------------
// Filename:    bucket.hpp
// Revision:    $Id$
// Description: this file contains the Bucket class definition.
// Created:     04/08/2016 01:20:29 PM
// Compiler:    G++
// Author:      Jason Meng (jm), jm652564@sju.edu
//
// Copyright (c) 2016 by Jason Meng, no rights reserved.
// -----------------------------------------------------------------------------


#include <cstddef>  // for nullptr
#include <iostream> // for ostream, cout, endl
#include <iomanip>  // setprecision, setw, setfill

#include "logging.hpp"


/** include guard */
#ifndef BUCKET_CLASS_H
#define BUCKET_CLASS_H

using std::ostream;
using std::cout;
using std::endl;

namespace bucketsort {
    /**
     * Class Bucket defines a singly linked list node data structure.
     */
    class Bucket {
    public:

        double mData = -1.0;    // data value for bucket
        Bucket *mNext = nullptr; // ptr to next bucket

        /**
         * bucket dtor.
         *  note that this cascades destruction to the next element in the list.
         *  that way, the entire list is dtor's automagically.
         */
        ~Bucket(void) {
            debug(__func__, "in ~Bucket() dtor");
            if (mNext != nullptr) {
                delete mNext;
                mNext = nullptr;
            }
        }

        /**
         * allow one to pretty print the contents of a bucket to an output stream.
         * note that this cascades printing to the next element in the list.
         * that way, the entire list is printed automagically.
         */
        friend ostream& operator<< (ostream& os, const Bucket& b) {
            if (b.mNext != nullptr)
                os << b.mData << " -> " << *b.mNext;
            else
                os << b.mData << " -> null";

            return os;
        }
    };
}

#endif /* ifndef BUCKET_CLASS_H */
/** end of include guard */
