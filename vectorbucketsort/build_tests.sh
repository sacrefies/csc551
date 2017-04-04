#!/bin/bash
g++ -std=c++11 -DGRAD -DEXTRA_CREDIT -Wall -o unittests unittests.cpp logging.cpp utilities.cpp unittestsuite.cpp
echo "DONE"
echo "The runnable: ./unittests"
