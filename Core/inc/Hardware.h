/////////////////////////////////////////////////////////////
/** @file Hardware.h
 *  @ingroup Core
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 22/01/2015 - 02/02/2015
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
#ifndef APRO_HARDWARE_H
#define APRO_HARDWARE_H

#include "Platform.h"
#include "BaseObject.h"
#include "ThreadSafe.h"
#include "Singleton.h"
#include "HardwareListener.h"

namespace APro
{
	/////////////////////////////////////////////////////////////
	/** @class Hardware
	 *  @ingroup Core
	 *  @brief Regroups some Hardware Listeners, like mouse, keyboard, 
	 *  and eventually joysticks, ...
	**/
	/////////////////////////////////////////////////////////////
	class APRO_DLL Hardware :
		public BaseObject<Hardware>,
		public ThreadSafe
	{
		APRO_DECLARE_MANUALSINGLETON(Hardware)
		
	public:
			
		Hardware();
		~Hardware();
		
	public:
		
		////////////////////////////////////////////////////////////
        /** @brief Returns the HardwareListener given by name.
         *  
         *  @param hardwarelistener : The name of the HardwareListener
         *  to return. This listener is created either by the Hardware
         *  object, either by a plugin.
        **/
        ////////////////////////////////////////////////////////////
		EventListenerPtr getListener(const String& hardwarelistener);
		
		////////////////////////////////////////////////////////////
        /** @brief Add a Custom HardwareListener to the Hardware 
         *  object. 
         *
         *  @param hardwarelistener : Pointer to a created HardwareListener
         *  implemented by the user.
        **/
        ////////////////////////////////////////////////////////////
		void addCustomListener(EventListenerPtr& hardwarelistener);
		
		////////////////////////////////////////////////////////////
        /** @brief Returns Name for each HardwareListener.
        **/
        ////////////////////////////////////////////////////////////
		StringArray getAllListeners() const;
		
	private:
		
		HardwareListenerPtr    m_lkeyboard; ///< @brief Listener for the mouse.
		HardwareListenerPtr    m_lmouse;    ///< @brief Listener for the keyboard.
		HardwareListenersArray m_lcustoms;  ///< @brief Customs listeners for the user.
	};
}

#endif // APRO_HARDWARE_H
