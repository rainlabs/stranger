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
#include <math.h>
#include <algorithm>

#include <iostream>
#include <fstream>

#define MIN_VOICE_DURATION 90 // 90 ms for speech detection

namespace Stranger {
    
    class Vad {
    public:
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
        Vad& destroyMfcc();
        
        bool initialized();
        std::vector<bool> process();
    private:
        SizeType mDuration;
        SizeType mShift;
        SizeType mLifterInd;
        Signal*  mSignal;
        Mfcc*    mMfcc;

    };
}

#endif	/* VAD_HPP */

