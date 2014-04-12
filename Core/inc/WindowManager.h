////////////////////////////////////////////////////////////
/** @file WindowManager.h
 *  @ingroup Core
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 06/09/2012 - 12/04/2014
 *
 *  Defines the WindowManager class.
 *
**/
////////////////////////////////////////////////////////////
#ifndef APROWINDOWMANAGER_H
#define APROWINDOWMANAGER_H

#include "Platform.h"
#include "Manager.h"
#include "IdGenerator.h"
#include "Window.h"

namespace APro
{
    ////////////////////////////////////////////////////////////
    /** @class WindowManager
     *  @ingroup Core
     *  @brief Manages every created Window instances in the
     *  Engine.
     *
     *  The WindowManager easily creates and destroys Window objects
     *  instanciated. When you create a Window, be sure a Window Plugin
     *  is already loaded or nothing will be shown and you will
     *  have to go through errors.
     *
     *  @note You can use the WindowManager::hasValidWindowImplementation()
     *  to check the Window implementation.
     *
     *  @note The number of Window that can be created by this
     *  manager is 1024. This is done to make the user not be
     *  able to destroy the GUI subsystem in doing somethings
     *  stupids. At least you will never need more than 1024 Windows.
    **/
    ////////////////////////////////////////////////////////////
    class APRO_DLL WindowManager : public Manager<Window, Array<WindowPtr> >
    {

        APRO_DECLARE_MANUALSINGLETON(WindowManager)

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Constructs the Window Manager.
        **/
        ////////////////////////////////////////////////////////////
        WindowManager();

        ////////////////////////////////////////////////////////////
        /** @brief Destructs the Window Manager.
         *  @note Every Window objects created in this Manager will be
         *  destroyed during the process.
        **/
        ////////////////////////////////////////////////////////////
        ~WindowManager();

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Creates a new Window object and returns its Id.
         *
         *  @note Window is not showen at the end of this function,
         *  so you must use Window::show() to show the Window. You should
         *  associate a Context before showing the Window.
         *
         *  @return 0 if an error occured.
        **/
        ////////////////////////////////////////////////////////////
        WindowId create(const String& title, const size_t& width, const size_t& height, bool fullscreen);

        ////////////////////////////////////////////////////////////
        /** @brief Destroys the given Window object.
         *
         *  If the Window object has a valid context, with a running
         *  renderer, the renderer will be stopped and the context will
         *  be invalid. @note The Context object may not be destroyed
         *  with the Window object.
         *
         *  @param window : Valid pointer to a Window object. @note This
         *  pointer can't be constant as this function nullize the pointer
         *  and invalidate it.
         *
         *  @return true on success, false on error.
        **/
        ////////////////////////////////////////////////////////////
        bool destroy(WindowPtr& window);

        ////////////////////////////////////////////////////////////
        /** @brief Destroys the given Window object.
         *
         *  If the Window object has a valid context, with a running
         *  renderer, the renderer will be stopped and the context will
         *  be invalid. @note The Context object may not be destroyed
         *  with the Window object.
         *
         *  @return true on success, false on error.
        **/
        ////////////////////////////////////////////////////////////
        bool destroy(const WindowId& windowId);

        ////////////////////////////////////////////////////////////
        /** @brief Returns the Window indicated to given ID.
         *  @return A null pointer if windowid is not valid.
        **/
        ////////////////////////////////////////////////////////////
        WindowPtr& getWindow(const WindowId& windowid);

        ////////////////////////////////////////////////////////////
        /** @brief Returns the Window indicated to given ID.
         *  @return A null pointer if windowid is not valid.
        **/
        ////////////////////////////////////////////////////////////
        const WindowPtr& getWindow(const WindowId& windowid) const;

        ////////////////////////////////////////////////////////////
        /** @brief Returns the number of not-null registered Window.
        **/
        ////////////////////////////////////////////////////////////
        size_t countActiveWindows() const;

        ////////////////////////////////////////////////////////////
        /** @brief Destroys every Window objects and reset the
         *  IdGenerator.
        **/
        ////////////////////////////////////////////////////////////
        void clear();

        ////////////////////////////////////////////////////////////
        /** @brief Updates every windows message queue.
        **/
        ////////////////////////////////////////////////////////////
        void updateWindows();

        ////////////////////////////////////////////////////////////
        /** @brief Returns true if ID is valid.
        **/
        ////////////////////////////////////////////////////////////
        bool isIdValid(const WindowId& windowid) const;

        ////////////////////////////////////////////////////////////
        /** @brief Returns true if window is registered in the
         *  WindowManager.
        **/
        ////////////////////////////////////////////////////////////
        bool isWindowRegistered(const WindowPtr& window) const;

    protected:

        ////////////////////////////////////////////////////////////
        /** @brief Returns the first null ID in the array.
        **/
        ////////////////////////////////////////////////////////////
        WindowId findNullId() const;

    private:

        typedef Array<WindowPtr> WindowArray;
        WindowArray&             windows;///< Array of windows.
        IdGenerator              idgen;  ///< The Window Id Generator.
    };
}

#endif
