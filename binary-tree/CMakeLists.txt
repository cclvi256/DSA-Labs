cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 11)

project(BinaryTree)

include_directoryies(${CMAKE_CURRENT_SOURCE_DIR})
file(GLOB SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_executable(BinaryTree ${SRC_LIST})
