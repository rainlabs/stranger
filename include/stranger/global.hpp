/* 
 * File:   global.hpp
 * Author: Vladimir Zyablitskiy <https://github.com/rainlabs>
 *
 * Created on 11 апреля 2014 г., 12:26
 */

#ifndef GLOBAL_HPP
#define	GLOBAL_HPP

#include <vector>
#include <string>
#include <complex>
#include <exception>

#define Malloc(type,n) (type *)malloc((n)*sizeof(type)) // from svm_train.c
#define STRANGER_ENERGY_FLOOR 1.0 // from spro.h

// dllimport || dllexport
#if defined (_WIN32) && defined(BUILD_SHARED_LIBS)
#    define STRANGER_EXPORT  __declspec(dllimport)
#else
#    define STRANGER_EXPORT
#endif

/**
 * Main library namespace.
 */
namespace Stranger
{
    /**
     * Library version in an easily comparable format.
     * 0x00(MAJOR)00(MINOR)00(PATCH)
     */
    const int VERSION = 0x000300;
    
    /**
     * Library status (dev, stable, beta, alpha)
     */
    const char* const STATUS = "dev";

    /**
     * Different size types (unsigned)
     */
    typedef unsigned short SizeType;
    
    /**
     * Sample value type.
     */
    typedef double SampleType;

    /**
     * Our standard complex number type, using double precision.
     */
    typedef std::complex<SampleType> ComplexType;

    /**
     * Spectrum type - a vector of complex values.
     */
    typedef std::vector<ComplexType> SpectrumType;
    
    /**
     * vector2d - a vector of 2 dimensional
     */
    typedef std::vector< std::vector<SampleType> > vector2d;
}


#endif	/* GLOBAL_HPP */

