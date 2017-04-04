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
#include "headers/logging.h"
#include "headers/VectorBucketSort.h"
#include "headers/utils.h"
#include "headers/unittests.h"


using std::exception;
using std::stringstream;
using std::endl;
using std::setprecision;
using std::runtime_error;
using std::invalid_argument;
using std::to_string;
using std::string;
using std::isnan;


int default_initialzation_disposal_test() {
    stringstream msg;
    const string testName = "Default Initialization and Disposal";
    int testFlag = -1;

    msg << "******** Test Name: " << testName;
    info("", msg.str());
    msg.clear();
    msg.str("");

    VectorBucketSort * bs = nullptr;
    // test starts
    try {
        bs = new VectorBucketSort();

        if (bs == nullptr)
            throw runtime_error("Failed. VectorBucketSort is nullptr");

        if (bs->size() != 10) {
            msg << "Failed. Size expected=10, actual=";
            msg << bs->size();
            throw runtime_error(msg.str());
        }

        msg << *bs;
        info("", msg.str());

        testFlag = 0;
    } catch (exception& e) {
        error(__func__, e.what());
        testFlag = -1;
        if (bs != nullptr) {
            msg.clear();
            msg.str("");
            msg << *bs;
            error(__func__, "Problematic BucketSort: " + msg.str());
        }
    }

    if (bs != nullptr) {
        delete bs;
        bs = nullptr;
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
    const string testName = "Initialization and Disposal in Size 1";
    int testFlag = -1;

    msg << "******** Test Name: " << testName;
    info("", msg.str());
    msg.clear();
    msg.str("");

    VectorBucketSort * bs = nullptr;
    // test starts
    try {
        bs = new VectorBucketSort(1);

        if (bs == nullptr)
            throw runtime_error("Failed. BucketSort is nullptr");

        if (bs->size() != 1) {
            msg << "Failed. Size expected=1, actual=";
            msg << bs->size();
            throw runtime_error(msg.str());
        }

        msg << *bs;
        info("", msg.str());
        testFlag = 0;
    } catch (exception& e) {
        error(__func__, e.what());
        testFlag = -1;
        if (bs != nullptr) {
            msg.clear();
            msg.str("");
            msg << *bs;
            error(__func__, "Problematic BucketSort: " + msg.str());
        }
    }

    if (bs != nullptr) {
        delete bs;
        bs = nullptr;
    }

    msg.clear();
    msg.str("");
    msg << "Test Finished: ";
    if (testFlag != 0) msg << "Failed";
    else msg << "Passed";
    info("", msg.str());

    return testFlag;
} // initialzation_disposal_test


int get_random_in_random_size_test() {
    stringstream msg;
    const string testName =
        "Get Data at Random Index out of 20 elements from Random Size Bucket List";
    int testFlag = -1;

    msg << "******** Test Name: " << testName;
    info("", msg.str());
    msg.clear();
    msg.str("");

    // test starts
    VectorBucketSort * bs = nullptr;
    try {
        int bucketListSize = random_int(5, 20);
        bs = new VectorBucketSort(bucketListSize);
        double * values = new double[30];

        for (int i = 0; i < 20; ++i) {
            values[i] = random_double(0, 1);
            bs->add(values[i]);
        }

        if (bs->size() != bucketListSize) {
            msg << "Failed. Size expected=4, actual=";
            msg << bs->size();
            throw runtime_error(msg.str());
        }

        info("", "Generated: " + array_to_string(values, 20));
        bs->sortAll();

        info("",
             "Fetch elements at index in range [0, 50], some of the returns should be NAN");
        testFlag = 0;
        for (int i = 0; i < 50; ++i) {
            int random_index = random_int(0, 51);
            msg << "get(" << random_index << ")=";
            double item = bs->get(random_index);
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
            throw runtime_error(
                      "Failed. BucketSort.get(i) returns wrong result.");

        msg << *bs;
        info("", msg.str());
        testFlag = 0;
    } catch (exception& e) {
        error(__func__, e.what());
        testFlag = -1;
        if (bs != nullptr) {
            msg.clear();
            msg.str("");
            msg << *bs;
            error(__func__, "Problematic BucketSort: " + msg.str());
        }
    }

    if (bs != nullptr) {
        delete bs;
        bs = nullptr;
    }

    msg.clear();
    msg.str("");
    msg << "Test Finished: ";
    if (testFlag != 0) msg << "Failed";
    else msg << "Passed";
    info("", msg.str());

    return testFlag;
}


int add_1_to_size_1_test() {
    stringstream msg;
    const string testName = "Add 1 element into Size 1 Bucket List";
    int testFlag = -1;

    msg << "******** Test Name: " << testName;
    info("", msg.str());
    msg.clear();
    msg.str("");

    VectorBucketSort * bs = nullptr;
    // test starts
    try {
        bs = new VectorBucketSort(1);
        const double tmp = 0.30;
        bs->add(tmp);

        if (bs->size() != 1) {
            msg << "Failed. Size expected=1, actual=";
            msg << bs->size();
            throw runtime_error(msg.str());
        }

        double item = bs->get(0);
        if (true == isnan(item)) {
            msg << "Failed. Result from get() expected=";
            msg << setprecision(6) << tmp;
            msg << ", actual=" << setprecision(6) << item;
            throw runtime_error(msg.str());
        }

        if (item - tmp > threshold) {
            msg << "Failed. Result from get() expected=";
            msg << setprecision(6) << tmp;
            msg << ", actual=" << setprecision(6) << item;
            throw runtime_error(msg.str());
        }

        msg << *bs;
        info("", msg.str());
        testFlag = 0;
    } catch (exception& e) {
        error(__func__, e.what());
        testFlag = -1;
        if (bs != nullptr) {
            msg.clear();
            msg.str("");
            msg << *bs;
            error(__func__, "Problematic BucketSort: " + msg.str());
        }
    }

    if (bs != nullptr) {
        delete bs;
        bs = nullptr;
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
    const string testName = "Add 5 Same elements into Size 1 Bucket List";
    int testFlag = -1;

    msg << "******** Test Name: " << testName;
    info("", msg.str());
    msg.clear();
    msg.str("");

    // test starts
    VectorBucketSort * bs = nullptr;
    try {
        bs = new VectorBucketSort(1);
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

        for (int i = 0; i < 5; ++i) {
            double item = bs->get(i);
            if (true == isnan(item)) {
                msg << "Failed. Result from get(" << i << ") expected=";
                msg << setprecision(6) << 0.10;
                msg << ", actual=" << setprecision(6) << item;
                throw runtime_error(msg.str());
            }

            if (item - 0.10 > threshold ||
                item - 0.10 < 0.0) {
                msg << "Failed. Result from get(" << i << ") expected=";
                msg << setprecision(6) << 0.10;
                msg << ", actual=" << setprecision(6) << item;
                throw runtime_error(msg.str());
            }
        }

        msg << *bs;
        info("", msg.str());
        testFlag = 0;
    } catch (exception& e) {
        error(__func__, e.what());
        testFlag = -1;
        if (bs != nullptr) {
            msg.clear();
            msg.str("");
            msg << *bs;
            error(__func__, "Problematic BucketSort: " + msg.str());
        }
    }

    if (bs != nullptr) {
        delete bs;
        bs = nullptr;
    }

    msg.clear();
    msg.str("");
    msg << "Test Finished: ";
    if (testFlag != 0) msg << "Failed";
    else msg << "Passed";
    info("", msg.str());

    return testFlag;
} // add_5_to_size_1_test


int add_random_5_to_size_2_sort_test() {
    stringstream msg;
    const string testName =
        "Add 5 Random Elements into Size 2 Sorted Bucket List";
    int testFlag = -1;

    msg << "******** Test Name: " << testName;
    info("", msg.str());
    msg.clear();
    msg.str("");

    // test starts
    VectorBucketSort * bs = nullptr;
    try {
        bs = new VectorBucketSort(2);
        double * values = new double[5];
        for (int i = 0; i < 5; ++i) {
            values[i] = random_double(0, 1);
            bs->add(values[i]);
        }

        info("", "Generated: " + array_to_string(values, 5));

        if (bs->size() != 2) {
            msg << "Failed. Size expected=2, actual=";
            msg << bs->size();
            throw runtime_error(msg.str());
        }

        insertion_sort(values, 5);
        info("", "Sorted: " + array_to_string(values, 5));
        bs->sortAll();

        for (int i = 0; i < 5; ++i) {
            double item = bs->get(i);
            if (true == isnan(item)) {
                msg << "Failed. Result from get(" << i << ") expected=";
                msg << setprecision(6) << values[i];
                msg << ", actual=" << setprecision(6) << item;
                throw runtime_error(msg.str());
            }

            if (item - values[i] > threshold ||
                item - values[i] < 0.0) {
                msg << "Failed. Result from get(" << i << ") expected=";
                msg << setprecision(6) << values[i];
                msg << ", actual=" << setprecision(6) << item;
                throw runtime_error(msg.str());
            }
        }

        msg << *bs;
        info("", msg.str());
        testFlag = 0;
    } catch (exception& e) {
        error(__func__, e.what());
        testFlag = -1;
        if (bs != nullptr) {
            msg.clear();
            msg.str("");
            msg << *bs;
            error(__func__, "Problematic BucketSort: " + msg.str());
        }
    }

    if (bs != nullptr) {
        delete bs;
        bs = nullptr;
    }

    msg.clear();
    msg.str("");
    msg << "Test Finished: ";
    if (testFlag != 0) msg << "Failed";
    else msg << "Passed";
    info("", msg.str());

    return testFlag;
} // add_5_to_size_2_test


int add_random_5_to_size_3_sort_test() {
    stringstream msg;
    const string testName =
        "Add 5 Ramdom Elements into Size 3 Sorted Bucket List";
    int testFlag = -1;

    msg << "******** Test Name: " << testName;
    info("", msg.str());
    msg.clear();
    msg.str("");

    // test starts
    VectorBucketSort * bs = nullptr;
    try {
        bs = new VectorBucketSort(3);
        double * values = new double[5];
        for (int i = 0; i < 5; ++i) {
            values[i] = random_double(0, 1);
            bs->add(values[i]);
        }
        if (bs->size() != 3) {
            msg << "Failed. Size expected=2, actual=";
            msg << bs->size();
            throw runtime_error(msg.str());
        }

        bs->sortAll();
        info("", "Generated: " + array_to_string(values, 5));
        insertion_sort(values, 5);
        info("", "Sorted: " + array_to_string(values, 5));
        for (int i = 0; i < 5; ++i) {
            double item = bs->get(i);
            if (true == isnan(item)) {
                msg << "Failed. Result from get(" << i << ")=NAN";
                throw runtime_error(msg.str());
            }

            if (item - values[i] > threshold || item - values[i] < 0.0) {
                msg << "Failed. Result from get(" << i << ") expected=";
                msg << setprecision(6) << values[i];
                msg << ", actual=" << setprecision(6) << item;
                throw runtime_error(msg.str());
            }
        }

        msg << *bs;
        info("", msg.str());
        testFlag = 0;
    } catch (exception& e) {
        error(__func__, e.what());
        testFlag = -1;
        if (bs != nullptr) {
            msg.clear();
            msg.str("");
            msg << *bs;
            error(__func__, "Problematic BucketSort: " + msg.str());
        }
    }

    if (bs != nullptr) {
        delete bs;
        bs = nullptr;
    }

    msg.clear();
    msg.str("");
    msg << "Test Finished: ";
    if (testFlag != 0) msg << "Failed";
    else msg << "Passed";
    info("", msg.str());

    return testFlag;
} // add_5_to_size_2_test


int add_random_20_to_size_10_test() {
    stringstream msg;
    const string testName =
        "Add 20 Random Elements into Size 10 Unsorted Bucket List";
    int testFlag = -1;

    msg << "******** Test Name: " << testName;
    info("", msg.str());
    msg.clear();
    msg.str("");

    // test starts
    VectorBucketSort * bs = nullptr;
    try {
        bs = new VectorBucketSort();
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
        testFlag = 0;
    } catch (exception& e) {
        error(__func__, e.what());
        testFlag = -1;
        if (bs != nullptr) {
            msg.clear();
            msg.str("");
            msg << *bs;
            error(__func__, "Problematic BucketSort: " + msg.str());
        }
    }

    if (bs != nullptr) {
        delete bs;
        bs = nullptr;
    }

    msg.clear();
    msg.str("");
    msg << "Test Finished: ";
    if (testFlag != 0) msg << "Failed";
    else msg << "Passed";
    info("", msg.str());

    return testFlag;
}


int add_random_20_to_size_10_sort_test() {
    stringstream msg;
    const string testName =
        "Add 20 Random Elements into Size 10 Sorted Buckets List";
    int testFlag = -1;

    msg << "******** Test Name: " << testName;
    info("", msg.str());
    msg.clear();
    msg.str("");

    // test starts
    VectorBucketSort * bs = nullptr;
    try {
        bs = new VectorBucketSort();
        double * values = new double[20];
        for (int i = 0; i < 20; ++i) {
            values[i] = random_double(0, 1);
            bs->add(values[i]);
        }

        if (bs->size() != 10) {
            msg << "Failed. Size expected=2, actual=";
            msg << bs->size();
            throw runtime_error(msg.str());
        }

        bs->sortAll();
        info("", "Generated: " + array_to_string(values, 20));
        insertion_sort(values, 20);
        info("", "Sorted: " + array_to_string(values, 20));

        for (int i = 0; i < 20; ++i) {
            double item = bs->get(i);
            if (true == isnan(item)) {
                msg << "Failed. Result from get(" << i << ")=NAN";
                throw runtime_error(msg.str());
            }

            if (item - values[i] > threshold || item - values[i] < 0.0) {
                msg << "Failed. Result from get(" << i << ") expected=";
                msg << setprecision(6) << values[i];
                msg << ", actual=" << setprecision(6) << item;
                throw runtime_error(msg.str());
            }
        }

        msg << *bs;
        info("", msg.str());
        testFlag = 0;
    } catch (exception& e) {
        error(__func__, e.what());
        testFlag = -1;
        if (bs != nullptr) {
            msg.clear();
            msg.str("");
            msg << *bs;
            error(__func__, "Problematic BucketSort: " + msg.str());
        }
    }

    if (bs != nullptr) {
        delete bs;
        bs = nullptr;
    }

    msg.clear();
    msg.str("");
    msg << "Test Finished: ";
    if (testFlag != 0) msg << "Failed";
    else msg << "Passed";
    info("", msg.str());

    return testFlag;
}


int load_factor_random_in_random_size_test() {
    stringstream msg;
    const string testName = "Test load factor computation.";
    int testFlag = 0;

    msg << "******** Test Name: " << testName;
    info("", msg.str());
    msg.clear();
    msg.str("");

    const int repeating = 30;
    info("", "Try 30 times for random recipes.");

    for (int i = 0; i < repeating; ++i) {
        // init data array in random size.
        int dataSize = random_int(0, 50) + 1;
        int bucketSize = random_int(0, 20) + 1;

        double * values = new double[dataSize];
        VectorBucketSort * bs = nullptr;

        try {
            bs = new VectorBucketSort(bucketSize);
            for (int j = 0; j < dataSize; ++j) {
                values[j] = random_double(0, 1);
                bs->add(values[j]);
            }
            info("", "Generated: " + array_to_string(values, dataSize));
            // testing the load factors
            double expectedLoadFactor = (double)dataSize / bucketSize;
            double actualLoadFactor = bs->getLoadFactor();
            if (expectedLoadFactor - actualLoadFactor > threshold) {
                msg << "Failed. Load factor expected=" << setprecision(9) <<
                expectedLoadFactor << ", ";
                msg << "actual=" << setprecision(9) << actualLoadFactor << endl;
                msg << "Data size: " << dataSize << ", Bucket List Size: " <<
                bucketSize;
                throw runtime_error(msg.str());
            }
        } catch (exception& e) {
            error(__func__, e.what());
            error(__func__,
                  "Source array: " + array_to_string(values, dataSize));
            msg.clear();
            msg.str("");
            if (bs != nullptr) {
                msg << *bs;
                error(__func__, "Problematic BucketSort: " + msg.str());
            }
            testFlag = -1;
        }

        if (bs != nullptr) {
            delete bs;
            bs = nullptr;
        }
    }

    msg.clear();
    msg.str("");
    msg << "Test Finished: ";
    if (testFlag == 0) msg << "Passed";
    else msg << "Failed";
    info("", msg.str());
    return testFlag;
}


// ===============================================================
#if defined(GRAD) && defined(EXTRA_CREDIT)
int get_random_in_random_size_test2() {
    stringstream msg;
    const string testName =
        "Get Data at Random Index out of 20 elements from Random Size Bucket List";
    int testFlag = -1;

    msg << "******** Test Name: " << testName;
    info("", msg.str());
    msg.clear();
    msg.str("");

    // test starts
    VectorBucketSort * bs = nullptr;
    try {
        int bucketListSize = random_int(5, 20);
        bs = new VectorBucketSort(bucketListSize);
        double * values = new double[30];

        for (int i = 0; i < 20; ++i) {
            values[i] = random_double(0, 1);
            bs->add(values[i]);
        }

        if (bs->size() != bucketListSize) {
            msg << "Failed. Size expected=4, actual=";
            msg << bs->size();
            throw runtime_error(msg.str());
        }

        info("", "Generated: " + array_to_string(values, 20));
        bs->sortAll();

        info("",
             "Fetch elements at index in range [0, 50], some of the returns should be NAN");
        testFlag = 0;
        for (int i = 0; i < 50; ++i) {
            int random_index = random_int(0, 51);
            msg << "get2(" << random_index << ")=";
            double item = bs->get2(random_index);
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
            throw runtime_error(
                      "Failed. BucketSort.get2(i) returns wrong result.");

        msg << *bs;
        info("", msg.str());
        testFlag = 0;
    } catch (exception& e) {
        error(__func__, e.what());
        testFlag = -1;
        if (bs != nullptr) {
            msg.clear();
            msg.str("");
            msg << *bs;
            error(__func__, "Problematic BucketSort: " + msg.str());
        }
    }

    if (bs != nullptr) {
        delete bs;
        bs = nullptr;
    }

    msg.clear();
    msg.str("");
    msg << "Test Finished: ";
    if (testFlag != 0) msg << "Failed";
    else msg << "Passed";
    info("", msg.str());

    return testFlag;
}


int add_1_to_size_1_test2() {
    stringstream msg;
    const string testName = "Add 1 element into Size 1 Bucket List";
    int testFlag = -1;

    msg << "******** Test Name: " << testName;
    info("", msg.str());
    msg.clear();
    msg.str("");

    VectorBucketSort * bs = nullptr;
    // test starts
    try {
        bs = new VectorBucketSort(1);
        const double tmp = 0.30;
        bs->add(tmp);

        if (bs->size() != 1) {
            msg << "Failed. Size expected=1, actual=";
            msg << bs->size();
            throw runtime_error(msg.str());
        }

        double item = bs->get2(0);
        if (true == isnan(item)) {
            msg << "Failed. Result from get2() expected=";
            msg << setprecision(6) << tmp;
            msg << ", actual=" << setprecision(6) << item;
            throw runtime_error(msg.str());
        }

        if (item - tmp > threshold) {
            msg << "Failed. Result from get2() expected=";
            msg << setprecision(6) << tmp;
            msg << ", actual=" << setprecision(6) << item;
            throw runtime_error(msg.str());
        }

        msg << *bs;
        info("", msg.str());
        testFlag = 0;
    } catch (exception& e) {
        error(__func__, e.what());
        testFlag = -1;
        if (bs != nullptr) {
            msg.clear();
            msg.str("");
            msg << *bs;
            error(__func__, "Problematic BucketSort: " + msg.str());
        }
    }

    if (bs != nullptr) {
        delete bs;
        bs = nullptr;
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
    const string testName = "Add 5 Same elements into Size 1 Bucket List";
    int testFlag = -1;

    msg << "******** Test Name: " << testName;
    info("", msg.str());
    msg.clear();
    msg.str("");

    // test starts
    VectorBucketSort * bs = nullptr;
    try {
        bs = new VectorBucketSort(1);
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

        for (int i = 0; i < 5; ++i) {
            double item = bs->get2(i);
            if (true == isnan(item)) {
                msg << "Failed. Result from get2(" << i << ") expected=";
                msg << setprecision(6) << 0.10;
                msg << ", actual=" << setprecision(6) << item;
                throw runtime_error(msg.str());
            }

            if (item - 0.10 > threshold ||
                item - 0.10 < 0.0) {
                msg << "Failed. Result from get2(" << i << ") expected=";
                msg << setprecision(6) << 0.10;
                msg << ", actual=" << setprecision(6) << item;
                throw runtime_error(msg.str());
            }
        }

        msg << *bs;
        info("", msg.str());
        testFlag = 0;
    } catch (exception& e) {
        error(__func__, e.what());
        testFlag = -1;
        if (bs != nullptr) {
            msg.clear();
            msg.str("");
            msg << *bs;
            error(__func__, "Problematic BucketSort: " + msg.str());
        }
    }

    if (bs != nullptr) {
        delete bs;
        bs = nullptr;
    }

    msg.clear();
    msg.str("");
    msg << "Test Finished: ";
    if (testFlag != 0) msg << "Failed";
    else msg << "Passed";
    info("", msg.str());

    return testFlag;
} // add_5_to_size_1_test


int add_random_5_to_size_2_sort_test2() {
    stringstream msg;
    const string testName =
        "Add 5 Random Elements into Size 2 Sorted Bucket List";
    int testFlag = -1;

    msg << "******** Test Name: " << testName;
    info("", msg.str());
    msg.clear();
    msg.str("");

    // test starts
    VectorBucketSort * bs = nullptr;
    try {
        bs = new VectorBucketSort(2);
        double * values = new double[5];
        for (int i = 0; i < 5; ++i) {
            values[i] = random_double(0, 1);
            bs->add(values[i]);
        }

        info("", "Generated: " + array_to_string(values, 5));

        if (bs->size() != 2) {
            msg << "Failed. Size expected=2, actual=";
            msg << bs->size();
            throw runtime_error(msg.str());
        }

        insertion_sort(values, 5);
        info("", "Sorted: " + array_to_string(values, 5));
        bs->sortAll();

        for (int i = 0; i < 5; ++i) {
            double item = bs->get2(i);
            if (true == isnan(item)) {
                msg << "Failed. Result from get2(" << i << ") expected=";
                msg << setprecision(6) << values[i];
                msg << ", actual=" << setprecision(6) << item;
                throw runtime_error(msg.str());
            }

            if (item - values[i] > threshold ||
                item - values[i] < 0.0) {
                msg << "Failed. Result from get2(" << i << ") expected=";
                msg << setprecision(6) << values[i];
                msg << ", actual=" << setprecision(6) << item;
                throw runtime_error(msg.str());
            }
        }

        msg << *bs;
        info("", msg.str());
        testFlag = 0;
    } catch (exception& e) {
        error(__func__, e.what());
        testFlag = -1;
        if (bs != nullptr) {
            msg.clear();
            msg.str("");
            msg << *bs;
            error(__func__, "Problematic BucketSort: " + msg.str());
        }
    }

    if (bs != nullptr) {
        delete bs;
        bs = nullptr;
    }

    msg.clear();
    msg.str("");
    msg << "Test Finished: ";
    if (testFlag != 0) msg << "Failed";
    else msg << "Passed";
    info("", msg.str());

    return testFlag;
} // add_5_to_size_2_test


int add_random_5_to_size_3_sort_test2() {
    stringstream msg;
    const string testName =
        "Add 5 Ramdom Elements into Size 3 Sorted Bucket List";
    int testFlag = -1;

    msg << "******** Test Name: " << testName;
    info("", msg.str());
    msg.clear();
    msg.str("");

    // test starts
    VectorBucketSort * bs = nullptr;
    try {
        bs = new VectorBucketSort(3);
        double * values = new double[5];
        for (int i = 0; i < 5; ++i) {
            values[i] = random_double(0, 1);
            bs->add(values[i]);
        }
        if (bs->size() != 3) {
            msg << "Failed. Size expected=2, actual=";
            msg << bs->size();
            throw runtime_error(msg.str());
        }

        bs->sortAll();
        info("", "Generated: " + array_to_string(values, 5));
        insertion_sort(values, 5);
        info("", "Sorted: " + array_to_string(values, 5));
        for (int i = 0; i < 5; ++i) {
            double item = bs->get2(i);
            if (true == isnan(item)) {
                msg << "Failed. Result from get2(" << i << ")=NAN";
                throw runtime_error(msg.str());
            }

            if (item - values[i] > threshold || item - values[i] < 0.0) {
                msg << "Failed. Result from get2(" << i << ") expected=";
                msg << setprecision(6) << values[i];
                msg << ", actual=" << setprecision(6) << item;
                throw runtime_error(msg.str());
            }
        }

        msg << *bs;
        info("", msg.str());
        testFlag = 0;
    } catch (exception& e) {
        error(__func__, e.what());
        testFlag = -1;
        if (bs != nullptr) {
            msg.clear();
            msg.str("");
            msg << *bs;
            error(__func__, "Problematic BucketSort: " + msg.str());
        }
    }

    if (bs != nullptr) {
        delete bs;
        bs = nullptr;
    }

    msg.clear();
    msg.str("");
    msg << "Test Finished: ";
    if (testFlag != 0) msg << "Failed";
    else msg << "Passed";
    info("", msg.str());

    return testFlag;
} // add_5_to_size_2_test


int add_random_20_to_size_10_test2() {
    stringstream msg;
    const string testName =
        "Add 20 Random Elements into Size 10 Unsorted Bucket List";
    int testFlag = -1;

    msg << "******** Test Name: " << testName;
    info("", msg.str());
    msg.clear();
    msg.str("");

    // test starts
    VectorBucketSort * bs = nullptr;
    try {
        bs = new VectorBucketSort();
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

        for (int i = 0; i < 20; ++i) {
            double item = bs->get2(i);
            if (true == isnan(item)) {
                msg << "Failed. Result from get2(" << i << ")=NAN";
                throw runtime_error(msg.str());
            }

            if (0 != in_array(item, values, 20)) {
                msg << "Failed. get2(" << i << ") = ";
                msg << setprecision(6) << item;
                msg << " does not exist in original values";
                throw runtime_error(msg.str());
            }
        }

        msg << *bs;
        info("", msg.str());
        testFlag = 0;
    } catch (exception& e) {
        error(__func__, e.what());
        testFlag = -1;
        if (bs != nullptr) {
            msg.clear();
            msg.str("");
            msg << *bs;
            error(__func__, "Problematic BucketSort: " + msg.str());
        }
    }

    if (bs != nullptr) {
        delete bs;
        bs = nullptr;
    }

    msg.clear();
    msg.str("");
    msg << "Test Finished: ";
    if (testFlag != 0) msg << "Failed";
    else msg << "Passed";
    info("", msg.str());

    return testFlag;
}


int add_random_20_to_size_10_sort_test2() {
    stringstream msg;
    const string testName =
        "Add 20 Random Elements into Size 10 Sorted Buckets List";
    int testFlag = -1;

    msg << "******** Test Name: " << testName;
    info("", msg.str());
    msg.clear();
    msg.str("");

    // test starts
    VectorBucketSort * bs = nullptr;
    try {
        bs = new VectorBucketSort();
        double * values = new double[20];
        for (int i = 0; i < 20; ++i) {
            values[i] = random_double(0, 1);
            bs->add(values[i]);
        }

        if (bs->size() != 10) {
            msg << "Failed. Size expected=2, actual=";
            msg << bs->size();
            throw runtime_error(msg.str());
        }

        bs->sortAll();
        info("", "Generated: " + array_to_string(values, 20));
        insertion_sort(values, 20);
        info("", "Sorted: " + array_to_string(values, 20));

        for (int i = 0; i < 20; ++i) {
            double item = bs->get2(i);
            if (true == isnan(item)) {
                msg << "Failed. Result from get2(" << i << ")=NAN";
                throw runtime_error(msg.str());
            }

            if (item - values[i] > threshold || item - values[i] < 0.0) {
                msg << "Failed. Result from get2(" << i << ") expected=";
                msg << setprecision(6) << values[i];
                msg << ", actual=" << setprecision(6) << item;
                throw runtime_error(msg.str());
            }
        }

        msg << *bs;
        info("", msg.str());
        testFlag = 0;
    } catch (exception& e) {
        error(__func__, e.what());
        testFlag = -1;
        if (bs != nullptr) {
            msg.clear();
            msg.str("");
            msg << *bs;
            error(__func__, "Problematic BucketSort: " + msg.str());
        }
    }

    if (bs != nullptr) {
        delete bs;
        bs = nullptr;
    }

    msg.clear();
    msg.str("");
    msg << "Test Finished: ";
    if (testFlag != 0) msg << "Failed";
    else msg << "Passed";
    info("", msg.str());

    return testFlag;
}

#endif // if defined(GRAD) && defined(EXTRA_CREDIT)
