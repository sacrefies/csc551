cmake_minimum_required(VERSION 3.7)
project(sorts)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        headers/sorts.h
        headers/timing.h
        insertionSort.cpp
        mergeSort.cpp
        selectionSort.cpp
        sortMain.cpp
        timing.cpp quickSort.cpp)

add_executable(sorts ${SOURCE_FILES})
