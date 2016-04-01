/**
 * (c) Lewis Maitland 2015
*/
#pragma once

#include <cstdint>
#include <Database/Repository.hpp>
#include <Database/Model/User.hpp>
#include <Exception/HttpException.hpp>

namespace Repository {
    class UserRepository : public Repository<User> {
    public:
        User find( int32_t id );

        User create( User& user );

        void update( const User& user );

        void remove( int32_t id );

        vector<User> range( uint32_t start = 0, uint32_t end = 100 );

        uint32_t count();
    };
}