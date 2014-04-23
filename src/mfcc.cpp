/* 
 * File:   mfcc.cpp
 * Author: Vladimir Zyablitskiy <https://github.com/rainlabs>
 * 
 * Created on 10 апреля 2014 г., 21:31
 */

#include "stranger/mfcc.hpp"

namespace Stranger {
    Mfcc::Mfcc(SizeType fftSize, SizeType trifBankSize, SizeType outSize) 
        : mFftSize(fftSize), mTrifBankSize(trifBankSize), mDctSize(outSize) {
        mFft      = nullptr;
        mTrifBank = nullptr;
        
        mDct    = new Dct(mTrifBankSize, mDctSize);
        mLifter = new Lifter(1, mDctSize);
    }

    Mfcc::~Mfcc() {
        if(mFft != nullptr)
            delete mFft;
        if(mTrifBank != nullptr)
            delete mTrifBank;
        if(mDct != nullptr)
            delete mDct;
        if(mLifter != nullptr)
            delete mLifter;
    }
    
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
//        return Misc::meanNormalize( mLifter->apply( mDct->apply( mTrifBank->apply( mFft->execute(frame) ) ) ) );
    }
    
    vector2d Mfcc::delta(vector2d mfccFeatures, SizeType N) {
        vector2d ret;
        SampleType sum1, sum2;
        SizeType mfccSize = mfccFeatures.front().size();
        std::size_t i, t, n;
        int left, right;
        if (N == 0) {
            throw StrangerException("\"n\" must be greater than zero");
        }
        for(t = 0; t < mfccFeatures.size(); t++) {
            std::vector<SampleType> vec;
            for(i = 0; i < mfccSize; i++) {
                sum1 = 0; sum2 = 0;
                for(n = 1; n <= N; n++) {
                    left = t - n;
                    right = t + n;
                    if (left < 0)
                        left = 0;
                    if (right > mfccFeatures.size() - 1)
                        right = mfccFeatures.size() - 1;
                    sum1 += n * (mfccFeatures[right][i] - mfccFeatures[left][i]);
                    sum2 += (n*n);
                }
                vec.push_back( sum1 / (2.0*sum2) );
            }
            ret.push_back( vec );
        }
        return ret;
    }
}