#include <Exception/ExceptionTest.hpp>

void ExceptionTest::SetUp() {
}

void ExceptionTest::TearDown() {
}


TEST_F (ExceptionTest, testMessage) {
    Exception::Exception e( "Some Message" );
    ASSERT_STREQ( "Some Message", e.getMessage().c_str() );
}