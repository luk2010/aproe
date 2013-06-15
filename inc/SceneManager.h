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
#ifndef APRO_SCENEMANAGER_H
#define APRO_SCENEMANAGER_H

#include "Platform.h"
#include "Manager.h"
#include "ThreadSafe.h"
#include "Scene.h"
#include "Copyable.h"

namespace APro
{
    ////////////////////////////////////////////////////////////
    /** @class SceneManager
     *  @ingroup Rendering
     *  @brief Manages the Scenes in the renderer.
     *  @details The SceneManager exists in every Renderer. It is a
     *  manager to help manages the different Scenes in a rendering
     *  context.
     *
     *  @note The scenes are not guaranteed to be destroyed when
     *  they are removed from the SceneManager. Whereas it uses
     *  SharedPointer, if another SceneManager use the Scene, it won't
     *  be destroyed when removed from this one.
     *  @note This class is designed to be Thread-Safe.
    **/
    ////////////////////////////////////////////////////////////
    class APRO_DLL SceneManager : public Manager<Scene>,
                                  public ThreadSafe,
                                  public Copyable<SceneManager>
    {
        /*
            The scene manager is constitued by :

            SceneManager
                ---------> SceneList -----> Scene -----> ViewPorts
                                                  -----> SceneNodes
                                                  -----> Lights

        */

    public:

        typedef List<Scene::ptr> SceneList;

    protected:

        SceneList& m_scenes;///< Scenes.

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Default Constructor.
        **/
        ////////////////////////////////////////////////////////////
        SceneManager();

        ////////////////////////////////////////////////////////////
        /** @brief Copy Constructor.
        **/
        ////////////////////////////////////////////////////////////
        SceneManager(const SceneManager& other);

        ////////////////////////////////////////////////////////////
        /** @brief Destructor.
        **/
        ////////////////////////////////////////////////////////////
        ~SceneManager();

        ////////////////////////////////////////////////////////////
        /** @see Copyable::copyFrom
        **/
        ////////////////////////////////////////////////////////////
        void copyFrom(const SceneManager& other);

        /////////////////////////////////////////////////////////////
        /** @see Copyable::operator==
         *  @note No SceneManager are the same, so it returns
         *  always false.
        **/
        /////////////////////////////////////////////////////////////
        bool operator == (const SceneManager& other) const;

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Create a Scene.
         *  @details The Scene isn't stored in this SceneManager. You
         *  can store it in anyone you want.
         *
         *  @param scene_name : Name of the Scene created.
         *  @return A pointer to this Scene.
        **/
        ////////////////////////////////////////////////////////////
        Scene::ptr createScene(const String& scene_name) const;

        ////////////////////////////////////////////////////////////
        /** @brief Create a Scene and Stores it in the SceneManager.
         *  @details If the Scene name given already exists in the
         *  SceneManager, this function will return the current Scene
         *  corresponding to this name.
         *
         *  @param scene_name : Name of the Scene created.
         *  @return A pointer to this Scene.
        **/
        ////////////////////////////////////////////////////////////
        Scene::ptr createAndAddScene(const String& scene_name);

        ////////////////////////////////////////////////////////////
        /** @brief Return the Scene corresponding to given name.
         *
         *  @param scene_name : Name of the Scene returned.
         *  @return A pointer to this Scene.
        **/
        ////////////////////////////////////////////////////////////
        Scene::ptr getScene(const String& scene_name);

        ////////////////////////////////////////////////////////////
        /** @brief Remove the Scene corresponding to given name.
         *  @note If the Scene is used by another SceneManager, it
         *  won't be destroyed here.
         *
         *  @param scene_name : Name of the Scene to remove.
        **/
        ////////////////////////////////////////////////////////////
        void removeScene(const String& scene_name);

        ////////////////////////////////////////////////////////////
        /** @brief Return if the SceneManager has this scene.
         *  @return has this scene.
        **/
        ////////////////////////////////////////////////////////////
        bool hasScene(const String& scene_name) const;
    };
}

#endif // APRO_SCENEMANAGER_H
