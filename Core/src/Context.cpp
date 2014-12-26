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
#include "RenderingAPI.h"

namespace APro
{
    APRO_REGISTER_EVENT_NOCONTENT(ContextBindedEvent);
    APRO_REGISTER_EVENT_NOCONTENT(ContextUnbindedEvent);

    Context::Context(Window* associatedWindow, RenderingAPI* renderingAPI)
        : EventEmitter()
    {
        aproassert1(associatedWindow != nullptr);
        aproassert1(renderingAPI != nullptr);

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
        aproassert1(m_renderingapi != nullptr);
        aproassert1(m_loaded == true);

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
        aproassert1(m_renderingapi != nullptr);
        aproassert1(m_loaded == true);

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
                m_viewports.push_back(viewport);
                aprodebug("Added Viewport \"") << viewport->getName() << "\" to viewports list.";
            }
            else
            {
                Console::Get() << "\n[Context]{addViewport} Can't add Viewport \"" << viewport->getName() << "\" to list because another one exists.";
            }
        }
    }

    void Context::removeViewPort(const String& name)
    {
        Array<ViewPortPtr>::iterator it = getViewPortIterator(name);
        if(it == m_viewports.end() || (*it).isNull())
        {
            Console::Get() << "\n[Context]{removeViewPort} Can't find ViewPort \"" << name << "\".";
            return;
        }
        m_viewports.erase(it);
    }

    const ViewPortPtr& Context::getViewPort(const String& name) const
    {
        if(name.isEmpty())
            return ViewPortPtr::Null;

        Array<ViewPortPtr>::const_iterator e = m_viewports.end();
        for(Array<ViewPortPtr>::const_iterator it = m_viewports.begin(); it != e; it++)
        {
            if(!(*it).isNull() &&
               (*it)->getName() == name)
                return (*it);
        }

        return ViewPortPtr::Null;
    }

    ViewPortPtr& Context::getViewPort(const String & name)
    {
        if(name.isEmpty())
            return ViewPortPtr::Null;

        Array<ViewPortPtr>::const_iterator e = m_viewports.end();
        for(Array<ViewPortPtr>::iterator it = m_viewports.begin(); it != e; it++)
        {
            if(!(*it).isNull() &&
               (*it)->getName() == name)
                return (*it);
        }

        return ViewPortPtr::Null;
    }

    const ViewPortPtr& Context::getDefaultViewPort() const
    {
        return *m_viewports.begin();
    }

    Array<ViewPortPtr>::const_iterator Context::getViewPortIterator(const String& name) const
    {
        if(name.isEmpty())
            return m_viewports.end();

        Array<ViewPortPtr>::const_iterator e = m_viewports.end();
        for(Array<ViewPortPtr>::const_iterator it = m_viewports.begin(); it != e; it++)
        {
            if(!(*it).isNull() &&
               (*it)->getName() == name)
                return it;
        }

        return m_viewports.end();
    }

    Array<ViewPortPtr>::iterator Context::getViewPortIterator(const String& name)
    {
        if(name.isEmpty())
            return m_viewports.end();

        Array<ViewPortPtr>::const_iterator e = m_viewports.end();
        for(Array<ViewPortPtr>::iterator it = m_viewports.begin(); it != e; it++)
        {
            if(!(*it).isNull() &&
               (*it)->getName() == name)
                return it;
        }

        return m_viewports.end();
    }

    bool Context::hasViewPort(const String& name) const
    {
        return getViewPortIterator(name) != m_viewports.end();
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
        return m_viewports.size();
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

        Rectangle zone(0, 0, width, height);
        (*m_viewports.begin())->setZone(zone);

        for(size_t i = 0; i < m_viewports.size(); ++i)
        {
            ViewPortPtr& viewport = m_viewports.at(i);
            Rectangle& zonev = viewport->getZone();

            Intersection result = zone.intersects(zonev);

            if(result == INTBETWEEN)
            {
                viewport->setCurrentZone(Rectangle(Numeric::Min(zone.getLeft(),   zonev.getLeft()),
                                                   Numeric::Min(zone.getTop(),    zonev.getTop()),
                                                   Numeric::Min(zone.getWidth(),  zonev.getWidth()),
                                                   Numeric::Min(zone.getHeight(), zonev.getHeight())));
                viewport->setVisible(true);
            }
            else if(result == INTOUT)
            {
                viewport->setCurrentZone(Rectangle(0,0,0,0));
                viewport->setVisible(false);
            }
            else
            {
                viewport->setCurrentZone(zonev);
                viewport->setVisible(true);
            }
        }
    }

    EventPtr Context::createEvent(const HashType& e_type) const
    {
        if(e_type == ContextBindedEvent::Hash) {
            EventPtr ret = (Event*) AProNew(ContextBindedEvent);
            ret->m_emitter = this;
            return ret;
        }

        else if(e_type == ContextUnbindedEvent::Hash) {
            EventPtr ret = (Event*) AProNew(ContextUnbindedEvent);
            ret->m_emitter = this;
            return ret;
        }

        else
            return EventEmitter::createEvent(e_type);
    }
}
