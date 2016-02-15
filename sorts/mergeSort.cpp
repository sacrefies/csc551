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
 * An alternative method for megerging 2 list.
 * This method creates a temp array to store the merged result
 * and copies the items in the temp array back to the original array.
 *
 * @param   lStart  The starting index of the left sub-array
 * @param   lEnd    The ending index of the left sub-array
 * @param   rStart  The starting index of the right sub-array
 * @param   rEnd    The ending index of the right sub-array
 * @param   list    The array which conatins the left and right sub arrays to be merged
 */
static int mergeInnerSwap(const int lStart, const int lEnd, const int rStart, const int rEnd, int list[]) {
    // a tmp array as the merged result
    int *merged = new int[rEnd - lStart + 1];
    int leftHead = lStart;
    int rightHead = rStart;
    int mergedIndex = 0;

    while (leftHead <= lEnd && rightHead <= rEnd) {
        if (list[leftHead] < list[rightHead])
            merged[mergedIndex++] = list[leftHead++];
        else
            merged[mergedIndex++] = list[rightHead++];
    }

    // Check whether left has remaining or right has remaining
    // and then put the remaining into the merged
    if (leftHead <= lEnd) {
        // left has remaining
        for (int i = leftHead; i <= lEnd; ++i)
            merged[mergedIndex++] = list[i];
    } else if (rightHead <= rEnd) {
        // right has remaining
        for (int i = rightHead; i <= rEnd; ++i)
            merged[mergedIndex++] = list[i];
    }

    // copy the items from merged to list, from lStart to rEnd
    for (int i = lStart; i <= rEnd; ++i)
        list[i] = merged[i-lStart];

    // free the temp array
    delete[] merged;

    return 0;
}


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
 * @return  Returns 0 if no error happens; return -1 if otherwise
 *
 */
static int merge(const int lStart, const int lEnd, const int rStart, const int rEnd, int list[], int cache[]) {

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
    if (leftHead <= lEnd) {
        // left has remaining
        for (int i = leftHead; i <= lEnd; ++i)
            cache[mergedIndex++] = list[i];
    } else if (rightHead <= rEnd) {
        // right has remaining
        for (int i = rightHead; i <= rEnd; ++i)
            cache[mergedIndex++] = list[i];
    }

    // copy the items from merged to list, from lStart to rEnd
    for (int i = lStart; i <= rEnd; ++i)
        list[i] = cache[i-lStart];

    return 0;
}


/**
 * Merge 2 sub-arrays which have been sorted already from right to left in an array.
 * This merge method move and swap array items within the given array. It does not
 * create temp array for item swapping/saving.
 *
 * @param   lStart  The starting index of the left sub-array
 * @param   lEnd    The ending index of the left sub-array
 * @param   rStart  The starting index of the right sub-array
 * @param   rEnd    The ending index of the right sub-array
 * @param   list    The array which conatins the left and right sub-arrays to be merged.
 *
 * @return Returns 0 if no error happens; returns -1 if otherwise.
 */
static int mergeInplace(const int lStart, const int lEnd, const int rStart, const int rEnd, int list[]) {
    int leftHead, rightHead, leftEnd, tmpRHItem;

    leftHead = lStart;
    rightHead = rStart;
    leftEnd = lEnd;
    tmpRHItem = 0;

    // left and right are sorted already.
    // just consider the overlapping part:
    //   if lh <= rh, just move lh to the next, no insertion
    //   if lh > rh, insert rh into the position where lh is
    //      move lh ... le to the right one by one (moving to the right
    //          means le -> le+1 == rh)
    //      move both lh and rh to their next postion
    while (leftHead <= leftEnd && leftEnd <= rEnd && rightHead <= rEnd) {
        if (list[leftHead] > list[rightHead]) {
            // save the current element value at rightHead
            tmpRHItem = list[rightHead];
            // move every elements of left subarray 1 position to right,
            // starting from leftHead
            for (int i = leftEnd; i >= leftHead; --i)
                list[i+1] = list[i];
            // insert old rightHead value to leftHead position
            list[leftHead] = tmpRHItem;
            // set the end of left subarray to the rightHead
            leftEnd = rightHead ++;
        }
        // increase leftHead
        leftHead ++;
    }

    return 0;
}


/**
 * Compute a median number between to numbers. This median is left leaning
 * which means this median is closer to the lowEnd.
 * E.g.:
 *  lowEnd = 0, highEnd = 5, median = 2
 *  lowEnd = 0, highEnd = 4, median = 1
 *
 * @param   lowEnd  The lower boundary of the number section
 * @param   highEnd The higher boundary of the number section
 *
 * @return  Returns the median number of the number section
 *          if no error happened; returns -1 if otherwise.
 */
static int getMedian(int lowEnd, int highEnd) {
    if (lowEnd > highEnd)
        return -1;
    if (lowEnd == highEnd)
        return 0;

    int sub = (highEnd + lowEnd);
    // ensure len(left) <= len(right)
    return ((sub & 1) == 1) ? sub >> 1: (sub - 1) >> 1;
}


