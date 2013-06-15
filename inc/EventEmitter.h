/** @file EventEmitter.h
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 11/09/2012
 *
 *  @addtogroup Global
 *  @addtogroup System
 *
 *  This file defines the EventEmitter class.
 *
**/
#ifndef APROEVENTEMITTER_H
#define APROEVENTEMITTER_H

#include "Event.h"
#include "EventListener.h"

#include "List.h"

namespace APro
{
    /** @class EventEmitter
      * @brief Emit Events through the Normal Event Handling path. Events will be send to listeners registered
      * to this Emitter.<br />
      * This emitter can document every events he may be able to send, so the user will be able to show it using
      * the simple command explainEvents().
    **/
    class APRO_DLL EventEmitter
    {
    public:

        EventEmitter();
        EventEmitter(const EventEmitter& emitter);

        virtual ~EventEmitter();

        void sendEvent(const Event::ptr& e);
        void sendSpecificEvent(const Event::ptr& e, const String& name);
        void sendManualEvent(const Event::ptr& e, EventListener::ptr& listener);

    protected:

        void documentEvent(const String& event, const String& description);

    public:

        String explainEvents() const;
        const String getEventDocumentation(const String& event) const;
        bool isEventDocumented(const String& event) const;

    protected:

        typedef Map<String, String> EventsList;

        List<EventListener::ptr>    listeners;
        EventsList                  events;

    public:

        EventListener::ptr addListener(const String& name);
        EventListener::ptr getListener(const String& name);
        EventListener::ptr registerListener(const EventListener::ptr & listener);

        void removeListener(const String& name);

    public:

        virtual EventListener::ptr createListener(const String& name) const;
        virtual Event::ptr createEvent(const String& name) const;
    };
}

#endif
