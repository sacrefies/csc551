// ------------------------------------------------------------------------------------
//            $Id$
//          $Date$
//       Filename:  sortMain.cpp
//
//    Description:  The program main execution entrance which invokes insertion
//                  sort and selection sort.
//
//        Version:  1.0
//        Created:  01/28/2016 04:06:05 PM
//       Compiler:  g++
//         Author:  Jason Meng (jm), jm652564@sju.edu
//
// Copyright (c) 2016, Jason Meng
// ------------------------------------------------------------------------------------

// c includes
#include <sys/time.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
// c++ includes
#include <iostream>
#include <string>
// custom headers
#include "headers/sorts.h"
#include "headers/timing.h"


using namespace std;


/**
 * A structure which holds the translated command line
 * arguments for the program to run the sorts.
 */
struct options_t {
    // count of iterations
    int runs;
    // sort algorithm to apply
    // insertion=0; selection=1; merge=2, mergeInplace=3, mergeInner=4
    int sort;
    // array size
    int size;
};


/*
 * Validate the options
 *
 * @param options A struct which holds the option data fields.
 * @return returns 0 if the options are valid; returns -1 if otherwise.
 */
int validateOptions(struct options_t options) {
    if (options.size < 2) {
        cout << "Input array size is less than 2." << endl;
        return -1;
    };

    if (options.runs < 1) {
        cout << "Input runs is less than 1." << endl;
        return -1;
    };
    return 0;
};


/**
 * read the command line arguments and store the arguments into
 * options object.
 *
 * @param argc The number of arguments
 * @param argv An array of argument elements
 * @return A struct of options_t
 */
options_t readOptions(const int argc, const char *argv[]) {
    // define and set the default values of the options.
    struct options_t options = {
        20,
        0,
        20,
    };

    for (int i = 0; i < argc; i ++) {
        if (strcmp("-r", argv[i]) == 0 || strcmp("--runs", argv[i]) == 0) {
            try {
                options.runs = strtoll(argv[i+1], NULL, 10);
            } catch (...) {
                cout << "Cannot parse the argument to runs. Input: " << argv[i+1] << endl;
                throw;
            };
            continue;
        };

        if (strcmp("-s", argv[i]) == 0 || strcmp("--sort", argv[i]) == 0) {
            if (strcmp("insertionSort", argv[i+1]) == 0)
                options.sort = 0;
            else if (strcmp("selectionSort", argv[i+1]) == 0)
                options.sort = 1;
            else if (strcmp("mergeSort", argv[i+1]) == 0)
                options.sort = 2;
            else if (strcmp("mergeSortInplace", argv[i+1]) == 0)
                options.sort = 3;
            else if (strcmp("mergeSortInnerSwap", argv[i+1]) == 0)
                options.sort = 4;
            else {
                cout << "Sort " << argv[i+1] << " is not supported yet." << endl;
                cout << "The default insertion sort will be applied." << endl;
            }
            continue;
        };

        if (strcmp("-n", argv[i]) == 0 || strcmp("--size", argv[i]) == 0) {
            try {
                options.size = strtoll(argv[i+1], NULL, 10);
            } catch (...) {
                cout << "Cannot parse the argument to array size. Input: " << argv[i+1] << endl;
                throw;
            };
            continue;
        };
    };

    return options;
};

/**
 *         Name:  main
 *  Description:
 */
int main(const int argc, const char *argv[]) {
    string help = "sortMain.out [OPTIONS]\n";
    struct options_t options;

    help += "Usages: ./sortMain[.out] -n 20 -r 50 -s selectionSort\n";
    help += "\nOPTIONS:\n";
    help += "-n/--size     The size of the array to be sorted\n";
    help += "-r/--runs     The iteration number\n";
    help += "-s/--sort     The sort algorithm to be used\n\n";
    help += "EX:\n";
    help += "./sortMain.out -r 50 -s insertionSort -n 50\n";
    help += "The command above triggers insertion sort apply for 50 times to an array which conatins 50 elements.\n";
    help += "\n";


    if (argc < 2) {
        // print help;
        cout << help << endl;
        return 0;
    };

    try {
        // cout << "parse options" << endl;
        options = readOptions(argc, argv);
        cout << "size: " << options.size << " iter: " << options.runs << " sort: " << options.sort << endl;
    } catch (...){
        cout << help << endl;
        return -1;
    };

    if (validateOptions(options) != 0) {
        cout << "Wrong options" << endl;
        cout << help << endl;
        return -1;
    };

    // exec sorts.
    switch (options.sort) {
        case 0:
            timing(options.runs, options.size, insertionSort);
            break;
        case 1:
            timing(options.runs, options.size, selectionSort);
            break;
        case 2:
            timing(options.runs, options.size, mergeSort);
            break;
        case 3:
            timing(options.runs, options.size, mergeSortInplace);
            break;
        case 4:
            timing(options.runs, options.size, mergeSortInnerSwap);
            break;
        default:
            cout << "Unknown sort, stopped." << endl;
            return -1;
    }

    return 0;

}
