/**
 * (c) Lewis Maitland 2015
*/
#include <Http/Response.hpp>

namespace Http {

    Response::Response( HttpVersion version, HttpHeaders headers, ostream& out ) noexcept
    : out_( out ) {
        version_ = version;
        headers_ = headers;
        status_  = Http::OK;
        sent_    = false;
    }

    void Response::addHeaders( HttpHeaders headers ) {
        headers_.insert( headers.begin(), headers.end() );
    }

    void Response::setStatusCode( HttpStatus status ) {
        status_ = status;
    }

    void Response::send() {
        if( !sent_ ) {
            out_ << Http::HttpVersionString.at( version_ ) << " " << status_ << " " << Http::HttpResponseStrings.at( status_ ) << "\r\n";
            for( auto& header : headers_ ) {
                out_ << header.first << ": " << header.second << "\r\n";
            }
            out_ << "\r\n";
            sent_ = true;
        }
    }
}