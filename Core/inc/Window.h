////////////////////////////////////////////////////////////
/** @file Window.h
 *  @ingroup Core
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 03/09/2012 - 16/04/2014
 *
 *  Defines the Window class.
 *
**/
////////////////////////////////////////////////////////////
#ifndef APROWINDOW_H
#define APROWINDOW_H

#include "Platform.h"
#include "ThreadSafe.h"
#include "Implementable.h"
#include "WindowImplementation.h"
#include "EventEmitter.h"

namespace APro
{
    typedef Id WindowId;
    class Context;

    ////////////////////////////////////////////////////////////
    /** @class Window
     *  @ingroup Core
     *  @brief A Window object describing a Window.
     *
     *  When you create the Window object, the WindowImplementation
     *  object must be valid. It will create the Window from its own
     *  API but no window is shown on screen. You must associate a
     *  Context object and then use the Window::show() method.
    **/
    ////////////////////////////////////////////////////////////
    class APRO_DLL Window : public Implementable<WindowImplementation>
                            public ThreadSafe,
                            public EventEmitter

    {

    public:

        friend class WindowImplementation;

        /** @brief Describes the current status of the Window object. */
        enum Status
        {
            StatusCreated,     ///< Window is created but not shown yet.
            StatusShown,      ///< Window is created and shown.
            StatusHidden,      ///< Window is Created but hidden (a call of 'hide()' after a 'show()').
            StatusNull         ///< Default status : not created yet.
        };

        struct Rect
        {
            size_t width; ///< Width.
            size_t height;///< Height.
            size_t x;     ///< X coordinate.
            size_t y;     ///< y coordinate.
        };

    protected:

        WindowId              m_id;             ///< ID of the Window object.
        String                m_title;          ///< Title showed on the Window Title bar.
        Rect                  m_rect;           ///< Rectangle information of the Window.
        bool                  m_fullscreen;     ///< Is the Window fullscreen mode ?
        bool                  m_cursorshown;    ///< Is cursor shown ?
        WindowImplementation* m_implementation; ///< Pointer to the internal Implementation.
        Status                m_status;         ///< Current Window status.
        ContextPtr            m_context;        ///< Associated Context object.

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Constructs a Window but do not show it on screen.
        **/
        ////////////////////////////////////////////////////////////
        Window(const WindowId& id, const String& title, size_t width, size_t height, bool fullscreen);

        ////////////////////////////////////////////////////////////
        /** @brief Destructs the Window object.
        **/
        ////////////////////////////////////////////////////////////
        ~Window();

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Show the Window object on screen.
         *  @note Showing a Window object without associating a Context
         *  object before is undefined behavior.
        **/
        ////////////////////////////////////////////////////////////
        void show();

        ////////////////////////////////////////////////////////////
        /** @brief Hide the Window object if its current status is
         *  StatusShown.
        **/
        ////////////////////////////////////////////////////////////
        void hide();

        ////////////////////////////////////////////////////////////
        /** @brief Move the Window object to a new position on screen.
         *  @note On fullscreen mode, this doesn't take effect.
         *  @param relativePos : When set to true, new position is calculed
         *  as @code new_x = (old_x + x) @endcode and the same for y.
        **/
        ////////////////////////////////////////////////////////////
        void move(int x, int y, bool relativePos = false);

        ////////////////////////////////////////////////////////////
        /** @brief Resizes the Window object.
         *  @note The associated context will also be resized.
        **/
        ////////////////////////////////////////////////////////////
        void resize(size_t width, size_t height);

        ////////////////////////////////////////////////////////////
        /** @brief Set the tite of this Window object.
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
        String getTitle() const;

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
        /** @brief update the Window object.
         *
         *  Generally it only means filters the system events loop
         *  for this Window object, but it is API-dependant.
        **/
        ////////////////////////////////////////////////////////////
        void update();

        ////////////////////////////////////////////////////////////
        /** @brief Toggle Cursor hiding in the Window.
         *  @note This doesn't disable Mouse move inside the Window.
        **/
        ////////////////////////////////////////////////////////////
        void toggleCursor() const;

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Associate a Context object to this Window.
         *
         *  The Context object will be notified when the Window is
         *  resized. When the Window object is destroyed, the Context
         *  is deassociated (as a common call to 'associateContext(nullptr)' )
         *  but the Context object is not ddestroyed with the Window,
         *  as it is not fully part of the Window API.
        **/
        ////////////////////////////////////////////////////////////
        void associateContext(Context* context);

        ////////////////////////////////////////////////////////////
        /** @brief Returns a pointer to the current associated Context
         *  object.
        **/
        ////////////////////////////////////////////////////////////
        Context* getAssociatedContext();

    protected:

        ////////////////////////////////////////////////////////////
        /** @brief Destroy the Window object.
        **/
        ////////////////////////////////////////////////////////////
        void destroy();

        /** @brief The implementation notifiate when the window is moved. */
        void _notifiate_window_moved(size_t new_x, size_t new_y);
        /** @brief The implementation notifiate when the window is resized. */
        void _notifiate_window_resized(size_t new_width, size_t new_height);

    public:

        /////////////////////////////////////////////////////////////
        /** @brief Create an event recognized by his hash type.
         *
         *  It creates an event and fill every needed informations. By
         *  default, this function return a NullEvent because no event
         *  are handled.
        **/
        /////////////////////////////////////////////////////////////
        EventPtr createEvent(const HashType& e_type) const;
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
    APRO_DECLARE_EVENT_CONTENT_END()

    APRO_DECLARE_EVENT_CONTENT(WindowSizedEvent)
        size_t new_width;
        size_t new_height;
    APRO_DECLARE_EVENT_CONTENT_END()
}

#endif
