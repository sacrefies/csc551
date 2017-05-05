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
#include "logging.h"

using std::string;

/// A struct which holds the parsed command line arguments
struct options_t {
    bool file;
    bool all;
    bool help;
    bool logOn;
    loglevel_t logLevel;
    string filePath;
};

/// Print this program's usage.
///
/// \param prog The name of this program.
void printUsages(string prog);

/// Validate the command line arguments.
///
/// \param argc The number of the arguments
/// \param argv The command line arguments
/// \return Returns true if the validation passes.
bool checkArgsSanity(const int argc, const char *argv[]);

/// Parse the command line arguments.
///
/// \param argc The number of the arguments
/// \param argv The command line arguments
/// \return Returns an instance of the struct options_t
options_t parseArgs(const int argc, const char *argv[]);

#endif /** end of include guard */
