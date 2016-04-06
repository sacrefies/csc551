#!/bin/bash
g++ -std=c++11 -O3 -o ptsp brutes.cpp logging.cpp utilities.cpp main.cpp -Wall -O3 -DGRAD -DEXTRA_CREDIT_RECURSIVE -DEXTRA_CREDIT_NON_RECURSIVE
echo "DONE"
echo "The runnable: ./main"
