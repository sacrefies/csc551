// ------------------------------------------------------------------------------------
//       Filename: arrayUtils.cpp
//       Revision: $Id$
//    Description: This file includes a few helper or utility function for array handling.
//        Created: 02/15/2016 01:20:29 PM
//       Compiler: G++
//         Author: Jason Meng (jm), jm652564@sju.edu
//
// Copyright (c) 2016 by Jason Meng
// ------------------------------------------------------------------------------------


// C includes
#include <sys/time.h>
// C++ includes
#include <iostream>
#include <string>


using std::cout;
using std::endl;


/**
 * Fill up a given array by using random int64 numbers
 *
 * @param size The size of the array
 * @param list The array to be filled
 */
void fillArray(const int seed, const int size, int list[]) {
    if (size < 1) {
        cout << __func__ << " -- size=" << size
        << ", quit." << endl;
        return;
    }
    // srand(time(NULL));
    for (int i = 0; i < size; i++)
        list[i] = rand() % size;
}


/**
 * Print the given array to the stdout
 *
 * @param size The size of the array
 * @param list The array of type int64
 */
void printArray(const int size, int list[], string msg) {
    cout << __func__ << " -- " << msg << " [";
    for (int i = 0; i < size; ++i) {
        cout << list[i] << ",";
    }
    cout << "]" << endl;
}

/**
 * Print the given array to the stdout
 *
 * @param size The size of the array
 * @param list The array of type int64
 */
void printArray(const int startIndex, const int endIndex, int list[], string msg) {
    if (startIndex < 0 || endIndex < 0) {
        cout << __func__ << " -- Error: One or both of
                            the indices are less than 0." << endl;
        cout << __func__ << " -- startIndex=" << startIndex
        << " endIndex=" << endIndex;
        return;
    }

    cout << __func__ << " -- " << msg << " [";
    for (int i = startIndex; i <= endIndex; ++i) {
        cout << list[i] << ",";
    }
    cout << "]" << endl;
}
