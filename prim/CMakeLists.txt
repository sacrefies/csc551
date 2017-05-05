cmake_minimum_required(VERSION 3.7)
project(prim)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        headers/args.h
        headers/Vertex.h
        headers/Prim.h
        headers/logging.h
        arguments.cpp
        logging.cpp
        main.cpp)

add_executable(prim ${SOURCE_FILES})
