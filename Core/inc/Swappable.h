////////////////////////////////////////////////////////////
/** @file Swappable.h
 *  @ingroup Maths
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 24/12/2013 - 07/02/2015
 *
 *  @brief
 *  Defines the Swappable class.
 *
 *  @copyright
 *  Atlanti's Project Engine
 *  Copyright (C) 2012 - 2015  Atlanti's Corp
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
