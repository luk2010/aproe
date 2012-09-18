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

    void EventReceiver::addListener(const SharedPointer<EventListener>& listener)
    {
        if(listeners.find(listener) == -1)
        {
            listeners.append(listener);
        }
    }

    SharedPointer<EventListener> EventReceiver::getListener(const String& name)
    {
        for(List<SharedPointer<EventListener> >::Iterator i(listeners.begin()); !i.isEnd(); i++)
        {
            if(i.get()->name() == name)
                return i.get();
        }

        return SharedPointer<EventListener> ();
    }

    void EventReceiver::removeListener(const String& name)
    {
        SharedPointer<EventListener> l = getListener(name);
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
        for(List<SharedPointer<EventListener> >::Iterator i(listeners.begin()); !i.isEnd(); i++)
        {
            for(List<String>::Iterator j(eventProcessed.begin()); !j.isEnd(); j++)
            {
                SharedPointer<Event> r = i.get()->received(j.get());
                if(!r.isNull())
                {
                    processEvent(r);
                }
            }
        }
    }

    void EventReceiver::processEvent(const SharedPointer<Event>& e)
    {

    }
}
