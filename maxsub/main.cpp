// ------------------------------------------------------------------------------------
//       Filename: main.cpp
//       Revision: $Id$
//    Description: This file contains the main program execution entrance.
//        Created: 02/15/2016 01:15:59 PM
//       Compiler: G++
//         Author: Jason Meng (jm), jm652564@sju.edu
//
// Copyright (c) 2016 by Jason Meng, no rights reserved.
// ------------------------------------------------------------------------------------


// C includes
#include <cstring>
#include <cstdlib>
// C++ includes
#include <iostream>
#include <sstream>
#include <exception>
#include <string>
#include <stdexcept>
#include <unistd.h>
// custom includess
#include "headers/maxSumSubarray.h"
#include "headers/logging.h"
#include "headers/arrayUtils.h"


#define SLEEP_TIME 1


using std::stringstream;
using std::exception;
using std::strncmp;
using std::strlen;
using std::atoi;
using std::exit;
using std::runtime_error;
using std::cout;
using std::endl;


/**
 * A runner function to run the algorithms. This function generates numOfArrays
 * arrays whose sizes are from 1 to 10 with random integers as their elements.
 *
 * @param numOfArrays   An integer to specify how many arrays to be generated.
 * @param func          A function which implements an algorithm to find the
 *                      max-sum subarray. This function must satify the
 *                      standard signature:
 *                      void func_name(int[] array, int size, int& bestStart,
 *                                     int& bestEnd, int& bestSum)
 */
static void max_sub_random_runner(int numOfArrays, string funcName,
                                  void (* func)(int[], int, int&, int&, int&)) {
    int bestStart = -1,
        bestEnd = -1,
        bestSum = 0;
    // for generating random array sizes.
    int sizeSeed;
    // to store the generated arrays
    int ** array = new int *[numOfArrays];
    int * sizes = new int[numOfArrays];

    stringstream msg;

    msg << "******************* MAX-SUB Runner: " << numOfArrays;
    msg << " Arrays to Run *******************";
    info(__func__, msg.str());
    msg.clear();
    msg.str("");
    msg << ":::::::: Function: " << funcName;
    info(__func__, msg.str());
    msg.clear();
    msg.str("");

    // set the sizes for the arrays to feed to the maxsub functions
    debug(__func__, "Generating array sizes");
    debug(__func__, "Program sleeps 1 sec for each seed generation.");
    for (int i = 0; i < numOfArrays; ++i) {
        // gen random sizes
        sizeSeed = time(NULL);
        sleep(SLEEP_TIME);
        msg << "seed: " << sizeSeed;
        debug(__func__, msg.str());
        msg.clear();
        msg.str("");
        srand(sizeSeed);
        // only gen size <= 20
        sizes[i] = rand() % 20 + 1;
        msg << "Size of array[" << i << "]: " << sizes[i];
        debug(__func__, msg.str());
        msg.clear();
        msg.str("");
    }

    // init arrays
    debug(__func__, "Generating arrays with random integers");
    for (int i = 0; i < numOfArrays; ++i) {
        array[i] = new int[sizes[i]];
        fillArray(time(NULL), sizes[i], (int *)array[i]);
    }

    // iterate each array. do max-sub searching
    for (int i = 0; i < numOfArrays; ++i) {
        info(__func__, "-----------------------");
        msg << "Do searching on array[" << i << "], size = " << sizes[i];
        info(__func__, msg.str());
        msg.clear();
        msg.str("");
        try {
            (*func)((int *)array[i], sizes[i], bestStart, bestEnd, bestSum);
            msg << "bestStart = " << bestStart;
            msg << " bestEnd = " << bestEnd;
            msg << " bestSum = " << bestSum;
            info(__func__, msg.str());
            msg.clear();
            msg.str("");
            printArray(bestStart, bestEnd, array[i], "The max-sub:");
        } catch (exception& e) {
            error(__func__, e.what());
        }
    }

    // release arrays
    debug(__func__, "Disposing arrays");
    for (int i = 0; i < numOfArrays; ++i) {
        delete [] array[i];
        msg << "Disposing A[" << i << "] in size " << sizes[i];
        debug(__func__, msg.str());
        msg.clear();
        msg.str("");
    }
    debug(__func__, "Disposing array table");
    delete [] array;
    debug(__func__, "Disposing size table");
    delete[] sizes;
} // max_sub_random_runner


