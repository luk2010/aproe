////////////////////////////////////////////////////////////
/** @file Window.cpp
 *  @ingroup Core
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 04/09/2012 - 16/04/2014
 *
 *  Implements the Window class.
 *
**/
////////////////////////////////////////////////////////////
#include "Window.h"
#include "Context.h"

namespace APro
{

    APRO_REGISTER_EVENT_NOCONTENT(WindowCreatedEvent)
    APRO_REGISTER_EVENT_NOCONTENT(WindowDestroyedEvent)
    APRO_REGISTER_EVENT_NOCONTENT(WindowClosingEvent)
    APRO_REGISTER_EVENT_NOCONTENT(WindowShowedEvent)
    APRO_REGISTER_EVENT_NOCONTENT(WindowHideEvent)

    APRO_REGISTER_EVENT_CONTENT(WindowMovedEvent)
    APRO_REGISTER_EVENT_CONTENT(WindowSizedEvent)

    Window::Window(const WindowId& id, const String& title, size_t width, size_t height, bool fullscreen)
        : EventEmitter(), ThreadSafe(), Implementable()
    {
        aproassert(id != 0, "Bad ID given for Window.");
        aproassert(createImplementation() == true, "Can't create implementation.");

        m_id          = id;
        m_title       = title;
        m_rect.width  = width;
        m_rect.height = height;
        m_rect.x      = 0;
        m_rect.y      = 0;
        m_fullscreen  = fullscreen;
        m_cursorShown = true;
        m_implementation = imp();
        m_status      = StatusNull;
        m_implementation->parent_window = this;

        documentEvent(WindowCreatedEvent::Hash,   "Window is created. There are no garantee that the window has been showed or drawned. This event is sended after \"create\" has been called.");
        documentEvent(WindowDestroyedEvent::Hash, "Window is destroyed. This event is sended after \"destroy\" has been called.");
        documentEvent(WindowMovedEvent::Hash,     "Window has been moved. Event field \"Position\" contains the new position of the window.");
        documentEvent(WindowSizedEvent::Hash,     "Window has been resized. Event field \"Size\" contains the new size of the window.");
        documentEvent(WindowClosingEvent::Hash,   "Window is closing.");
        documentEvent(WindowShowedEvent::Hash,    "Window is showed. There is no garantee that the function \"show\" is a success.");
        documentEvent(WindowHideEvent::Hash,      "Window is hidden. There is no garantee that the function \"hide\" is a success.");

        // Create the Window object
        if(!m_implementation->create(title, width, height, fullscreen))
        {
            aprodebug("Can't create Window object (title='") << title << "'.";
        }
        else
        {
            m_status = StatusCreated;
            sendEvent(createEvent(WindowCreatedEvent::Hash));
        }
    }

    Window::~Window()
    {
        destroy();
    }

    void Window::show()
    {
        APRO_THREADSAFE_AUTOLOCK

        if(m_status != StatusNull &&
           m_status != StatusShown)
        {
            if(m_implementation->show())
            {
                m_status = StatusShown;
                sendEvent(createEvent(WindowShowedEvent::Hash));
            }
        }
    }

    void Window::hide()
    {
        APRO_THREADSAFE_AUTOLOCK

        if(m_status == StatusShown)
        {
            if(m_implementation->hide())
            {
                m_status = StatusHidden;
                sendEvent(createEvent(WindowHideEvent::Hash));
            }
        }
    }

    void Window::move(int x, int y, bool relativePos)
    {
        if(m_status != StatusNull &&
           !m_fullscreen)
        {
            if(relativePos)
            {
                x = x + m_rect.x;
                y = y + m_rect.y;
            }
            m_implementation->move(x, y);
        }
    }

    void Window::_notifiate_window_moved(size_t new_x, size_t new_y)
    {
        m_rect.x = new_x;
        m_rect.y = new_y;
        sendEvent(createEvent(WindowMovedEvent::Hash));
    }

    void Window::resize(size_t width, size_t height)
    {
        if(m_status != StatusNull &&
           !m_fullscreen)
        {
            m_implementation->resize(width, height);
        }
    }

    void Window::_notifiate_window_resized(size_t new_width, size_t new_height)
    {
        m_rect.width = new_width;
        m_rect.height = new_height;
        if(m_context)
            m_context->onWindowResized(new_width, new_height);
        sendEvent(createEvent(WindowSizedEvent::Hash));
    }

    void Window::setTitle(const String& other)
    {
        if(m_status != StatusNull)
        {
            m_title = other;
            m_implementation->setTitle(other);
        }
    }

    bool Window::isFullScreen() const
    {
        return m_fullscreen;
    }

    Window::Status Window::getStatus() const
    {
        return m_status;
    }

    String Window::getTitle() const
    {
        return m_title;
    }

    size_t Window::getWidth() const
    {
        return m_rect.width;
    }

    size_t Window::getHeight() const
    {
        return m_rect.height;
    }

    size_t Window::getX() const
    {
        return m_rect.x;
    }

    size_t Window::getY() const
    {
        return m_rect.y;
    }

    const Window::Rect& Window::getRect() const
    {
        return m_rect;
    }

    void Window::update()
    {
        if(m_status != StatusNull)
        {
            m_implementation->update();
        }
    }

    void Window::toggleCursor() const
    {
        if(m_status != StatusNull)
        {
            m_implementation->showCursor(!m_cursorShown);
            m_cursorShown = !m_cursorShown;
        }
    }

    void Window::associateContext(Context* context)
    {
        if(m_status != StatusNull)
        {
            if(m_context)
                m_context.nullize();// This destroy the Context.

            m_context = context;
            m_context.setOwning(true);// Only the Window object can destroy this Context object.
        }
    }

    Context* Window::getAssociatedContext()
    {
        return m_context;
    }

    void Window::destroy()
    {
        if(m_status != StatusNull)
        {
            associateContext(nullptr);
            sendEvent(createEvent(WindowClosingEvent::Hash));
            m_implementation->destroy();
            sendEvent(createEvent(WindowDestroyedEvent::Hash));
            m_status = StatusNull;
        }
    }

    EventPtr Window::createEvent(const HashType& e_type) const
    {
        switch (e_type)
        {
        case WindowCreatedEvent::Hash :
            EventPtr ret = (Event*) AProNew(WindowCreatedEvent);
            ret->m_emitter = this;
            return ret;

        case WindowClosingEvent::Hash :
            EventPtr ret = (Event*) AProNew(WindowClosingEvent);
            ret->m_emitter = this;
            return ret;

        case WindowDestroyedEvent::Hash :
            EventPtr ret = (Event*) AProNew(WindowDestroyedEvent);
            ret->m_emitter = this;
            return ret;

        case WindowHideEvent::Hash :
            EventPtr ret = (Event*) AProNew(WindowHideEvent);
            ret->m_emitter = this;
            return ret;

        case WindowMovedEvent::Hash :
            WindowMovedEvent* e = (WindowMovedEvent*) AProNew(WindowMovedEvent);
            e->new_x = m_rect.x;
            e->new_y = m_rect.y;
            e->m_emitter = this;
            return EventPtr((Event*) e);

        case WindowShowedEvent::Hash :
            EventPtr ret = (Event*) AProNew(WindowShowedEvent);
            ret->m_emitter = this;
            return ret;

        case WindowSizedEvent::Hash :
            WindowSizedEvent* e = (WindowSizedEvent*) AProNew(WindowSizedEvent);
            e->new_width = m_rect.width;
            e->new_height = m_rect.height;
            e->m_emitter = this;
            return EventPtr((Event*) e);

        default:
            return EventEmitter::createEvent(e_type);
        }
    }
}
