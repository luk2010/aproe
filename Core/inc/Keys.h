////////////////////////////////////////////////////////////
/** @file Keys.h
 *  @ingroup Core
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 21/03/2013 - 07/02/2015
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
#ifndef APRO_KEYS_H
#define APRO_KEYS_H

#include "Platform.h"
#include "Event.h"

namespace APro
{
	////////////////////////////////////////////////////////////
	/** @class Key
	 *  @ingroup Core
	 *  @brief Groups every common Keys used by the Engine.
	**/
	////////////////////////////////////////////////////////////
    class Key 
    {
	public:
		
		static const Key A;
		static const Key B;
		static const Key C;
		static const Key D;
		static const Key E;
		static const Key F;
		static const Key G;
		static const Key H;
		static const Key I;
		static const Key J;
		static const Key K;
		static const Key L;
		static const Key M;
		static const Key N;
		static const Key O;
		static const Key P;
		static const Key Q;
		static const Key R;
		static const Key S;
		static const Key T;
		static const Key U;
		static const Key V;
		static const Key W;
		static const Key X;
		static const Key Y;
		static const Key Z;
		
		static const Key k0;
		static const Key k1;
		static const Key k2;
		static const Key k3;
		static const Key k4;
		static const Key k5;
		static const Key k6;
		static const Key k7;
		static const Key k8;
		static const Key k9;
		
		static const Key Num0;
		static const Key Num1;
		static const Key Num2;
		static const Key Num3;
		static const Key Num4;
		static const Key Num5;
		static const Key Num6;
		static const Key Num7;
		static const Key Num8;
		static const Key Num9;
		
		static const Key F1;
		static const Key F2;
		static const Key F3;
		static const Key F4;
		static const Key F5;
		static const Key F6;
		static const Key F7;
		static const Key F8;
		static const Key F9;
		static const Key F10;
		static const Key F11;
		static const Key F12;
		
		static const Key Shift;
		static const Key Control;
		static const Key Menu;
		
		static const Key Tabulate;
		static const Key CapsLock;
		static const Key Erase;
		static const Key Enter;
		static const Key Pause;
		static const Key Escape;
		static const Key Space;
		
		static const Key Up;
		static const Key Down;
		static const Key Left;
		static const Key Right;
		
		static const Key Invalid;
		
	public:
		
		static Key Translate(uint8_t vkey);
		
		static bool IsSpecial(const Key& key);
		static bool IsShift(const Key& key);
		static bool IsControl(const Key& key);
		static bool IsMenu(const Key& key);
		
	public:
		
		Key() : m_id(0) {}
		Key(uint8_t k) : m_id(k) {}
		
		Key& operator = (const Key& other) { m_id = other.m_id; return *this; }
		bool operator == (const Key& other) const { return m_id == other.m_id; }
		bool operator != (const Key& other) const { return m_id != other.m_id; }
				
	private:
		
		uint8_t m_id;
    };
    
    APRO_DECLARE_EVENT_CONTENT(KeyDownEvent)
		Key key;
		bool isShiftPressed;
		bool isControlPressed;
		bool isMenuPressed;
		
		Prototype* clone() {
			KeyDownEvent* ev = dynamic_cast<KeyDownEvent*> (Event::clone());
			ev->key 			 = key;
			ev->isControlPressed = isControlPressed;
			ev->isShiftPressed   = isShiftPressed;
			ev->isMenuPressed    = isMenuPressed;
			return ev;
		}
    APRO_DECLARE_EVENT_CONTENT_END()
    
    APRO_DECLARE_EVENT_CONTENT(KeyUpEvent)
		Key key;
		bool isShiftPressed;
		bool isControlPressed;
		bool isMenuPressed;
		
		Prototype* clone() {
			KeyUpEvent* ev = dynamic_cast<KeyUpEvent*> (Event::clone());
			ev->key 			 = key;
			ev->isControlPressed = isControlPressed;
			ev->isShiftPressed   = isShiftPressed;
			ev->isMenuPressed    = isMenuPressed;
			return ev;
		}
    APRO_DECLARE_EVENT_CONTENT_END()
    
    ////////////////////////////////////////////////////////////
	/** @class KeyTranslateDictionnary
	 *  @ingroup Core
	 *  @brief Translate from a platform-specific virtual key
	 *  to an Engine specific virtual key.
	**/
	////////////////////////////////////////////////////////////
    class KeyTranslateDictionnary
    {
	public:
		
		virtual ~KeyTranslateDictionnary() {}
		
		////////////////////////////////////////////////////////////
		/** @brief Translate platform-specific virtual key to
		 *  Engine specific virtual key.
		**/
		////////////////////////////////////////////////////////////
		virtual Key translate(uint8_t vkey) = 0;
    };
}

#endif // APRO_KEYS_H
