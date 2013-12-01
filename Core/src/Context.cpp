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
    APRO_REGISTER_EVENT_NOCONTENT(ContextBindedEvent);
    APRO_REGISTER_EVENT_NOCONTENT(ContextUnbindedEvent);

    Context::Context(Window* _window)
        : EventReceiver(), EventEmitter(), window(_window), loaded(false)
    {
        // Events Emitted
        documentEvent(ContextBindedEvent::Hash, String("Context is binded."));
        documentEvent(ContextUnbindedEvent::Hash, String("Context is unbinded."));

        // Events Listened
        addEventProcessed(WindowResizedEvent::Hash);

        initDefaultViewPort();

        if(!_window)
        {
            Console::get() << "\n[Context]{Constructor} Warning : Constructed context without window.";
        }
    }

    Context::~Context()
    {

    }

    Window* Context::getWindow()
    {
        return window;
    }

    const Window* Context::getWindow() const
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

    bool Context::bind()
    {
        if(window)
        {
            if(window->context_bind())
            {
                setBinded(true);
                sendEvent(createEvent(ContextBindedEvent::Hash));
                return true;
            }
            else
            {
                Console::get() << "\n[Context]{bind} Warning : Could not bind Context.";
                return false;
            }
        }
    }

    void Context::unbind()
    {
        if(window && isBinded())
        {
            if(window->context_unbind())
            {
                setBinded(false);
                sendEvent(createEvent(ContextUnbindedEvent::Hash));
                return true;
            }
            else
            {
                Console::get() << "\n[Context]{unbind} Warning : Could not unbind Context.";
                return false;
            }
        }
    }

    void Context::setLoaded(bool l)
    {
        loaded = l;
    }

    void Context::setBinded(bool b)
    {
        binded = b;
    }

    void Context::addViewPort(const ViewPortPtr& viewport)
    {
        if(!viewport.isNull())
        {
            if(!hasViewPort(viewport->getName()))
            {
                viewports.push_back(viewport);
                aprodebug("Added Viewport \"") << viewport->getName() << "\" to viewports list.";
            }
            else
            {
                Console::get() << "\n[Context]{addViewport} Can't add Viewport \"" << viewport->getName() << "\" to list because another one exists.";
            }
        }
    }

    void Context::removeViewPort(const String& name)
    {
        Array<ViewPortPtr>::iterator it = getViewPortIterator(name);
        if(it == viewports.end() || (*it).isNull())
        {
            Console::get() << "\n[Context]{removeViewPort} Can't find ViewPort \"" << name << "\".";
            return;
        }
        viewports.erase(it);
    }

    const ViewPortPtr Context::getViewPort(const String& name) const
    {
        if(name.isEmpty())
            return ViewPortPtr();

        Array<ViewPortPtr>::const_iterator e = viewports.end();
        for(Array<ViewPortPtr>::const_iterator it = viewports.begin(): it != e; it++)
        {
            if(!(*it).isNull() &&
               (*it)->getName() == name)
                return (*it);
        }

        return ViewPortPtr();
    }

    ViewPortPtr Context::getViewPort(const String & name)
    {
        if(name.isEmpty())
            return ViewPortPtr();

        Array<ViewPortPtr>::const_iterator e = viewports.end();
        for(Array<ViewPortPtr>::iterator it = viewports.begin(): it != e; it++)
        {
            if(!(*it).isNull() &&
               (*it)->getName() == name)
                return (*it);
        }

        return ViewPortPtr();
    }

    const ViewPortPtr Context::getDefaultViewPort() const
    {
        return getViewPort(String("Default"));
    }

    Array<ViewPortPtr>::const_iterator Context::getViewPortIterator(const String& name) const
    {
        if(name.isEmpty())
            return ViewPortPtr();

        Array<ViewPortPtr>::const_iterator e = viewports.end();
        for(Array<ViewPortPtr>::const_iterator it = viewports.begin(): it != e; it++)
        {
            if(!(*it).isNull() &&
               (*it)->getName() == name)
                return it;
        }

        return ViewPortPtr();
    }

    Array<ViewPortPtr>::iterator Context::getViewPortIterator(const String& name)
    {
        if(name.isEmpty())
            return ViewPortPtr();

        Array<ViewPortPtr>::const_iterator e = viewports.end();
        for(Array<ViewPortPtr>::iterator it = viewports.begin(): it != e; it++)
        {
            if(!(*it).isNull() &&
               (*it)->getName() == name)
                return it;
        }

        return ViewPortPtr();
    }

    bool Context::hasViewPort(const String& name) const
    {
        return getViewPortIterator(name) != viewports.end();
    }

    bool Context::hasViewPorts(const StringArray& names) const
    {
        if(names.isEmpty())
            return false;

        StringArray::const_iterator e = names.end();
        for(StringArray::const_iterator it = names.begin(); it != names.end(); it++)
        {
            if(!hasViewPort((*it)))
                return false;
        }

        return true;
    }

    size_t Context::getNumViewPorts() const
    {
        return viewports.size();
    }

    void Context::initDefaultViewPort()
    {
        ViewPortPtr defaultv = AProNew(ViewPort, String("Default"));
        defaultv->setVisible(true);

        addViewPort(defaultv);
        setLoaded(true);
    }

    void Context::updateViewPorts(WindowResizedEvent* e)
    {
        if(!isLoaded())
            return;

        Pair<size_t, size_t> newsize = e->getNewSize();
        RectangleF zone(0, 0, newsize.first(), newsize.second());

        getDefaultViewPort()->setZone(zone);

        for(size_t i = 0; i < viewports.size(); ++i)
        {
            ViewPortPtr& viewport = viewports.at(i);
            RectangleF& zonev = viewport->getZone();

            Intersection::_ result = zone.intersects(zonev);

            if(result == Intersection::Between)
            {
                viewport->setCurrentZone(RectangleF(Numeric::Min(zone.left(), zonev.left()),
                                                    Numeric::Min(zone.top(), zonev.top()),
                                                    Numeric::Min(zone.width(), zonev.width()),
                                                    Numeric::Min(zone.height(), zonev.height())));
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

    ViewPortPtr& Context::getViewPort(size_t index)
    {
        return viewports.at(index);
    }

    const ViewPortPtr& Context::getViewPort(size_t index) const
    {
        return viewports.at(index);
    }

    bool Context::handle(EventPtr& event)
    {
        if(event->type() == WindowResizedEvent::Hash)
        {
            updateViewPorts(event->reinterpret<WindowResizedEvent*>());
            return true;
        }
    }

    EventPtr Context::createEvent(const HashType& e_type) const
    {
        switch (e_type)
        {
        case ContextBindedEvent::Hash:
            EventPtr ret = (Event*) AProNew(ContextBindedEvent);
            ret->m_emitter = this;
            return ret;

        case ContextUnbindedEvent::Hash:
            EventPtr ret = (Event*) AProNew(ContextUnbindedEvent);
            ret->m_emitter = this;
            return ret;

        default:
            return EventEmitter::createEvent(e_type);
        }
    }
}
