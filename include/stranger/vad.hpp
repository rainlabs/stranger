/* 
 * File:   vad.hpp
 * Author: Vladimir Zyablitskiy <https://github.com/rainlabs>
 *
 * Created on 12 апреля 2014 г., 13:34
 */

#ifndef VAD_HPP
#define	VAD_HPP

#include "global.hpp"
#include "stranger_exception.hpp"
#include "signal.hpp"
#include "misc.hpp"
#include "mfcc.hpp"
#include "svm.hpp"
#include <math.h>
#include <list>
#include <algorithm>

#include <iostream>
#include <fstream>

#define MIN_VOICE_DURATION 90 // 90 ms for speech detection
#define STRANGER_FRAME_DEVIATION 0.01
#define STRANGER_SFM_WHITE_NOIZE 0.8
#define STRANGER_MIN_MEAN 0.08

namespace Stranger {
    
    class Vad {
    public:
        enum Mode {
            TRAIN,
            PREDICT
        };
        
        Vad();
        virtual ~Vad();
        
        Vad& loadSignal(std::string filename);
        
        /**
         * VAD Techniques for Real-Time Speech Transmission on the Internet
         * Current VoIP systems use 20-40ms frame sizes
         * 
         * @param duration
         * @return 
         */
        Vad& setDuration(SizeType duration);
        Vad& setShift(SizeType shift);
        Vad& setLifterIndex(SizeType l);
        Vad& setFrame(SizeType size);
        Vad& destroyMfcc();
        
        bool initialized();
        
        /**
         * @brief vad process
         * @param mode (PREDICT|TRAIN)
         * @return 
         */
        std::vector<SampleType> process(SizeType mode=PREDICT);
    protected:
        /**
         * @brief extract frames without sinus, white noize and frames have small deviation mfcc
         * @return 
         */
        vector2d extractFrames();
        
        SampleType getMean(std::vector<SampleType> values);
        SampleType getDeviation(std::vector<SampleType> values);
        SampleType getDeviation(std::list<SampleType> values);
    private:
        SizeType mDuration;
        SizeType mShift;
        SizeType mLifterInd;
        SizeType mFrameSize;
        SizeType mMfccSize;
        Signal*  mSignal;
        Mfcc*    mMfcc;

    };
}

#endif	/* VAD_HPP */

