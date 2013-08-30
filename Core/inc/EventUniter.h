/////////////////////////////////////////////////////////////
/** @file EventUniter.h
 *  @ingroup Event
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 03/07/2013
 *
 *  Defines the EventUniter object.
 *
 **/
/////////////////////////////////////////////////////////////
#ifndef APRO_EVENTUNITER_H
#define APRO_EVENTUNITER_H

#include <Platform.h>
#include <Queue.h>
#include <Event.h>

namespace APro
{
    class APRO_DLL EventUniter
    {
    protected:

        Queue<EventPtr> event_queue;

    public:

        EventUniter();
        ~EventUniter();

    public:

        void addEvent(
    };
}

#endif // APRO_EVENTUNITER_H
