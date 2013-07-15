/////////////////////////////////////////////////////////////
/** @file STDUtils.cpp
 *  @ingroup Utils
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 25/05/2013
 *
 *  Some Std lib utils.
 *
**/
/////////////////////////////////////////////////////////////
#include "STDUtils.h"

#include <cstring>

namespace APro
{
    namespace Std
    {
        void* Memcpy(void * dest, const void * src, size_t n)
        {
            return memcpy(dest, src, n);
        }

        int Memcmp(const void * s1, const void * s2,size_t n)
        {
            return memcmp(s1, s2, n);
        }
    }
}
