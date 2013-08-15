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
     *  @see Events for more explanation about the event system.
    **/
    /////////////////////////////////////////////////////////////
    class APRO_DLL EventEmitter
    {
    protected:
        
        typedef Map<String, String> EventsList;///< List of events type, with documentation.
        
        List<EventListenerPtr>       listeners;///< List of AutoPointer to listeners.
        EventsList                  events;///< List of events type with documentation, handled correctly by this emitter.
        
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
         *  @param e : Event to send. If null, nothing is done in this
         *  function.
         *  @param listener : Listener to send the event to. If null, 
         *  the emitter will send it to every listener registered.
         *  @return A value superior or equal to 0, corresponding to 
         *  the number of listeners that have handled this event.
        **/
        /////////////////////////////////////////////////////////////
        unsigned int sendEvent(const EventPtr& e, EventListenerPtr& listener = nullptr);
        
        /////////////////////////////////////////////////////////////
        /** @brief Send an event using the Synchronous Event System.
         *  
         *  @param e : Event to send. If the event is null, nothing is 
         *  done in this function.
         *  @param name : Name of the registered listener to send the
         *  event to. You can set this name to "__all" if you want to 
         *  send it to every listeners. 
         *  @return A value superior or equal to 0, corresponding to 
         *  the number of listeners that have handled this event.
        **/
        /////////////////////////////////////////////////////////////
        unsigned int sendEvent(const EventPtr& e, const String& name);
        
        /////////////////////////////////////////////////////////////
        /** @brief Send an event using the Synchronous Event System.
         *  
         *  @param e : Event to send. If the event is null, nothing is 
         *  done in this function.
         *  @param listener : Id of the listener to send. It must 
         *  correspond to an entry in the registered listeners list.
         *  @return A value superior or equal to 0, corresponding to 
         *  the number of listeners that have handled this event.
        **/
        /////////////////////////////////////////////////////////////
        unsigned int sendEvent(const EventPtr& e, const Id& listener);
        
        /////////////////////////////////////////////////////////////
        /** @brief Send an event using the Asynchronous Event System.
         *  
         *  @param e : Event to send. If the event is null, nothing is 
         *  done in this function.
         *  @param event_uniter : Event uniter to send the event to. If
         *  null, the global Event Uniter is used. 
         *  @return 0 if the uniter didn't handle the event, 1 otherweise.
        **/
        /////////////////////////////////////////////////////////////
        unsigned int sendASynchronousEvent(const EventPtr& e, EventUniter* event_uniter = nullptr);
        

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
        void documentEvent(const String& event, const String& description);

    public:
        
        /////////////////////////////////////////////////////////////
        /** @brief Return a String containing every events with their
         *  description.
        **/
        /////////////////////////////////////////////////////////////
        String documentation() const;
        
        /////////////////////////////////////////////////////////////
        /** @brief Return the documentation for one event.
        **/
        /////////////////////////////////////////////////////////////
        const String getEventDocumentation(const String& event) const;
        
        /////////////////////////////////////////////////////////////
        /** @brief Tell if an event is documented.
         *
         *  @see isEventHandled , wich is equivalent.
        **/
        /////////////////////////////////////////////////////////////
        bool isEventDocumented(const String& event) const;
        
        /////////////////////////////////////////////////////////////
        /** @brief Tell if event is handled.
         *
         *  @see isEventDocumented , wich is equivalent.
        **/
        /////////////////////////////////////////////////////////////
        bool isEventHandled(const String& event) const;

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

    public:

        /////////////////////////////////////////////////////////////
        /** @brief Create an event and populate it with correct 
         *  data.
         *
         *  @param event_type : Type of the event to create. You should
         *  set it to a natively handled event by this emitter.
         *  @param set_target : Set to true if you want to set the target
         *  field of the event. @see Event for more.
         *  @param target : Target of the event.
         *
         *  @return A pointer to the created event.
         *
         *  This function also call a virtual custom populating function
         *  that helps the emitter to set correct data into the event.
         *  You can overload it in subclasses.
         *  @see ::populateEvent
        **/
        /////////////////////////////////////////////////////////////
        EventPtr createAndPopulateEvent(const String& event_type, bool set_target = false, EventListenerPtr& target = nullptr) const;
        
        /////////////////////////////////////////////////////////////
        /** @brief Populate an event from his type.
         *
         *  If the type of the event is handled, the emitter will
         *  populate it with correct datas that will be interpreted
         *  by listeners and/or uniters.
         *
         *  @param event : Event to populate.
        **/
        /////////////////////////////////////////////////////////////
        virtual void populateEvent(EventPtr& event) const { }
    };
    
    typedef AutoPointer<EventEmitter> EventEmitterPtr;///< AutoPointer to EventEmitter. No need to overload the destruction.
}

#endif
