cmake_minimum_required(VERSION 3.8)

project(Huffman)
set(CMAKE_CXX_STANDARD 11)
file(GLOB SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(Huffman ${SRC_LIST})
