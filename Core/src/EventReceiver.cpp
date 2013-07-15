/** @file EventReceiver.cpp
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 11/09/2012
 *
 *  @addtogroup Global
 *  @addtogroup System
 *
 *  This file defines the EventReceiver class.
 *
**/
#include "EventReceiver.h"

namespace APro
{
    EventReceiver::EventReceiver()
    {

    }

    EventReceiver::~EventReceiver()
    {
        clearListeners();
    }

    void EventReceiver::addEventProcessed(const String& e)
    {
        if(eventProcessed.find(e) == -1)
        {
            eventProcessed.append(e);
        }
    }

    void EventReceiver::removeEventProcessed(const String& e)
    {
        int index = eventProcessed.find(e);
        if(index >= 0)
        {
            eventProcessed.erase((size_t) index);
        }
    }

    void EventReceiver::clearEvents()
    {
        eventProcessed.clear();
    }

    void EventReceiver::addListener(const EventListener::ptr& listener)
    {
        if(listeners.find(listener) == -1)
        {
            listeners.append(listener);
        }
    }

    EventListener::ptr EventReceiver::getListener(const String& name)
    {
        for(List<EventListener::ptr>::Iterator i(listeners.begin()); !i.isEnd(); i++)
        {
            if(i.get()->name() == name)
                return i.get();
        }

        return EventListener::ptr();
    }

    const EventListener::ptr EventReceiver::getListener(const String& name) const
    {
        for(List<EventListener::ptr>::ConstIterator i(listeners.begin()); !i.isEnd(); i++)
        {
            if(i.get()->name() == name)
                return i.get();
        }

        return EventListener::ptr();
    }

    void EventReceiver::removeListener(const String& name)
    {
        EventListener::ptr l = getListener(name);
        if(!l.isNull())
        {
            listeners.erase(listeners.find(l));
        }
    }

    void EventReceiver::clearListeners()
    {
        listeners.clear();
    }

    void EventReceiver::processEvents()
    {
        for(List<EventListener::ptr>::Iterator i(listeners.begin()); !i.isEnd(); i++)
        {
            for(List<String>::Iterator j(eventProcessed.begin()); !j.isEnd(); j++)
            {
                Event::ptr r = i.get()->received(j.get());
                if(!r.isNull())
                {
                    processEvent(r);
                }
            }

            i.get()->purge();
        }
    }

    void EventReceiver::processEvent(const Event::ptr&)
    {

    }
}
