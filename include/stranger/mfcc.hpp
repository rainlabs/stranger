/* 
 * File:   mfcc.hpp
 * Author: Vladimir Zyablitskiy <https://github.com/rainlabs>
 *
 * Created on 10 апреля 2014 г., 21:31
 */

#ifndef MFCC_HPP
#define	MFCC_HPP

#include "global.hpp"
#include "stranger_exception.hpp"
#include "transform.hpp"
#include "fft.hpp"
#include "trif_bank.hpp"
#include "dct.hpp"
#include "lifter.hpp"
#include "misc.hpp"

namespace Stranger {
    
    /**
     * @brief class for MFCC extract
     */
    class STRANGER_EXPORT Mfcc : public Transform {
    public:
        Mfcc(SizeType fftSize, SizeType trifBankSize, SizeType outSize);
        virtual ~Mfcc();
        
        Mfcc& initializeFft(SizeType windowType = 0);
        Mfcc& initializeTrifBank(float sampleFreq, float minFreq = 0.0, float maxFreq = 0.0);
        Mfcc& initializeLifter(int l);
        
        /**
         * @brief compute delta coefficients
         * @param mfccFeatures static or first delta features
         * @param N range
         * @return 
         */
        static vector2d delta(vector2d mfccFeatures, SizeType N=1);
        
        /**
         * @brief apply MFCC transform at frame
         * @param frame of signal
         * @return 
         */
        std::vector<SampleType> apply(std::vector<SampleType> frame);
    private:
        SizeType  mFftSize;
        SizeType  mTrifBankSize;
        SizeType  mDctSize;
        
        Fft*      mFft;
        TrifBank* mTrifBank;
        Dct*      mDct;
        Lifter*   mLifter;

    };
}

#endif	/* MFCC_HPP */

