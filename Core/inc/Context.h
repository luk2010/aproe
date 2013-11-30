////////////////////////////////////////////////////////////
/** @file Context.h
 *  @ingroup Rendering
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 19/09/2012
 *
 *  Defines the Context class.
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

    ////////////////////////////////////////////////////////////
    /** @class Context
     *  @ingroup Rendering
     *  @brief Represents a classic Context.
     *
     *  A Context is an object associated with a Window. The Context
     *  is an area where the Rendering API will be able to draw
     *  anythings. It also holds some datas.
     *
     *  It is the Window wich create the context. This class always
     *  pass through its window parent to make action, so it is
     *  independant from Rendering API.
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
    **/
    ////////////////////////////////////////////////////////////
    class APRO_DLL Context : public EventListener,
                             public EventEmitter,
                             public NonCopyable
    {
        APRO_DECLARE_SHAREDPOINTER_CLASS_TYPEDEF(Context)

    private:

        friend class Window;

        ////////////////////////////////////////////////////////////
        /** @brief Constructs an empty Context object.
        **/
        ////////////////////////////////////////////////////////////
        Context(Window* _window);

        ////////////////////////////////////////////////////////////
        /** @brief Destructs the Context object.
        **/
        ////////////////////////////////////////////////////////////
        ~Context();

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Returns a pointer to the parent window.
         *
         *  @note Don't delete this pointer nor use it on memory
         *  function.
        **/
        ////////////////////////////////////////////////////////////
        Window* getWindow();

        ////////////////////////////////////////////////////////////
        /** @brief Returns a pointer to the parent window.
        **/
        ////////////////////////////////////////////////////////////
        const Window* getWindow() const;

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
         *  @note It is to the Window class to physically bind the
         *  context because it is platform and API dependant.
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
         *  @note It is to the Window class to physically unbind the
         *  context because it is platform and API dependant.
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
        const ViewPortPtr getViewPort(const String & name) const;

        ////////////////////////////////////////////////////////////
        /** @brief Return the ViewPort designated by his name.
        **/
        ////////////////////////////////////////////////////////////
        ViewPortPtr getViewPort(const String & name);

        ////////////////////////////////////////////////////////////
        /** @brief Return the default ViewPort of this Context.
        **/
        ////////////////////////////////////////////////////////////
        const ViewPortPtr getDefaultViewPort() const;

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

    protected:

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
        void updateViewPorts(WindowResizeEvent* e);

    protected:

        void setLoaded(bool l);
        void setBinded(bool b);

    protected:

        /////////////////////////////////////////////////////////////
        /** @brief Handle a given event.
         *  @see EventListener::handle
        **/
        /////////////////////////////////////////////////////////////
        bool handle(EventPtr& event);

        /////////////////////////////////////////////////////////////
        /** @brief Create an event recognized by his hash type.
         *  @see EventEmitter::createEvent
        **/
        /////////////////////////////////////////////////////////////
        EventPtr createEvent(const HashType& e_type) const;

    protected:

        Window* window;
        bool loaded;
        bool binded;

        Array<ViewPortPtr> viewports;
    };

    typedef AutoPointer<Context> ContextPtr;///< An AutoPointer to a Context Object.

    /** @brief An event that is send when Context is binded. */
    APRO_DECLARE_EVENT_NOCONTENT(ContextBindedEvent);

    /** @brief An event that is send when Context is unbinded. */
    APRO_DECLARE_EVENT_NOCONTENT(ContextUnbindedEvent);
}

#endif
