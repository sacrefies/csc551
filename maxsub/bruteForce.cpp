// ------------------------------------------------------------------------------------
//       Filename: bruteForce.cpp
//       Revision: $Id$
//    Description: This file includes the implementations to looking for
//                 the maximum sub array in a given array.
//        Created: 02/15/2016 01:20:29 PM
//       Compiler: G++
//         Author: Jason Meng (jm), jm652564@sju.edu
//
// Copyright (c) 2016 by Jason Meng
// ------------------------------------------------------------------------------------

// C++ includes
#include <iostream>
#include <string>
// custom includes
#include "headers/arrayUtils.h"


using std::cout;
using std::endl;


// -------------------------------------------------------------------------------------
// Comparison on pointer parameter and reference parameter.
//  The below 2 function demonstrate the difference.
//  General speaking, when dealing with the values, they are the same.
//     changeValueByPointer(int *v) == changeValueByRef(int& v)
// -------------------------------------------------------------------------------------
static void changeValueByPointer(int *v) {
    cout << __func__ << " -- ";
    // if you want to change the value and
    // such change goes visible to the caller:
    cout << "*v = 10;" << endl;
    *v = 10;
}

static void changeValueByPointer1(const int *v) {
    cout << __func__ << " -- ";
    // the lines below should cause error in compile time,
    // because of const
    //   error: assignment of read-only location '* v'
    //     *v = 10;
    //        ^
    // *v = 10;
    cout << "int newValue = 20; v = &newValue;" << endl;
    int newValue = 20;
    v = &newValue;
}

static void changeValueByRef(int& v) {
    cout << __func__ << " -- ";
    // if you want to change the value and
    // such change goes visible to the caller:
    cout << "v = 10;" << endl;
    v = 10;
}

static void changeValueByRef1(const int& v) {
    cout << __func__ << " -- ";
    // the lines below should cause error in compile time,
    // because of const
    //   error: assignment of read-only reference 'v'
    //     v = 10;
    //       ^
    // v = 10;
    cout << "Compile error. Nothing done." << endl;
}
// -------------------------------------------------------------------------------------

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
void bruteForce_n2(int list[], int size, int& bestStart, int& bestEnd, int& bestSum) {
    int lastSum = 0,
        sum = 0;

    if (size <= 0) {
        cout << __func__;
        cout << "The given size <= 0."
               " Both start index and end index of"
               " the subarray are set as -1." << endl;
        bestStart = -1;
        bestEnd = -1;
        bestSum = 0;
        return;
    }

    bestStart = 0;
    bestEnd = 0;
    bestSum = list[0];

    if (size == 1) {
        cout << "The given size is less than 2."
                " The max sub array is the given array itself. " << endl;
        return;
    }

    // Starting from index 0, search the possible maximum sub array to size - 1.
    for (int startIndex = 0; startIndex < size; ++ startIndex) {            // T(n)
        for (int endIndex = startIndex; endIndex < size; ++ endIndex) {     // T(n)
            // get the current sum from [bestStart..Index]
            sum += list[endIndex];                                          // O(1)
            // if the current sum is larger than the current bestSum,
            // record this current maximum
            if (bestSum < sum) {                                            // O(1)
                bestSum = sum;                                              // O(1)
                bestEnd = endIndex;                                         // O(1)
                bestStart = startIndex;                                     // O(1)
            }
        }
    }
}


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
void bruteForce_n3(int list[], int size, int& bestStart, int& bestEnd, int& bestSum) {

}
