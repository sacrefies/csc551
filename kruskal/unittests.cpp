// ------------------------------------------------------------------------------------
// Filename: unitTests.cpp
// Revision: $Id$
// Description: This file includes the standard unit tests against the max-sum
// algorithms.
// Created: 02/15/2016 01:20:29 PM
// Compiler: G++
// Author: Jason Meng (jm), jm652564@sju.edu
//
// Copyright (c) 2016 by Jason Meng
// ------------------------------------------------------------------------------------

// C headers
#include <cmath>
// C++ includes
#include <iostream>
#include <iomanip>
#include <exception>
#include <sstream>
#include <string>
// custom includes
#include "headers/logging.hpp"
#include "headers/bucket.hpp"
#include "headers/bucketsort.hpp"
#include "headers/utils.hpp"
#include "headers/unittests.hpp"


using std::exception;
using std::stringstream;
using std::endl;
using std::setprecision;
using std::runtime_error;
using std::invalid_argument;
using std::to_string;
using std::string;
using std::isnan;

using bucketsort::BucketSort;
using bucketsort::Bucket;


int default_initialzation_disposal_test() {
    stringstream msg;
    const string testName = "Bucket Sort Initialization and Disposal";
    int testFlag = -1;

    msg << "******** Test Name: " << testName;
    info("", msg.str());
    msg.clear();
    msg.str("");

    BucketSort * bs = nullptr;
    // test starts
    try {
        bs = new BucketSort();

        if (bs == nullptr)
            throw runtime_error("Failed. BucketSort is nullptr");

        if (bs->size() != 10) {
            msg << "Failed. Size expected=10, actual=";
            msg << bs->size();
            throw runtime_error(msg.str());
        }

        if (bs->length() != 0) {
            msg << "Failed. Length expected=0, actual=" << bs->length();
            throw runtime_error(msg.str());
        }

        msg << *bs;
        info("", msg.str());

        delete bs;
        bs = nullptr;

        testFlag = 0;
    } catch (exception& e) {
        error(__func__, e.what());
        testFlag = -1;
        if (bs != nullptr) {
            msg.clear();
            msg.str("");
            msg << *bs;
            error(__func__, "Problematic BucketSort: " + msg.str());
            delete bs;
            bs = nullptr;
        }
    }

    msg.clear();
    msg.str("");
    msg << "Test Finished: ";
    if (testFlag != 0) msg << "Failed";
    else msg << "Passed";
    info("", msg.str());

    return testFlag;
} // default_initialzation_disposal_test


int initialzation_disposal_test() {
    stringstream msg;
    const string testName = "Bucket Sort Initialization and Disposal, Size 1";
    int testFlag = -1;

    msg << "******** Test Name: " << testName;
    info("", msg.str());
    msg.clear();
    msg.str("");

    BucketSort * bs = nullptr;
    // test starts
    try {
        bs = new BucketSort(1);

        if (bs == nullptr)
            throw runtime_error("Failed. BucketSort is nullptr");

        if (bs->size() != 1) {
            msg << "Failed. Size expected=1, actual=";
            msg << bs->size();
            throw runtime_error(msg.str());
        }

        if (bs->length() != 0) {
            msg << "Failed. Length expected=0, actual=" << bs->length();
            throw runtime_error(msg.str());
        }

        msg << *bs;
        info("", msg.str());
        delete bs;
        bs = nullptr;

        testFlag = 0;
    } catch (exception& e) {
        error(__func__, e.what());
        testFlag = -1;
        if (bs != nullptr) {
            msg.clear();
            msg.str("");
            msg << *bs;
            error(__func__, "Problematic BucketSort: " + msg.str());
            delete bs;
            bs = nullptr;
        }
    }

    msg.clear();
    msg.str("");
    msg << "Test Finished: ";
    if (testFlag != 0) msg << "Failed";
    else msg << "Passed";
    info("", msg.str());

    return testFlag;
} // initialzation_disposal_test


