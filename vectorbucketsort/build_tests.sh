#!/bin/bash
g++ -std=c++11 -O3 -DGRAD -DEXTRA_CREDIT -Wall -o unittests logging.cpp utilities.cpp unittestsuite.cpp unittests.cpp unittests_grad.cpp unittests_grad_extra.cpp
echo "DONE"
echo "The runnable: ./unittests"
