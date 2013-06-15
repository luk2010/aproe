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
#include "Main.h"

namespace APro
{
    void Context::processEvent(const SharedPointer<Event>& e)
    {
        if(isLoaded() && e->type() == String("WindowClosingEvent"))
        {
            setWindow(nullptr);
        }

        if(e->type() == String("WindowResizedEvent") && isLoaded() && hasViewPorts())
        {
            updateViewPorts(e);
        }
    }

    Context::Context()
        : EventReceiver(), window(nullptr) /*, renderer(nullptr) */, loaded(false) /*, rendererLoaded(false) */
    {
        addEventProcessed(String("WindowClosingEvent"));
        addEventProcessed(String("WindowResizedEvent"));

        initDefaultViewPort();
    }

    Context::Context(const Context & /* other */)
        : EventReceiver(), window(nullptr) /*, renderer(nullptr) */, loaded(false) /*, rendererLoaded(false) */
    {
        addEventProcessed(String("WindowClosingEvent"));
        addEventProcessed(String("WindowResizedEvent"));

        initDefaultViewPort();
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
            setLoaded(true);
        }

        if(w)
        {
            w->attachContext(this);
            window = w;
            setLoaded(false);
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

    bool Context::isBinded() const
    {
        return binded;
    }

    void Context::setLoaded(bool l)
    {
        loaded = l;
    }

    void Context::setBinded(bool b)
    {
        binded = b;
    }

    void Context::reset()
    {

    }

    void Context::addViewPort(const ViewPort::ptr& viewport)
    {
        ViewPort::ptr v = getViewPort(viewport->getName());
        if(!v.isNull())
        {
            Main::get().getConsole() << "\n[Context] Can't add a viewport with name=" << viewport->getName()
            << " because it already exist in this context !";
            return;
        }
/*
        if(viewport->isPrioritary())
        {
            viewports.prepend(viewport);
        }
        else
*/
        {
            viewports.append(viewport);
        }
    }

    const ViewPort::ptr Context::getViewPort(const String & name) const
    {
        if(name.isEmpty()) return ViewPort::ptr();

        for(size_t i = 0; i < viewports.size(); ++i)
        {
            if(viewports.at(i)->getName() == name)
                return viewports.at(i);
        }

        return ViewPort::ptr();
    }

    ViewPort::ptr Context::getViewPort(const String & name)
    {
        if(name.isEmpty()) return ViewPort::ptr();

        for(size_t i = 0; i < viewports.size(); ++i)
        {
            if(viewports.at(i)->getName() == name)
                return viewports.at(i);
        }

        return ViewPort::ptr();
    }

    void Context::removeViewPort(const String& name)
    {
        ViewPort::ptr v = getViewPort(name);

        if(v.isNull())
        {
            Main::get().getConsole() << "\n[Context] Can't find context " << name << " to destroy it !";
            return;
        }

        size_t index = viewports.find(v);
        viewports.erase(index);
        v.release();
    }

    bool Context::hasViewPorts() const
    {
        return viewports.size() > 0;
    }

    ViewPort::ptr Context::getDefaultViewPort() const
    {
        return getViewPort(String("Default"));
    }

    void Context::updateViewPorts(const Event::ptr& e)
    {
        if(e->type() != String("WindowResizedEvent"))
        {
            return;
        }

        Pair<size_t, size_t> newsize = e->getParam(String("Size")).to<Pair<size_t, size_t> >();
        RectangleF zone(0, 0, newsize.first(), newsize.second());

        getDefaultViewPort()->setZone(zone);

        for(size_t i = 0; i < viewports.size(); ++i)
        {
            ViewPort::ptr& viewport = viewports.at(i);
            RectangleF& zonev = viewport->getZone();

            Intersection::_ result = zone.intersects(zonev);

            if(result == Intersection::Between)
            {
                viewport->setCurrentZone(RectangleF(min_2(zone.left(), zonev.left()),
                                                          min_2(zone.top(), zonev.top()),
                                                          min_2(zone.width(), zonev.width()),
                                                          min_2(zone.height(), zonev.height())));
                viewport->setVisible(true);
            }
            else if(result == Intersection::Out)
            {
                viewport->setCurrentZone(RectangleF(0,0,0,0));
                viewport->setVisible(false);
            }
            else
            {
                viewport->setCurrentZone(zonev);
                viewport->setVisible(true);
            }
        }
    }

    void Context::initDefaultViewPort()
    {
        ViewPort::ptr defaultv = AProNew(1, ViewPort) (String("Default"));
        defaultv->setVisible(true);

        addViewPort(defaultv);
        setLoaded(true);
    }

    size_t Context::getNumViewPorts() const
    {
        return viewports.size();
    }

    ViewPort::ptr& Context::getViewPort(size_t index)
    {
        return viewports.at(index);
    }

    const ViewPort::ptr& Context::getViewPort(size_t index) const
    {
        return viewports.at(index);
    }

    void Context::bind()
    {
        if(window)
        {
            window->context_bind();
            setBinded(true);
        }
    }

    void Context::unbind()
    {
        if(window && isBinded())
        {
            window->context_unbind();
            setBinded(false);
        }
    }
}
