/**
 * (c) Lewis Maitland 2015
*/
#include <Database/Service/UserService.hpp>

namespace Service {
    User UserService::find( int32_t id ) {
        return userRepository.find( id );
    }

    User UserService::create( User& user ) {
        return userRepository.create( user );
    }

    void UserService::update( const User& user ) {
        userRepository.update( user );
    }

    void UserService::remove( int32_t id ) {
        userRepository.remove( id );
    }

    vector<User> UserService::range( uint32_t start , uint32_t end ) {
        return userRepository.range( start, end );
    }

    uint32_t UserService::count() {
        return userRepository.count();
    }
}