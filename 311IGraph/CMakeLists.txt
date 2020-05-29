cmake_minimum_required(VERSION 3.15)
project(311IGraph)

set(CMAKE_CXX_STANDARD 14)

add_executable(311IGraph main.cpp headers/IGraph.h headers/ListGraph.h src/ListGraph.cpp headers/MatrixGraph.h src/MatrixGraph.cpp headers/SetGraph.h src/SetGraph.cpp headers/ArcGraph.h src/ArcGraph.cpp)