// -----------------------------------------------------------------------------
//       Filename: kadane.cpp
//       Revision: $Id$
//    Description: This file includes the definitions of the functions
//                 that implement maximum summation subarray search algorithm.
//        Created: 02/25/2016 03:20:49 PM
//       Compiler: G++
//         Author: Jason Meng (jm), jm652564@sju.edu
//
// Copyright (c) 2016 by Jason Meng, no rights reserved.
// -----------------------------------------------------------------------------


/** include guard: */
#ifndef MAX_SUM_SUBARRAY_H
#define MAX_SUM_SUBARRAY_H

/**
 * Search a specified array of int to find a subarray whose element summation is
 * the maximum among all possible subarrays of the array. This function is an
 * implementation of Kadane's algorithm.
 *
 * @param list      An array of int.
 * @param size      The size of the specified array.
 * @param bestStart The starting index of the found max subarray,
 *                  one of the 3 return values.
 * @param bestEnd   The ending index of the found max subarray.
 *                  one of the 3 return values.
 * @param bestSum   The summation of the found max subarray.
 *                  one of the 3 return values.
 */
void kadane(int list[], int size, int& bestStart, int& bestEnd, int& bestSum);


/**
 * Search entire array for a maximum subarray by using divide-and-conquer
 * approach. This is a recusive method.
 *
 * @param list          An array of int in which the function looks up for a max
 *                      subarray.
 * @param size          The size of the array.
 * @param bestStart     The starting index of the found max subarray,
 *                      one of the 3 return values.
 * @param bestEnd       The ending index of the found max subarray.
 *                      one of the 3 return values.
 * @param bestSum       The summation of the found max subarray.
 *                      one of the 3 return values.
 */
void find_maximum_subarray(int list[], int size, int& bestStart, int& bestEnd,
                           int& bestSum);


/**
 * This function implements a brute force fashion in n^2 time complexity
 * to find a subarray whose element sum is the maximum
 * in the given array.
 *
 * @param   list        A array to search its max subarray.
 * @param   size        The size of list.
 * @param   bestStart   The starting index of the found subarray,
 *                      one of the return values. if size <= 0, bestStart = -1.
 * @param   bestEnd     The ending index of the found subarray,
 *                      one of the return values. if size <= 0, bestEnd = -1.
 * @param   bestSum     The summation of the elements in the found subarray,
 *                      one of the return values. If size <= 0, bestSum == 0.
 */
void bruteForce_n2(int list[], int size, int& bestStart, int& bestEnd,
                   int& bestSum);


/**
 * This function implements a brute force fashion in n^3 time complexity
 * to find a subarray whose element sum is the maximum
 * in the given array.
 *
 * @param   list        A array to search its max subarray.
 * @param   size        The size of list.
 * @param   bestStart   The starting index of the found subarray,
 *                      one of the return values.
 * @param   bestEnd     The ending index of the found subarray,
 *                      one of the return values.
 * @param   bestSum     The summation of the elements in the found subarray,
 *                      one of the return values.
 */
void bruteForce_n3(int list[], int size, int& bestStart, int& bestEnd,
                   int& bestSum);

#endif /** end of include guard */
