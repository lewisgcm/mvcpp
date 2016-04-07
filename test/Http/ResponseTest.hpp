#pragma once

#include <iostream>
#include <string>
#include <list>
#include <gtest/gtest.h>

#include <Http/Http.hpp>
#include <Exception/HttpException.hpp>
#include <Http/Response.hpp>

using namespace std;

class ResponseTest : public ::testing::Test {

    protected:

    Http::Response* response;

    virtual void SetUp();

    virtual void TearDown();

};