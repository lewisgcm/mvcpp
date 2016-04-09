#include <Http/RequestTest.hpp>

void RequestTest::SetUp() {
    this->request = NULL;
}

void RequestTest::TearDown() {
    if( this->request == NULL ) {
        delete this->request;
    }
}

TEST_F (RequestTest, testMalformedRequest) {
    std::istringstream iss(
        "asdasd\r\n\r\n"
    );
    ASSERT_THROW( this->request = new Http::Request(iss), Exception::HttpException );
}

TEST_F (RequestTest, testInvalidMethod) {
    std::istringstream iss(
        "POOT / HTTP/1.1\r\n\r\n"
    );
    ASSERT_THROW( this->request = new Http::Request(iss), Exception::HttpException );
}

TEST_F (RequestTest, testValidMethods) {
    for( string method : Http::HttpMethodString ) {
        std::istringstream iss(
            method + " / HTTP/1.1\r\n\r\n"
        );
        ASSERT_NO_THROW( this->request = new Http::Request(iss) );
    }
}

TEST_F (RequestTest, testInvalidQuery) {
    std::istringstream iss(
        "PUT HTTP/1.1\r\n\r\n"
    );
    ASSERT_THROW( this->request = new Http::Request(iss), Exception::HttpException );
}

TEST_F (RequestTest, testInvalidHTTPVersion) {
    std::istringstream iss(
        "PUT / HTTP3.1\r\n\r\n"
    );
    ASSERT_THROW( this->request = new Http::Request(iss), Exception::HttpException );
}

TEST_F (RequestTest, testValidHTTPVersion) {
    for( string version : Http::HttpVersionString ) {
        std::istringstream iss(
            "PUT / " + version + "\r\n\r\n"
        );
        ASSERT_NO_THROW( this->request = new Http::Request(iss) );
    }
}

TEST_F (RequestTest, testMaxStatusRequestLength) {
    string query = "a";
    for(int i=0; i<Http::MAX_REQUEST_LINE_LENGTH; i++) {
        query += "a";
    }
    std::istringstream iss(
        "PUT " + query + " HTTP/1.1\r\n\r\n"
    );
    ASSERT_THROW( this->request = new Http::Request(iss), Exception::HttpException );
}

TEST_F (RequestTest, testMaxHeaderRequestLength) {
    string query = "header: a";
    for(int i=0; i<Http::MAX_REQUEST_LINE_LENGTH; i++) {
        query += "a";
    }
    std::istringstream iss(
        "PUT / HTTP/1.1\r\n"
        "" + query + "\r\n\r\n"
    );
    ASSERT_THROW( this->request = new Http::Request(iss), Exception::HttpException );
}

TEST_F (RequestTest, testValidHeaders) {
    std::istringstream iss(
        "POST / HTTP/1.1\r\n"
        "Header: test\r\n"
        "Header1:test1\r\n"
        "  Header2  :  TesT2  \r\n"
        "  Header3  \r\n"
        "\r\n"
    );
    ASSERT_NO_THROW( this->request = new Http::Request(iss) );
    Http::HttpHeaders headers = this->request->getHeaders();
    ASSERT_EQ(    Http::HTTP1_1, this->request->getVersion() );
    ASSERT_EQ(    Http::POST,    this->request->getMethod() );
    ASSERT_STREQ( "test",     headers["header"].c_str() );
    ASSERT_STREQ( "test1",    headers["header1"].c_str() );
    ASSERT_STREQ( "test2",    headers["header2"].c_str() );
    ASSERT_STREQ( "",         headers["header3"].c_str() );
}

TEST_F (RequestTest, testValidBody) {
    std::istringstream iss(
        "POST / HTTP/1.1\r\n"
        "Content-Length: 5\r\n"
        "Content-Type: application/json\r\n"
        "\r\n"
        "12345"
    );
    ASSERT_NO_THROW( this->request = new Http::Request(iss) );
    Http::HttpHeaders headers = this->request->getHeaders();
    ASSERT_EQ(    Http::HTTP1_1, this->request->getVersion() );
    ASSERT_EQ(    Http::POST,    this->request->getMethod() );
    ASSERT_STREQ( "12345",       this->request->getBody().c_str() );
}

TEST_F (RequestTest, testLongInvalidBody) {
    std::istringstream iss(
        "POST / HTTP/1.1\r\n"
        "Content-Length: 5\r\n"
        "Content-Type: application/json\r\n"
        "\r\n"
        "12345asdasdasdasd"
    );
    ASSERT_NO_THROW( this->request = new Http::Request(iss) );
    Http::HttpHeaders headers = this->request->getHeaders();
    ASSERT_EQ(    Http::HTTP1_1,         this->request->getVersion() );
    ASSERT_EQ(    Http::POST,            this->request->getMethod() );
    ASSERT_STREQ( "application/json",    this->request->getContentType().c_str() );
    ASSERT_STREQ( "12345",               this->request->getBody().c_str() );
}

TEST_F (RequestTest, testInvalidBodyLength) {
    std::istringstream iss(
        "POST / HTTP/1.1\r\n"
        "Content-Length: asdasd\r\n"
        "Content-Type: application/json\r\n"
        "\r\n"
        "12345asdasdasdasd"
    );
    ASSERT_THROW( this->request = new Http::Request(iss), std::exception );
}

TEST_F (RequestTest, testOverMaxLength) {
    std::string max_length = boost::lexical_cast<std::string>( Http::MAX_REQUEST_BODY_LENGTH+1 );
    std::istringstream iss(
        "POST / HTTP/1.1\r\n"
        "Content-Length: " + max_length + "\r\n"
        "Content-Type: application/json\r\n"
        "\r\n"
        "body"
    );
    ASSERT_THROW( this->request = new Http::Request(iss), std::exception );
}