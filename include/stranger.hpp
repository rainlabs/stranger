/* 
 * File:   stranger.hpp
 * Author: Vladimir Zyablitskiy <https://github.com/rainlabs>
 *
 * Created on 11 апреля 2014 г., 13:05
 */

#ifndef STRANGER_HPP
#define	STRANGER_HPP

#include "global.hpp"
#include "misc.hpp"
#include "signal.hpp"
#include "window.hpp"
#include "trif_bank.hpp"
#include "fft.hpp"
#include "dct.hpp"
#include "lifter.hpp"
#include "mfcc.hpp"

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

