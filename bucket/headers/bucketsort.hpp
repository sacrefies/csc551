// -----------------------------------------------------------------------------
// Filename:    bucketsort.hpp
// Revision:    $Id$
// Description: this file contains the BucketSort class definition.
// Created:     04/08/2016 03:20:29 PM
// Compiler:    G++
// Author:      Jason Meng (jm), jm652564@sju.edu
//
// Copyright (c) 2016 by Jason Meng, no rights reserved.
// -----------------------------------------------------------------------------


#include <cstddef>   // nullptr
#include <exception> // invalid_argument
#include <cmath>     // NAN
#include <string>    // string, to_string
#include <iostream>  // ostream, cout, endl, hex
#include <iomanip>   // setprecision, setw, setfill
// custom includes
#include "bucket.hpp"
#include "logging.hpp"

/** include guard */
#ifndef BUCKET_SORT_CLASS_H
#define BUCKET_SORT_CLASS_H

using std::cout;
using std::endl;
using std::ostream;
using std::hex;
using std::dec;
using std::invalid_argument;
using std::out_of_range;
using std::runtime_error;
using std::string;
using std::to_string;
using std::setprecision;
using std::fixed;
using std::setw;
using std::flush;

namespace bucketsort {
    /**
     * A class that holds an array of pointers of Bucket objects.
     */
    class BucketSort {
    private:

        // # of buckets
        int mSize = 0;
        // the interval between list[i] and list[i+1], with regard to mSize.
        // if mSize = 10, interval = 1.0/mSize
        // list[i] should hold values from [i*interval, (i+1)*interval)
        double mInterval = 0.00;
        // buckets = list (array) of pointers to entries in a particular bucket
        Bucket ** mBucketList = nullptr;
        // threshold value for comparison on 2 doubles.
        // static const double comp_threshold = 0.00001;
        static const int mAmplifier = 100000000;
        #ifdef GRAD
        // an array to store the lengths of each mBucketList[i]
        int * mCounter = nullptr;
        #endif
        // Bucket length, the number of Bucket existing in this list
        int mLen = 0;

        #ifdef GRAD
        /**
         * Get a proper index of one bucket list which has
         * the bucket that bucketPos suggests.
         *
         * This method also returns posAtBucket as the suggested Bucket
         * index in the bucket list at mBucketList[getBucketListIndex]
         */
        int getBucketListIndex(const int bucketPos, int& posAtBucket) {
            if (bucketPos < 0) {
                posAtBucket = -1;
                return -1;
            }

            int index, bucket_count = 0, last_bucket_count = 0;
            for (index = 0; index < mSize; ++index) {
                last_bucket_count = bucket_count;
                bucket_count     += mCounter[index];
                if (bucket_count > bucketPos)
                    break;
            }
            posAtBucket = bucketPos - last_bucket_count;

            return (bucket_count > bucketPos)? index: -1;
        }

        #endif // ifdef GRAD

    public:

        /**
         * Returns this bucket list's size;
         */
        int size(void) const {
            return mSize;
        }

        /**
         * Returns the number of Buckets in this bucket list.
         */
        int length(void) const {
            return mLen;
        }

        #ifdef GRAD
        /**
         * Return the number of buckets in a particular bucket list.
         */
        int getCount(int which) const {
            if (which < 0 || which >= mSize)
                throw out_of_range("No such chain: which=" + to_string(which));

            return mCounter[which];
        }

        /**
         * this function calculates and returns the load factor (LF).  the LF is
         * the average chain length (# of data values added / total # of bucket
         * // lists).
         */
        double getLoadFactor(void) const {
            return (double)mLen / (double)mSize;
        }

        #endif // ifdef GRAD

        /**
         * bucket sort ctor. default size is 10.
         *
         * @param size  An integer for the desired size of the buckets.
         */
        BucketSort(int size = 10) {
            if (size <= 0) {
                string msg = "Invalid size = ";
                throw invalid_argument(msg + to_string(size));
            }
            debug(__func__, "in BucketSort() ctor");
            mSize     = size;
            mLen      = 0;
            mInterval = (1.0 * mAmplifier) / (((double)size) * mAmplifier);
            // create the bucket list array of the appropriate size.
            mBucketList = new Bucket *[size];
            if (mBucketList == nullptr)
                throw runtime_error("Failed to allocate memory for bucket list");

            // each entry in the list (array) is a pointer to a bucket.
            // init each to null.
            for (int i = 0; i < size; ++i)
                mBucketList[i] = nullptr;

            #ifdef GRAD
            // create the bucket list length array
            mCounter = new int[size];
            for (int i = 0; i < size; ++i)
                mCounter[i] = 0;
            #endif
        }

        /*
         * bucket sort dtor.
         * note that this also cascades destruction to the bucket list elements
         * as well.
         */
        ~BucketSort(void) {
            debug(__func__, "in ~BucketSort() dtor");
            // if there is no list, there's nothing to do.
            if (mBucketList == nullptr)
                return;

            // delete each bucket in the bucket list.
            for (int i = 0; i < mSize; i++)
                if (mBucketList[i] != nullptr) {
                    delete mBucketList[i];
                    mBucketList[i] = nullptr;
                }
            // finally, delete the bucket list itself
            delete[] mBucketList;
            mBucketList = nullptr;

            #ifdef GRAD
            if (mCounter == nullptr)
                return;

            delete[] mCounter;
            mCounter = nullptr;
            #endif
        }

