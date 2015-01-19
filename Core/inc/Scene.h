////////////////////////////////////////////////////////////
/** @file Scene.h
 *  @ingroup Core
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 19/01/2015
 *
 *  @brief 
 *  Defines the Scene implementation.
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
#ifndef APRO_SCENE_H
#define APRO_SCENE_H

#include "Platform.h"
#include "BaseObject.h"

#include "Color.h"
#include "SizeString.h"

namespace APro
{
	class Scene
		: public BaseObject<Scene>
	{
	public:
		
		Scene() {}
		~Scene() {}
		
	public:
		
		void setBackgroundColor(const Color& color) { m_backgroundcolor = color; }
		void setSize(const SizeString& sizestring) { }
		
	private:
		
		Color m_backgroundcolor;
	};
	
	typedef AutoPointer<Scene> ScenePtr;
}

#endif // APRO_SCENE_H
