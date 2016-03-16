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


#include <cstdlib>
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
#include "headers/unitTests.h"
#include "headers/logging.h"
#include "headers/maxSumSubarray.h"


using std::string;
using std::stringstream;
using std::setprecision;
using std::fixed;
using std::cout;
using std::endl;
using std::exit;


static void printUsage(const char * prog) {
    cout << "Usage: " << prog << " [OPTIONS]" << endl;
    cout << "Run all unit test cases for max-sub searching algorithms";
    cout << " with random integers filled." << endl;
    cout << endl;
    cout << "Options:" << endl;
    cout << "  -l           Set the screen log ouput level. The levels are:";
    cout << endl;
    cout << "                   debug, warn, error, info" << endl;
    cout << "               The default is warn if this argument is not specified.";
    cout << endl;
    cout << "  -h/--help    Print this usage information." << endl;
    cout << "E.g.:" << endl;
    cout << "  " << prog << " -l debug" << endl;
    cout << "  " << prog << endl;
    cout << endl;
}


int main(const int argc, const char * argv[]) {
    string arg;

    switch (argc) {
        case 0:
            setLoggingLevel(WARNING);
            break;
        case 3:
            arg = string(argv[1]);
            if (0 == arg.compare("-l")) {
                string lvl = string(argv[2]);
                if (0 == lvl.compare("debug"))
                    setLoggingLevel(DEBUG);
                else if (0 == lvl.compare("warn"))
                    setLoggingLevel(WARNING);
                else if (0 == lvl.compare("error"))
                    setLoggingLevel(ERROR);
                else if (0 == lvl.compare("info"))
                    setLoggingLevel(INFO);
                else {
                    printUsage(argv[0]);
                    exit(-1);
                }
            }
            if (0 == arg.compare("-h") || 0 == arg.compare("--help")) {
                printUsage(argv[0]);
                exit(-1);
            }
            break;
        default:
            printUsage(argv[0]);
            exit(-1);
    } // switch

    const string testSuite = "Test Suite: Max Subarray Search";
    stringstream msg;

    int passed, failed, total, rc;
    double passRatio;

    passed = failed = total = 0;

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

    rc = array_size_2_all_negative_test(bruteForce_n2);
    passed += (rc == 0) ? 1 : 0;
    failed += (rc == -1) ? 1 : 0;
    total++;

    rc = array_all_negative_test(bruteForce_n2);
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

    rc = array_size_2_all_negative_test(bruteForce_n3);
    passed += (rc == 0) ? 1 : 0;
    failed += (rc == -1) ? 1 : 0;
    total++;

    rc = array_all_negative_test(bruteForce_n3);
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

    rc = array_size_2_all_negative_test(find_maximum_subarray);
    passed += (rc == 0) ? 1 : 0;
    failed += (rc == -1) ? 1 : 0;
    total++;

    rc = array_all_negative_test(find_maximum_subarray);
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

    rc = array_size_2_all_negative_test(kadane);
    passed += (rc == 0) ? 1 : 0;
    failed += (rc == -1) ? 1 : 0;
    total++;

    rc = array_all_negative_test(kadane);
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
    info("", "");
    msg << "TOTAL CASES: " << total << ", ";
    msg << "PASSED: " << passed << ", ";
    msg << "FAILED: " << failed;
    info("", msg.str());
    msg.clear();
    msg.str("");

    msg << "PASS RATIO: " << setprecision(2) << fixed << passRatio << "%";
    info("", msg.str());
    info("", "**************************************");
} // main
