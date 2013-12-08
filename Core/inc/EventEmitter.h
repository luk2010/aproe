/////////////////////////////////////////////////////////////
/** @file EventEmitter.h
 *  @ingroup Events
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 11/09/2012
 *
 *  Defines the EventEmitter class.
 *
**/
/////////////////////////////////////////////////////////////
#ifndef APROEVENTEMITTER_H
#define APROEVENTEMITTER_H

#include "Event.h"
#include "EventListener.h"

#include "List.h"

namespace APro
{
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
     *  asked.
     *  - EP_MANUAL : The emitter send the events to registered listeners,
     *  no threaded queue. This i the default behaviour.
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
    class APRO_DLL EventEmitter
    {
    protected:

        typedef Map<HashType, String>  EventsList;   ///< List of events type, with documentation.
        typedef List<EventListenerPtr> ListenersList;///< List of listeners pointer.

        enum EmitPolicy
        {
            EP_NONE,   ///< Events are send to no-one.
            EP_MANUAL, ///< Events are send to the registered listeners, directly.
            EP_UNITER  ///< Events are send to the global uniter.
        };

        ListenersList   listeners;///< List of AutoPointer to listeners.
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
        bool sendEvent(EventPtr& e);

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
        bool sendEvent(EventPtr& e, EventListenerPtr& listener);

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
        bool sendEvent(EventPtr& e, const String& name);

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
        bool sendEvent(EventPtr& e, const Id& listener);

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
        void sendASynchronousEvent(EventPtr& e, EventUniter* event_uniter = nullptr);

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
        void sendAsynchronousEvent(EventPtr& e, EventListenerPtr& listener, EventUniter* event_uniter = nullptr);

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
        void sendAsynchronousEvent(EventPtr& e, const String& name, EventUniter* event_uniter = nullptr);

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
        void sendAsynchronousEvent(EventPtr& e, const Id& listener, EventUniter* event_uniter = nullptr);


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
         *  @param listener : Listener to register. If the listener
         *  name is already present, -1 is returned.
         *  @return Negativ if error, superior or equal to 0 otherweise.
         *  The exact value when success is the index of the registered
         *  listener in the list in this emitter.
        **/
        /////////////////////////////////////////////////////////////
        int registerListener(const EventListenerPtr& listener);

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
        virtual EventPtr createEvent(const HashType& e_type) const;

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
