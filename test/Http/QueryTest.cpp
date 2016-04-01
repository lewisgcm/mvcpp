#include <Http/QueryTest.hpp>


void QueryTest::testMalformedQuery() {
    CPPUNIT_ASSERT_NO_THROW( new Http::Query("==?====&&&&&&&") );
}

void QueryTest::testEmptyQuery() {
    CPPUNIT_ASSERT_NO_THROW( new Http::Query("") );
}

void QueryTest::testRootQuery() {
    Http::Query * q;
    CPPUNIT_ASSERT_NO_THROW( q = new Http::Query("/") );
    CPPUNIT_ASSERT_EQUAL( true, q->getPath() == "/" );
}

void QueryTest::testRootParams() {
    Http::Query * q;
    CPPUNIT_ASSERT_NO_THROW( q = new Http::Query("/?t=p&p=t") );
    CPPUNIT_ASSERT_EQUAL( true, q->getPath() == "/" );
    CPPUNIT_ASSERT_EQUAL( true, q->getParam("t") == "p" );
    CPPUNIT_ASSERT_EQUAL( true, q->getParam("p") == "t" );
    CPPUNIT_ASSERT_EQUAL( false, q->hasParam("f") );
}

void QueryTest::testEmptyParams() {
    Http::Query * q;
    CPPUNIT_ASSERT_NO_THROW( q = new Http::Query("/asdasdasdadasd?") );
    CPPUNIT_ASSERT_EQUAL( true, q->getPath() == "/asdasdasdadasd" );
}

void QueryTest::testParamsNoEquals() {
    Http::Query * q;
    CPPUNIT_ASSERT_NO_THROW( q = new Http::Query("/?t&p") );
    CPPUNIT_ASSERT_EQUAL( true, q->getPath() == "/" );
    CPPUNIT_ASSERT_EQUAL( true, q->hasParam("t") );
    CPPUNIT_ASSERT_EQUAL( true, q->hasParam("p") );
    CPPUNIT_ASSERT_EQUAL( false, q->hasParam("f") );
}

void QueryTest::testParamsNormal() {
    Http::Query * q;
    CPPUNIT_ASSERT_NO_THROW( q = new Http::Query("/hello_world/?t=p&p=t") );
    CPPUNIT_ASSERT_EQUAL( true, q->getPath() == "/hello_world/" );
    CPPUNIT_ASSERT_EQUAL( true, q->getParam("t") == "p" );
    CPPUNIT_ASSERT_EQUAL( true, q->getParam("p") == "t" );
    CPPUNIT_ASSERT_EQUAL( false, q->hasParam("f") );
}

void QueryTest::testParamsNormalCast() {
    Http::Query * q;
    CPPUNIT_ASSERT_NO_THROW( q = new Http::Query("/hello_world/?t=p&p=5") );
    CPPUNIT_ASSERT_EQUAL( true, q->getPath() == "/hello_world/" );
    CPPUNIT_ASSERT_EQUAL( true, q->getParam("t") == "p" );
    CPPUNIT_ASSERT_EQUAL( true, q->getParam<int>("p") == 5 );
    CPPUNIT_ASSERT_EQUAL( false, q->hasParam("f") );
}