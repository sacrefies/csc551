// ------------------------------------------------------------------------------------
//          $Date$
//            $Id$
//       Filename:  insertionSort.cpp
//    Description:  The header file for the sort algorithms.
//                  Currently inlcuded: insertion sort, selection sort
//        Version:  1.0
//        Created:  01/28/2016 01:00:30 PM
//       Compiler:  g++
//         Author:  Jason Meng (jm), jm652564@sju.edu
// ------------------------------------------------------------------------------------


#include <iostream>
// use the modern C11 standard
#include <stdint.h>
#include "headers/sorts.h"


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
int64_t insertionSort(int64_t size, int64_t list[]) {
    // boundary checks
    if (size < 0) {
        printf("The given array size < 0.\n");
        return -1;
    };
    if (size < 2) {
        cout << "The given size is either 0 or 1. Do nothing.";
        return 0;
    };

    // init tmp
    int64_t sorted, key;
    sorted = key = 0;
    for (int64_t i = 1; i < size; i++) {
        // get the key
        key = list[i];
        // find a space for the key in the sorted sublist.
        for (sorted = i-1; sorted > 0; sorted--) {
            if (list[sorted] > key) {
                list[sorted+1] = list[sorted];
            };
        };
        // insert the key here
        list[sorted+1] = key;
    };
    return 0;
};

