////////////////////////////////////////////////////////////
/** @file SceneMnager.cpp
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
#include "SceneManager.h"

namespace APro
{
	SceneManager::SceneManager()
	{
		m_scenemaxx = 0;
		m_scenemaxy = 0;
		m_scenemaxz = 0;
		m_isdirty   = false;
	}
	
	SceneManager::~SceneManager()
	{
		
	}
	
	void SceneManager::setSceneSize(uint32_t max_y, uint32_t max_z)
	{
		APRO_THREADSAFE_AUTOLOCK
		
		m_scenemaxy = max_y;
		m_scenemaxz = max_z;
		m_isdirty   = true;
	}
	
	Vector2 SceneManager::getSceneSize() const
	{
		return Vector2(m_scenemaxy, m_scenemaxz);
	}
	
	void SceneManager::setSceneVolumeSize(uint32_t max_y, uint32_t max_z, uint32_t max_x)
	{
		APRO_THREADSAFE_AUTOLOCK
		
		m_scenemaxx = max_x;
		m_scenemaxy = max_y;
		m_scenemaxz = max_z;
		m_isdirty   = true;
	}
	
	Vector3 SceneManager::getSceneVolumeSize() const
	{
		return Vector3(m_scenemaxy, m_scenemaxz, m_scenemaxx);
	}
}

