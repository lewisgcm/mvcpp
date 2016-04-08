#pragma once

#include <iostream>
#include <string>
#include <list>
#include <gtest/gtest.h>

#include <boost/lexical_cast.hpp>

#include <Http/Http.hpp>
#include <Http/Response.hpp>
#include <Http/Request.hpp>
#include <Http/Query.hpp>
#include <Routing/Router.hpp>
#include <Routing/Route.hpp>
#include <Exception/HttpException.hpp>
#include <LogRedirect.hpp>

using namespace std;

class RouterTest : public ::testing::Test {

    protected:

    Routing::Router* router;

    virtual void SetUp();

    virtual void TearDown();

};