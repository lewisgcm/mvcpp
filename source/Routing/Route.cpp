/**
 * (c) Lewis Maitland 2015
*/
#include <Routing/Route.hpp>

namespace Routing {

    Route::Route( Http::HttpMethod method, string path, ControllerAction action ) {
        method_ = method;
        action_ = action;

        string path_;

        regex param_regex("\\{([A-Za-z]+)\\}");
        regex_iterator<string::iterator> end;
        regex_iterator<string::iterator> match( path.begin(), path.end(), param_regex );
        while( match != end ) {
            path_params_.push_back( (*match)[1] );
            match++;
        }
        path_ = regex_replace ( path, param_regex, "(.+)" );
        path_regex_ = regex( path_ );
    }

    ControllerAction Route::getAction() noexcept {
        return action_;
    }

    bool Route::matchRoute( Http::HttpMethod method, string path ) {
        return method == method_ && regex_match( path, path_regex_ );
    }

    void Route::setQueryRouteParams( Http::Query& query ) {
        map<string, string> params;
        smatch match;
        string path = query.getPath();
        regex_match( path, match, path_regex_ );

        for(unsigned int i=0; i < path_params_.size(); i++) {
            params[ path_params_[i] ] = std::string(match[i+1]);
        }

        query.addParams( params );
    }
}