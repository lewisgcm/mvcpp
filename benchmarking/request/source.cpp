#include <stdio.h>
#include <iostream>
#include <Http/Http.hpp>
#include <Http/Request.hpp>

#define ITERATIONS 10000

int main() {

    for(int i=0; i< ITERATIONS; i++) {
        istringstream input(
            "POST /api/test/hello?some=parameters&to=test&parsing=ability&empty&ones=aswell HTTP/1.1\r\n"
            "Header: test\r\n"
            "Another: Header\r\n"
            "Header1: This is a very very very very long header that should test the ability to parse the longer strings\r\n"
            "\r\n"
            "And now for the body blah blah this is the body of the request"
        );
        Http::Request request( input );
    }
    return 0;
}