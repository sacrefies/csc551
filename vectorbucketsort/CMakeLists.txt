cmake_minimum_required(VERSION 3.7)
project(vectorbucketsort)

set(CMAKE_CXX_STANDARD 11)

add_definitions(-DGRAD)

add_definitions(-DEXTRA_CREDIT)

set(SOURCE_FILES
        headers/logging.h
        headers/unittests.h
        headers/utils.h
        headers/VectorBucketSort.h
        headers/unittests_grad.h
        headers/unittests_grad_extra.h
        logging.cpp
        unittests.cpp
        unittestsuite.cpp
        utilities.cpp
        unittests_grad.cpp
        unittests_grad_extra.cpp )

add_executable(vectorbucketsort ${SOURCE_FILES})
