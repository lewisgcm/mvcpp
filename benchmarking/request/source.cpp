#include <stdio.h>
#include <iostream>
#include <Http/Http.hpp>
#include <Http/Request.hpp>

#define ITERATIONS 150000

int main() {

    for(int i=0; i< ITERATIONS; i++) {
        istringstream input(
            "POST /api/test/hello HTTP/1.1\r\n"
            "Header: test\r\n"
            "Another: Header\r\n"
            "cookie: name=lewis\r\n"
            "\r\n"
            "And now for the body blah blah this is the body of the request"
        );
        Http::Request request( input );
    }
    return 0;
}