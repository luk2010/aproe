/** @file Event.h
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 11/09/2012
 *
 *  @addtogroup Global
 *  @addtogroup System
 *
 *  This file defines the Event class.
 *
**/
#ifndef AROEVENT_H
#define AROEVENT_H

#include "Platform.h"
#include "ParametedObject.h"
#include "SString.h"
#include "SharedPointer.h"

#include "Singleton.h"

namespace APro
{
    class APRO_DLL EventCounter : public Singleton<EventCounter>
    {
        APRO_DECLARE_SINGLETON(EventCounter)

    protected:

        EventCounter();
        ~EventCounter();

    public:

        void push();
        void pop();

    public:

        double count;
    };

    class APRO_DLL Event : public ParametedObject
    {
        APRO_DECLARE_SHAREDPOINTER_CLASS_TYPEDEF(Event)

    public:

        Event();
        Event(const String& type);
        Event(const Event& other);

        ~Event();

        const String & type() const;
    };
}

#endif