int add_1_to_size_1_test() {
    stringstream msg;
    const string testName = "Add 1 Bucket into Size 1 Bucket Sort";
    int testFlag = -1;

    msg << "******** Test Name: " << testName;
    info("", msg.str());
    msg.clear();
    msg.str("");

    BucketSort * bs = nullptr;
    // test starts
    try {
        bs = new BucketSort(1);
        const double tmp = 0.30;
        bs->add(tmp);

        if (bs->size() != 1) {
            msg << "Failed. Size expected=1, actual=";
            msg << bs->size();
            throw runtime_error(msg.str());
        }

        if (bs->length() != 1) {
            msg << "Failed. Length expected=1, actual=" << bs->length();
            throw runtime_error(msg.str());
        }

        double item = bs->get(0);
        if (true == isnan(item)) {
            msg << "Failed. Result from get() expected=";
            msg << setprecision(6) << tmp;
            msg << ", actual=" << setprecision(6) << item;
            throw runtime_error(msg.str());
        }

        if (item * amplifier - tmp * amplifier > threshold) {
            msg << "Failed. Result from get() expected=";
            msg << setprecision(6) << tmp;
            msg << ", actual=" << setprecision(6) << item;
            throw runtime_error(msg.str());
        }

        msg << *bs;
        info("", msg.str());
        delete bs;
        bs = nullptr;

        testFlag = 0;
    } catch (exception& e) {
        error(__func__, e.what());
        testFlag = -1;
        if (bs != nullptr) {
            msg.clear();
            msg.str("");
            msg << *bs;
            error(__func__, "Problematic BucketSort: " + msg.str());
            delete bs;
            bs = nullptr;
        }
    }

    msg.clear();
    msg.str("");
    msg << "Test Finished: ";
    if (testFlag != 0) msg << "Failed";
    else msg << "Passed";
    info("", msg.str());

    return testFlag;
} // add_1_to_size_1_test


int add_same_5_to_size_1_test() {
    stringstream msg;
    const string testName = "Add 5 same Bucket into Size 1 Bucket Sort";
    int testFlag = -1;

    msg << "******** Test Name: " << testName;
    info("", msg.str());
    msg.clear();
    msg.str("");

    // test starts
    BucketSort * bs = nullptr;
    try {
        bs = new BucketSort(1);
        bs->add(0.10);
        bs->add(0.10);
        bs->add(0.10);
        bs->add(0.10);
        bs->add(0.10);

        if (bs->size() != 1) {
            msg << "Failed. Size expected=1, actual=";
            msg << bs->size();
            throw runtime_error(msg.str());
        }

        if (bs->length() != 5) {
            msg << "Failed. Length expected=5, actual=" << bs->length();
            throw runtime_error(msg.str());
        }

        for (int i = 0; i < 5; ++i) {
            double item = bs->get(i);
            if (true == isnan(item)) {
                msg << "Failed. Result from get(" << i << ") expected=";
                msg << setprecision(6) << 0.10;
                msg << ", actual=" << setprecision(6) << item;
                throw runtime_error(msg.str());
            }

            if (item * amplifier - 0.10 * amplifier > threshold ||
                item * amplifier - 0.10 * amplifier < 0.0)
            {
                msg << "Failed. Result from get(" << i << ") expected=";
                msg << setprecision(6) << 0.10;
                msg << ", actual=" << setprecision(6) << item;
                throw runtime_error(msg.str());
            }
        }

        msg << *bs;
        info("", msg.str());
        delete bs;
        bs = nullptr;

        testFlag = 0;
    } catch (exception& e) {
        error(__func__, e.what());
        testFlag = -1;
        if (bs != nullptr) {
            msg.clear();
            msg.str("");
            msg << *bs;
            error(__func__, "Problematic BucketSort: " + msg.str());
            delete bs;
            bs = nullptr;
        }
    }

    msg.clear();
    msg.str("");
    msg << "Test Finished: ";
    if (testFlag != 0) msg << "Failed";
    else msg << "Passed";
    info("", msg.str());

    return testFlag;
} // add_5_to_size_1_test


