/////////////////////////////////////////////////////////////
/** @file HardwareMouseListener.h
 *  @ingroup Core
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 02/02/2015
 *
 *  @brief
 *  Defines the HardwareMouseListener.
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
#ifndef APRO_HARDWAREMOUSELISTENER_H
#define APRO_HARDWAREMOUSELISTENER_H

#include "Platform.h"
#include "HardwareListener.h"

namespace APro 
{
	class HardwareMouseListener :
		public BaseObject <HardwareMouseListener>,
		public HardwareListener
	{
	public:
		
		HardwareMouseListener();
		~HardwareMouseListener();
		
	protected:
		
		////////////////////////////////////////////////////////////
        /** @brief Called by the HardwareListener thread to update 
         *  this object.
        **/
        ////////////////////////////////////////////////////////////
		void update();
		
		////////////////////////////////////////////////////////////
        /** @brief Must return true if you overload the update() 
         *  function.
        **/
        ////////////////////////////////////////////////////////////
		const bool isUpdateNecessary() const;
	};
}

#endif // APRO_HARDWAREMOUSELISTENER_H
