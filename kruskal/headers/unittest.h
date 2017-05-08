//
// Created by Jason on 5/8/2017.
//

#include <string>

#ifndef KRUSKAL_UNITTEST_H
#define KRUSKAL_UNITTEST_H

using std::string;

/// Verify whether the vertex count is initialized correctly.
/// \return Returns true if the vertex count is correct.
bool test_init_vertices();

/// Test whether the sets are initialized correctly.
/// \return Returns true if the the sets are initialized correctly.
bool test_init_diagonal();

/// Verify whether the sets are initialized correctly.
/// \return Returns true if the the sets are initialized correctly.
bool test_init_off_diagonal();

/// Verify whether the sets are initialized correctly.
/// \return Returns true if the the sets are initialized correctly.
bool test_same_set();

/// Verify whether the Kruskal algorithm implementation can produce correct result.
/// \param filePath The data file path, relative or absolute.
/// \param expected The expected MST cost.
/// \return Returns true if the implementation returns the expected.
bool test_file_kruskal(const string filePath, const double expected);
#endif //KRUSKAL_UNITTEST_H
