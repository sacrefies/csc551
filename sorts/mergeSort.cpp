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
#include <stdint.h>
#include <iostream>

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
 *
 */
int64_t alterMerge(const int64_t lStart, const int64_t lEnd, const int64_t rStart, const int64_t rEnd, int64_t list[]) {
    // a tmp array as the merged result
    int64_t *merged = new int64_t[rEnd - lStart + 1];
    int64_t leftHead = lStart;
    int64_t rightHead = rStart;
    int64_t mergedIndex = 0;

/*
    // debug printing
    cout << __func__ << " -- The original: [";
    for (int64_t i = 0; i <= rEnd; ++i)
        cout << list[i] << ",";
    cout << "]" << endl;

    cout << "left: [";
    for (int64_t i = lStart; i <= lEnd; ++i)
        cout << list[i] << ",";
    cout << "]" << endl;

    cout << "right: [";
    for (int64_t i = rStart; i <= rEnd; ++i)
        cout << list[i] << ",";
    cout << "]" << endl;
*/

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
        for (int64_t i = leftHead; i <= lEnd; ++i)
            merged[mergedIndex++] = list[i];
    } else if (rightHead <= rEnd) {
        // right has remaining
        for (int64_t i = rightHead; i <= rEnd; ++i)
            merged[mergedIndex++] = list[i];
    }

/*
    // debug printing
    cout << __func__ << " -- temp merged: [";
    for (int64_t i = 0; i < rEnd - lStart + 1; ++i)
        cout << merged[i] << ",";
    cout << "]" << endl;
*/
    // copy the items from merged to list, from lStart to rEnd
    for (int64_t i = lStart; i <= rEnd; ++i)
        list[i] = merged[i-lStart];

    // free the temp array
    delete[] merged;

/*
    // debug printing
    cout << __func__ << " -- The merged which is copied back: [";
    for (int64_t i = lStart; i <= rEnd; ++i)
        cout << list[i] << ",";
    cout << "]" << endl;
*/

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
 */
int64_t merge(const int64_t lStart, const int64_t lEnd, const int64_t rStart, const int64_t rEnd, int64_t list[]) {
    int64_t leftHead, rightHead, leftEnd, tmpRHItem;

    leftHead = lStart;
    rightHead = rStart;
    leftEnd = lEnd;
    tmpRHItem = 0;

/*
    // debug printing
    cout << __func__ << " -- ";
    cout << "ls=" << lStart << " le=" << lEnd;
    cout << " rs=" << rStart << " re=" << rEnd;
    cout << endl;
    cout << __func__ << " -- The original: [";
    for (int64_t i = lStart; i <= rEnd; ++i)
        cout << list[i] << ",";
    cout << "]" << endl;

    cout << "left: [";
    for (int64_t i = lStart; i <= lEnd; ++i)
        cout << list[i] << ",";
    cout << "]" << endl;

    cout << "right: [";
    for (int64_t i = rStart; i <= rEnd; ++i)
        cout << list[i] << ",";
    cout << "]" << endl;
*/

    // left and right are sorted already.
    // just consider the overlapping part:
    //   if lh <= rh, just move lh to the next, no insertion
    //   if lh > rh, insert rh into the position where lh is
    //      move lh ... le to the right one by one (moving to the right
    //          means le -> le+1 == rh)
    //      move both lh and rh to their next postion
    while (leftHead <= leftEnd && leftEnd <= rEnd && rightHead <= rEnd) {
        // use <= to reduce the chance that moving happens
        if (list[leftHead] <= list[rightHead]) {
            // no insertion
            leftHead++;
        } else {
            // set the new leftEnd
            leftEnd = rightHead;
            // save the current rightHead value to tmpRHItem
            // list[rightHead] later will be replaced.
            tmpRHItem = list[rightHead];
/*
            // debug
            cout << __func__ << " -- rightHead=" << rightHead;
            cout << " tmpRHItem=" << tmpRHItem;
            cout << " leftHead=" << leftHead;
            cout << " leftEnd=" << leftEnd << endl;
*/
            // the destination of left-end is the current rightHead
            // move array items from leftHead to left-end to their right
            // one by one
            // use int instead of uint because here substraction is needed.
            for (int64_t i = rightHead - 1; i >= leftHead; --i)
                list[i+1] = list[i];
            // insert old rightHead value to the current leftHead
            list[leftHead] = tmpRHItem;
            // move leftHead and rightHead index to their next
            leftHead++;
            rightHead++;
        }
    }

/*
    // debug printing
    cout << __func__ << " -- The merged which is copied back: [";
    for (int64_t i = lStart; i <= rEnd; ++i)
        cout << list[i] << ",";
    cout << "]" << endl;
*/

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
int64_t getMedian(int64_t lowEnd, int64_t highEnd) {
/*
    // debug output
    cout << __func__;
    cout << " -- high = " << highEnd << " low = " << lowEnd;
*/
    if (lowEnd > highEnd)
        return -1;
    if (lowEnd == highEnd)
        return 0;

    int64_t sub = highEnd - lowEnd;

/*
    // debug output
    cout << " sub = " << sub;
    cout << " median = ";
    cout << (((sub & 1) == 1) ? sub >> 1: (sub - 1) >> 1);
    cout << endl;
*/

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
int64_t innerSort(const int64_t startIndex, const int64_t endIndex, int64_t list[]) {
/*
    // debug output
    cout << __func__ << " -- ";
    cout << "endIndex = " << endIndex;
    cout << " startIndex = " << startIndex << endl;
*/
    // return condition
    // -- only one item in the array, it is sorted.
    if (endIndex == startIndex) {
        return 0;
    }

    // get the median in left-leaning fashion
    int64_t median = getMedian(startIndex, endIndex);
/*
    // debug output
    cout << __func__ << " -- median = " << median << endl;
*/
    if (median < 0) {
        cout << __func__ << " -- Error happened: Wrong median." << endl;
        return -1;
    }

    // sort left
    if (innerSort(startIndex, median + startIndex, list) != 0) {
        cout << __func__ << " -- ";
        cout << "Error happened: Sorting left sub array failed." << endl;
        return -1;
    }

    // sort right
    if (innerSort(median + startIndex + 1, endIndex, list) != 0) {
        cout << __func__ << " -- ";
        cout << "Error happened: Sorting right sub array failed." << endl;
        return -1;
    }

    // merge
    if (merge(startIndex, median + startIndex, median + startIndex + 1, endIndex, list) != 0) {
    // if (alterMerge(startIndex, median + startIndex, median + startIndex + 1, endIndex, list) != 0) {
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
int64_t mergeSort(const int64_t size, int64_t list[]) {
    // some boundary checks
    if (size < 2) {
        cout << __func__ << " -- size == " << size << ", no sorting" << endl;
        return 0;
    }

/*
    // debug output
    cout << __func__ << " -- The original: [";
    for (int64_t i = 0; i < size; ++i)
        cout << list[i] << ",";
    cout << "]" << endl;
*/

    int64_t med = getMedian(0, size - 1);
    if (med < 0) {
        cout << __func__ << " -- Error happened: Wrong median." << endl;
        return -1;
    }

    innerSort(0, size - 1, list);

/*
    // debug output
    cout << __func__ << " -- The merged: [";
    for (int64_t i = 0; i < size; ++i)
        cout << list[i] << ",";
    cout << "]" << endl;
*/

    // end of program
    return 0;
}
