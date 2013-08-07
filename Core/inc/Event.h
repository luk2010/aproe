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
#include <ParametedObject.h>
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
     *  registered to him. More, it can create custom listeners. 
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
     *  An event is a structure with a String type descriptor, an
     *  id, an emitter object (the one wich send the event) and
     *  the target.
     *
     *  The event structure can have more fields, but this isn't 
     *  documented as the event is a ParametedObject subclass, you
     *  should use ParametedObject::listParameters to get descriptions.
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
     *  An event is a structure with a String type descriptor, an
     *  id, an emitter object (the one wich send the event) and
     *  the target.
     *
     *  The event structure can have more fields, but this isn't 
     *  documented as the event is a ParametedObject subclass, you
     *  should use ParametedObject::listParameters to get descriptions.
     *
     *  @note The event id correspond to a static incremented 
     *  number.
    **/
    /////////////////////////////////////////////////////////////
    class APRO_DLL Event : public ParametedObject,
                           public NonCopyable
    {
        APRO_DECLARE_SHAREDPOINTER_CLASS_TYPEDEF(Event)
        
    private:
        
        EventEmitter*  m_emitter;///< Emitter of this event.
        EventListener* m_target;///< Target of this event.
        
        String         m_type;///< Type description.
        unsigned long  m_id;///< Id of the event.

    public:

        /////////////////////////////////////////////////////////////
        /** @brief Constructor.
         *
         *  As you must provide a non-null emitter, target is not 
         *  required. Id is setted by the incrementation.
        **/
        /////////////////////////////////////////////////////////////
        Event(const String& type, EventEmitter* _emitter, EventListener* _target = nullptr);
        
        /////////////////////////////////////////////////////////////
        /** @brief Destructor. 
        **/
        /////////////////////////////////////////////////////////////
        ~Event();
        
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
        /** @brief Return the type of this event.
        **/
        /////////////////////////////////////////////////////////////
        const String& type() const;
        
        /////////////////////////////////////////////////////////////
        /** @brief Return the id of this event.
         **/
        /////////////////////////////////////////////////////////////
        const unsigned long & id() const;
        
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
        
    };
    
    typedef AutoPointer<Event> EventPtr;///< An AutoPointer to Events.
}

#endif
