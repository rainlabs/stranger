/* 
 * File:   fft_test.cpp
 * Author: rain
 * 
 * Created on 10 апреля 2014 г., 23:32
 */

#include "fft_test.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(FftTest);

FftTest::FftTest() {
}

FftTest::~FftTest() {
}

void FftTest::setUp() {
}

void FftTest::tearDown() {
}

void FftTest::plotDft() {
//    CPPUNIT_ASSERT(mfcc->mDuration     == 30);
    std::cout << version() << std::endl;
    Signal wav;
    std::string filename = "result/0dft";
    vector2d matrix;
    std::vector<float> x, y;
    int i;
    Fft fft(256, Window::HAMMING);
    wav.loadFromFile("fixtures/voice1.wav");
    float hzInterval = 256.0 / wav.getSampleRate();
    vector2d frames = wav.split(256, 128);
    
    for(auto frame : frames) {
        matrix.push_back( fft.execute2r(frame) );
    }
    
    for(i = 0; i < matrix.size(); i++) {
        for(int j = 0; j < matrix[i].size(); j++) {
            matrix[i][j] = log(matrix[i][j]);
        }
    }
    
    for(i = 0; i < matrix.size(); i++)
        x.push_back( i );
    for(i = 0; i < matrix.back().size(); i++)
        y.push_back( i*hzInterval );
    
    TestHelper::saveMatrix(matrix, x, y, filename);
    TestHelper::plotMatrix(filename);
}