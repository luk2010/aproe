////////////////////////////////////////////////////////////
/** @file Context.cpp
 *  @ingroup Rendering
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 19/09/2012 - 16/04/2014
 *
 *  Implements the Context class.
 *
**/
////////////////////////////////////////////////////////////
#include "Context.h"
#include "Window.h"

namespace APro
{
    APRO_REGISTER_EVENT_NOCONTENT(ContextBindedEvent);
    APRO_REGISTER_EVENT_NOCONTENT(ContextUnbindedEvent);

    Context::Context(Window* associatedWindow, RenderingAPI* renderingAPI)
        : EventEmitter()
    {
        aproassert(associatedWindow != nullptr);
        aproassert(renderingAPI != nullptr);

        m_window       = associatedWindow;
        m_renderingapi = renderingAPI;
        m_loaded       = false;
        m_binded       = false;
        m_viewports.reserve(2);// This is usefull if user wants to create a new viewport immediatly.

        // Events Emitted
        documentEvent(ContextBindedEvent::Hash, String("Context is binded."));
        documentEvent(ContextUnbindedEvent::Hash, String("Context is unbinded."));

        // We create the default Viewport.
        initDefaultViewPort();
    }

    Context::~Context()
    {
        // When the Context object is destroyed, we unbind it if binded and
        // we unregister it from the RenderingAPI.
        if(m_binded)
            unbind();
        m_renderingapi->unregisterContext(this);
    }

    Window* Context::getWindow()
    {
        return m_window;
    }

    RenderingAPI* Context::getRenderingAPI()
    {
        return m_renderingapi;
    }

    bool Context::isLoaded() const
    {
        return m_loaded;
    }

    bool Context::isBinded() const
    {
        return m_binded;
    }

    bool Context::bind()
    {
        aproassert(m_renderingapi != nullptr);
        aproassert(m_loaded == true);

        if(!m_binded)
        {
            m_binded = m_renderingapi->bindContext(this);
            if(m_binded)
                sendEvent(createEvent(ContextBindedEvent::Hash));
        }

        return m_binded;
    }

    bool Context::unbind()
    {
        aproassert(m_renderingapi != nullptr);
        aproassert(m_loaded == true);

        if(m_binded)
        {
            m_binded = m_renderingapi->unbindContext(this);
            if(!m_binded)
                sendEvent(createEvent(ContextUnbindedEvent::Hash));
        }

        return !m_binded;
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
        return *viewports.begin();
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
        m_loaded = true;
    }

    void Context::onWindowResized(size_t width, size_t height)
    {
        updateViewPorts(width, height);
    }

    void Context::updateViewPorts(size_t width, size_t height)
    {
        if(!m_loaded)
            return;

        RectangleF zone(0, 0, width, height);
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
