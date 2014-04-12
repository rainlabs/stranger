/* 
 * File:   trif_bank.cpp
 * Author: Vladimir Zyablitskiy <https://github.com/rainlabs>
 * 
 * Created on 11 апреля 2014 г., 14:18
 */

#include "stranger/trif_bank.hpp"

namespace Stranger {
    TrifBank::TrifBank(SizeType filterCount, SizeType fftSize, float sampleFreq, float minFreq, float maxFreq) {
        float startFreq, endFreq;
        int i;
        float f, d, z;
        endFreq = maxFreq;
        
        if (filterCount == 0 || fftSize == 0 || sampleFreq <= 0 || minFreq < 0 || maxFreq < 0 ) {
            throw StrangerException("Arguments have not valid size values");
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
    
    TrifBank::TrifBank(float alpha, SizeType filterCount, SizeType fftSize, float sampleFreq, float minFreq, float maxFreq) {
        float startFreq, endFreq;
        int i;
        float f, d, z;
        endFreq = maxFreq;
        
        if (filterCount == 0 || fftSize == 0 || sampleFreq <= 0 || minFreq < 0 || maxFreq < 0 ) {
            throw StrangerException("Arguments have not valid size values");
        }
        
        mSize = filterCount;
        mFftSize = fftSize;
        mFilterBank.resize(mSize+2, 0);
        
        if (endFreq <= 0) {
            endFreq = 0.5;
        }
        
        mFilterBank[0] = (SizeType)Round(2 * minFreq * ((float)(fftSize / 2 - 1)));
        mFilterBank[filterCount+1] = (SizeType)Round(2 * endFreq * (float)(fftSize / 2 - 1));
        
        startFreq = (minFreq) ? theta(2.0 * M_PI * minFreq, alpha) : 0.0; /* pulses in transform domain */
        endFreq = (endFreq < 0.5) ? theta(2.0 * M_PI * endFreq, alpha) : M_PI;

        d = (endFreq - startFreq) / (float)(filterCount + 1);
        z = (float)(fftSize / 2 - 1) / M_PI;
        f = startFreq;

        for(i = 1; i <= filterCount; i++) {
            f += d;
            mFilterBank[i] = (SizeType)Round(thetaInv(f, alpha) * z); /* index in the original domain */
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
        return(2595.0 * log10(1 + hz / 700.0));
//        return (1127.0 * log( 1.0 + hz / 700.0 ));
    }

    float TrifBank::melToHz(float mel) {
        return((float)(700.0 * (pow(10, mel / 2595.0) - 1)));
//        return (700.0 * (exp( mel / 1127.0) - 1.0 ));
    }
    
    float TrifBank::theta(float o, float a)
    {
      double v, a2;

      if (a == 0.0)
          return(o);

      if (o == M_PI)
          return(M_PI);

      a2 = a * a;
      v = atan(((1.0 - a2) * sin(o)) / ((1.0 + a2) * cos(o) - 2.0 * a));

      return((float)(v < (double)0.0 ? v + M_PI : v));
    }
    
    float TrifBank::thetaInv(float oop,float a)
    {
      float o, op, oinf, osup;
      double v, a2, b;

      if (a == 0.0)
          return(oop);

      if (oop <= 0.0)
          return(0.0);

      if(oop >= M_PI)
          return(M_PI);

      oinf = 0.0;
      osup = M_PI;
      a2 = a * a;
      b = 2.0 * a;
      do {
        o = oinf + (osup - oinf) / 2.0;
        v = atan(((1.0 - a2) * sin(o)) / ((1.0 + a2) * cos(o) - b));
        op = (v < 0) ? (float)v + M_PI : (float)v;
        if(op > oop)
            osup = o;
        else
            oinf = o;
      }
      while ((float)fabs(oop - op) > 0.00001);

      return(o);
    }
}