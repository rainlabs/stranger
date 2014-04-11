/* 
 * File:   trif_bank.cpp
 * Author: Vladimir Zyablitskiy <https://github.com/rainlabs>
 * 
 * Created on 11 апреля 2014 г., 14:18
 */

#include "trif_bank.hpp"

namespace Stranger {
    TrifBank::TrifBank(SizeType filterCount, SizeType fftSize, float sampleFreq, float minFreq, float maxFreq) {
        float startFreq, endFreq;
        int i;
        float f, d, z;
        endFreq = maxFreq;
        
        // TODO exception
        if (filterCount == 0 || fftSize == 0 || sampleFreq <= 0 || minFreq < 0 || maxFreq < 0 ) {
            throw std::exception();
        }
        
        mSize = filterCount;
        mFftSize = fftSize;
        mFilterBank.resize(mSize+2, 0);
        
        if (endFreq <= 0) {
            endFreq = 0.5;
        }
        
        mFilterBank[0] = (SizeType)Round(2 * minFreq * ((float)(fftSize / 2 - 1)));
        mFilterBank[filterCount+1] = (SizeType)Round(2 * endFreq * (float)(fftSize / 2 - 1));
        
        startFreq = hzToMel(minFreq * sampleFreq);
        endFreq   = hzToMel(endFreq * sampleFreq);
        
        d = (endFreq - startFreq) / (float)(filterCount + 1);
        z = (float)(fftSize / 2 - 1) * 2.0 / sampleFreq;
        f = startFreq;
        
        for(i = 1; i <= filterCount; i++) {
            f += d;
            mFilterBank[i] = (SizeType)Round(melToHz(f) * z); /* index in the original domain */
        }
    }

    //TrifBank::TrifBank(const TrifBank& orig) {}

    TrifBank::~TrifBank() {
    }
    
    std::vector<SampleType> TrifBank::apply(SpectrumType fftOut) {
        int i, j, from, to;
        double a, s, m;
        std::vector<SampleType> ret(mSize, 0.0);
        
        // TODO exception
//        if(fftOut.size() != mFftSize) {
//            throw std::exception();
//        }
        
        for(i = 0; i < mSize; i++) {
            s    = 0.0;
            
            /* ascending step from=idx[i] to=idx[i+1]-1: a = 1 / (idx[i+1] - idx[i] + 1) */
            from = mFilterBank[i];
            to   = mFilterBank[i+1];
            a    = 1.0 / (float)(to - from + 1);
            for (j = from; j < to; j++) {
                m = std::abs( fftOut[j] );
                s += m * (1.0 - a * (to - j));
            }
            
            /* descending step from=idx[i+1] to=idx[i+2]: a = 1 / (idx[i+2] - idx[i+1] + 1) */
            from = to;
            to = mFilterBank[i+2];
            a = 1.0 / (float)(to - from + 1);

            for (j = from; j <= to; j++) {
                m = std::abs( fftOut[j] );
                s += m * (1.0 - a * (j - from));
            }
            ret[i] = (s < STRANGER_ENERGY_FLOOR) ? (SampleType)log(STRANGER_ENERGY_FLOOR) : (SampleType)log(s);
//            std::cout << ret[i] << "; ";
        }
//        std::cout << std::endl;
        
        return ret;
    }
    
    float TrifBank::hzToMel(float hz) {
        return (1127.0 * log( 1.0 + hz / 700.0 ));
    }

    float TrifBank::melToHz(float mel) {
        return (700.0 * (exp( mel / 1127.0) - 1.0 ));
    }
}