int add_sorted_5_to_size_2_test() {
    stringstream msg;
    const string testName = "Add 5 Bucket into Size 2 Bucket Sort";
    int testFlag = -1;

    msg << "******** Test Name: " << testName;
    info("", msg.str());
    msg.clear();
    msg.str("");

    // test starts
    BucketSort * bs = nullptr;
    try {
        bs = new BucketSort(2);
        double * values = new double[5];

        for (int i = 0; i < 5; ++i)
            values[i] = random_double(0, 1);

        info("", "Generated: " + array_to_string(values, 5));
        insertion_sort(values, 5);
        info("", "Sorted: " + array_to_string(values, 5));

        for (int i = 0; i < 5; i++)
            bs->add(values[i]);

        if (bs->size() != 2) {
            msg << "Failed. Size expected=2, actual=";
            msg << bs->size();
            throw runtime_error(msg.str());
        }

        if (bs->length() != 5) {
            msg << "Failed. Length expected=5, actual=" << bs->length();
            throw runtime_error(msg.str());
        }

        for (int i = 0; i < 5; ++i) {
            double item = bs->get(i);
            if (true == isnan(item)) {
                msg << "Failed. Result from get(" << i << ") expected=";
                msg << setprecision(6) << values[i];
                msg << ", actual=" << setprecision(6) << item;
                throw runtime_error(msg.str());
            }

            if (item * amplifier - values[i] * amplifier > threshold ||
                item * amplifier - values[i] * amplifier < 0.0)
            {
                msg << "Failed. Result from get(" << i << ") expected=";
                msg << setprecision(6) << values[i];
                msg << ", actual=" << setprecision(6) << item;
                throw runtime_error(msg.str());
            }
        }

        msg << *bs;
        info("", msg.str());
        delete bs;
        bs = nullptr;

        testFlag = 0;
    } catch (exception& e) {
        error(__func__, e.what());
        testFlag = -1;
        if (bs != nullptr) {
            msg.clear();
            msg.str("");
            msg << *bs;
            error(__func__, "Problematic BucketSort: " + msg.str());
            delete bs;
            bs = nullptr;
        }
    }

    msg.clear();
    msg.str("");
    msg << "Test Finished: ";
    if (testFlag != 0) msg << "Failed";
    else msg << "Passed";
    info("", msg.str());

    return testFlag;
} // add_5_to_size_2_test


int add_5_to_size_3_test() {
    stringstream msg;
    const string testName = "Add 5 Bucket into Size 3 Bucket Sort";
    int testFlag = -1;

    msg << "******** Test Name: " << testName;
    info("", msg.str());
    msg.clear();
    msg.str("");

    // test starts
    BucketSort * bs = nullptr;
    try {
        bs = new BucketSort(3);
        double * values = new double[5];
        for (int i = 0; i < 5; ++i) {
            values[i] = random_double(0, 1);
            bs->add(values[i]);
        }
        info("", "Generated: " + array_to_string(values, 5));
        if (bs->size() != 3) {
            msg << "Failed. Size expected=2, actual=";
            msg << bs->size();
            throw runtime_error(msg.str());
        }

        if (bs->length() != 5) {
            msg << "Failed. Length expected=5, actual=" << bs->length();
            throw runtime_error(msg.str());
        }

        for (int i = 0; i < 5; ++i) {
            double item = bs->get(i);
            if (true == isnan(item)) {
                msg << "Failed. Result from get(" << i << ")=NAN";
                throw runtime_error(msg.str());
            }

            if (0 != in_array(item, values, 5)) {
                msg << "Failed. get(" << i << ") = ";
                msg << setprecision(6) << item;
                msg << " does not exist in original values";
                throw runtime_error(msg.str());
            }
        }

        msg << *bs;
        info("", msg.str());
        delete bs;
        bs = nullptr;

        testFlag = 0;
    } catch (exception& e) {
        error(__func__, e.what());
        testFlag = -1;
        if (bs != nullptr) {
            msg.clear();
            msg.str("");
            msg << *bs;
            error(__func__, "Problematic BucketSort: " + msg.str());
            delete bs;
            bs = nullptr;
        }
    }

    msg.clear();
    msg.str("");
    msg << "Test Finished: ";
    if (testFlag != 0) msg << "Failed";
    else msg << "Passed";
    info("", msg.str());

    return testFlag;
} // add_5_to_size_2_test


