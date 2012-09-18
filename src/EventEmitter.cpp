/** @file EventEmitter.cpp
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 11/09/2012
 *
 *  @addtogroup Global
 *  @addtogroup System
 *
 *  This file defines the EventEmitter class.
 *
**/
#include "EventEmitter.h"
#include "Console.h"

namespace APro
{
    EventEmitter::EventEmitter()
    {

    }

    EventEmitter::EventEmitter(const EventEmitter& other)
        : listeners(other.listeners)
    {

    }

    EventEmitter::~EventEmitter()
    {

    }

    void EventEmitter::sendEvent(const SharedPointer<Event>& e)
    {
        for(List<SharedPointer<EventListener> >::Iterator i(listeners.begin()); !i.isEnd(); i++)
        {
            sendManualEvent(e, i.get());
        }
    }

    void EventEmitter::sendSpecificEvent(const SharedPointer<Event>& e, const String& name)
    {
        SharedPointer<EventListener> listener = getListener(name);
        sendManualEvent(e, listener);
    }

    void EventEmitter::sendManualEvent(const SharedPointer<Event>& e, SharedPointer<EventListener>& listener)
    {
        if(!listener.isNull())
            listener->receive(e);
    }

    SharedPointer<EventListener> EventEmitter::addListener(const String& name)
    {
        if(name.isEmpty()) return SharedPointer<EventListener>();

        SharedPointer<EventListener> ret = getListener(name);
        if(!ret.isNull())
        {
            Console::get() << "\n[EventEmitter] Listener " << name << " already exists ! Can't add one with same name.";
        }
        else
        {
            ret = createListener(name);
            listeners.append(ret);
        }

        return ret;
    }

    SharedPointer<EventListener> EventEmitter::getListener(const String& name)
    {
        for(List<SharedPointer<EventListener> >::Iterator i(listeners.begin()); !i.isEnd(); i++)
        {
            if(i.get()->name() == name)
                return i.get();
        }

        return SharedPointer<EventListener>();
    }

    SharedPointer<EventListener> EventEmitter::registerListener(const SharedPointer<EventListener> & listener)
    {
        if(listener.isNull())
            return listener;

        SharedPointer<EventListener> ret = getListener(listener->name());

        if(!ret.isNull())
        {
            Console::get() << "\n[EventEmitter] Listener " << listener->name() << " already exists ! Can't add one with same name.";
            return ret;
        }
        else
        {
            ret = listener;
            listeners.append(ret);
        }

        return ret;
    }

    void EventEmitter::removeListener(const String& name)
    {
        SharedPointer<EventListener> ret = getListener(name);
        if(!ret.isNull())
        {
            listeners.erase(listeners.find(ret));
        }
    }

    SharedPointer<EventListener> EventEmitter::createListener(const String& name) const
    {
        return SharedPointer<EventListener>(AProNew(1, EventListener) (name));
    }

    SharedPointer<Event> EventEmitter::createEvent(const String& name) const
    {
        return SharedPointer<Event>(AProNew(1, Event) (name));
    }
}
