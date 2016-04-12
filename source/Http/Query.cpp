/**
 * (c) Lewis Maitland 2015
*/
#include <Http/Query.hpp>

namespace Http {
    Query::Query() {
    }

    Query::Query( const string &query ) {
        if( !parse( query ) ) {
            throw Exception::HttpException( Http::BAD_REQUEST );
        }
    }

    string Query::getParam( string param ) {
        if( hasParam(param) ) {
            return params_[ param ];
        }
        return "";
    }

    void Query::addParams( map<string, string> params ) {
        params_.insert( params.begin(), params.end() );
    }

    bool Query::hasParam( string param ) noexcept {
        if( params_.find(param) == params_.end() ) {
            return false;
        }
        return true;
    }
    
    string Query::getPath() noexcept {
        return path_;
    }

    bool Query::parse( const string &query ) {

        size_t p_end = query.find("?");
        path_ = query.substr( 0, p_end );

        if( path_[0] != '/' ) {
            return false;
        }

        if( p_end+1 < query.size() ) {

            std::string query_tail = query.substr( p_end+1, string::npos );
            vector<string> pairs;
            boost::split( pairs, query_tail, boost::is_any_of("&") );

            for( string pair : pairs ) {
                vector<string> parts;
                boost::split( parts, pair, boost::is_any_of("=") );
                params_[ parts[0] ] = (parts.size()==2) ? parts[1] : "";
            }
        }

        return true;
    }
}