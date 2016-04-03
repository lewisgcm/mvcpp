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
```
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