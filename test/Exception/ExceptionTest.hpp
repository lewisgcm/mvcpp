#pragma once

#include <iostream>
#include <string>
#include <list>
#include <gtest/gtest.h>

#include <Http/Http.hpp>
#include <Exception/Exception.hpp>
#include <Exception/HttpException.hpp>

using namespace std;

class ExceptionTest : public ::testing::Test {

    protected:

    virtual void SetUp();

    virtual void TearDown();

};