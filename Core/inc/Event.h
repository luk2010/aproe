/////////////////////////////////////////////////////////////
/** @file Event.h
 *  @ingroup Events
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 11/09/2012
 *
 *  Defines the Event class and the main Events documentation.
 *
**/
/////////////////////////////////////////////////////////////
#ifndef AROEVENT_H
#define AROEVENT_H

#include <Platform.h>
#include <SString.h>
#include <AutoPointer.h>

namespace APro
{
    class EventListener;
    class EventEmitter;

    /////////////////////////////////////////////////////////////
    /**
     *  @defgroup Events Events System
     *  @addtogroup Events
     *
     *  The Event system is divised in many classes, and in some
     *  subsystems completly independant. You have two main systems :
     *
     *  - The Emitter / Listener system.
     *  - The Uniter / Listener system.
     *
     *  You can see that a Listener can always listen events, either
     *  from emitters or from Uniters.
     *
     *  In this system, this is the event that always have the data.
     *
     *  ### The listener
     *
     *  A listener is an object that have the possibility to handle
     *  a given event. @note The listener never destroy the event.
     *
     *  ### The emitter
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
     *  The emitter can send events only to listeners that are
     *  registered to him, or that you give the pointer.
     *
     *  ### The uniter
     *
     *  The Uniters / Listeners system is an asynchronous system
     *  where the Uniter send given events through a threaded loop.
     *  This loop will send the event to appropriate listener as if it
     *  was an emitter call.
     *
     *  The uniter is global, and can handle every event but it handles
     *  them one by one, using a first-in first-out queue.
     *
     *  If events have the maximum priority, the uniter will take
     *  them first.
     *
     *  @note If the events target is null, a warning is given to
     *  the output.
     *
     *  ### The events
     *
     *  An event is an object that have a creator (the emitter), an
     *  unique id and a type given by a Hash. It might also have a
     *  specific target (a listener) but it might not be the case.
     *
     *  You can (and you should !) subclass this class to create
     *  customs events.
     *
     *  If your event has no additional content, you may use
     *  the APRO_DECLARE_EVENT_NOCONTENT and APRO_REGISTER_EVENT_NOCONTENT
     *  macros making creation of simple events easier.
     *
     *  @note Some predefined events are given in the Engine. Every
     *  class with suffix "-Event" shall be Events subclass.
     *
     *  ### Global Process
     *
     *  The event emitter is the base.
     *
     *  Emitter detect send signal -> send to either uniter or
     *  listener.
     *
     *  If uniter -> asynchronous system that send to registered
     *  listeners or to specific listener if target is not null.
     *
     *  If listener -> synchronous system, direct handling of the
     *  event.
     *
    **/
    /////////////////////////////////////////////////////////////


    /////////////////////////////////////////////////////////////
    /** @class Event
     *  @ingroup Events
     *  @brief A structure that describe an event.
     *
     *  An event is an object that have a creator (the emitter), an
     *  unique id and a type given by a Hash. It might also have a
     *  specific target (a listener) but it might not be the case.
     *
     *  You can (and you should !) subclass this class to create
     *  customs events.
     *
     *  If your event has no additional content, you may use
     *  the APRO_DECLARE_EVENT_NOCONTENT and APRO_REGISTER_EVENT_NOCONTENT
     *  macros making creation of simple events easier.
     *
     *  @note The event id is given by the global IdGenerator.
    **/
    /////////////////////////////////////////////////////////////
    class APRO_DLL Event : public NonCopyable
    {
//        APRO_DECLARE_SHAREDPOINTER_CLASS_TYPEDEF(Event)

    public:

        EventEmitter*  m_emitter;///< Emitter of this event. Might be null but should not.
        EventListener* m_target; ///< Target of this event. Might be null.

    protected:
        HashType       m_type;    ///< Hash of event type. If 0, event is invalid.
        unsigned long  m_id;      ///< Id of the event.
        bool           must_stop; ///< Boolean to be set to true if listener does not want the event to continue his propagation.

    public:

        /////////////////////////////////////////////////////////////
        /** @brief Constructs an empty event.
        **/
        /////////////////////////////////////////////////////////////
        Event();

