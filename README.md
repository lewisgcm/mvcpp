# mvc++
[![Build Status](https://travis-ci.org/lewisgcm/mvcpp.svg?branch=master)](https://travis-ci.org/lewisgcm/mvcpp)
C++ framework for HTTP based network applications with addtional MVC helpers and routing.
This library is designed to be easy to use, fast and extensible.
Various benchmarks have been included in the `benchmarking/*` directory.

Basic usage:
```C++
Routing::Router router({
    Routing::Route( Http::GET,  "/", []( Http::Request& request, Http::Response& response ) -> void {
        response << "Hello World";
    }),
    Routing::Route( Http::GET,  "/api/test", []( Http::Request& request, Http::Response& response ) -> void {
        response << "Testing!!!";
    }),
    Routing::Route( Http::GET,  "/api/test/{id}", []( Http::Request& request, Http::Response& response ) -> void {
        response << "Testing!!!" << request.getQuery().getParam<int>( "id" );
    })
});

Http::Server server( 8080, "0.0.0.0", router );
server.run();
```

Alternativley a Simple file server could be implemented as follows:
```C++
Http::Server server( 8080, "0.0.0.0" );
server.run(
    []( Http::Request request, Http::Response response ) -> void {
        response << "<h1>Hello World</h1>";
    },
    []( Http::Response response, std::exception_ptr exception ) -> void {
        response << "A bad error!";
    }
);
```

Advanced features have been added for JSON based APIs where request bodies can be auto-maigcally casted into objects from json.
```C++
Http::Server server( 8080, "0.0.0.0" );
server.run(
    []( Http::Request request, Http::Response response ) -> void {
        User user = request.getBody<User>();
        user.setName( "MyNewName" );
        response << static_cast<json>(user) ;
    },
    []( Http::Response response, std::exception_ptr exception ) -> void {
        response << "A bad error!";
    }
);
```
