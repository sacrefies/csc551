#!/usr/bin/env bash
g++ -O3 -std=c++11 -Wall -o testRunner testRunner.cpp unittest.cpp logging.cpp
echo "DONE"
echo "The runnable: ./testRunner"
