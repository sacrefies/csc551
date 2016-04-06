// -----------------------------------------------------------------------------
// Filename:    brutes.cpp
// Revision:    $Id$
// Description: This file includes TSP solver functions in brute force
// Created:     04/02/2016 01:20:29 PM
// Compiler:    G++
// Author:      Jason Meng (jm), jm652564@sju.edu
//
// Copyright (c) 2016 by Jason Meng, no rights reserved.
// -----------------------------------------------------------------------------


#include <cstdlib>
#include <sstream>
#include <iomanip>
#include <cfloat>
#include "headers/utils.h"
#include "headers/logging.h"
#include "headers/tsp.h"


using std::stringstream;
using std::setprecision;
using std::string;


/**
 * This function finds the optimal solution by repeatedly calling
 * randomize_in_place while keeping track of the best solution.
 * this function returns the best solution in tour.
 *
 * @param repeats   the number of repeats.
 * @param tour      the initial tour
 * @param size      the length of array
 */
void bruteForce1(double tour[][2], int size, long repeats) {
    if (repeats < 0L) {
        string s = "Param 'repeats' is given a negative number."
            " A default value 0 is assigned to repeats.";
        warning(__func__,  s);
        repeats = 0L;
    }
    double optimal, local_optm;
    double (*tmp)[2] = new double[size][2];
    copy(tmp, size, tour);
    optimal = cost(tmp, size);
    for (long i = 0L; i < repeats; ++i) {
        randomize_in_place(tmp, size);
        local_optm = cost(tmp, size);
        // reset the global
        if (local_optm < optimal) {
            optimal = local_optm;
            copy(tour, size, tmp);
        }
    }
    delete[] tmp;
    tmp = NULL;
    stringstream msg;
    msg << "Found the optimal tour, cost = " << setprecision(8);
    msg << optimal;
    info(__func__, msg.str());
    print(tour, size);
} // bruteForce1


// -----------------------------------------------------------------------------
#ifdef GRAD

static int tour_exists(double tour[5][2], double queue[][5][2],
                       long queue_size) {
    for (long i = 0; i < queue_size; ++i) {
        int same = 0;
        for (int j = 0; j < 5; ++j) {
            if ((queue[i][j][0] - tour[j][0] <= 0.0000001) &&
                (queue[i][j][1] - tour[j][1] <= 0.0000001))
                same++;
            else
                break;
        }
        if (same == 5)
            return 0;
    }
    return 1;
}

/**
 * this function generates (exactly) all permutations of the tour.
 * your solution should be hard-coded to only work for an array of length 5.
 * the optimal tour should be returned in tour.
 *
 * @param tour      the initial tour
 * @return the number of permutations tested should be returned
 */
long bruteForce2(double tour[5][2]) {
    // total permutations
    int permutations = fact(5L);
    // optimal costs
    double optimal = DBL_MAX, local_optm;
    stringstream msg;

    // lets do it in a mem expensive way
    // set up a queue (represented by an array)
    double (*queue)[5][2] = new double[permutations][5][2];
    // a temp array to record the tour which has the current optimal cost
    double (*opt_tour)[2] = new double[5][2];

    // add the first permutation, the original tour
    copy(queue[0], 5, tour);

    // there has been one item in queue
    int head = 0, tail = 0;
    while (head <= tail) {
        msg << "queue size=" << tail - head + 1;
        msg << ", head=" << head << ", tail=" << tail;
        debug(__func__, msg.str());
        msg.clear();
        msg.str("");

        double (*tmp)[2] = new double[5][2];
        // dequeue head
        copy(tmp, 5, queue[head++]);
        debug(__func__, "polled head:");
        // print(tmp, 5);
        // calc cost
        local_optm = cost(tmp, 5);
        if (local_optm < optimal) {
            msg << "found better route. local=" << setprecision(8) << local_optm;
            msg << ", global=" << setprecision(8) << optimal;
            debug(__func__, msg.str());
            msg.clear();
            msg.str("");
            copy(opt_tour, 5, tmp);
            optimal = local_optm;
        }

        // permute head
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                if (j != i) {
                    swap_position(tmp, i, j);
                    // now we have one permutation
                    // check if it exists in queue
                    if (0 != tour_exists(tmp, queue, tail + 1)) {
                        debug(__func__, "route not exists, add route");
                        // print(tmp, 5);
                        copy(queue[++tail], 5, tmp);
                    } else {
                        debug(__func__, "route exists");
                    }
                    swap_position(tmp, i, j);
                }
            }
        }

        delete[] tmp;
        tmp = NULL;

        msg << "after permuting, head=" << head;
        msg << ", tail=" << tail;
        debug(__func__, msg.str());
        msg.clear();
        msg.str("");
    }

    copy(tour, 5, opt_tour);

    // clean up
    delete[] opt_tour;
    delete[] queue;
    opt_tour = NULL;
    queue = NULL;

    msg << "Found the optimal tour, cost = " << setprecision(8);
    msg << optimal;
    info(__func__, msg.str());
    msg.clear();
    msg.str("");
    msg << "Permutations generated: " << tail + 1;
    info(__func__, msg.str());
    print(tour, 5);
    return tail + 1;

} // bruteForce2
#endif // ifdef GRAD


// -----------------------------------------------------------------------------
#ifdef EXTRA_CREDIT_RECURSIVE

