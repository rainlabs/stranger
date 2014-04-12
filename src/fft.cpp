/* 
 * File:   fft.cpp
 * Author: Vladimir Zyablitskiy <https://github.com/rainlabs>
 * 
 * Created on 10 апреля 2014 г., 22:41
 */

#include "stranger/fft.hpp"

namespace Stranger {
    
    Fft::Fft(SizeType size, SizeType windowType)
        : mSize(size) {
        mWindow = Window::get(size, windowType);
    }

    //Fft::fft(const Fft& orig) {
    //}

    Fft::~Fft() {
    //    mWindow.clear();
    }

    SpectrumType Fft::apply(std::vector<SampleType> frame) {
        return execute(frame);
    }
    
    SpectrumType Fft::execute(std::vector<SampleType> frame, SizeType size) {
        std::vector< std::complex<double> > ret;
        fftw_complex *in, *out;
        fftw_plan plan;
        int i;
        SizeType outSize = (size == 0) ? frame.size() : size;

        if(frame.size() != mSize) {
            throw StrangerException("frame size and fft size are not the same");
        }

        in =  FftwMalloc(fftw_complex, mSize);
        out = FftwMalloc(fftw_complex, mSize);
        plan = fftw_plan_dft_1d(mSize, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

        for(i = 0; i < mSize; i++) {
            in[i][0] = frame[i] * mWindow[i];
            in[i][1] = 0;
        }
        fftw_execute(plan);
        for(i = 0; i < outSize; i++) {
            ret.push_back( ComplexType(out[i][0], out[i][1]) );
        }

        fftw_destroy_plan(plan);
        fftw_free(in);
        fftw_free(out);

        return ret;
    }

    std::vector<double> Fft::execute2r(std::vector<SampleType> frame, SizeType size) {
        std::vector<SampleType> ret;
        SpectrumType c = execute(frame, size);

        for(auto x : c) {
            ret.push_back( std::abs(x) );
        }

        return ret;
    }
}