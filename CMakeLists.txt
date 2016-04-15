cmake_minimum_required(VERSION 3.2.2)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Release)
set(COVERAGE "FALSE" CACHE STRING "Determines wether or not gcov should be used to generate coverage.")
#Usage cmake -DCOVERAGE:STRING=TRUE .

project(mvcpp)

set(GCC_COVERAGE_COMPILE_FLAGS -fprofile-arcs -ftest-coverage)
set(GCC_COVERAGE_LINK_FLAGS    "-lgcov -fprofile-arcs")
 
#Define sources for test and library
file(GLOB SOURCES "source/**/*.cpp")
file(GLOB TEST_SOURCES "test/**/*.cpp" "test/test.cpp")

find_package( Threads )
find_package( Boost 1.54 REQUIRED COMPONENTS system )

#Include json.hpp and boost
include_directories(include submodules/json/src ${Boost_INCLUDE_DIRS} )

add_library(mvcpp SHARED ${SOURCES})
target_include_directories (mvcpp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries ( mvcpp LINK_PUBLIC ${Boost_SYSTEM_LIBRARY} )
target_compile_features( mvcpp PRIVATE cxx_auto_type cxx_lambdas )

if(("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU") AND ("${COVERAGE}" STREQUAL "TRUE"))
    message( "-- Compiling mvcpp library with code coverage." ) 
    target_compile_options( mvcpp PRIVATE "${GCC_COVERAGE_COMPILE_FLAGS}" )
    set_target_properties( mvcpp PROPERTIES LINK_FLAGS "${GCC_COVERAGE_LINK_FLAGS}" )
endif()

##Unit Testing
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(test)
add_executable ( UnitTest ${TEST_SOURCES} )

if(("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU") AND ("${COVERAGE}" STREQUAL "TRUE"))
    message( "-- Compiling UnitTest with code coverage." ) 
    target_compile_options( UnitTest PRIVATE "${GCC_COVERAGE_COMPILE_FLAGS}" )
    target_link_libraries ( UnitTest LINK_PUBLIC mvcpp ${Boost_SYSTEM_LIBRARY} ${GTEST_BOTH_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${GCC_COVERAGE_LINK_FLAGS} )
else()
    target_link_libraries ( UnitTest LINK_PUBLIC mvcpp ${Boost_SYSTEM_LIBRARY} ${GTEST_BOTH_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} )
endif()

add_custom_command(
    TARGET UnitTest
    POST_BUILD
    COMMAND UnitTest
)
#gcov CMakeFiles/mvcpp.dir/source/**/*.gcno CMakeFiles/UnitTest.dir/test/**/*.gcno
add_subdirectory (benchmarking)
add_subdirectory (examples)