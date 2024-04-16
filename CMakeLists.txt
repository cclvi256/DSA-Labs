cmake_minimum_required(VERSION 3.8)

set(dir ${CMAKE_CURRENT_SOURCE_DIR})
set(RUNTIME_OUTPUT_PATH ${dir}/bin)
set(CMAKE_CXX_STANDARD 17)

project(MinimumSpanningTree)
file(GLOB src ${dir}/src/*.cpp)
include_directories(${dir}/include)

add_executable(MinimumSpanningTree ${src})
