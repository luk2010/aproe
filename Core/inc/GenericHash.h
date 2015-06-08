////////////////////////////////////////////////////////////
/** @file GenericHash.h
 *  @ingroup Utils
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 27/02/2015
 *
 *  @brief
 *  Defines the GenericHash class.
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
#ifndef APRO_GENERICHASH_H
#define APRO_GENERICHASH_H

#include "Platform.h"

namespace APro
{
    template <typename _HashType>
    using GenericHashFunction = int (*) (const _HashType&);
    
    ////////////////////////////////////////////////////////////
    /** @class GenericHash
     *  @ingroup Utils
     *  @brief Represents a GenericHash class. 
     *
     *  Contains the Hash function used for a specific object.
     *  This function can be implemented by the user for its own
     *  custom objects.
     *  Hash functions are stored as the GenericHashFunction alias
     *  describe them. 
     *
     *  @note
     *  You can (and should) use the APRO_DECLARE_GENERICHASH() macro
     *  to create GenericHash specialization. This ensure the correct
     *  function are implemented, and it is quicker to use a macro.
    **/
    ////////////////////////////////////////////////////////////
    template <typename _HashType>
    class GenericHash
    {
    public:
        
        static GenericHashFunction<_HashType> GetFunction() { return nullptr; }
    };
    
    
#define APRO_DECLARE_GENERICHASH(mytype, myfunction) \
    template <> class GenericHash<mytype> \
    { public: static GenericHashFunction<mytype> GetFunction() { return myfunction; } };
    
    ////////////////////////////////////////////////////////////
    /** @brief Implement the simplest hash for very simple object.
     *  
     *  @note
     *  You should never use this function. It is used only for types
     *  like int, unsigned int, etc., which does not need any hash
     *  as 1 is always 1, etc.
    **/
    ////////////////////////////////////////////////////////////
    template <typename HashType>
    int SimpleTypeHash (const HashType& simpleobj)
    {
        return (int) simpleobj;
    }
    
    APRO_DECLARE_GENERICHASH(int, SimpleTypeHash<int>);
    APRO_DECLARE_GENERICHASH(char, SimpleTypeHash<char>);
    APRO_DECLARE_GENERICHASH(uint32_t, SimpleTypeHash<uint32_t>);
    APRO_DECLARE_GENERICHASH(uint16_t, SimpleTypeHash<uint16_t>);
    APRO_DECLARE_GENERICHASH(uint8_t, SimpleTypeHash<uint8_t>);
};

#endif
