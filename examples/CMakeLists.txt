add_executable ( FileServerExample file-server/file-server.cpp )
add_executable ( RouterExample     router/router.cpp )

target_link_libraries ( FileServerExample LINK_PUBLIC mvcpp pthread boost_system )
target_link_libraries ( RouterExample     LINK_PUBLIC mvcpp pthread boost_system )