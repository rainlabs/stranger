/* 
 * File:   vad.cpp
 * Author: Vladimir Zyablitskiy <https://github.com/rainlabs>
 * 
 * Created on 12 апреля 2014 г., 13:34
 */

#include "stranger/vad.hpp"

namespace Stranger {
    Vad::Vad(std::string svmDB, int mode)
        : mDuration(0), mShift(0), mLifterInd(1),
            mMode(mode), mVoice(+1), mSvmDb(svmDB), mFrameSize(1) {
        mMfcc   = nullptr;
        mSignal = nullptr;
        mSvm    = nullptr;
    }

    Vad::~Vad() {
        if(mMfcc != nullptr)
            delete mMfcc;
        if(mSignal != nullptr)
            delete mSignal;
    }
    
    bool Vad::initialized() {
        if(mSignal == nullptr || mMfcc == nullptr)
            return false;
        return true;
    }
    
    Vad& Vad::loadSignal(std::string filename) {
        if(mSignal != nullptr)
            delete mSignal;
        
        mSignal = new Signal;
        if (!mSignal->loadFromFile(filename))
            throw StrangerException("Cannot open filename:" + filename);
        
        return (*this);
    }
    
    Vad& Vad::setDuration(SizeType duration) {
        mDuration = duration;
        return (*this);
    }
    
    Vad& Vad::setShift(SizeType shift) {
        mShift = shift;
        return (*this);
    }
    
    Vad& Vad::setLifterIndex(SizeType l) {
        if (l != 0)
            mLifterInd = l;
        return (*this);
    }
    
    Vad& Vad::setVoice() {
        mVoice = +1;
        return (*this);
    }
    
    Vad& Vad::setSilence() {
        mVoice = -1;
        return (*this);
    }
    
    Vad& Vad::setMode(int mode) {
        mMode = mode;
        return (*this);
    }
    
    Vad& Vad::setFrame(SizeType size) {
        if (mFrameSize != 0)
            mFrameSize = size;
        return (*this);
    }
    
    Vad& Vad::saveSVM() {
        if(mSvm == nullptr) {
            throw StrangerException("SVM not specified");
        }
        mSvm->train();
        mSvm->save(mSvmDb);
        return (*this);
    }
    
    Vad& Vad::trainSVM() {
        if(mSvm == nullptr) {
            throw StrangerException("SVM not specified");
        }
        mSvm->train();
        return (*this);
    }
    
    Vad& Vad::destroyMfcc() {
        if(mMfcc != nullptr)
            delete mMfcc;
        mMfcc = nullptr;
        return (*this);
    }
    
    std::vector<SampleType> Vad::process() {
        std::vector<SampleType> ret;
        SizeType duration = Misc::msToFrameSize(mDuration, mSignal->getSampleRate());
        SizeType shift = Misc::msToFrameSize(mShift, mSignal->getSampleRate());
        float threshold = 2.5;
        SizeType mfccCount = 16;
        
        if(!initialized()) {
            if (mSignal == nullptr) {
                throw StrangerException("Sound file is not specified");
            }
            mMfcc = new Mfcc( 
                    duration,
                    24,
                    mfccCount
                );
            mMfcc->initializeFft(Window::HAMMING)
                    .initializeTrifBank(mSignal->getSampleRate(), 0.0, (4500.0 / mSignal->getSampleRate()) )
                    .initializeLifter(mLifterInd);
        }
        
        if (mSvm == nullptr) {
            mSvm = new SVM(mfccCount * mFrameSize, mSvmDb);
            if(mMode == PREDICT) {
                mSvm->load(mSvmDb);
            }
        }
        std::vector<SampleType> bank;
        
        vector2d frames = mSignal->split(duration, shift);
        
        for(auto frame : frames) {
            auto features = mMfcc->apply(frame);
            bank.insert(bank.end(), features.begin(), features.end());
            if (bank.size() == (mfccCount*mFrameSize)) {
                if (mMode == PREDICT) {
                    ret.push_back (mSvm->predict(bank) );
                } else if (mMode == TRAIN) {
                    mSvm->push_back(bank, mVoice);
                }
                bank.clear();
            }
//            if( Misc::energy(mMfcc->apply(frame), true) < threshold ) {
//                ret.push_back(false);
//            } else {
//                ret.push_back(true);
//            }
        }
        
        return ret;
    }
}