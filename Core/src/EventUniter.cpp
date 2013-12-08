/////////////////////////////////////////////////////////////
/** @file EventUniter.cpp
 *  @ingroup Event
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 02/12/2013
 *
 *  Implements the EventUniter object.
 *
 **/
/////////////////////////////////////////////////////////////
#include "EventUniter.h"
#include "ThreadManager.h"

namespace APro
{
    APRO_IMPLEMENT_MANUALSINGLETON(EventUniter)

    EventUniter::EventUniter(const String& n)
        : Thread(n)
    {

    }

    EventUniter::~EventUniter
    {
        terminate();
        events.clear();
    }

    void EventUniter::push(EventPtr& e, EventListenerPtr& l)
    {
        APRO_THREADSAFE_AUTOLOCK

        EventEntry _entry;
        _entry.event    = e;
        _entry.listener = l;

        events.push(_entry);
    }

    void EventUniter::exec()
    {
        // Infinite loop to send events to listeners.
        // This loop can and should be terminated by the
        // destructor of this class.
        while(1)
        {
            EventEntry _entry;
            {
                APRO_THREADSAFE_AUTOLOCK
                _entry = events.get();
                events.pop();
            }

            if(_entry.event.isNull() || ! _entry.event->isValid())
            {
                aprodebug("Incorrect event given.");
                continue;
            }

            if(_entry.event->must_stop)
            {
                aprodebug("Event has stop flag setted.");
                continue;
            }

            if(!_entry.listener.isNull())
            {
                _entry.listener->receive(e);
            }
        }
    }


}
