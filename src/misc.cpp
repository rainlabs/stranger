#include "stranger/misc.hpp"

namespace Stranger {
    SampleType Misc::energy(std::vector<SampleType> frame, bool logFlag) {
        std::size_t i;
        SampleType ret, v;
        ret = 0.0;

        for (i = 0; i < frame.size(); i++) {
          v = frame[i];
          ret += v * v;
        }

//        std::cout << ret << std::endl;
        ret = sqrt(ret);
        
        if(logFlag) {
            if (ret < STRANGER_ENERGY_FLOOR) {
                ret = STRANGER_ENERGY_FLOOR;
            }
            ret = (SampleType) (2.0 * log(ret));
        }
        
        return ret;
    }
    
    std::vector<SampleType> Misc::normalize(std::vector<SampleType> frame) {
        std::vector<SampleType> ret(frame);
        SampleType e, v;
        std::size_t i;
        e = energy(frame);
        
        if (e != 0.0) {
          v = 1.0 / e;
          for (i = 0; i < ret.size(); i++)
            ret[i] *= v;
        }
        
        return ret;
    }
    
    SizeType Misc::msToFrameSize(SizeType ms, SizeType sampleRate) {
        return SizeType(ms / 1000.0 * sampleRate);
    }
}
