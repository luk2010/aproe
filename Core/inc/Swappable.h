////////////////////////////////////////////////////////////
/** @file Swappable.h
 *  @ingroup Maths
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 24/12/2013
 *
 *  Defines the Swappable class.
 *
**/
////////////////////////////////////////////////////////////
#ifndef APRO_SWAPPABLE_H
#define APRO_SWAPPABLE_H

#include "Platform.h"

namespace APro
{
    ////////////////////////////////////////////////////////////
    /** @class Swappable
     *  @ingroup Utils
     *  @brief A class that defines an object Swappable.
    **/
    ////////////////////////////////////////////////////////////
    template<typename Class>
    class Swappable
    {
    public:

        virtual ~Swappable() {}

        ////////////////////////////////////////////////////////////
        /** @brief Swap this object with another one from the same
         *  kind.
        **/
        ////////////////////////////////////////////////////////////
        virtual void swap(const Class& obj) = 0;
    };
}

#endif // APRO_SWAPPABLE_H
