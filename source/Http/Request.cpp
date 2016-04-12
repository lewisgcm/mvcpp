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

    Cookie& Request::getCookie() noexcept {
        return cookie_;
    }

    HttpHeaders& Request::getHeaders() noexcept {
        return headers_;
    }

    string Request::getContentType() noexcept {
        return headers_[ "content-type" ];
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

        StringSplitter tokens;
        tokens.split( line, " " );
        if( tokens.size() != 3 ) {
            Log::Warning("Request status line malformed {%s}.", line.c_str() );
            return false;
        }

        auto it_method  = std::find( HttpMethodString.begin(), HttpMethodString.end(), tokens.results()[0].c_str() );
        auto it_version = std::find( HttpVersionString.begin(), HttpVersionString.end(), tokens.results()[2].c_str() );

        if( it_method == HttpMethodString.end() || it_version == HttpVersionString.end() ) {
            Log::Warning("Unknown HTTP method or HTTP version");
            return false;
        }

        method_  = (HttpMethod)std::distance( HttpMethodString.begin(), it_method );
        version_ = (HttpVersion)std::distance( HttpVersionString.begin(), it_version );
        query_   = Query(tokens.results()[1].c_str());

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

            StringSplitter header;
            header.split( line, ":" );
            if( header.size() == 2 ) {
                header.results()[ 0 ].trim();
                header.results()[ 1 ].trim();
                header.results()[ 0 ].to_lower();
                header.results()[ 1 ].to_lower();
                if( strcmp( header.results()[0].c_str(), "cookie" ) == 0 ) {
                    cookie_ = Cookie( header.results()[1].c_str() );
                    continue;
                }
                headers_[ header.results()[0].c_str() ] = header.results()[1].c_str();
            }
        }

        /*Copy remainder of the stream into the body string*/
        if( headers_.find( "content-length" ) != headers_.end() ) {

            unsigned int length = boost::lexical_cast<unsigned int>( headers_[ "content-length" ] );

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