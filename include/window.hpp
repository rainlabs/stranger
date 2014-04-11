#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "global.hpp"
#include <math.h>

namespace Stranger {
    
    /**
     * @brief Weighting windows
     */
    class STRANGER_EXPORT Window
    {
    public:
        enum {
            NONE,
            HAMMING,
            BLACKMAN_HARRIS,
            HANN
        };
        /**
         * @brief Get window samples by type
         * @param size of window
         * @param type of function
         * @return sample vector
         */
        static std::vector<SampleType> get(std::size_t size, std::size_t type = 0);
        static std::vector<SampleType> blackmanHarris(std::size_t size);
        static std::vector<SampleType> hamming(std::size_t size);
        static std::vector<SampleType> hann(std::size_t size);
        
        /**
         * @brief default window with rectangular full size vector (1 for each sample)
         * @param size
         * @return 
         */
        static std::vector<SampleType> none(std::size_t size);
    };
}

#endif // WINDOW_HPP
