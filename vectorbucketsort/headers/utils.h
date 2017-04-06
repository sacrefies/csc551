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

/// Convert an array of double to a string object.
/// \param list An array of double.
/// \param size The length of the array.
/// \return A string which represents the input array, elements are separated by comma.
const string array_to_string(double list[], int size);

/// Generate a random double number in the given range.
/// \param low The lower bound of the range, inclusive.
/// \param high The upper bound of the range, exclusive.
/// \return A random double value.
double random_double(const int low, const int high);

/// Generate a random integer number in the given range.
/// \param low The lower bound of the range, inclusive.
/// \param high The upper bound of the range, exclusive.
/// \return A random int value.
int random_int(const int low, const int high);

/// Check the existance of a double value in an array of double.
/// \param match The double value to search.
/// \param list An array of double.
/// \param size The length of the array.
/// \return Returns 0 if the value is found in the array; otherwise returns -1.
int in_array(const double match, const double list[], const int size);

/// Sort an array with the Insertion-Sort algorithm.
/// \param list An array to be sorted.
/// \param size The size of the given list(array).
void insertion_sort(double list[], int size);

#endif
/** end of include guard */
