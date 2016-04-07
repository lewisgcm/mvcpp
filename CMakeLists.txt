cmake_minimum_required(VERSION 3.2.2)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Release)

project(mvcpp)

set(CMAKE_C_COMPILER "g++-4.9")
set(CMAKE_CXX_COMPILER "g++-4.9")

#Bring the headers, such as Student.h into the project
include_directories(include submodules/json/src)
 
#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "source/**/*.cpp")
file(GLOB TEST_SOURCES "test/**/*.cpp" "test/test.cpp")
 
#add_library(mvcppa STATIC ${SOURCES})
#target_include_directories (mvcppa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(mvcpp SHARED ${SOURCES})
target_include_directories (mvcpp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

##Unit Testing
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(test)
add_executable ( UnitTest ${TEST_SOURCES} )
target_link_libraries ( UnitTest LINK_PUBLIC mvcpp boost_system cppunit ${GTEST_BOTH_LIBRARIES} pthread )
add_custom_command(
    TARGET UnitTest
    POST_BUILD
    COMMAND UnitTest
)

add_subdirectory (benchmarking)
add_subdirectory (examples)