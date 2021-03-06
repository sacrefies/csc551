// ------------------------------------------------------------------------------------
// Filename: logging.hpp
// Revision: $Id$
// Description: This file includes definitions of logging functions
// Created: 02/15/2016 01:20:29 PM
// Compiler: G++
// Author: Jason Meng (jm), jm652564@sju.edu
//
// Copyright (c) 2016 by Jason Meng, no rights reserved.
// ------------------------------------------------------------------------------------

#include <string>

/** include guard:  */
#ifndef LOGGING_H
#define LOGGING_H


using std::string;

/**
 * An Enum to define possible Log levels
 */
enum loglevel_t {
    DEBUG = 0,
    WARNING,
    ERROR,
    INFO
};

extern loglevel_t level;

/**
 * Convert current date and time into a string.
 *
 * @return A string which contains the formatted datetime value.
 */
string getFormattedTime();

/// Print out the leading tag of a log line
/// \param tag The tag of the line of log
void printTag(string tag);

/**
 * Set current logging level
 */
void setLoggingLevel(loglevel_t logLevel);

/**
 * Output debug log message to current stdout.
 *
 * @param tag   the tag of this line of log.
 * @param msg   log message
 */
void debug(string tag, string msg);

/**
 * Output info log message to current stdout.
 *
 * @param tag   the tag of this line of log.
 * @param msg   log message
 */
void info(string tag, string msg);

/**
 * Output warning log message to current stdout.
 *
 *@param tag   the tag of this line of log.
 * @param msg   log message
 */
void warning(string tag, string msg);

/**
 * Output error log message to current stdout.
 *
 * @param tag   the tag of this line of log.
 * @param msg   log message
 */
void error(string tag, string msg);

#endif
/** end of include guard:  */
