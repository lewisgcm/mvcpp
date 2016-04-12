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
#include <Exception/HttpException.hpp>
#include <map>
#include <iostream>
#include <fstream>
#include <Http/Response.hpp>
#include <Http/Request.hpp>
#include <Routing/Router.hpp>
#include <Http/Server.hpp>

int main( int argc, char** argv ) {
    try {

        Http::Server server( 8080, "0.0.0.0" );
        server.run(
            []( Http::Request request, Http::Response response ) -> void {
                response << "Hello World";
            },
            []( Http::Response response, std::exception_ptr exception ) -> void {
                try {
                    std::rethrow_exception( exception );
                } catch( Exception::HttpException e ) {
                    response.setStatusCode( e.getStatusCode() );
                    response << "<html><head><title>Error</title></head><body><h1>";
                    response << Http::HttpResponseStrings.at( e.getStatusCode() );
                    response << "</h1></body></html>";
                } catch( ... ) {
                    response.setStatusCode( Http::INTERNAL_SERVER_ERROR );
                    response << "<html><head><title>Error</title></head><body><h1>Unknown Server Error</h1></body></html>";
                }
            }
        );
    } catch( std::regex_error& e ) {
        cout << "ERROR CODE: " << e.code() << ", What:" << e.what() << "\n";
    }
    return 0;
}