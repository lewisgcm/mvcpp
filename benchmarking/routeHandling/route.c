#include <stdio.h>
#include <iostream>
#include <Http/Http.hpp>
#include <Http/Response.hpp>
#include <Http/Request.hpp>
#include <Routing/Route.hpp>
#include <Routing/Router.hpp>

#define ITERATIONS 10000

class BenchmarkController {

public:
    static void test( Http::Request& request, Http::Response& response ) {
        response << "test";
    }

    static void testt( Http::Request& request, Http::Response& response ) {
        response << "test";
    }

    static void testtt( Http::Request& request, Http::Response& response ) {
        response << "test";
    }
};

int main() {

    Routing::Router router({
        Routing::Route( Http::GET,  "/api/test/index",       BenchmarkController::test ),
        Routing::Route( Http::POST, "/api/test/{id}",        BenchmarkController::testt ),
        Routing::Route( Http::POST, "/api/test/{id}/{name}", BenchmarkController::testtt )
    });

    for(int i=0; i< ITERATIONS; i++) {
        ostringstream output;
        istringstream input(
            "POST /api/test/hello?some=parameters&to=test&parsing=ability&empty&ones=aswell HTTP/1.1\r\n"
            "Header: test\r\n"
            "Another: Header\r\n"
            "Header1: This is a very very very very long header that should test the ability to parse the longer strings\r\n"
            "\r\n"
            "And now for the body blah blah this is the body of the request"
        );
        Http::Request  request( input );
        Http::Response response( Http::HTTP1_1, {
            { "CARPSESSION", "12345678" },
            { "Content-type", "application/json" }
        }, output );
        router.handleRequest( request, response );
    }
    return 0;
}