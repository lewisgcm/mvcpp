/**
 * (c) Lewis Maitland 2015
*/
#include <Database/Repository/UserRepository.hpp>

namespace Repository {

    User UserRepository::find( int32_t id ) {
        User user;
        soci::statement statement = (session_.prepare << "select * from user WHERE id=:id", soci::use(id), soci::into(user) );
        statement.execute();
        if( !statement.fetch() ) {
            throw Exception::HttpException( Http::NOT_FOUND );
        }
        return user;
    }

    User UserRepository::create( User &user ) {
        session_ << "insert into user (username, password, email) values (:a,:b,:c)", 
        soci::use( user.username ), soci::use( user.password ), soci::use( user.email );
        long id;
        session_.get_last_insert_id("user", id);
        user.id = id;
        return user;
    }

    void UserRepository::update( const User &user ) {
        session_ << "update user SET username=:a, password=:b, email=:c WHERE id=:id",
        soci::use(user.username), soci::use(user.password), soci::use(user.email), soci::use(user.id);
    }

    void UserRepository::remove( int32_t id ) {
        session_ << "delete from user WHERE id=:id",
        soci::use(id);
    }

    vector<User> UserRepository::range( uint32_t offset, uint32_t limit ) {
        User user;
        vector<User> users;

        soci::statement statement = (session_.prepare << "select * from user LIMIT :limit OFFSET :offset ", soci::into(user), soci::use(limit), soci::use(offset) );
        statement.execute();
        while( statement.fetch() ) {
            users.push_back( user );
        }
        return users;
    }

    uint32_t UserRepository::count() {
        uint32_t count;
        session_ << "select count(id) from user", soci::into( count );
        return count;
    }
}