// ------------------------------------------------------------------------------------
//       Filename: main.cpp
//       Revision: $Id$
//    Description: This file contains the main program execution entrance.
//        Created: 02/15/2016 01:15:59 PM
//       Compiler: G++
//         Author: Jason Meng (jm), jm652564@sju.edu
//
// Copyright (c) 2016 by Jason Meng, no rights reserved.
// ------------------------------------------------------------------------------------


// C includes
#include <stdlib.h>
// C++ includes
#include <iostream>
// custom includess
#include "headers/maxSumSubarray.h"
#include "headers/logging.h"


/**
 * A unit test for bruteForce_n2
 */
int max_sub_random_runner(void (* func)(int[], int, int&, int&, int&)) {
    int bestStart = -1,
        bestEnd = -1,
        bestSum = 0;

    testFlag = 0;

    arraySizesToTest = 10;
    int array[],
        sizes[] = new int[arraySizesToTest];

    const string testName = "Random Max Test";
    stringstream msg;

    msg << "----------- Test Name: " << testName << " -----------";
    info(__func__, msg.str());
    msg.clear();
    msg.str("");

    // set the sizes for the arrays to feed to the maxsub functions
    for (int i = 0; i < arraySizesToTest; ++i) {
        size[i] = i + 1;
    }

    for (int i = 0; i < arraySizesToTest; ++i) {
        // initialize the array
        array = new int[sizes[i]];
        fillArray(time(NULL), sizes[i], array);
        msg << "Array size=" << sizes[i] << " initialized: ";
        printArray(size, array, msg.str());
        msg.clear();
        msg.str("");
        try {
            msg << "Run searching..." << endl;
            bruteForce_n2(array, size, bestStart, bestEnd, bestSum);
            msg << "Actual: bestStart=" << bestStart;
            msg << " bestEnd=" << bestEnd;
            msg << " bestSum=" << bestSum << endl;
            info(msg.str());
            msg.clear();
            msg.str("");
            printArray(bestStart, bestEnd, array, "Max sub:");
        } catch (exception& e) {
            msg.clear();
            msg.str("");
            msg << "Unexpected exception: " << e.what();
            info(__func__, msg.str());
        }
        msg.clear();
        msg.str("");
        // destroy the array space
        delete[] array;
        // clean up variables
        bestStart = bestEnd = -1;
        bestSum = 0;
    }
} // bruteForce_n2_Test


int main(int argc, char *argv[]) {

    return 0;
}
