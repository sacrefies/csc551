// ------------------------------------------------------------------------------------
//       Filename: unitTests.h
//       Revision: $Id$
//    Description: This file includes the definitions of test functions
//        Created: 02/15/2016 01:20:29 PM
//       Compiler: G++
//         Author: Jason Meng (jm), jm652564@sju.edu
//
// Copyright (c) 2016 by Jason Meng
// ------------------------------------------------------------------------------------


/* include guard:  */
#ifndef TESTS_H
#define TESTS_H


/**
 * Test an algorithm with an array whose max sum subarray is the largest
 * negative element (all elements are negative).
 *
 * @param func  A function which implements an algorithm to find the max-sum
 *              subarray. This function must satify the signature:
 *              void func_name(int[] array, int size, int& bestStart,
 *                             int& bestEnd, int& bestSum)
 *
 * @return Returns -1 if test failed; returns 0 if otherwise.
 */
int array_all_negative_test(void (* func)(int[], int, int&, int&, int&));


/**
 * Test an algorithm with an array which has 2 negative integers.
 *
 * @param func  A function which implements an algorithm to find the max-sum
 *              subarray. This function must satify the signature:
 *              void func_name(int[] array, int size, int& bestStart,
 *                             int& bestEnd, int& bestSum)
 *
 * @return Returns -1 if test failed; returns 0 if otherwise.
 */
int array_size_2_all_negative_test(void (* func)(int[], int, int&, int&, int&));


/**
 * Test an algorithm with a null pointer.
 *
 * @param func  A function which implements an algorithm to find the max-sum
 *              subarray. This function must satify the signature:
 *              void func_name(int[] array, int size, int& bestStart,
 *                             int& bestEnd, int& bestSum)
 *
 * @return Returns -1 if test failed; returns 0 if otherwise.
 */
int array_null_test(void (* func)(int[], int, int&, int&, int&));

/**
 * Test an algorithm with an array in size 1.
 *
 * @param func  A function which implements an algorithm to find the max-sum
 *              subarray. This function must satify the signature:
 *              void func_name(int[] array, int size, int& bestStart,
 *                             int& bestEnd, int& bestSum)
 *
 * @return Returns -1 if test failed; returns 0 if otherwise.
 */
int array_size_1_test(void (* func)(int[], int, int&, int&, int&));

/**
 * Test an algorithm with an array which has 2 positive integers.
 *
 * @param func  A function which implements an algorithm to find the max-sum
 *              subarray. This function must satify the signature:
 *              void func_name(int[] array, int size, int& bestStart,
 *                             int& bestEnd, int& bestSum)
 *
 * @return Returns -1 if test failed; returns 0 if otherwise.
 */
int array_size_2_all_positive_test(void (* func)(int[], int, int&, int&, int&));

/**
 * Test an algorithm with an array which has 1 positive and 1 negative integers.
 *
 * @param func  A function which implements an algorithm to find the max-sum
 *              subarray. This function must satify the signature:
 *              void func_name(int[] array, int size, int& bestStart,
 *                             int& bestEnd, int& bestSum)
 *
 * @return Returns -1 if test failed; returns 0 if otherwise.
 */
int array_size_2_1_pos_1_neg_test(void (* func)(int[], int, int&, int&, int&));

/**
 * Test an algorithm with an array which has 1 negative and 1 positive integers.
 *
 * @param func  A function which implements an algorithm to find the max-sum
 *              subarray. This function must satify the signature:
 *              void func_name(int[] array, int size, int& bestStart,
 *                             int& bestEnd, int& bestSum)
 *
 * @return Returns -1 if test failed; returns 0 if otherwise.
 */
int array_size_2_1_neg_1_pos_test(void (* func)(int[], int, int&, int&, int&));

/**
 * Test an algorithm with an array whose max sum subarray is itself.
 *
 * @param func  A function which implements an algorithm to find the max-sum
 *              subarray. This function must satify the signature:
 *              void func_name(int[] array, int size, int& bestStart,
 *                             int& bestEnd, int& bestSum)
 *
 * @return Returns -1 if test failed; returns 0 if otherwise.
 */
int array_self_max_test(void (* func)(int[], int, int&, int&, int&));

/**
 * Test an algorithm with an array whose max sum subarray appears in its 1st half.
 *
 * @param func  A function which implements an algorithm to find the max-sum
 *              subarray. This function must satify the signature:
 *              void func_name(int[] array, int size, int& bestStart,
 *                             int& bestEnd, int& bestSum)
 *
 * @return Returns -1 if test failed; returns 0 if otherwise.
 */
int array_max_1st_half_test(void (* func)(int[], int, int&, int&, int&));

/**
 * Test an algorithm with an array whose max sum subarray appears in its 2nd half.
 *
 * @param func  A function which implements an algorithm to find the max-sum
 *              subarray. This function must satify the signature:
 *              void func_name(int[] array, int size, int& bestStart,
 *                             int& bestEnd, int& bestSum)
 *
 * @return Returns -1 if test failed; returns 0 if otherwise.
 */
int array_max_2nd_half_test(void (* func)(int[], int, int&, int&, int&));

/**
 * Test an algorithm with an array whose max sum subarray appears in its middle.
 *
 * @param func  A function which implements an algorithm to find the max-sum
 *              subarray. This function must satify the signature:
 *              void func_name(int[] array, int size, int& bestStart,
 *                             int& bestEnd, int& bestSum)
 *
 * @return Returns -1 if test failed; returns 0 if otherwise.
 */
int array_max_mid_test(void (* func)(int[], int, int&, int&, int&));

/**
 * Test an algorithm with an array whose max sum subarray starts from some place
 * in its 1st half and ends at some place in the middle.
 *
 * @param func  A function which implements an algorithm to find the max-sum
 *              subarray. This function must satify the signature:
 *              void func_name(int[] array, int size, int& bestStart,
 *                             int& bestEnd, int& bestSum)
 *
 * @return Returns -1 if test failed; returns 0 if otherwise.
 */
int array_max_mid_left_leaning_test(void (* func)(int[], int, int&, int&, int&));

/**
 * Test an algorithm with an array whose max sum subarray starts from some place
 * in its middle and ends at some place in its 2nd half.
 *
 * @param func  A function which implements an algorithm to find the max-sum
 *              subarray. This function must satify the signature:
 *              void func_name(int[] array, int size, int& bestStart,
 *                             int& bestEnd, int& bestSum)
 *
 * @return Returns -1 if test failed; returns 0 if otherwise.
 */
int array_max_mid_right_leaning_test(void (* func)(int[], int, int&, int&, int&));

#endif /* end of include guard:  */
