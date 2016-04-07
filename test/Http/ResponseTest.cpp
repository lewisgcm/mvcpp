#include <Http/ResponseTest.hpp>

void ResponseTest::SetUp() {
    this->response = NULL;
}

void ResponseTest::TearDown() {
    if( this->response == NULL ) {
        delete this->response;
    }
}

TEST_F (ResponseTest, testHttpVersion) {
    std::ostringstream oss;
    this->response = new Http::Response( Http::HTTP1_1, {}, oss );
    *this->response << "";
    
    std::string correct(
        "HTTP/1.1 200 Ok\r\n"
        "\r\n"
    );
    ASSERT_STREQ( correct.c_str(), oss.str().c_str() );
}

TEST_F (ResponseTest, testHeaders) {
    std::ostringstream oss;
    this->response = new Http::Response( Http::HTTP1_1, { {"header", "value"} }, oss );
    *this->response << "";
    
    std::string correct(
        "HTTP/1.1 200 Ok\r\n"
        "header: value\r\n"
        "\r\n"
    );
    ASSERT_STREQ( correct.c_str(), oss.str().c_str() );
}