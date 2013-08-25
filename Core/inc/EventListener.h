/////////////////////////////////////////////////////////////
/** @file EventListener.h
 *  @ingroup Events
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 11/09/2012
 *
 *  Defines the EventListener class.
 *
**/
/////////////////////////////////////////////////////////////
#ifndef APROEVENTLISTENER_H
#define APROEVENTLISTENER_H

#include "Event.h"
#include "List.h"
#include "SharedPointer.h"
#include "ParametedObject.h"

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
    **/
    /////////////////////////////////////////////////////////////
    class APRO_DLL EventListener
    {
        APRO_DECLARE_SHAREDPOINTER_CLASS_TYPEDEF(EventListener)

    protected:

        String      m_name;    ///< Name of the listener.
        Id          id;        ///< Id of this listener.
        EventPtr    last_event;///< Last event received by this listener.

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
        /** @brief Constructor by copy.
         *
         *  @note A new id is generated in this function.
        **/
        /////////////////////////////////////////////////////////////
        EventListener(const EventListener& other);

    public:

        /////////////////////////////////////////////////////////////
        /** @brief Receive an event, store it as last received and
         *  handle it.
         *  @param event : Event to receive.
         *  @return true if event has been corectly used.
         *
         *  The event is correctly used only if the ::handle() function
         *  return true. So the last event will be stored, but if
         *  ::handle() return false the event won't be stored.
        **/
        /////////////////////////////////////////////////////////////
        bool receive(const EventPtr& event);

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
        virtual bool handle(const EventPtr& event) { return false; }

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
        const EventPtr& getLastEventReceived() const;

        /////////////////////////////////////////////////////////////
        /** @brief Return the id of this listener.
        **/
        /////////////////////////////////////////////////////////////
        const unsigned long& getId() const;

    };

    typedef AutoPointer<EventListener> EventListenerPtr;///< AutoPointerof EventListener. No custom destruction needed, so simple typedef used.
}

#endif
