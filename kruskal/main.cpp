// -----------------------------------------------------------------------------
// Filename:    main.cpp
// Revision:    $Id$
// Description: this file contains the demo runs for the Kruskal implementation.
// Created:     04/20/2016 01:20:29 PM
// Compiler:    G++
// Author:      Jason Meng (jm), jm652564@sju.edu
//
// Copyright (c) 2016 by Jason Meng, no rights reserved.
// -----------------------------------------------------------------------------
//
//   ______                           _        _____                   _
//  |  ____|                         | |      |_   _|                 | |
//  | |__  __  ____ _ _ __ ___  _ __ | | ___    | |  _ __  _ __  _   _| |_
//  |  __| \ \/ / _` | '_ ` _ \| '_ \| |/ _ \   | | | '_ \| '_ \| | | | __|
//  | |____ >  < (_| | | | | | | |_) | |  __/  _| |_| | | | |_) | |_| | |_
//  |______/_/\_\__,_|_| |_| |_| .__/|_|\___| |_____|_| |_| .__/ \__,_|\__|
//                             | |                        | |
//                             |_|                        |_|
//
// Example input file from: http://algs4.cs.princeton.edu/43mst/
// tinyEWG.txt contains 8 vertices and 16 edges.
// note:  vertices start at 0.
//
// 8
// 16
// 4 5 0.35 q
// 4 7 0.37 q
// 5 7 0.28 q
// 0 7 0.16 q
// 1 5 0.32 q
// 0 4 0.38 q
// 2 3 0.17 q
// 1 7 0.19 q
// 0 2 0.26 q
// 1 2 0.36 q
// 1 3 0.29 q
// 2 7 0.34 q
// 6 2 0.40 q
// 3 6 0.52 q
// 6 0 0.58 q
// 6 4 0.93 q
// -----------------------------------------------------------------------------


// cpp includes
#include <sstream> // for stringstream
#include <iostream> // for endl;
#include <string>
// homemade headers
#include "headers/Kruskal.h"
#include "headers/logging.h"
#include "headers/args.h"


using std::stringstream;
using std::endl;
using std::string;


static void run_manually_setup() {
    stringstream msg;
    msg << "=================== Test Graph Manual Set-up ===================";
    msg << endl;
    info("", msg.str());
    msg.clear();
    msg.str("");

    Kruskal k1(8);

    msg << "Graph initialized:" << k1;
    info("", msg.str());
    msg.clear();
    msg.str("");

    // normal adding
    k1.addEdge(4, 5, 0.35);
    k1.addEdge(4, 7, 0.37);
    k1.addEdge(5, 7, 0.28);
    k1.addEdge(0, 7, 0.16);
    k1.addEdge(1, 5, 0.32);
    k1.addEdge(0, 4, 0.38);
    k1.addEdge(2, 3, 0.17);
    k1.addEdge(1, 7, 0.19);
    k1.addEdge(0, 2, 0.26);
    // try adding some duplicates
    k1.addEdge(0, 4, 0.78);
    k1.addEdge(1, 7, 0.39);
    // normal adding
    k1.addEdge(1, 2, 0.36);
    k1.addEdge(1, 3, 0.29);
    k1.addEdge(2, 7, 0.34);
    k1.addEdge(6, 2, 0.40);
    // try adding some duplicates
    k1.addEdge(0, 7, 0.26);
    k1.addEdge(1, 3, 0.19);
    k1.addEdge(4, 7, 0.97);
    // normal adding
    k1.addEdge(3, 6, 0.52);
    k1.addEdge(6, 0, 0.58);
    k1.addEdge(6, 4, 0.93);
    // try adding some duplicates
    k1.addEdge(0, 7, 0.26);
    k1.addEdge(6, 0, 0.58);
    k1.addEdge(6, 4, 0.93);

    k1.process();

    msg << k1;
    info("", msg.str());
    msg.clear();
    msg.str("");

    msg << "Cost = " << k1.getMSTCost() << endl;
    info("", msg.str());
    msg.clear();
    msg.str("");
}


static void run_file_setup(string fileName) {
    // another test
    stringstream msg;
    msg << "============== Test Graph File Set-up: ";
    msg << fileName << " ===============" << endl;
    info("", msg.str());
    msg.clear();
    msg.str("");

    Kruskal k1(fileName);

    msg << "Graph initialized:" << k1;
    info("", msg.str());
    msg.clear();
    msg.str("");

    k1.process();

    msg << k1;
    info("", msg.str());
    msg.clear();
    msg.str("");

    msg << "Cost = " << k1.getMSTCost() << endl;
    info("", msg.str());
    msg.clear();
    msg.str("");
}


// ---------------------------------------------------------------------------
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

    if (true == op.manual) {
        run_manually_setup();
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
