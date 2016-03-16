// ------------------------------------------------------------------------------------
//       Filename: unitTests.cpp
//       Revision: $Id$
//    Description: This file includes the standard unit tests against the max-sum
//                 algorithms.
//        Created: 02/15/2016 01:20:29 PM
//       Compiler: G++
//         Author: Jason Meng (jm), jm652564@sju.edu
//
// Copyright (c) 2016 by Jason Meng
// ------------------------------------------------------------------------------------


// C++ includes
#include <climits>
#include <iostream>
#include <exception>
#include <sstream>
#include <string>
// custom includes
#include "headers/arrayUtils.h"
#include "headers/logging.h"


using std::exception;
using std::stringstream;
using std::endl;


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
int array_null_test(void (* func)(int[], int, int&, int&, int&)) {
    stringstream msg;
    const string testName = "NULL Array Test";
    int testFlag = -1;
    int bestStart, bestEnd, bestSum, size;
    int * array = NULL;

    size = 1;

    msg << "Test Name: " << testName;
    info("", msg.str());
    msg.clear();
    msg.str("");

    // test starts
    try {
        (*func)(array, size, bestStart, bestEnd, bestSum);
        // assert the return values
        if (bestStart == -1 && bestEnd == -1 && bestSum == INT_MIN)
            testFlag = 0;
    } catch (exception& e) {
        error(__func__, e.what());
    }

    // test log
    msg << "Expected: bestStart = -1, ";
    msg << "Actual: bestStart = " << bestStart;
    info("", msg.str());
    msg.clear();
    msg.str("");
    msg << "Expected: bestEnd = -1, ";
    msg << "Actual: bestEnd = " << bestEnd;
    info("", msg.str());
    msg.clear();
    msg.str("");
    msg << "Expected: bestSum = " << INT_MIN << ", ";
    msg << "Actual: bestSum = " << bestSum;
    info("", msg.str());
    msg.clear();
    msg.str("");
    msg << "Test Finished: ";
    if (testFlag != 0) msg << "Failed";
    else msg << "Passed";
    info("", msg.str());

    return testFlag;
} // array_null_test


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
int array_size_1_test(void (* func)(int[], int, int&, int&, int&)) {
    stringstream msg;
    const string testName = "Array In Size 1 Test";
    int testFlag = -1;
    int bestStart, bestEnd, bestSum, size;
    int array[1] = { 10 };

    size = 1;

    msg << "Test Name: " << testName;
    info("", msg.str());
    msg.clear();
    msg.str("");

    // test starts
    try {
        (*func)(array, size, bestStart, bestEnd, bestSum);
        // assert the return values
        if (bestStart == 0 && bestEnd == 0 && bestSum == array[0])
            testFlag = 0;
    } catch (exception& e) {
        error(__func__, e.what());
    }

    // test log
    msg << "Expected: bestStart = 0, ";
    msg << "Actual: bestStart = " << bestStart;
    info("", msg.str());
    msg.clear();
    msg.str("");
    msg << "Expected: bestEnd = 0, ";
    msg << "Actual: bestEnd = " << bestEnd;
    info("", msg.str());
    msg.clear();
    msg.str("");
    msg << "Expected: bestSum = " << array[0] << ", ";
    msg << "Actual: bestSum = " << bestSum;
    info("", msg.str());
    msg.clear();
    msg.str("");
    msg << "Test Finished: ";
    if (testFlag != 0) msg << "Failed";
    else msg << "Passed";
    info("", msg.str());

    return testFlag;
} // array_size_1_test


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
int array_size_2_all_positive_test(void (* func)(int[], int, int&, int&, int&)) {
    stringstream msg;
    const string testName = "Array Size 2: All Positive Test";
    int testFlag = -1;
    int bestStart, bestEnd, bestSum, sum, size;
    int array[2] = { 10, 11 };

    size = 2;

    msg << "Test Name: " << testName;
    info("", msg.str());
    msg.clear();
    msg.str("");

    sum = elementSum(0, 1, array);

    // test starts
    try {
        (*func)(array, size, bestStart, bestEnd, bestSum);
        // assert the return values
        if (bestStart == 0 && bestEnd == 1 && bestSum == sum)
            testFlag = 0;
    } catch (exception& e) {
        error(__func__, e.what());
    }

    // test log
    msg << "Expected: bestStart = 0, ";
    msg << "Actual: bestStart = " << bestStart;
    info("", msg.str());
    msg.clear();
    msg.str("");
    msg << "Expected: bestEnd = 1, ";
    msg << "Actual: bestEnd = " << bestEnd;
    info("", msg.str());
    msg.clear();
    msg.str("");
    msg << "Expected: bestSum = " << sum << ", ";
    msg << "Actual: bestSum = " << bestSum;
    info("", msg.str());
    msg.clear();
    msg.str("");
    msg << "Test Finished: ";
    if (testFlag != 0) msg << "Failed";
    else msg << "Passed";
    info("", msg.str());

    return testFlag;
} // array_size_2_all_positive_test


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
int array_size_2_all_negative_test(void (* func)(int[], int, int&, int&, int&)) {
    stringstream msg;
    const string testName = "Array Size 2: All Positive Test";
    int testFlag = -1;
    int bestStart, bestEnd, bestSum, sum, size;
    int array[2] = { -10, -1 };

    size = 2;

    msg << "Test Name: " << testName;
    info("", msg.str());
    msg.clear();
    msg.str("");

    sum = elementSum(1, 1, array);

    // test starts
    try {
        (*func)(array, size, bestStart, bestEnd, bestSum);
        // assert the return values
        if (bestStart == 1 && bestEnd == 1 && bestSum == sum)
            testFlag = 0;
    } catch (exception& e) {
        error(__func__, e.what());
    }

    // test log
    msg << "Expected: bestStart = 0, ";
    msg << "Actual: bestStart = " << bestStart;
    info("", msg.str());
    msg.clear();
    msg.str("");
    msg << "Expected: bestEnd = 1, ";
    msg << "Actual: bestEnd = " << bestEnd;
    info("", msg.str());
    msg.clear();
    msg.str("");
    msg << "Expected: bestSum = " << sum << ", ";
    msg << "Actual: bestSum = " << bestSum;
    info("", msg.str());
    msg.clear();
    msg.str("");
    msg << "Test Finished: ";
    if (testFlag != 0) msg << "Failed";
    else msg << "Passed";
    info("", msg.str());

    return testFlag;
} // array_size_2_all_negative_test


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
int array_size_2_1_pos_1_neg_test(void (* func)(int[], int, int&, int&, int&)) {
    stringstream msg;
    const string testName = "Array Size 2: First Positive Second Negative Test";
    int testFlag = -1;
    int bestStart, bestEnd, bestSum, sum;
    int array[2] = { 10, -11 };
    int size = 2;

    msg << "Test Name: " << testName;
    info("", msg.str());
    msg.clear();
    msg.str("");

    sum = array[0];

    // test starts
    try {
        (*func)(array, size, bestStart, bestEnd, bestSum);
        // assert the return values
        if (bestStart == 0 && bestEnd == 0 && bestSum == sum)
            testFlag = 0;
    } catch (exception& e) {
        error(__func__, e.what());
    }

    // test log
    msg << "Expected: bestStart = 0, ";
    msg << "Actual: bestStart = " << bestStart;
    info("", msg.str());
    msg.clear();
    msg.str("");
    msg << "Expected: bestEnd = 0, ";
    msg << "Actual: bestEnd = " << bestEnd;
    info("", msg.str());
    msg.clear();
    msg.str("");
    msg << "Expected: bestSum = " << sum << ", ";
    msg << "Actual: bestSum = " << bestSum;
    info("", msg.str());
    msg.clear();
    msg.str("");
    msg << "Test Finished: ";
    if (testFlag != 0) msg << "Failed";
    else msg << "Passed";
    info("", msg.str());

    return testFlag;
} // array_size_2_1_pos_1_neg_test


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
int array_size_2_1_neg_1_pos_test(void (* func)(int[], int, int&, int&, int&)) {
    stringstream msg;
    const string testName = "Array Size 2: First Negative Second Positive Test";
    int testFlag = -1;
    int bestStart, bestEnd, bestSum, sum;
    int array[2] = { -10, 11 };
    int size = 2;

    msg << "Test Name: " << testName;
    info("", msg.str());
    msg.clear();
    msg.str("");

    sum = array[1];

    // test starts
    try {
        (*func)(array, size, bestStart, bestEnd, bestSum);
        // assert the return values
        if (bestStart == 1 && bestEnd == 1 && bestSum == sum)
            testFlag = 0;
    } catch (exception& e) {
        error(__func__, e.what());
    }

    // test log
    msg << "Expected: bestStart = 1, ";
    msg << "Actual: bestStart = " << bestStart;
    info("", msg.str());
    msg.clear();
    msg.str("");
    msg << "Expected: bestEnd = 1, ";
    msg << "Actual: bestEnd = " << bestEnd;
    info("", msg.str());
    msg.clear();
    msg.str("");
    msg << "Expected: bestSum = " << sum << ", ";
    msg << "Actual: bestSum = " << bestSum;
    info("", msg.str());
    msg.clear();
    msg.str("");
    msg << "Test Finished: ";
    if (testFlag != 0) msg << "Failed";
    else msg << "Passed";
    info("", msg.str());

    return testFlag;
} // array_size_2_1_neg_1_pos_test


