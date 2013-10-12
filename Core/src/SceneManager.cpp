////////////////////////////////////////////////////////////
/** @file SceneManager.h
 *  @ingroup Rendering
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 12/05/2013
 *
 *  Defines the Scene Manager object.
 *
**/
////////////////////////////////////////////////////////////
#include "SceneManager.h"

namespace APro
{
    SceneManager::SceneManager()
        : m_scenes(Manager<Scene>::objects)
    {

    }

    SceneManager::SceneManager(const SceneManager& other)
        : m_scenes(Manager<Scene>::objects)
    {
        copyFrom(other);
    }

    SceneManager::~SceneManager()
    {
        clear();
    }

    void SceneManager::copyFrom(const SceneManager& other)
    {
        APRO_THREADSAFE_AUTOLOCK

        clear();
        m_scenes = other.m_scenes;
    }

    bool SceneManager::operator == (const SceneManager& other) const
    {
        return false;
    }

    Scene::ptr SceneManager::createScene(const String& scene_name) const
    {
        return Scene::ptr(AProNew(Scene, scene_name));
    }

    Scene::ptr SceneManager::createAndAddScene(const String& scene_name)
    {
        Scene::ptr tmp_scene = getScene(scene_name);
        if(tmp_scene.isNull())
        {
            tmp_scene = createScene(scene_name);
            if(tmp_scene.isNull())
            {
                Console::get() << "\n[SceneManager]{createAndAddScene} Can't create scene \"" << scene_name << "\".";
            }
            else
            {
                Console::get() << "\n[SceneManager]{createAndAddScene} Scene \"" << scene_name << "\" successfully created.";

                APRO_THREADSAFE_AUTOLOCK

                push(tmp_scene);
            }
        }
        else
        {
            Console::get() << "\n[SceneManager]{createAndAddScene} Scene \"" << scene_name << "\" already exists so cannot be re-created !";
        }

        return tmp_scene;
    }

    Scene::ptr SceneManager::getScene(const String& scene_name)
    {
        APRO_THREADSAFE_AUTOLOCK

        for(unsigned int i = 0; i < m_scenes.size(); ++i)
        {
            if(m_scenes.at(i).getName() == scene_name)
            {
                return m_scenes.at(i);
            }
        }

        return Scene::ptr;
    }

    void SceneManager::removeScene(const String& scene_name)
    {
        Scene::ptr tmp_scene = getScene(scene_name);
        if(scene_name.isNull())
        {
            Console::get() << "\n[SceneManager]{createAndAddScene} Scene \"" << scene_name << "\" already removed.";
        }
        else
        {
            APRO_THREADSAFE_AUTOLOCK

            m_scenes.erase(m_scenes.find(tmp_scene));
        }
    }

    bool SceneManager::hasScene(const String& scene_name) const
    {
        for(unsigned int i = 0; i < m_scenes.size(); ++i)
        {
            if(m_scenes.at(i).getName() == scene_name)
            {
                return true;
            }
        }

        return false;
    }
}
