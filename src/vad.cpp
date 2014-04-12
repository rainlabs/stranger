/* 
 * File:   vad.cpp
 * Author: Vladimir Zyablitskiy <https://github.com/rainlabs>
 * 
 * Created on 12 апреля 2014 г., 13:34
 */

#include "stranger/vad.hpp"

namespace Stranger {
    Vad::Vad()
        : mDuration(0), mShift(0), mLifterInd(1) {
        mMfcc = nullptr;
        mSignal = nullptr;
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
    
    Vad& Vad::destroyMfcc() {
        if(mMfcc != nullptr)
            delete mMfcc;
        mMfcc = nullptr;
        return (*this);
    }
    
    std::vector<bool> Vad::process() {
        std::vector<bool> ret;
        SizeType duration = Misc::msToFrameSize(mDuration, mSignal->getSampleRate());
        SizeType shift = Misc::msToFrameSize(mShift, mSignal->getSampleRate());
        float threshold = 2.5;
        
        if(!initialized()) {
            if (mSignal == nullptr) {
                throw StrangerException("Sound file is not specified");
            }
            mMfcc = new Mfcc( 
                    duration,
                    24,
                    16
                );
            mMfcc->initializeFft(Window::HAMMING)
                    .initializeTrifBank(mSignal->getSampleRate())
                    .initializeLifter(mLifterInd);
        }
        
        vector2d frames = mSignal->split(duration, shift);
        
        for(auto frame : frames) {
            if( Misc::energy(mMfcc->apply(frame), true) < threshold ) {
                ret.push_back(false);
            } else {
                ret.push_back(true);
            }
        }
        
        return ret;
    }
}