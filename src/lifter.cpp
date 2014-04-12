/* 
 * File:   lifter.cpp
 * Author: Vladimir Zyablitskiy <https://github.com/rainlabs>
 * 
 * Created on 11 апреля 2014 г., 21:41
 */

#include "stranger/lifter.hpp"

namespace Stranger {
    Lifter::Lifter(int l, SizeType size) {
        int i;
        mBank.resize(size, 0.0);
        for (i = 0; i < size; i++) {
            mBank[i] = (SampleType)(1.0 + 0.5 * (double)l * sin((double)(i + 1) * M_PI / (double)l));
        }
    }

    Lifter::~Lifter() {}
    
    std::vector<SampleType> Lifter::apply(std::vector<SampleType> frame) {
        if(frame.size() != mBank.size()) {
            throw StrangerException("frame size and lifter size are not the same");
        }
        std::size_t i;
        
        std::vector<SampleType> ret(frame);
        for(i = 0; i < ret.size(); i++) {
            ret[i] *= mBank[i];
        }
        return ret;
    }

}