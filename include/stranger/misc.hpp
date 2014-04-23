/* 
 * File:   misc.hpp
 * Author: Vladimir Zyablitskiy <https://github.com/rainlabs>
 *
 * Created on 11 апреля 2014 г., 21:18
 */

#ifndef MISC_HPP
#define	MISC_HPP

#include "global.hpp"
#include <math.h>
#include <algorithm>
#include <iostream>

namespace Stranger {
    
    class STRANGER_EXPORT Misc
    {
    public:
        /**
        * @brief compute frame energy
        * @param frame
        * @return SampleType
        */
       static SampleType energy(std::vector<SampleType> frame, bool logFlag = false);
       
       /**
        * @brief normalize a frame samples
        * @param frame
        * @param flag
        * @return 
        */
       static std::vector<SampleType> normalize(std::vector<SampleType> frame);
       
       /**
        * @brief transform ms time into frame count
        * @param ms
        * @param sampleRate of signal
        * @return frame size
        */
       static SizeType msToFrameSize(SizeType ms, SizeType sampleRate);
       
       /**
        * @brief substract mean for each element
        * @param values
        * @return 
        */
       static std::vector<SampleType> meanNormalize(std::vector<SampleType> values);
       
       /**
        * @brief compute flatness of vector values
        * @param features
        * @return 
        */
       static SampleType flatness(std::vector<SampleType> features);
       
       /**
        * @brief Flatten stl 2 dimensional structure into 1
        * COCiter - Container of Containers Iterator
        * Oiter - Output Iterator
        * @param start iterator
        * @param end iterator
        * @param dest destination end iterator
        */
       template <class COCiter, class Oiter>
        static void flatten (COCiter start, COCiter end, Oiter dest) {
            while (start != end) {
                dest = std::copy(start->begin(), start->end(), dest);
                ++start;
            }
        }
    };
    
}

#endif	/* MISC_HPP */

