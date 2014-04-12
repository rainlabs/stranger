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
    };
    
}

#endif	/* MISC_HPP */

