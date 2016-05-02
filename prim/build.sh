#!/bin/bash
g++ -O2 -std=c++11 -Wall -o prim main.cpp logging.cpp arguments.cpp
echo "DONE"
echo "The runnable: ./prim"
