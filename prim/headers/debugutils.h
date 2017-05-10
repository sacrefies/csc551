//
// Created by Jason on 5/9/2017.
//

#include <string>
#include <iostream>
#include <iomanip>
#include <limits>
#include <typeinfo>

#include "logging.h"

#ifndef PRIM_DEBUGUTILS_H
#define PRIM_DEBUGUTILS_H

using std::cout;
using std::endl;
using std::flush;
using std::setw;
using std::setprecision;
using std::string;
using std::to_string;
using std::numeric_limits;

/// Print an array to DEBUG log level.
///
/// \tparam T The element type in the array
/// \param tag The tag of this line of log.
/// \param list The array
/// \param size the length of the array
template<typename T>
void debugPrintArray(string tag, T *list, int size);

/// Print a matrix (2d array) to DEBUG log level
///
/// \tparam T The element type in the matrix
/// \param matrix The matrix
/// \param tag The tag of this line of log.
/// \param matrixSize the size of the matrix.
template<typename T>
void debugPrintMatrix(string tag, T **matrix, int matrixSize);

/// Print an array to DEBUG log level.
///
/// \tparam T The element type in the array
/// \param tag The tag of this line of log.
/// \param list The array
/// \param size the length of the array
template<typename T>
void debugPrintArray(string tag, T *list, int size) {
    if (level <= DEBUG) {
        cout << getFormattedTime() << " - ";
        cout << setw(5) << "DEBUG" << " - ";
        printTag(tag);
        string msg = "Print array ===> ";
        if (list == nullptr || size < 1)
            msg += "NULL";
        else {
            cout << endl << flush;
            cout << getFormattedTime() << " - ";
            cout << setw(5) << "DEBUG" << " - ";
            printTag(tag);
            msg += "[";
            for (int i = 0; i < size; ++i) {
                if (typeid(double) == typeid(list[i]) &&
                    numeric_limits<double>::max() == list[i])
                    msg += "MAX";
                else msg += to_string(list[i]);
                msg += ",";
            }
            msg = msg.substr(0, msg.length() - 1) + "]";
        }
        cout << msg << endl << flush;
    }
}

/// Print a matrix (2d array) to DEBUG log level
///
/// \tparam T The element type in the matrix
/// \param matrix The matrix
/// \param tag The tag of this line of log.
/// \param matrixSize the size of the matrix.
template<typename T>
void debugPrintMatrix(string tag, T **matrix, int matrixSize) {
    if (level <= DEBUG) {
        cout << getFormattedTime() << " - ";
        cout << setw(5) << "DEBUG" << " - ";
        printTag(tag);
        cout << "Print Matrix ===>" << endl << flush;
        if (matrix == nullptr || matrixSize < 1) {
            printTag(tag);
            cout << "The given matrix is NULL." << endl << flush;
            return;
        }
        for (int i = 0; i < matrixSize; ++i)
            debugPrintArray<T>(tag, matrix[i], matrixSize);
    }
}

#endif // PRIM_DEBUGUTILS_H
