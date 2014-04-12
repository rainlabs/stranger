/* 
 * File:   stranger_exception.cpp
 * Author: Vladimir Zyablitskiy <https://github.com/rainlabs>
 * 
 * Created on 12 апреля 2014 г., 12:31
 */

#include "stranger/stranger_exception.hpp"

namespace Stranger {
    StrangerException::StrangerException(const std::string& message): mMessage(message) {}
    
//    const char* StrangerException::what() const throw() {
//        return mMessage.c_str();
//    }
}
