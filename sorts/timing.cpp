// ------------------------------------------------------------------------------------
//            $Id$
//          $Date$
//       Filename:  timing.cpp
//
//    Description:  this file contains the timeing function to profile a function's
//                  performance. Note: This function works only on top of a POSIX env.
//
//        Version:  1.0
//        Created:  02/02/2016 02:46:19 PM
//       Compiler:  g++
//         Author:  Jason Meng (jm), jm652564@sju.edu
//
// Copyright (c) 2016, Jason Meng
// ------------------------------------------------------------------------------------

// c includes
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>
// c++ includes
#include <iostream>
// custom includes
#include "headers/timing.h"

using namespace std;


/**
 * Fill up a given array by using random int64 numbers
 *
 * @param size The size of the array
 * @param list The array to be filled
 */
void fillArray(const int seed, const int size, int list[]) {
    if (size < 1)
        return;

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
    for (int i = 0; i < size; i++)
        cout << list[i] << ",";
    cout << "]" << endl;
}


/**
 * Calculate the elapsed time of sort_function for the given runs.
 * @param runs Iteration times that a sort function runs.
 * @param size
 */
int timing(const int runs, const int size, void (* func)(int[], int)) {
    if (runs < 1) {
        cout << "The function iteration is less than 1. Do nothing" << endl;
        return 0;
    }
    ;

    if (size < 2) {
        cout << "The given size is less than 2. Do nothing" << endl;
        return 0;
    }
    ;

    // cpu time start
    clock_t start, end;
    struct timeval startTv, endTv;
    double cpuTime, avgCpuTime, funcElapseTime;
    int * list = new int[size];

    cpuTime = avgCpuTime = funcElapseTime = .0;
    // function elapse time clocking
    gettimeofday(&startTv, NULL);
    // cpu start clocking
    start = clock();
    // iterate sort runs
    for (int i = 0; i < runs; i++) {
        // create a new array in size of the given size.
        fillArray(time(NULL), size, list);
        // print out the original
        // printArray(size, list, "The shuffled: ");
        // do sorting
        (*func)(list, size);
    }

    // cpu time end
    end = clock();
    // function elapse time end
    gettimeofday(&endTv, NULL);
    // cpu elapse time
    cpuTime = ((double)end - start) / CLOCKS_PER_SEC;
    avgCpuTime = cpuTime / runs;
    // total elapse time
    funcElapseTime = (double)endTv.tv_sec - startTv.tv_sec +
                     ((double)endTv.tv_usec - startTv.tv_usec) / 1e6;

    // print out the sorted
    printArray(size, list, "The sorted: ");
    // free the array
    delete[] list;
    // outputs
    cout << "Runs: " << runs << ", ";
    cout << "Elapse Time: " << funcElapseTime << endl;
    cout << "CPU Time: total=" << cpuTime << ", avg=" << avgCpuTime;
    cout << endl;

    return 0;
}
