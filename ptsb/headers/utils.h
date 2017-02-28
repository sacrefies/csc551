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


/** include guard:  */
#ifndef UTILS_H
#define UTILS_H


int check_array_sanity(double list[][2], int size);

/**
 * Use random double values to initialize a tour.
 */
void fill_random_tour(double tour[][2], int size);


/**
 * this function copies the tour in src (of length size) into tour dest
 * (also of length size). the caller must properly init and allocate the tours.
 */
void copy(double dest[][2], int size, double src[][2]);


// void copy(double dest[][2], long dest_start, long dest_end,
//           double src[][2], long src_start, long src_end);

/**
 * this functions returns the cost of tour (of length size).
 */
double cost(double tour[][2], int size);


/**
 * non-recursive version of n factorial. n! is returned.
 */
long fact(long n);


/**
 * recursive version of n factorial.  n! is returned.
 */
long factRecursive(long n);


/**
 * pretty print (to cout) tour of length size.
 */
void print(double tour[][2], int size);


/**
 * randomize tour of length size in place
 */
void randomize_in_place(double tour[][ 2 ], int size);

/**
 * Swap 2 position
 */
void swap_position(double tour[][2], int pos_a, int pos_b);

#endif /** end of include guard:  */
