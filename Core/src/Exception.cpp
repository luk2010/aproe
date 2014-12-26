/** @file Exception.cpp
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 21/05/2012 - 26/05/2012
 *
 *  @addtogroup Global
 *  @addtogroup Memory
 *
 *  This file implements the basics Exceptions used in the engine.
 *
**/
#include "Exception.h"

namespace APro
{
    CustomException::CustomException(const char* msg, long l, const char* fi, const char* fu)
        : Exception(l, fi, fu)
    {
        sprintf(buffer, "Custom exception thrown at line '%dl' of function '%s' in file '%s' : '%s'.",
                l, fu, fi, msg);
    }
}
