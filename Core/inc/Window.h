////////////////////////////////////////////////////////////
/** @file Window.h
 *  @ingroup Core
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 03/09/2012 - 19/01/2015
 *
 *  Defines the Window class.
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
#ifndef APROWINDOW_H
#define APROWINDOW_H

#include "Platform.h"
#include "ThreadSafe.h"
#include "Implementable.h"
#include "EventEmitter.h"
#include "RenderingTarget.h"
#include "Context.h"

namespace APro
{
    typedef Id WindowId;
    class Context;

    ////////////////////////////////////////////////////////////
    /** @class Window
     *  @ingroup Core
     *  @brief A RenderingTarget represented by a Window.
     *
     *  The Window object is created by the RenderingAPI 
     *  implementation. 
    **/
    ////////////////////////////////////////////////////////////
    class APRO_DLL Window : 
    	public EventEmitter,
		public RenderingTarget
    {

    public:

        /** @brief Describes the current status of the Window object. */
        enum Status
        {
            StatusCreated,     ///< @brief Window is created but not shown yet.
            StatusShown,       ///< @brief Window is created and shown.
            StatusHidden,      ///< @brief Window is created but hidden (a call of 'hide()' after a 'show()').
            StatusNull         ///< @brief Default status : not created yet.
        };

        /** @brief Surface filled by the window, without borders. */
        struct Rect
        {
            size_t width; ///< @brief Width.
            size_t height;///< @brief Height.
            size_t x;     ///< @brief X coordinate. (from top)
            size_t y;     ///< @brief y coordinate. (from left)
        };

    protected:

        String                m_title;          ///< @brief Title showed on the Window Title bar.
        Rect                  m_rect;           ///< @brief Rectangle surface of the Window.
        ContextPtr            m_context;        ///< @brief Associated Context object.
        Status                m_status;         ///< @brief Current Window status.
        
        bool                  m_fullscreen;     ///< @brief Is the Window fullscreen mode ?
        bool                  m_cursorshown;    ///< @brief Is cursor shown ?

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Constructs a Window but do not show it on screen.
         *
         *  @param windowname : Name of this RenderingTarget. This is
         *  the default String set for m_title.
         *  @param width : Width of this Window.
         *  @param height : Height of this Window.
         *  @param fullscreen : Set true if window is fullscreen. If
         *  window is set to fullscreen, other Window object will not
         *  be activated while this one is activated.
        **/
        ////////////////////////////////////////////////////////////
        Window(const String& windowname, size_t width, size_t height, bool fullscreen);

        ////////////////////////////////////////////////////////////
        /** @brief Destructs the Window object.
        **/
        ////////////////////////////////////////////////////////////
        ~Window();

    public:
    	
    	////////////////////////////////////////////////////////////
        /** @brief Creates the Window, but do not show it.
        **/
        ////////////////////////////////////////////////////////////
    	bool create();

        ////////////////////////////////////////////////////////////
        /** @brief Show the Window object on screen.
         *
         *  @note 
         *  If this Window is fullscreen, it will hide other Window 
         *  objects.
        **/
        ////////////////////////////////////////////////////////////
        void show();

        ////////////////////////////////////////////////////////////
        /** @brief Hide the Window object if already showed.
        **/
        ////////////////////////////////////////////////////////////
        void hide();

        ////////////////////////////////////////////////////////////
        /** @brief Move the Window object to a new position on screen.
         *
         *  @note 
         *  On fullscreen mode, this doesn't take effect.
         * 
         *  @param relativePos : When set to true, new position is calculed
         *  as @code new_x = (old_x + x) @endcode and the same for y.
        **/
        ////////////////////////////////////////////////////////////
        void move(int x, int y, bool relativePos = false);

        ////////////////////////////////////////////////////////////
        /** @brief Resizes the Window object.
        **/
        ////////////////////////////////////////////////////////////
        void resize(size_t width, size_t height);

        ////////////////////////////////////////////////////////////
        /** @brief Set the title of this Window object.
        **/
        ////////////////////////////////////////////////////////////
        void setTitle(const String& other);

        ////////////////////////////////////////////////////////////
        /** @brief Returns true if fullscreen mode is on.
        **/
        ////////////////////////////////////////////////////////////
        bool isFullScreen() const;

        ////////////////////////////////////////////////////////////
        /** @brief Returns the current Status of this Window.
        **/
        ////////////////////////////////////////////////////////////
        Status getStatus() const;

        ////////////////////////////////////////////////////////////
        /** @brief Returns the current Title of this Window.
        **/
        ////////////////////////////////////////////////////////////
        const String& getTitle() const;

        ////////////////////////////////////////////////////////////
        /** @brief Returns the current Width of this Window.
        **/
        ////////////////////////////////////////////////////////////
        size_t getWidth() const;

        ////////////////////////////////////////////////////////////
        /** @brief Returns the current Height of this Window.
        **/
        ////////////////////////////////////////////////////////////
        size_t getHeight() const;

        ////////////////////////////////////////////////////////////
        /** @brief Returns the current X coordinate of this Window.
        **/
        ////////////////////////////////////////////////////////////
        size_t getX() const;

        ////////////////////////////////////////////////////////////
        /** @brief Returns the current Y coordinate of this Window.
        **/
        ////////////////////////////////////////////////////////////
        size_t getY() const;

        ////////////////////////////////////////////////////////////
        /** @brief Returns the current Rect structure of this Window.
        **/
        ////////////////////////////////////////////////////////////
        const Rect& getRect() const;

        ////////////////////////////////////////////////////////////
        /** @brief Update the Window object.
         *  @deprecated
        **/
        ////////////////////////////////////////////////////////////
        void update() {}

        ////////////////////////////////////////////////////////////
        /** @brief Toggle Cursor hiding in the Window.
         *  @note This doesn't disable Mouse move inside the Window.
        **/
        ////////////////////////////////////////////////////////////
        void toggleCursor() const;

    public:

		////////////////////////////////////////////////////////////
        /** @brief Returns, if exists, the Context associated with
         *  this Window.
        **/
        ////////////////////////////////////////////////////////////
        ContextPtr getContext();
        
        ////////////////////////////////////////////////////////////
        /** @brief Returns, if exists, the Context associated with
         *  this Window.
        **/
        ////////////////////////////////////////////////////////////
        const ContextPtr getContext() const;

    protected:

        ////////////////////////////////////////////////////////////
        /** @brief Destroy the Window object.
        **/
        ////////////////////////////////////////////////////////////
        void destroy();

    public:

        /////////////////////////////////////////////////////////////
        /** @brief Create an event recognized by his hash type.
         *
         *  It creates an event and fill every needed informations. By
         *  default, this function return a NullEvent because no event
         *  are handled.
        **/
        /////////////////////////////////////////////////////////////
        EventLocalPtr createEvent(const HashType& e_type) const;
        
	protected:
		
		/////////////////////////////////////////////////////////////
        /** @brief Implementation Specific create function.
         *  
         *  @note
         *  Should create the Window depending on parameters. If sucess, 
         *  this function should send a WindowCreated event using the 
		 *  helper Window::sendWindowCreatedEvent().
        **/
        /////////////////////////////////////////////////////////////
		virtual void _create() = 0;
		
		////////////////////////////////////////////////////////////
        /** @brief Helper to send WindowCreatedEvent.
        **/
        ////////////////////////////////////////////////////////////
		void sendWindowCreatedEvent();
		
		/////////////////////////////////////////////////////////////
        /** @brief Implementation Specific show function.
         *  
         *  @note
         *  Should draw the Window on the Screen. If sucess, this function
         *  should send a WindowShow event using the helper Window::sendWindowShowEvent().
        **/
        /////////////////////////////////////////////////////////////
		virtual void _show() = 0;
		
		////////////////////////////////////////////////////////////
        /** @brief Helper to send WindowShowEvent.
        **/
        ////////////////////////////////////////////////////////////
		void sendWindowShowEvent();
		
		/////////////////////////////////////////////////////////////
        /** @brief Implementation Specific hide function.
         *  
         *  @note
         *  Should hide the Window from the Screen. If sucess, this function
         *  should send a WindowHide event using the helper Window::sendWindowHideEvent().
        **/
        /////////////////////////////////////////////////////////////
		virtual void _hide() = 0;
		
		////////////////////////////////////////////////////////////
        /** @brief Helper to send WindowHideEvent.
        **/
        ////////////////////////////////////////////////////////////
		void sendWindowHideEvent();
		
		/////////////////////////////////////////////////////////////
        /** @brief Implementation Specific move function.
         *  
         *  @note
         *  Should move the Window on the Screen. If sucess, this function
         *  should send a WindowMoved event using the helper Window::sendWindowMovedEvent().
        **/
        /////////////////////////////////////////////////////////////
		virtual void _move(size_t x, size_t y) = 0;
		
		////////////////////////////////////////////////////////////
        /** @brief Helper to send WindowMovedEvent.
        **/
        ////////////////////////////////////////////////////////////
		void sendWindowMovedEvent();
		
		/////////////////////////////////////////////////////////////
        /** @brief Implementation Specific resize function.
         *  
         *  @note
         *  Should resize the Window on the Screen. If sucess, this function
         *  should send a WindowResized event using the helper Window::sendWindowResizedEvent().
         *  It should also take care of the Context object.
        **/
        /////////////////////////////////////////////////////////////
		virtual void _resize(size_t width, size_t height) = 0;
		
		////////////////////////////////////////////////////////////
        /** @brief Helper to send WindowMovedEvent.
        **/
        ////////////////////////////////////////////////////////////
		void sendWindowResizedEvent();
		
		/////////////////////////////////////////////////////////////
        /** @brief Implementation Specific setTitle function.
         *  
         *  @note
         *  Should set a new title to the title bar of this Window.
        **/
        /////////////////////////////////////////////////////////////
		virtual void _setTitle(const String& title) = 0;
		
		/////////////////////////////////////////////////////////////
        /** @brief Implementation Specific showCursor function.
         *  
         *  @note
         *  Should show or hide the cursor from the Window.
        **/
        /////////////////////////////////////////////////////////////
		virtual void _showCursor(bool cursorvisible) = 0;
		
		/////////////////////////////////////////////////////////////
        /** @brief Implementation Specific destroy function.
         *  
         *  @note
         *  Should close the Window and destroy every specific resources.
        **/
        /////////////////////////////////////////////////////////////
		virtual void _destroy() = 0;
		
		////////////////////////////////////////////////////////////
        /** @brief Helper to send WindowClosingEvent.
        **/
        ////////////////////////////////////////////////////////////
		void sendWindowClosingEvent();
		
		////////////////////////////////////////////////////////////
        /** @brief Helper to send WindowDestroyedEvent.
        **/
        ////////////////////////////////////////////////////////////
		void sendWindowDestroyedEvent();
    };

    typedef AutoPointer<Window> WindowPtr;

    APRO_DECLARE_EVENT_NOCONTENT(WindowCreatedEvent)
    APRO_DECLARE_EVENT_NOCONTENT(WindowDestroyedEvent)
    APRO_DECLARE_EVENT_NOCONTENT(WindowClosingEvent)
    APRO_DECLARE_EVENT_NOCONTENT(WindowShowedEvent)
    APRO_DECLARE_EVENT_NOCONTENT(WindowHideEvent)

    APRO_DECLARE_EVENT_CONTENT(WindowMovedEvent)
        size_t new_x;
        size_t new_y;
        
        Prototype* clone() const {
        	WindowMovedEvent* e = static_cast<WindowMovedEvent*>(Event::clone());
        	e->new_x = new_x;
        	e->new_y = new_y;
        	return e;
        }
    APRO_DECLARE_EVENT_CONTENT_END()

    APRO_DECLARE_EVENT_CONTENT(WindowSizedEvent)
        size_t new_width;
        size_t new_height;
        
        Prototype* clone() const {
        	WindowSizedEvent* e = static_cast<WindowSizedEvent*>(Event::clone());
        	e->new_width = new_width;
        	e->new_height = new_height;
        	return e;
        }
    APRO_DECLARE_EVENT_CONTENT_END()
}

#endif
