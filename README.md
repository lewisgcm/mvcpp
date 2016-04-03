# mvc++
C++ MVC Framework for REST API based applications.
Currently the following features have been implemented:
* Regex based router
* HTTP Request parsing
* Request dispatcher
* Benchmarking
The following features will be added:
* Unit tests

Basic usage:
```C++
try {

    Routing::Router router({
        Routing::Route( Http::GET,  "/", []( Http::Request& request, Http::Response& response ) -> void {
            response << "Hello World";
        }),
        Routing::Route( Http::GET,  "/api/test", []( Http::Request& request, Http::Response& response ) -> void {
            response << "Testing!!!";
        })
    });

    Http::Server server( 8080, "0.0.0.0", router );
    server.run();

} catch( std::regex_error& e ) {
    cout << "ERROR CODE: " << e.code() << ", What:" << e.what() << "\n";
}
```

Alternativley a Simple file server could be implemented as follows:
```C++
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
```