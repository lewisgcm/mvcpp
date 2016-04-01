/*
 *  (c) Lewis Maitland 2015
*/
#pragma once

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <map>
#include <stdlib.h>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <Log/Log.hpp>
#include <Exception/HttpException.hpp>

using namespace std;

namespace Http {

    /**
     * Query.
     * Class for parsing and encapsulating a HTTP query.
     * This class stores and resolves HTTP queries.
    */
    class Query {

        string path_;
        map<string, string> params_;

    public:

        /**
         * Default constructor.
         * Constructs an empty query object.
        */
        Query();

        /**
         * Constructor.
         * Parses the HTTP query from the given string to produce query object.
         * @param[in] query Query string to parse into query object
        */
        Query( string query );

        /**
         * getParam.
         * Template function allowing for retrieval of query
         * parameters as different types.
         * @param[in] param Parameter to get
        */
        template <typename T> T getParam( string param ) {
            return boost::lexical_cast<T>( getParam(param) );
        }

        /**
         * getParam.
         * Returns the query parameter or empty string if it does
         * not exist. eg /test?hello=world, would have param hello.
         * @param[in] param Name of the parameter in the query url
         * @return The parameter value or "" if it does not exist
        */
        string getParam( string param );

        /**
         * hasParam.
         * Returns a boolean indicating if the query has a parameter
         * or not.
         * @param[in] param Name of the parameter in the query url
         * @return true if the parameter exists or false if it does not
        */
        bool hasParam( string param ) noexcept;

        /**
         * getPath.
         * Get the base path of of the query with no
         * parameters appended.
         * @return Path of the query with no parameters
        */
        string getPath() noexcept;

        /**
         * addParams.
         * Inserts a key/value map of parameters into the 
         * query parameters. This is used for adding parameters
         * resolved from a route.
         * @param[in] params Map of parameters to add
        */
        void addParams( map<string, string> params );

    private:

        /**
         * parse.
         * This function is used to parse the query string into a query object
         * @param[in] query Query to parse
        */
        bool parse( string query );
    };

};