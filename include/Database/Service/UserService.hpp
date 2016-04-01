/**
 * (c) Lewis Maitland 2015
*/
#pragma once

#include <cstdint>
#include <Database/Service.hpp>
#include <Database/Repository/UserRepository.hpp>

namespace Service {
    class UserService : public Service<User> {
        Repository::UserRepository userRepository;
    public:
        User find( int32_t id );

        User create( User& user );

        void update( const User& user );

        void remove( int32_t id );

        vector<User> range( uint32_t start = 0, uint32_t end = 100 );

        uint32_t count();
    };
}