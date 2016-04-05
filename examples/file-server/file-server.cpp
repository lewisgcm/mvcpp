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
        std::string base = "";
        if( argc == 2 ) {
            base = argv[1];
        } else {
            base = "./";
        }

        const std::map< std::string, std::string> mime = {
            { "html",  "text/html" },
            { "json",  "application/json" },
            { "png",   "image/png" },
            { "jpg",   "image/jpeg" },
            { "jpeg",  "image/jpeg" },
            { "js",    "application/x-javascript" },
            { "css",   "text/css" }
        };

        Http::Server server( 8080, "0.0.0.0" );
        server.run(
            [base, mime]( Http::Request request, Http::Response response ) -> void {

                //Get the file the user is looking for
                std::string path = request.getQuery().getPath();
                if( path == "/" ) {
                    path = "index.html";
                }

                std::string line;
                std::ifstream file ( base + path );

                if( !file.good() ) {
                    throw Exception::HttpException( Http::NOT_FOUND );
                }

                std::string extension = path.substr(path.find_last_of(".") + 1);
                if( extension.length() > 0 ) {
                    if( mime.find( extension ) != mime.end() ) {
                        response.addHeaders({ { "Content-Type", mime.at( extension ) } });
                    } else {
                        response.addHeaders({ { "Content-Type", "text" } });
                    }
                }
                response.addHeaders({ { "Cache-Control", "max-age=30000000" } });

                while( getline( file, line ) ) {
                    response << line << '\n';
                }
                file.close();
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