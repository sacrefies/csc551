// -----------------------------------------------------------------------------
// Filename:    main.cpp
// Revision:    $Id$
// Description: This file includes the program execution entrance
// Created:     04/04/2016 01:20:29 PM
// Compiler:    G++
// Author:      Jason Meng (jm), jm652564@sju.edu
//
// Copyright (c) 2016 by Jason Meng, no rights reserved.
// -----------------------------------------------------------------------------


#include <ctime>
#include <cstdlib>

#include <iostream>
#include <sstream>
#include <random>
#include <exception>

#include "headers/logging.h"
#include "headers/utils.h"
#include "headers/tsp.h"


using std::exception;
using std::stringstream;
using std::endl;


#ifndef GRAD
#define  GRAD
#endif

#ifndef EXTRA_CREDIT_RECURSIVE
#define  EXTRA_CREDIT_RECURSIVE
#endif

#ifndef EXTRA_CREDIT_NON_RECURSIVE
#define  EXTRA_CREDIT_NON_RECURSIVE
#endif


// const int n = 5;
// double tour[n][2] = {
//     { 0.631980, 0.7925150 },
//     { 0.489609, 0.2541210 },
//     { 0.975682, 0.0843492 },
//     { 0.414236, 0.6135660 },
//     { 0.338385, 0.0315477 }
// };


// ---------------------------------------------------------------------------
int main(int argc, char * argv[]) {
    // set log level
    setLoggingLevel(WARNING);

    info("", "################# RUN STARTS #####################");

    // generate a random int [0, 20)
    srand(time(NULL));
    const int n = rand() % 10;

    double(*tour_copied)[2] = new double[n][2];
    double(*tour)[2] = new double[n][2];

    stringstream msg;
    msg << "Random tour legs, n = " << n << ". ";
    fill_random_tour(tour, n);
    msg << "The tour has been initialized:";
    info("", msg.str());
    msg.clear();
    msg.str("");
    print(tour, n);

    // run 1
    try {
        copy(tour_copied, n, tour);
        info("", "****************** bruteForce1: repeats");
        info("", "Repeat from -2 to 500");
        for (long i = -2; i < 500; ++i) {
            info("", "---------------------------------------------------");
            msg << "********* Repeat = " << i;
            info(__func__, msg.str());
            msg.clear();
            msg.str("");
            bruteForce1(tour_copied, n, i);
            info("", "Result tour:");
            print(tour_copied, n);
        }
    } catch (exception& e) {
        error(__func__, e.what());
    }

    #ifdef GRAD
    // run 2
    try {
        info("", "****************** bruteForce2: hard-coded permutations of 5");
        // must protect the function because it's hard-coded with size = 5.
        if (5 > n) {
            error("", "The random legs of the tour generated is less than 5!");
            error("", "bruteForce2 cannot run.");
        } else {
            copy(tour_copied, 5, tour);
            long perms = bruteForce2(tour_copied);
            msg << "Result permutations: " << perms;
            msg.clear();
            msg.str("");
            info("", msg.str());
            info("", "Result tour:");
            print(tour_copied, 5);
        }
    } catch (exception& e) {
        error(__func__, e.what());
    }
    #endif

    #ifdef EXTRA_CREDIT_RECURSIVE
    try {
        // double temp[5][2];
        copy(tour_copied, n, tour);
        info("", "****************** bruteForce3: recursive permutations of N");
        bruteForce3(tour_copied, n);
        info("", "Result tour:");
        print(tour_copied, n);
    } catch (exception& e) {
        error(__func__, e.what());
    }
    #endif

    #ifdef EXTRA_CREDIT_NON_RECURSIVE
    try {
        // double temp[5][2];
        copy(tour_copied, n, tour);
        info("", "****************** bruteForce4: non-recursive permutations of N");
        bruteForce4(tour_copied, n);
        info("", "Result tour:");
        print(tour_copied, n);
    } catch (exception& e) {
        error(__func__, e.what());
    }
    #endif

    delete[] tour_copied;
    delete[] tour;
    tour_copied = NULL;
    tour = NULL;
    info("", "################# RUN ENDS #####################");
} // main
