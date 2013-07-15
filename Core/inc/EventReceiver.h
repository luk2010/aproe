/** @file EventReceiver.h
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 11/09/2012
 *
 *  @addtogroup Global
 *  @addtogroup System
 *
 *  This file defines the EventReceiver class.
 *
**/
#ifndef APRORECEIVER_H
#define APRORECEIVER_H

#include "Event.h"
#include "EventListener.h"

namespace APro
{
    class APRO_DLL EventReceiver
    {
        APRO_DECLARE_SHAREDPOINTER_CLASS_TYPEDEF(EventReceiver)

    public:

        EventReceiver();

        virtual ~EventReceiver();

    public:

        void addEventProcessed(const String& e);
        void removeEventProcessed(const String& e);
        void clearEvents();

        void addListener(const EventListener::ptr& listener);

        EventListener::ptr getListener(const String& name);
        const EventListener::ptr getListener(const String& name) const;

        void removeListener(const String& name);
        void clearListeners();

    public:

        void processEvents();

    protected:

        virtual void processEvent(const Event::ptr&);

    private:

        List<String> eventProcessed;
        List<EventListener::ptr> listeners;
    };
}

#endif
