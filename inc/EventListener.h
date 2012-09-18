/** @file EventListener.h
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 11/09/2012
 *
 *  @addtogroup Global
 *  @addtogroup System
 *
 *  This file defines the EventListener class.
 *
**/
#ifndef APROEVENTLISTENER_H
#define APROEVENTLISTENER_H

#include "Event.h"
#include "List.h"
#include "SharedPointer.h"
#include "ParametedObject.h"

namespace APro
{
    class APRO_DLL EventListener : public ParametedObject
    {
    public:

        EventListener();
        EventListener(const String& n);

        virtual ~EventListener();

        virtual void receive(const SharedPointer<Event>& e);
        SharedPointer<Event> received(const String& name);

        void purge();

        const String& name() const;

    private:

        String mname;
        List<SharedPointer<Event> > receivedEvents;
    };
}

#endif
