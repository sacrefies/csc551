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


To Complile
-----------
This program is developed and runs only on Linux.

1. Unizp the package and save the directories under a certain directory, i.e.: ~\source.
2. Launch a terminal environment, change current directory to ~\source.
3. Run build.sh
    $ ./build.sh


To Run
------
The command is as below:
    ./sortMain -r <runs> -n <array_size> -s <sort_method>
E.g.: ./sortMain -r 500 -n 1000 -s selectionSort


[EOF]

