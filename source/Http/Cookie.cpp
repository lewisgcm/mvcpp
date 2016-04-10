#include <Http/Cookie.hpp>

namespace Http {

    Cookie::Cookie() {
        
    }

    Cookie::Cookie( const string &cookie ) {
        if( !parse( cookie ) ) {
            throw Exception::HttpException( BAD_REQUEST );
        }
    }

    bool Cookie::has( string key ) {
        return data_.find( key ) != data_.end();
    }

    string Cookie::get( string key ) {
        return data_[ key ];
    }

    void Cookie::set( string key, string value ) {
        data_[ key ] = value;
    }

    ostream& operator<<(ostream& os, const Cookie& cookie) {
        if( cookie.data_.empty() ) {
            return os;
        } else {
            string cookie_str = "Set-Cookie: ";
            for( auto& cookie_pair : cookie.data_ ) {
                cookie_str += cookie_pair.first + "=" + cookie_pair.second + ";";
            }
            cookie_str.pop_back();
            cookie_str+="\r\n";
            return os << cookie_str;
        }
    }

    bool Cookie::parse( const string &cookie ) {

        vector<string> parts;
        boost::split( parts, cookie, boost::is_any_of(";") );

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