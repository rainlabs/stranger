/* 
 * File:   global.hpp
 * Author: rain
 *
 * Created on 11 апреля 2014 г., 12:26
 */

#ifndef GLOBAL_HPP
#define	GLOBAL_HPP

#include <vector>
#include <string>
#include <complex>
#include <exception>
#include <fftw3.h>

#define FftwMalloc(type,n) (type *)fftw_malloc((n)*sizeof(type)) // from svm_train.c
#define Malloc(type,n) (type *)malloc((n)*sizeof(type)) // from svm_train.c

#ifndef STRANGER_EXPORT
#define STRANGER_EXPORT
#endif

/**
 * Main library namespace.
 */
namespace Stranger
{
    /**
     * Library version in an easily comparable format.
     */
    const long VERSION = 0x000001;
    
    /**
     * Library status (dev, stable, beta, alpha)
     */
    const char* const STATUS = "dev";

    /**
     * Sample value type.
     */
    typedef double SampleType;

    /**
     * Our standard complex number type, using double precision.
     */
    typedef std::complex<double> ComplexType;

    /**
     * Spectrum type - a vector of complex values.
     */
    typedef std::vector<ComplexType> SpectrumType;
    
    /**
     * vector2d - a vector of 2 dimensional
     */
    typedef std::vector< std::vector<double> > vector2d;
}


#endif	/* GLOBAL_HPP */

