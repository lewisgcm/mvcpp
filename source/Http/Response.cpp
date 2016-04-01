/**
 * (c) Lewis Maitland 2015
*/
#include <Http/Response.hpp>

namespace Http {

    Response::Response( HttpVersion version, HttpHeaders headers, ostream& out ) noexcept
    : out_( out ) {
        version_ = version;
        headers_ = headers;
    }

    void Response::send( HttpStatus code ) {
        if( out_.tellp() == 0 ) {
            cout << Http::HttpVersionString.at( version_ ) << " " << Http::HttpResponseStrings.at( code ) << "\r\n";
            for( auto& header : headers_ ) {
                cout << header.first << ": " << header.second << "\r\n";
            }
            cout << "\n\r";
        }
    }
}