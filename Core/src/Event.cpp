/////////////////////////////////////////////////////////////
/** @file Event.cpp
 *  @ingroup Events
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 11/09/2012 - 27/12/2014
 *
 *  @brief
 *  Implements the Event class.
 *
 *  @copyright
 *  Atlanti's Project Engine
 *  Copyright (C) 2012 - 2014  Atlanti's Corp
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
#include "Event.h"
#include "IdGenerator.h"

#include "EventEmitter.h"
#include "EventListener.h"

namespace APro
{

    APRO_REGISTER_EVENT_NOCONTENT(NullEvent)

    Event::Event()
    {
        m_type      = 0;
        m_id        = IdGenerator::Get().pick();
        m_target    = nullptr;
        m_emitter   = nullptr;
        must_stop   = false;
    }

    Event::~Event()
    {

    }

    const EventEmitter& Event::emitter() const
    {
        if(m_emitter)
            return *m_emitter;
        else
        {
            aprothrow_ce("Null emitter !");
        }
    }

    HashType Event::type() const
    {
        return m_type;
    }

    unsigned long Event::id() const
    {
        return m_id;
    }

    bool Event::hasEmitter() const
    {
        return m_emitter == nullptr;
    }

    bool Event::isValid() const
    {
        return m_type != 0;
    }

    bool Event::isNullEvent() const
    {
        return m_type == NullEvent::Hash;
    }

    void Event::mustStop()
    {
        must_stop = true;
    }
    
    Prototype* Event::clone() const
    {
    	Event* e = AProNew(Event);
    	e->m_emitter = m_emitter;
    	e->m_id      = m_id;
    	e->m_target  = m_target;
    	e->m_type    = m_type;
    	e->must_stop = must_stop;
    	return (Prototype*) e;
    }

}
