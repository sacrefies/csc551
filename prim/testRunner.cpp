//
// Created by Jason on 5/8/2017.
//

// c++ headers
#include <string>
#include <iostream>
// homemade headers
#include "headers/unittest.h"
#include "headers/logging.h"

using std::cout;
using std::endl;
using std::flush;
using std::string;
using std::to_string;

/// Print out the usage of this program to the stdout.
/// \param prog The name of this program.
static void printUsage(const char *prog) {
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

/// Prepare and parse the command line arguments
/// \param argc The count of the arguments.
/// \param argv The command line arguments.
static void prepare(const int argc, const char *argv[]) {
    setLoggingLevel(WARNING);
    if (argc == 1) return;
    if (argc < 3) {
        printUsage(argv[0]);
        exit(-1);
    }

    string arg = string(argv[1]);
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
}

/// The testsuite.
/// \param dataDir The path of the directory where the data files reside, relative or absolute.
static void testsuite(const string dataDir) {
    const string testSuite = "Test Suite: prim Test Suite";
    string msg = "";
    int passed, failed, total;
    double passRatio;
    bool rc;
    passed = failed = total = 0;

    info("", "************* " + testSuite + " *************");
    info("", "");
    string fileName = "tinyEWG.txt";
    string filePath = dataDir + "/" + fileName;
    double expected = 1.81;
    rc = test_file_prim(filePath, expected);
    passed += (rc == true) ? 1 : 0;
    failed += (rc == false) ? 1 : 0;
    total++;

    fileName = "mediumEWG.txt";
    filePath = dataDir + "/" + fileName;
    expected = 10.4635;
    rc = test_file_prim(filePath, expected);
    passed += (rc == true) ? 1 : 0;
    failed += (rc == false) ? 1 : 0;
    total++;

    fileName = "1000EWG.txt";
    filePath = dataDir + "/" + fileName;
    expected = 20.7732;
    rc = test_file_prim(filePath, expected);
    passed += (rc == true) ? 1 : 0;
    failed += (rc == false) ? 1 : 0;
    total++;

    fileName = "10000EWG.txt";
    filePath = dataDir + "/" + fileName;
    expected = 65.2407;
    rc = test_file_prim(filePath, expected);
    passed += (rc == true) ? 1 : 0;
    failed += (rc == false) ? 1 : 0;
    total++;

    fileName = "test1.txt";
    filePath = dataDir + "/" + fileName;
    expected = 19.;
    rc = test_file_prim(filePath, expected);
    passed += (rc == true) ? 1 : 0;
    failed += (rc == false) ? 1 : 0;
    total++;

    fileName = "test2.txt";
    filePath = dataDir + "/" + fileName;
    expected = 37.;
    rc = test_file_prim(filePath, expected);
    passed += (rc == true) ? 1 : 0;
    failed += (rc == false) ? 1 : 0;
    total++;

    fileName = "test3.txt";
    filePath = dataDir + "/" + fileName;
    expected = 18.;
    rc = test_file_prim(filePath, expected);
    passed += (rc == true) ? 1 : 0;
    failed += (rc == false) ? 1 : 0;
    total++;

    fileName = "test4.txt";
    filePath = dataDir + "/" + fileName;
    expected = 37.;
    rc = test_file_prim(filePath, expected);
    passed += (rc == true) ? 1 : 0;
    failed += (rc == false) ? 1 : 0;
    total++;

    info("", "");
    // statistic data output
    passRatio = (double) passed / total * 100;
    msg = "TOTAL CASES: " + to_string(total) + ", ";
    msg += "PASSED: " + to_string(passed) + ", ";
    msg += "FAILED: " + to_string(failed);
    info("", msg);
    info("", "PASS RATIO: " + to_string(passRatio) + "%");
    info("", "**************************************");
}

int main(const int argc, const char *argv[]) {
    prepare(argc, argv);
    testsuite("test_data");
    exit(0);
}
