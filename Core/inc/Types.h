////////////////////////////////////////////////////////////
/** @file Types.h
 *  @ingroup Utils
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 14/10/2013 - 22/01/2015
 *
 *  @brief
 *  Types namespace for Types helpers.
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
#ifndef APRO_TYPES_H
#define APRO_TYPES_H

#include "Base.h"
#include "Swappable.h"
#include "Copyable.h"

#include <type_traits>

namespace APro
{
	class APRO_DLL BaseObjectTrait {};
	
    namespace Types
    {
        ////////////////////////////////////////////////////////////
        /** @brief Tell if a Type has a destructor.
        **/
        ////////////////////////////////////////////////////////////
        template<typename T>
        APRO_DLL bool IsDestructible() { return std::is_destructible<T>::value; }
        
        ////////////////////////////////////////////////////////////
        /** @brief Tell if a Type must call its destructor or if it is
         *  not necessaryto explicitly call it in the AProNew / AProDelete
         *  system.
         *
         *  Destructors must be called in AProDelete function only if 
         *  object is not a fundamental type or a pointer to fundamental 
         *  type.
        **/
        ////////////////////////////////////////////////////////////
        template<typename T>
        APRO_DLL bool IsDestructorCallable() { return std::is_fundamental<T>::value; }
//        template<typename T>
//        APRO_DLL bool IsDestructorCallable<T*>() { return std::is_fundamental<T>::value; }

        ////////////////////////////////////////////////////////////
        /** @brief Tell if a Type has a constructor that correspond to
         *  given Args.
        **/
        ////////////////////////////////////////////////////////////
        template <typename T, typename... Args>
        APRO_DLL bool IsConstructible() { return std::is_constructible<T, Args...>::value; }

        ////////////////////////////////////////////////////////////
        /** @brief Tell if a Type is constructible by copy.
        **/
        ////////////////////////////////////////////////////////////
        template <typename T>
        APRO_DLL bool IsCopyConstructible() { return std::is_copy_constructible<T>::value; }

        ////////////////////////////////////////////////////////////
        /** @brief Tell if a Type is a class.
        **/
        ////////////////////////////////////////////////////////////
        template <typename T>
        APRO_DLL bool IsClass() { return std::is_class<T>::value; }
        
        ////////////////////////////////////////////////////////////
        /** @brief Tell if a Type is swappable (derive from SwappableTrait).
         **/
        ////////////////////////////////////////////////////////////
        template <typename T>
        APRO_DLL bool IsSwappable() { return std::is_base_of<SwappableTrait, T>::value; }
        
        ////////////////////////////////////////////////////////////
        /** @brief Returns true if a Type is BaseObject (derived from
         *  BaseObjectTrait).
        **/
        ////////////////////////////////////////////////////////////
        template <typename T>
        APRO_DLL bool IsBaseObject() { return std::is_base_of<BaseObjectTrait, T>::value; }
        
        ////////////////////////////////////////////////////////////
        /** @brief Returns true if a Type is copyable (derived from
         *  CopyableTrait).
         **/
        ////////////////////////////////////////////////////////////
        template <typename T>
        APRO_DLL bool IsCopyable() { return std::is_base_of<CopyableTrait, T>::value; }
    }
}

#endif // APRO_TYPES_H
