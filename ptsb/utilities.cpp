// -----------------------------------------------------------------------------
// Filename:    utilities.cpp
// Revision:    $Id$
// Description: This file includes helper functions
// Created:     04/02/2016 01:20:29 PM
// Compiler:    G++
// Author:      Jason Meng (jm), jm652564@sju.edu
//
// Copyright (c) 2016 by Jason Meng, no rights reserved.
// -----------------------------------------------------------------------------


#include <cmath>
#include <ctime>

#include <sstream>
#include <random>
#include <iomanip>

#include "headers/logging.h"
#include "headers/utils.h"


using std::stringstream;
using std::random_device;
using std::mt19937_64;
using std::uniform_real_distribution;
using std::uniform_int_distribution;
using std::setprecision;


static mt19937_64 g;
static random_device rd;



/**
 * Generate a random double number in between low and high.
 */
static double random_double(const int low, const int high) {
    mt19937_64 gen(rd());

    uniform_real_distribution<double> dist(low, high);

    // hard-coded: precision == 1e6
    return (double)(((int)(dist(gen) * 1e6))/1e6);
}


// O(n)
int check_array_sanity(double list[][2], int size) {
    if (list == NULL) {
        error(__func__, "The specified array is NULL");
        return -1;
    }

    if (size < 1)
        return 0;

    for (int i = 0; i < size; ++i)
        if (list[i] == NULL) {
            stringstream msg;
            msg << "Bad array struct at " << i;
            msg << ": NUll pointer";
            error(__func__, msg.str());
            msg.clear();
            msg.str("");
            return -1;
        }
    return 0;
} // check_array_sanity


/**
 * Calculate the Euclidean distance between 2 points. O(C)
 */
static double calc_euclid_dist(double x0, double y0, double x1, double y1) {
    return sqrt(pow(x0 - x1, 2) + pow(y0 - y1, 2));
}


// lg(n)
static long multiply(long start, long end) {
    if (start == end)
        return start;
    long mid = (start + end) >> 1;
    return multiply(start, mid) * multiply(mid + 1, end);
}


/**
 * A binary search: lg(n)
 * Returns 0 if to_search exists in list; returns -1 if otherwise.
 */
static int is_in_array(int to_search, int list[], int start, int end) {
    if (start < 0 || end < 0 || end < start) {
        stringstream msg;
        msg << "Wrong indices: start=" << start;
        msg << " end=" << end;
        error(__func__, msg.str());
        msg.clear();
        msg.str("");
        return -1;
    }

    if (start == end)
        return (to_search == list[start])? 0: -1;
    int mid = (end + start) >> 1;
    return is_in_array(to_search, list, start, mid) &
           is_in_array(to_search, list, mid + 1, end);
}


/**
 * O(3n)
 * Copy the tour in src (of length size) into dest
 * (also of length size). the caller must properly init and allocate the tours.
 */
void copy(double dest[][2], int size, double src[][2]) {
    if (check_array_sanity(dest, size) != 0 ||
        check_array_sanity(src, size) != 0) {
        error(__func__, "Failed to copy");
        return;
    }

    if (size == 0)
        return;

    for (int i = 0; i < size; ++i) {
        dest[i][0] = src[i][0];
        dest[i][1] = src[i][1];
    }
} // copy


/**
 * Calculate the cost of tour (of length size). O(n*(1+C))
 *
 * @return The cost of a tour. If error happens, return -1.0.
 */
double cost(double tour[][2], int size) {
    if (check_array_sanity(tour, size) != 0) {    // O(n)
        error(__func__, "Failed to calculate cost");
        return -1.0;
    }

    debug(__func__, "array received:");
    // print(tour, size);

    if (size < 2)
        return 0.0;

    int next;
    double dist = 0.0;
    for (int i = 0; i < size; ++i) {   // O(Cn)
        next = (i + 1) % size;
        dist += calc_euclid_dist(      // C, this constant cannot be ignored
            tour[i][0], tour[i][1],
            tour[next][0], tour[next][1]);
    }
    stringstream msg;
    msg << "cost computed: " << setprecision(8) << dist;
    debug(__func__, msg.str());
    msg.clear();
    msg.str("");
    return dist;
}


/**
 * non-recursive version of n factorial. n! is returned. O(n)
 */
long fact(long n) {
    if (n < 0L) {
        error(__func__, "Unable to do factorial of a negative number");
        return -1L;
    }

    if (n == 0L)
        return 1L;

    if (n <= 2L)
        return n;

    long r = 2;
    // do math through 2 to n, inclusively.
    for (long l = 3; l <= n; ++l)
        r *= l;

    return r;
}


/**
 * recursive version of n factorial.  n! is returned. lg(n)
 */
long factRecursive(long n) {
    if (n < 0L) {
        error(__func__, "Unable to do factorial of a negative number");
        return -1L;
    }

    if (n == 0L)
        return 1L;

    if (n <= 2L)
        return n;

    return multiply(2, n);
}


/**
 * pretty print (to cout) tour of length size. O(n)
 */
void print(double list[][2], int size) {
    if (check_array_sanity(list, size) != 0) {
        error(__func__,  "Not a legal tour");
        return;
    }

    stringstream message;
    for (int i = 0; i < size; ++i) {
        message << i << ": (";
        message << setprecision(8) << list[i][0] << ", ";
        message << setprecision(8) << list[i][1] << ")";
        if (i < size - 1)
            message << ",";
        info(__func__, message.str());
        message.clear();
        message.str("");
    }
}


/**
 * Swap 2 position: O(C) - constant time
 */
void swap_position(double tour[][2], int pos_a, int pos_b) {
    double tmp = tour[pos_a][0];
    tour[pos_a][0] = tour[pos_b][0];
    tour[pos_b][0] = tmp;
    tmp = tour[pos_a][1];
    tour[pos_a][1] = tour[pos_b][1];
    tour[pos_b][1] = tmp;
}


/**
 * randomize tour of length size in place - O(n)
 */
void randomize_in_place(double tour[][2], int size) {
    if (check_array_sanity(tour, size) != 0) {
        error(__func__, "Failed to shuffle tours");
        return;
    }

    // if size < 2, do nothing
    if (size < 2)
        return;

    uniform_int_distribution<int> ud(0, size - 1);
    // use current time as the seed
    g.seed(time(0));
    int dice;
    stringstream msg;
    msg << "size=" << size;
    debug(__func__, msg.str());
    msg.clear();
    msg.str("");
    for (int i = 0; i < size; ++i) {
        dice = ud(g);
        while (i == dice)
            dice = ud(g);
        msg << "dice = " << dice;
        debug(__func__, msg.str());
        msg.clear();
        msg.str("");
        swap_position(tour, i, dice);
    }
} // randomize_in_place


/**
 * Check whether to_search exists in array list[]: lg(n)
 *
 * @return 0 if to_search exists in the array; returns -1 if otherwise.
 */
int is_in_array(int to_search, int list[], int size) {
    if (list == NULL) {
        error(__func__, "Error: list is NULL");
        return -1;
    }

    if (size < 1) {
        error(__func__, "Error: size < 1");
        return -1;
    }

    if (size == 1)
        return list[0] == to_search;

    return is_in_array(to_search, list, 0, size - 1);
} // is_in_array


/**
 * Use random double values to initialize a tour.
 * O(n*(C + 1)) => O(Cn)
 */
void fill_random_tour(double tour[][2], int size) {
    // sanity checking
    if (0 != check_array_sanity(tour, size))
        return;

    for (int i = 0; i < size; ++i) {
        tour[i][0] = random_double(0, 1);
        tour[i][1] = random_double(0, 1);
    }
}
