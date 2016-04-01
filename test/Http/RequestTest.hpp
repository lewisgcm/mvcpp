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
#include <Http/Request.hpp>

using namespace CppUnit;
using namespace std;

class RequestTest : public CppUnit::TestFixture {

    CPPUNIT_TEST_SUITE(RequestTest);
    CPPUNIT_TEST(testMalformedRequest);
    CPPUNIT_TEST(testInvalidMethod);
    CPPUNIT_TEST(testValidMethods);
    CPPUNIT_TEST(testInvalidQuery);
    CPPUNIT_TEST(testInvalidHTTPVersion);
    CPPUNIT_TEST(testValidHTTPVersion);
    CPPUNIT_TEST(testMaxRequestLength);
    CPPUNIT_TEST(testValidHeaders);
    CPPUNIT_TEST(testHeadersAndBody);
    CPPUNIT_TEST_SUITE_END();

public:

protected:
    void testMalformedRequest();
    void testInvalidMethod();
    void testValidMethods();
    void testInvalidQuery();
    void testInvalidHTTPVersion();
    void testValidHTTPVersion();
    void testMaxRequestLength();
    void testValidHeaders();
    void testHeadersAndBody();
};