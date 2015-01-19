////////////////////////////////////////////////////////////
/** @file WindowManager.cpp
 *  @ingroup Core
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 06/09/2012 - 19/01/2015
 *
 *  @brief
 *  Implements the WindowManager class.
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
#include "WindowManager.h"

namespace APro
{
    APRO_IMPLEMENT_MANUALSINGLETON(WindowManager)

    WindowManager::WindowManager()
    {
    	m_eventutilities = nullptr;
    }
    
    WindowManager::~WindowManager()
    {
    	// NOTE : The WindowEventUtilities object should have been
    	// allocated using AProNew.
    	if(m_eventutilities) {
			AProDelete(m_eventutilities);
			m_eventutilities = nullptr;
    	}
    }
    
    void WindowManager::setWindowEventUtilities(WindowEventUtilities* eventutilities)
    {
    	APRO_THREADSAFE_AUTOLOCK
    	
    	if(m_eventutilities) {
			AProDelete(m_eventutilities);
			m_eventutilities = nullptr;
    	}
    	
    	if(eventutilities) {
			m_eventutilities = eventutilities;
			aprodebug("Using WindowEventUtilities '") << m_eventutilities->name() << "'.";
    	}
    	else {
			aprodebug("Using Null WindowEventUtilities.");
    	}
    }
    
    WindowEventUtilities* WindowManager::getWindowEventUtilities()
    {
    	return m_eventutilities;
    }
    
    const WindowEventUtilities* WindowManager::getWindowEventUtilities() const
    {
    	return m_eventutilities;
    }
    
    void WindowManager::messagePump()
    {
    	APRO_THREADSAFE_AUTOLOCK
    	if(m_eventutilities) {
			m_eventutilities->messagePump(m_windows);
    	}
    }
    
    WindowProcPtr WindowManager::getWindowProcPointer()
    {
    	if(m_eventutilities) {
			return m_eventutilities->windowProcPtr();
    	}
    	else {
			return nullptr;
    	}
    }
    
    void WindowManager::registerWindow(const String& name, Window* window)
    {
    	APRO_THREADSAFE_AUTOLOCK
    	
    	if(window && !name.isEmpty()) {
			if(!m_windows.keyExists(name)) {
				m_windows[name] = window;
				aprodebug("Registered Window '") << name << "'.";
			}
			else {
				aprodebug("Window '") << name << "' already registered !";
			}
    	}
    }
    
    void WindowManager::unregisterWindow(const String& name)
    {
    	APRO_THREADSAFE_AUTOLOCK
    	
    	if(!name.isEmpty()) {
			if(m_windows.keyExists(name)) {
				m_windows.erase(name);
				aprodebug("Unregistered Window '") << name << ".";
			}
    	}
    }
}
