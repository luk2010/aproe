/////////////////////////////////////////////////////////////
/** @file EventListener.cpp
 *  @ingroup Events
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 11/09/2012, 02/12/2013
 *
 *  Implements the EventListener class.
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
        id = IdGenerator::Get().canPick() ? IdGenerator::Get().pick() : 0;
        last_event = nullptr;
    }

    bool EventListener::receive(EventPtr& event)
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

    void EventListener::addEventProcessed(const HashType& event)
    {
        if(eventprocessed.find(event) == eventprocessed.end())
            eventprocessed.append(event);
    }

    void EventListener::removeEventProcessed(const HashType& event)
    {
        StringArray::const_iterator it = eventprocessed.find(event);
        if(it != eventprocessed.end())
            eventprocessed.erase(it);
    }

    bool EventListener::isEventProcessed(const HashType& event) const
    {
        return eventprocessed.find(event) != eventprocessed.end();
    }

}
