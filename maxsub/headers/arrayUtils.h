// ------------------------------------------------------------------------------------
//       Filename: arrayUtils.h
//       Revision: $Id$
//    Description: This file includes definitions of a few helper
//                 or utility function for array handling.
//        Created: 02/15/2016 01:20:29 PM
//       Compiler: G++
//         Author: Jason Meng (jm), jm652564@sju.edu
//
// Copyright (c) 2016 by Jason Meng
// ------------------------------------------------------------------------------------

#include <string>


/** include guard:  */
#ifndef ARRAYUTILS_H
#define ARRAYUTILS_H

using std::string;


/**
 * Fill up a given array by using random int64 numbers
 *
 * @param size The size of the array
 * @param list The array to be filled
 */
void fillArray(const int seed, const int size, int list[]);


/**
 * Print the given array to the stdout
 *
 * @param size The size of the array
 * @param list The array of type int64
 */
void printArray(const int size, int list[], const string msg);


/**
 * Print the given array to the stdout
 *
 * @param size The size of the array
 * @param list The array of type int64
 */
void printArray(const int startIndex, const int endIndex, int list[],
                const string msg);


/**
 * Calculate the summation of a specified int subarray.
 *
 * @param startIndex    The index where the subarray starts.
 * @param endIndex      The index where the subarray ends.
 * @param list          An array of int which contains the subarray.
 * @return  The summation result of the specified subarray.
 */
int elementSum(const int startIndex, const int endIndex, int list[]);

#endif /** end of include guard:  */
