/** @file Context.h
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
#ifndef APROCONTEXT_H
#define APROCONTEXT_H

#include "EventReceiver.h"
#include "Factory.h"

namespace APro
{
    class Window;
    class ContextFactory;

    class APRO_DLL Context : public EventReceiver
    {
    protected:

        virtual void processEvent(const SharedPointer<Event>& e);

    public:

        Context();

    private:
        Context(const Context& other);

    public:
        virtual ~Context();

        void setWindow(Window* w);
        Window* getWindow();

        bool isLoaded() const;

        virtual void initialize() = 0;
        virtual void release() = 0;

    protected:

        void setLoaded(bool l);

    protected:

        Window* window;
        bool loaded;
    };

    class APRO_DLL ContextFactory : public Factory<Context>
    {
    public:

        ContextFactory();
        ContextFactory(const String& n);

        virtual ~ContextFactory();

        void destroy(const SharedPointer<Context>& obj);
    };

    typedef FactoryManager<ContextFactory> ContextFactoryManager;
}

#endif
