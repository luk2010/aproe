/** @file Event.cpp
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
#include "Event.h"

namespace APro
{
    APRO_IMPLEMENT_SINGLETON(EventCounter)

    EventCounter::EventCounter()
    {

    }

    EventCounter::~EventCounter()
    {

    }

    void EventCounter::push()
    {
        count++;
    }

    void EventCounter::pop()
    {
        if(count > 0)
            count--;
    }

    Event::Event()
        : ParametedObject()
    {
        EventCounter::get().push();
        setParam(String("Type"), Variant(String("Null")), String("Type of this event."));
    }

    Event::Event(const String& mtype)
        : ParametedObject()
    {
        EventCounter::get().push();
        setParam(String("Type"), Variant(mtype), String("Type of this event."));
    }

    Event::Event(const Event& other)
        : ParametedObject(other)
    {
        EventCounter::get().push();
    }

    Event::~Event()
    {
        EventCounter::get().pop();
    }

    const String & Event::type() const
    {
        return getParam(String("Type")).to<String>();
    }
}
