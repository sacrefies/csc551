// -----------------------------------------------------------------------------
// Filename:    utilities.cpp
// Revision:    $Id$
// Description: This file includes implementation of utility functions
// Created:     04/10/2016 01:20:29 PM
// Compiler:    G++
// Author:      Jason Meng (jm), jm652564@sju.edu
//
// Copyright (c) 2016 by Jason Meng, no rights reserved.
// -----------------------------------------------------------------------------


#include <random>  // random_device, mt19937_64, uniform_real_distribution
#include <sstream> // stringstream
#include <iomanip> // setprecision
#include <string>

#include "headers/utils.hpp"
#include "headers/logging.hpp"

using std::random_device;
using std::mt19937_64;
using std::uniform_real_distribution;
using std::stringstream;
using std::setprecision;
using std::string;
using std::to_string;


// the randoms
static random_device rd;

const string array_to_string(double list[], int size) {
    stringstream * out = new stringstream();
    string rs;

    *out << "[";
    for (int i = 0; i < size; ++i) {
        *out << setprecision(6) << list[i];
        if (i < size - 1)
            *out << ",";
    }
    *out << "]";
    rs = out->str();
    out->clear();
    out->str("");
    delete out;

    return rs;
}


/**
 * Generate a random double number in between low and high.
 */
double random_double(const int low, const int high) {
    mt19937_64 gen(rd());

    uniform_real_distribution<double> dist(low, high);

    return dist(gen);
}


/**
 * Search an array of double and return whether match exists in the array.
 *
 * @return Returns 0 if match is found; returns -1 otherwise.
 */
int in_array(const double match, const double list[], const int size) {
    double key = match * amplifier;

    for (int i = 0; i < size; ++i) {
        if (list[i] * amplifier - key <= threshold)
            return 0;
    }

    return -1;
}


/**
 * Do insertion sort to the given list(array).
 *
 * @param size The size of the given list(array).
 * @param list An array to be sorted.
 */
void insertion_sort(double list[], int size) {
    // boundary checks
    if (size < 2) {
        string msg = "Do nothing: size = ";
        debug(__func__, msg + to_string(size));

        return;
    }

    // init tmp
    int sortedIndex = 0;
    double key      = 0.;
    for (int i = 1; i < size; ++i) {
        // get the key
        key = list[i];
        // find a space for the key in the sorted sublist.
        for (sortedIndex = i - 1; sortedIndex >= 0; --sortedIndex) {
            if (list[sortedIndex] * amplifier > key * amplifier)
                list[sortedIndex + 1] = list[sortedIndex];
            else
                break;
        }
        // insert the key here
        list[sortedIndex + 1] = key;
    }
}
