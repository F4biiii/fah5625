#define BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>
#include "pemploy.h"

BOOST_AUTO_TEST_SUITE(pemploy_test)

BOOST_AUTO_TEST_CASE(rise1){
    float s = 4000.0;
    riseSalary(s,5);
    BOOST_CHECK(s == 4200.0);

}

BOOST_AUTO_TEST_SUITE_END()