int add_20_to_size_10_test() {
    stringstream msg;
    const string testName = "Add 5 Bucket into Size 3 Bucket Sort";
    int testFlag = -1;

    msg << "******** Test Name: " << testName;
    info("", msg.str());
    msg.clear();
    msg.str("");

    // test starts
    BucketSort * bs = nullptr;
    try {
        bs = new BucketSort();
        double * values = new double[20];
        for (int i = 0; i < 20; ++i) {
            values[i] = random_double(0, 1);
            bs->add(values[i]);
        }
        info("", "Generated: " + array_to_string(values, 20));
        if (bs->size() != 10) {
            msg << "Failed. Size expected=2, actual=";
            msg << bs->size();
            throw runtime_error(msg.str());
        }

        if (bs->length() != 20) {
            msg << "Failed. Length expected=20, actual=" << bs->length();
            throw runtime_error(msg.str());
        }

        for (int i = 0; i < 20; ++i) {
            double item = bs->get(i);
            if (true == isnan(item)) {
                msg << "Failed. Result from get(" << i << ")=NAN";
                throw runtime_error(msg.str());
            }

            if (0 != in_array(item, values, 20)) {
                msg << "Failed. get(" << i << ") = ";
                msg << setprecision(6) << item;
                msg << " does not exist in original values";
                throw runtime_error(msg.str());
            }
        }

        msg << *bs;
        info("", msg.str());
        delete bs;
        bs = nullptr;

        testFlag = 0;
    } catch (exception& e) {
        error(__func__, e.what());
        testFlag = -1;
        if (bs != nullptr) {
            msg.clear();
            msg.str("");
            msg << *bs;
            error(__func__, "Problematic BucketSort: " + msg.str());
            delete bs;
            bs = nullptr;
        }
    }

    msg.clear();
    msg.str("");
    msg << "Test Finished: ";
    if (testFlag != 0) msg << "Failed";
    else msg << "Passed";
    info("", msg.str());

    return testFlag;
} // add_20_to_size_10_test


int get_1_not_in_size_4_test() {
    stringstream msg;
    const string testName = "Get Data at Random Index from Size 4 BucketSort";
    int testFlag = -1;

    msg << "******** Test Name: " << testName;
    info("", msg.str());
    msg.clear();
    msg.str("");

    // test starts
    BucketSort * bs = nullptr;
    try {
        bs = new BucketSort(4);
        double * values = new double[20];

        for (int i = 0; i < 20; ++i) {
            values[i] = random_double(0, 1);
            bs->add(values[i]);
        }
        info("", "Generated: " + array_to_string(values, 20));
        insertion_sort(values, 20);
        info("", "Sorted: " + array_to_string(values, 20));

        if (bs->size() != 4) {
            msg << "Failed. Size expected=4, actual=";
            msg << bs->size();
            throw runtime_error(msg.str());
        }

        if (bs->length() != 20) {
            msg << "Failed. Length expected=20, actual=" << bs->length();
            throw runtime_error(msg.str());
        }

        info("", "Fetch buckets with index in range [0, 50), some of the returns should be NAN");
        int random_index;
        double item;
        testFlag = 0;
        for (int i = 0; i < 50; ++i) {
            random_index = (int) random_double(0, 51);
            msg << "get(" << random_index << ")=";
            item = bs->get(random_index);
            if (true == isnan(item)) {
                msg << "NAN";
                if (random_index < 20)
                    testFlag = -1;
            } else {
                msg << setprecision(6) << item;
                if (random_index >= 20)
                    testFlag = -1;
            }
            debug("", msg.str());
            msg.clear();
            msg.str("");
        }

        if (testFlag != 0)
            throw runtime_error("Failed. BucketSort.get(i) returns wrong result.");

        msg << *bs;
        info("", msg.str());
        delete bs;
        bs = nullptr;

        testFlag = 0;
    } catch (exception& e) {
        error(__func__, e.what());
        testFlag = -1;
        if (bs != nullptr) {
            msg.clear();
            msg.str("");
            msg << *bs;
            error(__func__, "Problematic BucketSort: " + msg.str());
            delete bs;
            bs = nullptr;
        }
    }

    msg.clear();
    msg.str("");
    msg << "Test Finished: ";
    if (testFlag != 0) msg << "Failed";
    else msg << "Passed";
    info("", msg.str());

    return testFlag;
} // add_20_to_size_10_test