/**
 * Test an algorithm with an array whose max sum subarray is itself
 * (all elements are positive).
 *
 * @param func  A function which implements an algorithm to find the max-sum
 *              subarray. This function must satify the signature:
 *              void func_name(int[] array, int size, int& bestStart,
 *                             int& bestEnd, int& bestSum)
 *
 * @return Returns -1 if test failed; returns 0 if otherwise.
 */
int array_self_max_test(void (* func)(int[], int, int&, int&, int&)) {
    stringstream msg;
    const string testName = "Array Self Max Test";
    int testFlag = -1;
    int bestStart, bestEnd, bestSum, sum;
    int array[10] = { 1, 3, 4, 5, 2, 4, 8, 10, 8, 3 };
    int size = 10;

    msg << "Test Name: " << testName;
    info("", msg.str());
    msg.clear();
    msg.str("");

    sum = elementSum(0, 9, array);

    // test starts
    try {
        (*func)(array, size, bestStart, bestEnd, bestSum);
        // assert the return values
        if (bestStart == 0 && bestEnd == 9 && bestSum == sum)
            testFlag = 0;
    } catch (exception& e) {
        error(__func__, e.what());
    }

    // test log
    msg << "Expected: bestStart = 0, ";
    msg << "Actual: bestStart = " << bestStart;
    info("", msg.str());
    msg.clear();
    msg.str("");
    msg << "Expected: bestEnd = 9, ";
    msg << "Actual: bestEnd = " << bestEnd;
    info("", msg.str());
    msg.clear();
    msg.str("");
    msg << "Expected: bestSum = " << sum << ", ";
    msg << "Actual: bestSum = " << bestSum;
    info("", msg.str());
    msg.clear();
    msg.str("");
    msg << "Test Finished: ";
    if (testFlag != 0) msg << "Failed";
    else msg << "Passed";
    info("", msg.str());

    return testFlag;
} // array_self_max_test


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
int array_all_negative_test(void (* func)(int[], int, int&, int&, int&)) {
    stringstream msg;
    const string testName = "Array All Negative Test";
    int testFlag = -1;
    int bestStart, bestEnd, bestSum, sum;
    int array[10] = { -9, -3, -4, -5, -2, -4, -8, -10, -8, -3 };
    int size = 10;

    msg << "Test Name: " << testName;
    info("", msg.str());
    msg.clear();
    msg.str("");

    sum = elementSum(4, 4, array);

    // test starts
    try {
        (*func)(array, size, bestStart, bestEnd, bestSum);
        // assert the return values
        if (bestStart == 4 && bestEnd == 4 && bestSum == sum)
            testFlag = 0;
    } catch (exception& e) {
        error(__func__, e.what());
    }

    // test log
    msg << "Expected: bestStart = 0, ";
    msg << "Actual: bestStart = " << bestStart;
    info("", msg.str());
    msg.clear();
    msg.str("");
    msg << "Expected: bestEnd = 9, ";
    msg << "Actual: bestEnd = " << bestEnd;
    info("", msg.str());
    msg.clear();
    msg.str("");
    msg << "Expected: bestSum = " << sum << ", ";
    msg << "Actual: bestSum = " << bestSum;
    info("", msg.str());
    msg.clear();
    msg.str("");
    msg << "Test Finished: ";
    if (testFlag != 0) msg << "Failed";
    else msg << "Passed";
    info("", msg.str());

    return testFlag;
} // array_all_negative_test


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
int array_max_1st_half_test(void (* func)(int[], int, int&, int&, int&)) {
    stringstream msg;
    const string testName = "Array Max in 1st Half Test";
    int testFlag = -1;
    int bestStart, bestEnd, bestSum, sum;
    int array[10] = { 1, 3, 4, 5, 0, -2, -1, 3, 0, -8 };
    int size = 10;

    msg << "Test Name: " << testName;
    info("", msg.str());
    msg.clear();
    msg.str("");

    sum = elementSum(0, 3, array);

    // test starts
    try {
        (*func)(array, size, bestStart, bestEnd, bestSum);
        // assert the return values
        if (bestStart == 0 && bestEnd == 3 && bestSum == sum)
            testFlag = 0;
    } catch (exception& e) {
        error(__func__, e.what());
    }

    // test log
    msg << "Expected: bestStart = 0, ";
    msg << "Actual: bestStart = " << bestStart;
    info("", msg.str());
    msg.clear();
    msg.str("");
    msg << "Expected: bestEnd = 3, ";
    msg << "Actual: bestEnd = " << bestEnd;
    info("", msg.str());
    msg.clear();
    msg.str("");
    msg << "Expected: bestSum = " << sum << ", ";
    msg << "Actual: bestSum = " << bestSum;
    info("", msg.str());
    msg.clear();
    msg.str("");
    msg << "Test Finished: ";
    if (testFlag != 0) msg << "Failed";
    else msg << "Passed";
    info("", msg.str());

    return testFlag;
} // array_max_1st_half_test


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
int array_max_2nd_half_test(void (* func)(int[], int, int&, int&, int&)) {
    stringstream msg;
    const string testName = "Array Max in 2nd Half Test";
    int testFlag = -1;
    int bestStart, bestEnd, bestSum, sum;
    int array[10] = { -1, 3, -2, -5, 1, 2, -1, 3, 7, 8 };
    int size = 10;

    msg << "Test Name: " << testName;
    info("", msg.str());
    msg.clear();
    msg.str("");

    sum = elementSum(4, 9, array);

    // test starts
    try {
        (*func)(array, size, bestStart, bestEnd, bestSum);
        // assert the return values
        if (bestStart == 4 && bestEnd == 9 && bestSum == sum)
            testFlag = 0;
    } catch (exception& e) {
        error(__func__, e.what());
    }

    // test log
    msg << "Expected: bestStart = 4, ";
    msg << "Actual: bestStart = " << bestStart;
    info("", msg.str());
    msg.clear();
    msg.str("");
    msg << "Expected: bestEnd = 9, ";
    msg << "Actual: bestEnd = " << bestEnd;
    info("", msg.str());
    msg.clear();
    msg.str("");
    msg << "Expected: bestSum = " << sum << ", ";
    msg << "Actual: bestSum = " << bestSum;
    info("", msg.str());
    msg.clear();
    msg.str("");
    msg << "Test Finished: ";
    if (testFlag != 0) msg << "Failed";
    else msg << "Passed";
    info("", msg.str());

    return testFlag;
} // array_max_2nd_half_test


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
int array_max_mid_test(void (* func)(int[], int, int&, int&, int&)) {
    stringstream msg;
    const string testName = "Array Max in middle Test";
    int testFlag = -1;
    int bestStart, bestEnd, bestSum, sum;
    int array[10] = { -1, 3, -4, 5, 0, 2, -1, 3, 0, -8 };
    int size = 10;

    msg << "Test Name: " << testName;
    info("", msg.str());
    msg.clear();
    msg.str("");

    sum = elementSum(3, 7, array);

    // test starts
    try {
        (*func)(array, size, bestStart, bestEnd, bestSum);
        // assert the return values
        if (bestStart == 3 && bestEnd == 7 && bestSum == sum)
            testFlag = 0;
    } catch (exception& e) {
        error(__func__, e.what());
    }

    // test log
    msg << "Expected: bestStart = 3, ";
    msg << "Actual: bestStart = " << bestStart;
    info("", msg.str());
    msg.clear();
    msg.str("");
    msg << "Expected: bestEnd = 7, ";
    msg << "Actual: bestEnd = " << bestEnd;
    info("", msg.str());
    msg.clear();
    msg.str("");
    msg << "Expected: bestSum = " << sum << ", ";
    msg << "Actual: bestSum = " << bestSum;
    info("", msg.str());
    msg.clear();
    msg.str("");
    msg << "Test Finished: ";
    if (testFlag != 0) msg << "Failed";
    else msg << "Passed";
    info("", msg.str());

    return testFlag;
} // array_max_mid_test


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
int array_max_mid_left_leaning_test(void (* func)(int[], int, int&, int&, int&)) {
    stringstream msg;
    const string testName = "Array Max In 1st Half and across Middle Test";
    int testFlag = -1;
    int bestStart, bestEnd, bestSum, sum;
    int array[10] = { -1, 3, 4, 5, 0, 2, 1, -3, 0, -8 };
    int size = 10;

    msg << "Test Name: " << testName;
    info("", msg.str());
    msg.clear();
    msg.str("");

    sum = elementSum(1, 6, array);

    // test starts
    try {
        (*func)(array, size, bestStart, bestEnd, bestSum);
        // assert the return values
        if (bestStart == 1 && bestEnd == 6 && bestSum == sum)
            testFlag = 0;
    } catch (exception& e) {
        error(__func__, e.what());
    }

    // test log
    msg << "Expected: bestStart = 1, ";
    msg << "Actual: bestStart = " << bestStart;
    info("", msg.str());
    msg.clear();
    msg.str("");
    msg << "Expected: bestEnd = 6, ";
    msg << "Actual: bestEnd = " << bestEnd;
    info("", msg.str());
    msg.clear();
    msg.str("");
    msg << "Expected: bestSum = " << sum << ", ";
    msg << "Actual: bestSum = " << bestSum;
    info("", msg.str());
    msg.clear();
    msg.str("");
    msg << "Test Finished: ";
    if (testFlag != 0) msg << "Failed";
    else msg << "Passed";
    info("", msg.str());

    return testFlag;
} // array_max_mid_left_leaning_test


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
int array_max_mid_right_leaning_test(void (* func)(int[], int, int&, int&, int&)) {
    stringstream msg;
    const string testName = "Array Max In 2st Half and across Middle Test";
    int testFlag = -1;
    int bestStart, bestEnd, bestSum, sum;
    int array[10] = { -1, -3, -2, 5, 0, 2, 1, 7, 4, -8 };
    int size = 10;

    msg << "Test Name: " << testName;
    info("", msg.str());
    msg.clear();
    msg.str("");

    sum = elementSum(3, 8, array);

    // test starts
    try {
        (*func)(array, size, bestStart, bestEnd, bestSum);
        // assert the return values
        if (bestStart == 3 && bestEnd == 8 && bestSum == sum)
            testFlag = 0;
    } catch (exception& e) {
        error(__func__, e.what());
    }

    // test log
    msg << "Expected: bestStart = 3, ";
    msg << "Actual: bestStart = " << bestStart;
    info("", msg.str());
    msg.clear();
    msg.str("");
    msg << "Expected: bestEnd = 8, ";
    msg << "Actual: bestEnd = " << bestEnd;
    info("", msg.str());
    msg.clear();
    msg.str("");
    msg << "Expected: bestSum = " << sum << ", ";
    msg << "Actual: bestSum = " << bestSum;
    info("", msg.str());
    msg.clear();
    msg.str("");
    msg << "Test Finished: ";
    if (testFlag != 0) msg << "Failed";
    else msg << "Passed";
    info("", msg.str());

    return testFlag;
} // array_max_mid_right_leaning_test
