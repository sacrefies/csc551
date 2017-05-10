#!/usr/bin/env bash
g++ -O3 -Wall -std=c++11 -o testRunner testRunner.cpp logging.cpp unittest.cpp
echo "DONE"
echo "The runnable: ./testRunner"
