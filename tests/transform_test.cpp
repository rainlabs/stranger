/* 
 * File:   transform_test.cpp
 * Author: Vladimir Zyablitskiy <https://github.com/rainlabs>
 * 
 * Created on 10 апреля 2014 г., 23:32
 */

#include "transform_test.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(TransformTest);

TransformTest::TransformTest() {
    mSoundFile = "fixtures/samplePalette.wav";
    mWav.loadFromFile(mSoundFile);
    mFftSize = Misc::msToFrameSize(30, mWav.getSampleRate());
    mShift = Misc::msToFrameSize(15, mWav.getSampleRate());
}

TransformTest::~TransformTest() {
}

void TransformTest::setUp() {
}

void TransformTest::tearDown() {
}

void TransformTest::plotDft() {
//    CPPUNIT_ASSERT(mfcc->mDuration     == 30);
    std::string filename = "result/0dft";
    vector2d matrix;
    std::vector<float> x, y;
    int i;
    Fft fft(mFftSize, Window::HAMMING);
    float hzInterval = (float) mFftSize / mWav.getSampleRate();
    vector2d frames = mWav.split(SizeType(mFftSize), SizeType(mShift));
    
    for(auto frame : frames) {
        matrix.push_back( fft.execute2r(frame, mShift) );
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
    std::string filename = "result/1dftOnTrifBank";
    vector2d matrix;
    std::vector<float> x, y;
    int i;
    Fft fft(mFftSize, Window::HAMMING);
    TrifBank bank(24, mFftSize, mWav.getSampleRate());
    float hzInterval = (float) mFftSize / mWav.getSampleRate();
    vector2d frames = mWav.split(SizeType(mFftSize), SizeType(mShift));
    
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
//    FILE* file = fopen("9mfccraw.pcm", "wb");
    std::string filename = "result/2mfcc";
    vector2d matrix;
    std::vector<float> x, y;
    int i;
//    float tmp;
    float hzInterval = (float) mFftSize / mWav.getSampleRate();
    vector2d frames = mWav.split(SizeType(mFftSize), SizeType(mShift));
    Mfcc mfcc(mFftSize, 24, 12);
    mfcc.initializeFft(Window::HAMMING)
            .initializeTrifBank(mWav.getSampleRate());
//            .initializeLifter(12);
    
    for(auto frame : frames) {
        matrix.push_back( mfcc.apply(frame) );
//        for(auto m : matrix.back()) {
//            tmp = m;
//            fwrite(&tmp, sizeof(float), 1, file);
//        }
    }
    
    for(i = 0; i < matrix.size(); i++)
        x.push_back( i );
    for(i = 0; i < matrix.back().size(); i++)
        y.push_back( i );
    
    TestHelper::saveMatrix(matrix, x, y, filename);
    TestHelper::plotMatrix(filename);
//    fclose(file);
}

void TransformTest::plotDeltaMfcc() {
    std::string filename = "result/2mfcc_delta";
    vector2d matrix;
    std::vector<float> x, y;
    int i;
    float hzInterval = (float) mFftSize / mWav.getSampleRate();
    vector2d frames = mWav.split(SizeType(mFftSize), SizeType(mShift));
    Mfcc mfcc(mFftSize, 24, 12);
    mfcc.initializeFft(Window::HAMMING)
            .initializeTrifBank(mWav.getSampleRate());
    
    for(auto frame : frames) {
        matrix.push_back( mfcc.apply(frame) );
    }
    auto matrix2 = Mfcc::delta(matrix, 2);
    
    for(i = 0; i < matrix2.size(); i++)
        x.push_back( i );
    for(i = 0; i < matrix2.back().size(); i++)
        y.push_back( i );
    
    TestHelper::saveMatrix(matrix2, x, y, filename);
    TestHelper::plotMatrix(filename);
}

void TransformTest::plotLifterMfcc() {
    std::string filename = "result/3liftermfcc";
    vector2d matrix;
    std::vector<float> x, y;
    int i;
    float hzInterval = (float) mFftSize / mWav.getSampleRate();
    vector2d frames = mWav.split(SizeType(mFftSize), SizeType(mShift));
    Mfcc mfcc(mFftSize, 24, 12);
    mfcc.initializeFft(Window::HAMMING)
            .initializeTrifBank(mWav.getSampleRate())
            .initializeLifter(4);
    
    for(auto frame : frames) {
        matrix.push_back( mfcc.apply(frame) );
    }
    
    for(i = 0; i < matrix.size(); i++)
        x.push_back( i );
    for(i = 0; i < matrix.back().size(); i++)
        y.push_back( i );
    
    FILE* file = fopen("result/mfcc.pcm", "wb");
    for (auto m : matrix) {
        for(SampleType val : m) {
            float temp = (float) val;
            fwrite(&temp, sizeof(float), 1, file);
        }
    }
    fclose(file);
    
    TestHelper::saveMatrix(matrix, x, y, filename);
    TestHelper::plotMatrix(filename);
}

void TransformTest::plotEnergy() {
    std::string filename = "result/4energy";
    vector2d matrix;
    std::vector<SampleType> temp;
    std::vector<float> x, y;
    int i;
    float hzInterval = (float) mFftSize / mWav.getSampleRate();
    vector2d frames = mWav.split(SizeType(mFftSize), SizeType(mShift));
    Mfcc mfcc(mFftSize, 24, 12);
    mfcc.initializeFft(Window::HAMMING)
            .initializeTrifBank(mWav.getSampleRate());
    
    for(auto frame : frames) {
        temp.push_back( Misc::energy(mfcc.apply(frame), false) );
    }
    matrix.push_back(temp);
    
    for(i = 0; i < matrix.back().size(); i++) {
        x.push_back( i );
    }
    
    TestHelper::savePoints(matrix, x, filename);
    TestHelper::plotPoints(filename);
}

void TransformTest::plotLogEnergy() {
    std::string filename = "result/5log_energy";
    vector2d matrix;
    std::vector<SampleType> temp;
    std::vector<float> x, y;
    int i;
    float hzInterval = (float) mFftSize / mWav.getSampleRate();
    vector2d frames = mWav.split(SizeType(mFftSize), SizeType(mShift));
    Mfcc mfcc(mFftSize, 24, 12);
    mfcc.initializeFft(Window::HAMMING)
            .initializeTrifBank(mWav.getSampleRate());
    
    for(auto frame : frames) {
        temp.push_back( Misc::energy(mfcc.apply(frame), true) );
    }
    matrix.push_back(temp);
    
    for(i = 0; i < matrix.back().size(); i++) {
        x.push_back( i );
    }
    
    TestHelper::savePoints(matrix, x, filename);
    TestHelper::plotPoints(filename);
}

void TransformTest::plotWavForm() {
    std::string filename = "result/6wav";
    vector2d matrix;
    std::vector<SampleType> temp;
    std::vector<float> x, y;
    int i;
    float hzInterval = (float) mFftSize / mWav.getSampleRate();
    
    for(auto d : mWav) {
        temp.push_back(d);
    }
    matrix.push_back(temp);
    
    for(i = 0; i < matrix.back().size(); i++) {
        x.push_back( i * (1.0 / mShift ) * 0.015 );
    }
    
    TestHelper::savePoints(matrix, x, filename);
//    TestHelper::plotPoints(filename);
}

void TransformTest::plotVad() {
    std::string filename = "result/6wav";
    vector2d matrix;
    std::vector<float> x;
    int i;
    Vad vad;
    vad.setDuration(30).setShift(15).setLifterIndex(3).setFrame(10).loadSignal("fixtures/samplePalette.wav");
//    vad.process(Vad::TRAIN);
    matrix.push_back(vad.loadSignal(mSoundFile).destroyMfcc().process());
    
    for(i = 0; i < matrix.back().size(); i++) {
        x.push_back( i * 0.015 /* 10*/ );
    }
    
    TestHelper::savePoints(matrix, x, filename, 1);
//    TestHelper::plotPoints(filename);
}