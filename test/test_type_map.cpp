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

#include "../include/type_map.h"


using map_t = typemap::Map<
    typemap::Pair<55, int8_t>,
    typemap::Pair<22, float>,
    typemap::Pair<4, bool>
>;

static_assert(std::is_same_v<map_t::get<55>,  int8_t>,  "Type map error");
static_assert(std::is_same_v<map_t::get<22>,  float>,   "Type map error");
static_assert(std::is_same_v<map_t::get<4>,   bool>,    "Type map error");

// check unknown types
static_assert(!std::is_same_v<map_t::get<78>,  int>,                "Type map error");
static_assert(std::is_same_v<map_t::get<1048>, std::false_type>,    "Type map error");


int main(){
    // informs test-listener about testresults
    CPPUNIT_NS::TestResult testresult;

    // register listener for collecting the test-results
    CPPUNIT_NS::TestResultCollector collectedresults;
    testresult.addListener (&collectedresults);

    // register listener for per-test progress output
    CPPUNIT_NS::BriefTestProgressListener progress;
    testresult.addListener (&progress);

    // insert test-suite at test-runner by registry
    CPPUNIT_NS::TestRunner testrunner;
    testrunner.addTest (CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest ());
    testrunner.run(testresult);

    // output results in compiler-format
    CPPUNIT_NS::CompilerOutputter compileroutputter(&collectedresults, std::cerr);
    compileroutputter.write ();

    // Output XML for Jenkins CPPunit plugin
    // std::ofstream xmlFileOut("MicroParcelMessageTest.xml");
    // CPPUNIT_NS::XmlOutputter xmlOut(&collectedresults, xmlFileOut);
    // xmlOut.write();

    // return 0 if tests were successful
    return collectedresults.wasSuccessful() ? 0 : 1;
}
