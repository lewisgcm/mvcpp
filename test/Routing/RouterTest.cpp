#include <Routing/RouterTest.hpp>

void RouterTest::SetUp() {
}

void RouterTest::TearDown() {
}

TEST_F (RouterTest, NotFoundRoute) {
    std::istringstream iss(
        "GET /test HTTP/1.1\r\n"
    );
    std::ostringstream oss;

    Routing::Router router({
        Routing::Route( Http::GET,  "/", []( Http::Request& request, Http::Response& response ) -> void {
        })
    });
    Http::Request  request( iss );
    Http::Response response( Http::HTTP1_1, {}, oss );
    ASSERT_THROW( router.handleRequest( request, response ), Exception::HttpException );
}

TEST_F (RouterTest, NotFoundMethod) {
    std::istringstream iss(
        "POST / HTTP/1.1\r\n"
    );
    std::ostringstream oss;

    Routing::Router router({
        Routing::Route( Http::GET,  "/", []( Http::Request& request, Http::Response& response ) -> void {
        })
    });
    Http::Request  request( iss );
    Http::Response response( Http::HTTP1_1, {}, oss );
    ASSERT_THROW( router.handleRequest( request, response ), Exception::HttpException );
}

TEST_F (RouterTest, SubRoute) {
    std::istringstream iss(
        "GET /hello/test HTTP/1.1\r\n"
    );
    std::ostringstream oss;

    Routing::Router router({
        Routing::Route( Http::GET,  "/hello", []( Http::Request& request, Http::Response& response ) -> void {
            FAIL() << "Router matched incorrect route.";
        }),
        Routing::Route( Http::GET,  "/hello/test", []( Http::Request& request, Http::Response& response ) -> void {
        })
    });
    Http::Request  request( iss );
    Http::Response response( Http::HTTP1_1, {}, oss );
    ASSERT_NO_THROW( router.handleRequest( request, response ) );
}

TEST_F (RouterTest, RouteControllerThrow) {
    std::istringstream iss(
        "GET /hello?t=asds HTTP/1.1\r\n"
    );
    std::ostringstream oss;

    Routing::Router router({
        Routing::Route( Http::GET,  "/hello", []( Http::Request& request, Http::Response& response ) -> void {
            int t = request.getQuery().getParam<int>( "t" );
        })
    });
    Http::Request  request( iss );
    Http::Response response( Http::HTTP1_1, {}, oss );
    ASSERT_THROW( router.handleRequest( request, response ), boost::bad_lexical_cast );
}

TEST_F (RouterTest, RouteParamInt) {
    std::istringstream iss(
        "GET /hello/2 HTTP/1.1\r\n"
    );
    std::ostringstream oss;

    Routing::Router router({
        Routing::Route( Http::GET,  "/hello/{id}", []( Http::Request& request, Http::Response& response ) -> void {
            int t = request.getQuery().getParam<int>( "id" );
            ASSERT_EQ( 2, t );
        })
    });
    Http::Request  request( iss );
    Http::Response response( Http::HTTP1_1, {}, oss );
    ASSERT_NO_THROW( router.handleRequest( request, response ) );
}

TEST_F (RouterTest, RouteParamString) {
    std::istringstream iss(
        "GET /hello/test HTTP/1.1\r\n"
    );
    std::ostringstream oss;

    Routing::Router router({
        Routing::Route( Http::GET,  "/hello/{name}", []( Http::Request& request, Http::Response& response ) -> void {
            std::string name = request.getQuery().getParam<std::string>( "name" );
            ASSERT_STREQ( "test", name.c_str() );
        })
    });
    Http::Request  request( iss );
    Http::Response response( Http::HTTP1_1, {}, oss );
    ASSERT_NO_THROW( router.handleRequest( request, response ) );
}

TEST_F (RouterTest, RouteParamNested) {
    std::istringstream iss(
        "GET /hello/2 HTTP/1.1\r\n"
    );
    std::ostringstream oss;

    Routing::Router router({
        Routing::Route( Http::GET,  "/hello", []( Http::Request& request, Http::Response& response ) -> void {
            FAIL() << "Router matched incorrect route.";
        }),
        Routing::Route( Http::GET,  "/{name}/{id}", []( Http::Request& request, Http::Response& response ) -> void {
        })
    });
    Http::Request  request( iss );
    Http::Response response( Http::HTTP1_1, {}, oss );
    ASSERT_NO_THROW( router.handleRequest( request, response ) );
}