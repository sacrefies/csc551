// -----------------------------------------------------------------------------
// Filename:    unittests.h
// Revision:    $Id$
// Description: This file includes definitions of unit test functions
// Created:     04/10/2016 01:20:29 PM
// Compiler:    G++
// Author:      Jason Meng (jm), jm652564@sju.edu
//
// Copyright (c) 2016 by Jason Meng, no rights reserved.
// -----------------------------------------------------------------------------


/** include guard */
#ifndef UNITESTS_H
#define UNITESTS_H


int default_initialzation_disposal_test();


int initialzation_disposal_test();


int add_1_to_size_1_test();


int add_same_5_to_size_1_test();


int add_sorted_5_to_size_2_test();


int add_5_to_size_3_test();


int add_20_to_size_10_test();

int get_random_in_size_4_test();

// ===============================================================
#if defined(GRAD) && defined(EXTRA_CREDIT)
int add_1_to_size_1_test2();


int add_same_5_to_size_1_test2();


int add_sorted_5_to_size_2_test2();


int add_5_to_size_3_test2();


int add_20_to_size_10_test2();


int get_random_in_size_4_test2();


#endif // if defined(GRAD) && defined(EXTRA_CREDIT)


#endif // ifndef UNITESTS_H
/** end of include guard */
