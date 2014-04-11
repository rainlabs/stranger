/* 
 * File:   mfcc.hpp
 * Author: rain
 *
 * Created on 10 апреля 2014 г., 21:31
 */

#ifndef MFCC_HPP
#define	MFCC_HPP

#include "global.hpp"
#include "signal.hpp"

namespace Stranger {
    
    /**
     * @brief class for MFCC extract
     */
    class STRANGER_EXPORT Mfcc {
    public:
        Mfcc();
    //    Mfcc(const Mfcc& orig);
        virtual ~Mfcc();
    private:

    };
}

#endif	/* MFCC_HPP */

