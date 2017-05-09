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

#ifndef ARGUMENTS_H
#define ARGUMENTS_H


#include <string>
#include "logging.h"


using std::string;

class Options {
public:
    bool isManual;
    bool isFile;
    bool isAll;
    bool isHelp;
    bool isLogOn;
    loglevel_t logLevel;
    string filePath;
};

void printUsages(string prog);

bool checkArgsSanity(const int argc, const char *argv[]);

Options parseArgs(const int argc, const char * argv[]);

#endif
