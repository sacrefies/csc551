// -----------------------------------------------------------------------------
// Filename:    args.hpp
// Revision:    $Id$
// Description: this file contains the definition of the argument handling
//              functions.
// Created:     04/20/2016 01:20:29 PM
// Compiler:    G++
// Author:      Jason Meng (jm), jm652564@sju.edu
//
// Copyright (c) 2016 by Jason Meng, no rights reserved.
// -----------------------------------------------------------------------------

/** include guard */
#ifndef ARGUMENTS_H
#define ARGUMENTS_H


#include <string>
#include "logging.hpp"



using std::string;

struct options_t {
    bool file;
    bool all;
    bool help;
    bool logOn;
    loglevel_t logLevel;
    string filePath;
};

void printUsages(string prog);

bool checkArgsSanity(const int argc, const char * argv[]);

options_t parseArgs(const int argc, const char * argv[]);

#endif /** end of include guard */