/**
 * Print this program's usage to the current stdout.
 */
static void printUsage(const char * prog) {
    cout << "Usage: " << prog << " [OPTIONS]" << endl;
    cout << "Run max-sub searching METHOD on [NUM_OF_ARRAYS]";
    cout << " with random integers filled." << endl;
    cout << endl;
    cout << "Mandatory options:" << endl;
    cout << "  -n    Number of arrays to be generated and searched." << endl;
    cout << "  -m    The name of the search method to apply. The valid values:";
    cout << endl;
    cout << "        bruteForce_n2, bruteForce_n3, recursive, kadane, all.";
    cout << endl;
    cout << "        If all is given, every available method will run." << endl;
    cout << endl;
    cout << "E.g.:" << endl;
    cout << "  " << prog << " -n 10 -m kadane" << endl;
    cout << "  " << prog << " -n 4 -m all" << endl;
    cout << endl;
}


/**
 * Validate whether a string is a legal number representation.
 *
 * @param src   A string to be validated.
 * @return Returns 0 if the given string is a legal number representation;
 *         returns -1 if otherwise.
 */
static int isNumber(const char * src) {
    int dotCount = 0;
    int length = strlen(src);

    if (length < 1) return -1;

    for (int i = 0; i < length; ++i) {
        if (i == 0) {
            if (src[i] < '0' || src[i] > '9') {
                if (src[i] != '+' && src[i] != '-' && src[i] != '.') {
                    return -1;
                } else if (src[i] == '.') {
                    dotCount++;
                }
            }
        } else {
            if (src[i] == '.') {
                dotCount++;
                if (dotCount > 1)
                    return -1;
            } else if (src[i] < '0' || src[i] > '9') {
                return -1;
            }
        }
    }
    return 0;
} // isNumber


/**
 * The program runtime execution entrance
 */
int main(int argc, char * argv[]) {
    if (argc != 5)
        printUsage(argv[0]);

    int numOfArrays = -1;
    string method;
    try {
        for (int i = 1; i < argc; ++i) {
            // -n argument
            if (strncmp(argv[i], "-n", 2) == 0) {
                if (i != 1 && i != 3)
                    throw runtime_error("Argument is not at correct position.");
                if (isNumber(argv[i + 1]) != 0)
                    throw runtime_error("Not a valid number");
                numOfArrays = atoi(argv[i + 1]);
                if (numOfArrays <= 0)
                    throw runtime_error("Not a valid number");
                continue;
            }
            // -m argument
            if (strncmp(argv[i], "-m", 2) == 0) {
                if (i != 1 && i != 3)
                    throw runtime_error("Argument is not at correct position.");
                method = string(argv[i + 1]);
            }
        }
    } catch (exception& e) {
        cout << e.what() << endl;
        printUsage(argv[0]);
        exit(-1);
    }

    // enclose function execution in a try block
    try {
        // set logging logLevel
        // setLoggingLevel(DEBUG);
        setLoggingLevel(INFO);

        // do the searching
        cout << method.empty();
        if (numOfArrays == -1 || method.empty() )
            throw runtime_error("Parsing arguments failed");

        if (0 == method.compare("bruteForce_n2"))
            max_sub_random_runner(numOfArrays, method, bruteForce_n2);
        else if (0 == method.compare("bruteForce_n3"))
            max_sub_random_runner(numOfArrays, method, bruteForce_n3);
        else if (0 == method.compare("recursive"))
            max_sub_random_runner(numOfArrays, method, find_maximum_subarray);
        else if (0 == method.compare("kadane"))
            max_sub_random_runner(numOfArrays, method, kadane);
        else if (0 == method.compare("all")) {
            max_sub_random_runner(numOfArrays, method, bruteForce_n2);
            max_sub_random_runner(numOfArrays, method, bruteForce_n3);
            max_sub_random_runner(numOfArrays, method, find_maximum_subarray);
            max_sub_random_runner(numOfArrays, method, kadane);
        }
    } catch (exception& e) {
        cout << e.what() << endl;
        exit(-1);
    }
    exit(0);
} // main
