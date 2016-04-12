add_executable ( FileServerExample file-server/file-server.cpp )
add_executable ( RouterExample     router/router.cpp )
add_executable ( FastExample       fast/fast.cpp )

target_link_libraries ( FileServerExample LINK_PUBLIC mvcpp ${CMAKE_THREAD_LIBS_INIT} ${Boost_SYSTEM_LIBRARY} )
target_link_libraries ( RouterExample     LINK_PUBLIC mvcpp ${CMAKE_THREAD_LIBS_INIT} ${Boost_SYSTEM_LIBRARY} )
target_link_libraries ( FastExample     LINK_PUBLIC mvcpp ${CMAKE_THREAD_LIBS_INIT} ${Boost_SYSTEM_LIBRARY} )