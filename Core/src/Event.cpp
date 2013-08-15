/////////////////////////////////////////////////////////////
/** @file Event.cpp
 *  @ingroup Events
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 11/09/2012
 *
 *  Implements the Event class.
 *
 **/
/////////////////////////////////////////////////////////////
#include <Event.h>
#include <Main.h>// For the id generator.

#include <EventEmitter.h>
#include <EventListener.h>

namespace APro
{
    Event::Event(const String& type, EventEmitter* _emitter, EventListener* _target)
    : ParametedObject()
    {
        m_type      = type;
        m_id        = Main::get().getIdGenerator().pick();
        m_target    = _target;
        m_emitter   = _emitter;
    }
    
    Event::~Event()
    {
        
    }
    
    EventEmitter& Event::emitter()
    {
        if(m_emitter) 
            return *m_emitter;
        else
        {
            APRO_THROW("NullPtrToReference", "Null emitter !", "Event");
        }
    }
    
    const EventEmitter& Event::emitter() const
    {
        if(m_emitter) 
            return *m_emitter;
        else
        {
            APRO_THROW("NullPtrToReference", "Null emitter !", "Event");
        }
    }
    
    EventListener& Event::listener()
    {
        if(m_listener)
            return *m_listener;
        else
        {
            APRO_THROW("NullPtrToReference", "Null target !", "Event");
        }
    }
    
    const EventListener& Event::listener() const
    {
        if(m_listener)
            return *m_listener;
        else
        {
            APRO_THROW("NullPtrToReference", "Null target !", "Event");
        }
    }
    
    const String& Event::type() const
    {
        return m_type;
    }
    
    const unsigned int & Event::id() const
    {
        return m_id;
    }
    
    bool Event::hasEmitter() const
    {
        return m_emitter == nullptr;
    }
    
    bool Event::hasListener() const
    {
        return m_listener == nullptr;
    }
    
}
