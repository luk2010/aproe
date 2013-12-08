/////////////////////////////////////////////////////////////
/** @file EventEmitter.cpp
 *  @ingroup Events
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 11/09/2012
 *
 *  Implements the EventEmitter class.
 *
**/
/////////////////////////////////////////////////////////////
#include "EventEmitter.h"
#include "Console.h"
#include "StringStream.h"

namespace APro
{
    EventEmitter::EventEmitter()
    {
        epolicy = EP_MANUAL;
    }

    EventEmitter::EventEmitter(const EventEmitter& emitter)
    {
        listeners = emitter.listeners;
        events    = emitter.events;
        epolicy = EP_MANUAL;
    }

    EventEmitter::~EventEmitter()
    {

    }

    bool EventEmitter::sendEvent(EventPtr& e)
    {
        if(e.isNull() || ! e->isValid())
        {
            aprodebug("Incorrect event given.");
            return false;
        }

        if(e->must_stop)
        {
            aprodebug("Event hhas stop flag setted.");
            return false;
        }

        if(epolicy == EP_MANUAL)
        {
            bool tmp = false;
            ListenersList::const_iterator e = listeners.end();
            for(ListenersList::iterator it = listeners.begin(); it != e && !(e->must_stop); it++)
            {
                if((*it)->receive(e))
                    tmp = true;
            }

            return tmp;
        }
        else if(epolicy == EP_UNITER)
            return sendAsynchronousEvent(e);
        else
            return true;// Stub
    }

    bool EventEmitter::sendEvent(EventPtr& e, EventListenerPtr& listener)
    {
        if(e.isNull() || ! e->isValid())
        {
            aprodebug("Incorrect event given.");
            return false;
        }

        if(e->must_stop)
        {
            aprodebug("Event has stop flag setted.");
            return false;
        }

        if(!listener.isNull())
        {
            return listener->receive(e);
        }
        else
        {
            aprodebug("Incorrect listener given to EventEmitter. Sending event to every listeners registered.");
            return sendEvent(e);
        }
    }

    bool EventEmitter::sendEvent(EventPtr& e, const String& listener)
    {
        EventListenerPtr& ptr = getListener(listener);

        if(ptr.isNull())
        {
            aprodebug("Listener \"") << listener << "\" given not found.";
            return false;
        }

        return sendEvent(e, listener);
    }

    bool EventEmitter::sendEvent(EventPtr& e, const Id& listener)
    {
        EventListenerPtr& ptr = getListener(listener);

        if(ptr.isNull())
        {
            aprodebug("Listener \"") << listener << "\" given not found.";
            return false;
        }

        return sendEvent(e, listener);
    }

    void EventEmitter::sendASynchronousEvent(EventPtr& e, EventUniter* event_uniter)
    {
        if(!e.isNull())
        {
            if(!event_uniter)
                event_uniter = &(EventUniter::Get());

            if(!event_uniter)
            {
                aprodebug("No EventUniter detected.");
                return;
            }

            ListenersList::const_iterator e = listeners.end();
            for(ListenersList::iterator it = listeners.begin(); it != e; it++)
            {
                event_uniter->push(e, it);
            }
        }
    }

    void EventEmitter::sendAsynchronousEvent(EventPtr& e, EventListenerPtr& listener, EventUniter* event_uniter)
    {
        if(listener.isNull())
        {
            aprodebug("Null listener given.");
            return;
        }

        if(!e.isNull())
        {
            if(!event_uniter)
                event_uniter = &(EventUniter::Get());

            if(!event_uniter)
            {
                aprodebug("No EventUniter detected.");
                return;
            }

            event_uniter->push(e, listener);
        }
    }

    void EventEmitter::sendAsynchronousEvent(EventPtr& e, const String& name, EventUniter* event_uniter)
    {
        EventListenerPtr& ptr = getListener(name);

        if(ptr.isNull())
        {
            aprodebug("Listener \"") << name << "\" given not found.";
            return;
        }

        sendAsynchronousEvent(e, ptr, event_uniter);
    }

    void EventEmitter::sendAsynchronousEvent(EventPtr& e, const Id& listener, EventUniter* event_uniter)
    {
        EventListenerPtr& ptr = getListener(listener);

        if(ptr.isNull())
        {
            aprodebug("Listener \"") << listener << "\" given not found.";
            return;
        }

        sendAsynchronousEvent(e, ptr, event_uniter);
    }

