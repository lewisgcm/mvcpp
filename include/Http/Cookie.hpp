/*
 *  (c) Lewis Maitland 2015
*/
#pragma once

#include <string>
#include <map>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <Log/Log.hpp>
#include <Exception/HttpException.hpp>

using namespace std;

namespace Http {

    class Cookie {
        map< string, string > data_;

        bool parse( const string &cookie );

    public:

        Cookie();

        Cookie( const string &cookie );

        bool has( string key );

        string get( string key );

        template <typename T> T get( string key ) {
            return boost::lexical_cast<T>( this->get( key ) );
        }

        template <typename T> void set( string key, T item ) {
            data_[ key ] = boost::lexical_cast<string>( item );
        }

        void set( string key, string value );

        friend ostream& operator<<(ostream& os, const Cookie& cookie);
    };
}