/**
 * (c) Lewis Maitland 2015
*/
#pragma once

#include <string>
#include <utility>
#include <vector>
#include <soci/soci.h>
#include <soci/sqlite3/soci-sqlite3.h>

using namespace std;

namespace Repository {
    template<typename T>
    class Repository {

    protected:
        static soci::session session_;

    public:
        T find( int32_t id );

        T create( T& t );

        void update( const T& t );

        void remove( int32_t id );

        vector<T> range( uint32_t start, uint32_t end );

        uint32_t count();
    };

    template<typename T>
    soci::session Repository<T>::session_( soci::sqlite3, "test.db" );
}