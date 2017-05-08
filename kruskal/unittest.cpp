//
// Created by Jason on 5/8/2017.
//

#include <string>
#include <queue>
#include <set>
#include <exception>

#include "headers/logging.h"
#include "headers/Kruskal.h"
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

/// Verify whether the vertex count is initialized correctly.
/// \return Returns true if the vertex count is correct.
bool test_init_vertices() {
    info(__func__, "***** Test Case: Vertex count init");
    Kruskal *k = nullptr;
    int verts = 6;
    debug(__func__, "set vertices: " + to_string(verts));
    string msg = "";
    bool rt = false;
    try {
        info(__func__, "Init Kruskal with vertices count: " + to_string(verts));
        k = new Kruskal(verts);
        if (k->getVertexCount() != verts) {
            msg = "The vertex count is wrong. \n";
            msg += "The expected=" + to_string(verts);
            msg += " the actual=" + to_string(k->getVertexCount());
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
    k = nullptr;
    msg = (rt == true) ? "Passed" : "Failed";
    info(__func__, "Test Finished: " + msg);
    return rt;
}

/// Verify whether the sets are initialized correctly.
/// \return Returns true if the the sets are initialized correctly.
bool test_init_diagonal() {
    info(__func__, "***** Test Case: Set init diagonal");
    Kruskal *k = nullptr;
    int verts = 6;
    debug(__func__, "set vertices: " + to_string(verts));
    string msg = "";
    bool rt = false;
    try {
        info(__func__, "Init Kruskal with vertices count: " + to_string(verts));
        k = new Kruskal(verts);
        for (int i = 0; i < verts; i++) {
            if (false == k->sameSet(i, i)) {
                msg = "The sameSet(" + to_string(i) + ", " + to_string(i) + ")";
                msg += " method returns wrong result. \n";
                msg += "The expected=true, the actual=false";
                throw runtime_error(msg);
            }
        }
        rt = true;
        delete k;
    } catch (exception &e) {
        if (k != nullptr)
            delete k;
        error(__func__, e.what());
        rt = false;
    }
    k = nullptr;
    msg = (rt == true) ? "Passed" : "Failed";
    info(__func__, "Test Finished: " + msg);
    return rt;
}

/// Verify whether the sets are initialized correctly.
/// \return Returns true if the the sets are initialized correctly.
bool test_init_off_diagonal() {
    info(__func__, "***** Test Case: Set init off diagonal");
    Kruskal *k = nullptr;
    int verts = 6;
    debug(__func__, "set vertices: " + to_string(verts));
    string msg = "";
    bool rt = false;
    try {
        info(__func__, "Init Kruskal with vertices count: " + to_string(verts));
        k = new Kruskal(verts);
        for (int r = 0; r < verts; r++) {
            for (int c = 0; c < verts; c++) {
                if (r == c) continue;
                if (true == k->sameSet(r, c) || true == k->sameSet(c, r)) {
                    msg = "The sameSet(" + to_string(r) + ", " + to_string(c) + ")";
                    msg += " method returns wrong result. \n";
                    msg += "The expected=false, the actual=true";
                    throw runtime_error(msg);
                }
            }
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
    return rt;
}

/// Verify whether the sets are initialized correctly.
/// \return Returns true if the the sets are initialized correctly.
bool test_same_set() {
    info(__func__, "***** Test Case: Set init correctly");
    Kruskal *k = nullptr;
    int verts = 6;
    debug(__func__, "set vertices: " + to_string(verts));
    string msg = "";
    bool rt = false;
    try {
        info(__func__, "Init Kruskal with vertices count: " + to_string(verts));
        k = new Kruskal(verts);
        for (int r = 0; r < verts; r++) {
            for (int c = 0; c < verts; c++) {
                if (r == c && false == k->sameSet(r, c)) {
                    msg = "The sameSet(" + to_string(r) + ", " + to_string(c) + ")";
                    msg += " method returns wrong result. \n";
                    msg += "The expected=true, the actual=false";
                    throw runtime_error(msg);
                } else if (r != c && (true == k->sameSet(r, c) || true == k->sameSet(c, r))) {
                    msg = "The sameSet(" + to_string(r) + ", " + to_string(c) + ")";
                    msg += " method returns wrong result. \n";
                    msg += "The expected=false, the actual=true";
                    throw runtime_error(msg);
                }
            }
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
    return rt;
}

/// Verify whether the Kruskal algorithm implementation can produce correct result.
/// \param filePath The data file path, relative or absolute.
/// \param expected The expected MST cost.
/// \return Returns true if the implementation returns the expected.
bool test_file_kruskal(const string filePath, const double expected) {
    info(__func__, "***** Test Case: Verify the Kruskal algorithm");
    Kruskal *k = nullptr;
    debug(__func__, "data file: " + filePath);
    debug(__func__, "the expected:" + to_string(expected));
    string msg = "";
    bool rt = false;
    try {
        info(__func__, "Init Kruskal with the data file: " + filePath);
        k = new Kruskal(filePath);
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
    return rt;
}
