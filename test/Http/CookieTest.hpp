#pragma once

#include <string>
#include <gtest/gtest.h>

#include <Http/Http.hpp>
#include <Http/Cookie.hpp>
#include <Exception/HttpException.hpp>

#include <LogRedirect.hpp>

using namespace std;

class CookieTest : public ::testing::Test {

    protected:

    Http::Cookie * cookie;

    virtual void SetUp();

    virtual void TearDown();

};