/////////////////////////////////////////////////////////////
/** @file EventListener.cpp
 *  @ingroup Events
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 11/09/2012
 *
 *  Implements the EventListener class.
 *
**/
/////////////////////////////////////////////////////////////
#include "EventListener.h"

#include "Main.h"

namespace APro
{
    EventListener::EventListener(const String& name)
    {
        m_name = name;
        id     = Main::get().getIdGenerator().canPick() ? Main::get().getIdGenerator().pick() : 0;
        last_event = nullptr;
    }
    
    EventListener::EventListener(const EventListener& other)
    {
        m_name = other.m_name;
        id = Main::get().getIdGenerator().canPick() ? Main::get().getIdGenerator().pick() : 0;
        last_event = nullptr;
    }
    
    bool EventListener::receive(const EventPtr& event)
    {
        if(event.isNull())
            return false;
        
        if(handle(event))
        {
            last_event = event;
            return true;
        }
        
        return false;
    }
    
    const String& EventListener::getName() const
    {
        return m_name;
    }
    
    const EventPtr& EventListener::getLastEventReceived() const
    {
        return last_event;
    }
    
    const unsigned long& EventListener::getId() const
    {
        return id;
    }
}
