////////////////////////////////////////////////////////////
/** @file RenderingAPI.cpp
 *  @ingroup Rendering
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 26/12/2014
 *
 *  @brief 
 *  Implements the RenderingAPI and RenderingAPIFactory classes.
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
#include "RenderingAPI.h"

namespace APro
{
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
		aproassert1(prototypes.keyExists(renderer));
		RenderingAPI* render = create(renderer);
		render->setName(renderername);
		return RenderingAPIPtr(render);
	}
}
