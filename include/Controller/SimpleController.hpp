/**
 * (c) Lewis Maitland 2015
*/
#pragma once

#include <Http/Request.hpp>
#include <Http/Response.hpp>
#include <Database/Service/UserService.hpp>

namespace Controller {

    class SimpleController {
        static Service::UserService userService;
    public:
        static void all( Http::Request& request, Http::Response& response );

        static void get( Http::Request& request, Http::Response& response );

        static void create( Http::Request& request, Http::Response& response );

        static void update( Http::Request& request, Http::Response& response );

        static void remove( Http::Request& request, Http::Response& response );

        static void validation( Http::Request& request, Http::Response& response );
    };
}