        /////////////////////////////////////////////////////////////
        /** @brief Destructor.
        **/
        /////////////////////////////////////////////////////////////
        virtual ~Event();

    public:

        /////////////////////////////////////////////////////////////
        /** @brief Return the emitter of this event.
         *
         *  @warning There shoudl always be an emitter, but if user
         *  send a faked event, you should use Event::hasEmitter to test
         *  it.
         *
         *  @throw NullPtrToReference
        **/
        /////////////////////////////////////////////////////////////
        EventEmitter& emitter();

        /////////////////////////////////////////////////////////////
        /** @brief Return the emitter of this event.
         *
         *  @warning There shoudl always be an emitter, but if user
         *  send a faked event, you should use Event::hasEmitter to test
         *  it.
         *
         *  @throw NullPtrToReference
        **/
        /////////////////////////////////////////////////////////////
        const EventEmitter& emitter() const;

        /////////////////////////////////////////////////////////////
        /** @brief Return the target of this event.
         *
         *  @warning If this function is used as there are not any
         *  target, you might see an exception throw. You should
         *  always test if there is one using Event::hasTarget.
         *
         *  @throw NullPtrToReference
        **/
        /////////////////////////////////////////////////////////////
        EventListener& target();

        /////////////////////////////////////////////////////////////
        /** @brief Return the target of this event.
         *
         *  @warning If this function is used as there are not any
         *  target, you might see an exception throw. You should
         *  always test if there is one using Event::hasTarget.
         *
         *  @throw NullPtrToReference
         **/
        /////////////////////////////////////////////////////////////
        const EventListener& target() const;

        /////////////////////////////////////////////////////////////
        /** @brief Return the hash type of this event.
        **/
        /////////////////////////////////////////////////////////////
        HashType type() const;

        /////////////////////////////////////////////////////////////
        /** @brief Return the id of this event.
        **/
        /////////////////////////////////////////////////////////////
        unsigned long id() const;

    public:

        /////////////////////////////////////////////////////////////
        /** @brief Return true if the emitter is non-null.
        **/
        /////////////////////////////////////////////////////////////
        bool hasEmitter() const;

        /////////////////////////////////////////////////////////////
        /** @brief Return true if the target is non-null.
        **/
        /////////////////////////////////////////////////////////////
        bool hasTarget() const;

        /////////////////////////////////////////////////////////////
        /** @brief Return true if this event is valid.
         *
         *  An event is valid only if the HashType is different from
         *  0.
        **/
        /////////////////////////////////////////////////////////////
        bool isValid() const;

        /////////////////////////////////////////////////////////////
        /** @brief Return true if this event correspond to the
         *  NullEvent.
         *
         *  The NullEvent correspond to no event. Do not treat this
         *  event.
        **/
        /////////////////////////////////////////////////////////////
        bool isNullEvent() const;

    public:

        /////////////////////////////////////////////////////////////
        /** @brief Stop the propagation of this event by setting 'must_stop'
         *  property to false.
        **/
        /////////////////////////////////////////////////////////////
        void mustStop();

    };

    typedef AutoPointer<Event> EventPtr;///< An AutoPointer to Events.

/// @brief Declares a new event type with his hash.
/// @ingroup Events
/// You must use this function in a header file. See
/// APRO_REGISTER_EVENT_NOCONTENT for registering the event
/// in a source file.
///
/// @param name : Name of the event to declare.
#define APRO_DECLARE_EVENT_NOCONTENT(name) \
class APRO_DLL name : public Event \
{ public: name() { m_type = Hash; } ~name() {} static HashType Hash; }

/// @brief Register a new event type hash.
/// @ingroup Events
/// You must use this function in a source file. See
/// APRO_DECLARE_EVENT_NOCONTENT for declaring the event
/// in a header file.
///
/// @param name : Name of the event to register.
#define APRO_REGISTER_EVENT_NOCONTENT(name) \
HashType name::Hash = String::Hash( TOTEXT(name) );

    APRO_DECLARE_EVENT_NOCONTENT(NullEvent)

}

#endif
