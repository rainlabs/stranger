/* 
 * File:   lifter.hpp
 * Author: Vladimir Zyablitskiy <https://github.com/rainlabs>
 *
 * Created on 11 апреля 2014 г., 21:41
 */

#ifndef LIFTER_HPP
#define	LIFTER_HPP

#include "global.hpp"
#include "stranger_exception.hpp"
#include <math.h>
#include "transform.hpp"

namespace Stranger {
    
    /**
     * @brief class for liftering
     * h[i] = 1.0 + l * sin((i + 1) * M_PI / l) / 2.0
     */
    class STRANGER_EXPORT Lifter : public Transform {
    public:
        Lifter(int l, SizeType size);
        virtual ~Lifter();
        
        /**
         * @brief apply liftering to frame
         * @param frame
         * @return 
         */
        std::vector<SampleType> apply(std::vector<SampleType> frame);
    private:
        std::vector<SampleType> mBank;

    };
}

#endif	/* LIFTER_HPP */

