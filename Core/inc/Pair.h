////////////////////////////////////////////////////////////
/** @file Pair.h
 *  @ingroup Utils
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 07/02/2015
 *
 *  @brief
 *  This file defines the Pair class.
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
#ifndef APROPAIR_H
#define APROPAIR_H

#include "Map.h"

namespace APro
{
	////////////////////////////////////////////////////////////
	/** @class Pair
	 *  @ingroup Utils
	 *  @brief Regroups two objects of different type.
	**/
	////////////////////////////////////////////////////////////
    template <typename T1, typename T2>
    class Pair :
    	public Swappable <Pair <T1, T2> >
    {
	private:
		
		T1 m_first;
		T2 m_second;
			
    public:

        typedef Pair<T1, T2> pair_t;

    public:

        Pair()
            : pair_t()
        {

        }

        Pair(const pair_t& other)
        {

        }

        Pair(const T1& t1, const T2& t2)
        {

        }

        ~Pair()
        {

        }
        
	public:
		
		T1& getFirst() { return m_first; }
		const T1& getFirst() const { return m_first; }
		
		T2& getSecond() { return m_second; }
		const T2& getSecond() const { return m_second; }
		
		void setFirst(const T1& first) { m_first = first; }
		void setSecond(const T2& second) { m_second = second; }
		
		////////////////////////////////////////////////////////////
        /** @brief Swap this object with another one from the same
         *  kind.
        **/
        ////////////////////////////////////////////////////////////
		void swap(pair_t& obj) {
			using std::swap;
			swap (m_first, obj.m_first);
			swap (m_second, obj.m_second);
		}

    };
}

#endif
