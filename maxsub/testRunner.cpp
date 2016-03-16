// -----------------------------------------------------------------------------
// Filename:    testRunner.cpp
// Revision:    $Id$
// Description: This file includes the unit test runner.
// Created:     03/15/2016 01:20:29 PM
// Compiler:    G++
// Author:      Jason Meng (jm), jm652564@sju.edu
//
// Copyright (c) 2016 by Jason Meng, no rights reserved.
// -----------------------------------------------------------------------------


#include <string>
#include <sstream>
#include <iomanip>
#include "headers/unitTests.h"
#include "headers/logging.h"
#include "headers/maxSumSubarray.h"


using std::string;
using std::stringstream;
using std::setprecision;
using std::fixed;


int main(const int argc, const char * argv[]) {

    const string testSuite = "Test Suite: Max Subarray Search";
    stringstream msg;

    int passed, failed, total, rc;
    double passRatio;

    passed = failed = total = 0;

    setLoggingLevel(WARNING);

    info("", "************* " + testSuite + " *************");

    // tests against bruteForce_n2
    info("", "::::::::: Tests on bruteForce_n2 :::::::::");
    rc = array_null_test(bruteForce_n2);
    passed += (rc == 0) ? 1 : 0;
    failed += (rc == -1) ? 1 : 0;
    total++;

    rc = array_size_1_test(bruteForce_n2);
    passed += (rc == 0) ? 1 : 0;
    failed += (rc == -1) ? 1 : 0;
    total++;

    rc = array_size_2_all_positive_test(bruteForce_n2);
    passed += (rc == 0) ? 1 : 0;
    failed += (rc == -1) ? 1 : 0;
    total++;

    rc = array_size_2_1_pos_1_neg_test(bruteForce_n2);
    passed += (rc == 0) ? 1 : 0;
    failed += (rc == -1) ? 1 : 0;
    total++;

    rc = array_size_2_1_neg_1_pos_test(bruteForce_n2);
    passed += (rc == 0) ? 1 : 0;
    failed += (rc == -1) ? 1 : 0;
    total++;

    rc = array_self_max_test(bruteForce_n2);
    passed += (rc == 0) ? 1 : 0;
    failed += (rc == -1) ? 1 : 0;
    total++;

    rc = array_max_1st_half_test(bruteForce_n2);
    passed += (rc == 0) ? 1 : 0;
    failed += (rc == -1) ? 1 : 0;
    total++;

    rc = array_max_2nd_half_test(bruteForce_n2);
    passed += (rc == 0) ? 1 : 0;
    failed += (rc == -1) ? 1 : 0;
    total++;

    rc = array_max_mid_test(bruteForce_n2);
    passed += (rc == 0) ? 1 : 0;
    failed += (rc == -1) ? 1 : 0;
    total++;

    rc = array_max_mid_left_leaning_test(bruteForce_n2);
    passed += (rc == 0) ? 1 : 0;
    failed += (rc == -1) ? 1 : 0;
    total++;

    rc = array_max_mid_right_leaning_test(bruteForce_n2);
    passed += (rc == 0) ? 1 : 0;
    failed += (rc == -1) ? 1 : 0;
    total++;


    // tests against bruteForce_n2
    info("", "::::::::: Tests on bruteForce_n3 :::::::::");
    rc = array_null_test(bruteForce_n3);
    passed += (rc == 0) ? 1 : 0;
    failed += (rc == -1) ? 1 : 0;
    total++;

    rc = array_size_1_test(bruteForce_n3);
    passed += (rc == 0) ? 1 : 0;
    failed += (rc == -1) ? 1 : 0;
    total++;

    rc = array_size_2_all_positive_test(bruteForce_n3);
    passed += (rc == 0) ? 1 : 0;
    failed += (rc == -1) ? 1 : 0;
    total++;

    rc = array_size_2_1_pos_1_neg_test(bruteForce_n3);
    passed += (rc == 0) ? 1 : 0;
    failed += (rc == -1) ? 1 : 0;
    total++;

    rc = array_size_2_1_neg_1_pos_test(bruteForce_n3);
    passed += (rc == 0) ? 1 : 0;
    failed += (rc == -1) ? 1 : 0;
    total++;

    rc = array_self_max_test(bruteForce_n3);
    passed += (rc == 0) ? 1 : 0;
    failed += (rc == -1) ? 1 : 0;
    total++;

    rc = array_max_1st_half_test(bruteForce_n3);
    passed += (rc == 0) ? 1 : 0;
    failed += (rc == -1) ? 1 : 0;
    total++;

    rc = array_max_2nd_half_test(bruteForce_n3);
    passed += (rc == 0) ? 1 : 0;
    failed += (rc == -1) ? 1 : 0;
    total++;

    rc = array_max_mid_test(bruteForce_n3);
    passed += (rc == 0) ? 1 : 0;
    failed += (rc == -1) ? 1 : 0;
    total++;

    rc = array_max_mid_left_leaning_test(bruteForce_n3);
    passed += (rc == 0) ? 1 : 0;
    failed += (rc == -1) ? 1 : 0;
    total++;

    rc = array_max_mid_right_leaning_test(bruteForce_n3);
    passed += (rc == 0) ? 1 : 0;
    failed += (rc == -1) ? 1 : 0;
    total++;

    // tests against bruteForce_n2
    info("", "::::::::: Tests on recursive :::::::::");
    rc = array_null_test(find_maximum_subarray);
    passed += (rc == 0) ? 1 : 0;
    failed += (rc == -1) ? 1 : 0;
    total++;

    rc = array_size_1_test(find_maximum_subarray);
    passed += (rc == 0) ? 1 : 0;
    failed += (rc == -1) ? 1 : 0;
    total++;

    rc = array_size_2_all_positive_test(find_maximum_subarray);
    passed += (rc == 0) ? 1 : 0;
    failed += (rc == -1) ? 1 : 0;
    total++;

    rc = array_size_2_1_pos_1_neg_test(find_maximum_subarray);
    passed += (rc == 0) ? 1 : 0;
    failed += (rc == -1) ? 1 : 0;
    total++;

    rc = array_size_2_1_neg_1_pos_test(find_maximum_subarray);
    passed += (rc == 0) ? 1 : 0;
    failed += (rc == -1) ? 1 : 0;
    total++;

    rc = array_self_max_test(find_maximum_subarray);
    passed += (rc == 0) ? 1 : 0;
    failed += (rc == -1) ? 1 : 0;
    total++;

    rc = array_max_1st_half_test(find_maximum_subarray);
    passed += (rc == 0) ? 1 : 0;
    failed += (rc == -1) ? 1 : 0;
    total++;

    rc = array_max_2nd_half_test(find_maximum_subarray);
    passed += (rc == 0) ? 1 : 0;
    failed += (rc == -1) ? 1 : 0;
    total++;

    rc = array_max_mid_test(find_maximum_subarray);
    passed += (rc == 0) ? 1 : 0;
    failed += (rc == -1) ? 1 : 0;
    total++;

    rc = array_max_mid_left_leaning_test(find_maximum_subarray);
    passed += (rc == 0) ? 1 : 0;
    failed += (rc == -1) ? 1 : 0;
    total++;

    rc = array_max_mid_right_leaning_test(find_maximum_subarray);
    passed += (rc == 0) ? 1 : 0;
    failed += (rc == -1) ? 1 : 0;
    total++;

    // tests against bruteForce_n2
    info("", "::::::::: Tests on Kadane :::::::::");
    rc = array_null_test(kadane);
    passed += (rc == 0) ? 1 : 0;
    failed += (rc == -1) ? 1 : 0;
    total++;

    rc = array_size_1_test(kadane);
    passed += (rc == 0) ? 1 : 0;
    failed += (rc == -1) ? 1 : 0;
    total++;

    rc = array_size_2_all_positive_test(kadane);
    passed += (rc == 0) ? 1 : 0;
    failed += (rc == -1) ? 1 : 0;
    total++;

    rc = array_size_2_1_pos_1_neg_test(kadane);
    passed += (rc == 0) ? 1 : 0;
    failed += (rc == -1) ? 1 : 0;
    total++;

    rc = array_size_2_1_neg_1_pos_test(kadane);
    passed += (rc == 0) ? 1 : 0;
    failed += (rc == -1) ? 1 : 0;
    total++;

    rc = array_self_max_test(kadane);
    passed += (rc == 0) ? 1 : 0;
    failed += (rc == -1) ? 1 : 0;
    total++;

    rc = array_max_1st_half_test(kadane);
    passed += (rc == 0) ? 1 : 0;
    failed += (rc == -1) ? 1 : 0;
    total++;

    rc = array_max_2nd_half_test(kadane);
    passed += (rc == 0) ? 1 : 0;
    failed += (rc == -1) ? 1 : 0;
    total++;

    rc = array_max_mid_test(kadane);
    passed += (rc == 0) ? 1 : 0;
    failed += (rc == -1) ? 1 : 0;
    total++;

    rc = array_max_mid_left_leaning_test(kadane);
    passed += (rc == 0) ? 1 : 0;
    failed += (rc == -1) ? 1 : 0;
    total++;

    rc = array_max_mid_right_leaning_test(kadane);
    passed += (rc == 0) ? 1 : 0;
    failed += (rc == -1) ? 1 : 0;
    total++;

    // statistic data output
    passRatio = (double)passed / total * 100;
    msg << " TOTAL CASES: " << total << ", ";
    msg << "PASSED: " << passed << ", ";
    msg << "FAILED: " << failed;
    info(__func__, msg.str());
    msg.clear();
    msg.str("");

    msg << "PASS RATIO: " << setprecision(2) << fixed << passRatio << "%";
    info("", msg.str());
    info("", "**************************************");
} // main
