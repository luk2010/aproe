/** @file Context.cpp
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 19/09/2012
 *
 *  @addtogroup Global
 *  @addtogroup Rendering
 *
 *  This file defines the Context class.
 *
**/
#include "Context.h"
#include "Window.h"
#include "Console.h"

namespace APro
{
    void Context::processEvent(const SharedPointer<Event>& e)
    {
        if(isLoaded() && e->type() == String("WindowClosingEvent"))
        {
            setWindow(nullptr);
        }
    }

    Context::Context()
        : EventReceiver(), window(nullptr), loaded(false)
    {
        addEventProcessed(String("WindowClosingEvent"));
    }

    Context::Context(const Context & other)
        : EventReceiver(), window(nullptr), loaded(false)
    {
        addEventProcessed(String("WindowClosingEvent"));
    }

    Context::~Context()
    {

    }

    void Context::setWindow(Window* w)
    {
        if(window)
        {
            window->detachContext();
            window = nullptr;
        }

        if(w)
        {
            window->attachContext(this);
            window = w;
        }
    }

    Window* Context::getWindow()
    {
        return window;
    }

    bool Context::isLoaded() const
    {
        return loaded;
    }

    void Context::setLoaded(bool l)
    {
        loaded = l;
    }



    ContextFactory::ContextFactory()
        : Factory<Context>()
    {

    }

    ContextFactory::ContextFactory(const String& n)
        : Factory<Context>(n)
    {

    }

    ContextFactory::~ContextFactory()
    {

    }

    void ContextFactory::destroy(const SharedPointer<Context>& obj)
    {
        SharedPointer<Context>(obj)->release();
        unregisterObject(obj);
    }
}
