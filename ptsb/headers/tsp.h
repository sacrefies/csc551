// -----------------------------------------------------------------------------
// Filename:    tsp.h
// Revision:    $Id$
// Description: This file includes definitions of TSP problem solvers
// Created:     04/02/2016 01:20:29 PM
// Compiler:    G++
// Author:      Jason Meng (jm), jm652564@sju.edu
//
// Copyright (c) 2016 by Jason Meng, no rights reserved.
// -----------------------------------------------------------------------------


/** include guard:  */
#ifndef TSP_H
#define TSP_H


/**
 * This function finds the optimal solution by repeatedly calling
 * randomize_in_place while keeping track of the best solution.
 *
 * @param repeats   the number of repeats.
 * @param tour      the initial tour
 * @param size      the length of array
 *
 * @return Returns the best solution in array.
 */
void bruteForce1(double tour[][2], int size, long repeats);


// -----------------------------------------------------------------------------
#ifdef GRAD
/**
 * this function generates (exactly) all permutations of the tour.
 * your solution should be hard-coded to only work for an array of length 5.
 * the optimal tour should be returned in tour.
 *
 * @param tour      the initial tour
 * @return the number of permutations tested should be returned
 */
long bruteForce2(double tour[5][2]);
#endif


// -----------------------------------------------------------------------------
#ifdef  EXTRA_CREDIT_RECURSIVE
// this recursive function generates (exactly) all permutations of the tour A.
//  your solution should work for an array of any length n.
//  the optimal tour should be returned in A.
// note:
//  to dynamically allocate 2D arrays, use the following:
//      double  (*tmp)[2] = new double[n][2];  //tmp is a ptr to pairs of doubles
void bruteForce3(double tour[][2], int size);
#endif


// ---------------------------------------------------------------------------
#ifdef  EXTRA_CREDIT_NON_RECURSIVE
// this nonrecursive function generates (exactly) all permutations of the tour A.
//  your solution should work for an array of any length n.
//  the optimal tour should be returned in A.
// note:
//  to dynamically allocate 2D arrays, use the following:
//      double  (*tmp)[2] = new double[n][2];  //tmp is a ptr to pairs of doubles
void bruteForce4(double tour[][2], int size);
#endif


#endif /** end of include guard:  */
