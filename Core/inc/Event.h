/////////////////////////////////////////////////////////////
/** @file Event.h
 *  @ingroup Events
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 11/09/2012 - 27/12/2014
 *
 *  @brief
 *  Defines the Event class and the main Events documentation.
 *
 *  @copyright
 *  Atlanti's Project Engine
 *  Copyright (C) 2012 - 2014  Atlanti's Corp
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
#ifndef AROEVENT_H
#define AROEVENT_H

#include "Platform.h"
#include "SString.h"
#include "AutoPointer.h"

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
     *  Every emitter can create and register basic Listener, which 
     *  you can add callbacks. TThis is the "simple" method.
     *  @code
     *  EventListenerPtr myListener = myemitter->registerListener("MyListener", MyCustomEvent::Hash);
     *  myListener->addCallback(MyCustomEvent::Hash, [] (Event& e) { 
	 *  Console::get() << "\nHello !"; 
	 *  });
	 *  @endcode
	 *
	 *  You can also subclass the Listener to make your own handle() 
	 *  function. You then register it :
	 *  @code
	 *  CustomListenerPtr mylistener = CustomListener::New();
	 *  myemitter->registerListener(mylistener, MyCustomEvent::Hash);
	 *  @endcode
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
    class APRO_DLL Event : public Prototype
    {

    public:

		EventEmitter*  m_emitter;///< Emitter of this event. Might be null but should not.
        EventListener* m_target; ///< Target of this event. Might be null.
        bool           must_stop;///< Boolean to be set to true if listener does not want the event to continue his propagation.

    protected:
        HashType       m_type;   ///< Hash of event type. If 0, event is invalid.
        unsigned long  m_id;     ///< Id of the event.


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
         *  @warning There should always be an emitter, but if user
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
        
        /////////////////////////////////////////////////////////////
        /** @brief Clone this object.
         *  @note This function should be used only by a factory.
         *
         *  @return A new instance of this object.
        **/
        /////////////////////////////////////////////////////////////
        virtual Prototype* clone() const;
        
	public:
		
		/////////////////////////////////////////////////////////////
        /** @brief Returns the event with another type.
         * 
         *  Use this function depending on the ::type() return, you should
         *  test this value with your handled types to be sure Event is
         *  of correct type.
        **/
        /////////////////////////////////////////////////////////////
		template<typename T>
		T& to() { return *(dynamic_cast<T*>(this)); }
		
		/////////////////////////////////////////////////////////////
        /** @brief Returns the event with another type.
         * 
         *  Use this function depending on the ::type() return, you should
         *  test this value with your handled types to be sure Event is
         *  of correct type.
        **/
        /////////////////////////////////////////////////////////////
		template<typename T>
		const T& to() const { return *(dynamic_cast<const T*>(this)); }
    };

    typedef Event* EventRawPtr; ///< @brief A normal pointer to an Event.
    typedef AutoPointer<Event> EventPtr;///< @brief An AutoPointer to Events.
    typedef Event& EventRef; ///< @brief A reference to an event. Prefers this type instead of EventPtr.
    typedef Event  EventCopy; ///< @brief An explicit copy of an Event.
    
    class EventLocalPtr
    {
    	Event* ptr;
    	
	public:

    	EventLocalPtr() : ptr (nullptr) {}
    	
    	EventLocalPtr(const EventLocalPtr& rhs) : ptr (nullptr) { 
    		if(rhs.ptr)
				ptr = dynamic_cast<Event*>(rhs.ptr->clone()); 
		}
		
    	EventLocalPtr(EventLocalPtr&& rhs) : ptr (rhs.ptr) { 
    		rhs.ptr = nullptr; 
		}
    	
    	~EventLocalPtr() { 
    		if(ptr) 
				AProDelete(ptr); 
    	}
    	
    	Event& operator* () { return *ptr; }
    	const Event& operator* () const { return *ptr; }
    	
    	Event& operator-> () { return *ptr; }
    	const Event& operator-> () const { return *ptr; }
    	
    	bool operator == (Event* rhs) { return ptr == rhs; }
    };

/// @brief Declares a new event type with his hash.
/// @ingroup Events
/// You must use this function in a header file. See
/// APRO_REGISTER_EVENT_NOCONTENT for registering the event
/// in a source file.
///
/// @param name : Name of the event to declare.
#define APRO_DECLARE_EVENT_NOCONTENT(name) \
class APRO_DLL name : public Event \
{ public: name() { m_type = Hash; } ~name() {} static const HashType Hash; };

/// @brief Declares a new event type with his hash.
/// @ingroup Events
/// You must use this function in a header file. See
/// APRO_REGISTER_EVENT_CONTENT for registering the event
/// in a source file.
///
/// When creating an event with specific content, you should
/// overload the ::clone() method to clone your content 
/// to newly created event.
///
/// @code
/// Prototype* MyEvent::clone() const
/// { 
///    MyEvent* e = dynamic_cast<MyEvent*>(Event::clone());
///    [ Clone your data... ]
///    return (Prototype*) e;
/// }
/// @endcode
///
/// @param name : Name of the event to declare.
#define APRO_DECLARE_EVENT_CONTENT(name) \
class APRO_DLL name : public Event \
{ public: name() { m_type = Hash; } ~name() {} static const HashType Hash;

/// @brief Ends the APRO_DECLARE_EVENT_CONTENT macro.
#define APRO_DECLARE_EVENT_CONTENT_END() };

/// @brief Register a new event type hash.
/// @ingroup Events
/// You must use this function in a source file. See
/// APRO_DECLARE_EVENT_NOCONTENT for declaring the event
/// in a header file.
///
/// @param name : Name of the event to register.
#define APRO_REGISTER_EVENT_NOCONTENT(name) \
const HashType name::Hash = String::Hash( TOTEXT(name) );

/// @brief Register a new event type hash.
/// @ingroup Events
/// You must use this function in a source file. See
/// APRO_DECLARE_EVENT_CONTENT for declaring the event
/// in a header file.
///
/// @param name : Name of the event to register.
#define APRO_REGISTER_EVENT_CONTENT(name) \
const HashType name::Hash = String::Hash( TOTEXT(name) );

    APRO_DECLARE_EVENT_NOCONTENT(NullEvent)

}

#endif
