/////////////////////////////////////////////////////////////
/** @file Hardware.cpp
 *  @ingroup Core
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 26/01/2015
 *
 *  @brief
 *  Defines the Hardware class, listeners and events.
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
#include "Hardware.h"

#include "HardwareKeyboardListener.h"
#include "HardwareMouseListener.h"

namespace APro
{
	Hardware::Hardware()
	{
		// We must create a Keyboard and a Mouse listener.
		m_lkeyboard = HardwareKeyboardListener::New();
		m_lmouse    = HardwareMouseListener::New();
		
		aproassert1(!m_lkeyboard.isNull() && !m_lmouse.isNull());
		
		// Own the pointer so every one can use it simply.
		m_lkeyboard.setOwning(true);
		m_lmouse.setOwning(true);
		
		// Then we start them if necessary.
		if(m_lkeyboard->isUpdateNecessary())
			m_lkeyboard->start();
		if(m_lmouse->isUpdateNecessary())
			m_lmouse->start();
	}
	
	Hardware::~Hardware()
	{
		// Listeners are destroyed by the AutoPointer correctly using Pools.
	}
	
	EventListenerPtr Hardware::getListener(const String& hardwarelistener)
	{
		if(!hardwarelistener.isEmpty())
		{
			if(hardwarelistener == "Keyboard") {
				return m_lkeyboard;
			}
			else if (hardwarelistener == "Mouse") {
				return m_lmouse;
			}
			else {
				APRO_THREADSAFE_AUTOLOCK

				for(uint32_t i = 0; i < m_lcustoms.size(); ++i) {
					if(m_lcustoms.at(i)->EventListener::getName() == hardwarelistener) {
						return m_lcustoms.at(i);
					}
				}
				
			}
		}
		
		return EventListenerPtr::Null;
	}
	
	void Hardware::addCustomListener(EventListenerPtr& hardwarelistener)
	{
		APRO_THREADSAFE_AUTOLOCK
		m_lcustoms.append(hardwarelistener);
	}
	
	StringArray Hardware::getAllListeners() const
	{
		StringArray ret;
		ret << String("Keyboard");
		ret << String("Mouse");
		
		{APRO_THREADSAFE_AUTOLOCK
			for(uint32_t i = 0; i < m_lcustoms.size(); ++i) {
				ret << m_lcustoms.at(i)->EventListener::getName();
			}
		}
		
		return ret;
	}
}


