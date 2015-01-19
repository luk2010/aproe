////////////////////////////////////////////////////////////
/** @file SizeString.h
 *  @ingroup Utility
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 19/01/2015
 *
 *  @brief 
 *  Defines the SizeString implementation.
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
#ifndef APRO_SIZESTRING_H
#define APRO_SIZESTRING_H

#include "Platform.h"
#include "BaseObject.h"

#include "SString.h"

namespace APro
{
	////////////////////////////////////////////////////////////
    /** @class SizeString
     *  @ingroup Utility
     *  @brief Converts a String with format %ix%i to 2 sizes.
    **/
    ////////////////////////////////////////////////////////////
	class SizeString
		: public BaseObject<SizeString>
	{
	public:
		
		////////////////////////////////////////////////////////////
        /** @brief Constructs the SizeString object.
        **/
        ////////////////////////////////////////////////////////////
		SizeString(const String& sz);
		
		////////////////////////////////////////////////////////////
        /** @brief Destructs the SizeString object.
        **/
        ////////////////////////////////////////////////////////////
		~SizeString() {}
		
	public:
		
		////////////////////////////////////////////////////////////
        /** @brief Returns the first Size component.
        **/
        ////////////////////////////////////////////////////////////
		uint32_t getFirst() const;
		
		////////////////////////////////////////////////////////////
        /** @brief Returns the second Size component.
        **/
        ////////////////////////////////////////////////////////////
		uint32_t getSecond() const;
		
	private:
		
		uint32_t m_first;  ///< @brief First Size component.
		uint32_t m_second; ///< @brief Second Size component.
	};
}

#endif // APRO_SIZESTRING_H
