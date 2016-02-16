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
#include <exception>
// custom includes
#include "headers/arrayUtils.h"
#include "header/bruteForce.h"
#include "headers/recursive.h"
#include "headers/kadane.h"


using std::cout;
using std::endl;
using std::exception;


/**
 * A unit test for bruteForce_n2
 */
void bruteForce_n2_Test() {
    int bestStart = -1,
        bestEnd = -1,
        bestSum = 0;
        arraySizesToTest = 10;
    int array[],
        sizes[] = new int[arraySizesToTest];

    cout << endl;
    cout << "----------- Test Name: " << __func__ << " -----------" << endl;

    // set the sizes for the arrays to feed to the maxsub functions
    for (int i = 0; i < arraySizesToTest; ++i)
        size[i] = i + 1;

    for (int i = 0; i < arraySizesToTest; ++i) {
        cout << "--------------------------------" << endl;
        cout << __func__ " -- Testing array size=" << sizes[i] << endl;
        // initialize the array
        array = new int[sizes[i]];
        fillArray(time(NULL), sizes[i], array);
        cout << __func__ << " -- Array initialized." << endl;
        printArray(size, array, "Original:");
        try {
            cout << __func__ << " -- Run searching..." << endl;
            bruteForce_n2(array, size, bestStart, bestEnd, bestSum);
            printArray(bestStart, bestEnd, array, "Max sub:");
        } catch (exception& e) {
            cout << __func__ << " -- Exception: ";
            cout << e.what() << endl;
        }
        // destroy the array space
        delete[] array;
        // clean up variables
        bestStart = bestEnd = -1;
        bestSum = 0;
    }
}


/**
 * A unit test for bruteForce_n3
 */
void bruteForce_n2_Test() {
    int bestStart = -1,
        bestEnd = -1,
        bestSum = 0;
        arraySizesToTest = 10;
    int array[],
        sizes[] = new int[arraySizesToTest];

    cout << endl;
    cout << "----------- Test Name: " << __func__ << " -----------" << endl;

    // set the sizes for the arrays to feed to the maxsub functions
    for (int i = 0; i < arraySizesToTest; ++i)
        size[i] = i + 1;

    for (int i = 0; i < arraySizesToTest; ++i) {
        cout << "--------------------------------" << endl;
        cout << __func__ " -- Testing array size=" << sizes[i] << endl;
        // initialize the array
        array = new int[sizes[i]];
        fillArray(time(NULL), sizes[i], array);
        cout << __func__ << " -- Array initialized." << endl;
        printArray(size, array, "Original:");
        try {
            cout << __func__ << " -- Run searching..." << endl;
            bruteForce_n3(array, size, bestStart, bestEnd, bestSum);
            printArray(bestStart, bestEnd, array, "Max sub:");
        } catch (exception& e) {
            cout << __func__ << " -- Exception: ";
            cout << e.what() << endl;
        }
        // destroy the array space
        delete[] array;
        // clean up variables
        bestStart = bestEnd = -1;
        bestSum = 0;
    }
}
