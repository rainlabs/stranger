/* 
 * File:   dct.hpp
 * Author: rain
 *
 * Created on 10 апреля 2014 г., 23:19
 */

#ifndef DCT_HPP
#define	DCT_HPP

#include "global.hpp"
#include <math.h>

namespace Stranger {
    
    /**
     * @brief class for DCT-II transform
     */
    class STRANGER_EXPORT Dct {
    public:
        Dct(SizeType = 24, SizeType outputSize = 12);
    //    Dct(const Dct& orig);
        virtual ~Dct();
        
        std::vector<SampleType> apply(std::vector<SampleType> frame);

        /**
         * @brief execute DCT-II
         * @return vector
         */
//        std::vector<SampleType> execute(std::vector<SampleType> frame);
    private:
        SizeType mSize;
        SizeType mOutputSize;
        float    mZ;
        vector2d mBank;

    };
}

#endif	/* DCT_HPP */

