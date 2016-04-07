#include <Routing/RouteTest.hpp>

void RouteTest::SetUp() {
}

void RouteTest::TearDown() {
}

TEST_F (RouteTest, MatchRouteBoth) {

    Routing::Route route(
        Http::GET,
        "/test",
        []( Http::Request& request, Http::Response& response ) {

        } 
    );

    ASSERT_TRUE( route.matchRoute( Http::GET, "/test" ) );
}

TEST_F (RouteTest, NoMatchMethodRoute) {

    Routing::Route route(
        Http::POST,
        "/test",
        []( Http::Request& request, Http::Response& response ) {

        } 
    );

    ASSERT_FALSE( route.matchRoute( Http::GET, "/test" ) );
}

TEST_F (RouteTest, NoMatchRoute) {

    Routing::Route route(
        Http::GET,
        "/test/hello",
        []( Http::Request& request, Http::Response& response ) {

        } 
    );

    ASSERT_FALSE( route.matchRoute( Http::GET, "/test" ) );
}

TEST_F (RouteTest, NoMatchRouteBoth) {

    Routing::Route route(
        Http::POST,
        "/test/test",
        []( Http::Request& request, Http::Response& response ) {

        } 
    );

    ASSERT_FALSE( route.matchRoute( Http::GET, "/test" ) );
}

TEST_F (RouteTest, QueryParam) {

    Routing::Route route(
        Http::GET,
        "/test/{id}",
        []( Http::Request& request, Http::Response& response ) {
        }
    );

    ASSERT_TRUE ( route.matchRoute( Http::GET, "/test/5" ) );
    Http::Query query( "/test/5" );
    route.setQueryRouteParams( query );
    ASSERT_EQ( 5, query.getParam<int>( "id" ) );
}

TEST_F (RouteTest, QueryParamNested) {

    Routing::Route route(
        Http::GET,
        "/{name}/{id}",
        []( Http::Request& request, Http::Response& response ) {
        }
    );

    ASSERT_TRUE ( route.matchRoute( Http::GET, "/test/5" ) );
    Http::Query query( "/test/5" );
    route.setQueryRouteParams( query );
    ASSERT_STREQ( "test", query.getParam<std::string>( "name" ).c_str() );
    ASSERT_EQ(    5,      query.getParam<int>( "id" ) );
}