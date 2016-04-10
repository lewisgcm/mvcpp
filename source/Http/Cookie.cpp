#include <Http/Cookie.hpp>

namespace Http {

    Cookie::Cookie( const string &cookie ) {
        if( !parse( cookie ) ) {
            throw Exception::HttpException( BAD_REQUEST );
        }
    }

    bool Cookie::has( string key ) {
        return !( data_.find( key ) == data_.end() );
    }

    string Cookie::get( string key ) {
        return data_[ key ];
    }

    template <typename T> T Cookie::get( string key ) {
        return boost::lexical_cast<T>( this->get( key ) );
    }

    template <typename T> void Cookie::set( string key, T item ) {
        data_[ key ] = boost::lexical_cast<string>( item );
    }

    bool Cookie::parse( const string &cookie ) {

        vector<string> parts;
        boost::split( parts, cookie, boost::is_any_of(";") );

        if( parts.size() == 0 ) {
            return false;
        }

        for( int i = 0; i < parts.size(); i++ ) {
            vector<string> key_values;
            boost::split( key_values, parts[i], boost::is_any_of("=") );
            if( key_values.size() == 2 ) {
                boost::trim( key_values[0] );
                boost::trim( key_values[1] );
                this->set( key_values[0], key_values[1] );
            } else {
                return false;
            }
        }

        return true;
    }
}