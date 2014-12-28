/////////////////////////////////////////////////////////////
/** @file EventEmitter.cpp
 *  @ingroup Events
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 11/09/2012 - 27/12/2014
 *
 *  @brief
 *  Implements the EventEmitter class.
 *
 *  @copyright
 *  Atlanti's Project Engine
 *  Copyright (C) 2012 - 2014  Atlanti's Corp
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
**/
/////////////////////////////////////////////////////////////
#include "EventEmitter.h"
#include "EventUniter.h"
#include "Console.h"

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
        epolicy   = EP_MANUAL;
    }

    EventEmitter::~EventEmitter()
    {

    }

    bool EventEmitter::sendEvent(EventLocalPtr e)
    {
        if(e == nullptr || ! e->isValid())
        {
            aprodebug("Incorrect event given.");
            return false;
        }

        if(e->must_stop)
        {
            aprodebug("Event has stop flag setted.");
            return false;
        }

        /*
			In Manual mode, we simply send the Event to every Listeners waiting
			them to handle the Event.
		*/
        if(epolicy == EP_MANUAL)
        {
            bool tmp = false;
            
            // Global List
            for(ListenersList::iterator it = listenersbytype[0].begin(); 
					it != listenersbytype[0].end() && !(e->must_stop); it++)
            {
                if((*it)->receive( (EventRef) *e))
                    tmp = true;
            }
            
            // Specific List
            for(ListenersList::iterator it = listenersbytype[e->type()].begin(); 
					it != listenersbytype[e->type()].end() && !(e->must_stop); it++)
            {
                if((*it)->receive( (EventRef) *e))
                    tmp = true;
            }

            return tmp;
        }
        
        /*
			In Uniter Mode, we send the Event to the Uniter, which will make 
			a COPY of this event and then will send it to every target we send
			to it.
        */
        else if(epolicy == EP_UNITER)
        {
            sendASynchronousEvent(e);
            return true;// Stub
        }
        
        /*
			In other mode, only passthrough.
        */
        else {
            return true;// Stub
        }
    }

    bool EventEmitter::sendEvent(EventLocalPtr e, EventListenerPtr& listener)
    {
        if(e == nullptr || ! e->isValid())
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
            return listener->receive( (EventRef) *e);
        }
        else
        {
            aprodebug("Incorrect listener given to EventEmitter. Sending event to every listeners registered.");
            return sendEvent(e);
        }
    }

    bool EventEmitter::sendEvent(EventLocalPtr e, const String& listener)
    {
        EventListenerPtr& ptr = getListener(listener);

        if(ptr.isNull())
        {
            aprodebug("Listener \"") << listener << "\" given not found.";
            return false;
        }

        return sendEvent(e, listener);
    }

    bool EventEmitter::sendEvent(EventLocalPtr e, const Id& listener)
    {
        EventListenerPtr& ptr = getListener(listener);

        if(ptr.isNull())
        {
            aprodebug("Listener \"") << (long unsigned int) listener << "\" given not found.";
            return false;
        }

        return sendEvent(e, listener);
    }

    void EventEmitter::sendASynchronousEvent(EventLocalPtr e, EventUniter* event_uniter)
    {
        if(! (e == nullptr))
        {
            if(!event_uniter)
                event_uniter = &(EventUniter::Get());

            if(!event_uniter)
            {
                aprodebug("No EventUniter detected.");
                return;
            }
            
            EventUniter::SendCommand cmd;
            cmd.eventptr = static_cast<Event*>(e->clone());
            cmd.listeners.append(listenersbytype[0]);
            cmd.listeners.append(listenersbytype[e->type()]);
            event_uniter->push(cmd);
        }
    }

    void EventEmitter::sendAsynchronousEvent(EventLocalPtr e, EventListenerPtr& listener, EventUniter* event_uniter)
    {
        if(listener.isNull())
        {
            aprodebug("Null listener given.");
            return;
        }

        if(! (e == nullptr))
        {
            if(!event_uniter)
                event_uniter = &(EventUniter::Get());

            if(!event_uniter)
            {
                aprodebug("No EventUniter detected.");
                return;
            }

            EventUniter::SendCommand cmd;
            cmd.eventptr = static_cast<Event*>(e->clone());
            cmd.listeners.append(listener);
            event_uniter->push(cmd);
        }
    }

    void EventEmitter::sendAsynchronousEvent(EventLocalPtr e, const String& name, EventUniter* event_uniter)
    {
        EventListenerPtr& ptr = getListener(name);

        if(ptr.isNull())
        {
            aprodebug("Listener \"") << name << "\" given not found.";
            return;
        }

        sendAsynchronousEvent(e, ptr, event_uniter);
    }

    void EventEmitter::sendAsynchronousEvent(EventLocalPtr e, const Id& listener, EventUniter* event_uniter)
    {
        EventListenerPtr& ptr = getListener(listener);

        if(ptr.isNull())
        {
            aprodebug("Listener \"") << (long unsigned int) listener << "\" given not found.";
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

        EventsList::const_iterator e = events.end();
        for (EventsList::const_iterator it = events.begin(); it != e; it++)
        {
            ret << " + Hash['" << it.key() << "'] : " << it.value() << "\n";
        }

        ret << "-----------------------------------";
        return ret;
    }

    const String& EventEmitter::getEventDocumentation(const HashType& event) const
    {
        if(events.keyExists(event))
            return events.at(event);
        else
            return String::Empty;
    }

    bool EventEmitter::isEventDocumented(const HashType& event) const
    {
        return events.keyExists(event);
    }

    bool EventEmitter::isEventHandled(const HashType& event) const
    {
        return events.keyExists(event);
    }
    
    EventListenerPtr EventEmitter::registerListener(const String& nlistener)
    {
    	EventListenerPtr& _phl = getListener(nlistener);
    	if(!_phl.isNull())
		{
			Console::Get() << "\n[EventEmitter]{registerListener} Can't register listener \"" << nlistener << "\" because name already taken.";
			return EventListenerPtr::Null;
		}
		else
		{
			EventListenerPtr listener = AProNew(EventListener);
			listeners.append(listener);
			listenersbytype[0].append(listener);
			return listener;
		}
    }

    int EventEmitter::registerListener(const EventListenerPtr& listener)
    {
        if(!listener.isNull())
        {
            EventListenerPtr& _phl = getListener(listener->getName());
            if(!_phl.isNull())
            {
                Console::Get() << "\n[EventEmitter]{registerListener} Can't register listener \"" << listener->getName() << "\" because name already taken.";
                return -1;
            }
            else
            {
                listeners.append(listener);
                listenersbytype[0].append(listener);
                return listeners.size() - 1;
            }
        }
        else
        {
            return -1;
        }
    }
    
    EventListenerPtr EventEmitter::registerListener(const String& nlistener, std::initializer_list<HashType> elist)
    {
    	EventListenerPtr& _phl = getListener(nlistener);
    	if(!_phl.isNull())
		{
			Console::Get() << "\n[EventEmitter]{registerListener} Can't register listener \"" << nlistener << "\" because name already taken.";
			return EventListenerPtr::Null;
		}
		else
		{
			EventListenerPtr listener = AProNew(EventListener);
			listeners.append(listener);
			
			for(auto type : elist) {
				listenersbytype[type].append(listener);
			}
			
			return listener;
		}
    }
    
    int EventEmitter::registerListener(const EventListenerPtr& listener, std::initializer_list<HashType> elist)
    {
    	if(!listener.isNull())
        {
            EventListenerPtr& _phl = getListener(listener->getName());
            if(!_phl.isNull())
            {
                Console::Get() << "\n[EventEmitter]{registerListener} Can't register listener \"" << listener->getName() << "\" because name already taken.";
                return -1;
            }
            else
            {
                listeners.append(listener);
                
                for(auto type : elist) {
					listenersbytype[type].append(listener);
                }
                
                return listeners.size() - 1;
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
                Console::Get() << "\n[EventEmitter]{unregisterListener} Can't find listener \"" << name << "\".";
                return -1;
            }
            else
            {
                int index = listeners.find(_listener);
                listeners.erase(listeners.begin()+(size_t)index);
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
            Console::Get() << "\n[EventEmitter]{unregisterListener} Can't find listener \"" << (int) id << "\".";
            return -1;
        }
        else
        {
            int index = listeners.find(_listener);
            listeners.erase(listeners.begin()+(size_t)index);
            return index;
        }

        return -1;
    }

    const EventListenerPtr& EventEmitter::getListener(const String& name) const
    {
        if(!name.isEmpty())
        {
            for(unsigned int i = 0; i < listeners.size(); ++i)
            {
                const EventListenerPtr& _listener = listeners.at(i);
                if(!_listener.isNull() && _listener->getName() == name)
                {
                    return _listener;
                }
            }

            return EventListenerPtr::Null;
        }
        else
        {
            return EventListenerPtr::Null;
        }
    }

    EventListenerPtr& EventEmitter::getListener(const String& name)
    {
        if(!name.isEmpty())
        {
            for(unsigned int i = 0; i < listeners.size(); ++i)
            {
                EventListenerPtr& _listener = listeners.at(i);
                if(!_listener.isNull() && _listener->getName() == name)
                {
                    return _listener;
                }
            }

            return EventListenerPtr::Null;
        }
        else
        {
            return EventListenerPtr::Null;
        }
    }

    const EventListenerPtr& EventEmitter::getListener(const Id& identifier) const
    {
        for (unsigned int i = 0; i < listeners.size(); ++i)
        {
            const EventListenerPtr& plistener = listeners.at(i);
            if(!plistener.isNull() && plistener->getId() == identifier)
            {
                return plistener;
            }
        }

        return EventListenerPtr::Null;
    }

    EventListenerPtr& EventEmitter::getListener(const Id& identifier)
    {
        for (unsigned int i = 0; i < listeners.size(); ++i)
        {
            EventListenerPtr& plistener = listeners.at(i);
            if(!plistener.isNull() && plistener->getId() == identifier)
            {
                return plistener;
            }
        }

        return EventListenerPtr::Null;
    }

    EventLocalPtr EventEmitter::createEvent(const HashType& e_type) const
    {
        aprodebug("Creating default NullEvent because no overwritten function is available.");
        EventLocalPtr ret (AProNew(NullEvent));
        ret->m_emitter = this;
        return ret;
    }

    void EventEmitter::setEmitPolicy(EmitPolicy ep)
    {
        epolicy = ep;
    }

}
