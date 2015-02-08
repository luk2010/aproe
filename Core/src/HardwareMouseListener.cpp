/////////////////////////////////////////////////////////////
/** @file HardwareMouseListener.cpp
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
#include "HardwareMouseListener.h"
#include "WindowManager.h"

namespace APro
{
	HardwareMouseListener::HardwareMouseListener()
	{
		
	}
	
	HardwareMouseListener::~HardwareMouseListener()
	{
		
	}
	
	void HardwareMouseListener::update()
	{
		static bool __warning = false;
		if(!__warning) {
			__warning = true;
			aprodebug("Going on without Mouse Listener !");
		}
	}
	
	const bool HardwareMouseListener::isUpdateNecessary() const
	{
		return !WindowManager::Get().getWindowEventUtilities()->isMouseSupported();
	}
}
