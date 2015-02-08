////////////////////////////////////////////////////////////
/** @file SceneMnager.h
 *  @ingroup Core
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 21/01/2015
 *
 *  @brief 
 *  Defines the SceneManager implementation.
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
#ifndef APRO_SCENEMANAGER_H
#define APRO_SCENEMANAGER_H

#include "Platform.h"
#include "ThreadSafe.h"

#include "Factory.h"
#include "Vector3.h"

namespace APro
{
	class SceneManager :
		public Prototype,
		public ThreadSafe
	{
	public:
			
		SceneManager();
		virtual ~SceneManager();
		
	public:
		
		////////////////////////////////////////////////////////////
        /** @brief Sets the Maximum Size surface (y and z values) of
         *  the Scene.
        **/
        ////////////////////////////////////////////////////////////
		void setSceneSize(uint32_t max_y, uint32_t max_z);
		
		////////////////////////////////////////////////////////////
        /** @brief Returns the Size of the Scene (which is the Y maximum
		 *  value and the Z maximum value).
        **/
        ////////////////////////////////////////////////////////////
		Vector2 getSceneSize() const;
		
		////////////////////////////////////////////////////////////
        /** @brief Sets the maximum value for x, y and z axis.
        **/
        ////////////////////////////////////////////////////////////
		void setSceneVolumeSize(uint32_t max_y, uint32_t max_z, uint32_t max_x);
		
		////////////////////////////////////////////////////////////
        /** @brief Returns the 3 volumes coordinates (y, z and x maximum
		 *  values).
        **/
        ////////////////////////////////////////////////////////////
		Vector3 getSceneVolumeSize() const;
		
	protected:
		
		uint32_t m_scenemaxx; ///< @brief The Scene Max X value.
		uint32_t m_scenemaxy; ///< @brief The Scene Max Y value.
		uint32_t m_scenemaxz; ///< @brief The Scene Max Z value.
		
		bool     m_isdirty;   ///< @brief True if SceneManager must be updated.
	};  
	
	typedef PrototypeLocalPtr<SceneManager> SceneManagerLocalPtr;
}

#endif // APRO_SCENEMANAGER_H

