add_executable ( FileServer file-server/file-server.cpp )
add_executable ( Router     router/router.cpp )

target_link_libraries ( FileServer LINK_PUBLIC mvcpp pthread boost_system )
target_link_libraries ( Router     LINK_PUBLIC mvcpp pthread boost_system )