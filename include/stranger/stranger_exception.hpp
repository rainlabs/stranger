/* 
 * File:   stranger_exception.hpp
 * Author: Vladimir Zyablitskiy <https://github.com/rainlabs>
 *
 * Created on 12 апреля 2014 г., 12:31
 */

#ifndef STRANGER_EXCEPTION_HPP
#define	STRANGER_EXCEPTION_HPP

#include "global.hpp"

namespace Stranger {
    
    /**
     * @brief Basic Exception class with message
     * @param message
     */
    class STRANGER_EXPORT StrangerException: public std::exception {
    public:
        StrangerException(const std::string& message);
        virtual const char* what() const throw() {
            return mMessage.c_str();
        }
    private:
        std::string mMessage;
    };
}

#endif	/* STRANGER_EXCEPTION_HPP */

