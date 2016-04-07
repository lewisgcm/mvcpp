#include <Http/QueryTest.hpp>

void QueryTest::SetUp() {
    this->query = NULL;
}

void QueryTest::TearDown() {
    if( this->query == NULL ) {
        delete this->query;
    }
}

TEST_F (QueryTest, testMalformedQuery) {
    ASSERT_THROW( this->query = new Http::Query("==?====&&&&&&&"), Exception::HttpException );
}

TEST_F (QueryTest, testEmptyQuery) {
    ASSERT_THROW( this->query = new Http::Query(""), Exception::HttpException );
}

TEST_F (QueryTest, testRootQuery) {
    ASSERT_NO_THROW( this->query = new Http::Query("/") );
    ASSERT_STREQ( "/", this->query->getPath().c_str() );
}

TEST_F (QueryTest, testRootParams) {
    ASSERT_NO_THROW( this->query = new Http::Query("/?t=p&p=t") );
    ASSERT_STREQ( "/",   this->query->getPath().c_str() );
    ASSERT_STREQ( "p",   this->query->getParam("t").c_str() );
    ASSERT_STREQ( "t",   this->query->getParam("p").c_str() );
    ASSERT_EQ   ( false, this->query->hasParam("f") );
}

TEST_F (QueryTest, testNoParam) {
    ASSERT_NO_THROW( this->query = new Http::Query("/") );
    ASSERT_STREQ( "/",   this->query->getPath().c_str() );
    ASSERT_STREQ( "",    this->query->getParam("t").c_str() );
}

TEST_F (QueryTest, testEmptyParams) {
    ASSERT_NO_THROW( this->query = new Http::Query("/asdasdasdadasd?") );
    ASSERT_STREQ( "/asdasdasdadasd", this->query->getPath().c_str() );
}

TEST_F (QueryTest, testParamsNoValues) {
    ASSERT_NO_THROW( this->query = new Http::Query("/?t&p") );
    ASSERT_STREQ( "/",   this->query->getPath().c_str() );
    ASSERT_STREQ( "",    this->query->getParam("t").c_str() );
    ASSERT_STREQ( "",    this->query->getParam("p").c_str() );
    ASSERT_EQ   ( true,  this->query->hasParam("t") );
    ASSERT_EQ   ( true,  this->query->hasParam("p") );
}

TEST_F (QueryTest, testParamsSubDir) {
    ASSERT_NO_THROW( this->query = new Http::Query("/hello_world/?t=p&p=t") );
    ASSERT_STREQ( "/hello_world/", this->query->getPath().c_str() );
    ASSERT_STREQ( "p",             this->query->getParam("t").c_str() );
    ASSERT_STREQ( "t",             this->query->getParam("p").c_str() );
    ASSERT_EQ   ( false,           this->query->hasParam("f") );
}

TEST_F (QueryTest, testParamsSubDirCast) {
    ASSERT_NO_THROW( this->query = new Http::Query("/hello_world/?t=p&p=5") );
    ASSERT_STREQ( "/hello_world/", this->query->getPath().c_str() );
    ASSERT_STREQ( "p",             this->query->getParam("t").c_str() );
    ASSERT_EQ   ( 5,               this->query->getParam<int>("p") );
    ASSERT_EQ   ( false,           this->query->hasParam("f") );
}

TEST_F (QueryTest, testParamsSubDirBadCast) {
    ASSERT_NO_THROW( this->query = new Http::Query("/hello_world/?t=p&p=aa") );
    ASSERT_STREQ( "/hello_world/", this->query->getPath().c_str() );
    ASSERT_STREQ( "p",             this->query->getParam("t").c_str() );
    ASSERT_EQ   ( false,           this->query->hasParam("f") );
    ASSERT_THROW( this->query->getParam<int>("p"), std::exception );
}