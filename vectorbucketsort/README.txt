------------------------------------
PROGRAM: VectorBucketSort
Author : Jason Qiao Meng
ID     : 10652564
Email  : jason.meng@sju.edu
-----------------------------------

Description
-----------
This program demonstrates bucket sort.
This program is written in C++, -std=c++11 must be turn on when compiling.


Files
-----
headers                                 // headers
  |- VectorBucketSort.h                 // class VectorBucketSort
  |- logging.h                          // functions for logging for testing
  |- unittests.h                        // unit tests
  |- utils.h                            // some helper functions
logging.cpp                             // logging func implementation
main.cpp                                // main program execution entry point
unittests.cpp                           // unit test cases
unittestsuite.cpp                       // unit test case execution entry point
utilities.cpp                           // helper func implementation
build.sh                                // Build tool for Linux
build_tests.sh                          // Build tool for unit tesing program.
README.txt                              // This file


To Compile
-----------
This program is developed and runs only on Linux.

1. Unizp the package and save the directories under a certain directory, i.e.: ~/source.
2. Launch a terminal environment, change current directory to ~/source.
3. Run build.sh
    # . ./build.sh
4. For test executable
    # . ./build_tests.sh
5. Or run g++ directly:
    # g++ -std=c++11 -DGRAD -DEXTRA_CREDIT -Wall -o unittests unittests.cpp logging.cpp utilities.cpp unittestsuite.cpp
    # g++ -O3 -std=c++11 -Wall -DGRAD -DEXTRA_CREDIT -o bucketsort utilities.cpp main.cpp logging.cpp


To Run
------
The command is as below:
    # ./buckesort

The command for unit test runner (default log level is warning):
    # ./unittests
    # ./unittests -l debug
    # ./unittests -l info
    # ./unittests -h
    # ./unittests --help


WINDOWS
------
To compile and run on Window successfully, some third-party POSIX porting programs are required.
The recommended one is CYGWIN. This program has been tested with a CYGWIN environment too.


[EOF]
