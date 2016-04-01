/**
 * (c) Lewis Maitland 2015
*/
#include <Routing/Route.hpp>

namespace Routing {

    Route::Route( Http::HttpMethod method, string path, ControllerAction action ) {
        method_ = method;
        action_ = action;

        smatch match;
        string path_ = path;
        while( regex_search( path, match, regex("\\{[A-Za-z]+\\}")) ) {
            path_ = path_.replace( path_.find(match[0]), match.length(0), "(.+)" );
            path  = match.suffix().str();
            string name = match[0];
            pathParams_.push_back( name.substr( 1, name.length()-2 ) );
        }
        pathRegex_ = regex( path_ );
    }

    ControllerAction Route::getAction() noexcept {
        return action_;
    }

    Http::HttpMethod Route::getMethod() noexcept {
        return method_;
    }

    bool Route::matchRoute( Http::HttpMethod method, string path ) {
        return method == method_ && regex_match( path, pathRegex_ );
    }

    void Route::setQueryRouteParams( Http::Query& query ) {
        map<string, string> params;
        smatch match;
        regex_match( query.getPath(), match, pathRegex_ );
        for(unsigned int i=0; i < match.size()-1 && i < pathParams_.size(); i++) {
            params[ pathParams_[i] ] = match[i+1];
        }
        query.addParams( params );
    }
}