/////////////////////////////////////////////////////////////
/** @file HardwareKeyboardListener.h
 *  @ingroup Core
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 26/01/2015 - 02/02/2015
 *
 *  @brief
 *  Defines the HardwareKeyboardListener.
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
#ifndef APRO_HARDWAREKEYBOARDLISTENER_H
#define APRO_HARDWAREKEYBOARDLISTENER_H

#include "Platform.h"
#include "HardwareListener.h"

namespace APro
{
	/////////////////////////////////////////////////////////////
	/** @class HardwareKeyboardListener
	 *  @ingroup Core
	 *  @brief Class used to listen for events from the Keyboard.
	 *  
	 *  This listening can be done either by updating the Keyboard
	 *  (may be very slow but on certain platform, it is needed), or
	 *  it can be done by the WindowEventUtilities class which is 
	 *  platform-specific.
	**/
	/////////////////////////////////////////////////////////////
	class HardwareKeyboardListener :
		public BaseObject<HardwareKeyboardListener>,
		public HardwareListener
	{
	public:
			
		HardwareKeyboardListener();
		~HardwareKeyboardListener();
		
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
		
	private:
		
		bool m_isshiftpressed;  ///< @brief True if SHIFT key is pressed.
		bool m_iscontrolpressed;///< @brief True if CONTROL key is pressed.
		bool m_ismenupressed;	///< @brief True if MENU key is pressed.
		
#if APRO_PLATFORM == APRO_LINUX
		String m_kbname; ///< @brief The right path to the Keyboard file.
#endif // APRO_PLATFORM
	};
}

#endif // APRO_HARDWAREKEYBOARDLISTENER_H
