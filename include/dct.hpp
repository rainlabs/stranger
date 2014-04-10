/* 
 * File:   dct.hpp
 * Author: rain
 *
 * Created on 10 апреля 2014 г., 23:19
 */

#ifndef DCT_HPP
#define	DCT_HPP

#include "misc.hpp"

class Dct {
public:
    Dct(std::size_t size = 24, std::size_t outputSize = 13);
//    Dct(const Dct& orig);
    virtual ~Dct();
    
    /**
     * @brief execute DCT-II
     * @return vector
     */
    std::vector<double> execute(std::vector<double> frame);
private:
    std::size_t mSize;
    std::size_t mOutputSize;

};

#endif	/* DCT_HPP */

