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


#include <cctype>
#include <cstdio>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>
#include <sys/time.h>

#include "headers/logging.h"


/** fold all 'using std::foo' togethor */
using namespace std;


/** Set the default level is INFO */
loglevel_t level = INFO;


/**
 * Convert current date and time into a string, and store it into a string buffer.
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
 * @param func the name of the running function.
 * @param msg  log message
 */
void debug(string func, string msg) {
    if (level <= DEBUG) {
        cout << getFormattedTime() << " - ";
        cout << setw(5) << "DEBUG" << " - ";
        if (!func.empty())
            cout << func << " - ";
        cout << msg << endl;
    }
}


/**
 * Output info log message to current stdout.
 *
 * @param func the name of the running function.
 * @param msg  log message
 */
void info(string func, string msg) {
    if (level <= INFO) {
        cout << getFormattedTime() << " - ";
        cout << setw(5) << "INFO" << " - ";
        if (!func.empty())
            cout << func << " - ";
        cout << msg << endl;
    }
}


/**
 * Output warning log message to current stdout.
 *
 * @param func the name of the running function.
 * @param msg  log message
 */
void warning(string func, string msg) {
    if (level <= WARNING) {
        cout << getFormattedTime() << " - ";
        cout << setw(5) << "WARN" << " - ";
        if (!func.empty())
            cout << func << " - ";
        cout << msg << endl;
    }
}


/**
 * Output error log message to current stdout.
 *
 * @param func the name of the running function.
 * @param msg  log message
 */
void error(string func, string msg) {
    if (level <= ERROR) {
        cerr << getFormattedTime() << " - ";
        cerr << setw(5) << "ERROR" << " - ";
        if (!func.empty())
            cerr << func << " - ";
        cerr << msg << endl;
    }
}
