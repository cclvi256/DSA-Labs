cmake_minimum_required(VERSION 3.8)

set(dir ${CMAKE_CURRENT_SOURCE_DIR}/..)
set(EXECUTABLE_OUTPUT_PATH ${dir}/bin)

project(Template)
file(GLOB src ${dir}/src/*.cpp)
include_directories(${dir}/include)

add_executable(Template ${src})
