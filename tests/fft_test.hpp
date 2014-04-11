/* 
 * File:   fft_test.hpp
 * Author: rain
 *
 * Created on 10 апреля 2014 г., 23:32
 */

#ifndef FFT_TEST_HPP
#define	FFT_TEST_HPP

#define UNIT_TEST
class FftTest;

#include <string>
#include <cppunit/extensions/HelperMacros.h>
#include <iostream>
#include <math.h>
#include "test_helper.hpp"
#include "stranger.hpp"

using namespace Stranger;

class FftTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(FftTest);

    CPPUNIT_TEST(plotDft);
    CPPUNIT_TEST_SUITE_END();

public:
    FftTest();
    virtual ~FftTest();
    void setUp();
    void tearDown();

private:
    void plotDft();
};

#endif	/* FFT_TEST_HPP */

