// ------------------------------------------------------------------------------------
//            $Id$
//          $Date$
//       Filename:  timing.h
//
//    Description:  this header file includes the timing function definition.
//
//        Version:  1.0
//        Created:  02/02/2016 02:51:13 PM
//       Compiler:  g++
//         Author:  Jason Meng (jm), jm652564@sju.edu
//
// Copyright (c) 2016, Jason Meng
// ------------------------------------------------------------------------------------

#include <string>

#ifndef TIMING_H
#define TIMING_H

using namespace std;

/**
 * Calculate the elapsed time of sort_function for the given runs.
 * @param runs Iteration times that a sort function runs.
 * @param
 */
int timing(const int runs, const int size, void (*func)(int[], int));

/**
 * Print the given array to the stdout
 *
 * @param size The size of the array
 * @param list The array of type int64
 */
void printArray(const int size, int list[], string msg);

/**
 * Fill up a given array by using random int64 numbers
 *
 * @param size The size of the array
 * @param list The array to be filled
 */
void fillArray(const int size, int list[]);

void debug(string tag, string msg);
#endif
