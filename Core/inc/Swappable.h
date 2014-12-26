////////////////////////////////////////////////////////////
/** @file Swappable.h
 *  @ingroup Maths
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 24/12/2013 - 29/11/2014
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
    class SwappableTrait {};
    
    ////////////////////////////////////////////////////////////
    /** @class Swappable
     *  @ingroup Utils
     *  @brief A class that defines an object Swappable.
     *  Under C++11, you should create a constructor for movable
     *  reference, enabling the move-and-swap idiom (which is a C++11
     *  feature derived from the copy-and-swap idiom).
    **/
    ////////////////////////////////////////////////////////////
    template<typename Class>
    class Swappable : public SwappableTrait
    {
    public:

        virtual ~Swappable() {}

        ////////////////////////////////////////////////////////////
        /** @brief Swap this object with another one from the same
         *  kind.
        **/
        ////////////////////////////////////////////////////////////
        virtual void swap(Class& obj) = 0;
        friend void swap (Class& lhs, Class& rhs) { lhs.swap(rhs); }
        
    };
}

#endif // APRO_SWAPPABLE_H
