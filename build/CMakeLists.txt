cmake_minimum_required(VERSION 3.8)

SET(CMAKE_C_COMPILER /usr/bin/clang)
SET(CMAKE_CXX_COMPILER /usr/bin/clang++)

set(dir ${CMAKE_CURRENT_SOURCE_DIR}/..)
set(EXECUTABLE_OUTPUT_PATH ${dir}/bin)

project(Graph)
file(GLOB src ${dir}/src/*.cpp)
include_directories(${dir}/include)

add_executable(Graph ${src})
