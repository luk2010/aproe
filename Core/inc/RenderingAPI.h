////////////////////////////////////////////////////////////
/** @file RenderingAPI.h
 *  @ingroup Rendering
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 18/04/2014
 *
 *  Defines the RenderingAPI implementation.
 *
**/
////////////////////////////////////////////////////////////
#ifndef APRO_RENDERINGAPI_H
#define APRO_RENDERINGAPI_H

#include "Platform.h"
#include "Implementation.h"

namespace APro
{
    ////////////////////////////////////////////////////////////
    /** @class RenderingAPI
     *  @ingroup Rendering
     *  @brief An implementation class for the Rendering API.
     *
     *  This implementation object is a base for every rendering
     *  AI supported by this engine. A plugin can create its own
     *  rendering API and so supports any kind of render.
     *  Every functions must be overwritten. @see Functions
     *  documentation for more explanation on how to overwrite
     *  them.
    **/
    ////////////////////////////////////////////////////////////
    class RenderingAPI : public Implementation
    {
    public:

        ////////////////////////////////////////////////////////////
        /** @brief Constructs a RenderingAPI object.
        **/
        ////////////////////////////////////////////////////////////
        RenderingAPI() {}

        ////////////////////////////////////////////////////////////
        /** @brief Destructs a RenderingAPI object.
        **/
        ////////////////////////////////////////////////////////////
        virtual ~RenderingAPI() {}

    public:

        ////////////////////////////////////////////////////////////
        /** @name Context Managing functions
         *  @{
         *
         *  A note on overwriting Context functions : always keep in
         *  mind that the Context object is created by the RenderingAPI
         *  but, as it is linked to the Window object for its whole life,
         *  the Context object is destroyed by the Window object.
         *
        **/
        ////////////////////////////////////////////////////////////

        ////////////////////////////////////////////////////////////
        /** @brief Creates a Context object and associate it to a
         *  Window object.
         *
         *  This function should create the Context object, initialize
         *  it, and associate it with the given Window object. The steps
         *  can be done without orders. The returned AutoPointer should
         *  be created after associating the Context object to the Window
         *  object, because the Window object must set the owning property
         *  to itself.
        **/
        ////////////////////////////////////////////////////////////
        virtual ContextPtr createContext(Window* window) = 0;

        ////////////////////////////////////////////////////////////
        /** @brief Bind the given Context object, if not null.
        **/
        ////////////////////////////////////////////////////////////
        virtual bool bindContext(Context* context) = 0;

        ////////////////////////////////////////////////////////////
        /** @brief Unbind the given Context object, if not null.
        **/
        ////////////////////////////////////////////////////////////
        virtual bool unbindContext(Context* context) = 0;

        ////////////////////////////////////////////////////////////
        /** @brief Should unregister the Context object from this
         *  RenderingAPI.
         *
         *  This function is called when the Context is about to be
         *  destroyed by the Winodw object, because the Window::associateContext(nullptr)
         *  function is called or because the Window destructor is called.
         *  Context should already be unbinded but API data should
         *  be cleaned here.
        **/
        ////////////////////////////////////////////////////////////
        virtual void unregisterContext(Context* context) = 0;

        /** @} */

    protected:


    };
}

#endif // APRO_RENDERINGAPI_H
