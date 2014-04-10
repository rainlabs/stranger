/* 
 * File:   dct.cpp
 * Author: rain
 * 
 * Created on 10 апреля 2014 г., 23:19
 */

#include "dct.hpp"

Dct::Dct(std::size_t size, std::size_t outputSize) {
    mSize = size;
    mOutputSize = outputSize;
}

//Dct::Dct(const Dct& orig) {
//}

Dct::~Dct() {
}

std::vector<double> Dct::execute(std::vector<double> frame) {
    fftw_plan plan;
    int i, N = frame.size();
    std::vector<double> ret;
    double *in, *out;
    
    in =  FftwMalloc(double, N);
    out = FftwMalloc(double, N);
    plan = fftw_plan_r2r_1d(N, in, out, FFTW_REDFT10, FFTW_ESTIMATE);
    
    for(i = 0; i < N; i++) {
        in[i] = frame[i];
    }
    
    fftw_execute(plan);
    
    // TODO normalize
    for(i = 0; i < mOutputSize; i++) {
        ret.push_back(out[i] / 2.0);
    }
    
    fftw_destroy_plan(plan);
    fftw_free(in);
    fftw_free(out);
    
    return ret;
}
