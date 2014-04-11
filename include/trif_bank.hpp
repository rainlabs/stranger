/* 
 * File:   trif_bank.hpp
 * Author: rain
 *
 * Created on 11 апреля 2014 г., 14:18
 */

#ifndef TRIF_BANK_HPP
#define	TRIF_BANK_HPP

#include "global.hpp"
#include <math.h>
#include <iostream>

#define Round(x) ((int)ceil(x) - x < x - (int)floor(x)) ? (int)ceil(x) : (int)floor(x)
#define SPRO_ENERGY_FLOOR 1.0 // from spro.h

namespace Stranger {
    class STRANGER_EXPORT TrifBank {
    public:
        TrifBank(SizeType filterCount, SizeType fftSize, float sampleFreq, float minFreq = 0.0, float maxFreq = 0.0);
//        TrifBank(const trif_bank& orig);
        virtual ~TrifBank();
        
        std::vector<SampleType> apply(SpectrumType fftOut);
    protected:
        float hzToMel(float hz);
        float melToHz(float mel);
    private:
        std::vector<SizeType> mFilterBank;
        SizeType mSize;
        SizeType mFftSize;

    };
}

#endif	/* TRIF_BANK_HPP */

