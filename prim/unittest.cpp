//
// Created by Jason on 5/8/2017.
//

#include <string>
#include <queue>
#include <set>
#include <exception>

#include "headers/logging.h"
#include "headers/Prim.h"
#include "headers/unittest.h"


using std::to_string;
using std::string;
using std::exception;
using std::runtime_error;

/// Verify whether 2 double values are equal.
/// \param a One double value
/// \param b The otehr double value
/// \return Returns true if the 2 doubles are equal.
static bool closeEnough(double a, double b) {
    double diff = a - b;
    if (diff < 0) diff = -diff;
    return diff < 1e-4;
}

/// Verify whether the Prim algorithm implementation can produce correct result.
/// \param filePath The data file path, relative or absolute.
/// \param expected The expected MST cost.
/// \return Returns true if the implementation returns the expected.
bool test_file_prim(const string filePath, const double expected) {
    info(__func__, "***** Test Case: Verify the Kruskal algorithm");
    Prim *k = nullptr;
    debug(__func__, "data file: " + filePath);
    debug(__func__, "the expected:" + to_string(expected));
    string msg = "";
    bool rt = false;
    try {
        info(__func__, "Init Kruskal with the data file: " + filePath);
        k = new Prim(filePath);
        k->process();
        double actual = k->getMSTCost();
        debug(__func__, "k->getMSTCost()=" + to_string(actual));
        if (false == closeEnough(actual, expected)) {
            msg = "The implementation returns wrong result.\n";
            msg += "The expected=" + to_string(expected);
            msg += " the actual=" + to_string(actual);
            throw runtime_error(msg);
        }
        rt = true;
        delete k;
    } catch (exception &e) {
        if (k != nullptr)
            delete k;
        error(__func__, e.what());
        rt = false;
    }
    k = nullptr; // kill the dangling pointer.
    msg = (rt == true) ? "Passed" : "Failed";
    info(__func__, "Test Finished: " + msg);
    info("", "");
    return rt;
}
