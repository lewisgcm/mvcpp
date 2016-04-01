/**
 * (c) Lewis Maitland 2015
*/
#include <Controller/SimpleController.hpp>

namespace Controller {

    Service::UserService SimpleController::userService;

    void SimpleController::all( Http::Request& request, Http::Response& response ) {
        vector<User> users = userService.range();
        json json_r;

        for( User user : users ) {
            json_r.push_back( static_cast<json>(user) );
        }
        response << json_r;
    };

    void SimpleController::get( Http::Request& request, Http::Response& response ) {
        User user = userService.find( request.getQuery().getParam<int32_t>("id") );
        response << static_cast<json>(user);
    }

    void SimpleController::create( Http::Request& request, Http::Response& response ) {
        User user = request.getBody<User>();
        userService.create( user );
        response << static_cast<json>(user);
    }

    void SimpleController::update( Http::Request& request, Http::Response& response ) {
        User user = request.getBody<User>();
        userService.update( user );
        response << static_cast<json>(user);
    }

    void SimpleController::remove( Http::Request& request, Http::Response& response ) {
        userService.remove( request.getQuery().getParam<int32_t>("id")  );
    }
}