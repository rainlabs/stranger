/* 
 * File:   fft.cpp
 * Author: rain
 * 
 * Created on 10 апреля 2014 г., 22:41
 */

#include "fft.hpp"

namespace Stranger {
    
    Fft::Fft(std::size_t size, std::size_t windowType) {
        mSize = size;
        mWindow = Window::get(size, windowType);
    }

    //Fft::fft(const Fft& orig) {
    //}

    Fft::~Fft() {
    //    mWindow.clear();
    }

    SpectrumType Fft::execute(std::vector<SampleType> frame) {
        std::vector< std::complex<double> > ret;
        fftw_complex *in, *out;
        fftw_plan plan;
        int i;

        if(frame.size() != mSize) {
            throw std::exception(); // TODO named errors
        }

        in =  FftwMalloc(fftw_complex, mSize);
        out = FftwMalloc(fftw_complex, mSize);
        plan = fftw_plan_dft_1d(mSize, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

        for(i = 0; i < mSize; i++) {
            in[i][0] = frame[i] * mWindow[i];
            in[i][1] = 0;
        }
        fftw_execute(plan);
        for(i = 0; i < mSize / 2 + 1; i++) {
            ret.push_back( ComplexType(out[i][0], out[i][1]) );
        }

        fftw_destroy_plan(plan);
        fftw_free(in);
        fftw_free(out);

        return ret;
    }

    std::vector<double> Fft::execute2r(std::vector<SampleType> frame) {
        std::vector<SampleType> ret;
        SpectrumType c = execute(frame);

        for(auto x : c) {
            ret.push_back( std::abs(x) );
        }

        return ret;
    }
}