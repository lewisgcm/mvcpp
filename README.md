# MVC++ Fast C++ HTTP Networking Library
[![Build Status](https://travis-ci.org/lewisgcm/mvcpp.svg?branch=master)](https://travis-ci.org/lewisgcm/mvcpp)
[![Coverage Status](https://coveralls.io/repos/github/lewisgcm/mvcpp/badge.svg?branch=master)](https://coveralls.io/github/lewisgcm/mvcpp?branch=master)
[![License Type](https://img.shields.io/badge/license-LGPL%203.0-blue.svg)](http://www.gnu.org/licenses/lgpl-3.0.en.html)

C++ library for HTTP based network applications including additional MVC helpers and routing.
This library was designed for simplicity, speed and modularity.
Various benchmarks have been included in the `benchmarking/*` directory and 
examples can be viewed in the `examples/*` directory.

## Getting Started
Building this project requires cmake 3, boost-system 1.54, google test and a C++11 compiler.

### Linux - debian based
Dependencies can be installed using the following commands on a debian based Linux system:
```bash
sudo add-apt-repository -y ppa:ubuntu-toolchain-r/test;
sudo apt-get update;
sudo apt-get install make g++-4.9 libcppunit-dev libboost-system-dev cmake libgtest-dev;
```

### OSX
On OSX dependencies can be installed using homebrew:
```bash
brew install cmake
brew install boost
```
GoogleTest (gtest) is also required.
This can be installed using the following commands:
```bash
git clone https://github.com/google/googletest.git
cd googletest; cmake .
make
make install
```

## Building OSX/Ubuntu
CMake is used as the build system for this project, follow the steps below to compile:
```bash
git clone --recursive https://github.com/lewisgcm/mvcpp
cd mvcpp; cmake .
make UnitTest  #Run unit tests
make RequestBenchmark #Compile request benchmark
make RouterExample #Compile router example
```

## Usage
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

Http::Server server( 8080, "0.0.0.0" );
server.run(
    router,
    []( Http::Response response, std::exception_ptr exception ) -> void {
        response.setStatusCode( Http::INTERNAL_SERVER_ERROR );
        response << "error"; 
    }
);
```

Alternativley a Simple file server could be implemented as follows:
```C++
Http::Server server( 8080, "0.0.0.0" );
server.run(
    []( Http::Request request, Http::Response response ) -> void {
        response << "<h1>Hello World</h1>";
    },
    []( Http::Response response, std::exception_ptr exception ) -> void {
        response.setStatusCode( Http::INTERNAL_SERVER_ERROR );
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
        response.setStatusCode( Http::INTERNAL_SERVER_ERROR );
        response << "A bad error!";
    }
);
```
