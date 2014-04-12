/* 
 * File:   fft.hpp
 * Author: Vladimir Zyablitskiy <https://github.com/rainlabs>
 *
 * Created on 10 апреля 2014 г., 22:41
 */

#ifndef FFT_HPP
#define	FFT_HPP

#include "global.hpp"
#include "stranger_exception.hpp"
#include "window.hpp"
#include <fftw3.h>

#define FftwMalloc(type,n) (type *)fftw_malloc((n)*sizeof(type)) // from svm_train.c

namespace Stranger {
    
    /**
     * @brief Class for fft execute (base on fftw3)
     */
    class STRANGER_EXPORT Fft {
    public:
        Fft(SizeType size = 512, SizeType windowType = 0);
        virtual ~Fft();
        
        SpectrumType apply(std::vector<SampleType> frame);

        /**
         * @brief execute fft
         * @param frame signal
         * @param size to return
         * @return complex vector
         */
        SpectrumType execute(std::vector<SampleType> frame, SizeType size = 0);

        /**
         * @brief execute fft with transform to real
         * @return real vector
         */
        std::vector<SampleType> execute2r(std::vector<SampleType> frame, SizeType size = 0);
    private:
        SizeType mSize;
        std::vector<SampleType> mWindow;

    };
}

#endif	/* FFT_HPP */

