/* 
 * File:   stranger.hpp
 * Author: rain
 *
 * Created on 11 апреля 2014 г., 13:05
 */

#ifndef STRANGER_HPP
#define	STRANGER_HPP

#include "global.hpp"
#include "signal.hpp"
#include "window.hpp"
#include "trif_bank.hpp"
#include "fft.hpp"
#include "dct.hpp"
#include "mfcc.hpp"

namespace Stranger {
    
    /**
     * @brief Humanize version string (split VERSION by 2 bytes + STATUS)
     * @return 
     */
    const char* version() {
        std::string ret;
        ret = std::to_string(VERSION & 0xff0000) + "."; // MAJOR
        ret+= std::to_string(VERSION & 0x00ff00) + "."; // MINOR
        ret+= std::to_string(VERSION & 0x0000ff) + "-"; // PATCH
        ret+= STATUS;                                   // STATUS
        return ret.data();
    };
    
}

#endif	/* STRANGER_HPP */

