// -----------------------------------------------------------------------------
// Filename:    unittestsuite.cpp
// Revision:    $Id$
// Description: this file contains the unit test runner method.
// Created:     04/08/2016 03:20:29 PM
// Compiler:    G++
// Author:      Jason Meng (jm), jm652564@sju.edu
//
// Copyright (c) 2016 by Jason Meng, no rights reserved.
// -----------------------------------------------------------------------------

// C headers
#include <cstdlib>
// C++ headers
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
// homebrew
#include "headers/unittests.h"
#ifdef GRAD
#include "headers/unittests_grad.h"
#endif
#ifdef EXTRA_CREDIT
#include "headers/unittests_grad_extra.h"
#endif
#include "headers/logging.h"


using std::string;
using std::stringstream;
using std::setprecision;
using std::fixed;
using std::cout;
using std::endl;
using std::exit;


static void printUsage(const char * prog) {
    cout << "Usage: " << prog << " [OPTIONS]" << endl;
    cout << "Run all unit test cases for bucket sort" << endl;
    cout << endl;
    cout << "Options:" << endl;
    cout << "  -l           Set the screen log ouput level. The levels are:";
    cout << endl;
    cout << "                   debug, warn, error, info" << endl;
    cout <<
        "               The default is warn if this argument is not specified.";
    cout << endl;
    cout << "  -h/--help    Print this usage information." << endl;
    cout << "E.g.:" << endl;
    cout << "  " << prog << " -l debug" << endl;
    cout << "  " << prog << endl;
    cout << endl;
}

static void prepare(const int argc, const char * argv[]) {
    string arg;

    setLoggingLevel(WARNING);

    if (argc == 1)
        return;

    if (argc < 3) {
        printUsage(argv[0]);
        exit(-1);
    }

    arg = string(argv[1]);
    if (0 == arg.compare("-h") || 0 == arg.compare("--help")) {
        printUsage(argv[0]);
        exit(0);
    }

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
} // prepare

static double testsuite(int &passed, int &failed, int &total) {
    const string testSuite = "Test Suite: Vector Bucket Sort";
    stringstream msg;

    int rc;
    double passRatio;

    passed = failed = total = 0;

    info("", "************* " + testSuite + " *************");
    info("", "");
    rc = default_initialization_disposal_test();
    passed += (rc == 0)? 1: 0;
    failed += (rc == -1)? 1: 0;
    total++;

    info("", "");
    rc = initialization_disposal_test();
    passed += (rc == 0)? 1: 0;
    failed += (rc == -1)? 1: 0;
    total++;

    info("", "");
    rc = get_random_in_random_size_test();
    passed += (rc == 0)? 1: 0;
    failed += (rc == -1)? 1: 0;
    total++;

    info("", "");
    rc = add_1_to_size_1_test();
    passed += (rc == 0)? 1: 0;
    failed += (rc == -1)? 1: 0;
    total++;

    info("", "");
    rc = add_same_5_to_size_1_test();
    passed += (rc == 0)? 1: 0;
    failed += (rc == -1)? 1: 0;
    total++;

    info("", "");
    rc = add_random_5_to_size_2_sort_test();
    passed += (rc == 0)? 1: 0;
    failed += (rc == -1)? 1: 0;
    total++;

    info("", "");
    rc = add_random_5_to_size_3_sort_test();
    passed += (rc == 0)? 1: 0;
    failed += (rc == -1)? 1: 0;
    total++;

    info("", "");
    rc = add_random_20_to_size_10_test();
    passed += (rc == 0)? 1: 0;
    failed += (rc == -1)? 1: 0;
    total++;

    info("", "");
    rc = add_random_20_to_size_10_sort_test();
    passed += (rc == 0)? 1: 0;
    failed += (rc == -1)? 1: 0;
    total++;

    info("", "");
    rc = add_random_positive_invalid_values();
    passed += (rc == 0)? 1: 0;
    failed += (rc == -1)? 1: 0;
    total++;

    info("", "");
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

    return passRatio;
} // testsuite1

