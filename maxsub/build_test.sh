#!/bin/bash
g++ -std=c++98 -O3 -o testRunner testRunner.cpp unitTests.cpp recursive.cpp logging.cpp bruteForce.cpp kadane.cpp arrayUtils.cpp
echo "DONE"
echo "The runnable: ./testRunner"
