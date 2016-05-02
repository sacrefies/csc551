------------------------------------
PROGRAM: Prim's MST
Author : Jason Qiao Meng
ID     : 10652564
Email  : jason.meng@sju.edu
-----------------------------------

Description
-----------
A C++ implementation of Prim's MST (min spanning tree) algorithm.

This program is developed, compiled and verified/run on top of a WINNT system
with g++ from CYGWIN environment. It's compatible by nature with a POSIX system
simply by a recompilation.

This program is written in C++, -std=c++11 must be turn on when compiling.


Files and Directories
---------------------
The header files are named with .hpp other than .h extension
only because my Atom editor identify .h files as C headers.

headers                                 // headers
  |- args.hpp
  |- Prim.hpp                           // Prim algorithm implementation
  |- Vertex.hpp                         // Vertex class
  |- logging.hpp                        // logging facility
test_data
  |- 1000EWG.txt
  |- 10000EWG.txt
  |- largeEWG.txt
  |- mediumEWG.txt
  |- tinyEWG.txt
arguments.cpp                           // command line argument handler
logging.cpp                             // logging func implementation
main.cpp                                // main program execution entry point
build.sh                                // Build tool for Linux
README.txt                              // This file


To Compile
-----------
This program is developed and runs only on Linux.

1. Unizp the package and save the directories under a certain directory, i.e.: ~/source.
2. Launch a terminal environment, change current directory to ~/source.
3. Run build.sh
    # . ./build.sh
4. Or run g++ directly:
    # g++ -O2 -std=c++11 -Wall -o prim main.cpp logging.cpp arguments.cpp


To Run
------
The command is as below:
    # ./prim -f test_data/tinyEWG.txt
    # ./prim -f test_data/tinyEWG.txt -l debug    // verbose screen output
Also, run command below to get more argument description:
    # ./prim -h


WINDOWS
-------
To compile and run on Window successfully, some third-party POSIX porting
environment are required. The recommended is CYGWIN.
This program has been tested with a CYGWIN environment too.


[EOF]
