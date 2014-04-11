/* 
 * File:   dct.hpp
 * Author: Vladimir Zyablitskiy <https://github.com/rainlabs>
 *
 * Created on 10 апреля 2014 г., 23:19
 */

#ifndef DCT_HPP
#define	DCT_HPP

#include "global.hpp"
#include <math.h>
#include "transform.hpp"

namespace Stranger {
    
    /**
     * @brief class for DCT-II transform
     * c[i]=sqrt(2/N) * sum_{j=1}^{N}(m[j] * cos(M_PI*i*(j-0.5)/N)     i=1,...,p
     */
    class STRANGER_EXPORT Dct : public Transform {
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

