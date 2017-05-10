cmake_minimum_required(VERSION 3.7)
project(prim)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        #headers/args.h
        headers/Vertex.h
        headers/Prim.h
        headers/logging.h
        headers/debugutils.h
        headers/unittest.h
        #arguments.cpp
        logging.cpp
        #main.cpp
        testRunner.cpp
        unittest.cpp)

add_executable(testRunner ${SOURCE_FILES})
