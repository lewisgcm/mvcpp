/*
 *  (c) Lewis Maitland 2015
*/
#pragma once

#include <vector>
#include <streambuf>
#include <iostream>
#include <Log/Log.hpp>
#include <Http/Http.hpp>
#include <Exception/Exception.hpp>

using namespace std;

namespace Http {

    /**
     * Response.
     * Class for encapsulating HTTP Responses.
     * This class is used to create HTTP responses from the
     * application. Version and headers can be
     * added to the response object. Piping data into the
     * response object buffers the output to the client.
    */
    class Response {

        HttpVersion version_;
        HttpHeaders headers_;
        HttpStatus status_;
        bool sent_;
        ostream& out_;

        /**
         * send.
         * Send will send the headers to the client.
        */
        void send();

    public:

        /**
         * Constructor.
         * This constructor builds a response object
         * @param[in] version HttpVersion of the response
         * @param[in] headers Default headers for response objects
         * @param[in] out ostream for writing responses to
        */
        Response( HttpVersion version, HttpHeaders headers, ostream& out ) noexcept;

        /**
         * setStatusCode
         * Set the status code for this response.
         * @param[in] status Status code of the response
        */
        void setStatusCode( HttpStatus status ) noexcept;

        /**
         * setContentType
         * Set the content type for the response.
         * @param[in] string type Content type
        */
         void setContentType( string type ) noexcept;

        /**
         * addHeaders
         * Add additional headers to the response before sending
         * @param[in] headers HttpHeaders to add to response headers.
        */
        void addHeaders( HttpHeaders headers ) noexcept;

        /**
         * Operator<<.
         * This operator to the response class is used to pipe the input
         * object directly into the output stream. This operator is used
         * as other objects etc can overload this operator for easy class
         * writing to json.
         * NOTE: If the headers have not been sent they will be sent after the
         * first write.
        */
        template<typename T>
        ostream& operator<<(T in) {
            send();
            return out_ << in;
        }
    };
}