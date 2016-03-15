// ------------------------------------------------------------------------------------
//       Filename: logging.h
//       Revision: $Id$
//    Description: This file includes definitions of logging functions
//        Created: 02/15/2016 01:20:29 PM
//       Compiler: G++
//         Author: Jason Meng (jm), jm652564@sju.edu
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
enum loglevel_t
{
   DEBUG = 0,
   WARNING,
   ERROR,
   INFO
};


/**
 * Copy and convert every char in a string to their upper case form.
 *
 * @param buffer A string whose characters need to be converted to upper case form.
 * @return A string which is a copy of the src with every character capitalized.
 */
string toUpperCase(string src);


/**
 * Set current logging level
 */
void setLoggingLevel(loglevel_t logLevel);


/**
 * Output debug log message to current stdout.
 *
 * @param func the name of the running function.
 * @param msg  log message
 */
void debug(string func, string msg);


/**
 * Output info log message to current stdout.
 *
 * @param func the name of the running function.
 * @param msg  log message
 */
void info(string func, string msg);


/**
 * Output warning log message to current stdout.
 *
 * @param func the name of the running function.
 * @param msg  log message
 */
void warning(string func, string msg);


/**
 * Output error log message to current stdout.
 *
 * @param func the name of the running function.
 * @param msg  log message
 */
void error(string func, string msg);
#endif /** end of include guard:  */
