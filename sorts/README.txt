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
headers                                         // headers
  |- timing.h
  |- sorts.h
insertionSort.cpp
selectionSort.cpp
sortMain.cpp
timing.cpp
README.txt


To Complile
-----------
1. Unizp the package and save the directories under a certain directory, i.e.: ~\source.
2. Launch a terminal environment, change current directory to ~\source.
3. run g++ with the options:
    g++ -O3 -std=c++11 -Wstrict-overflow -Wno-missing-field-initializers -Wno-missing-field-initializers -Wall -o sortMain sortMain.cpp timing.cpp insertionSort.cpp selectionSort.cpp


To Run
------
The command is as below:
    ./sortMain -r <runs> -n <array_size> -s <sort_method>
E.g.: ./sortMain -r 500 -n 1000 -s selectionSort


[EOF]

