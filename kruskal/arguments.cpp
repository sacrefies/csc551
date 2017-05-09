// -----------------------------------------------------------------------------
// Filename:    arguments.cpp
// Revision:    $Id$
// Description: This file includes the implementation of command line argument
//              handling for Kruskal program.
//
//              The arguments needed:
//                  -a              run all tests, including manual,
//                                  files in sizes of tinyEWG, mediumEWG,
//                                  largeEWG, 1000EWG, 10000EWG.
//                  -m              run only manual test, overrides --all.
//                  -f <filePath>   run with the specified data file,
//                                  overrides -a, -m.
//                  -l <loglevel>   specify the log output level. It can be one
//                                  of the following: debug, error, warn, info
//                  -h             print out usage.
//              -m is the default argument.
//
// Created:     04/26/2016 01:20:29 PM
// Compiler:    G++
// Author:      Jason Meng (jm), jm652564@sju.edu
//
// Copyright (c) 2016 by Jason Meng, no rights reserved.
// -----------------------------------------------------------------------------


#include <string>
#include <iostream>

#include "headers/logging.h"
#include "headers/args.h"


using std::string;
using std::cout;
using std::endl;


void printUsages(const string prog) {
    cout << "Usage: " << prog << " [OPTIONS]" << endl;
    cout << "OPTIONS" << endl;
    cout << "   -a               Run all tests, including manual,";
    cout << endl;
    cout << "                    files in sizes of tinyEWG, mediumEWG,";
    cout << endl;
    cout << "                    largeEWG, 1000EWG, 10000EWG." << endl;
    cout << "   -m               Run only manual test, overrides --all.";
    cout << endl;
    cout << "   -f <filePath>    Run with the specified data file,";
    cout << endl;
    cout << "                    overrides -a, -m." << endl;
    cout << "   -h               Print out this usage, overrides all others.";
    cout << endl;
    cout << "   -l               The log level amongst debug, warn, info, error.";
    cout << endl;
    cout << "                    The default log level is warn.";
    cout << endl;
    cout << "-m is the default argument." << endl;
}


bool checkArgsSanity(const int argc, const char * argv[]) {
    if (argc < 2)
        return true;

    bool san = false;
    for (int i = 1; i < argc; ++i) {
        string arg(argv[i]);
        if (0 == arg.compare("-f")) {
            if (i == argc - 1)
                return false;
            ++i;
            san = true;
        } else if (0 == arg.compare("-a"))
            san = true;
        else if (0 == arg.compare("-m"))
            san = true;
        else if (0 == arg.compare("-l")) {
            if (i == argc - 1)
                return false;
            arg = string(argv[++i]);
            if (0 != arg.compare("debug") && 0 != arg.compare("warn") &&
                0 != arg.compare("info") && 0 != arg.compare("error"))
                return false;
            san = true;
        }
    }
    return san;
}


Options parseArgs(const int argc, const char * argv[]) {
    Options op;
    op.isManual = false;
    op.isFile = false;
    op.isAll = false;
    op.isHelp = false;
    op.isLogOn = false;
    op.filePath = "";
    op.logLevel = WARNING;

    if (argc < 2) {
        op.isManual = true;
        return op;
    }
    for (int i = 1; i < argc; ++i) {
        string arg(argv[i]);
        if (0 == arg.compare("-f")) {
            op.isFile = true;
            op.filePath = string(argv[++i]);
        }
        if (0 == arg.compare("-a")) op.isAll = true;
        if (0 == arg.compare("-m")) op.isManual = true;
        if (0 == arg.compare("-l")) {
            arg = string(argv[++i]);
            op.isLogOn = true;
            if (0 == arg.compare("debug"))
                op.logLevel = DEBUG;
            else if (0 == arg.compare("info"))
                op.logLevel = INFO;
            else if (0 == arg.compare("warn"))
                op.logLevel = WARNING;
            else if (00 == arg.compare("error"))
                op.logLevel = ERROR;
        }
        if (0 == arg.compare("-h")) op.isHelp = true;
    }
    // check if print help is needed
    if (op.isLogOn && false == op.isManual &&
        false == op.isFile && false == op.isAll)
        op.isManual = true;
    return op;
}
