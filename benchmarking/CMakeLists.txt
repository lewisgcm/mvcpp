add_executable ( Request request/source.cpp )
add_executable ( Route   route/source.cpp )

target_link_libraries ( Request LINK_PUBLIC mvcpp pthread boost_system )
target_link_libraries ( Route   LINK_PUBLIC mvcpp pthread boost_system )