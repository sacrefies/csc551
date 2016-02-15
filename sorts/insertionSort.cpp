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

// c headers
// c++ headers
#include <iostream>
// custom headers
#include "headers/sorts.h"


using namespace std;


/**
 * Do insertion sort to the given list(array).
 *
 * @param size The size of the given list(array).
 * @param list An array to be sorted.
 */
void insertionSort(int list[], int size) {
    // boundary checks
    if (size < 0)
        cout << "The given array size < 0." << endl;
    if (size < 2)
        cout << "The given size is either 0 or 1. Do nothing." << endl;

    // init tmp
    int sortedIndex = 0, key = 0;
    for (int i = 1; i < size; i++) {
        // get the key
        key = list[i];
        // find a space for the key in the sorted sublist.
        for (sortedIndex = i - 1; sortedIndex >= 0; --sortedIndex) {
            if (list[sortedIndex] > key)
                list[sortedIndex+1] = list[sortedIndex];
            else
                break;
        }
        // insert the key here
        list[sortedIndex+1] = key;
    }
}
