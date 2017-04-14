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
#include "headers/unittests_grad_extra.h"

using std::exception;
using std::stringstream;
using std::endl;
using std::setprecision;
using std::runtime_error;
using std::invalid_argument;
using std::to_string;
using std::string;
using std::isnan;

#if defined(GRAD) && defined(EXTRA_CREDIT)

int get_random_in_random_size_test2() {
    string msg =
        "Get Value at Random Indices in [0, 50) out of 20 elements from Random Size in [5, 20) Bucket List";
    int testFlag = -1;
    msg = "******** Test Name: " + msg;
    info("", msg);
    VectorBucketSort * bs = nullptr;
    try {
        // set up a loop for random times [1, 50)
        int repeats = random_int(1, 50);
        info("", "Repeats for " + to_string(repeats) + " times.");
        int valueLength = 20;
        debug(__func__, "total value length=" + to_string(valueLength));
        for (int i = 0; i < repeats; ++i) {
            debug(__func__, "**** Repeat: " + to_string(i + 1));
            // init buckects: size = [5, 20)
            int bucketListSize = random_int(5, 20);
            debug(__func__, "bucket size=" + to_string(bucketListSize));
            bs = new VectorBucketSort(bucketListSize);
            if (bs->size() != bucketListSize) {
                msg = "Failed. Size expected=" + to_string(bucketListSize);
                msg += ", actual=" + to_string(bs->size());
                throw runtime_error(msg);
            }
            double * values = new double[valueLength];
            // add values
            for (int j = 0; j < valueLength; ++j) {
                values[j] = random_double(0, 1);
                debug(__func__,
                      "adding values[" + to_string(j) + "]=" +
                      to_string(values[j]));
                bs->add(values[j]);
            }
            debug("", "Generated: " + array_to_string(values, valueLength));
            stringstream buckets;
            buckets << *bs;
            debug("", "Generated Buckets:\n" + buckets.str());
            info("",
                 "Fetch elements at index in range [0, 50], some of the returns should be NAN");
            for (int j = 0; j < valueLength; ++j) {
                int random_index = random_int(0, 51);
                msg = "get2(" + to_string(random_index) + ")=";
                debug(__func__, msg);
                double item = bs->get2(random_index);
                if (true == isnan(item)) {
                    msg += "NAN";
                    debug(__func__, msg);
                    if (random_index < 20) {
                        msg = "Failed. Expected=" +
                              to_string(values[random_index]);
                        msg += ", actual=NAN";
                        throw runtime_error(msg);
                    }
                } else {
                    msg += to_string(item);
                    debug(__func__, msg);
                    if (random_index >= 20) {
                        msg = "Failed. Expected=NAN";
                        msg += ", actual=" + to_string(item);
                        throw runtime_error(msg);
                    }
                }
            }
            delete bs;
            bs = nullptr;
        }
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
    msg = (testFlag == 0)? "Passed": "Failed";
    info("", "Test Finished: " + msg);
    return testFlag;
}

int add_1_to_size_1_test2() {
    string msg = "Add 1 element into Size 1 Bucket List";
    int testFlag = -1;

    msg = "******** Test Name: " + msg;
    info("", msg);
    VectorBucketSort * bs = nullptr;
    try {
        bs = new VectorBucketSort(1);
        const double tmp = 0.30;
        debug(__func__,
              "adding values[0]=" +
              to_string(tmp));
        bs->add(tmp);
        stringstream buckets;
        buckets << *bs;
        debug("", "Generated Buckets:\n" + buckets.str());
        if (bs->size() != 1) {
            msg = "Failed. Size expected=1, actual=";
            msg += to_string(bs->size());
            throw runtime_error(msg);
        }
        debug(__func__, "get2(0)=");
        double item = bs->get2(0);
        debug(__func__, "get2(0)=" + to_string(item));
        if (true == isnan(item)) {
            msg = "Failed. Result from get2(0) expected=";
            msg += to_string(tmp);
            msg += ", actual=NAN";
            throw runtime_error(msg);
        }
        if (item - tmp > threshold) {
            msg = "Failed. Result from get2(0) expected=";
            msg += to_string(tmp);
            msg += ", actual=" + to_string(item);
            throw runtime_error(msg);
        }
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
    msg = (testFlag == 0)? "Passed": "Failed";
    info("", "Test Finished: " + msg);
    return testFlag;
}

int add_same_5_to_size_1_test2() {
    string msg = "Add 5 Same elements into Size 1 Bucket List";
    msg = "******** Test Name: " + msg;
    int testFlag = -1;
    info("", msg);
    // test starts
    VectorBucketSort * bs = nullptr;
    try {
        bs = new VectorBucketSort(1);
        if (bs->size() != 1) {
            msg = "Failed. Size expected=1, actual=";
            msg += to_string(bs->size());
            throw runtime_error(msg);
        }
        // add the values
        for (int i = 0; i < 5; ++i) {
            debug(__func__,
                  "adding values[" + to_string(i) + "]=" +
                  to_string(0.10));
            bs->add(0.10);
        }
        stringstream buckets;
        buckets << *bs;
        debug("", "Generated Buckets:\n" + buckets.str());
        // test get2(i)
        for (int i = 0; i < 5; ++i) {
            debug(__func__, "get2(" + to_string(i) + ")=");
            double item = bs->get2(i);
            debug(__func__, "get2(" + to_string(i) + ")=" + to_string(item));
            if (true == isnan(item) || item - 0.10 > threshold ||
                item - 0.10 < 0.0) {
                msg = "Failed. Result from get2(" + to_string(i) +
                      ") expected=0.10";
                msg += ", actual=" + to_string(item);
                throw runtime_error(msg);
            }
        }
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
    msg = (testFlag == 0)? "Passed": "Failed";
    info("", "Test Finished: " + msg);
    return testFlag;
}

int add_random_5_to_size_2_sort_test2() {
    string msg = "Add 5 Random Elements into Size 2 Sorted Bucket List";
    msg = "******** Test Name: " + msg;
    info("", msg);
    int testFlag = -1;
    // test starts
    VectorBucketSort * bs = nullptr;
    try {
        bs = new VectorBucketSort(2);
        if (bs->size() != 2) {
            msg = "Failed. Size expected=2, actual=";
            msg += to_string(bs->size());
            throw runtime_error(msg);
        }
        double * values = new double[5];
        for (int i = 0; i < 5; ++i) {
            values[i] = random_double(0, 1);
            debug(__func__,
                  "adding values[" + to_string(i) + "]=" +
                  to_string(values[i]));
            bs->add(values[i]);
        }
        debug("", "Generated: " + array_to_string(values, 5));
        stringstream buckets;
        buckets << *bs;
        debug("", "Generated Buckets:\n" + buckets.str());
        insertion_sort(values, 5);
        debug("", "Sorted: " + array_to_string(values, 5));
        bs->sortAll();
        buckets.clear();
        buckets << *bs;
        debug("", "Sorted Buckets:\n" + buckets.str());
        // test get2(i) == values[i]
        for (int i = 0; i < 5; ++i) {
            debug(__func__, "get2(" + to_string(i) + ")=");
            double item = bs->get2(i);
            debug(__func__, "get2(" + to_string(i) + ")=" + to_string(item));
            if (true == isnan(item) || item - values[i] > threshold ||
                item - values[i] < 0.0) {
                msg = "Failed. Result from get2(" + to_string(i) +
                      ") expected=";
                msg += to_string(values[i]);
                msg += ", actual=" + to_string(item);
                throw runtime_error(msg);
            }
        }
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
    msg = (testFlag == 0)? "Passed": "Failed";
    info("", "Test Finished: " + msg);
    return testFlag;
}

int add_random_5_to_size_3_sort_test2() {
    string msg = "Add 5 Ramdom Elements into Size 3 Sorted Bucket List";
    msg = "******** Test Name: " + msg;
    info("", msg);
    int testFlag = -1;
    // test starts
    VectorBucketSort * bs = nullptr;
    try {
        bs = new VectorBucketSort(3);
        if (bs->size() != 3) {
            msg = "Failed. Size expected=3, actual=";
            msg += to_string(bs->size());
            throw runtime_error(msg);
        }
        double * values = new double[5];
        for (int i = 0; i < 5; ++i) {
            values[i] = random_double(0, 1);
            debug(__func__,
                  "adding values[" + to_string(i) + "]=" +
                  to_string(values[i]));
            bs->add(values[i]);
        }
        debug("", "Generated: " + array_to_string(values, 5));
        stringstream buckets;
        buckets << *bs;
        debug("", "Generated Buckets:\n" + buckets.str());
        insertion_sort(values, 5);
        debug("", "Sorted: " + array_to_string(values, 5));
        bs->sortAll();
        buckets.clear();
        buckets << *bs;
        debug("", "Sorted Buckets:\n" + buckets.str());
        // test get2(i) == values[i]
        for (int i = 0; i < 5; ++i) {
            debug(__func__, "get2(" + to_string(i) + ")=");
            double item = bs->get2(i);
            debug(__func__, "get2(" + to_string(i) + ")=" + to_string(item));
            if (true == isnan(item) || item - values[i] > threshold ||
                item - values[i] < 0.0) {
                msg = "Failed. Result from get2(" + to_string(i) +
                      ") expected=";
                msg += to_string(values[i]);
                msg += ", actual=" + to_string(item);
                throw runtime_error(msg);
            }
        }
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
    msg = (testFlag == 0)? "Passed": "Failed";
    info("", "Test Finished: " + msg);
    return testFlag;
}

int add_random_20_to_size_10_test2() {
    string msg = "Add 20 Random Elements into Size 10 Unsorted Bucket List";
    msg = "******** Test Name: " + msg;
    info("", msg);
    int testFlag = -1;
    // test starts
    VectorBucketSort * bs = nullptr;
    try {
        bs = new VectorBucketSort();
        if (bs->size() != 10) {
            msg = "Failed. Size expected=10, actual=";
            msg += to_string(bs->size());
            throw runtime_error(msg);
        }
        double * values = new double[20];
        for (int i = 0; i < 20; ++i) {
            values[i] = random_double(0, 1);
            debug(__func__,
                  "adding values[" + to_string(i) + "]=" +
                  to_string(values[i]));
            bs->add(values[i]);
        }
        debug("", "Generated: " + array_to_string(values, 20));
        stringstream buckets;
        buckets << *bs;
        debug("", "Generated Buckets:\n" + buckets.str());

        for (int i = 0; i < 20; ++i) {
            debug(__func__, "get2(" + to_string(i) + ")=");
            double item = bs->get2(i);
            debug(__func__, "get2(" + to_string(i) + ")=" + to_string(item));
            if (true == isnan(item)) {
                msg = "Failed. Result from get2(" + to_string(i) +
                      ") expected=";
                msg += to_string(values[i]);
                msg += ", actual=NAN";
                throw runtime_error(msg);
            }
            if (0 != in_array(item, values, 20)) {
                msg = "Failed. Result from get2(" + to_string(i) + ")=";
                msg += to_string(item);
                msg += " does not exist in original values";
                throw runtime_error(msg);
            }
        }
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
    msg = (testFlag == 0)? "Passed": "Failed";
    info("", "Test Finished: " + msg);
    return testFlag;
}

int add_random_20_to_size_10_sort_test2() {
    string msg = "Add 20 Random Elements into Size 10 Sorted Buckets List";
    msg = "******** Test Name: " + msg;
    info("", msg);
    int testFlag = -1;
    // test starts
    VectorBucketSort * bs = nullptr;
    try {
        bs = new VectorBucketSort();
        if (bs->size() != 10) {
            msg = "Failed. Size expected=10, actual=";
            msg += to_string(bs->size());
            throw runtime_error(msg);
        }
        double * values = new double[20];
        for (int i = 0; i < 20; ++i) {
            values[i] = random_double(0, 1);
            debug(__func__,
                  "adding values[" + to_string(i) + "]=" +
                  to_string(values[i]));
            bs->add(values[i]);
        }
        debug("", "Generated: " + array_to_string(values, 20));
        stringstream buckets;
        buckets << *bs;
        debug("", "Generated Buckets:\n" + buckets.str());
        insertion_sort(values, 20);
        debug("", "Sorted: " + array_to_string(values, 20));
        bs->sortAll();
        buckets.clear();
        buckets << *bs;
        debug("", "Sorted Buckets:\n" + buckets.str());
        for (int i = 0; i < 20; ++i) {
            debug(__func__, "get2(" + to_string(i) + ")=");
            double item = bs->get2(i);
            debug(__func__, "get2(" + to_string(i) + ")=" + to_string(item));
            if (true == isnan(item) || item - values[i] > threshold ||
                item - values[i] < 0.0) {
                msg = "Failed. Result from get2(" + to_string(i) +
                      ") expected=";
                msg += to_string(values[i]);
                msg += ", actual=" + to_string(item);
                throw runtime_error(msg);
            }
        }
        testFlag = 0;
    } catch (exception &e) {
        error(__func__, e.what());
        testFlag = -1;
        if (bs != nullptr) {
            stringstream buckets;
            buckets << *bs;
            error(__func__, "Problematic BucketSort: " + msg);
        }
    }

    if (bs != nullptr) {
        delete bs;
        bs = nullptr;
    }
    msg = (testFlag == 0)? "Passed": "Failed";
    info("", "Test Finished: " + msg);
    return testFlag;
}

int add_random_positive_invalid_values2() {
    string msg =
        "Add 20 Random Elements in [1.0, 10.0) into Size 10 Buckets List";
    int testFlag = -1;
    msg = "******** Test Name: " + msg;
    info("", msg);
    VectorBucketSort * bs = nullptr;
    try {
        bs = new VectorBucketSort();
        double * values = new double[20];
        int upperBound = random_int(1, 10);
        for (int i = 0; i < 20; ++i) {
            values[i] = random_double(1, upperBound);
            debug(__func__,
                  "adding values[" + to_string(i) + "]=" +
                  to_string(values[i]));
            bs->add(values[i]);
        }
        if (bs->size() != 10) {
            msg = "Failed. Size expected=10, actual=";
            msg += to_string(bs->size());
            throw runtime_error(msg);
        }
        debug("", "Generated: " + array_to_string(values, 20));
        stringstream buckets;
        buckets << *bs;
        debug("", "Generated Buckets:\n" + buckets.str());
        for (int i = 0; i < 20; ++i) {
            debug(__func__, "get2(" + to_string(i) + ")=");
            double item = bs->get2(i);
            debug(__func__, "get2(" + to_string(i) + ")=" + to_string(item));
            if (false == isnan(item))
                throw runtime_error(
                          "Failed. get2(" + to_string(i) + ") = " +
                          to_string(item) + ", is not NAN");
        }
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
    msg = (testFlag == 0)? "Passed": "Failed";
    info("", "Test Finished: " + msg);
    return testFlag;
}

#endif // if defined(GRAD) && defined(EXTRA_CREDIT)
