#include <Exception/ExceptionTest.hpp>

void ExceptionTest::SetUp() {
}

void ExceptionTest::TearDown() {
}


TEST_F (ExceptionTest, testMessage) {
    Exception::Exception e( "Some Message" );
    ASSERT_STREQ( "Some Message", e.getMessage().c_str() );
}

TEST_F (ExceptionTest, testHttpException) {
    Exception::HttpException e( Http::INTERNAL_SERVER_ERROR );
    ASSERT_EQ( Http::INTERNAL_SERVER_ERROR, e.getStatusCode() );
    ASSERT_STREQ( "Internal Server Error", e.getMessage().c_str() );
}