        /*
         * this function should add a new element to the appropriate list
         * in the correct order.
         *
         * @param value A double value to be added into the bucket list.
         */
        void add(double value) {
            if (value < 0. || value * mAmplifier - mAmplifier > 0.000001) {
                string msg = "Invalid value = ";
                throw invalid_argument(msg + to_string(value));
            }

            // which bucket?
            int index  = (int)((value * mAmplifier) / (mInterval * mAmplifier));
            Bucket * b = new Bucket();
            b->mData = value;
            Bucket * cursor = mBucketList[index];
            Bucket * last   = mBucketList[index];

            for (; cursor != nullptr; cursor = cursor->mNext) {
                // looking for one bucket which holds a mData > value
                if (cursor->mData * mAmplifier > value * mAmplifier)
                    break;
                last = cursor;
            }

            #ifdef GRAD
            mCounter[index]++;
            #endif
            mLen++;

            // mBucketList[index] is empty
            if (last == nullptr) {
                mBucketList[index] = b;
                b = nullptr;

                return;
            }

            if (cursor == nullptr)
                // not found a bigger one
                cursor = last;
            else {
                // found one item > value
                // b should insert in front of item
                // so swap the each other's data
                // ---> always let the smaller one stay in the list
                b->mData      = cursor->mData;
                cursor->mData = value;
            }
            // insert b right after cursor
            b->mNext      = cursor->mNext;
            cursor->mNext = b;

            // clean up
            b = cursor = last = nullptr;
        } // add

        /**
         * return the ith value in the list.
         * if there is no such entry, then return NAN.
         */
        double get(const int i) {
            int index = -1;

            Bucket * cursor = nullptr;

            // BucketSort[0]: 0.024207 -> 0.148600 -> null
            // BucketSort[1]: 0.521781 -> 0.700223 -> 0.813572 -> null
            for (int head = 0; (head < mSize && index < i); ++head) {
                cursor = mBucketList[head];
                if (cursor == nullptr)
                    continue;

                if (index++ == i)
                    break;

                while (cursor != nullptr && index < i) {
                    cursor = cursor->mNext;
                    index++;
                }
                if (cursor == nullptr)
                    index--;
            }

            if (cursor != nullptr)
                return cursor->mData;

            return (NAN);
        } // get

        #if defined(GRAD) && defined(EXTRA_CREDIT)
        /**
         * return the ith value in the list.
         * if there is no such entry, then return NAN.
         */
        double get2(const int i) {
            /*
             * This method is better than get() because get()'s time
             *
             * Best case: i = 0, mBucketList[0] != nullptr;
             *   get() = O(1), get2() = O(1);
             * Worst case: i > mLen, every bucket resides in mBucketList[mSize-1]
             *   get() = O(mSize + mLen), get2() = O(mSize + mLen)
             * Average case: i < mLen, buckets are evenly distributed
             *   get() = O(i + k), 0 <= k <= mSize,
             *   get2() = O(k + i - mLen/mSize * k), 0 <= k <= mSize
             *          = O(i + k * (1 - mLen/mSize))
             */

            // calc the correct offset pos, at mBucketList[index]
            int pos;
            int index = getBucketListIndex(i, pos);

            // if index < 0, i is illegal
            // else goto mBucketList[index], get item at pos (the offset)
            // since i is not checked here, so pos can be greater than
            // the offset of the last Bucket in mBucketList[index]
            if (index >= 0) {
                Bucket * cursor = mBucketList[index];
                for (int offset = 0; (offset < pos && cursor != nullptr);
                     ++offset)
                    cursor = cursor->mNext;
                // make 100% sure no error
                if (cursor != nullptr)
                    return cursor->mData;
            }

            return (NAN);
        }

        #endif // if  defined(GRAD) && defined(EXTRA_CREDIT)

        // -----------------------------------------------------------------------
        // allow one to pretty print the contents of the bucket list to an output stream.
        friend ostream& operator<< (ostream& os, const BucketSort& bs) {
            os << "  mSize=" << bs.mSize;
            os << "  mloadFactor=" << setprecision(3) << bs.getLoadFactor();
            os << "  mBucketList=0x" << hex << (unsigned long)(bs.mBucketList);
            os << dec << endl;
            string tmp;
            for (int i = 0; i < bs.mSize; ++i) {
                tmp = "BucketSort[" + to_string(i) + "]:";
                os << setw(16) << tmp;
                #ifdef GRAD
                tmp = "count=" + to_string(bs.mCounter[i]) + ":";
                os << setw(10) << tmp << flush;
                #endif
                if (bs.mBucketList[i] == nullptr)
                    os << " -> null";
                else {
                    os << " -> ";
                    os << fixed << setprecision(6);
                    os << *bs.mBucketList[i];
                }
                if (i < bs.mSize - 1)
                    os << endl;
            }
            os << flush;
            return (os);
        }
    };
}

#endif // ifndef BUCKET_SORT_CLASS_H
/** end of include guard */
