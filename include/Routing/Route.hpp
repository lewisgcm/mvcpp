/**
 * (c) Lewis Maitland 2015
*/
#pragma once

#include <vector>
#include <regex>
#include <Log/Log.hpp>
#include <Http/Http.hpp>
#include <Http/Response.hpp>
#include <Http/Request.hpp>
#include <Http/Query.hpp>

namespace Routing {

    /**
     * ControllerAction.
     * Typedef for pointing to the function of a controller.
     * This function must take two parameters by reference, the request and response.
    */
    typedef void (*ControllerAction)( Http::Request& request, Http::Response& response );

    /**
     * Route.
     * Route class is used to parse and handle routing requests to the system
     * by parsing the request and matching it against an internal regex. The 
     * regex is compiled during initial instantiation for increased performance.
    */
    class Route {

        Http::HttpMethod method_;
        vector<string> pathParams_;
        ControllerAction action_;
        regex pathRegex_;

    public:

        /**
         * Constructor.
         * Constructor of the route object is used to create a new routing entry.
         * The routing entry can then be used in the router for mapping requests
         * to controllers.
        */
        Route( Http::HttpMethod method, string path, ControllerAction action );

        ControllerAction getAction() noexcept;

        Http::HttpMethod getMethod() noexcept;

        /**
         * matchRoute.
         * Checks if the given path matches this route. Does not
         * parse any parameters from the path.
         * @param[in] method HttpMethod of the request
         * @param[in] path Path of the request
         * @return True if the method and path are a match for this route
        */
        bool matchRoute( Http::HttpMethod method, string path );

        /**
         * setQueryRouteParams.
         * Add parameters parsed from the route into the
         * parameters for the query. For example /test/{id} would add
         * the paramter id into the query for use in controllers.
         * @param[in,out] query Query to add the parameters to
        */
        void setQueryRouteParams( Http::Query& query );
    };
}