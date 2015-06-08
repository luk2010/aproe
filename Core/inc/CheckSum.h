/////////////////////////////////////////////////////////////
/** @file CheckSum.h
 *  @ingroup Utils
 *
 *  @author Luk2010
 *  @date 08/03/2015 - 05/06/2015
 *
 *  @brief 
 *  Defines the CheckSum class.
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
 **/
////////////////////////////////////////////////////////////
#ifndef APRO_CHECKSUM_H
#define APRO_CHECKSUM_H

#include "Platform.h"
#include "Factory.h"
#include "QuickMap.h"

namespace APro
{
    typedef void* CheckSumType;///< @brief A General CheckSum type to return value. It should be interpreted by 
							   ///         the CheckSum class depending on the implementation.
    
    /////////////////////////////////////////////////////////////
    /** @class CheckSum
     *  @ingroup Utils
     *  @brief Describes a Generic CheckSum interface to generate
     *  checksums from data.
    **/
    /////////////////////////////////////////////////////////////
    class CheckSum
        : public Prototype
    {
    public:
        
        CheckSum() {}
        virtual ~CheckSum() {}
        
    public:
        
        /////////////////////////////////////////////////////////////
        /** @brief Clone this object.
         *  @note This function should be used only by a factory.
         *
         *  @return A new instance of this object.
        **/
        /////////////////////////////////////////////////////////////
        virtual Prototype* clone() const = 0;
        
        /////////////////////////////////////////////////////////////
        /** @brief Generate a checksum for the given String.
         *
         *  The return of this function depends on the implementation
         *  used to generate the CheckSum.
        **/
        /////////////////////////////////////////////////////////////
        CheckSumType generate(const String& str) { return generate(str.toCstChar(), str.size()); }
        
        /////////////////////////////////////////////////////////////
        /** @brief Generate a checksum for the given gbyte array.
         *
         *  The return of this function depends on the implementation
         *  used to generate the CheckSum.
         **/
        /////////////////////////////////////////////////////////////
        virtual CheckSumType generate(const void* data, uint32_t lenght) = 0;
        
        /////////////////////////////////////////////////////////////
        /** @brief Compares two CheckSum results.
         **/
        /////////////////////////////////////////////////////////////
        virtual CompareResult compare(const CheckSumType first, const CheckSumType second) const = 0;
        
    public:
        
        /////////////////////////////////////////////////////////////
        /** @brief Set if a property should be enabled or no.
        **/
        /////////////////////////////////////////////////////////////
        void setCustomProperty(const String& name, bool value) { mCustomProperties[name] = value; }
        
    protected:
        
        QuickMap<String, bool> mCustomProperties;///< @brief Properties holded by the CheckSum.
    };
    
    
/*
    class CheckSumFactory
    : public Factory<CheckSum>
    {
    public:
        
        CheckSumFactory() : Factory<CheckSum>()
        {
            register_prototype(String("CRC16"), AProNew(CheckSumCRC16));
            register_prototype(String("CRC32"), AProNew(CheckSumCRC32));
        }
        
    private:
        
        
    };
    */
}

#endif
