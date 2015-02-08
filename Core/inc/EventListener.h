/////////////////////////////////////////////////////////////
/** @file EventListener.h
 *  @ingroup Events
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 11/09/2012 - 07/02/2015
 *
 *  @brief
 *  Defines the EventListener class.
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
#ifndef APROEVENTLISTENER_H
#define APROEVENTLISTENER_H

#include "Platform.h"
#include "AutoPointer.h"
#include "Event.h"
#include "Array.h"

namespace APro
{
    /////////////////////////////////////////////////////////////
    /** @class EventListener
     *  @ingroup Events
     *  @brief An object that handle events emitted.
     *
     *  A listener is an object that have the possibility to handle
     *  a given event. @note The listener never destroy the event.
     *
     *  It process the event depending on its type, but by default,
     *  it does nothing. You must overload the ::handle function
     *  to modify the comportment of the listener.
     *
     *  Some Engine class will have their own pre-fabriced listeners,
     *  we hope you will have good use of it.
     *
     *  The listener have a unique identifiable id.
     *
     *  ### Process of handling an event by the Listener.
     * 
     *  - 1. Event is null ?
     *  - 2. Event is allowed ?
     *  - 3. Listener call the handle() method.
     *  - 4. Listener calls every callbacks <b>in the order they
     *  were registered<\b>.
     *  - 5. Returns true, that indicates event has been handled
     *  correctly by the Listener.
    **/
    /////////////////////////////////////////////////////////////
    class APRO_DLL EventListener  //public BaseObject <EventListener>
    {
	protected:
		
		typedef std::function<void (Event&)> Callback;
		typedef Array<Callback> Callbacks;
		typedef Map<HashType, Callbacks> CallbacksbyType;
		
    protected:

        String          m_name;         ///< @brief Name of the listener.
        Id              id;             ///< @brief Id of this listener.
        EventCopy*      last_event;     ///< @brief Last event received by this listener.
        HashArray       eventprocessed; ///< @brief List of event normally processed by this listener.
        CallbacksbyType callbacks;      ///< @brief Array of callbacks to call, filtered by event type.

    public:

        /////////////////////////////////////////////////////////////
        /** @brief Constructor.
         *
         *  @param name : Name of the listener newly created.
         *  @note A new id is generated in this function.
        **/
        /////////////////////////////////////////////////////////////
        EventListener(const String & name = String("no_name"));
        
        /////////////////////////////////////////////////////////////
        /** @brief Copy a listener.
        **/
        /////////////////////////////////////////////////////////////
        EventListener(const EventListener& other);
        
		/////////////////////////////////////////////////////////////
        /** @brief Destructs the Listener.
        **/
        /////////////////////////////////////////////////////////////
        virtual ~EventListener() {}

    public:

        /////////////////////////////////////////////////////////////
        /** @brief Receive an event, store it as last received and
         *  handle it.
         *  @param event : Event to receive.
         *  @return true if event has been correctly passed through the
         *  function.
        **/
        /////////////////////////////////////////////////////////////
        bool receive(EventRef event);
        
        /////////////////////////////////////////////////////////////
        /** @brief Returns true if this Listener has ever received any
         *  Event.
        **/
        /////////////////////////////////////////////////////////////
        bool hasLastEvent() const { return last_event != nullptr; }

    protected:

        /////////////////////////////////////////////////////////////
        /** @brief Handle a given event.
         *
         *  As this function is called at the end of receive, you should
         *  not process to null-pointer verification, nor change the
         *  last received event because it is the receive function
         *  job.
         *
         *  @param event : Event to handle.
         *  @return true if event is used, user-dependant.
        **/
        /////////////////////////////////////////////////////////////
        virtual bool handle(EventRef event) { return true; };

    public:

        /////////////////////////////////////////////////////////////
        /** @brief Return the name of this listener.
        **/
        /////////////////////////////////////////////////////////////
        const String& getName() const;

        /////////////////////////////////////////////////////////////
        /** @brief Return the last event received by this listener.
        **/
        /////////////////////////////////////////////////////////////
        const EventRef getLastEventReceived() const;

        /////////////////////////////////////////////////////////////
        /** @brief Return the id of this listener.
        **/
        /////////////////////////////////////////////////////////////
        const unsigned long getId() const;

    public:

        /////////////////////////////////////////////////////////////
        /** @brief Add an event to the list of processed events.
        **/
        /////////////////////////////////////////////////////////////
        void addEventProcessed(const HashType& event);

        /////////////////////////////////////////////////////////////
        /** @brief Remove an event from the list of processed events.
        **/
        /////////////////////////////////////////////////////////////
        void removeEventProcessed(const HashType& event);

        /////////////////////////////////////////////////////////////
        /** @brief Tell if an event can normally be processed by this
         *  listener.
        **/
        /////////////////////////////////////////////////////////////
        bool isEventProcessed(const HashType& event) const;
        
	public:
		
		/////////////////////////////////////////////////////////////
        /** @brief Adds a callback to this listener.
         *
         *  @warning
         *  The given callback can be removed only using the ::clearCallbacks()
         *  method, which removes every other callbacks.
        **/
        /////////////////////////////////////////////////////////////
		void addCallback(const HashType& event, Callback func);
		
		/////////////////////////////////////////////////////////////
        /** @brief Removes every callbacks for a given event.
        **/
        /////////////////////////////////////////////////////////////
		void clearCallbacks(const HashType& event);
		
		/////////////////////////////////////////////////////////////
        /** @brief Removes every callbacks.
        **/
        /////////////////////////////////////////////////////////////
		void clearAllCallbacks();
    };

    typedef AutoPointer<EventListener> EventListenerPtr;///< AutoPointer of EventListener. No custom destruction needed, so simple typedef used.
}

#endif
