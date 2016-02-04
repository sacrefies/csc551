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


#include <iostream>
#include <sys/time.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <string>
#include "headers/sorts.h"
#include "headers/timing.h"


using namespace std;

/**
 * A structure which holds the translated command line
 * arguments for the program to run the sorts.
 */
struct options_t {
    int64_t runs;
    string sort;
    int64_t size;
};

/*
 * Validate the options
 *
 * @param options A struct which holds the option data fields.
 * @return returns 0 if the options are valid; returns -1 if otherwise.
 */
int64_t validateOptions(struct options_t options) {
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
        "insertionSort",
        20,
    };

    for (int64_t i = 0; i < argc; i ++) {
        if (strcmp("-r", argv[i]) || strcmp("--runs", argv[i])) {
            try {
                options.runs = strtoll(argv[i+1], NULL, 10);
            } catch (...) {
                cout << "Cannot parse the argument to runs. Input: " << argv[i+1] << endl;
                throw;
            };
            continue;
        };

        if (strcmp("-s", argv[i]) || strcmp("--sort", argv[i])) {
            options.sort = argv[i+1];
            continue;
        };

        if (strcmp("-n", argv[i]) || strcmp("--size", argv[i])) {
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
 * fill the given array with random integers.
 *
 * @param size The size of the array.
 * @param list An array of integer.
 */
void fillArray(const int64_t size, int64_t list[]) {
    if (size < 1) {
        return;
    }

    srand(time(NULL));
    for (int64_t i = 0; i < size; i++) {
        list[i] = rand() % size;
    };
};


/**
 *         Name:  main
 *  Description:  
 */
int main(const int argc, const char *argv[]) {
    string help = "sortMain.out [OPTIONS]\n";
    struct options_t options;
    int64_t *list;

    help += "OPTIONS:\n";
    help += "-n/--size     The size of the array to be sorted\n";
    help += "-r/--runs     The iteration number\n";
    help += "-s/--sort     The sort algorithm to be used\n\n";
    help += "EX:\n";
    help += "./sortMain.out -r 50 -s insertionSort -n 50\n";
    help += "The command above triggers insertion sort apply for 50 times to an array which conatins 50 elements.\n";


    if (argc == 0) {
        // print help;
        cout << help << endl;
        return 0;
    };

    try {
        options = readOptions(argc, argv);
    } catch (...){
        cout << help << endl;
        return -1;
    };

    if (!validateOptions(options)) {
        cout << help << endl;
        return -1;
    };

    // fill the array
    list = new int64_t[options.size];
    fillArray(options.size, list);

    // exec sorts.
    if (options.sort.compare("insertionSort") == 0) {
        // do timing insortion sort.
        timing(options.runs, insertionSort, options.size, list);
    } else if (options.sort.compare("selectionSort")) {
        // do timing selection sort.
        timing(options.runs, selectionSort, options.size, list);
    } else {
        cout << options.sort << " not supported yet." << endl;
    };

    // free the mem
    delete[] list;

    return 0;

}

