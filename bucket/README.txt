------------------------------------
PROGRAM: BucketSort
Author : Jason Qiao Meng
ID     : 10652564
Email  : jason.meng@sju.edu
-----------------------------------

Description
-----------
This program demonstrates bucket sort
This program is written in C++, -std=c++11 must be turn on
when compiling.


Files and Directories
---------------------
The header files are named with .hpp other than .h extension
only because my Atom editor identify .h files as C headers.

headers                                 // headers
  |- bucket.hpp                         // class Bucket
  |- bucketsort.hpp                     // class BucketSort
  |- logging.hpp                        // functions for logging for testing
  |- unittests.hpp                      // unit tests
  |- utils.hpp                          // some helper functions
logging.cpp                             // logging func implementation
main.cpp                                // main program execution entry point
README.txt                              // This file
unittests.cpp                           // unit test cases
unittestsuite.cpp                       // unit test case execution entry point
utilities.cpp                           // helper func implementation
build.sh                                // Build tool for Linux
build.bat                               // Build tool for Windows (This tool requires GNU C/C++ toolchain installed)


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
    # g++ -std=c++11 -DGRAD -DEXTRA_CREDIT -Wall -o unittests.exe unittests.cpp logging.cpp utilities.cpp unittestsuite.cpp
    # g++ -O2 -std=c++11 -Wall -DGRAD -DEXTRA_CREDIT -o bucketsort utilities.cpp main.cpp logging.cpp 


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
The recommended one is CYGWIN.
This program has been tested with a CYGWIN environment too.


[EOF]
