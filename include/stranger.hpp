/* 
 * File:   stranger.hpp
 * Author: Vladimir Zyablitskiy <https://github.com/rainlabs>
 *
 * Created on 11 апреля 2014 г., 13:05
 */

#ifndef STRANGER_HPP
#define	STRANGER_HPP

#include "stranger/global.hpp"               // Common definitions
#include "stranger/stranger_exception.hpp"
#include "stranger/misc.hpp"                 // Any Non object functions
#include "stranger/signal.hpp"               // Sound Source
#include "stranger/window.hpp"               // TODO rework class to transform
#include "stranger/trif_bank.hpp"            // Triangular filter bank with mel or alpha scale
#include "stranger/fft.hpp"                  // DFT(!) transform using libFFTW3, TODO rename and rework
#include "stranger/dct.hpp"                  // DCT-II transform, TODO move to libFFTW3
#include "stranger/lifter.hpp"               // Liftering transform
#include "stranger/mfcc.hpp"                 // MFCC features extraction
#include "stranger/svm.hpp"                  // Support Vector Machine, using libSVM
//#include "stranger/cnn.hpp"                  // Convolutional Neural Network, TODO need implementation
#include "stranger/vad.hpp"                  // Voice Activity Detector

namespace Stranger {
    
    /**
     * @brief Humanize version string (split VERSION + STATUS)
     * @return MAJOR.MINOR.PATCH-STATUS
     */
    const char* version() {
        std::string ret("");
        for(int i = 2; i >= 0; i--) {
            if(i != 2) {
                ret += ".";
            }
            ret += std::to_string((VERSION >> (8*i)) & 0xff);
        }
        ret += "-";
        ret += STATUS;                                   // STATUS
        return ret.data();
    };
    
}
    
#endif	/* STRANGER_HPP */

