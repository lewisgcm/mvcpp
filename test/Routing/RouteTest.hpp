#pragma once

#include <iostream>
#include <string>
#include <list>
#include <gtest/gtest.h>

#include <boost/lexical_cast.hpp>

#include <Http/Http.hpp>
#include <Http/Query.hpp>
#include <Routing/Route.hpp>
#include <Exception/HttpException.hpp>

using namespace std;

class RouteTest : public ::testing::Test {

    protected:

    virtual void SetUp();

    virtual void TearDown();

};