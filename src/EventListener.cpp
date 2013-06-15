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

    void EventListener::receive(const Event::ptr& e)
    {
        if(!e.isNull())
            receivedEvents.append(e);
    }

    Event::ptr EventListener::received(const String& name)
    {
        for(List<Event::ptr>::Iterator i(receivedEvents.begin()); !i.isEnd(); i++)
        {
            if(i.get()->type() == name)
            {
                Event::ptr ret = i.get();
                receivedEvents.erase(receivedEvents.find(ret));
                return ret;
            }
        }

        return Event::ptr();
    }

    const Event::ptr EventListener::received(const String& name) const
    {
        for(List<Event::ptr>::ConstIterator i(receivedEvents.begin()); !i.isEnd(); i++)
        {
            if(i.get()->type() == name)
            {
                const Event::ptr& ret = i.get();
                return ret;
            }
        }

        return Event::ptr();
    }

    void EventListener::purge()
    {
        receivedEvents.clear();
    }

    const String& EventListener::name() const
    {
        return mname;
    }

    String& EventListener::name()
    {
        return mname;
    }
}
