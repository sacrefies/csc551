// ------------------------------------------------------------------------------------
//            $Id$
//          $Date$
//       Filename:  timing.cpp
//
//    Description:  this file contains the timeing function to profile a function's
//                  performance.
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
 * Calculate the elapsed time of sort_function for the given runs.
 * @param runs Iteration times that a sort function runs.
 * @param
 */
int64_t timing(const int64_t runs, int64_t (*func)(int64_t, int64_t[]), int64_t size, list[]) {
    if (runs < 1) {
        cout << "The function iteration is less than 1. Do nothing" << endl;
        return 0;
    };

    cout << "Running " << __func__ << " for " << runs << " times with size=" << size << endl;

    // cpu time start
    clock_t start, end;
    struct timeval startTv, endTv;
    double cpuTime, avgCpuTime, funcElapseTime;

    cpuTime = avgCpuTime = funcElapseTime = .0;

     cout << "Sort: " << __func__ << ", Size: " << size << endl;
    // print out the original input
    cout << "Input: ";
    for (int64_i i = 0; i < size; i++) {
        cout << i << ",";
    };
    cout << endl;

    // function elapse time clocking
    cout << "Runs: " << runs << endl;
    gettimeofday(&startTv, NULL);
    // cpu start clocking
    start = clock();
    for (int64_t i = 0; i < runs; i++) {
        if ((*func)(size, list) < 0) {
            cerr << "ERROR happened at run " << i <<  endl;
        } else if (i == 0) {
            cout << "Sorted: ";
            for (int64_t j = 0; j < size; j++) {
                cout << list[j] << ",";
            };
            cout << endl;
        };
    };
    cout << "fin." << endl;
    // cpu time end
    end = clock();

    // function elapse time end
    gettimeofday(&endTv, NULL);
    // cpu elapse time
    cpuTime = ((double)end - start) / CLOCKS_PER_SEC;
    avgCpuTime = cpuTime / runs;
    // total elapse time
    funcElapseTime = (double)endTv.tv_sec - startTv.tv_sec + ((double)endTv.tv_usec - startTv.tv_usec) / 1e6;

    // outputs
    cout << "Iteration: " << runs << ", ";
    cout << "total elapse time: " << funcElapseTime << ", ";
    cout << "CPU time: total= " << cpuTime << ", average=" << avgCpuTime;
    cout << endl;

    return 0;
};

