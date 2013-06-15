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
#include "ViewPort.h"

namespace APro
{
    class Window;

    class APRO_DLL Context : public EventReceiver
    {
        APRO_DECLARE_SHAREDPOINTER_CLASS_TYPEDEF(Context)

    public:

        void processEvent(const SharedPointer<Event>& e);

    public:

        Context();

    private:
        Context(const Context& other);

    public:
        ~Context();

        void setWindow(Window* w);
        Window* getWindow();

        bool isLoaded() const;
        bool isBinded() const;

        void bind();
        void unbind();

        void reset();

    public:

        void addViewPort(const ViewPort::ptr& viewport);
        const ViewPort::ptr getViewPort(const String & name) const;
        ViewPort::ptr getViewPort(const String & name);
        void removeViewPort(const String& name);

        bool hasViewPorts() const;
        size_t getNumViewPorts() const;

        ViewPort::ptr getDefaultViewPort() const;
        ViewPort::ptr& getViewPort(size_t index);
        const ViewPort::ptr& getViewPort(size_t index) const;

    protected:

        void initDefaultViewPort();
        void updateViewPorts(const Event::ptr& e);

    protected:

        void setLoaded(bool l);
        void setBinded(bool b);

    protected:

        Window* window;
        bool loaded;
        bool binded;

        List<ViewPort::ptr> viewports;
    };
}

#endif
