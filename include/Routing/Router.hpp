/**
 * (c) Lewis Maitland 2015
*/
#pragma once

#include <cstdlib>
#include <map>
#include <tuple>
#include <vector>
#include <string>
#include <regex>
#include <boost/regex.hpp>
#include <Log/Log.hpp>
#include <Http/Http.hpp>
#include <Http/Response.hpp>
#include <Http/Request.hpp>
#include <Routing/Route.hpp>

using namespace std;

namespace Routing {

    /**
     * Router.
     * Router class is used to handle request routing in the
     * application. All requests are passed to the appropriate
     * function for handling using the request path.
    */
    class Router {

        vector<Route> routes_;

    public:

        /**
         * Constructor.
         * This constructor takes a vector of route objects.
         * The list of route objects are then used when handling requests.
         * @param[in] routes Vector of route objects for request handling
        */
        Router( vector<Route> routes );

        /**
         * handleRequest.
         * Handles input request and maps it to the correct controller.
         * Responses can be set by sending output in the response object.
         * @param[in] request Request object parsed for incoming request
         * @param[out] response Response object to send to client connection
        */
        void handleRequest( Http::Request& request, Http::Response& response );
    };
}