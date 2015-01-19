////////////////////////////////////////////////////////////
/** @file Window.cpp
 *  @ingroup Core
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 04/09/2012 - 19/01/2015
 *
 *  @brief
 *  Implements the Window class.
 *
 *  @copyright
 *  Atlanti's Project Engine
 *  Copyright (C) 2012 - 2015  Atlanti's Corp
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
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

    Window::Window(const String& windowname, size_t width, size_t height, bool fullscreen)
        : NonCopyable(), EventEmitter(), RenderingTarget()
    {
    	setName(windowname);
        m_title       = windowname;
        m_rect.width  = width;
        m_rect.height = height;
        m_rect.x      = 0;
        m_rect.y      = 0;
        m_fullscreen  = fullscreen;
        m_cursorShown = true;
        m_status      = StatusNull;

        documentEvent(WindowCreatedEvent::Hash,   "Window is created. There are no garantee that the window has been showed or drawned. This event is sended after \"create\" has been called.");
        documentEvent(WindowDestroyedEvent::Hash, "Window is destroyed. This event is sended after \"destroy\" has been called.");
        documentEvent(WindowMovedEvent::Hash,     "Window has been moved. Event field \"Position\" contains the new position of the window.");
        documentEvent(WindowSizedEvent::Hash,     "Window has been resized. Event field \"Size\" contains the new size of the window.");
        documentEvent(WindowClosingEvent::Hash,   "Window is closing.");
        documentEvent(WindowShowedEvent::Hash,    "Window is showed. There is no garantee that the function \"show\" is a success.");
        documentEvent(WindowHideEvent::Hash,      "Window is hidden. There is no garantee that the function \"hide\" is a success.");
    }

    Window::~Window()
    {
        destroy();
    }
    
    bool Window::create()
    {
    	if(m_status == StatusNull)
		{
			if(_create())
			{
				WindowManager::Get().registerWindow(getName(), this);
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return true;
		}
    }

    void Window::show()
    {
        if(m_status == StatusNull)
		{
			// Create the Window before showing it.
			if(create()) {
				// Call this function again.
				return show();
			}
		}
		else if(m_status == StatusShown)
		{
			return;
		}
		else
		{
			// Call the implementation specific function.
			_show();
		}
    }

    void Window::hide()
    {
    	if(m_status == StatusNull)
		{
			// Create the Window
			if(create()) {
				// Call this fuction again.
				return hide();
			}
		}
		else if(m_status == StatusShown)
		{
			// Call implementation specific function.
			_hide();
		}
		else
		{
			return;
		}
    }

    void Window::move(int x, int y, bool relativePos)
    {
    	if(m_status == StatusNull)
		{
			// Create the Window
			if(create()) {
				// Call this fuction again.
				return move(x,y,relativePos);
			}
		}
		else if(m_status == StatusShown && !m_fullscreen)
		{
			if(relativePos)
            {
                x = x + m_rect.x;
                y = y + m_rect.y;
            }
			_move(x, y);
		}
		else
		{
			return;
		}
    }

    void Window::resize(size_t width, size_t height)
    {
    	if(m_status == StatusNull)
		{
			// Create the Window
			if(create()) {
				// Call this fuction again.
				return resize(width, height);
			}
		}
		else if(m_status == StatusShown)
		{
			_resize(width, height);
		}
    	else
		{
			return;
		}
    }

    void Window::setTitle(const String& other)
    {
        if(m_status != StatusNull)
        {
            _setTitle(other);
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

    const String& Window::getTitle() const
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

    void Window::toggleCursor() const
    {
        if(m_status == StatusShown)
        {
            _showCursor(!m_cursorshown);
        }
    }

    ContextPtr Window::getContext()
    {
        return ContextPtr(m_context, nullptr, true, &m_context);
    }
    
    const ContextPtr Window::getContext() const
    {
        return ContextPtr(m_context, nullptr, true, &m_context);
    }

    void Window::destroy()
    {
        if(m_status != StatusNull)
        {
        	_destroy();
        	WindowManager::Get().unregisterWindow(getName());
        }
    }

    EventLocalPtr Window::createEvent(const HashType& e_type) const
    {
        switch (e_type)
        {
        case WindowCreatedEvent::Hash :
            EventLocalPtr ret = (Event*) AProNew(WindowCreatedEvent);
            ret->m_emitter = this;
            return ret;

        case WindowClosingEvent::Hash :
            EventLocalPtr ret = (Event*) AProNew(WindowClosingEvent);
            ret->m_emitter = this;
            return ret;

        case WindowDestroyedEvent::Hash :
            EventLocalPtr ret = (Event*) AProNew(WindowDestroyedEvent);
            ret->m_emitter = this;
            return ret;

        case WindowHideEvent::Hash :
            EventLocalPtr ret = (Event*) AProNew(WindowHideEvent);
            ret->m_emitter = this;
            return ret;

        case WindowMovedEvent::Hash :
            WindowMovedEvent* e = (WindowMovedEvent*) AProNew(WindowMovedEvent);
            e->new_x = m_rect.x;
            e->new_y = m_rect.y;
            e->m_emitter = this;
            return EventLocalPtr((Event*) e);

        case WindowShowedEvent::Hash :
            EventLocalPtr ret = (Event*) AProNew(WindowShowedEvent);
            ret->m_emitter = this;
            return ret;

        case WindowSizedEvent::Hash :
            WindowSizedEvent* e = (WindowSizedEvent*) AProNew(WindowSizedEvent);
            e->new_width = m_rect.width;
            e->new_height = m_rect.height;
            e->m_emitter = this;
            return EventLocalPtr((Event*) e);

        default:
            return EventEmitter::createEvent(e_type);
        }
    }
    
    void Window::sendWindowCreatedEvent()
    {
    	sendEvent(createEvent(WindowCreatedEvent::Hash));
    }
    
    void Window::sendWindowShowEvent()
    {
    	sendEvent(createEvent(WindowShowedEvent::Hash));
    }
    
    void Window::sendWindowHideEvent()
    {
    	sendEvent(createEvent(WindowHideEvent::Hash));
    }
    
    void Window::sendWindowMovedEvent()
    {
    	sendEvent(createEvent(WindowMovedEvent::Hash));
    }
    
    void Window::sendWindowResizedEvent()
    {
    	sendEvent(createEvent(WindowSizedEvent::Hash));
    }
    
    void Window::sendWindowClosingEvent()
    {
    	sendEvent(createEvent(WindowClosingEvent::Hash));
    }
    
    void Window::sendWindowDestroyedEvent()
    {
    	sendEvent(createEvent(WindowDestroyedEvent::Hash));
    }
}
