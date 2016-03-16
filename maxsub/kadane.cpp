// -----------------------------------------------------------------------------
//       Filename: kadane.cpp
//       Revision: $Id$
//    Description: This file includes the implementation of Kadane's algorithm
//                 to find a maximum subarray of an array.
//        Created: 02/25/2016 03:20:49 PM
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
using std::string;


/**
 * Search a specified array of int to find a subarray whose element summation is
 * the maximum among all possible subarrays of the array. This function is an
 * implementation of Kadane's algorithm.
 *
 * @param list      An array of int.
 * @param size      The size of the specified array.
 * @param bestStart The starting index of the found max subarray,
 *                  one of the 3 return values.
 * @param bestEnd   The ending index of the found max subarray.
 *                  one of the 3 return values.
 * @param bestSum   The summation of the found max subarray.
 *                  one of the 3 return values.
 */
void kadane(int list[], int size, int& bestStart, int& bestEnd, int& bestSum) {
    int currSum, localStart;
    /** only for debugging   */
    stringstream msg;

    bestSum = INT_MIN;
    bestStart = bestEnd = -1;

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
        msg << "The given size < 1.";
        msg << " bestStart, bestEnd are set as -1,";
        msg << " bestSum is set as INT_MIN.";
        error(__func__, msg.str());
        msg.clear();
        msg.str("");
        msg << "size=" << size;
        debug(__func__, msg.str());
        return;
    }

    bestStart = bestEnd = localStart = 0;
    bestSum = currSum = list[0];

    if (size == 1) {
        msg << "The given size = 1.";
        msg << " The max sub array is the specified array itself.";
        info(__func__, msg.str());
        msg.clear();
        msg.str("");
        msg << "size=" << size;
        debug(__func__, msg.str());
        return;
    }

    // print the input array
    printArray(size, list, "Array input:");
    for (int i = 1; i < size; ++i) {
        // continue adding up
        currSum += list[i];
        if (list[i] > currSum) {
            // when this case happens, the max-sub actually is reset to list[i],
            // therefore bestStart has a new index to record ==> i
            currSum = list[i];
            localStart = i;
        }

        if (bestSum < currSum) {
            bestStart = localStart;
            bestEnd = i;
            bestSum = currSum;
        }
    }
    // debugging
    msg.clear();
    msg.str("");
    msg << "bestStart=" << bestStart;
    msg << " bestEnd=" << bestEnd;
    msg << " bestSum=" << bestSum;
    debug(__func__, msg.str());
    printArray(bestStart, bestEnd, list, "The max subarray:");
} // kadane
