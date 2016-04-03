#include <Http/RequestTest.hpp>

void RequestTest::testMalformedRequest() {
    std::istringstream iss(
        "asdasd\r\n\r\n"
    );
    CPPUNIT_ASSERT_THROW( new Http::Request(iss), Exception::HttpException );
}

void RequestTest::testInvalidMethod() {
    std::istringstream iss(
        "POOT / HTTP/1.1\r\n\r\n"
    );
    CPPUNIT_ASSERT_THROW( new Http::Request(iss), Exception::HttpException );
}

void RequestTest::testValidMethods() {
    for( string method : Http::HttpMethodString ) {
        std::istringstream iss(
            method + " / HTTP/1.1\r\n\r\n"
        );
        CPPUNIT_ASSERT_NO_THROW( new Http::Request(iss) );
    }
}

void RequestTest::testInvalidQuery() {
    std::istringstream iss(
        "PUT HTTP/1.1\r\n\r\n"
    );
    CPPUNIT_ASSERT_THROW( new Http::Request(iss), Exception::HttpException );
}

void RequestTest::testInvalidHTTPVersion() {
    std::istringstream iss(
        "PUT / HTTP3.1\r\n\r\n"
    );
    CPPUNIT_ASSERT_THROW( new Http::Request(iss), Exception::HttpException );
}

void RequestTest::testValidHTTPVersion() {
    for( string version : Http::HttpVersionString ) {
        std::istringstream iss(
            "PUT / " + version + "\r\n\r\n"
        );
        CPPUNIT_ASSERT_NO_THROW( new Http::Request(iss) );
    }
}

void RequestTest::testMaxRequestLength() {
    string query = "a";
    for(int i=0; i<Http::MAX_REQUEST_LINE_LENGTH; i++) {
        query += "a";
    }
    std::istringstream iss(
        "PUT " + query + " HTTP/1.1\r\n\r\n"
    );
    CPPUNIT_ASSERT_THROW( new Http::Request(iss), Exception::HttpException );
}

void RequestTest::testValidHeaders() {
    std::istringstream iss(
        "POST / HTTP/1.1\r\n"
        "Header: test\r\n"
        "Header1:test1\r\n"
        "  Header2  :  test2  \r\n"
        "  Header3  \r\n"
        "\r\n"
    );
    Http::Request request(iss);
    Http::HttpHeaders headers = request.getHeaders();
    CPPUNIT_ASSERT_EQUAL_MESSAGE( "Method",  true, Http::POST == request.getMethod() );
    CPPUNIT_ASSERT_EQUAL_MESSAGE( "Header",  true, "test" == headers["Header"] );
    CPPUNIT_ASSERT_EQUAL_MESSAGE( "Header1", true, "test1" == headers["Header1"] );
    CPPUNIT_ASSERT_EQUAL_MESSAGE( "Header2", true, "test2" == headers["Header2"] );
    CPPUNIT_ASSERT_EQUAL_MESSAGE( "Header3", true, "" == headers["Header3"] );
}