#ifdef GRAD
static double testsuite_grad(int& passed, int& failed, int& total) {
    const string testSuite = "Test Suite for GRAD: Vector Bucket Sort";
    stringstream msg;

    int rc;
    double passRatio;

    passed = failed = total = 0;

    info("", "************* " + testSuite + " *************");
    info("", "");
    rc      = load_factor_random_in_random_size_test();
    passed += (rc == 0)? 1: 0;
    failed += (rc == -1)? 1: 0;
    total++;

    info("", "");
    rc      = add_random_invalid_values_load_factor_test();
    passed += (rc == 0)? 1: 0;
    failed += (rc == -1)? 1: 0;
    total++;

    info("", "");
    rc      = chain_size_negative_index_test();
    passed += (rc == 0)? 1: 0;
    failed += (rc == -1)? 1: 0;
    total++;

    info("", "");
    rc      = chain_size_positive_invalid_index_test();
    passed += (rc == 0)? 1: 0;
    failed += (rc == -1)? 1: 0;
    total++;

    info("", "");
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

    return passRatio;
}
#endif

#ifdef EXTRA_CREDIT
static double testsuite_grad_extra(int& passed, int& failed, int& total) {
    const string testSuite =
        "Test Suite for GRAD with Extra Credit: Vector Bucket Sort";
    stringstream msg;

    int rc;
    double passRatio;

    passed = failed = total = 0;

    info("", "************* " + testSuite + " *************");
    info("", "");
    rc      = get_random_in_random_size_test2();
    passed += (rc == 0)? 1: 0;
    failed += (rc == -1)? 1: 0;
    total++;

    info("", "");
    rc      = add_1_to_size_1_test2();
    passed += (rc == 0)? 1: 0;
    failed += (rc == -1)? 1: 0;
    total++;

    info("", "");
    rc      = add_same_5_to_size_1_test2();
    passed += (rc == 0)? 1: 0;
    failed += (rc == -1)? 1: 0;
    total++;

    info("", "");
    rc      = add_random_5_to_size_2_sort_test2();
    passed += (rc == 0)? 1: 0;
    failed += (rc == -1)? 1: 0;
    total++;

    info("", "");
    rc      = add_random_5_to_size_3_sort_test2();
    passed += (rc == 0)? 1: 0;
    failed += (rc == -1)? 1: 0;
    total++;

    info("", "");
    rc      = add_random_20_to_size_10_test2();
    passed += (rc == 0)? 1: 0;
    failed += (rc == -1)? 1: 0;
    total++;

    info("", "");
    rc      = add_random_20_to_size_10_sort_test2();
    passed += (rc == 0)? 1: 0;
    failed += (rc == -1)? 1: 0;
    total++;

    info("", "");
    rc      = add_random_positive_invalid_values2();
    passed += (rc == 0)? 1: 0;
    failed += (rc == -1)? 1: 0;
    total++;

    info("", "");
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

    return passRatio;
} // testsuite2
#endif // if defined(GRAD) && defined(EXTRA_CREDIT)

int main(const int argc, const char * argv[]) {
    prepare(argc, argv);

    int passed, failed, total;
    stringstream msg;

    testsuite(passed, failed, total);

#ifdef GRAD
    int passed2, failed2, total2;
    testsuite_grad(passed2, failed2, total2);
    total += total2;
    passed += passed2;
    failed += failed2;
#endif

#ifdef EXTRA_CREDIT
    int passed3, failed3, total3;
    testsuite_grad_extra(passed3, failed3, total3);
    total += total3;
    passed += passed3;
    failed += failed3;
#endif

    info("", "");
    info("", "");
    info("", "");
    // statistic data output
    double passRatio = (double)passed / total * 100;
    info("", "");
    msg << "OVERALL TOTAL CASES: " << total << ", ";
    msg << "OVERALL PASSED: " << passed << ", ";
    msg << "OVERALL FAILED: " << failed;
    info("", msg.str());
    msg.clear();
    msg.str("");

    msg << "PASS RATIO: " << setprecision(2) << fixed << passRatio << "%";
    info("", msg.str());
    info("", "**************************************");

    exit(0);
} // main
