////////////////////////////////////////////////////////////
/** @file Context.h
 *  @ingroup Rendering
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 19/09/2012 - 17/12/2014
 *
 *  @brief
 *  Defines the Context class.
 *
 *  @copyright
 *  Atlanti's Project Engine
 *  Copyright (C) 2012 - 2014  Atlanti's Corp
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
#ifndef APROCONTEXT_H
#define APROCONTEXT_H

#include "Platform.h"
#include "AutoPointer.h"

#include "EventReceiver.h"
#include "ViewPort.h"

namespace APro
{
    class Window;
    class RenderingAPI;

    ////////////////////////////////////////////////////////////
    /** @class Context
     *  @ingroup Rendering
     *  @brief Represents a classic Context.
     *
     *  A Context is an object associated with a Window. The Context
     *  is an area where the Rendering API will be able to draw
     *  anythings. It also holds some datas.
     *
     *  The Context Object is associated to a Window Object. It is
     *  a link between the Window API and the Rendering API.
     *
     *  ### Events Emitted
     *
     *  - ContextBindedEvent   : Context is binded.
     *  - ContextUnbindedEvent : Context is unbinded.
     *
     *  ### Events Listened
     *
     *  - WindowResizedEvent : Context resize his default viewport
     *  size and update the others.
     *
     *  ### Part in the Rendering System
     *
     *  The currently binded Context is used by the Rendering System
     *  to know where to draw. In the Context, it will draw in the default
     *  Viewport, but also in each separate Viewport.
     *
     *  @code
     *  // Create a basic Window
     *  WindowID myWindow = WindowManager::Get().create(...);
     *
     *  // Create the Context for given Window
     *  RenderingAPIPtr myRenderingAPI = Main::Get().createRenderingAPI();
     *  ContextPtr myContext = myRenderingAPI->createContext(myWindow);
     *
     *  // Do what you want with the context here...
     *
     *  // Destroying the context is done with the Window.
     *  WindowManager::Get().destroy(myWindow);
     *  myContext.nullize(); // We ensure the pointer is invalidated.
     *  @endcode
     *
     *  @note The Context object destruction is owned by the Window
     *  object.
    **/
    ////////////////////////////////////////////////////////////
    class APRO_DLL Context : public EventEmitter
    {
    protected:

        Window*            m_window;       ///< Associated Window.
        RenderingAPI*      m_renderingapi; ///< RenderingAPI wich constructe the Context object.
        bool               m_loaded;       ///< true if Context object is ready to be binded.
        bool               m_binded;       ///< true if binded.
        Array<ViewPortPtr> m_viewports;    ///< Viewports holded by this Context object.

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Constructs a Context object.
        **/
        ////////////////////////////////////////////////////////////
        Context(Window* associatedWindow, RenderingAPI* renderingAPI);

        ////////////////////////////////////////////////////////////
        /** @brief Destructs the Context object.
        **/
        ////////////////////////////////////////////////////////////
        ~Context();

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Returns a pointer to the associated Window object.
        **/
        ////////////////////////////////////////////////////////////
        Window* getWindow();

        ////////////////////////////////////////////////////////////
        /** @brief Returns a pointer to the associated RenderingAPI
         *  object.
        **/
        ////////////////////////////////////////////////////////////
        RenderingAPI* getRenderingAPI();

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Tell if context has been loaded.
         *
         *  The context is loaded when the default viewport has been
         *  created, so you can access it.
        **/
        ////////////////////////////////////////////////////////////
        bool isLoaded() const;

        ////////////////////////////////////////////////////////////
        /** @brief Tell if context has been binded.
         *
         *  Context is binded when the Window asked the API to use
         *  this Contex as the current Context.
        **/
        ////////////////////////////////////////////////////////////
        bool isBinded() const;

        ////////////////////////////////////////////////////////////
        /** @brief Bind this context.
         *
         *  This is equivalent to set this context as the current
         *  drawing context. At the end of the function, this context
         *  will be the surface where the Rendering System will draw
         *  the Scenes.
         *
         *  @return True if context has been successfully binded.
        **/
        ////////////////////////////////////////////////////////////
        bool bind();

        ////////////////////////////////////////////////////////////
        /** @brief Unbind this context.
         *
         *  This is equivalent to set the current context to null.
         *  At the end of the function, the Rendering System will stop
         *  drawing in this Context.
         *
         *  @return True if context has been successfully unbinded.
        **/
        ////////////////////////////////////////////////////////////
        bool unbind();

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Add a given ViewPort to this Context.
         *
         *  The newly added ViewPort will not be visible untill the
         *  user set its visible property to true.
         *
         *  @note The Viewport name must be different from every other
         *  Viewport already in this Context.
        **/
        ////////////////////////////////////////////////////////////
        void addViewPort(const ViewPortPtr& viewport);

        ////////////////////////////////////////////////////////////
        /** @brief Remove given ViewPort from the viewport list.
         *
         *  It destroys the stocked AutoPointer, so if it was the last
         *  holding AutoPointer the ViewPort is correctly released.
        **/
        ////////////////////////////////////////////////////////////
        void removeViewPort(const String& name);

        ////////////////////////////////////////////////////////////
        /** @brief Return the ViewPort designated by his name.
        **/
        ////////////////////////////////////////////////////////////
        const ViewPortPtr& getViewPort(const String & name) const;

        ////////////////////////////////////////////////////////////
        /** @brief Return the ViewPort designated by his name.
        **/
        ////////////////////////////////////////////////////////////
        ViewPortPtr& getViewPort(const String & name);

        ////////////////////////////////////////////////////////////
        /** @brief Return the default ViewPort of this Context.
        **/
        ////////////////////////////////////////////////////////////
        const ViewPortPtr& getDefaultViewPort() const;

    protected:

        ////////////////////////////////////////////////////////////
        /** @brief Return the const_iterator corresponding to the given
         *  ViewPort by name.
        **/
        ////////////////////////////////////////////////////////////
        Array<ViewPortPtr>::const_iterator getViewPortIterator(const String& name) const;

        ////////////////////////////////////////////////////////////
        /** @brief Return the const_iterator corresponding to the given
         *  ViewPort by name.
        **/
        ////////////////////////////////////////////////////////////
        Array<ViewPortPtr>::iterator getViewPortIterator(const String& name);

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Return True if given ViewPort is in this Context.
        **/
        ////////////////////////////////////////////////////////////
        bool hasViewPort(const String& name) const;

        ////////////////////////////////////////////////////////////
        /** @brief Return True if given ViewPorts are in this Context.
         *
         *  @note If the array is empty, or if one of thh ViewPort name
         *  is not found, this function returns false.
        **/
        ////////////////////////////////////////////////////////////
        bool hasViewPorts(const StringArray& names) const;

        ////////////////////////////////////////////////////////////
        /** @brief Return the number of ViewPort in this Context.
        **/
        ////////////////////////////////////////////////////////////
        size_t getNumViewPorts() const;

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Initialize the default ViewPort.
         *  @internal
        **/
        ////////////////////////////////////////////////////////////
        void initDefaultViewPort();

        ////////////////////////////////////////////////////////////
        /** @brief Update Viewports when Window is resized.
         *  @internal
        **/
        ////////////////////////////////////////////////////////////
        void onWindowResized(size_t width, size_t height);

        ////////////////////////////////////////////////////////////
        /** @brief Update Viewports when Window is resized.
         *  @internal
        **/
        ////////////////////////////////////////////////////////////
        void updateViewPorts(size_t width, size_t height);

    protected:

        /////////////////////////////////////////////////////////////
        /** @brief Create an event recognized by his hash type.
         *  @see EventEmitter::createEvent
        **/
        /////////////////////////////////////////////////////////////
        EventPtr createEvent(const HashType& e_type) const;
    };

    typedef AutoPointer<Context> ContextPtr;///< An AutoPointer to a Context Object.

    /** @brief An event that is send when Context is binded. */
    APRO_DECLARE_EVENT_NOCONTENT(ContextBindedEvent);

    /** @brief An event that is send when Context is unbinded. */
    APRO_DECLARE_EVENT_NOCONTENT(ContextUnbindedEvent);
}

#endif
