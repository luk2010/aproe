/////////////////////////////////////////////////////////////
/** @file EventUniter.h
 *  @ingroup Event
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 02/12/2013 - 07/02/2015
 *
 *  @brief
 *  Defines the EventUniter object.
 *
 *  @copyright
 *  Atlanti's Project Engine
 *  Copyright (C) 2012 - 2015  Atlanti's Corp
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
#ifndef APRO_EVENTUNITER_H
#define APRO_EVENTUNITER_H

#include "Platform.h"
#include "BaseObject.h"
#include "ThreadSafe.h"

#include "Queue.h"
#include "Event.h"
#include "Thread.h"
#include "ThreadCondition.h"

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
    class APRO_DLL EventUniter : 
    	public BaseObject <EventUniter>,
		public Thread
    {
        APRO_DECLARE_MANUALSINGLETON(EventUniter)
        
	public:
		
		typedef Array<EventListenerPtr> ListenersArray;						
		typedef struct _SendCommand
        {
        	EventCopy* 		eventptr;  ///< @brief A COPY of the Event to send, made generally by the EventEmitter.
        	ListenersArray 	listeners; ///< @brief An Array of listeners, to which to send the Event to.
        	
        	bool operator == (const struct _SendCommand& rhs) const {
        		return eventptr == rhs.eventptr &&
					   listeners == rhs.listeners;
        	}
        	
        	bool operator != (const struct _SendCommand& rhs) const {
        		return eventptr != rhs.eventptr ||
					   listeners != rhs.listeners;
        	}
        } SendCommand;

    private:
        
        Queue<SendCommand> commands; ///< @brief Commands the Uniter have to send, in order.
        ThreadCondition    idlecondition; ///< @brief Thread Condition for idling purpose.
        bool               isidling; ///< @brief True if idling.

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
        /** @brief Push a Command in the Queue.
        **/
        /////////////////////////////////////////////////////////////
        void push(SendCommand& command);
        
        /////////////////////////////////////////////////////////////
        /** @brief Returns true if this Uniter is waiting for an Event
         *  to send.
        **/
        /////////////////////////////////////////////////////////////
        bool isIdling() const { return isidling; }

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
