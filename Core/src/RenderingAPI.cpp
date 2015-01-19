////////////////////////////////////////////////////////////
/** @file RenderingAPI.cpp
 *  @ingroup Rendering
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 26/12/2014 - 19/01/2015
 *
 *  @brief 
 *  Implements the RenderingAPI and RenderingAPIFactory classes.
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
#include "RenderingAPI.h"

namespace APro
{
	void RendererInfo::print(Console& console) const
	{
		console << "\nDriver Vendor   : " << drivervendor;
		console << "\nDriver Renderer : " << renderer;
		console << "\nDriver Version  : " << version;
	}
	
	APRO_IMPLEMENT_MANUALSINGLETON(RenderingAPIFactory)
	
	bool RenderingAPIFactory::hasRenderer (const String& renderer) const 
	{ 
		return hasPrototype(renderer); 
	}
	
	String RenderingAPIFactory::listRegisteredRenderers() const 
	{
		String ret;
		for(Map<String, PrototypeBase*>::const_iterator it = prototypes.begin(); it != prototypes.end(); it++)
		{ 
			ret << "\"" << it.key() << "\", ";
		}
		
		return ret;
	}
	
	RenderingAPIPtr RenderingAPIFactory::createRenderer(const String& renderer, const String& renderername) const 
	{
		APRO_THREADSAFE_AUTOLOCK
		
		aproassert1(prototypes.keyExists(renderer));
		RenderingAPI* render = create(renderer);
		if (render)
		{
			render->setName(renderername);
			return RenderingAPIPtr(render);
		}
		else
			return RenderingAPIPtr::Null;
	}
	
	StringArray RenderingAPIFactory::getRenderersList() const
	{
		return prototypes.getKeysArray();
	}
	
	RenderingAPI::RenderingAPI()
	{
		rootscene = nullptr;
	}
	
	WindowPtr RenderingAPI::createWindow(const String& windowname, uint32_t width, uint32_t height, bool fullscreen)
	{
		aproassert1(width != 0 && height != 0 && !windowname.isEmpty());
		
		APRO_THREADSAFE_AUTOLOCK
		
		// Call the implementation to create the Window object.
		WindowPtr retwin = _createWindowImpl(windowname, width, height, fullscreen);
		if(!retwin) {
			aprodebug("Couldn't create Appropriate Window !");
			return WindowPtr::Null;
		}
		
		renderingtargets.append(retwin);
		retwin->setActivated(false); // This should be activated when Window::show() is called.
		
		return retwin;
	}
	
	ScenePtr RenderingAPI::getRoot()
	{
		return rootscene;
	}
	
	const ScenePtr RenderingAPI::getRoot() const
	{
		return rootscene;
	}
}
