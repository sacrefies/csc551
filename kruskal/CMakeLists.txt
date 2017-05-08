cmake_minimum_required(VERSION 3.7)
project(kruskal)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        headers/args.h
        headers/Edge.h
        headers/Kruskal.h
        headers/logging.h
        #headers/unittest.h
        arguments.cpp
        logging.cpp
        main.cpp
        #unittest.cpp
        #testRunner.cpp)

add_executable(kruskal ${SOURCE_FILES})
