#include <Http/CookieTest.hpp>

void CookieTest::SetUp() {
    this->cookie = NULL;
    REDIRECT_ON( stderr );
}

void CookieTest::TearDown() {
    if( this->cookie == NULL ) {
        delete this->cookie;
    }
    REDIRECT_OFF( stderr );
}

TEST_F (CookieTest, testValidCookie) {
    ASSERT_NO_THROW( this->cookie = new Http::Cookie( "name=Mike; expires=Sat, 03 May 2025 17:44:22 GMT" ) );
    ASSERT_STREQ( "Mike", this->cookie->get( "name" ).c_str() );
    ASSERT_STREQ( "Sat, 03 May 2025 17:44:22 GMT", this->cookie->get( "expires" ).c_str() );
}

TEST_F (CookieTest, testValidCookieSpaces) {
    ASSERT_NO_THROW( this->cookie = new Http::Cookie( "name  =   Mike   ; expires   =   Sat, 03 May 2025 17:44:22 GMT    " ) );
    ASSERT_STREQ( "Mike", this->cookie->get( "name" ).c_str() );
    ASSERT_STREQ( "Sat, 03 May 2025 17:44:22 GMT", this->cookie->get( "expires" ).c_str() );
}

TEST_F (CookieTest, testInvalidCookieKeyValue) {
    ASSERT_THROW( this->cookie = new Http::Cookie( "name; expires   =   Sat, 03 May 2025 17:44:22 GMT    " ), Exception::HttpException );
}

TEST_F (CookieTest, testInvalidCookieNoBody) {
    ASSERT_THROW( this->cookie = new Http::Cookie( "" ), Exception::HttpException );
}

TEST_F (CookieTest, testValidCookieSingleEntry) {
    ASSERT_NO_THROW( this->cookie = new Http::Cookie( "name=test" ) );
    ASSERT_STREQ( "test", this->cookie->get( "name" ).c_str() );
}