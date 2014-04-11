/* 
 * File:   fft.hpp
 * Author: rain
 *
 * Created on 10 апреля 2014 г., 22:41
 */

#ifndef FFT_HPP
#define	FFT_HPP

#include "global.hpp"
#include "window.hpp"

namespace Stranger {
    
    /**
     * @brief Class for fft execute (base on fftw3)
     */
    class STRANGER_EXPORT Fft {
    public:
        Fft(std::size_t size = 512, std::size_t windowType = 0);
    //    Fft(const Fft& orig);
        virtual ~Fft();

        /**
         * @brief execute fft
         * @return complex vector with size (fftSize / 2 + 1)
         */
        SpectrumType execute(std::vector<SampleType> frame);

        /**
         * @brief execute fft with transform to real
         * @return real vector
         */
        std::vector<SampleType> execute2r(std::vector<SampleType> frame);
    private:
        std::size_t mSize;
        std::vector<SampleType> mWindow;

    };
}

#endif	/* FFT_HPP */

