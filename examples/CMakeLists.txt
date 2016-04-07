add_executable ( FileServerExample file-server/file-server.cpp )
add_executable ( RouterExample     router/router.cpp )

find_package( Boost REQUIRED COMPONENTS system )

target_link_libraries ( FileServerExample LINK_PUBLIC mvcpp pthread ${Boost_SYSTEM_LIBRARY} )
target_link_libraries ( RouterExample     LINK_PUBLIC mvcpp pthread ${Boost_SYSTEM_LIBRARY} )