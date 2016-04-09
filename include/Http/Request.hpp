/*
 *  (c) Lewis Maitland 2015
*/
#pragma once

#include <vector>
#include <streambuf>
#include <iostream>
#include <sstream>
#include <streambuf>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <json.hpp>
#include <Log/Log.hpp>
#include <Exception/Exception.hpp>
#include <Exception/HttpException.hpp>
#include <Http/Http.hpp>
#include <Http/Query.hpp>

using namespace std;
using json = nlohmann::json;

namespace Http {

    /**
     * Request.
     * Class for encapsulating HTTP Requests.
     * This class when instantiated can either parse a request from an istream
     * or be instantiated with the correct parameters to build a request object. 
    */
    class Request {

        HttpMethod method_;
        HttpVersion version_;
        HttpHeaders headers_;
        string body_;
        Query query_;
        
    public:

        /**
         * Constructor.
         * This constructor parses the supplied istream to build a request object
         * @param[in] stream Stream to parse
         * @exception 
        */
        Request( istream& stream );

        /**
         * getMethod.
         * Gets the method of the HTTP request
         * @return HttpMethod of the request
        */
        HttpMethod getMethod() noexcept;

        /**
         * getVersion.
         * Gets the version of the HTTP request 
         * @return HttpVersion of the request
        */
        HttpVersion getVersion() noexcept;

        /**
         * getQuery.
         * Get the query of the request (includes query parameters)
         * @return Reference to the request query
        */
        Query& getQuery() noexcept;

        /**
         * getContentType.
         * Get the content type for the request.
         * @return string type of request or empty string if not specified
        */
        string getContentType() noexcept;

        /**
         * getBody.
         * This version of get body will parse an incoming json
         * request and return the approipriate model.
         * @return Object of the apprioriate type (if it has json serialization)
        */
        template<typename T>
        T getBody() {
            return T( json::parse( body_ ) );
        }

        /**
         * getBody.
         * Get the body of the HTTP request
         * @return Reference to the body of the request
        */
        string& getBody() noexcept;

        /**
         * getHeaders.
         * Get the headers of the HTTP request.
         * @return Reference to HttpHeaders for the request
        */
        HttpHeaders& getHeaders() noexcept;

    private:

        /**
         * HTTP Request parse.
         * This function is used to parse a HTTP request object from the given istream.
         * @param[in] stream Stream to parse the HTTP request from
        */
        bool parse( istream& stream );
    };
}