//
// Created by Jason on 5/8/2017.
//

#include <string>

#ifndef PRIM_UNITTEST_H
#define PRIM_UNITTEST_H

using std::string;

/// Verify whether the Prim algorithm implementation can produce correct result.
/// \param filePath The data file path, relative or absolute.
/// \param expected The expected MST cost.
/// \return Returns true if the implementation returns the expected.
bool test_file_prim(const string filePath, const double expected);
#endif //KRUSKAL_UNITTEST_H
