// ------------------------------------------------------------------------------------
// Filename: VectorBucketSort.h
// Revision: $Id$
// Description: This file contains the VectorBucketSort class definition.
// Created: 02/15/2016 01:20:29 PM
// Compiler: G++
// Author: Jason Meng (jm), jm652564@sju.edu
//
// Copyright (c) 2016-2017 by Jason Meng
// ------------------------------------------------------------------------------------


#include <algorithm>
#include <assert.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <iostream>


/** include guard */
#ifndef VECTORBUCKETSORT_H
#define VECTORBUCKETSORT_H

using namespace std;

class VectorBucketSort {
private:
    // full length of all elements contained by this bucket list
    int mLength = 0;
    // the size of buckets
    int mSize = 0;
    // The buckets
    vector<double> *mBucketList = nullptr;
    // is the elements are sorted?
    bool mIsSorted = false;

public:
    /// Check whether the elements are sorted.
    /// \return Returns true if all the elements are sorted.
    bool isSorted(void) const {
        return mIsSorted;
    }

    /// Get the size of the bucket list maintained by this object.
    /// \return Returns the size of the bucket list.
    int size(void) const {
        return mSize;
    }

    /// bucket sort ctor.  default size is 10 buckets.
    /// \param size The size of the inner buckets. If omitted, the default value is 10.
    VectorBucketSort(int size = 10) {
        cout << "in VectorBucketSort() ctor" << endl;
        assert(size > 0);
        if (size < 1) return;
        mSize = size;
        // create the bucket list array of the appropriate size.
        mBucketList = new vector<double>[size];
        if (mBucketList == nullptr) return;
    }

    /// bucket sort dtor.
    ~VectorBucketSort(void) {
        cout << "in ~VectorBucketSort() dtor" << endl;
        // if there is no list, there's nothing to do.
        if (mBucketList == nullptr) return;
        for (int i = 0; i < mSize; ++i)
            if (!mBucketList[i].empty()) {
                mBucketList[i].clear();
                vector<double>().swap(mBucketList[i]);
            }
        // delete the bucket list itself
        delete[] mBucketList;
        mBucketList = nullptr;
        mSize = 0;
    }

    /// Add a new element to the appropriate list.
    /// \param value A double value which is in [0, 1).
    void add(double value) {
        if (value < 0. || value >= 1.) return;
        if (mBucketList == nullptr) return;

        mIsSorted = false;
        // which bucket?
        int index = (int) (value * mSize);
        // adding this value into the bucket vector at the beginning
        mBucketList[index].push_back(value);
        mLength++;
    }

    /// Sort all of the lists.
    void sortAll(void) {
        if (mBucketList == nullptr) return;
        if (mIsSorted) return;

        for (int i = 0; i < mSize; i++)
            sort(mBucketList[i].begin(), mBucketList[i].end());
        mIsSorted = true;
    }

    /// Get the i-th (starting at 0) value in the list.
    /// if there is no such entry, then return NAN.
    ///
    /// \param i The index at which the desired value is.
    /// \return Returns the value at the given index
    ///         or NAN if the given index is invalid.
    double get(const int i) {
        // O(n)
        int count = 0;
        for (int bucketIndex = 0; bucketIndex < mSize; ++bucketIndex)
            for (int j = 0; j < (int) mBucketList[bucketIndex].size(); ++j) {
                if (count == i) return mBucketList[bucketIndex][j];
                count++;
            }
        return NAN;
    }

#if defined(GRAD) && defined(EXTRA_CREDIT)

    /// An alternative get method to get the i-th (starting at 0) value in the list.
    /// if there is no such entry, then return NAN.
    ///
    /// This implement is a bit more efficient that get(i)
    /// because its computation complexity is O(bucketSize).
    ///
    /// \param i The index at which the desired value is.
    /// \return Returns the value at the given index
    ///         or NAN if the given index is invalid.
    double get2(const int i) {
        if (i >= mLength) return NAN;

        if (i < (int) mBucketList[0].size()) return mBucketList[0][i];

        int count = 0, bucketIndex = 0;
        while (bucketIndex < mSize && ((int) mBucketList[bucketIndex].size() + count - 1) < i)
            count += (int) mBucketList[bucketIndex++].size();
        // failsafe: prevent it from crashing
        if (count > i || mBucketList[bucketIndex].empty() ||
            (int) mBucketList[bucketIndex].size() <= (i - count))
            return NAN;

        return mBucketList[bucketIndex][i - count];
    }

#endif
    // -----------------------------------------------------------------------
#ifdef GRAD

    /// Get the chain size of the bucket at the given position.
    /// \param which The position of a bucket.
    /// \return The size of the chain.
    int getCount(int which) const {
        if (which < 0 || which >= mSize)
            return -1;
        return (int) mBucketList[which].size();
    }

    /// Get the load factor (LF), or return NAN if this object is not initialized correctly.
    /// \return The load factor or NAN.
    double getLoadFactor(void) const {
        // the LF is the average chain length (# of data values added / total #
        // of bucket lists).
        return (mSize == 0 || mBucketList == nullptr) ? NAN : (double) mLength / (double) mSize;
    }

    /// Get the length of the elements contained by this object.
    /// \return The total number of the elements.
    int getLength(void) const {
        return mLength;
    }

#endif

    // -----------------------------------------------------------------------
    // pretty print the contents of the bucket list to an output stream.
    friend ostream &operator<<(ostream &os, const VectorBucketSort &bs) {
        os << "  mSize=" << bs.mSize;
        os << "  mBucketList=0x" << hex << (unsigned long) (bs.mBucketList) <<
           dec << endl;

        for (int i = 0; i < bs.mSize; i++) {
            os << "[" << i << "][" << bs.mBucketList[i].size() << "]";
            for (int j = 0; j < (int) bs.mBucketList[i].size(); j++)
                os << " " << setprecision(6) << bs.mBucketList[i].at(j);
            os << endl;
        }
        return os;
    }
};

#endif
