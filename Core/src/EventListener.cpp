/////////////////////////////////////////////////////////////
/** @file EventListener.cpp
 *  @ingroup Events
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 11/09/2012 - 27/12/2014
 *
 *  @brief
 *  Implements the EventListener class.
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
#include "EventListener.h"
#include "IdGenerator.h"

namespace APro
{
    EventListener::EventListener(const String& name)
    {
        m_name = name;
        id     = IdGenerator::Get().canPick() ? IdGenerator::Get().pick() : 0;
        last_event = nullptr;
    }

    EventListener::EventListener(const EventListener& other)
    {
        m_name = other.m_name;
        id     = IdGenerator::Get().canPick() ? IdGenerator::Get().pick() : 0;
        last_event = nullptr;
    }

    bool EventListener::receive(EventRef event)
    {
		if(!isEventProcessed(event.type()))
			return true; // Ignore it (Passthrough)
		
		// Handle event
		bool ret = handle(event);
		
		// Call callbacks
		for(uint32_t i = 0; i < callbacks[event].size(); ++i) {
			callbacks[event].at(i) (event);
		}
		
		// Return and copy event
		if(last_event)
			AProDelete(last_event);
		last_event = static_cast<Event*>(event.clone());
		
		return ret;
    }

    const String& EventListener::getName() const
    {
        return m_name;
    }

    const EventRef EventListener::getLastEventReceived() const
    {
        return *last_event;
    }

    const unsigned long EventListener::getId() const
    {
        return id;
    }

    void EventListener::addEventProcessed(const HashType& event)
    {
        if(eventprocessed.find(event) == eventprocessed.end())
            eventprocessed.append(event);
    }

    void EventListener::removeEventProcessed(const HashType& event)
    {
        HashArray::iterator it = eventprocessed.find(event);
        if(it != eventprocessed.end())
            eventprocessed.erase(it);
    }

    bool EventListener::isEventProcessed(const HashType& event) const
    {
        return eventprocessed.find(event) != eventprocessed.end();
    }
    
    void EventListener::addCallback(const HashType& event, Callback func)
    {
    	callbacks[event].append(func);
    }
    
    void EventListener::clearCallbacks(const HashType& event)
    {
    	callbacks[event].clear();
    }
    
    void EventListener::clearAllCallbacks()
    {
    	callbacks.clear();
    }

}
