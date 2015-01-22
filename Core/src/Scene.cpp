////////////////////////////////////////////////////////////
/** @file Scene.cpp
 *  @ingroup Core
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 20/01/2015
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
#include "Scene.h"

namespace APro
{
	Scene::Scene()
	{
		m_backgroundcolor = Color::Black;
		m_scenemanager = SceneManagerFactory::Get().create(String("DefaultSceneManager"));
		
		if(m_scenemanager.isNull()) {
			aprodebug("Can't create a default SceneManager !!");
		}
	}
	
	Scene::~Scene() 
	{

	}
	
	void Scene::setBackgroundColor(const Color& color)
	{
		APRO_THREADSAFE_AUTOLOCK
		m_backgroundcolor = color;
	}
	
	const Color& Scene::getBackgroundColor() const
	{
		return m_backgroundcolor;
	}
	
	void Scene::setActiveSize(const SizeString& sizestring)
	{
		if(!m_scenemanager.isNull()) {
			m_scenemanager->setSceneSize(sizestring.getFirst(), sizestring.getSecond());
		}
	}
	
	Vector2 Scene::getActiveSize() const
	{
		if(m_scenemanager.isNull()) {
			return Vector2::Zero;
		}
		else {
			return m_scenemanager->getSceneSize();
		}
	}
	
	SceneManager& Scene::getSceneManager()
	{
		return *m_scenemanager;
	}
	
	const SceneManager& Scene::getSceneManager() const
	{
		return *m_scenemanager;
	}
	
	SceneManager& Scene::setSceneManager(const SceneManagerLocalPtr& scenemanager)
	{
		APRO_THREADSAFE_AUTOLOCK 
		m_scenemanager = scenemanager;
	}
}
