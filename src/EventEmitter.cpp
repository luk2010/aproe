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
#include "StringStream.h"

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

    void EventEmitter::sendEvent(const Event::ptr& e)
    {
    for(List<EventListener::ptr>::Iterator i(listeners.begin()); !i.isEnd(); i++)
        {
            sendManualEvent(e, i.get());
        }
    }

    void EventEmitter::sendSpecificEvent(const Event::ptr& e, const String& name)
    {
        EventListener::ptr listener = getListener(name);
        sendManualEvent(e, listener);
    }

    void EventEmitter::sendManualEvent(const Event::ptr& e, EventListener::ptr& listener)
    {
        if(!listener.isNull())
        {
            if(!isEventDocumented(e->type()))
            {
                Console::get() << "\n[EventEmitter] None documented event \"" << e->type() << "\" has been send ! Try not to send yourself custom event from a non-custom event emitter.";
            }

            listener->receive(e);
        }

    }

    EventListener::ptr EventEmitter::addListener(const String& name)
    {
        if(name.isEmpty()) return EventListener::ptr();

        EventListener::ptr ret = getListener(name);
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

    EventListener::ptr EventEmitter::getListener(const String& name)
    {
        for(List<EventListener::ptr>::Iterator i(listeners.begin()); !i.isEnd(); i++)
        {
            if(i.get()->name() == name)
                return i.get();
        }

        return EventListener::ptr();
    }

    EventListener::ptr EventEmitter::registerListener(const EventListener::ptr & listener)
    {
        if(listener.isNull())
            return listener;

        EventListener::ptr ret = getListener(listener->name());

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
        EventListener::ptr ret = getListener(name);
        if(!ret.isNull())
        {
            listeners.erase(listeners.find(ret));
        }
    }

    EventListener::ptr EventEmitter::createListener(const String& name) const
    {
        EventListener::ptr listener = EventListener::ptr(AProNew3(EventListener) (name));
        listener.setDeletionMethod(DeletionMethod::Delete3);
        return listener;
    }

    Event::ptr EventEmitter::createEvent(const String& name) const
    {
        Event::ptr event = Event::ptr(AProNew3(Event) (name));
        event.setDeletionMethod(DeletionMethod::Delete3);
        return event;
    }

    void EventEmitter::documentEvent(const String& event, const String& description)
    {
        events[event] = description;
    }

    String EventEmitter::explainEvents() const
    {
        String ret;

        ret << "\n[EventEmitter] Explaining events"
            << "\n--------------------------------";

        for(unsigned int i = 0; i < events.size(); ++i)
        {
            const EventsList::Pair& pair = events.getPair(i);
            ret << "\n+ " << pair.first() << " : " << pair.second() << ".";
        }

        ret << "\n--------------------------------";
        return ret;
    }

    const String EventEmitter::getEventDocumentation(const String& event) const
    {
        if(events.exists(event))
        {
            return events[event];
        }

        return String();
    }

    bool EventEmitter::isEventDocumented(const String& event) const
    {
        return events.exists(event);
    }
}
