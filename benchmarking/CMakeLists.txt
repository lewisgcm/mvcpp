add_executable ( RequestBenchmark request/source.cpp )
add_executable ( RouteBenchmark   route/source.cpp )

target_link_libraries ( RequestBenchmark LINK_PUBLIC mvcpp ${CMAKE_THREAD_LIBS_INIT} ${Boost_SYSTEM_LIBRARY} )
target_link_libraries ( RouteBenchmark   LINK_PUBLIC mvcpp ${CMAKE_THREAD_LIBS_INIT} ${Boost_SYSTEM_LIBRARY} )