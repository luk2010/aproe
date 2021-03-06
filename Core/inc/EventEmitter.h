/////////////////////////////////////////////////////////////
/** @file EventEmitter.h
 *  @ingroup Events
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 11/09/2012 - 17/01/2015
 *
 *  @brief
 *  Defines the EventEmitter class.
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
#ifndef APROEVENTEMITTER_H
#define APROEVENTEMITTER_H

#include "List.h"
#include "Event.h"
#include "EventListener.h"
#include "ThreadSafe.h"

namespace APro
{
    class EventUniter;

    /////////////////////////////////////////////////////////////
    /** @class EventEmitter
     *  @ingroup Events
     *  @brief An Event emitter entering the synchronous event
     *  subsystem.
     *
     *  The Emitters / Listeners system is a synchronous event
     *  system. When the emitter emit the event, he will call
     *  appropriate function to make the listener handle the event.
     *  This has no conflict with threaded systems.
     *  @note The emitter can send event using the Uniter system
     *  thanks to EventEmitter::sendASynchronousEvent.
     *
     *  @note If the event's target is null, the emitter send it to
     *  all his listeners.
     *
     *  The emitter creates the events it has to send. It populates
     *  it with correct datas. The listener just receive it and this
     *  is the listener problem to handle it.
     *
     *  @note Getting listeners by name only get the first listener
     *  with given name, you should use unique id's instead.
     *
     *  You can set an EmitPolicy to the Emitter :
     *  - EP_NONE : The emitter doesn't send the event, even if
     *  asked. It does <br>not</br> totally disable event sending action
     *  as you always can send events using manual function specifying
     *  the listener or the uniter.
     *  - EP_MANUAL : The emitter send the events to registered listeners,
     *  no threaded queue. This is the default behaviour.
     *  - EP_UNITER : The emitter send event to the Global Uniter,
     *  this is a threaded system.
     *
     *  This policy choice let you change the default behaviour of the
     *  emitter by the EventEmitter::send() function. But you also can
     *  have the EP_MANUAL policy and send events to the uniter thanks
     *  to EventEmitter::sendAsynchronousEvent().
     *
     *  @note The EmitPolicy affects only the EventEmitter::sendEvent(event)
     *  function. If you specifies the listener, it will send to the
     *  listener. The EmitPolicy is here just to make easier the choice
     *  to send event to registered listeners or to GlobalUniter.
     *
     *  @see Events for more explanation about the event system.
    **/
    /////////////////////////////////////////////////////////////
    class APRO_DLL EventEmitter :
    	virtual public ThreadSafe
    {
    protected:

        typedef Map<HashType, String>  EventsList;   ///< List of events type, with documentation.
        typedef Array<EventListenerPtr> ListenersList;///< List of listeners pointer.
        typedef Map<HashType, ListenersList> ListenersByType; ///< @brief If an Event Type have been specified for a Listener, store it here.

        enum EmitPolicy
        {
            EP_NONE,   ///< Events are send to no-one.
            EP_MANUAL, ///< Events are send to the registered listeners, directly.
            EP_UNITER  ///< Events are send to the global uniter.
        };

        ListenersList   listeners;///< List of AutoPointer to listeners.
        ListenersByType listenersbytype; ///< @brief Map of Listeners by Type (General Listeners in the 0 type.)
        EventsList      events;   ///< List of events type with documentation, handled correctly by this emitter.
        EmitPolicy      epolicy;  ///< Current EmitPolicy. By default, it is EP_MANUAL.

    public:

        /////////////////////////////////////////////////////////////
        /** @brief Constructor.
        **/
        /////////////////////////////////////////////////////////////
        EventEmitter();

        /////////////////////////////////////////////////////////////
        /** @brief Copy Constructor.
        **/
        /////////////////////////////////////////////////////////////
        EventEmitter(const EventEmitter& emitter);

        /////////////////////////////////////////////////////////////
        /** @brief Destructor.
        **/
        /////////////////////////////////////////////////////////////
        virtual ~EventEmitter();

    public:

        /////////////////////////////////////////////////////////////
        /** @brief Send an event using the Synchronous Event System.
         *
         *  Send given event to every listeners registered in this
         *  emitter. Process can be stop if listener receiving the event
         *  set 'stop' event flag to true.
         *
         *  @param e : Event to send. If null, nothing is done in this
         *  function.
         *  @return True if event has been handled at least one time.
        **/
        /////////////////////////////////////////////////////////////
        bool sendEvent(EventLocalPtr e);

        /////////////////////////////////////////////////////////////
        /** @brief Send an event using the Synchronous Event System.
         *
         *  @param e : Event to send. If null, nothing is done in this
         *  function.
         *  @param listener : Listener to send the event to. If null,
         *  the emitter will send it to every listener registered, but
         *  it shall not be as the function sendEvent(EventPtr) exists.
         *  @return True if event has been handled.
        **/
        /////////////////////////////////////////////////////////////
        bool sendEvent(EventLocalPtr e, EventListenerPtr& listener);

        /////////////////////////////////////////////////////////////
        /** @brief Send an event using the Synchronous Event System.
         *
         *  @param e : Event to send. If the event is null, nothing is
         *  done in this function.
         *  @param name : Name of the registered listener to send the
         *  event to.
         *  @return True if event has been handled.
        **/
        /////////////////////////////////////////////////////////////
        bool sendEvent(EventLocalPtr e, const String& name);

        /////////////////////////////////////////////////////////////
        /** @brief Send an event using the Synchronous Event System.
         *
         *  @param e : Event to send. If the event is null, nothing is
         *  done in this function.
         *  @param listener : Id of the listener to send. It must
         *  correspond to an entry in the registered listeners list.
         *  @return True if event has been handled.
        **/
        /////////////////////////////////////////////////////////////
        bool sendEvent(EventLocalPtr e, const Id& listener);

        /////////////////////////////////////////////////////////////
        /** @brief Send an event using the Asynchronous Event System.
         *
         *  Every listeners registered in this Emitter will receive the
         *  event. The pointer is duplicated with different receiver
         *  (listener) in the Uniter Queue.
         *
         *  @param e : Event to send. If the event is null, nothing is
         *  done in this function.
         *  @param event_uniter : Event uniter to send the event to. If
         *  null, the global Event Uniter is used.
        **/
        /////////////////////////////////////////////////////////////
        void sendASynchronousEvent(EventLocalPtr e, EventUniter* event_uniter = nullptr);

        /////////////////////////////////////////////////////////////
        /** @brief Send an event using the Asynchronous Event System.
         *
         *  The event will be send using the Uniter to the given
         *  listener.
         *
         *  @param e : Event to send. If the event is null, nothing is
         *  done in this function.
         *  @param listener : Listener to send the event to.
         *  @param event_uniter : Event uniter to send the event to. If
         *  null, the global Event Uniter is used.
        **/
        /////////////////////////////////////////////////////////////
        void sendAsynchronousEvent(EventLocalPtr e, EventListenerPtr& listener, EventUniter* event_uniter = nullptr);

        /////////////////////////////////////////////////////////////
        /** @brief Send an event using the Asynchronous Event System.
         *
         *  The event will be send using the Uniter to the given
         *  listener.
         *
         *  @param e : Event to send. If the event is null, nothing is
         *  done in this function.
         *  @param name : Listener to send the event to.
         *  @param event_uniter : Event uniter to send the event to. If
         *  null, the global Event Uniter is used.
        **/
        /////////////////////////////////////////////////////////////
        void sendAsynchronousEvent(EventLocalPtr e, const String& name, EventUniter* event_uniter = nullptr);

        /////////////////////////////////////////////////////////////
        /** @brief Send an event using the Asynchronous Event System.
         *
         *  The event will be send using the Uniter to the given
         *  listener.
         *
         *  @param e : Event to send. If the event is null, nothing is
         *  done in this function.
         *  @param listener : Listener to send the event to.
         *  @param event_uniter : Event uniter to send the event to. If
         *  null, the global Event Uniter is used.
        **/
        /////////////////////////////////////////////////////////////
        void sendAsynchronousEvent(EventLocalPtr e, const Id& listener, EventUniter* event_uniter = nullptr);


    protected:

        /////////////////////////////////////////////////////////////
        /** @brief Document an event.
         *
         *  Use this function to give a description to a specific event
         *  handled by this emitter.
         *
         *  @param event : Type of the event to document.
         *  @param description : Documentation of the event.
        **/
        /////////////////////////////////////////////////////////////
        void documentEvent(const HashType& event, const String& description);

    public:

        /////////////////////////////////////////////////////////////
        /** @brief Return a String containing every events with their
         *  description.
         *  @deprecated
         *  @note Due to HashType in events name, this function no more
         *  returns Events name. See class documentation for events
         *  emitting.
        **/
        /////////////////////////////////////////////////////////////
        String documentation() const;

        /////////////////////////////////////////////////////////////
        /** @brief Return the documentation for one event.
        **/
        /////////////////////////////////////////////////////////////
        const String& getEventDocumentation(const HashType& event) const;

        /////////////////////////////////////////////////////////////
        /** @brief Tell if an event is documented.
         *
         *  @see isEventHandled , wich is equivalent.
        **/
        /////////////////////////////////////////////////////////////
        bool isEventDocumented(const HashType& event) const;

        /////////////////////////////////////////////////////////////
        /** @brief Tell if event is handled.
         *
         *  @see isEventDocumented , wich is equivalent.
        **/
        /////////////////////////////////////////////////////////////
        bool isEventHandled(const HashType& event) const;

    public:
    	
    	/////////////////////////////////////////////////////////////
        /** @brief Register a new listener to this emitter.
         *
         *  @param nlistener : Listener to register aand create. If the 
         *  listener name is already present, -1 is returned.
         *  @return The Pointer to the created Listener.
        **/
        /////////////////////////////////////////////////////////////
        EventListenerPtr registerListener(const String& nlistener);

        /////////////////////////////////////////////////////////////
        /** @brief Register a new listener to this emitter.
         *
         *  @param listener : Listener to register. If the listener
         *  name is already present, -1 is returned.
         *  @return Negativ if error, superior or equal to 0 otherweise.
         *  The exact value when success is the index of the registered
         *  listener in the list in this emitter.
        **/
        /////////////////////////////////////////////////////////////
        int registerListener(const EventListenerPtr& listener);
        
        /////////////////////////////////////////////////////////////
        /** @brief Register a new listener to this emitter, preparing it
         *  for specific event sending.
         *
         *  @param nlistener : Listener to register. If the listener
         *  name is already present, -1 is returned.
         *  @param elist : The given Listener will receive, from this emitter,
         *  only the Events Types given in the list.
         *
         *  @return The Pointer to the created Listener.
        **/
        /////////////////////////////////////////////////////////////
        EventListenerPtr registerListener(const String& nlistener, std::initializer_list<HashType> elist);
        
        /////////////////////////////////////////////////////////////
        /** @brief Register a new listener to this emitter, preparing it
         *  for specific event sending.
         *
         *  @param listener : Listener to register. If the listener
         *  name is already present, -1 is returned.
         *  @param elist : The given Listener will receive, from this emitter,
         *  only the Events Types given in the list.
         *
         *  @return The index in the internal list.
        **/
        /////////////////////////////////////////////////////////////
        int registerListener(const EventListenerPtr& listener, std::initializer_list<HashType> elist);

        /////////////////////////////////////////////////////////////
        /** @brief Unregister listener.
         *
         *  @param name : Name of the registered listener to remove.
         *  @return The old index in the list of the removed listener.
         *  If value is -1, an error occured, else value is superior
         *  or equal to 0.
        **/
        /////////////////////////////////////////////////////////////
        int unregisterListener(const String& name);

        /////////////////////////////////////////////////////////////
        /** @brief Unregister listener.
         *
         *  @param id : id of the registered listener to remove.
         *  @return The old index in the list of the removed listener.
         *  If value is -1, an error occured, else value is superior
         *  or equal to 0.
        **/
        /////////////////////////////////////////////////////////////
        int unregisterListener(const Id& id);

        /////////////////////////////////////////////////////////////
        /** @brief Return listener from his name, registered in this
         *  emitter.
         *  @note Only the first encountered listener with given name
         *  is returned. If you have many listeners with same name
         *  registered, please use the id method instead.
        **/
        /////////////////////////////////////////////////////////////
        const EventListenerPtr& getListener(const String& name) const;

        /////////////////////////////////////////////////////////////
        /** @brief Return listener from his name, registered in this
         *  emitter.
         *
         *  @note Only the first encountered listener with given name
         *  is returned. If you have many listeners with same name
         *  registered, please use the id method instead.
        **/
        /////////////////////////////////////////////////////////////
        EventListenerPtr& getListener(const String& name);

        /////////////////////////////////////////////////////////////
        /** @brief Return listener from his id, registered in this
         *  emitter.
        **/
        /////////////////////////////////////////////////////////////
        const EventListenerPtr& getListener(const Id& identifier) const;

        /////////////////////////////////////////////////////////////
        /** @brief Return listener from his id, registered in this
         *  emitter.
        **/
        /////////////////////////////////////////////////////////////
        EventListenerPtr& getListener(const Id& identifier);

    protected:

        /////////////////////////////////////////////////////////////
        /** @brief Create an event recognized by his hash type.
         *
         *  It creates an event and fill every needed informations. By
         *  default, this function return a NullEvent because no event
         *  are handled.
        **/
        /////////////////////////////////////////////////////////////
        virtual EventLocalPtr createEvent(const HashType& e_type) const;

    public:

        /////////////////////////////////////////////////////////////
        /** @brief Change the EmitPolicy to given one.
        **/
        /////////////////////////////////////////////////////////////
        void setEmitPolicy(EmitPolicy ep);
    };

    typedef AutoPointer<EventEmitter> EventEmitterPtr;///< AutoPointer to EventEmitter. No need to overload the destruction.
}

#endif
