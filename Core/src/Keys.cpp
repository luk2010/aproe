////////////////////////////////////////////////////////////
/** @file Keys.h
 *  @ingroup Core
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 21/03/2013 - 03/02/2015
 *
 *  @brief
 *  Defines the Keys used in the Engine.
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
#include "Keys.h"

#include "WindowManager.h"
#include "Console.h"

namespace APro
{
	
	// For efficiency, on Windows we have the same Codes for Keys.

	const Key Key::A = Key(0x41);
	const Key Key::B = Key(0x42);
	const Key Key::C = Key(0x43);
	const Key Key::D = Key(0x44);
	const Key Key::E = Key(0x45);
	const Key Key::F = Key(0x46);
	const Key Key::G = Key(0x47);
	const Key Key::H = Key(0x48);
	const Key Key::I = Key(0x49);
	const Key Key::J = Key(0x4A);
	const Key Key::K = Key(0x4B);
	const Key Key::L = Key(0x4C);
	const Key Key::M = Key(0x4D);
	const Key Key::N = Key(0x4E);
	const Key Key::O = Key(0x4F);
	const Key Key::P = Key(0x50);
	const Key Key::Q = Key(0x51);
	const Key Key::R = Key(0x52);
	const Key Key::S = Key(0x53);
	const Key Key::T = Key(0x54);
	const Key Key::U = Key(0x55);
	const Key Key::V = Key(0x56);
	const Key Key::W = Key(0x57);
	const Key Key::X = Key(0x58);
	const Key Key::Y = Key(0x59);
	const Key Key::Z = Key(0x5A);
		
	const Key Key::k0 = Key(0x30);
	const Key Key::k1 = Key(0x31);
	const Key Key::k2 = Key(0x32);
	const Key Key::k3 = Key(0x33);
	const Key Key::k4 = Key(0x34);
	const Key Key::k5 = Key(0x35);
	const Key Key::k6 = Key(0x36);
	const Key Key::k7 = Key(0x37);
	const Key Key::k8 = Key(0x38);
	const Key Key::k9 = Key(0x39);
		
	const Key Key::Num0 = Key(0x60);
	const Key Key::Num1 = Key(0x61);
	const Key Key::Num2 = Key(0x62);
	const Key Key::Num3 = Key(0x63);
	const Key Key::Num4 = Key(0x64);
	const Key Key::Num5 = Key(0x65);
	const Key Key::Num6 = Key(0x66);
	const Key Key::Num7 = Key(0x67);
	const Key Key::Num8 = Key(0x68);
	const Key Key::Num9 = Key(0x69);
		
	const Key Key::F1 = Key(0x70);
	const Key Key::F2 = Key(0x71);
	const Key Key::F3 = Key(0x72);
	const Key Key::F4 = Key(0x73);
	const Key Key::F5 = Key(0x74);
	const Key Key::F6 = Key(0x75);
	const Key Key::F7 = Key(0x76);
	const Key Key::F8 = Key(0x77);
	const Key Key::F9 = Key(0x78);
	const Key Key::F10 = Key(0x79);
	const Key Key::F11 = Key(0x7A);
	const Key Key::F12 = Key(0x7B);
		
	const Key Key::Shift 	= Key(0x10);
	const Key Key::Control 	= Key(0x11);
	const Key Key::Menu 	= Key(0x12);
	
	const Key Key::Tabulate = Key(0x09);
	const Key Key::CapsLock = Key(0x14);
	const Key Key::Erase = Key(0x2E);
	const Key Key::Enter = Key(0x0D);
	const Key Key::Pause = Key(0x13);
	const Key Key::Escape = Key(0x1B);
	const Key Key::Space = Key(0x20);
		
	const Key Key::Up 	 = Key(0x26);
	const Key Key::Down  = Key(0x28);
	const Key Key::Left  = Key(0x25);
	const Key Key::Right = Key(0x27);
		
	const Key Key::Invalid = Key(0x00);
	
	Key Key::Translate(uint8_t vkey)
	{
#if APRO_PLATFORM == APRO_WINDOWS
		return Key(vkey);
#elif APRO_PLATFORM == APRO_LINUX
		
		// For Linux Platform, we must see which keyboard it is (depending on 
	    // the GUI manager). So We lead it to the WindowEventUtilities.
	    
	    if(!WindowManager::Get().getWindowEventUtilities()) {
			aprothrow_ce((String("Couldn't translate vkey : ") + String::toString(vkey) + ".").toCstChar());
	    }
	    
	    KeyTranslateDictionnary* ktd = WindowManager::Get().getWindowEventUtilities()->getKeyTranslateDictionnary();
	    if(!ktd) {
			aprothrow_ce((String("Couldn't translate vkey : ") + String::toString(vkey) + ". (No dictionnary)").toCstChar());
	    }
	    
	    return ktd->translate(vkey);

#else
		aprothrow_ce((String("Couldn't translate vkey : ") + String::toString(vkey) + ". (No implementation)").toCstChar());
		
#endif // APRO_PLATFORM
	}
	
	bool Key::IsSpecial(const Key& key)
	{
		return IsShift(key) ||
			   IsControl(key) ||
			   IsMenu(key);
	}
	
	bool Key::IsShift(const Key& key)
	{
		return key == Key::Shift;
	}
	
	bool Key::IsControl(const Key& key)
	{
		return key == Key::Control;
	}
	
	bool Key::IsMenu(const Key& key)
	{
		return key == Key::Menu;
	}
}
