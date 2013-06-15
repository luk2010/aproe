////////////////////////////////////////////////////////////
/** @file Scene.h
 *  @ingroup Rendering
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 12/05/2013
 *
 *  Defines the Scene object.
 *
**/
////////////////////////////////////////////////////////////
#ifndef APRO_SCENE_H
#define APRO_SCENE_H

#include "Platform.h"
#include "SharedPointer.h"
#include "NonCopyable.h"
#include "SString.h"
#include "SceneNode.h"

namespace APro
{
    class APRO_DLL Scene : public NonCopyable
    {
        APRO_DECLARE_SHAREDPOINTER_CLASS_TYPEDEF(Scene)

    private:

        String m_name;
        SceneTree m_scene_tree;

        typedef List<LightSceneNode*> LightNodeList;
        typedef List<CameraSceneNode*> CameraNodeList;
        typedef List<ViewPortSceneNode*> ViewPortNodelist;

        LightNodeList m_light_nodes;
        CameraNodeList m_camera_nodes;
        ViewPortNodelist m_viewport_nodes;

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Constructor.
         *  @param name : Name of the scene.
        **/
        ////////////////////////////////////////////////////////////
        Scene(const String& name);

        ////////////////////////////////////////////////////////////
        /** @brief Destructor.
        **/
        ////////////////////////////////////////////////////////////
        ~Scene();

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Return the name of this scene.
        **/
        ////////////////////////////////////////////////////////////
        const String& getName() const;

        ////////////////////////////////////////////////////////////
        /** @brief Return the name of this scene.
        **/
        ////////////////////////////////////////////////////////////
        String& getName();

    public:

        SceneNode* createSceneNode(Light* light);

    };
}

#endif // APRO_SCENE_H
