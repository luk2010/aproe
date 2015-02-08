/////////////////////////////////////////////////////////////
/** @file HardwareKeyboardListener.h
 *  @ingroup Core
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 02/02/2015
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
#include "HardwareKeyboardListener.h"
#include "WindowManager.h"
#include "Keys.h"

#include <string.h>
#include <linux/input.h>
#include <sys/ioctl.h>

namespace APro 
{
	HardwareKeyboardListener::HardwareKeyboardListener()
	{
		m_isshiftpressed 	= false;
		m_iscontrolpressed 	= false;
		m_ismenupressed 	= false;

#if APRO_PLATFORM == APRO_LINUX
		
		if(isUpdateNecessary())
		{
			// We must find a valid keyboard
			DIR* d;
			struct dirent* dir;
			d = opendir("/dev/input/by-path/");
			
			if(!d) {
				aprothrow_ce("Can't find correct path for keyboard !");
			}
			
			while ((dir = readdir(d)) != NULL) {
				if(String(dir->d_name).findFirst(String("kbd")) > 0) {
					m_kbname = String("/dev/input/by-path/") + String(dir->d_name);
					aprodebug("Setting Keyboard path to : '") << m_kbname << "'.";
					break;
				}
			}
			
			closedir(d);
			aproassert1(!m_kbname.isEmpty());
		}
		
#endif // APRO_PLATFORM
	}
	
	HardwareKeyboardListener::~HardwareKeyboardListener()
	{
		
	}
	
	void HardwareKeyboardListener::update()
	{
		if(!isUpdateNecessary())
			return;
			
		static bool __curkeys[256] = { false };
		static int __keys[256] = { 0 };
		
#if APRO_PLATFORM == APRO_WINDOWS
		
		for(uint32_t i = 0; i < 256; ++i) {
			__keys[i] = GetAsyncKeyState(i);
			
			// Handle events
			
			if((__keys[i] & 1) && __curkeys[i] == true) {
				
			}
			else if((__keys[i] & 1) && __curkeys[i] == false) {
				// Key has been pushed
				__curkeys[i] = true;
				
				// Create event to simulate external control
				KeyDownEvent ev;
				ev.m_emitter = nullptr;
				ev.m_target  = this;
				ev.must_stop = false;
				
				ev.key		 		= Key::Translate(i);
				ev.isShiftPressed 	= m_isshiftpressed;
				ev.isControlPressed = m_iscontrolpressed;
				ev.ismenupressed	= m_ismenupressed;
				
				// Handle event
				receive(ev);
				
				// Special keys
				Key _key = Key::Translate(i);
				if(Key::IsSpecial(_key)) {
					if(Key::IsShift(_key)) {
						m_isshiftpressed = true;
					}
					if(Key::IsControl(_key)) {
						m_iscontrolpressed = true;
					}
					if(Key::IsMenu(_key)) {
						m_ismenupressed = true;
					}
				}
			}
			else if(!(__keys[i] & 1) && __curkeys[i] == false) {
				
			}
			else if(!(__keys[i] & 1) && __curkeys[i] == true) {
				// Key has been unpushed
				__curkeys[i] = false;
				
				// Create event to simulate external control
				KeyUpEvent ev;
				ev.m_emitter = nullptr;
				ev.m_target  = this;
				ev.must_stop = false;
				
				ev.key				= Key::Translate(i);
				ev.isShiftPressed 	= m_isshiftpressed;
				ev.isControlPressed = m_iscontrolpressed;
				ev.ismenupressed	= m_ismenupressed;
				
				// Handle event
				receive(ev);
				
				// Special keys
				Key _key = Key::Translate(i);
				if(Key::IsSpecial(_key)) {
					if(Key::IsShift(_key)) {
						m_isshiftpressed = false;
					}
					if(Key::IsControl(_key)) {
						m_iscontrolpressed = false;
					}
					if(Key::IsMenu(_key)) {
						m_ismenupressed = false;
					}
				}
			}
		}
		
#elif APRO_PLATFORM == APRO_LINUX

		// This is a bad implementation but i only have found that.
		// see : http://stackoverflow.com/questions/3649874/how-to-get-keyboard-state-in-linux
		
		// We find a valid keyboard file in constructor then :
		
		FILE *kbd = fopen(m_kbname.toCstChar(), "r");
		
		char key_map[KEY_MAX/8 + 1];
		memset(key_map, 0, sizeof(key_map));
		ioctl(fileno(kbd), EVIOCGKEY(sizeof(key_map)), key_map);
		
		fclose(kbd);
		
		for(uint32_t i = 0; i < KEY_MAX; ++i) {
				
			bool _keypress = !(key_map[i/8] & (1 << (i%8)));
			
			// Handle events
			
			if(_keypress && __curkeys[i] == true) {
				
			}
			else if(_keypress && __curkeys[i] == false) {
				// Key has been pushed
				__curkeys[i] = true;
				
				// Create event to simulate external control
				KeyDownEvent ev;
				ev.m_emitter = nullptr;
				ev.m_target  = this;
				ev.must_stop = false;
				
				ev.key		 		= Key::Translate(i);
				ev.isShiftPressed 	= m_isshiftpressed;
				ev.isControlPressed = m_iscontrolpressed;
				ev.isMenuPressed	= m_ismenupressed;
				
				// Handle event
				receive(ev);
				
				// Special keys
				Key _key = Key::Translate(i);
				if(Key::IsSpecial(_key)) {
					if(Key::IsShift(_key)) {
						m_isshiftpressed = true;
					}
					if(Key::IsControl(_key)) {
						m_iscontrolpressed = true;
					}
					if(Key::IsMenu(_key)) {
						m_ismenupressed = true;
					}
				}
			}
			else if(!_keypress && __curkeys[i] == false) {
				
			}
			else if(!_keypress && __curkeys[i] == true) {
				// Key has been unpushed
				__curkeys[i] = false;
				
				// Create event to simulate external control
				KeyUpEvent ev;
				ev.m_emitter = nullptr;
				ev.m_target  = this;
				ev.must_stop = false;
				
				ev.key				= Key::Translate(i);
				ev.isShiftPressed 	= m_isshiftpressed;
				ev.isControlPressed = m_iscontrolpressed;
				ev.isMenuPressed	= m_ismenupressed;
				
				// Handle event
				receive(ev);
				
				// Special keys
				Key _key = Key::Translate(i);
				if(Key::IsSpecial(_key)) {
					if(Key::IsShift(_key)) {
						m_isshiftpressed = false;
					}
					if(Key::IsControl(_key)) {
						m_iscontrolpressed = false;
					}
					if(Key::IsMenu(_key)) {
						m_ismenupressed = false;
					}
				}
			}
		}
					
#elif APRO_PLATFORM == APRO_OSX
		aprothrow_ce("No implentation for keyboard on OS X for now !");
#else
 		aprothrow_ce("No implentation for keyboard found !");
#endif // APRO_PLATFORM


	}
	
	const bool HardwareKeyboardListener::isUpdateNecessary() const
	{
		return !(WindowManager::Get().getWindowEventUtilities()->isHardwareKeyboardAutoUpdated());
	}
}
