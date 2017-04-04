// file  : VectorBucketSort.h
// author: ...
// desc. : this file contains the VectorBucketSort class definition.

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
    int mLength = 0; // full length of all elements contained by this bucketlist
    int mSize = 0;  // # of buckets
    vector<double> * mBucketList = nullptr;  // treat as an array

#ifdef  GRAD
    int * mCounter = nullptr;  // number of buckets in each individual chain
    bool isSorted = false;
#endif

public:
    bool sorted(void) const {
        return isSorted;
    }

    int size(void) const {
        return mSize;
    }

    // bucket sort ctor.  default size is 10 buckets.
    VectorBucketSort(int size = 10) {
        cout << "in VectorBucketSort() ctor" << endl;
        assert(size > 0);
        if (size < 1) return;
        mSize = size;
        // create the bucket list array of the appropriate size.
        mBucketList = new vector<double>[size];
        if (mBucketList == nullptr) return;

        #ifdef GRAD
        // create the bucket list length array
        mCounter = new int[size];
        for (int i = 0; i < size; ++i)
            mCounter[i] = 0;
        #endif
    }
    // -----------------------------------------------------------------------
    // bucket sort dtor.
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
        #ifdef GRAD
        delete[] mCounter;
        mCounter = nullptr;
        #endif
    }
    // -----------------------------------------------------------------------
    // this function should add a new element to the appropriate list
    // _in arbitrary order_.
    void add(double value) {
        if (value < 0. || value >= 1.) return;
        // which bucket?
        int index  = (int)(value * mSize);
        // adding this value into the bucket vectory at the beginning
        mBucketList[index].push_back(value);
        mLength++;

        #ifdef GRAD
        mCounter[index]++;
        #endif
    }
    // -----------------------------------------------------------------------
    // this function sorts all of the lists.
    void sortAll(void) {
        if (mBucketList == nullptr)    return;
        for (int i = 0; i < mSize; i++)
            sort(mBucketList[i].begin(), mBucketList[i].end());
        isSorted = true;
    }
    // -----------------------------------------------------------------------
    // return the ith (starting at 0) value in the list.
    // if there is no such entry, then return NAN.
    double get(const int i) {
        // O(n)
        int count = 0;
        for (int bucketIndex = 0; bucketIndex < mSize; ++bucketIndex)
            for (int j = 0; j < (int)mBucketList[bucketIndex].size(); ++j) {
                if (count == i) return mBucketList[bucketIndex][j];
                count++;
            }
        return NAN;
    }
    // -----------------------------------------------------------------------
#if defined(GRAD) && defined(EXTRA_CREDIT)
    /**
     * An alternative get method with better performance.
     */
    double get2(const int i) {
        if (i >= mLength) return NAN;

        int count = 0, bucketIndex = 0;
        while (bucketIndex < mSize && (mCounter[bucketIndex] + count - 1) < i)
            count += mCounter[bucketIndex++];
        // failsafe: prevent from crashing
        if (count > i) return NAN;

        return mBucketList[bucketIndex][i - count];
    }
#endif
    // -----------------------------------------------------------------------
#ifdef GRAD
    // this function returns the number of buckets in a particular bucket
    // list.
    int getCount(int which) {
        if (which < 0 || which >= mSize)
            return NAN;

        return mCounter[which];
    }

    // this function calculates and returns the load factor (LF).
    // the LF is the average chain length (# of data values added / total #
    // of bucket lists).
    double getLoadFactor(void) {
        return (double)mLength / (double)mSize;
    }

    int length(void) const {
        return mLength;
    }
#endif

    // -----------------------------------------------------------------------
    // pretty print the contents of the bucket list to an output stream.
    friend ostream& operator<< (ostream& os, const VectorBucketSort& bs) {
        os << "  mSize=" << bs.mSize;
        os << "  mBucketList=0x" << hex << (unsigned long)(bs.mBucketList) <<
            dec << endl;

        for (int i = 0; i < bs.mSize; i++) {
            os << "[" << i << "][" << bs.mCounter[i] << "]";
            for (int j = 0; j < (int)bs.mBucketList[i].size(); j++)
                os << " " << setprecision(6) << bs.mBucketList[i].at(j);
            os << endl;
        }
        return os;
    }
};
#endif
