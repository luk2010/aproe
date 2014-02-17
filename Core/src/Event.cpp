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

    APRO_REGISTER_EVENT_NOCONTENT(NullEvent)

    Event::Event()
    {
        m_type      = 0;
        m_id        = Main::Get().getIdGenerator().pick();
        m_target    = nullptr;
        m_emitter   = nullptr;
        must_stop   = false;
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
            aprothrow_ce("NullPtrToReference", "Null emitter !", "Event");
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

    HashType Event::type() const
    {
        return m_type;
    }

    unsigned long Event::id() const
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

    bool Event::isValid() const
    {
        return m_type != 0;
    }

    bool Event::isNullEvent() const
    {
        return m_type == NullEvent::Hash;
    }

    void Event::mustStop()
    {
        must_stop = true;
    }

}
