------------------------------------
PROGRAM: maxsub
Author : Jason Qiao Meng
ID     : 10652564
Email  : jason.meng@sju.edu
-----------------------------------

Description
-----------
This program contains implementations of a set of max-sub searching functions.
This program is written in C++.

There are 4 different algorithm implementations included, and they all are
defined in header/maxSumSubarray.h:

  1. bruteForce_n2          O(n^2) time complexity
  2. bruteForce_n3          O(n^3) time complexity
  3. find_maximum_subarray  O(n*lg(n)) time complexity
  4. Kadane                 O(n) time complexity


Files and Directories
---------------------
headers                                 // headers
  |- arrayUtils.h                       // Some utility functions for array
  |- logging.h                          // Logging function definitions
  |- maxSumSubarray.h                   // max-sub function definitions
  |- unitTests.h                        // Unit test function definitions
arrayUtils.cpp
bruteForce.cpp
kadane.cpp
logging.cpp
recursive.cpp
testRunner.cpp
unitTests.cpp
README.txt                              // This file
build_test.sh                           // unit test runner builder for Linux
build_test.bat                          // unit test runner builder for Windows (This tool requires GNU C/C++ toolchain installed)


To Compile
-----------
This program is developed and runs only on Linux.

1. Unizp the package and save the directories under a certain directory, i.e.: ~\source.
2. Launch a terminal environment, change current directory to ~\source.
3. Run build.sh
    $ ./build.sh
4. In case on Windows:
    build.bat

To Run
------
The command is as below:
[Main program runner]
    ./main -n <num_of_arrays> -m <max_sub_func_name>
E.g.: ./main -n 10 -m kadane

[The unit test runner]
    ./testRunner -l debug
    ./testRunner -l info
    ./testRunner


[EOF]
