/**
 * (c) Lewis Maitland 2015
*/
#include <Exception/HttpException.hpp>

namespace Exception {
    HttpException::HttpException( Http::HttpStatus statusCode ) : Exception( "" ) {
        this->statusCode = statusCode;
        this->message = Http::HttpResponseStrings.at( statusCode );
    }

    Http::HttpStatus HttpException::getStatusCode() {
        return this->statusCode;
    }
}