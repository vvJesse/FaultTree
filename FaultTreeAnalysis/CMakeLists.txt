cmake_minimum_required(VERSION 3.15)
project(FaultTreeAnalysis)

set(CMAKE_CXX_STANDARD 14)

add_executable(FaultTreeAnalysis main.cpp FaultTree.cpp FaultTree.h node.cpp node.h BDD.cpp BDD.h BDD_node.cpp BDD_node.h)