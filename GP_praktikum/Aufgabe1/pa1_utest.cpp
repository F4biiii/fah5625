#define BOOST_TEST_MAIN
#include <cmath>
#include <type_traits>
#include <vector>
#include <boost/test/included/uint_test.hpp>
#include "vertical.h"

BOOST_AUTO_TEST_SUITE(pa_utest)

std::vector<float> dest1 = { 10.0, 10.0, 8.0 };
std::vector<float> dest2 = { 10.0, 0.0, 10.0 };

BOOST_AUTO_TEST_CASE(initially)
{
    Vertical vert("r2d2");
    BOOST_CHECK(Vertical::getType() == "vertical");
    BOOST_CHECK(vert.getId() == "r2d2");

    BOOST_CHECK(size(vert.getPosition()) == 3);

    if (size(vert.getPosition()) == 3)
    {
        BOOST_CHECK(vert.getPosition()[0] == 0.0);
        BOOST_CHECK(vert.getPosition()[1] == 0.0);
        BOOST_CHECK(vert.getPosition()[2] == 0.0);
    }

    BOOST_CHECK(vert.getFtime() == 0.0);
}

BOOST_AUTO_TEST_CASE(after_one_flight)
{
    Vertical vert("r2d2");
    vert.flyToDest(dest1[0], dest1[1], dest1[2], 10);
    BOOST_CHECK(Vertical::getType() == "vertical");
    BOOST_CHECK(vert.getId() == "r2d2");

    BOOST_CHECK(size(vert.getPosition()) == 3);

    if (size(vert.getPosition()) == 3)
    {
        BOOST_CHECK(fabs(vert.getPosition()[0] - dest1[0]) < 0.1);
        BOOST_CHECK(fabs(vert.getPosition()[1] - dest1[1]) < 0.1);
        BOOST_CHECK(vert.getPosition()[2] == 0.0);
    }

    BOOST_CHECK(fabs(vert.getFtime() - 38.0) < 3);
}

BOOST_AUTO_TEST_CASE(after_two_flights)
{
    Vertical vert("r2d2");
    vert.flyToDest(dest1[0], dest1[1], dest1[2], 10);
    vert.flyToDest(dest2[0], dest2[1], dest2[2], 15);
    BOOST_CHECK(Vertical::getType() == "vertical");
    BOOST_CHECK(vert.getId() == "r2d2");

    BOOST_CHECK(size(vert.getPosition()) == 3);

    if (size(vert.getPosition()) == 3)
    {
        BOOST_CHECK(fabs(vert.getPosition()[0] - dest2[0]) < 0.1);
        BOOST_CHECK(fabs(vert.getPosition()[1] - dest2[1]) < 0.1);
        BOOST_CHECK(vert.getPosition()[2] == 0.0);
    }
}

BOOST_AUTO_TEST_CASE(angle)
{
    BOOST_CHECK(fabs(Vertical::angle(1.0, 1.0, 1.0, 1.0) - 0.0) < 0.001);
    BOOST_CHECK(fabs(Vertical::angle(0.0, 0.0, 0.0, 1.0) - 0.0) < 0.001);
    BOOST_CHECK(fabs(Vertical::angle(0.0, 0.0, 1.0, 2.0) - 26.5651) < 0.001);
    BOOST_CHECK(fabs(Vertical::angle(1.0, 1.0, 2.0, 2.0) - 45.0) < 0.001);
    BOOST_CHECK(fabs(Vertical::angle(0.0, 0.0, 2.0, 1.0) - 63.4349) < 0.001);

    BOOST_CHECK(fabs(Vertical::angle(1.0, 1.0, 2.0, 1.0) - 90.0) < 0.001);
    BOOST_CHECK(fabs(Vertical::angle(0.0, 0.0, 2.0, -1.0) - 116.565) < 0.001);
    BOOST_CHECK(fabs(Vertical::angle(-1.0, 1.0, 0.0, 0.0) - 135.0) < 0.001);
    BOOST_CHECK(fabs(Vertical::angle(0.0, 0.0, 1.0, -2.0) - 153.435) < 0.001);
    BOOST_CHECK(fabs(Vertical::angle(55.0, 20.0, 95.0, -115.0) - 163.496) < 0.001);

    BOOST_CHECK(fabs(Vertical::angle(0.0, 0.0, 0.0, -1.0) - 180.0) < 0.001);
    BOOST_CHECK(fabs(Vertical::angle(9.99996185, 9.99996185, 10.0, 0.0) - 180.0) < 0.001);
    BOOST_CHECK(fabs(Vertical::angle(0.0, 1.0, -1.0, -3.0)-  194.036) < 0.001);
    BOOST_CHECK(fabs(Vertical::angle(0.0, 0.0, -1.0, -2.0) - 206.565) < 0.001);
    BOOST_CHECK(fabs(Vertical::angle(0.0, 0.0, -1.0, -1.0) - 225.0) < 0.001);
    BOOST_CHECK(fabs(Vertical::angle(0.0, 0.0, -2.0, -1.0) - 243.435) < 0.001);

    BOOST_CHECK(fabs(Vertical::angle(0.0, 0.0, -1.0, 0.0) - 270.0) < 0.001);
    BOOST_CHECK(fabs(Vertical::angle(0.0, 0.0, -2.0, 1.0) - 296.565) < 0.001);
    BOOST_CHECK(fabs(Vertical::angle(1.0, 1.0, 0.0, 2.0) - 315.0) < 0.001);
    BOOST_CHECK(fabs(Vertical::angle(0.0, 0.0, -1.0, 2.0) - 333.435) < 0.001);
    BOOST_CHECK(fabs(Vertical::angle(0.0, 0.0, -10.0, 30.0) - 341.565) < 0.001);
    BOOST_CHECK(fabs(Vertical::angle(-1.0, -1.0, -1.9, 30.0) - 358.337) < 0.001);
}

BOOST_AUTO_TEST_CASE(type_checks)
{
    BOOST_CHECK(std::is_class_v<Vertical>);
}

BOOST_AUTO_TEST_SUITE_END()
