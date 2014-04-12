/* 
 * File:   trif_bank.hpp
 * Author: Vladimir Zyablitskiy <https://github.com/rainlabs>
 *
 * Created on 11 апреля 2014 г., 14:18
 */

#ifndef TRIF_BANK_HPP
#define	TRIF_BANK_HPP

#include "global.hpp"
#include "stranger_exception.hpp"
#include <math.h>

#define Round(x) ((int)ceil(x) - x < x - (int)floor(x)) ? (int)ceil(x) : (int)floor(x)

namespace Stranger {
    class STRANGER_EXPORT TrifBank {
    public:
        /*
         * Set cut-off indexes on a MEL scale
         */
        TrifBank(SizeType filterCount, SizeType fftSize, float sampleFreq, float minFreq = 0.0, float maxFreq = 0.0);
        
        /*
         * Set cut-off indexes on a alpha-transformed scale
         */
        TrifBank(float alpha, SizeType filterCount, SizeType fftSize, float sampleFreq, float minFreq = 0.0, float maxFreq = 0.0);

        virtual ~TrifBank();
        
        std::vector<SampleType> apply(SpectrumType fftOut);
    protected:
        /*
         * Return the value corresponding to Mel frequency f on a 
         * linear scale.
         *   Mel(f) = 2595 * log10(1 + f / 700)
         *   mel_inv(f) = 700 * (10 ^ (f / 2595) - 1)
         */
        float hzToMel(float hz);
        float melToHz(float mel);
        
        /*
         * The function determines the pulsation value on the transformed
         * axis (omega), assuming a spectral factor alpha.
         * 
         * For details on this, refer to:
         *       "Analyse spectrale a resolution variable", Ph.D. Thesis,
         *       Christian Chouzenoux, ENST
         * In this Ph.D., we are given omega'=theta(omega).
         */
        float theta(float o, float a);
        
        /*
         * The function determines the pulsation value on the original
         * axis (omega), assuming a spectral factor alpha.
         * 
         * For details on this, refer to:
         *       "Analyse spectrale a resolution variable", Ph.D. Thesis,
         *       Christian Chouzenoux, ENST
         *
         * In this Ph.D., we are given omega'=theta(omega). As I don't feel
         * like finding out an analytical solution to the inverse problem,
         * I simply look for a dichotomic solution to the problem by using
         * omega in the range [0,PI], as the transformation is monotonous.
         *
         * oop: original omega'
         * op:  omega'
         * opmem: omega' memory
         *
         * NOTE: If someone feels like programming an analytical solution
         * to the problem, he is welcome! Have fun ...
         *
         */
        float thetaInv(float oop,float a);
    private:
        std::vector<SizeType> mFilterBank;
        SizeType mSize;
        SizeType mFftSize;

    };
}

#endif	/* TRIF_BANK_HPP */

