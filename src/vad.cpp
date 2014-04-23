/* 
 * File:   vad.cpp
 * Author: Vladimir Zyablitskiy <https://github.com/rainlabs>
 * 
 * Created on 12 апреля 2014 г., 13:34
 */

#include "stranger/vad.hpp"

namespace Stranger {
    Vad::Vad()
        : mDuration(0), mShift(0), mLifterInd(1), mFrameSize(1), mMfccSize(12) {
        mMfcc   = nullptr;
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
        destroyMfcc();            // lazy reinitialize dft size
        
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
    
    Vad& Vad::setFrame(SizeType size) {
        if (mFrameSize != 0)
            mFrameSize = size;
        return (*this);
    }
    
    Vad& Vad::destroyMfcc() {
        if(mMfcc != nullptr)
            delete mMfcc;
        mMfcc = nullptr;
        return (*this);
    }
    
    std::vector<SampleType> Vad::process(SizeType mode) {
        std::vector<SampleType> ret, bank;
        vector2d frames = extractFrames();
        std::vector<SampleType> features(mMfccSize*3);
        SVM svm(mMfccSize*3, "svm.model");
        SampleType cls;
        std::size_t i = 0, j, k;
        std::vector<SizeType> index;
        
        if (mode == PREDICT) {
            svm.load();
        }
        
        for(auto frame : frames) {
            if (frame.size() != 0) {
                for(j = 0; j < frame.size(); j++) {
                    features[j] = frame[j] / 1.0;
                }
                if (mode == TRAIN) {
                    cls = +1;
                    if ( (i > 200 && i < 600) || (i > 2172 && i < 2732) || (i > 2929) ) {
                        cls = -1;
                    }
                    svm.push_back(features, cls);
#ifdef DEBUG
                    std::cout << i << ": " << cls << std::endl;
#endif
                } else if (mode == PREDICT) {
                    cls = svm.predict(features);
//                    if ( cls > 0) {
//                        for(j = i - mFrameSize+1; j <= i; j++) {
////                            std::cout << i << std::endl;
//                            index.push_back(j);
//                        }
//                    }
                    ret.push_back(cls);
                }
            } else if (mode == PREDICT) {
                ret.push_back(0);
            }
            i++;
        }
        
        if (mode == TRAIN) {
            svm.train();
            svm.save();
        } /*else if (mode == PREDICT) {
//            std::sort(index.begin(), index.end());
//            auto it = std::unique(index.begin(), index.end());
//            index.resize( std::distance(index.begin(), it) );
//
//            SizeType lastInd = 0;
//            SizeType c;
//            for(auto ind : index) {
//                c = 0;
//                if ( (ind - lastInd) < (mFrameSize / 2) ) {
//                    c = 1;
//                }
//                for(j = lastInd+1; j < ind; j++) {
//                    ret.push_back(c);
//                }
//                lastInd = ind;
//                ret.push_back(1);
//            }
//            c = 0;
//            if ( (frames.size() - lastInd) < (mFrameSize / 2) ) {
//                c = 1;
//            }
//            for(j = lastInd+1; j < frames.size(); j++) {
//                ret.push_back(c);
//            }
//            for(auto f : frames) {
//                if (f.size() == 0)
//                    ret.push_back(0);
//                else
//                    ret.push_back(1);
//            }
        }*/
        std::cout << i << " : " << ret.size() << std::endl;
        
//        for (j = mFrameSize; j < bank.size(); j += mFrameSize) {
//            std::vector<SampleType> median(bank.begin() + j - mFrameSize, bank.begin() + j);
//            ret.push_back( getMean(median) );
//        }
        
        return ret;
    }
    
    vector2d Vad::extractFrames() {
        vector2d ret;
        SizeType duration = Misc::msToFrameSize(mDuration, mSignal->getSampleRate());
        SizeType shift = Misc::msToFrameSize(mShift, mSignal->getSampleRate());
        SizeType trifBankSize = 24;
        Fft fft(duration, Window::HAMMING);
        std::vector<SizeType> index;
        
        if(!initialized()) {
            if (mSignal == nullptr) {
                throw StrangerException("Sound file is not specified");
            }
            mMfcc = new Mfcc( 
                    duration,
                    trifBankSize,
                    mMfccSize
                );
            mMfcc->initializeFft(Window::HAMMING)
                    .initializeTrifBank(mSignal->getSampleRate(), 0.0, (4500.0 / mSignal->getSampleRate()) )
                    .initializeLifter(mLifterInd);
        }

        vector2d frames = mSignal->split(duration, shift);
        bool haveSilenceFrame, haveWhiteNoize;
        SampleType temp;
        std::list< std::vector<SampleType> > fftBank, mfccBank;      // mMfccSize * mFrameSize
        vector2d mfccFrames;
        std::size_t i, j, k = 0;
        
        for(auto frame : frames) {
            auto features = mMfcc->apply(frame);
            mfccBank.push_back(features);
            mfccFrames.push_back(features);
            fftBank.push_back(fft.execute2r(frame));
            if (fftBank.size() == mFrameSize) {
                haveSilenceFrame = false;
                for(auto d : mfccBank) {
                    if (getDeviation(d) < STRANGER_FRAME_DEVIATION) {
#ifdef DEBUG
                        std::cout << k << ": deviation " << getDeviation(d) << std::endl;
#endif
                        haveSilenceFrame = true;
                        break;
                    }
                }
                haveWhiteNoize = false;
                for(auto d : fftBank) {
                    if (Misc::flatness(d) > STRANGER_SFM_WHITE_NOIZE) {
#ifdef DEBUG
                        std::cout << k << ": white " << Misc::flatness(d) << std::endl;
#endif
                        haveWhiteNoize = true;
                        break;
                    }
                }
                temp = 0;
                if ( !haveSilenceFrame && !haveWhiteNoize) {
                    std::vector<SampleType> devs;
                    for(i = 0; i < mFrameSize; i++) {
                        std::vector<SampleType> vec;
                        for (auto d : mfccBank) {
                            vec.push_back(d[i]);
                        }
                        devs.push_back(getDeviation(vec));
                    }
                    temp = getMean(devs);
                    if (temp < STRANGER_MIN_MEAN) {
                        temp = 0;
                    }
//                    temp = 1;
#ifdef DEBUG
                    std::cout << k << ": " << temp << std::endl;
#endif
                }
                if (temp > 0) {
                    for(j = k - mFrameSize+1; j <= k; j++) {
                        index.push_back(j);
                    }
                }
//                ret.push_back(temp);
                mfccBank.pop_front();
                fftBank.pop_front();
            }
            k++;
        }
        
        auto deltaMfcc = Mfcc::delta(mfccFrames, 4); // delta with 2 range
        auto ddeltaMfcc = Mfcc::delta(deltaMfcc, 4);
        std::sort(index.begin(), index.end());
        auto it = std::unique(index.begin(), index.end());
        index.resize( std::distance(index.begin(), it) );
        
        SizeType lastInd = 0;
        SizeType c;
        for(auto ind : index) {
            c = 0;
            if ( (ind - lastInd) < (mFrameSize / 2) ) {
                c = 1;
            }
            for(j = lastInd+1; j < ind; j++) {
                if (c == 0) {
                    ret.push_back({});
                } else {
                    std::vector<SampleType> vec(mfccFrames[j]);
                    vec.insert(vec.end(), deltaMfcc[j].begin(), deltaMfcc[j].end()); // mfcc + first delta
                    vec.insert(vec.end(), ddeltaMfcc[j].begin(), ddeltaMfcc[j].end()); // + second delta
                    ret.push_back(vec);
                }
            }
            lastInd = ind;
            ret.push_back(mfccFrames[ind]);
        }
        c = 0;
        if ( (mfccFrames.size() - lastInd) < (mFrameSize / 2) ) {
            c = 1;
        }
        for(j = lastInd+1; j < mfccFrames.size(); j++) {
            if (c == 0) {
                ret.push_back({});
            } else {
                ret.push_back(mfccFrames[j]);
            }
        }
        
//#ifdef DEBUG
        std::cout << ret.size() << " : " << mfccFrames.size() << std::endl;
//#endif
        
        return ret;
    }
    
    SampleType Vad::getMean(std::vector<SampleType> values) {
        return (std::accumulate(values.begin(), values.end(), 0.0) / values.size());
    }
    
    SampleType Vad::getDeviation(std::vector<SampleType> values) {
        SampleType mean = 0.0, deviation = 0.0;
        mean = std::accumulate(values.begin(), values.end(), 0.0) / values.size();
        std::for_each(values.begin(), values.end(), [&](const SampleType& el) {
            deviation += pow( (el - mean), 2 );
        });
        deviation = sqrt( (deviation / values.size()) );
        return deviation;
    }
    
    SampleType Vad::getDeviation(std::list<SampleType> values) {
        SampleType mean = 0.0, deviation = 0.0;
        mean = std::accumulate(values.begin(), values.end(), 0.0) / values.size();
        std::for_each(values.begin(), values.end(), [&](const SampleType& el) {
            deviation += pow( (el - mean), 2 );
        });
        deviation = sqrt( (deviation / values.size()) );
        return deviation;
    }
}