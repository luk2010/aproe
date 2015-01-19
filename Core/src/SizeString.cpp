////////////////////////////////////////////////////////////
/** @file SizeString.cpp
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
#include "SizeString.h"

namespace APro
{
	SizeString::SizeString(const SizeString& sz)
	{
		StringList lst(sz.explode('x'));
		if(lst.size() >= 2) {
			m_first = lst.at(0).toInt();
			m_second = lst.at(1).toInt();
		}
		else {
			m_first = 0;
			m_second = 0;
		}
	}
	
	SizeString::~SizeString()
	{
		
	}
	
	uint32_t SizeString::getFirst() const
	{
		return m_first;
	}
	
	uint32_t SizeString::getSecond() const
	{
		return m_second;
	}
}
