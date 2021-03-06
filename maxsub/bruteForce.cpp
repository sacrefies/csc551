// -----------------------------------------------------------------------------
//       Filename: bruteForce.cpp
//       Revision: $Id$
//    Description: This file includes the implementations to looking for
//                 the maximum sub array in a given array.
//        Created: 02/15/2016 01:20:29 PM
//       Compiler: G++
//         Author: Jason Meng (jm), jm652564@sju.edu
//
// Copyright (c) 2016 by Jason Meng
// -----------------------------------------------------------------------------


// C++ includes
#include <climits>
#include <iostream>
#include <sstream>
// custom includes
#include "headers/arrayUtils.h"
#include "headers/logging.h"


using std::stringstream;
using std::cout;
using std::endl;


/**
 * This function implements a brute force fashion in n^2 time complexity
 * to find a subarray whose element sum is the maximum
 * in the given array.
 *
 * @param   list        A array to search its max subarray.
 * @param   size        The size of list.
 * @param   bestStart   The starting index of the found subarray,
 *                      one of the return values. if size <= 0, bestStart = -1.
 * @param   bestEnd     The ending index of the found subarray,
 *                      one of the return values. if size <= 0, bestEnd = -1.
 * @param   bestSum     The summation of the elements in the found subarray,
 *                      one of the return values. If size <= 0, bestSum == 0.
 */
void bruteForce_n2(int list[], int size, int& bestStart, int& bestEnd,
                   int& bestSum) {
    bestStart = bestEnd = -1;
    bestSum = INT_MIN;

    stringstream msg;

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

    bestStart = bestEnd = 0;
    bestSum = list[0];

    if (size == 1) {
        msg << "The given size = 1.";
        msg << " The max sub array is the specified array itself.";
        debug(__func__, msg.str());
        msg.clear();
        msg.str("");
        msg << "size=" << size;
        debug(__func__, msg.str());
        return;
    }

    // print the input array
    printArray(size, list, "Array input:");

    int sum;
    // Starting from index 0, search the possible maximum sub array to size - 1.
    for (int startIndex = 0; startIndex < size; ++startIndex) {         // T(n)
        sum = 0;                                                        // C1
        for (int endIndex = startIndex; endIndex < size; ++endIndex) {  // T(n)
            // get the current sum from [bestStart..Index]
            sum += list[endIndex];                                      // C2
            // if the current sum is larger than the current bestSum,
            // record this current maximum
            if (bestSum < sum) {                                        // C3
                bestSum = sum;                                          // C4
                bestEnd = endIndex;                                     // C5
                bestStart = startIndex;                                 // C6
            }
        }
    }
    msg << "bestSum=" << bestSum;
    msg << " bestStart=" << bestStart;
    msg << " bestEnd=" << bestEnd;
    debug(__func__, msg.str());
    printArray(bestStart, bestEnd, list, "The max subarray:");
} // bruteForce_n2


/**
 * This function implements a brute force fashion in n^3 time complexity
 * to find a subarray whose element sum is the maximum
 * in the given array.
 *
 * @param   list        A array to search its max subarray.
 * @param   size        The size of list.
 * @param   bestStart   The starting index of the found subarray,
 *                      one of the return values.
 * @param   bestEnd     The ending index of the found subarray,
 *                      one of the return values.
 * @param   bestSum     The summation of the elements in the found subarray,
 *                      one of the return values.
 */
void bruteForce_n3(int list[], int size, int& bestStart, int& bestEnd,
                   int& bestSum) {
    bestStart = bestEnd = -1;
    bestSum = INT_MIN;

    stringstream msg;

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

    bestStart = bestEnd = 0;
    bestSum = list[0];

    if (size == 1) {
        msg << "The given size = 1.";
        msg << " The max sub array is the specified array itself.";
        debug(__func__, msg.str());
        msg.clear();
        msg.str("");
        msg << "size=" << size;
        debug(__func__, msg.str());
        return;
    }

    // print the input array
    printArray(size, list, "Array input:");

    int local_max_sum;
    for (int start = 0; start < size; ++start) {                    // T(n)
        for (int end = start; end < size; ++end) {                  // T(n)
            // get the local sum
            local_max_sum = 0;                                      // C1
            for (int index = start; index <= end; ++index) {        // T(n)
                local_max_sum += list[index];                       // C2
            }
            if (local_max_sum > bestSum) {                          // C3
                bestStart = start;                                  // C4
                bestEnd = end;                                      // C5
                bestSum = local_max_sum;                            // C6
            }
        }
    }

    msg << "bestSum=" << bestSum;
    msg << " bestStart=" << bestStart;
    msg << " bestEnd=" << bestEnd;
    debug(__func__, msg.str());
    printArray(bestStart, bestEnd, list, "The max subarray:");
} // bruteForce_n3
