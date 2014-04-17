////////////////////////////////////////////////////////////
/** @file WindowImplementation.h
 *  @ingroup Core
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 16/03/2013 - 15/04/2014
 *
 *  Defines the WindowImplementation class.
 *
**/
////////////////////////////////////////////////////////////
#ifndef APRO_WINDOWIMPLEMENTATION_H
#define APRO_WINDOWIMPLEMENTATION_H

#include "Platform.h"
#include "Implementation.h"

namespace APro
{
    class Window;

    ////////////////////////////////////////////////////////////
    /** @class WindowImplementation
     *  @ingroup Core
     *  @brief An implementation interface for Window object.
     *
     *  Overwrite every pure function of this object to create a
     *  new implementation for Window object.
    **/
    ////////////////////////////////////////////////////////////
    class APRO_DLL WindowImplementation : public Implementation
    {

    public:

        WindowImplementation() {}
        virtual ~WindowImplementation() {}

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Constructs the Window object ut does not show it.
         *
         *  When overwriting this function, you should prepare the Window
         *  to receive an associated Context object. Kee p in mind that
         *  your window must be ready for the RenderingAPI to associate
         *  a Context whatever rendering API is used, so tryy to be the
         *  most standard compliant as possible.
         *
         *  @param title : The title the Window should show on the top
         *  bar.
         *  @param width : The width parameter of the Window, in number
         *  of pixels.
         *  @param height : The height parameter of the Window, in number
         *  of pixels.
         *  @param fullscreen : If true, the Window should be shown
         *  fullscreen, if your Window API supports it.
        **/
        ////////////////////////////////////////////////////////////
        virtual bool create(const String& title, size_t width, size_t height, bool fullscreen) = 0;

        ////////////////////////////////////////////////////////////
        /** @brief Show the Window on the screen.
         *  @return True on success.
        **/
        ////////////////////////////////////////////////////////////
        virtual bool show() = 0;

        ////////////////////////////////////////////////////////////
        /** @brief Hide the Window from the screen.
         *  @return True on success.
        **/
        ////////////////////////////////////////////////////////////
        virtual bool hide() = 0;

        ////////////////////////////////////////////////////////////
        /** @brief Move the Window at the given new position set.
         *
         *  This function must call Window::_notifiate_window_moved()
         *  to notifiate the parent Window that the Window successfully
         *  moved.
         *
         *  @param x : The x coordinate property of the Window, in number
         *  of pixels.
         *  @param y : The y coordinate property of the Window, in number
         *  of pixels.
        **/
        ////////////////////////////////////////////////////////////
        virtual void move(size_t x, size_t y) = 0;

        ////////////////////////////////////////////////////////////
        /** @brief Resize the Window at the given new size set.
         *
         *  This function must call Window::_notifiate_window_resized()
         *  to notifiate the parent Window that the Window successfully
         *  resized.
         *
         *  @param width : The width parameter of the Window, in number
         *  of pixels.
         *  @param height : The height parameter of the Window, in number
         *  of pixels.
        **/
        ////////////////////////////////////////////////////////////
        virtual void resize(size_t width, size_t height) = 0;

        ////////////////////////////////////////////////////////////
        /** @brief Change the title of the Window.
         *  @param title : New title for the Window.
        **/
        ////////////////////////////////////////////////////////////
        virtual void setTitle(const String& title);

        ////////////////////////////////////////////////////////////
        /** @brief Updates the Window.
         *
         *  Generally this corresponds to lookk at the system message
         *  queue for the Window object.
        **/
        ////////////////////////////////////////////////////////////
        virtual void update() = 0;

        ////////////////////////////////////////////////////////////
        /** @brief Show (or not) the cursor on the screen when it is
         *  over the window.
        **/
        ////////////////////////////////////////////////////////////
        virtual void showCursor(bool show_cursor) = 0;

        ////////////////////////////////////////////////////////////
        /** @brief Destroys the Window.
        **/
        ////////////////////////////////////////////////////////////
        virtual void destroy() = 0;

        ////////////////////////////////////////////////////////////
        /** @brief Returns the holded specific data of this Window
         *  implementation.
         *
         *  This data is used by RenderingAPI to create and associate
         *  context depending on used API.
        **/
        ////////////////////////////////////////////////////////////
        virtual void* getData() = 0;

    public:

        Window* parent_window;///< A pointer to the parent Window object. This pointer is setted
                              ///  by the Window object himself.
    };
}

#endif // APRO_WINDOWIMPLEMENTATION_H
