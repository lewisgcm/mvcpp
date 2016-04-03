/**
 * (c) Lewis Maitland 2015
*/
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <vector>
#include <tuple>
#include <Http/Http.hpp>
#include <Exception/Exception.hpp>
#include <map>
#include <iostream>
#include <Http/Response.hpp>
#include <Http/Request.hpp>
#include <Routing/Router.hpp>
#include <Http/Server.hpp>

int main() {
    try {
        Http::Server server( 8080, "0.0.0.0" );
        server.run(
            []( Http::Request request, Http::Response response ) -> void {
                response << "<h1>Hello World</h1>";
            },
            []( Http::Response response, std::exception_ptr exception ) -> void {
                response << "A bad error!";
            }
        );
    } catch( std::regex_error& e ) {
        cout << "ERROR CODE: " << e.code() << ", What:" << e.what() << "\n";
    }
    return 0;
}