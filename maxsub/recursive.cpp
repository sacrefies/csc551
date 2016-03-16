// -----------------------------------------------------------------------------
//       Filename: recursive.cpp
//       Revision: $Id$
//    Description: This file include functions which use recursive approach to
//                 search in an array for its maximum subarray
//        Created: 02/15/2016 01:20:49 PM
//       Compiler: G++
//         Author: Jason Meng (jm), jm652564@sju.edu
//
// Copyright (c) 2016 by Jason Meng, no rights reserved.
// -----------------------------------------------------------------------------

#include <climits>
#include <iostream>
#include <sstream>
#include "headers/arrayUtils.h"
#include "headers/logging.h"


using std::cout;
using std::endl;
using std::stringstream;


/**
 * Search for the maximum subarray in an array starting from the middle position
 * in the array.
 *
 * @param list          An array of int in which the function looks up for a max
 *                      subarray.
 * @param low           The index that the search is to begin with.
 * @param mid           The median of the indices of the specified array.
 * @param high          The index that the search is to end with.
 * @param bestStart     The starting index of the found max subarray,
 *                      one of the 3 return values.
 * @param bestEnd       The ending index of the found max subarray.
 *                      one of the 3 return values.
 * @param bestSum       The summation of the found max subarray.
 *                      one of the 3 return values.
 */
static void find_maximum_subarray_crossover(int list[], int low, int mid,
                                            int high, int& bestStart,
                                            int& bestEnd, int& bestSum) {
    /** only for debugging        */
    stringstream msg;

    // print the input array
    printArray(low, high, list, "Crossover:");
    /** vars for debugging ends   */

    int lMax = INT_MIN,
        rMax = INT_MIN;
    int sum = 0;

    // get max subarray of mid-left part, the ending i is the bestStart.
    for (int i = mid; i >= low; --i) {
        sum += list[i];
        if (sum > lMax) {
            lMax = sum;
            bestStart = i;
            /** debugging                */
            msg << "lmax=" << lMax << ", bs=" << i;
            debug(__func__, msg.str());
            msg.clear();
            msg.str("");
            /** debugging ends           */
        }
    }
    // clear up sum
    sum = 0;
    // get max subarray of mid-right part, the ending i is the bestEnd
    for (int i = mid + 1; i <= high; ++i) {
        sum += list[i];
        if (sum > rMax) {
            rMax = sum;
            bestEnd = i;
            /** debugging                */
            msg << "rmax=" << lMax << ", be=" << i;
            debug(__func__, msg.str());
            msg.clear();
            msg.str("");
            /** debugging ends           */
        }
    }
    // set the best sum = left + right
    bestSum = rMax + lMax;

    /** debugging                */
    msg << "bestSum=" << bestSum;
    msg << ", bestStart=" << bestStart;
    msg << ", bestEnd=" << bestEnd;
    debug(__func__, msg.str());
    /** debugging ends           */
} // find_maximum_subarray_crossover


/**
 * Search for a max subarray in a specified array from index low to index high.
 *
 * @param list          An array of int in which the function looks up for a max
 *                      subarray.
 * @param low           The index that the search is to begin with.
 * @param high          The index that the search is to end with.
 * @param bestStart     The starting index of the found max subarray,
 *                      one of the 3 return values.
 * @param bestEnd       The ending index of the found max subarray.
 *                      one of the 3 return values.
 * @param bestSum       The summation of the found max subarray.
 *                      one of the 3 return values.
 */
