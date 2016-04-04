add_executable ( RequestBenchmark request/source.cpp )
add_executable ( RouteBenchmark   route/source.cpp )

target_link_libraries ( RequestBenchmark LINK_PUBLIC mvcpp pthread boost_system )
target_link_libraries ( RouteBenchmark   LINK_PUBLIC mvcpp pthread boost_system )