/**
 * The inner recursive sort which serves the merge sort.
 *
 * @param   startIndex  The starting index of an array or sub array
 *                      which needs to be sorted.
 * @param   endIndex    The ending index of an array or sub array
 *                      which needs to be sorted.
 * @param   list        The array to be sorted.
 *
 * @return Returns 0 if no error happens; returns -1 if otherwise.
 */
static int innerSortInplace(const int startIndex, const int endIndex, int list[]) {
    // return condition
    // -- only one item in the array, it is sorted.
    if (endIndex == startIndex) {
        return 0;
    }

    // get the median in left-leaning fashion
    int median = getMedian(startIndex, endIndex);
    if (median < 0) {
        cout << __func__ << " -- Error happened: Wrong median." << endl;
        return -1;
    }

    // sort left
    if (innerSortInplace(startIndex, median, list) != 0) {
        cout << __func__ << " -- ";
        cout << "Error happened: Sorting left sub array failed." << endl;
        return -1;
    }

    // sort right
    if (innerSortInplace(median + 1, endIndex, list) != 0) {
        cout << __func__ << " -- ";
        cout << "Error happened: Sorting right sub array failed." << endl;
        return -1;
    }

    // merge
    if (mergeInplace(startIndex, median, median + 1, endIndex, list) != 0) {
    // if (alterMerge(startIndex, median + startIndex, median + startIndex + 1, endIndex, list) != 0) {
        cout << __func__ << " -- ";
        cout << "Error happened: Merging failed." << endl;
        return -1;
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
 *
 * @return Returns 0 if no error happens; returns -1 if otherwise.
 */
static int innerSortWithInnerSwap(const int startIndex, const int endIndex, int list[]) {
    // return condition
    // -- only one item in the array, it is sorted.
    if (endIndex == startIndex) {
        return 0;
    }

    // get the median in left-leaning fashion
    int median = getMedian(startIndex, endIndex);
    if (median < 0) {
        cout << __func__ << " -- Error happened: Wrong median." << endl;
        return -1;
    }

    // sort left
    if (innerSortWithInnerSwap(startIndex, median, list) != 0) {
        cout << __func__ << " -- ";
        cout << "Error happened: Sorting left sub array failed." << endl;
        return -1;
    }

    // sort right
    if (innerSortWithInnerSwap(median + 1, endIndex, list) != 0) {
        cout << __func__ << " -- ";
        cout << "Error happened: Sorting right sub array failed." << endl;
        return -1;
    }

    // merge
    if (mergeInnerSwap(startIndex, median, median + 1, endIndex, list) != 0) {
        cout << __func__ << " -- ";
        cout << "Error happened: Merging failed." << endl;
        return -1;
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
static int innerSort(const int startIndex, const int endIndex, int list[], int cache[]) {
    // return condition
    // -- only one item in the array, it is sorted.
    if (endIndex == startIndex) {
        return 0;
    }

    // get the median in left-leaning fashion
    int median = getMedian(startIndex, endIndex);
    if (median < 0) {
        cout << __func__ << " -- Error happened: Wrong median." << endl;
        return -1;
    }

    // sort left
    if (innerSort(startIndex, median, list, cache) != 0) {
        cout << __func__ << " -- ";
        cout << "Error happened: Sorting left sub array failed." << endl;
        return -1;
    }

    // sort right
    if (innerSort(median + 1, endIndex, list, cache) != 0) {
        cout << __func__ << " -- ";
        cout << "Error happened: Sorting right sub array failed." << endl;
        return -1;
    }

    // merge
    if (merge(startIndex, median, median + 1, endIndex, list, cache) != 0) {
        cout << __func__ << " -- ";
        cout << "Error happened: Merging failed." << endl;
        return -1;
    }

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
void mergeSortInplace(int list[], int size) {
    // some boundary checks
    if (size < 2) {
        cout << __func__ << " -- size == " << size << ", no sorting" << endl;
        return;
    }

    int med = getMedian(0, size - 1);
    if (med < 0) {
        cout << __func__ << " -- Error happened: Wrong median." << endl;
        return;
    }

    if (innerSortInplace(0, size - 1, list) != 0)
        cout << __func__ << " -- Unexpected error happened." << endl;
}


/**
 * Merge sort algorithm implementation.
 *
 * @param   size    The size of the array to be sorted.
 * @param   list    The array to be sorted.
 *
 * @return Returns 0 if no error happens; returns -1 if otherwise.
 */
void mergeSortInnerSwap(int list[], int size) {
    // some boundary checks
    if (size < 2) {
        cout << __func__ << " -- size == " << size << ", no sorting" << endl;
        return;
    }

    int med = getMedian(0, size - 1);
    if (med < 0) {
        cout << __func__ << " -- Error happened: Wrong median." << endl;
        return;
    }

    if (innerSortWithInnerSwap(0, size - 1, list) != 0)
        cout << __func__ << " -- Unexpected error happened." << endl;
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

    int med = getMedian(0, size - 1);
    if (med < 0) {
        cout << __func__ << " -- Error happened: Wrong median." << endl;
        return;
    }

    int *swap = new int[size];

    if (innerSort(0, size - 1, list, swap) != 0)
        cout << __func__ << " -- Unexpected error happened." << endl;

    delete[] swap;
}
