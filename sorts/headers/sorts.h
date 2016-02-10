// ------------------------------------------------------------------------------------
// Copyright (c) 2016, Jason Meng
//       Filename:  sorts.h
//
//    Description: The header file for the sort algorithms.
//                 Currently inlcuded: insertion sort, selection sort
//        Version:  1.0
//        Created:  01/28/2016 01:00:30 PM
//       Revision:  $Id$
//       Compiler:  g++
//
//         Author:  Jason Meng (jm), jm652564@sju.edu
//
// ------------------------------------------------------------------------------------

#pragma once
#include <stdint.h>


using namespace std;

/**
 * Do selection sort to the given list(array).
 *
 * @param size The size of the given list(array).
 * @param list An array to be sorted.
 *
 * @return 0/-1, returns 0 if this function ends without error;
 *         returns -1 if some exception happened.
 */
int64_t selectionSort(const int64_t size, int64_t list[]);

/**
 * Do insertion sort to the given list(array).
 *
 * @param size The size of the given list(array).
 * @param list An array to be sorted.
 *
 * @return 0/-1, returns 0 if this function ends without error;
 *         returns -1 if some exception happened.
 */
int64_t insertionSort(const int64_t size, int64_t list[]);

/**
 * Merge sort algorithm implementation.
 *
 * @param   size    The size of the array to be sorted.
 * @param   list    The array to be sorted.
 *
 * @return Returns 0 if no error happens; returns -1 if otherwise.
 */
int64_t mergeSort(const int64_t size, int64_t list[]);

