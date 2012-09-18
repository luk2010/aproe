/** @file EventListener.cpp
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 11/09/2012
 *
 *  @addtogroup Global
 *  @addtogroup System
 *
 *  This file defines the EventListener class.
 *
**/
#include "EventListener.h"

#include "Console.h"

namespace APro
{
    EventListener::EventListener()
        : ParametedObject(), mname("")
    {

    }

    EventListener::EventListener(const String& n)
        : ParametedObject(), mname(n)
    {

    }

    EventListener::~EventListener()
    {
        purge();
    }

    void EventListener::receive(const SharedPointer<Event>& e)
    {
        if(!e.isNull())
            receivedEvents.append(e);
    }

    SharedPointer<Event> EventListener::received(const String& name)
    {
        for(List<SharedPointer<Event> >::Iterator i(receivedEvents.begin()); !i.isEnd(); i++)
        {
            if(i.get()->type() == name)
            {
                SharedPointer<Event> ret = i.get();
                receivedEvents.erase(receivedEvents.find(ret));
                return ret;
            }
        }

        return SharedPointer<Event>();
    }

    void EventListener::purge()
    {
        receivedEvents.clear();
    }

    const String& EventListener::name() const
    {
        return mname;
    }
}
