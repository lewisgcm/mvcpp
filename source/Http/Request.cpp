/**
 * (c) Lewis Maitland 2015
*/
#include <Http/Request.hpp>

namespace Http {

    Request::Request( istream& stream ) {
        if( !parse( stream ) ) {
            throw Exception::HttpException( BAD_REQUEST );
        }
    }

    string& Request::getBody() noexcept {
        return body_;
    }

    HttpMethod Request::getMethod() noexcept {
        return method_;
    }

    HttpVersion Request::getVersion() noexcept {
        return version_;
    }

    Query& Request::getQuery() noexcept {
        return query_;
    }

    HttpHeaders& Request::getHeaders() noexcept {
        return headers_;
    }

    bool Request::parse( istream& stream ) {

        string line;
        getline( stream, line );

        if( line.size() > 0 ) {
            line.pop_back();
        }

        if( line.size() > Http::MAX_REQUEST_LINE_LENGTH ) {
            Log::Warning("Request exceeds maximum status line length.");
            return false;
        }

        vector<string> tokens;
        boost::split( tokens, line, boost::is_any_of(" ") );
        if( tokens.size() != 3 ) {
            Log::Warning("Request status line malformed {%s}.", line.c_str() );
            return false;
        }

        auto it_method  = std::find( HttpMethodString.begin(), HttpMethodString.end(), tokens[0] );
        auto it_version = std::find( HttpVersionString.begin(), HttpVersionString.end(), tokens[2] );

        if( it_method == HttpMethodString.end() || it_version == HttpVersionString.end() ) {
            Log::Warning("Unknown HTTP method or HTTP version");
            return false;
        }

        method_  = (HttpMethod)std::distance( HttpMethodString.begin(), it_method );
        version_ = (HttpVersion)std::distance( HttpVersionString.begin(), it_version );
        query_   = Query(tokens[1]);

        while( !stream.eof() ) {

            getline( stream, line );
            if( line.size() > 1 ) {
                line.pop_back();
            } else {
                break;
            }

            if( line.size() > Http::MAX_REQUEST_LINE_LENGTH ) {
                Log::Warning("Request exceeds maximum status line length.");
                return false;
            }

            vector<string> header;
            boost::split( header, line, boost::is_any_of(":") );
            if( header.size() == 2 ) {
                boost::trim(header[0]);
                boost::trim(header[1]);
                headers_[ header[0] ] = header[1];
            }
        }

        /*Copy remainder of the stream into the body string*/
        /*This should be handled correctly!!!*/
        if( headers_.find( "Content-Length" )    != headers_.end() ) {

            unsigned int length = boost::lexical_cast<unsigned int>( headers_[ "Content-Length" ] );

            if( length > Http::MAX_REQUEST_BODY_LENGTH ) {
                Log::Warning("Request body is larger than server allows.");
                return false;
            }

            //Copy either content length bytes or end of stream
            std::copy_n(
                istreambuf_iterator<char>(stream),
                length,
                back_inserter(body_)
            );
        }

        return true;
    }
}