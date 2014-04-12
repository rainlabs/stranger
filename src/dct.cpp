/* 
 * File:   dct.cpp
 * Author: Vladimir Zyablitskiy <https://github.com/rainlabs>
 * 
 * Created on 10 апреля 2014 г., 23:19
 */

#include "stranger/dct.hpp"

namespace Stranger {
    
    Dct::Dct(SizeType size, SizeType outputSize) {
        int i, j;
        mSize = size;
        mOutputSize = outputSize;
        
        for(i = 0; i < mOutputSize; i++) {
            std::vector<SampleType> vec(mSize, 0.0);
            for(j = 0; j < mSize; j++) {
                vec[j] = (SampleType)cos(M_PI * (i + 1.0) * (j + 0.5) / mSize);
            }
            mBank.push_back( vec );
        }
        mZ = (float)sqrt(2.0 / mSize);
    }

    //Dct::Dct(const Dct& orig) {
    //}

    Dct::~Dct() {
    }
    
    std::vector<SampleType> Dct::apply(std::vector<SampleType> frame) {
        int i, j;
        double s;
        std::vector<SampleType> ret(mOutputSize, 0.0);
        for (i = 0; i < mOutputSize; i++) {
            s = 0.0;
            for (j = 0; j < mSize; j++)
              s += ( frame[j] * mBank[i][j] );
            ret[i] = (SampleType)(s * mZ);
        }
        return ret;
    }

    //TODO fftw DCT-II transform
//    std::vector<SampleType> Dct::execute(std::vector<SampleType> frame) {
//        fftw_plan plan;
//        int i, N = frame.size();
//        std::vector<SampleType> ret;
//        double *in, *out;
//
//        in =  Malloc(SampleType, N);
//        out = Malloc(SampleType, N);
//        plan = fftw_plan_r2r_1d(N, in, out, FFTW_REDFT10, FFTW_ESTIMATE);
//
//        for(i = 0; i < N; i++) {
//            in[i] = frame[i];
//        }
//
//        fftw_execute(plan);
//
//        // TODO normalize
//        for(i = 0; i < mOutputSize; i++) {
//            ret.push_back(out[i] / 2.0);
//        }
//
//        fftw_destroy_plan(plan);
//        fftw_free(in);
//        fftw_free(out);
//
//        return ret;
//    }
}