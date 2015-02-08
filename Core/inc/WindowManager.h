////////////////////////////////////////////////////////////
/** @file WindowManager.h
 *  @ingroup Core
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 06/09/2012 - 02/02/2015
 *
 *  @brief
 *  Defines the WindowManager class.
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
#ifndef APROWINDOWMANAGER_H
#define APROWINDOWMANAGER_H

#include "Platform.h"
#include "BaseObject.h"
#include "ThreadSafe.h"
#include "Window.h"
#include "Keys.h"

namespace APro
{
	typedef void* WindowProcPtr;
	
	////////////////////////////////////////////////////////////
    /** @class WindowManager
     *  @ingroup Core
     *  @brief Implementation specific Window Utilities.
    **/
    ////////////////////////////////////////////////////////////
	class WindowEventUtilities
	{
	public:
		
		WindowEventUtilities() {}
		virtual ~WindowEventUtilities() {}
		
	public:
		
		virtual void messagePump(Map<String,Window*>& windows) = 0;
		virtual WindowProcPtr windowProcPtr() = 0;
		virtual const String name() = 0;
		
		////////////////////////////////////////////////////////////
        /** @brief Returns true if Keyboard is handled by this 
         *  WindowEventUtilities class.
        **/
        ////////////////////////////////////////////////////////////
		virtual bool isHardwareKeyboardAutoUpdated() const = 0;
		
		////////////////////////////////////////////////////////////
        /** @brief Returns true if Mouse is handled by this 
         *  WindowEventUtilities class.
        **/
        ////////////////////////////////////////////////////////////
		virtual bool isMouseSupported() const = 0;
		
		////////////////////////////////////////////////////////////
        /** @brief Returns a pointer to a valid KeyTranslateDictionnary.
        **/
        ////////////////////////////////////////////////////////////
		virtual KeyTranslateDictionnary* getKeyTranslateDictionnary() const = 0;
	};
	
    ////////////////////////////////////////////////////////////
    /** @class WindowManager
     *  @ingroup Core
     *  @brief Manages the Window specific Events.
    **/
    ////////////////////////////////////////////////////////////
    class APRO_DLL WindowManager :
    	public BaseObject<WindowManager>,
    	public ThreadSafe
    {

        APRO_DECLARE_MANUALSINGLETON(WindowManager)

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Constructs the Window Manager.
        **/
        ////////////////////////////////////////////////////////////
        WindowManager();

        ////////////////////////////////////////////////////////////
        /** @brief Destructs the Window Manager.
        **/
        ////////////////////////////////////////////////////////////
        ~WindowManager();
        
	public:
		
		////////////////////////////////////////////////////////////
        /** @brief Sets a new WindowEventUtilities.
        **/
        ////////////////////////////////////////////////////////////
		void setWindowEventUtilities(WindowEventUtilities* eventutilities);
		
		////////////////////////////////////////////////////////////
        /** @brief Returns the WindowEventUtilities.
        **/
        ////////////////////////////////////////////////////////////
		WindowEventUtilities* getWindowEventUtilities();
		
		////////////////////////////////////////////////////////////
        /** @brief Returns the WindowEventUtilities.
        **/
        ////////////////////////////////////////////////////////////
		const WindowEventUtilities* getWindowEventUtilities() const;
		
	public:
		
		////////////////////////////////////////////////////////////
        /** @brief Updates all the registered Windows. 
         *  You can call it once per frame if not using Main::update().
        **/
        ////////////////////////////////////////////////////////////
		void messagePump();
		
		////////////////////////////////////////////////////////////
        /** @brief Returns a pointer to a function pointer used by 
         *  the WindowEventUtilities. This pointer might be used to
         *  initialize the Window object.
        **/
        ////////////////////////////////////////////////////////////
		WindowProcPtr getWindowProcPointer();
		
	public:
		
		////////////////////////////////////////////////////////////
        /** @brief Register a window to the message pump.
        **/
        ////////////////////////////////////////////////////////////
		void registerWindow(const String& name, Window* window);
		
		////////////////////////////////////////////////////////////
        /** @brief Unregister a window from the message pump.
        **/
        ////////////////////////////////////////////////////////////
		void unregisterWindow(const String& name);
        
	private:
		
		WindowEventUtilities* m_eventutilities; ///< @brief The specific WindowEventUtilities used by the manager.
		Map<String, Window*>  m_windows; 		///< @brief Registered Windows.
    };
    
    #define WINDOWPROC_TO_DATA(func) *(void**)(&func)
    #define DATA_TO_WINDOWPROC(type,func) *(type*)(&func)
}

#endif
