/* 
 * File:   transform.hpp
 * Author: Vladimir Zyablitskiy <https://github.com/rainlabs>
 *
 * Created on 11 апреля 2014 г., 22:21
 */

#ifndef TRANSFORM_HPP
#define	TRANSFORM_HPP

#include "global.hpp"

namespace Stranger {
    
    /**
     * @brief abstract transform class
     */
    class STRANGER_EXPORT Transform {
    public:
        /**
         * @brief apply transform at frame
         * @param frame
         * @return 
         */
        virtual std::vector<SampleType> apply(std::vector<SampleType> frame) = 0;
    };
}

#endif	/* TRANSFORM_HPP */

