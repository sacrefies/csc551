// ------------------------------------------------------------------------------------
// Copyright (c) 2016, Jason Meng
//       Filename:  selectionSorts.h
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

#include <iostream>
// use the modern C11 standard
#include <stdint.h>

using namespace std;


/**
 * Do insertion sort to the given list(array).
 *
 * @param size The size of the given list(array).
 * @param list An array to be sorted.
 *
 * @return 0/-1, returns 0 if this function ends without error;
 *         returns -1 if some exception happened.
 *
 */
int64_t selectionSort(const int64_t size, int64_t list[]) {
    // boundry checks
    if (size < 0) {
        printf("The given array size < 0.\n");
        throw -1;
    };
    if (size == 0) return 0;

    // init tmp
    int64_t tmp = list[0];
    // start with the first item in the array.
    // set the first item as the first marker list[0].
    for (int64_t i=0; i<size; i++) {
        // set the marker as list[i]
        for (int64_t j=i+1;j<size; j++) {
            // looking for the local minimum value
            // swap the min value with the marker list[i].
            if (list[i] > list[j]) {
                tmp = list[i];
                list[i] = list[j];
                list[j] = tmp;
            };
        };
    };
};