static void find_maximum_subarray(int list[], int low, int high, int& bestStart,
                                  int& bestEnd, int& bestSum) {
    // debugging
    printArray(low, high, list, "Looking into:");

    bestStart = low;
    bestEnd = high;
    bestSum = list[low];
    // base case: only one element in list[];
    if (low == high) {
        // debugging
        printArray(bestStart, bestEnd, list, "Found subarray:");
        return;
    }

    /** only for debugging    */
    stringstream msg;
    /** declare ends          */

    // results from the left
    int lStart, lEnd, lMax;
    // results from the right
    int rStart, rEnd, rMax;
    // results from the crossover
    int cStart, cEnd, cMax;

    // get the index of the median position
    int mid = (high + low) >> 1;

    msg << "low=" << low << " mid=" << mid << " high=" << high;
    debug(__func__, msg.str());
    msg.clear();
    msg.str("");

    // searching the left half
    find_maximum_subarray(list, low, mid, lStart, lEnd, lMax);
    // searching the right half
    find_maximum_subarray(list, mid + 1, high, rStart, rEnd, rMax);
    // searching the cross part sitting in the middle of the array.
    find_maximum_subarray_crossover(list, low, mid, high, cStart, cEnd, cMax);

    // debugging
    msg << "ls=" << lStart << " le=" << lEnd << " lm=" << lMax << endl;
    msg << "rs=" << rStart << " re=" << rEnd << " rm=" << rMax << endl;
    msg << "cs=" << cStart << " ce=" << cEnd << " cm=" << cMax;
    debug(__func__, msg.str());
    msg.clear();
    msg.str("");

    // compare and get the max among the sums gotten from left, right and cross
    if (lMax >= rMax && lMax >= cMax) {
        bestStart = lStart;
        bestEnd = lEnd;
        bestSum = lMax;
    } else if (rMax >= lMax && rMax >= cMax) {
        bestStart = rStart;
        bestEnd = rEnd;
        bestSum = rMax;
    } else {
        bestStart = cStart;
        bestEnd = cEnd;
        bestSum = cMax;
    }

    // debugging
    msg << "bestStart=" << bestStart;
    msg << " bestEnd=" << bestEnd;
    msg << " bestSum=" << bestSum;
    debug(__func__, msg.str());
    printArray(bestStart, bestEnd, list, "Found subarray:");

} // find_maximum_subarray


/**
 * Search entire array for a maximum subarray by using divide-and-conquer
 * approach. This is a recusive method.
 *
 * @param list          An array of int in which the function looks up for a max
 *                      subarray.
 * @param size          The size of the array.
 * @param bestStart     The starting index of the found max subarray,
 *                      one of the 3 return values.
 * @param bestEnd       The ending index of the found max subarray.
 *                      one of the 3 return values.
 * @param bestSum       The summation of the found max subarray.
 *                      one of the 3 return values.
 */
void find_maximum_subarray(int list[], int size, int& bestStart, int& bestEnd,
                           int& bestSum) {
    stringstream msg;

    bestStart = bestEnd = -1;
    bestSum = INT_MIN;

    if (list == NULL) {
        msg << "The specified array is NULL.";
        msg << " bestStart, bestEnd as set as -1,";
        msg << " bestSum is set as INT_MIN.";
        error(__func__, msg.str());
        msg.clear();
        msg.str("");
        msg << "list=NULL, size=" << size;
        debug(__func__, msg.str());
        return;
    }

    if (size < 1) {
        msg << "The specified size is less than 1.";
        msg << " bestStart, bestEnd as set as -1,";
        msg << " bestSum is set as INT_MIN.";
        error(__func__, msg.str());
        msg.clear();
        msg.str("");
        msg << "size=" << size;
        debug(__func__, msg.str());
        return;
    }

    bestSum = list[0];
    bestStart = bestEnd = 0;

    if (size == 1) {
        msg << "The given size = 1.";
        msg << " The max sub array is the specified array itself.";
        info(__func__, msg.str());
        msg.clear();
        msg.str("");
        msg << "list[0]=" << list[0] << ", size=" << size;
        debug(__func__, msg.str());
        return;
    }

    // print the input array
    printArray(size, list, "Array input:");
    // recursive approach
    find_maximum_subarray(list, 0, size - 1, bestStart, bestEnd, bestSum);
    // debugging
    msg.clear();
    msg.str("");
    msg << "bestStart=" << bestStart;
    msg << " bestEnd=" << bestEnd;
    msg << " bestSum=" << bestSum;
    debug(__func__, msg.str());
    printArray(bestStart, bestEnd, list, "The max subarray:");
} // find_maximum_subarray
