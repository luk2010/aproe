/////////////////////////////////////////////////////////////
/** @file Copyable.h
 *  @ingroup Utils
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 25/05/2013 - 22/01/2015
 *
 *  @brief
 *  Defines an interface for copyable objects.
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
/////////////////////////////////////////////////////////////
#ifndef APRO_COPYABLE_H
#define APRO_COPYABLE_H

#include "Platform.h"

namespace APro
{
	class CopyableTrait {};
	
    /////////////////////////////////////////////////////////////
    /** @class Copyable
     *  @ingroup utils
     *  @brief Describes a Copyable class.
     *  @details Inherits from this class if you want yours to
     *  be correctly copyable. You will have to implements the pure
     *  functions.
    **/
    /////////////////////////////////////////////////////////////
    template <typename ClassType>
    class Copyable : 
    	public CopyableTrait
    {
    public:

        /////////////////////////////////////////////////////////////
        /** @brief Destructor
        **/
        /////////////////////////////////////////////////////////////
        virtual ~Copyable()
        {

        }

        /////////////////////////////////////////////////////////////
        /** @brief Copy this object from another object of same kind.
         *  @param other : Object to copy.
        **/
        /////////////////////////////////////////////////////////////
        virtual void copyFrom(const ClassType& other) = 0;

        /////////////////////////////////////////////////////////////
        /** @brief Copy this object in a given one.
         *  @param other : Object to copy to.
        **/
        /////////////////////////////////////////////////////////////
        void copyTo(ClassType& other)
        {
            other.copyFrom(*this);
        }

        /////////////////////////////////////////////////////////////
        /** @brief Assignment operator.
        **/
        /////////////////////////////////////////////////////////////
        ClassType& operator = (const ClassType& other)
        {
            copyFrom(other);
            return *this;
        }

        /////////////////////////////////////////////////////////////
        /** @brief Egality operator.
        **/
        /////////////////////////////////////////////////////////////
        virtual bool operator == (const ClassType& other) const = 0;

        /////////////////////////////////////////////////////////////
        /** @brief Inegality operator.
        **/
        /////////////////////////////////////////////////////////////
        bool operator != (const ClassType& other) const
        {
            return !(*this == other);
        }
    };
}

#endif // APRO_COPYABLE_H
