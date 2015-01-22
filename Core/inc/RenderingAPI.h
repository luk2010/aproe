////////////////////////////////////////////////////////////
/** @file RenderingAPI.h
 *  @ingroup Rendering
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 18/04/2014 - 20/01/2015
 *
 *  @brief 
 *  Defines the RenderingAPI implementation.
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
#ifndef APRO_RENDERINGAPI_H
#define APRO_RENDERINGAPI_H

#include "Platform.h"
#include "Factory.h"
#include "ThreadSafe.h"

#include "Context.h"
#include "Singleton.h"
#include "Printable.h"
#include "Scene.h"

namespace APro
{
	class RenderingAPIFactory;
	
	class RendererInfo : 
		public Printable
	{
	public:
			
		String drivervendor; ///< @brief Name of the Vendor responsible for this implementation.
		String version;      ///< @brief Version of the Implementation.
		String renderer;     ///< @brief Name of the hardware renderer.
		
		void print(Console& console) const;
	};
	
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
    class RenderingAPI : 
    	public Prototype,
		public ThreadSafe
    {
    public:

        ////////////////////////////////////////////////////////////
        /** @brief Constructs a RenderingAPI object.
        **/
        ////////////////////////////////////////////////////////////
        RenderingAPI();

        ////////////////////////////////////////////////////////////
        /** @brief Destructs a RenderingAPI object.
        **/
        ////////////////////////////////////////////////////////////
        virtual ~RenderingAPI() {}

    public:
    	
    	friend class RenderingAPIFactory;

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
        
        ////////////////////////////////////////////////////////////
        /** @brief Returns the name of this Rendering API.
        **/
        ////////////////////////////////////////////////////////////
        const String& getName() const { return m_name; }
        
        ////////////////////////////////////////////////////////////
        /** @brief Returns Info about the current Renderer.
         *
         *  @note
         *  This function is implemented as it should fill every fields
         *  in the returned structure.
        **/
        ////////////////////////////////////////////////////////////
        virtual RendererInfo getRendererInfo() const = 0;
        
        ////////////////////////////////////////////////////////////
        /** @brief Creates a new Window Rendering Target and attach it
         *  to this Renderer.
         *  
         *  @note
         *  The returned Window will not be shown. You have to use
         *  Window::show() to show it on screen.
        **/
        ////////////////////////////////////////////////////////////
		WindowPtr createWindow(const String& windowname, uint32_t width, uint32_t height, bool fullscreen);
		
		////////////////////////////////////////////////////////////
        /** @brief Returns the Root Scene node of this Renderer.
         *  
         *  @note
         *  The Root Scene node is the first Node of the Scene. It must
         *  contains every Renderable Object registered to this Renderer,
         *  and contains every Scene susceptible to be rendered in a 
         *  Rendering Target.
        **/
        ////////////////////////////////////////////////////////////
		Scene& getRoot();
		
		////////////////////////////////////////////////////////////
        /** @brief Returns the Root Scene node of this Renderer.
         *  
         *  @note
         *  The Root Scene node is the first Node of the Scene. It must
         *  contains every Renderable Object registered to this Renderer,
         *  and contains every Scene susceptible to be rendered in a 
         *  Rendering Target.
        **/
        ////////////////////////////////////////////////////////////
		const Scene& getCstRoot() const;
		
	protected:
		
		////////////////////////////////////////////////////////////
        /** @brief Creates a new Window Rendering Target.
         * 
         *  @note 
         *  The created window should not be appended by this 
         *  function to the renderer target list. The created Window
         *  also should be fully initialized and ready to call 
         *  Window::show(). 
        **/
        ////////////////////////////////////////////////////////////
		WindowPtr _createWindowImpl(const String& windowname, uint32_t width, uint32_t height, bool fullscreen) const = 0;

    protected:

		////////////////////////////////////////////////////////////
        /** @brief Sets the name of this Rendering API, which will be
         *  saw in debug mode messages.
        **/
        ////////////////////////////////////////////////////////////
		void setName(const String& renderername) { m_name = renderername; }
		
	private:
		
		String 				 m_name;			///< @brief Name of this Renderer.
		RenderingTargetArray renderingtargets;  ///< @brief Targets rendered by this Renderer.
		ScenePtr 			 rootscene;			///< @brief Root Scene node owned by the Renderer.
    };

    typedef AutoPointer<RenderingAPI> RenderingAPIPtr;
    
    ////////////////////////////////////////////////////////////
    /** @brief The RenderingAPIFactory is a factory instanciated
     *  by the Main Object. 
     *
     *  @note
     *  You can create a rendering api directly from this factory.
    **/
    ////////////////////////////////////////////////////////////
    class RenderingAPIFactory : public Factory<RenderingAPI>
    {
    	APRO_DECLARE_MANUALSINGLETON(RenderingAPIFactory)
    	
	public:
		
		////////////////////////////////////////////////////////////
        /** @brief Returns true if given renderer name is registered.
        **/
        ////////////////////////////////////////////////////////////
		bool hasRenderer (const String& renderer) const;
		
		////////////////////////////////////////////////////////////
        /** @brief Lists every registered renderers.
        **/
        ////////////////////////////////////////////////////////////
		String listRegisteredRenderers() const;
		
		////////////////////////////////////////////////////////////
        /** @brief Creates a new Renderer using given name.
        **/
        ////////////////////////////////////////////////////////////
		RenderingAPIPtr createRenderer(const String& renderer, const String& renderername) const;
		
		////////////////////////////////////////////////////////////
        /** @brief Returns an Array with every registered Renderers.
        **/
        ////////////////////////////////////////////////////////////
		StringArray getRenderersList() const;
    };
}

#endif // APRO_RENDERINGAPI_H
