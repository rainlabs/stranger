/* 
 * File:   fft_test.cpp
 * Author: Vladimir Zyablitskiy <https://github.com/rainlabs>
 * 
 * Created on 10 апреля 2014 г., 23:32
 */

#include "transform_test.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(TransformTest);

TransformTest::TransformTest() {
}

TransformTest::~TransformTest() {
}

void TransformTest::setUp() {
}

void TransformTest::tearDown() {
}

void TransformTest::plotDft() {
//    CPPUNIT_ASSERT(mfcc->mDuration     == 30);
    Signal wav;
    std::string filename = "result/0dft";
    vector2d matrix;
    std::vector<float> x, y;
    int i;
    Fft fft(256, Window::HAMMING);
    wav.loadFromFile("fixtures/voice1.wav");
    float hzInterval = 256.0 / wav.getSampleRate();
    vector2d frames = wav.split(SizeType(256), SizeType(128));
    
    for(auto frame : frames) {
        matrix.push_back( fft.execute2r(frame, 128) );
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

void TransformTest::plotDftOnTrifBank() {
    Signal wav;
    std::string filename = "result/1dftOnTrifBank";
    vector2d matrix;
    std::vector<float> x, y;
    int i;
    Fft fft(256, Window::HAMMING);
    wav.loadFromFile("fixtures/voice1.wav");
    TrifBank bank(24, 256, wav.getSampleRate());
    float hzInterval = 256.0 / wav.getSampleRate();
    vector2d frames = wav.split(SizeType(256), SizeType(128));
    
    for(auto frame : frames) {
        matrix.push_back( bank.apply( fft.execute(frame) ) );
    }
    
//    for(i = 0; i < matrix.size(); i++) {
//        for(int j = 0; j < matrix[i].size(); j++) {
//            matrix[i][j] = log(matrix[i][j]);
//        }
//    }
    
    for(i = 0; i < matrix.size(); i++)
        x.push_back( i );
    for(i = 0; i < matrix.back().size(); i++)
        y.push_back( i );
    
    TestHelper::saveMatrix(matrix, x, y, filename);
    TestHelper::plotMatrix(filename);
}

void TransformTest::plotMfcc() {
    Signal wav;
    std::string filename = "result/2mfcc";
    vector2d matrix;
    std::vector<float> x, y;
    int i;
    Fft fft(256, Window::HAMMING);
    wav.loadFromFile("fixtures/voice1.wav");
    TrifBank bank(24, 256, wav.getSampleRate());
    Dct dct;
    float hzInterval = 256.0 / wav.getSampleRate();
    vector2d frames = wav.split(SizeType(256), SizeType(128));
    
    for(auto frame : frames) {
        matrix.push_back( dct.apply( bank.apply( fft.execute(frame) ) ) );
    }
    
//    for(i = 0; i < matrix.size(); i++) {
//        for(int j = 0; j < matrix[i].size(); j++) {
//            matrix[i][j] = log(matrix[i][j]);
//        }
//    }
    
    for(i = 0; i < matrix.size(); i++)
        x.push_back( i );
    for(i = 0; i < matrix.back().size(); i++)
        y.push_back( i );
    
    TestHelper::saveMatrix(matrix, x, y, filename);
    TestHelper::plotMatrix(filename);
}

void TransformTest::plotLifterMfcc() {
    Signal wav;
    std::string filename = "result/3liftermfcc";
    vector2d matrix;
    std::vector<float> x, y;
    int i;
    Fft fft(256, Window::HAMMING);
    wav.loadFromFile("fixtures/voice1.wav");
    TrifBank bank(24, 256, wav.getSampleRate());
    Dct dct;
    Lifter lifter(3, 12);
    float hzInterval = 256.0 / wav.getSampleRate();
    vector2d frames = wav.split(SizeType(256), SizeType(128));
    
    for(auto frame : frames) {
        matrix.push_back( lifter.apply( dct.apply( bank.apply( fft.execute(frame) ) ) ) );
    }
    
//    for(i = 0; i < matrix.size(); i++) {
//        for(int j = 0; j < matrix[i].size(); j++) {
//            matrix[i][j] = log(matrix[i][j]);
//        }
//    }
    
    for(i = 0; i < matrix.size(); i++)
        x.push_back( i );
    for(i = 0; i < matrix.back().size(); i++)
        y.push_back( i );
    
    TestHelper::saveMatrix(matrix, x, y, filename);
    TestHelper::plotMatrix(filename);
}

void TransformTest::plotEnergy() {
    Signal wav;
    std::string filename = "result/4energy";
    vector2d matrix;
    std::vector<SampleType> temp;
    std::vector<float> x, y;
    int i;
    Fft fft(256, Window::HAMMING);
    wav.loadFromFile("fixtures/voice1.wav");
    TrifBank bank(24, 256, wav.getSampleRate());
    Dct dct;
    float hzInterval = 256.0 / wav.getSampleRate();
    vector2d frames = wav.split(SizeType(256), SizeType(128));
    
    for(auto frame : frames) {
        temp.push_back( Misc::energy(dct.apply( bank.apply( fft.execute(frame) ) ), false) );
    }
    matrix.push_back(temp);
    
    for(i = 0; i < matrix.back().size(); i++) {
        x.push_back( i );
    }
    
    TestHelper::savePoints(matrix, x, filename);
    TestHelper::plotPoints(filename);
}

void TransformTest::plotLogEnergy() {
    Signal wav;
    std::string filename = "result/5log_energy";
    vector2d matrix;
    std::vector<SampleType> temp;
    std::vector<float> x, y;
    int i;
    Fft fft(256, Window::HAMMING);
    wav.loadFromFile("fixtures/voice1.wav");
    TrifBank bank(24, 256, wav.getSampleRate());
    Dct dct;
    float hzInterval = 256.0 / wav.getSampleRate();
    vector2d frames = wav.split(SizeType(256), SizeType(128));
    
    for(auto frame : frames) {
        temp.push_back( Misc::energy(dct.apply( bank.apply( fft.execute(frame) ) ), true) );
    }
    matrix.push_back(temp);
    
    for(i = 0; i < matrix.back().size(); i++) {
        x.push_back( i );
    }
    
    TestHelper::savePoints(matrix, x, filename);
    TestHelper::plotPoints(filename);
}