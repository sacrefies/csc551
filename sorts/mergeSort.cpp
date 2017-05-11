// ------------------------------------------------------------------------------------
//            $Id$
//          $Date$
//       Filename:  mergeSort.cpp
//
//    Description:  This cpp file contains the implementation of merge sort algorithm
//
//        Version:  1.0
//        Created:  02/05/2016 03:20:57 PM
//       Compiler:  g++
//         Author:  Jason Meng (jm), jm652564@sju.edu
//
// Copyright (c) 2016, Jason Meng
// ------------------------------------------------------------------------------------


// c includes
// c++ includes
#include <iostream>
// custom headers
#include "headers/sorts.h"


using namespace std;

/**
 * This method uses a temp array which is passed from the caller
 * to store the merged result and copies the items in the temp
 * array back to the original array.
 *
 * @param   lStart  The starting index of the left sub-array
 * @param   lEnd    The ending index of the left sub-array
 * @param   rStart  The starting index of the right sub-array
 * @param   rEnd    The ending index of the right sub-array
 * @param   list    The array which conatins the left and right sub arrays to be merged
 *
 * @return  Returns 0 if no error happens; return -1 if
 */
static int merge(const int lStart, const int lEnd,
                 const int rStart, const int rEnd,
                 int list[], int cache[]) {
    int leftHead = lStart;
    int rightHead = rStart;
    int mergedIndex = 0;

    while (leftHead <= lEnd && rightHead <= rEnd) {
        if (list[leftHead] < list[rightHead])
            cache[mergedIndex++] = list[leftHead++];
        else
            cache[mergedIndex++] = list[rightHead++];
    }

    // Check whether left has remaining or right has remaining
    // and then put the remaining into the merged
    if (leftHead <= lEnd)
        // left has remaining
        for (int i = leftHead; i <= lEnd; ++i)
            cache[mergedIndex++] = list[i];
    else if (rightHead <= rEnd)
        // right has remaining
        for (int i = rightHead; i <= rEnd; ++i)
            cache[mergedIndex++] = list[i];

    // copy the items from merged to list, from lStart to rEnd
    for (int i = lStart; i <= rEnd; ++i) {
        list[i] = cache[i - lStart];
    }
    return 0;
}

/**
 * The inner recursive sort which serves the merge sort.
 *
 * @param   startIndex  The starting index of an array or sub array
 *                      which needs to be sorted.
 * @param   endIndex    The ending index of an array or sub array
 *                      which needs to be sorted.
 * @param   list        The array to be sorted.
 * @param   swap        A temp array for saving the merging result
 *
 * @return Returns 0 if no error happens; returns -1 if otherwise.
 */
static int innerSort(const int startIndex, const int endIndex,
                     int list[], int cache[]) {
    // return condition
    // -- only one item in the array, it is sorted.
    if (endIndex == startIndex) return 0;
    // get the median in left-leaning fashion
    int median = (((endIndex + startIndex) & 1) == 1) ?
                 (endIndex + startIndex) >> 1 : ((endIndex + startIndex) - 1) >> 1;
    if (median < 0) return -1;
    // sort left
    if (innerSort(startIndex, median, list, cache) != 0) return -1;
    // sort right
    if (innerSort(median + 1, endIndex, list, cache) != 0) return -1;
    // merge
    if (merge(startIndex, median, median + 1, endIndex, list, cache) != 0) return -1;
    return 0;
}

/**
 * Merge sort algorithm implementation.
 *
 * @param   size    The size of the array to be sorted.
 * @param   list    The array to be sorted.
 *
 * @return Returns 0 if no error happens; returns -1 if otherwise.
 */
void mergeSort(int list[], int size) {
    // some boundary checks
    if (size < 2) {
        cout << __func__ << " -- size == " << size << ", no sorting" << endl;
        return;
    }

    int *swap;
    if (size <= 100000) swap = new int[100000];
    else swap = new int[size];

    if (innerSort(0, size - 1, list, swap) != 0)
        cout << __func__ << " -- Unexpected error happened." << endl;
    delete[] swap;
}
