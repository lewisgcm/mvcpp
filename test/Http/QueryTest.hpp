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

class QueryTest : public CppUnit::TestFixture {

    CPPUNIT_TEST_SUITE(QueryTest);
    CPPUNIT_TEST(testMalformedQuery);
    CPPUNIT_TEST(testEmptyQuery);
    CPPUNIT_TEST(testRootQuery);
    CPPUNIT_TEST(testRootParams);
    CPPUNIT_TEST(testEmptyParams);
    CPPUNIT_TEST(testParamsNoEquals);
    CPPUNIT_TEST(testParamsNormal);
    CPPUNIT_TEST(testParamsNormalCast);
    CPPUNIT_TEST_SUITE_END();

public:

protected:
    void testMalformedQuery();
    void testEmptyQuery();
    void testRootQuery();
    void testRootParams();
    void testEmptyParams();
    void testParamsNoEquals();
    void testParamsNormal();
    void testParamsNormalCast();
};