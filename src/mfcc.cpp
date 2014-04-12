/* 
 * File:   mfcc.cpp
 * Author: Vladimir Zyablitskiy <https://github.com/rainlabs>
 * 
 * Created on 10 апреля 2014 г., 21:31
 */

#include "mfcc.hpp"

namespace Stranger {
    Mfcc::Mfcc(SizeType fftSize, SizeType trifBankSize, SizeType outSize) 
        : mFftSize(fftSize), mTrifBankSize(trifBankSize), mDctSize(outSize) {
        mFft      = nullptr;
        mTrifBank = nullptr;
        
        mDct    = new Dct(mTrifBankSize, mDctSize);
        mLifter = new Lifter(1, mDctSize);
    }

    Mfcc::~Mfcc() {}
    
    Mfcc& Mfcc::initializeFft(SizeType windowType) {
        if (mFft != nullptr) {
            delete mFft;
        }
        mFft = new Fft(mFftSize, windowType);
        return (*this);
    }
    
    Mfcc& Mfcc::initializeTrifBank(float sampleFreq, float minFreq, float maxFreq) {
        if (mTrifBank != nullptr) {
            delete mTrifBank;
        }
        mTrifBank = new TrifBank(mTrifBankSize, mFftSize, sampleFreq, minFreq, maxFreq);
        return (*this);
    }
    
    Mfcc& Mfcc::initializeLifter(int l) {
        if (mLifter != nullptr) {
            delete mLifter;
        }
        mLifter = new Lifter(l, mDctSize);
        return (*this);
    }
    
    std::vector<SampleType> Mfcc::apply(std::vector<SampleType> frame) {
        if (mFft == nullptr || mTrifBank == nullptr || mDct == nullptr || mLifter == nullptr) {
            throw StrangerException("Some transform not defined yet!");
        }
        return mLifter->apply( mDct->apply( mTrifBank->apply( mFft->execute(frame) ) ) );
    }
}