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
    class APRO_DLL EventEmitter
    {
    public:

        EventEmitter();
        EventEmitter(const EventEmitter& emitter);

        virtual ~EventEmitter();

        void sendEvent(const SharedPointer<Event>& e);
        void sendSpecificEvent(const SharedPointer<Event>& e, const String& name);
        void sendManualEvent(const SharedPointer<Event>& e, SharedPointer<EventListener>& listener);

    protected:

        List<SharedPointer<EventListener> > listeners;

    public:

        SharedPointer<EventListener> addListener(const String& name);
        SharedPointer<EventListener> getListener(const String& name);
        SharedPointer<EventListener> registerListener(const SharedPointer<EventListener> & listener);

        void removeListener(const String& name);

    public:

        virtual SharedPointer<EventListener> createListener(const String& name) const;
        virtual SharedPointer<Event> createEvent(const String& name) const;
    };
}

#endif