// ===============================================================
#if defined(GRAD) && defined(EXTRA_CREDIT)
int add_1_to_size_1_test2() {
    stringstream msg;
    const string testName = "Add 1 Bucket into Size 1 Bucket Sort";
    int testFlag = -1;

    msg << "******** Test Name: " << testName;
    info("", msg.str());
    msg.clear();
    msg.str("");

    BucketSort * bs = nullptr;
    // test starts
    try {
        bs = new BucketSort(1);
        const double tmp = 0.30;
        bs->add(tmp);

        if (bs->size() != 1) {
            msg << "Failed. Size expected=1, actual=";
            msg << bs->size();
            throw runtime_error(msg.str());
        }

        if (bs->length() != 1) {
            msg << "Failed. Length expected=1, actual=" << bs->length();
            throw runtime_error(msg.str());
        }

        double item = bs->get2(0);
        if (true == isnan(item)) {
            msg << "Failed. Result from get() expected=";
            msg << setprecision(6) << tmp;
            msg << ", actual=" << setprecision(6) << item;
            throw runtime_error(msg.str());
        }

        if (item * amplifier - tmp * amplifier > threshold) {
            msg << "Failed. Result from get() expected=";
            msg << setprecision(6) << tmp;
            msg << ", actual=" << setprecision(6) << item;
            throw runtime_error(msg.str());
        }

        msg << *bs;
        info("", msg.str());
        delete bs;
        bs = nullptr;

        testFlag = 0;
    } catch (exception& e) {
        error(__func__, e.what());
        testFlag = -1;
        if (bs != nullptr) {
            msg.clear();
            msg.str("");
            msg << *bs;
            error(__func__, "Problematic BucketSort: " + msg.str());
            delete bs;
            bs = nullptr;
        }
    }

    msg.clear();
    msg.str("");
    msg << "Test Finished: ";
    if (testFlag != 0) msg << "Failed";
    else msg << "Passed";
    info("", msg.str());

    return testFlag;
} // add_1_to_size_1_test


int add_same_5_to_size_1_test2() {
    stringstream msg;
    const string testName = "Add 5 same Bucket into Size 1 Bucket Sort";
    int testFlag = -1;

    msg << "******** Test Name: " << testName;
    info("", msg.str());
    msg.clear();
    msg.str("");

    // test starts
    BucketSort * bs = nullptr;
    try {
        bs = new BucketSort(1);
        bs->add(0.10);
        bs->add(0.10);
        bs->add(0.10);
        bs->add(0.10);
        bs->add(0.10);

        if (bs->size() != 1) {
            msg << "Failed. Size expected=1, actual=";
            msg << bs->size();
            throw runtime_error(msg.str());
        }

        if (bs->length() != 5) {
            msg << "Failed. Length expected=5, actual=" << bs->length();
            throw runtime_error(msg.str());
        }

        for (int i = 0; i < 5; ++i) {
            double item = bs->get2(i);
            if (true == isnan(item)) {
                msg << "Failed. Result from get(" << i << ") expected=";
                msg << setprecision(6) << 0.10;
                msg << ", actual=" << setprecision(6) << item;
                throw runtime_error(msg.str());
            }

            if (item * amplifier - 0.10 * amplifier > threshold ||
                item * amplifier - 0.10 * amplifier < 0.0)
            {
                msg << "Failed. Result from get(" << i << ") expected=";
                msg << setprecision(6) << 0.10;
                msg << ", actual=" << setprecision(6) << item;
                throw runtime_error(msg.str());
            }
        }

        msg << *bs;
        info("", msg.str());
        delete bs;
        bs = nullptr;

        testFlag = 0;
    } catch (exception& e) {
        error(__func__, e.what());
        testFlag = -1;
        if (bs != nullptr) {
            msg.clear();
            msg.str("");
            msg << *bs;
            error(__func__, "Problematic BucketSort: " + msg.str());
            delete bs;
            bs = nullptr;
        }
    }

    msg.clear();
    msg.str("");
    msg << "Test Finished: ";
    if (testFlag != 0) msg << "Failed";
    else msg << "Passed";
    info("", msg.str());

    return testFlag;
} // add_5_to_size_1_test


