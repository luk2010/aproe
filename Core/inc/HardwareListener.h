/////////////////////////////////////////////////////////////
/** @file HardwareListener.h
 *  @ingroup Core
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 26/01/2015 - 02/02/2015
 *
 *  @brief
 *  Defines the HardwareListener.
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
#ifndef APRO_HARDWARELISTENER_H
#define APRO_HARDWARELISTENER_H

#include "Platform.h"

#include "EventListener.h"
#include "Thread.h"
#include "AutoPointer.h"
#include "Array.h"

namespace APro
{
	class APRO_DLL Hardware;
	
	/////////////////////////////////////////////////////////////
	/** @class HardwareListener
	 *  @ingroup Core
	 *  @brief Base class for Hardware Listeners.
	 *
	 *  Derive from this class if you want to create a new Hardware
	 *  specific Listener. The Listener can then be added to the Engine
	 *  with Hardware::Get().addCustomListener() .
	**/
	/////////////////////////////////////////////////////////////
	class APRO_DLL HardwareListener : 
		public EventListener,
		public Thread
	{
		
	public:
		
		friend class Hardware;
		
	protected:
	
		////////////////////////////////////////////////////////////
        /** @brief Called by the HardwareListener thread to update 
         *  this object.
        **/
        ////////////////////////////////////////////////////////////
		virtual void update() { };
		
		////////////////////////////////////////////////////////////
        /** @brief Must return true if you overload the update() 
         *  function.
        **/
        ////////////////////////////////////////////////////////////
		virtual const bool isUpdateNecessary() const = 0;
		
	protected:
		
		////////////////////////////////////////////////////////////
        /** @brief Launch the update() function.
        **/
        ////////////////////////////////////////////////////////////
		void exec() { update(); }
	};
	
	typedef AutoPointer<HardwareListener> HardwareListenerPtr;
	typedef Array<HardwareListenerPtr> HardwareListenersArray;
}

#endif // APRO_HARDWARELISTENER_H
