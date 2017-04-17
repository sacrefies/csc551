// -----------------------------------------------------------------------------
// Filename:    logging.cpp
// Revision:    $Id$
// Description: This file includes the some utility functions for logging
//              outputs.
// Created:     02/15/2016 01:20:29 PM
// Compiler:    G++
// Author:      Jason Meng (jm), jm652564@sju.edu
//
// Copyright (c) 2016 by Jason Meng, no rights reserved.
// -----------------------------------------------------------------------------


// C includes
#include <cctype>
#include <cstdio>
#include <sys/time.h>
//#include <ctime>
// CPP includes
#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>
// homemade headers
#include "headers/logging.h"


/** fold all 'using std::foo' togethor */
using namespace std;


/** Set the default level is INFO */
loglevel_t level = INFO;


/**
 * Convert current date and time into a string.
 *
 * @return A string which contains the formatted datetime value.
 */
static string getFormattedTime() {
    // a string stream to form the final output
    stringstream ss;
    // a time value which to be set by gettimeofday()
    // to get the millisecond faction
    struct timeval t_value;
    // a string buffer to store the millisecond part.
    char buffer[50];

    // get the current time value
    gettimeofday(&t_value, NULL);
    // set the return string
    strftime(buffer, sizeof(buffer), "%F %T.", gmtime(&t_value.tv_sec));
    ss << buffer << t_value.tv_usec / 1000;
    return ss.str();
}


/**
 * Set current logging level
 */
void setLoggingLevel(loglevel_t logLevel) {
    level = logLevel;
}


/**
 * Output debug log message to current stdout.
 *
 * @param tag   the tag of this line of log.
 * @param msg   log message
 */
void debug(string tag, string msg) {
    if (level <= DEBUG) {
        cout << getFormattedTime() << " - ";
        cout << setw(5) << "DEBUG" << " - ";
        if (!tag.empty())
            cout << tag << " - ";
        cout << msg << endl;
    }
}


/**
 * Output info log message to current stdout.
 *
 * @param tag   the tag of this line of log.
 * @param msg   log message
 */
void info(string tag, string msg) {
    if (level <= INFO) {
        cout << getFormattedTime() << " - ";
        cout << setw(5) << "INFO" << " - ";
        if (!tag.empty())
            cout << tag << " - ";
        cout << msg << endl;
    }
}


/**
 * Output warning log message to current stdout.
 *
 * @param tag   the tag of this line of log.
 * @param msg   log message
 */
void warning(string tag, string msg) {
    if (level <= WARNING) {
        cout << getFormattedTime() << " - ";
        cout << setw(5) << "WARN" << " - ";
        if (!tag.empty())
            cout << tag << " - ";
        cout << msg << endl;
    }
}


/**
 * Output error log message to current stdout.
 *
 * @param tag   the tag of this line of log.
 * @param msg   log message
 */
void error(string tag, string msg) {
    if (level <= ERROR) {
        cerr << getFormattedTime() << " - ";
        cerr << setw(5) << "ERROR" << " - ";
        if (!tag.empty())
            cerr << tag << " - ";
        cerr << msg << endl;
    }
}