int add_sorted_5_to_size_2_test2() {
    stringstream msg;
    const string testName = "Add 5 Bucket into Size 2 Bucket Sort";
    int testFlag = -1;

    msg << "******** Test Name: " << testName;
    info("", msg.str());
    msg.clear();
    msg.str("");

    // test starts
    BucketSort * bs = nullptr;
    try {
        bs = new BucketSort(2);
        double * values = new double[5];

        for (int i = 0; i < 5; ++i)
            values[i] = random_double(0, 1);

        info("", "Generated: " + array_to_string(values, 5));
        insertion_sort(values, 5);
        info("", "Sorted: " + array_to_string(values, 5));

        for (int i = 0; i < 5; i++)
            bs->add(values[i]);

        if (bs->size() != 2) {
            msg << "Failed. Size expected=2, actual=";
            msg << bs->size();
            throw runtime_error(msg.str());
        }

        if (bs->length() != 5) {
            msg << "Failed. Length expected=5, actual=" << bs->length();
            throw runtime_error(msg.str());
        }

        for (int i = 0; i < 5; ++i) {
            double item = bs->get2(i);
            if (true == isnan(item)) {
                msg << "Failed. Result from get(" << i << ") expected=";
                msg << setprecision(6) << values[i];
                msg << ", actual=" << setprecision(6) << item;
                throw runtime_error(msg.str());
            }

            if (item * amplifier - values[i] * amplifier > threshold ||
                item * amplifier - values[i] * amplifier < 0.0)
            {
                msg << "Failed. Result from get(" << i << ") expected=";
                msg << setprecision(6) << values[i];
                msg << ", actual=" << setprecision(6) << item;
                throw runtime_error(msg.str());
            }
        }

        msg << *bs;
        info("", msg.str());
        delete bs;
        bs = nullptr;

        testFlag = 0;
    } catch (exception& e) {
        error(__func__, e.what());
        testFlag = -1;
        if (bs != nullptr) {
            msg.clear();
            msg.str("");
            msg << *bs;
            error(__func__, "Problematic BucketSort: " + msg.str());
            delete bs;
            bs = nullptr;
        }
    }

    msg.clear();
    msg.str("");
    msg << "Test Finished: ";
    if (testFlag != 0) msg << "Failed";
    else msg << "Passed";
    info("", msg.str());

    return testFlag;
} // add_5_to_size_2_test


int add_5_to_size_3_test2() {
    stringstream msg;
    const string testName = "Add 5 Bucket into Size 3 Bucket Sort";
    int testFlag = -1;

    msg << "******** Test Name: " << testName;
    info("", msg.str());
    msg.clear();
    msg.str("");

    // test starts
    BucketSort * bs = nullptr;
    try {
        bs = new BucketSort(3);
        double * values = new double[5];
        for (int i = 0; i < 5; ++i) {
            values[i] = random_double(0, 1);
            bs->add(values[i]);
        }
        info("", "Generated: " + array_to_string(values, 5));
        if (bs->size() != 3) {
            msg << "Failed. Size expected=2, actual=";
            msg << bs->size();
            throw runtime_error(msg.str());
        }

        if (bs->length() != 5) {
            msg << "Failed. Length expected=5, actual=" << bs->length();
            throw runtime_error(msg.str());
        }

        for (int i = 0; i < 5; ++i) {
            double item = bs->get2(i);
            if (true == isnan(item)) {
                msg << "Failed. Result from get(" << i << ")=NAN";
                throw runtime_error(msg.str());
            }

            if (0 != in_array(item, values, 5)) {
                msg << "Failed. get(" << i << ") = ";
                msg << setprecision(6) << item;
                msg << " does not exist in original values";
                throw runtime_error(msg.str());
            }
        }

        msg << *bs;
        info("", msg.str());
        delete bs;
        bs = nullptr;

        testFlag = 0;
    } catch (exception& e) {
        error(__func__, e.what());
        testFlag = -1;
        if (bs != nullptr) {
            msg.clear();
            msg.str("");
            msg << *bs;
            error(__func__, "Problematic BucketSort: " + msg.str());
            delete bs;
            bs = nullptr;
        }
    }

    msg.clear();
    msg.str("");
    msg << "Test Finished: ";
    if (testFlag != 0) msg << "Failed";
    else msg << "Passed";
    info("", msg.str());

    return testFlag;
} // add_5_to_size_2_test


