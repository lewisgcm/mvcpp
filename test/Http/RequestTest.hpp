#pragma once

#include <iostream>
#include <string>
#include <list>
#include <gtest/gtest.h>

#include <Http/Http.hpp>
#include <Exception/HttpException.hpp>
#include <Http/Request.hpp>

using namespace std;

class RequestTest : public ::testing::Test {

    protected:

    Http::Request* request;

    virtual void SetUp();

    virtual void TearDown();

};