static double recur_permute_cost(double tour[][2], int size, int start, int end,
                                 double opt[][2]) {
    if (start == end) {
        // last one, just return the cost
        // no comparison happens;
        copy(opt, size, tour);
        return cost(tour, size);
    }

    double local_optm, optimal;
    for (int i = start; i <= end; ++i) {
        // swap
        swap_position(tour, start, i);
        local_optm = cost(tour, size);
        optimal = recur_permute_cost(tour, size, start + 1, end, opt);

        if (local_optm < optimal) {
            copy(opt, size, tour);
            optimal = local_optm;
        }
        swap_position(tour, start, i);
    }
    return optimal;
} // recur_permute_cost

/**
 * this recursive function generates (exactly) all permutations of the tour.
 * your solution should work for an array of any size.
 * the optimal tour should be returned in tour.
 * note:
 *  to dynamically allocate 2D arrays, use the following:
 *     double  (*tmp)[2] = new double[n][2];  //tmp is a ptr to pairs of doubles
 */
void bruteForce3(double tour[][2], int size) {
    // a temp array to record the tour which has the current optimal cost
    double (*opt_tour)[2] = new double[size][2];
    double optimal = recur_permute_cost(tour, size, 0, size - 1, opt_tour);
    copy(opt_tour, size, tour);

    delete[] opt_tour;
    opt_tour = NULL;

    stringstream msg;
    msg << "Found the optimal tour, cost = " << setprecision(8) << optimal;
    info(__func__, msg.str());
    print(tour, 5);
}
#endif // ifdef  EXTRA_CREDIT_RECURSIVE


// ---------------------------------------------------------------------------
#ifdef  EXTRA_CREDIT_NON_RECURSIVE

static int tour_exists_1(double tour[][2], double *** queue, long queue_size) {
    for (long i = 0; i < queue_size; ++i) {
        int same = 0;
        for (int j = 0; j < 5; ++j) {
            if ((queue[i][j][0] - tour[j][0] <= 0.0000001) &&
                (queue[i][j][1] - tour[j][1] <= 0.0000001))
                same++;
            else
                break;
        }
        if (same == 5)
            return 0;
    }
    return 1;
}

/**
 * his nonrecursive function generates (exactly) all permutations of the tour.
 * your solution should work for an array of any length n.
 * the optimal tour should be returned in A.
 * note:
 *   to dynamically allocate 2D arrays, use the following:
 *    double (*tmp)[2] = new double[n][2];  //tmp is a ptr to pairs of doubles
 */
void bruteForce4(double tour[][2], int size) {
    if (size == 5) {
        bruteForce2(tour);
        return;
    }

    long permutations = (size <= 10) ? fact((long)size) : factRecursive((long)size);
    // optimal costs
    double optimal = DBL_MAX, local_optm;
    stringstream msg;

    double *** queue = new double **[permutations];
    for (long x = 0; x < permutations; ++x) {
        double (*tmp)[2] = new double[size][2];
        queue[x] = (double **)tmp;
    }

    // lets do it in a mem expensive way
    // set up a queue (represented by an array)
    // double (*queue)[5][2] = new double[permutations][5][2];
    // a temp array to record the tour which has the current optimal cost
    double (*opt_tour)[2] = new double[size][2];
    // add the first permutation, the original tour
    copy((double (*)[2])queue[0], size, tour);

    // there has been one item in queue
    int head = 0, tail = 0;
    while (head <= tail) {
        msg << "queue size=" << tail - head + 1;
        msg << ", head=" << head << ", tail=" << tail;
        debug(__func__, msg.str());
        msg.clear();
        msg.str("");

        double (*tmp)[2] = new double[5][2];
        // dequeue head
        copy(tmp, 5, (double (*)[2])queue[head++]);
        debug(__func__, "polled head:");
        // print(tmp, 5);
        // calc cost
        local_optm = cost(tmp, 5);
        if (local_optm < optimal) {
            msg << "found better route. local=" << setprecision(8) << local_optm;
            msg << ", global=" << setprecision(8) << optimal;
            debug(__func__, msg.str());
            msg.clear();
            msg.str("");
            copy(opt_tour, 5, tmp);
            optimal = local_optm;
        }

        // permute head
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                if (j != i) {
                    swap_position(tmp, i, j);
                    // now we have one permutation
                    // check if it exists in queue
                    if (0 != tour_exists_1(tmp, queue, tail + 1)) {
                        debug(__func__, "route not exists, add route");
                        // print(tmp, 5);
                        copy((double (*)[2])queue[++tail], 5, tmp);
                    } else {
                        debug(__func__, "route exists");
                    }
                    swap_position(tmp, i, j);
                }
            }
        }

        delete[] tmp;
        tmp = NULL;

        msg << "after permuting, head=" << head;
        msg << ", tail=" << tail;
        debug(__func__, msg.str());
        msg.clear();
        msg.str("");
    }

    copy(tour, 5, opt_tour);

    // clean up
    delete[] opt_tour;
    delete[] queue;
    opt_tour = NULL;
    queue = NULL;

    msg << "Found the optimal tour, cost = " << setprecision(8);
    msg << optimal;
    info(__func__, msg.str());
    msg.clear();
    msg.str("");
    msg << "Permutations generated: " << tail + 1;
    info(__func__, msg.str());
    print(tour, 5);
} // bruteForce4
#endif // ifdef  EXTRA_CREDIT_NON_RECURSIVE
