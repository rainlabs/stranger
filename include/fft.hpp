/* 
 * File:   fft.hpp
 * Author: rain
 *
 * Created on 10 апреля 2014 г., 22:41
 */

#ifndef FFT_HPP
#define	FFT_HPP

#include <vector>
#include <complex>
#include <exception>
#include <fftw3.h>
#include "misc.hpp"
#include "window.hpp"

class Fft {
public:
    Fft(std::size_t size = 512, std::size_t windowType = 0);
//    Fft(const Fft& orig);
    virtual ~Fft();
    
    /**
     * @brief execute fft
     * @return complex vector with size (fftSize / 2 + 1)
     */
    std::vector< std::complex<double> > execute(std::vector<double> frame);
    
    /**
     * @brief execute fft with transform to real
     * @return real vector
     */
    std::vector<double> execute2r(std::vector<double> frame);
private:
    std::size_t mSize;
    std::vector<double> mWindow;

};

#endif	/* FFT_HPP */

