////////////////////////////////////////////////////////////
/** @file Assert.cpp
 *  @ingroup Core
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 04/10/2013 - 28/02/2014
 *
 *  Implements the throwing exception Assert function.
 *
**/
////////////////////////////////////////////////////////////
#include "Platform.h"

namespace APro
{
    void __assert_with_except(bool _succeeded, const char* _msg, const char* _condition)
    {
        if(!_succeeded)
        {
            char buffer[512];
            sprintf(buffer, "Assertion failed ['%s'] (\"%s\").",
                    _condition, _msg);
            aprothrow_ce(buffer);
        }
    }
}
