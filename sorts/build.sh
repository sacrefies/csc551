#!/bin/bash
g++ -O3 -std=c++11 -Wstrict-overflow -Wno-missing-field-initializers -Wno-missing-field-initializers -Wall -o sortMain insertionSort.cpp selectionSort.cpp mergeSort.cpp timing.cpp sortMain.cpp
echo "DONE"
echo "The runnable: ./sortMain"
