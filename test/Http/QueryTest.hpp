#pragma once

#include <iostream>
#include <string>
#include <list>
#include <gtest/gtest.h>

#include <Http/Http.hpp>
#include <Exception/HttpException.hpp>
#include <Http/Query.hpp>

using namespace std;

class QueryTest : public ::testing::Test {

    protected:

    Http::Query * query;

    virtual void SetUp();

    virtual void TearDown();

};