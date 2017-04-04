// -----------------------------------------------------------------------------
// Filename:    utils.h
// Revision:    $Id$
// Description: This file includes definitions of utility functions
// Created:     04/02/2016 01:20:29 PM
// Compiler:    G++
// Author:      Jason Meng (jm), jm652564@sju.edu
//
// Copyright (c) 2016 by Jason Meng, no rights reserved.
// -----------------------------------------------------------------------------


#include <string>


/** include guard */
#ifndef UTILS_H
#define UTILS_H

using std::string;

const double threshold = 0.00000001;


const string array_to_string(double list[], int size);


/**
 * Generate a random double number in between low and high.
 */
double random_double(const int low, const int high);

/**
 * Generate a random integer number in between low and high.
 */
int random_int(const int low, const int high);

/**
 * Search an array of double and return whether match exists in the array.
 *
 * @return Returns 0 if match is found; returns -1 otherwise.
 */
int in_array(const double match, const double list[], const int size);


/**
 * Do insertion sort to the given list(array).
 *
 * @param size The size of the given list(array).
 * @param list An array to be sorted.
 */
void insertion_sort(double list[], int size);

#endif // ifndef UTILS_H
/** end of include guard */
