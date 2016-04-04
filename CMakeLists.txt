cmake_minimum_required(VERSION 3.2.2)
set (CMAKE_CXX_STANDARD 11)

project(mvcpp)

set(CMAKE_C_COMPILER "g++-4.9")
set(CMAKE_CXX_COMPILER "g++-4.9")

#Bring the headers, such as Student.h into the project
include_directories(include submodules/json/src)
 
#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "source/**/*.cpp")
 
#add_library(mvcppa STATIC ${SOURCES})
#target_include_directories (mvcppa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(mvcpp SHARED ${SOURCES})
target_include_directories (mvcpp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory (benchmarking)
add_subdirectory (examples)