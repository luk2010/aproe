/////////////////////////////////////////////////////////////
/** @file EventUniter.h
 *  @ingroup Event
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 02/12/2013
 *
 *  Defines the EventUniter object.
 *
 **/
/////////////////////////////////////////////////////////////
#ifndef APRO_EVENTUNITER_H
#define APRO_EVENTUNITER_H

#include "Platform.h"
#include "Queue.h"
#include "Event.h"
#include "Thread.h"

namespace APro
{
    /////////////////////////////////////////////////////////////
    /** @class EventUniter
     *  @ingroup Event
     *  @brief A threaded event queue.
     *
     *  Events pushed in the Uniter will be sended by a threaded
     *  loop.
     *  EventEmitter can automaticly send events to the Global Uniter
     *  using the EP_UNITER flag instead of the EP_MANUAL flag wich
     *  is the default one.
     *
     *  EventUniter doesn't have registered listeners. You must tell
     *  wich listener will receive given event in the loop.
     *
     *  @note The EventUniter is a particular thread that doesn't
     *  not count in the ThreadManager. You can create one without,
     *  but you must be sure that the thread is terminated. It can
     *  be done in the destructor while destructing the object.
    **/
    /////////////////////////////////////////////////////////////
    class APRO_DLL EventUniter : public ThreadSafe,
                                 public Thread
    {
        APRO_DECLARE_MANUALSINGLETON(EventUniter)

    private:

        typedef struct EventEntry
        {
            EventPtr         event;
            EventListenerPtr listener;
        } EventEntry;
        Queue<EventEntry> events;///< Events in the loop.

    public:

        /////////////////////////////////////////////////////////////
        /** @brief Constructs the EventUniter.
        **/
        /////////////////////////////////////////////////////////////
        EventUniter(const String& n = String("Unkown"));

        /////////////////////////////////////////////////////////////
        /** @brief Destructs the EventUniter.
         *
         *  The thread is terminated and every events are destroyed.
         *  Not sended events are lost during the operation.
        **/
        /////////////////////////////////////////////////////////////
        ~EventUniter();

    public:

        /////////////////////////////////////////////////////////////
        /** @brief Push an event in the Queue.
         *
         *  It will be sended to given listener.
        **/
        /////////////////////////////////////////////////////////////
        void push(EventPtr& e, EventListenerPtr& l);

    protected:

        ////////////////////////////////////////////////////////////
        /** @brief Main procedure of this thread.
         *  @see Thread::exec()
        **/
        ////////////////////////////////////////////////////////////
        virtual void exec();

    };
}

#endif // APRO_EVENTUNITER_H
