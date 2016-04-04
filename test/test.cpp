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

#include <Http/QueryTest.hpp>
#include <Http/RequestTest.hpp>
#include <MVC/RouteTest.hpp>

using namespace CppUnit;
using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION( RequestTest );
CPPUNIT_TEST_SUITE_REGISTRATION( QueryTest );
CPPUNIT_TEST_SUITE_REGISTRATION( RouteTest );

int main(int argc, char* argv[])
{
    FILE* err_file = freopen("test_out.txt","w",stderr);

    CPPUNIT_NS::TestResult testresult;

    CPPUNIT_NS::TestResultCollector collectedresults;
    testresult.addListener (&collectedresults);

    CPPUNIT_NS::BriefTestProgressListener progress;
    testresult.addListener (&progress);

    CPPUNIT_NS::TestRunner testrunner;
    testrunner.addTest (CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest ());
    testrunner.run(testresult);
    
    CPPUNIT_NS::CompilerOutputter compileroutputter(&collectedresults, std::cerr);
    compileroutputter.write ();
    ofstream xmlFileOut("test_results.xml");
    XmlOutputter xmlOut(&collectedresults, xmlFileOut);
    xmlOut.write();

    fclose(err_file);

    return collectedresults.wasSuccessful() ? 0 : 1;
}