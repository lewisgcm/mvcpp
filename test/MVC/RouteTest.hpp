#pragma once

#include <iostream>
#include <string>
#include <list>
#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/ui/text/TextTestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/XmlOutputter.h>
#include <netinet/in.h>
#include <Http/Http.hpp>
#include <Exception/HttpException.hpp>
#include <Http/Query.hpp>

using namespace CppUnit;
using namespace std;

class RouteTest : public CppUnit::TestFixture {

    CPPUNIT_TEST_SUITE(RouteTest);
    CPPUNIT_TEST(testRoute);
    CPPUNIT_TEST_SUITE_END();

protected:
    void testRoute();
};