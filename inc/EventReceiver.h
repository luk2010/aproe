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
    public:

        EventReceiver();

        virtual ~EventReceiver();

    public:

        void addEventProcessed(const String& e);
        void removeEventProcessed(const String& e);
        void clearEvents();

        void addListener(const SharedPointer<EventListener>& listener);
        SharedPointer<EventListener> getListener(const String& name);
        void removeListener(const String& name);
        void clearListeners();

        void processEvents();

    protected:

        virtual void processEvent(const SharedPointer<Event>& e);

    private:

        List<String> eventProcessed;
        List<SharedPointer<EventListener> > listeners;
    };
}

#endif
