#!/bin/bash
g++ -O2 -std=c++11 -Wall -DGRAD -DEXTRA_CREDIT -o bucketsort utilities.cpp main.cpp logging.cpp
echo "DONE"
echo "The runnable: ./bucketsort"
