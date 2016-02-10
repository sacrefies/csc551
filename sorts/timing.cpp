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


#include <iostream>
#include <sys/time.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include "headers/timing.h"

using namespace std;


/**
 * Fill up a given array by using random int64 numbers
 *
 * @param size The size of the array
 * @param list The array to be filled
 */
void fillArray(const int64_t seed, const int64_t size, int64_t list[]) {
    if (size < 1) {
        return;
    }

    // srand(time(NULL));
    for (int64_t i = 0; i < size; i++) {
        list[i] = rand() % size;
    };
};

/**
 * Print the given array to the stdout
 *
 * @param size The size of the array
 * @param list The array of type int64
 */
void printArray(const int64_t size, int64_t list[]) {
    cout << "[";
    for (int64_t i = 0; i < size; i++) {
        cout << list[i] << ",";
    };
    cout << "]" << endl;
};

/**
 * Calculate the elapsed time of sort_function for the given runs.
 * @param runs Iteration times that a sort function runs.
 * @param size 
 */
int64_t timing(const int64_t runs, const int64_t size, int64_t (*func)(const int64_t, int64_t[])) {
    if (runs < 1) {
        cout << "The function iteration is less than 1. Do nothing" << endl;
        return 0;
    };

    if (size < 2) {
        cout << "The given size is less than 2. Do nothing" << endl;
        return 0;
    };

    // cpu time start
    clock_t start, end;
    struct timeval startTv, endTv;
    double cpuTime, avgCpuTime, funcElapseTime;
    int64_t *list = new int64_t[size];

    cpuTime = avgCpuTime = funcElapseTime = .0;

    cout << "start..." << endl;
    // function elapse time clocking
    gettimeofday(&startTv, NULL);
    // cpu start clocking
    start = clock();
    // iterate sort runs
    for (int64_t i = 0; i < runs; i++) {
        // create a new array in size of the given size.
        fillArray(time(NULL), size, list);
        // print out the original
        // printArray(size, list);
        // do sorting
        (*func)(size, list);
        // print out the sorted
        // printArray(size, list);
    };

    // cpu time end
    end = clock();
    // function elapse time end
    gettimeofday(&endTv, NULL);
    // cpu elapse time
    cpuTime = ((double)end - start) / CLOCKS_PER_SEC;
    avgCpuTime = cpuTime / runs;
    // total elapse time
    funcElapseTime = (double)endTv.tv_sec - startTv.tv_sec + ((double)endTv.tv_usec - startTv.tv_usec) / 1e6;

    cout << "fin." << endl;
    // free the array
    delete[] list;
    // outputs
    cout << "Iteration: " << runs << ", ";
    cout << "total elapse time: " << funcElapseTime << ", ";
    cout << "CPU time: total= " << cpuTime << ", average=" << avgCpuTime;
    cout << endl;

    return 0;
};
