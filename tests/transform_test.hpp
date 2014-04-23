/* 
 * File:   transform_test.hpp
 * Author: Vladimir Zyablitskiy <https://github.com/rainlabs>
 *
 * Created on 10 апреля 2014 г., 23:32
 */

#ifndef TRANSFORM_TEST_HPP
#define	TRANSFORM_TEST_HPP

#define UNIT_TEST
class TransformTest;

#include <string>
#include <cppunit/extensions/HelperMacros.h>
#include <iostream>
#include <math.h>
#include "test_helper.hpp"
#include "stranger.hpp"

using namespace Stranger;

class TransformTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(TransformTest);

    CPPUNIT_TEST(plotDft);
    CPPUNIT_TEST(plotDftOnTrifBank);
    CPPUNIT_TEST(plotMfcc);
    CPPUNIT_TEST(plotDeltaMfcc);
    CPPUNIT_TEST(plotLifterMfcc);
    CPPUNIT_TEST(plotEnergy);
    CPPUNIT_TEST(plotLogEnergy);
    CPPUNIT_TEST(plotWavForm);
    CPPUNIT_TEST(plotVad);
    CPPUNIT_TEST_SUITE_END();

public:
    TransformTest();
    virtual ~TransformTest();
    void setUp();
    void tearDown();

private:
    void plotDft();
    void plotDftOnTrifBank();
    void plotMfcc();
    void plotDeltaMfcc();
    void plotLifterMfcc();
    void plotEnergy();
    void plotLogEnergy();
    void plotWavForm();
    void plotVad();
    
    Signal mWav;
    std::string mSoundFile;
    SizeType mFftSize, mShift;
};

#endif	/* TRANSFORM_TEST_HPP */