int add_20_to_size_10_test2() {
    stringstream msg;
    const string testName = "Add 5 Bucket into Size 3 Bucket Sort";
    int testFlag = -1;

    msg << "******** Test Name: " << testName;
    info("", msg.str());
    msg.clear();
    msg.str("");

    // test starts
    BucketSort * bs = nullptr;
    try {
        bs = new BucketSort();
        double * values = new double[20];
        for (int i = 0; i < 20; ++i) {
            values[i] = random_double(0, 1);
            bs->add(values[i]);
        }
        info("", "Generated: " + array_to_string(values, 20));
        if (bs->size() != 10) {
            msg << "Failed. Size expected=2, actual=";
            msg << bs->size();
            throw runtime_error(msg.str());
        }

        if (bs->length() != 20) {
            msg << "Failed. Length expected=20, actual=" << bs->length();
            throw runtime_error(msg.str());
        }

        for (int i = 0; i < 20; ++i) {
            double item = bs->get2(i);
            if (true == isnan(item)) {
                msg << "Failed. Result from get(" << i << ")=NAN";
                throw runtime_error(msg.str());
            }

            if (0 != in_array(item, values, 20)) {
                msg << "Failed. get(" << i << ") = ";
                msg << setprecision(6) << item;
                msg << " does not exist in original values";
                throw runtime_error(msg.str());
            }
        }

        msg << *bs;
        info("", msg.str());
        delete bs;
        bs = nullptr;

        testFlag = 0;
    } catch (exception& e) {
        error(__func__, e.what());
        testFlag = -1;
        if (bs != nullptr) {
            msg.clear();
            msg.str("");
            msg << *bs;
            error(__func__, "Problematic BucketSort: " + msg.str());
            delete bs;
            bs = nullptr;
        }
    }

    msg.clear();
    msg.str("");
    msg << "Test Finished: ";
    if (testFlag != 0) msg << "Failed";
    else msg << "Passed";
    info("", msg.str());

    return testFlag;
} // add_20_to_size_10_test


int get_1_not_in_size_4_test2() {
    stringstream msg;
    const string testName = "Get Data at Random Index from Size 4 BucketSort";
    int testFlag = -1;

    msg << "******** Test Name: " << testName;
    info("", msg.str());
    msg.clear();
    msg.str("");

    // test starts
    BucketSort * bs = nullptr;
    try {
        bs = new BucketSort(4);
        double * values = new double[20];

        for (int i = 0; i < 20; ++i) {
            values[i] = random_double(0, 1);
            bs->add(values[i]);
        }
        info("", "Generated: " + array_to_string(values, 20));
        insertion_sort(values, 20);
        info("", "Sorted: " + array_to_string(values, 20));

        if (bs->size() != 4) {
            msg << "Failed. Size expected=4, actual=";
            msg << bs->size();
            throw runtime_error(msg.str());
        }

        if (bs->length() != 20) {
            msg << "Failed. Length expected=20, actual=" << bs->length();
            throw runtime_error(msg.str());
        }

        info("", "Fetch buckets with index in range [0, 50), some of the returns should be NAN");
        int random_index;
        double item;
        testFlag = 0;
        for (int i = 0; i < 50; ++i) {
            random_index = (int) random_double(0, 51);
            msg << "get(" << random_index << ")=";
            item = bs->get2(random_index);
            if (true == isnan(item)) {
                msg << "NAN";
                if (random_index < 20)
                    testFlag = -1;
            } else {
                msg << setprecision(6) << item;
                if (random_index >= 20)
                    testFlag = -1;
            }
            debug("", msg.str());
            msg.clear();
            msg.str("");
        }

        if (testFlag != 0)
            throw runtime_error("Failed. BucketSort.get(i) returns wrong result.");

        msg << *bs;
        info("", msg.str());
        delete bs;
        bs = nullptr;

        testFlag = 0;
    } catch (exception& e) {
        error(__func__, e.what());
        testFlag = -1;
        if (bs != nullptr) {
            msg.clear();
            msg.str("");
            msg << *bs;
            error(__func__, "Problematic BucketSort: " + msg.str());
            delete bs;
            bs = nullptr;
        }
    }

    msg.clear();
    msg.str("");
    msg << "Test Finished: ";
    if (testFlag != 0) msg << "Failed";
    else msg << "Passed";
    info("", msg.str());

    return testFlag;
} // add_20_to_size_10_test


#endif // if defined(GRAD) && defined(EXTRA_CREDIT)
