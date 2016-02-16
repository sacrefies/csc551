// ------------------------------------------------------------------------------------
//       Filename: arrayUtils.h
//       Revision: $Id$
//    Description: This file includes definitions of a few helper
//                 or utility function for array handling.
//        Created: 02/15/2016 01:20:29 PM
//       Compiler: G++
//         Author: Jason Meng (jm), jm652564@sju.edu
//
// Copyright (c) 2016 by Jason Meng
// ------------------------------------------------------------------------------------

/* include guard:  */
#ifndef ARRAYUTILS_H
#define ARRAYUTILS_H

/**
 * Fill up a given array by using random int64 numbers
 *
 * @param size The size of the array
 * @param list The array to be filled
 */
void fillArray(const int seed, const int size, int list[]);


/**
 * Print the given array to the stdout
 *
 * @param size The size of the array
 * @param list The array of type int64
 */
void printArray(const int size, int list[], string msg);

#endif /* end of include guard:  */
