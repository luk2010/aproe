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
        
    }
    
    EventEmitter::EventEmitter(const EventEmitter& emitter)
    {
        listeners = emitter.listeners;
        events    = emitter.events;
    }
    
    EventEmitter::~EventEmitter()
    {
        
    }
    
    unsigned int EventEmitter::sendEvent(const EventPtr& e, EventListenerPtr& listener)
    {
        if(!e.isNull())
        {
            unsigned int ret = 0;
            
            if(listener.isNull())
            {
                // Send to every listeners registered
                for(unsigned int i = 0; i < listeners.size(); ++i)
                {
                    EventListenerPtr& _listener = listeners.at(i);
                    ret += sendEvent(e, _listener);
                }
            }
            else
            {
                // Send to given listener
                if(listener->receive(e))
                {
                    ret += 1;
                }
            }
            
            return ret;
        }
        
        Console::get() << "\n[EventEmitter]{sendEvent} Null event tried to be send !";
        return 0;
    }
    
    unsigned int EventEmitter::sendEvent(const EventPtr& e, const String& listener)
    {
        if(!e.isNull())
        {
            EventListenerPtr& _listener = getListener(listener);
            if(!_listener.isNull())
            {
                return sendEvent(e, _listener);
            }
            else
            {
                if(listener == "__all")
                {
                    return sendEvent(e, nullptr);
                }
                else
                {
                    if(listener.isEmpty())
                    {
                        Console::get() << "\n[EventEmitter]{sendEvent} No listener provided ! Send \"__all\" if you don't want to set one specific.";
                        return 0;
                    }
                    else
                    {
                        Console::get() << "\n[EventEmitter]{sendEvent} Can't find listener \"" << listener << "\".";
                        return 0;
                    }
                }
            }
        }
        
        Console::get() << "\n[EventEmitter]{sendEvent} Null event tried to be send !";
        return 0;
    }
    
    unsigned int EventEmitter::sendEvent(const EventPtr& e, const Id& listener)
    {
        if(!e.isNull())
        {
            EventListenerPtr& plistener = getListener(listener);
            if(plistener.isNull())
            {
                Console::get() << "\n[EventEmitter]{sendEvent} Listener's id \"" << listener << "\" not registered !";
                return 0;
            }
            else
            {
                return sendEvent(plistener);
            }
        }
        
        Console::get() << "\n[EventEmitter]{sendEvent} Null event tried to be send !";
        return 0;
    }
    
    unsigned int EventEmitter::sendASynchronousEvent(const EventPtr& e, EventUniter* event_uniter)
    {
        if(!e.isNull())
        {
            if(!event_uniter)
            {
                event_uniter = Main::get().getEventUniter();
            }
            
            return event_uniter->push(e) ? 1 : 0;
        }
        
        Console::get() << "\n[EventEmitter]{sendASynchronousEvent} Null event tried to be send !";
        return 0;
    }
    
    void EventEmitter::documentEvent(const String& event, const String& description)
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
    
    const String EventEmitter::getEventDocumentation(const String& event) const
    {
        events.exists(event) ? return events[event] : return String();
    }
    
    bool EventEmitter::isEventDocumented(const String & event) const
    {
        return events.exists(event);
    }
    
    bool EventEmitter::isEventHandled(const String & event) const
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
    
    EventPtr createAndPopulateEvent(const String& event_type, bool set_target, EventListenerPtr& target) const
    {
        if(!isEventHandled(event_type))
        {
            Console::get() << "\n[Console]{createAndPopulateEvent} Sending not handled event type \"" << event_type << "\" is not recommended !";
        }
        
        EventPtr ret = AProNew(Event) (event_type, this, set_target ? target.getPointer() : nullptr);
        
        if(ret.isNull())
        {
            Console::get() << "\n[Console]{createAndPopulateEvent} Couldn't create event \"" << event_type << "\".";
        }
        else
        {
            populateEvent(ret);
        }
        
        return ret;
    }
    
}
