/////////////////////////////////////////////////////////////
/** @file STDUtils.h
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
#ifndef APRO_STD_UTILS_H
#define APRO_STD_UTILS_H

#include "Platform.h"

namespace APro
{
    namespace Std
    {
        /////////////////////////////////////////////////////////////
        /** @brief Copy the first n bytes pointed to by src to the
         *  buffer pointed to by dest.
         *  @note Source and Destination shouldn't overlap.
         *
         *  @param dest : Destination to copy.
         *  @param src : Source of copy.
         *  @param n : Size of copy.
        **/
        /////////////////////////////////////////////////////////////
        void* Memcpy(void * dest, const void * src, size_t n);

        /////////////////////////////////////////////////////////////
        /** @brief The memcmp() function compares the first n characters
         *  of the object pointed to by s1 to the first n characters of
         *  the object pointed to by s2.
         *
         *  @return The memcmp() function returns an integer greater than,
         *  equal to, or less than zero, accordingly as the object pointed
         *  to by s1 is greater than, equal to, or less than the object
         *  pointed to by s2.
        **/
        /////////////////////////////////////////////////////////////
        int Memcmp(const void * s1, const void * s2,size_t n);
    }
}

#endif // APRO_STD_UTILS_H
