// -----------------------------------------------------------------------------
//       Filename: arrayUtils.cpp
//       Revision: $Id$
//    Description: This file includes a few helper or utility function for array
//                 handling.
//        Created: 02/15/2016 01:20:29 PM
//       Compiler: G++
//         Author: Jason Meng (jm), jm652564@sju.edu
//
// Copyright (c) 2016 by Jason Meng
// -----------------------------------------------------------------------------


// C++ includes
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <limits>
#include "headers/logging.h"


using std::cout;
using std::endl;
using std::stringstream;


/**
 * Fill up a given array by using random int64 numbers
 *
 * @param size The size of the array
 * @param list The array to be filled
 */
void fillArray(const int seed, const int size, int list[]) {
    if (size < 1) {
        stringstream msg;
        msg << "size=" << size;
        error(__func__, msg.str());
        return;
    }
    srand(seed);
    for (int i = 0; i < size; i++) {
        list[i] = rand() % size;
    }
}


/**
 * Print the given array to the stdout
 *
 * @param size The size of the array
 * @param list The array of type int64
 */
void printArray(const int size, int list[], string msg) {
    if (list == NULL) {
        error(__func__,  "The given array is NULL");
        return;
    }
    stringstream message;
    message << msg << "[";
    for (int i = 0; i < size; ++i) {
        message << list[i] << ",";
    }
    message << "]";
    info(__func__, message.str());
    debug(__func__, message.str());
}

/**
 * Print the given array to the stdout
 *
 * @param size The size of the array
 * @param list The array of type int64
 */
void printArray(const int startIndex, const int endIndex, int list[],
                string msg) {
    stringstream message;

    if (startIndex < 0 || endIndex < 0) {
        error(__func__, "One or both of the indices are less than 0.");
        message << "startIndex=" << startIndex;
        message << ", endIndex=" << endIndex;
        error(__func__, message.str());
        return;
    }
    message << msg << "[";
    for (int i = startIndex; i <= endIndex; ++i) {
        cout << list[i] << ",";
    }
    message << "]";
    info(__func__, message.str());
    debug(__func__, message.str());
}


/**
 * Calculate the summation of a specified int subarray.
 *
 * @param startIndex    The index where the subarray starts.
 * @param endIndex      The index where the subarray ends.
 * @param list          An array of int which contains the subarray.
 * @return  The summation result of the specified subarray.
 */
int elementSum(const int startIndex, const int endIndex, int list[]) {
    stringstream message;
    int sum = 0;

    if (startIndex < 0 || endIndex < 0) {
        error(__func__, "One or both of the indices are less than 0.");
        message << "startIndex=" << startIndex;
        message << ", endIndex=" << endIndex;
        error(__func__, message.str());
        return INT_MIN;
    }

    for (int i = startIndex; i <= endIndex; ++i) {
        sum += list[i];
    }
    message << "startIndex=" << startIndex << " endIndex=" << endIndex;
    message << " sum=" << sum;
    debug(__func__, message.str());
    return sum;
}
