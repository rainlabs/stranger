/* 
 * File:   misc.hpp
 * Author: rain
 *
 * Created on 10 апреля 2014 г., 23:17
 */

#ifndef MISC_HPP
#define	MISC_HPP

#include <vector>
#include <fftw3.h>

#define FftwMalloc(type,n) (type *)fftw_malloc((n)*sizeof(type)) // from svm_train.c

typedef std::vector< std::vector<double> > vector2d;

#endif	/* MISC_HPP */