    void EventEmitter::documentEvent(const HashType& event, const String& description)
    {
        events[event] = description;
    }

    String EventEmitter::documentation() const
    {
        String ret("[EventEmitter] Events documentation");
        ret   << "\n-----------------------------------"
              << "\n";

        for (unsigned int i = 0; i < events.size(); ++i)
        {
            ret << " + " << events.getPair(i).first() << " : " << events.getPair(i).second() << "\n";
        }

        ret << "-----------------------------------";
        return ret;
    }

    const String& EventEmitter::getEventDocumentation(const HashType& event) const
    {
        events.exists(event) ? return events[event] : return String();
    }

    bool EventEmitter::isEventDocumented(const HashType& event) const
    {
        return events.exists(event);
    }

    bool EventEmitter::isEventHandled(const HashType& event) const
    {
        return events.exists(event);
    }

    int EventEmitter::registerListener(const EventListenerPtr& listener)
    {
        if(!listener.isNull())
        {
            EventListenerPtr& _phl = getListener(listener->getName());
            if(!_phl.isNull())
            {
                Console::get() << "\n[EventEmitter]{registerListener} Can't register listener \"" << listener->getName() << "\" because name already taken.";
                return -1;
            }
            else
            {
                listeners.append(listener);
                return listeners.lastIndex();
            }
        }
        else
        {
            return -1;
        }
    }

    int EventEmitter::unregisterListener(const String& name)
    {
        if(!name.isEmpty())
        {
            EventListenerPtr& _listener = getListener(name);
            if(_listener.isNull())
            {
                Console::get() << "\n[EventEmitter]{unregisterListener} Can't find listener \"" << name << "\".";
                return -1;
            }
            else
            {
                int index = listeners.find(_listener);
                listeners.erase(index);
                return index;
            }
        }

        return -1;
    }

    int EventEmitter::unregisterListener(const Id& id)
    {
        EventListenerPtr& _listener = getListener(id);
        if(_listener.isNull())
        {
            Console::get() << "\n[EventEmitter]{unregisterListener} Can't find listener \"" << id << "\".";
            return -1;
        }
        else
        {
            int index = listeners.find(_listener);
            listeners.erase(index);
            return index;
        }

        return -1;
    }

    const EventListenerPtr& EventEmitter::getListener(const String& name) const
    {
        if(!name.isEmpty())
        {
            const EventListenerPtr& _listener;
            for(unsigned int i = 0; i < listeners.size(); ++i)
            {
                _listener = listeners.at(i);
                if(!_listener.isNull() && _listener->getName() == name)
                {
                    return _listener;
                }
            }

            return nullptr;
        }
        else
        {
            return EventListenerPtr();
        }
    }

    EventListenerPtr& EventEmitter::getListener(const String& name)
    {
        if(!name.isEmpty())
        {
            EventListenerPtr& _listener;
            for(unsigned int i = 0; i < listeners.size(); ++i)
            {
                _listener = listeners.at(i);
                if(!_listener.isNull() && _listener->getName() == name)
                {
                    return _listener;
                }
            }

            return nullptr;
        }
        else
        {
            return EventListenerPtr();
        }
    }

    const EventListenerPtr& EventEmitter::getListener(const Id& identifier) const
    {
        const EventListenerPtr& plistener;
        for (unsigned int i = 0; i < listeners.size(); ++i)
        {
            plistener = listeners.at(i);
            if(!plistener.isNull() && plistener->getId() == identifier)
            {
                return plistener;
            }
        }

        return nullptr;
    }

    EventListenerPtr& EventEmitter::getListener(const Id& identifier)
    {
        EventListenerPtr& plistener;
        for (unsigned int i = 0; i < listeners.size(); ++i)
        {
            plistener = listeners.at(i);
            if(!plistener.isNull() && plistener->getId() == identifier)
            {
                return plistener;
            }
        }

        return nullptr;
    }

    EventPtr EventEmitter::createEvent(const HashType& e_type) const
    {
        aprodebug("Creating default NullEvent because no overwritten function is available.");
        EventPtr ret = AProNew(NullEvent);
        ret->m_emitter = this;
        return ret;
    }

    void EventEmitter::setEmitPolicy(EmitPolicy ep)
    {
        epolicy = ep;
    }

}
