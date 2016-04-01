/**
 * (c) Lewis Maitland 2015
*/
#pragma once

#include <vector>

using namespace std;

namespace Service {
    template<typename T>
    class Service {
    public:
        Service() {};

        T find( int32_t id );

        T create( T& t );

        void update( const T& t );

        void remove( int32_t id );

        vector<T> range( uint32_t start, uint32_t end );

        uint32_t count();
    };
}