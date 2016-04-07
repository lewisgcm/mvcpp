add_executable ( RequestBenchmark request/source.cpp )
add_executable ( RouteBenchmark   route/source.cpp )

find_package( Boost REQUIRED COMPONENTS system )

target_link_libraries ( RequestBenchmark LINK_PUBLIC mvcpp pthread ${Boost_SYSTEM_LIBRARY} )
target_link_libraries ( RouteBenchmark   LINK_PUBLIC mvcpp pthread ${Boost_SYSTEM_LIBRARY} )