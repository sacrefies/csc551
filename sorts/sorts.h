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


/**
 * Do selection  sort to the given list(array).
 *
 * @param size The size of the given list(array).
 * @param list An array to be sorted.
 *
 * @return 0/-1, returns 0 if this function ends without error;
 *         returns -1 if some exception happened.
 */
int64_t selectionSort(int64_t size, int64_t list[]);

/**
 * Do insertion sort to the given list(array).
 *
 * @param size The size of the given list(array).
 * @param list An array to be sorted.
 *
 * @return 0/-1, returns 0 if this function ends without error;
 *         returns -1 if some exception happened.
 */
int64_t insertionSort(int64_t size, int64_t list[]);

