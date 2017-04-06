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
#include "headers/unittests_grad.h"

using std::exception;
using std::stringstream;
using std::endl;
using std::setprecision;
using std::runtime_error;
using std::invalid_argument;
using std::to_string;
using std::string;
using std::isnan;


#ifdef GRAD

int load_factor_random_in_random_size_test() {
    string msg = "Test Load Factor Computation for 30 Times with Random Values and Bucket Lists in Random Sizes.";
    msg = "******** Test Name: " + msg;
    info("", msg);
    int testFlag = -1;
    const int repeats = 30;

    VectorBucketSort *bs = nullptr;
    try {
        for (int i = 0; i < repeats; ++i) {
            // init data array in random size.
            const int dataSize = random_int(0, 50) + 1;
            const int bucketSize = random_int(0, 20) + 1;
            double *values = new double[dataSize];

            bs = new VectorBucketSort(bucketSize);
            for (int j = 0; j < dataSize; ++j) {
                values[j] = random_double(0, 1);
                bs->add(values[j]);
            }
            info("", "Generated: " + array_to_string(values, dataSize));
            // testing the load factors
            double expectedLoadFactor = (double) dataSize / bucketSize;
            double actualLoadFactor = bs->getLoadFactor();
            if (expectedLoadFactor - actualLoadFactor > threshold) {
                msg = "Failed. Load factor expected=" + to_string(expectedLoadFactor) + ", ";
                msg += "actual=" + to_string(actualLoadFactor) + "\n";
                msg += "Data size: " + to_string(dataSize) + ", Bucket List Size: " +
                       to_string(bucketSize);
                throw runtime_error(msg);
            }
            if (bs != nullptr) {
                delete bs;
                bs = nullptr;
            }
        }
        testFlag = 0;
    } catch (exception &e) {
        error(__func__, e.what());
        if (bs != nullptr) {
            stringstream buckets;
            buckets << *bs;
            error(__func__, "Problematic BucketSort: " + buckets.str());
        }
        testFlag = -1;
    }
    if (bs != nullptr) {
        delete bs;
        bs = nullptr;
    }
    info("", "Test Finished: " + (testFlag == 0) ? "Passed" : "Failed");
    return testFlag;
}

int add_random_invalid_values_load_factor_test() {
    string msg = "Test Load Factor after Adding 20 Random Elements in [1.0, 10.0)";
    int testFlag = -1;
    msg = "******** Test Name: " + msg;
    info("", msg);
    VectorBucketSort *bs = nullptr;
    try {
        bs = new VectorBucketSort();
        double *values = new double[20];
        int upperBound = random_int(1, 10);
        for (int i = 0; i < 20; ++i) {
            values[i] = random_double(1, upperBound);
            bs->add(values[i]);
        }
        if (bs->size() != 10) {
            msg = "Failed. Size expected=10, actual=";
            msg += to_string(bs->size());
            throw runtime_error(msg);
        }
        info("", "Generated: " + array_to_string(values, 20));

        double factor = bs->getLoadFactor();
        if (true == isnan(factor) || factor - 0.0 > threshold)
            throw runtime_error("Failed. Expected=0.0, actual=" + to_string(factor));

        stringstream buckets;
        buckets << *bs;
        info("", buckets.str());

        testFlag = 0;
    } catch (exception &e) {
        error(__func__, e.what());
        testFlag = -1;
        if (bs != nullptr) {
            stringstream buckets;
            buckets << *bs;
            error(__func__, "Problematic BucketSort: " + buckets.str());
        }
    }

    if (bs != nullptr) {
        delete bs;
        bs = nullptr;
    }

    info("", "Test Finished: " + (testFlag == 0) ? "Passed" : "Failed");
    return testFlag;
}

int chain_size_negative_index_test() {
    string msg = "Test Getting the Size of One Particular Chain in the Bucket List with a Negative Number.";
    msg = "******** Test Name: " + msg;
    info("", msg);
    int testFlag = -1;
    VectorBucketSort *bs = nullptr;
    try {
        bs = new VectorBucketSort();
        const int dataSize = random_int(0, 50) + 1;
        double *values = new double[dataSize];
        for (int j = 0; j < dataSize; ++j) {
            values[j] = random_double(0, 1);
            bs->add(values[j]);
        }
        info("", "Generated: " + array_to_string(values, dataSize));
        int index = random_int(-20, 0);
        int actualSize = bs->getCount(index);
        if (actualSize >= 0) {
            msg = "Failed. getCount(" + to_string(index) + ") result is expected < 0, ";
            msg += "actual=" + to_string(actualSize);
            throw runtime_error(msg);
        }
        testFlag = 0;
    } catch (exception &e) {
        error(__func__, e.what());
        if (bs != nullptr) {
            stringstream buckets;
            buckets << *bs;
            error(__func__, "Problematic BucketSort: " + buckets.str());
        }
        testFlag = -1;
    }
    info("", "Test Finished: " + (testFlag == 0) ? "Passed" : "Failed");
    return testFlag;
}

int chain_size_positive_invalid_index_test() {
    string msg = "Test Getting the Size of One Particular Chain with an Invalid Positive Number.";
    msg = "******** Test Name: " + msg;
    info("", msg);
    int testFlag = -1;
    VectorBucketSort *bs = nullptr;
    try {
        bs = new VectorBucketSort();
        const int dataSize = random_int(0, 50) + 1;
        double *values = new double[dataSize];
        for (int j = 0; j < dataSize; ++j) {
            values[j] = random_double(0, 1);
            bs->add(values[j]);
        }
        info("", "Generated: " + array_to_string(values, dataSize));
        int index = random_int(0, 20) + 51;
        int actualSize = bs->getCount(index);
        if (actualSize >= 0) {
            msg = "Failed. getCount(" + to_string(index) + ") result is expected < 0, ";
            msg += "actual=" + to_string(actualSize);
            throw runtime_error(msg);
        }
        testFlag = 0;
    } catch (exception &e) {
        error(__func__, e.what());
        if (bs != nullptr) {
            stringstream buckets;
            buckets << *bs;
            error(__func__, "Problematic BucketSort: " + buckets.str());
        }
        testFlag = -1;
    }
    info("", "Test Finished: " + (testFlag == 0) ? "Passed" : "Failed");
    return testFlag;
}

#endif
