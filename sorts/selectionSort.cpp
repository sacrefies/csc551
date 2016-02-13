// ------------------------------------------------------------------------------------
//          $Date$
//            $Id$
//       Filename:  selectionSort.cpp
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
 * Do selection sort to the given list(array).
 *
 * @param size The size of the given list(array).
 * @param list An array to be sorted.
 */
void selectionSort(int list[], int size) {
    // boundary checks
    if (size < 0)
        cout << "The given array size < 0." << endl;
    if (size < 2)
        cout << "The given size is either 0 or 1. Do nothing." << endl;

    // init tmp
    int tmp = 0;
    // start with the first item in the array.
    // set the first item as the first marker list[0].
    for (int i = 0; i < size; ++i) {
        // set the marker as list[i]
        for (int j = i + 1; j < size; ++j) {
            // looking for the local minimum value
            // swap the min value with the marker list[i].
            if (list[i] > list[j]) {
                tmp = list[i];
                list[i] = list[j];
                list[j] = tmp;
            }
        }
    }
}
