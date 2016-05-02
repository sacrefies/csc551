// -----------------------------------------------------------------------------
// Filename:    main.cpp
// Revision:    $Id$
// Description: test MST - Prim's algorithm.
// Created:     04/26/2016 01:20:29 PM
// Compiler:    G++
// Author:      Jason Meng (jm), jm652564@sju.edu
//              George J. Grevera, Ph.d.
//
// Copyright (c) George J. Grevera, 2016.  All rights reserved.
// Copyright (c) 2016 by Jason Meng, no rights reserved.
// -----------------------------------------------------------------------------


// C++ headers
#include <iostream>     // cout, endl
// home-made headers
#include "headers/Prim.hpp"
#include "headers/logging.hpp"
#include "headers/args.hpp"


using std::cout;
using std::endl;


static void run_file_setup(string filePath) {
    debug(__func__, "starting test, test file");
    Prim prim(filePath);
    // Prim  prim( "tinyEWG.txt" );
    // Prim  prim( "1000EWG.txt" );
    prim.process();
    cout << prim;
}

/**
 * Main program exec entry point
 */
int main(const int argc, const char * argv[]) {

    if (false == checkArgsSanity(argc, argv)) {
        printUsages(argv[0]);
        exit(1);
    }

    options_t op = parseArgs(argc, argv);
    setLoggingLevel(op.logLevel);
    if (true == op.file) {
        run_file_setup(op.filePath);
        exit(0);
    }

    if (true == op.all) {
        run_file_setup("test_data/tinyEWG.txt");
        run_file_setup("test_data/mediumEWG.txt");
        run_file_setup("test_data/1000EWG.txt");
        run_file_setup("test_data/10000EWG.txt");
    }

    exit(0);
}
