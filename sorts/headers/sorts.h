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

#ifndef SORTS_H
#define SORTS_H


using namespace std;

/**
 * Do selection sort to the given list(array).
 *
 * @param size The size of the given list(array).
 * @param list An array to be sorted.
 */
void selectionSort(int list[], int size);

/**
 * Do insertion sort to the given list(array).
 *
 * @param size The size of the given list(array).
 * @param list An array to be sorted.
 */
void insertionSort(int list[], int size);

/**
 * Merge sort algorithm implementation.
 *
 * @param   size    The size of the array to be sorted.
 * @param   list    The array to be sorted.
 */
void mergeSort(int list[], int size);

/// Quick sort implementation
/// \param list The array to be sorted
/// \param size The length of the array
void quickSort(int list[], int size);

#endif
