------------------------------------
PROGRAM: sortMain
Author : Jason Qiao Meng
ID     : 10652564
Email  : jason.meng@sju.edu
-----------------------------------

Description
-----------
This program invokes functions which implement sort algorithms and profile the functions repectively.
This program is written in C++, with C11 standard.

There are 3 merge sort implementation included in mergeSort.cpp:
  1. mergeSort              In-place array item swap which beats mergeSortInnerSwap when size <= 200,
                            and which is defeated by mergeSortOuterSwap in any case.
  2. mergeSortInnerSwap     At merge step, an inner temp array is maintained.
  3. mergeSortOuterSwap     [FASTEST] At merge step, a temp array which is passed from the caller is used.
The performance difference is significant!


Files and Directories
---------------------
headers                                 // headers
  |- timing.h
  |- sorts.h
insertionSort.cpp                       // The implementation of insertion sort
selectionSort.cpp                       // The implementation of selection sort
mergeSort.cpp                           // The implementation of merge sort
sortMain.cpp                            // The program exection entrance
timing.cpp                              // The implementation of performance profiling
README.txt                              // This file
build.sh                                // Build tool for Linux
build.bat                               // Build tool for Windows (This tool requires GNU C/C++ toolchain installed)


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
    ./sortMain -r <runs> -n <array_size> -s <sort_method>
E.g.: ./sortMain -r 500 -n 1000 -s selectionSort

Merge sort commands:
  $ ./sortMain -r 100 -n 200000 -s mergeSort            // not recommended
  $ ./sortMain -r 100 -n 200000 -s mergeSortInnerSwap
  $ ./sortMain -r 100 -n 200000 -s mergeSortOuterSwap   // recommended


[EOF]
