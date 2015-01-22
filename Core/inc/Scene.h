////////////////////////////////////////////////////////////
/** @file Scene.h
 *  @ingroup Core
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 19/01/2015 - 20/01/2015
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
#include "ThreadSafe.h"

#include "Color.h"
#include "SizeString.h"
#include "SceneManager.h"

namespace APro
{
	////////////////////////////////////////////////////////////
	/** @class Scene
	 *  @ingroup Core
	 *  @brief Integrates every Scene related objects.
	 *
	 *  The Scene object has a great role in the Engine. It must 
	 *  organize every objects before they can be drawn by the
	 *  RenderingAPI. Objects should be organized using the 
	 *  appropriate SceneManager, which can be the default one, 
	 *  or a loaded one ( see SceneManagerFactory ).
	 *  You can load the SceneManager you want, but you will have 
	 *  to reload every objects. This can take time, depending on
	 *  the SceneManager and on the number of objects.
	**/
	////////////////////////////////////////////////////////////
	class Scene : 
		public BaseObject<Scene>,
		public ThreadSafe
	{
	public:
		
		////////////////////////////////////////////////////////////
        /** @brief Constructs a Scene object, and sets a new default 
         *  SceneManager (using SceneManagerFactory::create("DefaultSceneManager") ).
        **/
        ////////////////////////////////////////////////////////////
		Scene();
		
		////////////////////////////////////////////////////////////
        /** @brief Destructs the Scene object, and also the SceneManager.
        **/
        ////////////////////////////////////////////////////////////
		~Scene();
		
	public:
		
		////////////////////////////////////////////////////////////
        /** @brief Sets the background color for the whole scene.
        **/
        ////////////////////////////////////////////////////////////
		void setBackgroundColor(const Color& color);
		
		////////////////////////////////////////////////////////////
        /** @brief Returns the background color for the whole scene.
        **/
        ////////////////////////////////////////////////////////////
		const Color& getBackgroundColor() const;
		
		////////////////////////////////////////////////////////////
        /** @brief Sets the size of the active Scene. 
         *  @note This is a task performed by the SceneManager, but it
         *  may probably reload the whole Scene so don't use it too 
         *  much.
        **/
        ////////////////////////////////////////////////////////////
		void setActiveSize(const SizeString& sizestring);
		
		////////////////////////////////////////////////////////////
        /** @brief Returns the size of the active Scene. 
        **/
        ////////////////////////////////////////////////////////////
		Vector2 getActiveSize() const;
		
	public:
		
		////////////////////////////////////////////////////////////
        /** @brief Returns the SceneManager in use.
        **/
        ////////////////////////////////////////////////////////////
		SceneManager& getSceneManager();
		
		////////////////////////////////////////////////////////////
        /** @brief Returns the SceneManager in use.
        **/
        ////////////////////////////////////////////////////////////
		const SceneManager& getSceneManager() const;
		
		////////////////////////////////////////////////////////////
        /** @brief Sets the SceneManager which will be used.
         *  @note This function copy the SceneManager, and so can be 
         *  very expensive.
        **/
        ////////////////////////////////////////////////////////////
		SceneManager& setSceneManager(const SceneManagerLocalPtr& scenemanager);
		
	private:
		
		Color                m_backgroundcolor; ///< @brief The background color.
		SceneManagerLocalPtr m_scenemanager;    ///< @brief Manages the Scene nodes.
	};
	
	typedef AutoPointer<Scene> ScenePtr;
}

#endif // APRO_SCENE_H
