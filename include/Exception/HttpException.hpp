/**
 * (c) Lewis Maitland 2015
*/
#pragma once

#include <Http/Http.hpp>
#include <Exception/Exception.hpp>

using namespace std;

namespace Exception {

    /**
     * HttpException.
     * HttpException class extends Exception class to provide http
     * exception handling within the application.
    */
    class HttpException : public Exception {
    private:
        Http::HttpStatus statusCode;

    public:

        /**
         * Constructor.
         * Constructor builds HttpException using HttpStatus code
         * @param[in] statusCode HttpStatus code
        */
        HttpException( Http::HttpStatus statusCode );

        /**
         * getStatusCode.
         * Gets the HttpStatus code of the exception.
         * @return HttpStatus code
        */
        Http::HttpStatus getStatusCode();
    };
}