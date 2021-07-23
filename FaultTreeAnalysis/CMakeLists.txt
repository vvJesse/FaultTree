cmake_minimum_required(VERSION 3.15)
project(FTA_BDD)

set(CMAKE_CXX_STANDARD 14)

file(GLOB SOURCES
        BDD.h						//*号对应具体的文件名
        BDD.cpp
        BDD_node.h
        BDD_node.cpp
        FaultTree.h
        FaultTree.cpp
        node.h
        node.cpp
        )

add_executable(ChainList main.cpp ${SOURCE_FILES} ${SOURCES})