/**
 * (c) Lewis Maitland 2015
*/
#include <Routing/Router.hpp>

namespace Routing {

    Router::Router() {
        
    }

    Router::Router( const vector<Route> routes ) {
        routes_ = routes;
    }

    void Router::handleRequest( Http::Request& request, Http::Response& response ) {

        for( Route route : routes_ ) {
            if( route.matchRoute( request.getMethod(), request.getQuery().getPath() ) ) {
                route.setQueryRouteParams( request.getQuery() );
                route.getAction()( request, response );
                return;
            }
        }

        Log::Error( "No matching route for path {%s}.", request.getQuery().getPath().c_str() );
        throw Exception::HttpException( Http::NOT_FOUND );
    }
}