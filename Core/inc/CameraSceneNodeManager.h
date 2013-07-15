/** @file CameraSceneNodeManager.h
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 20/10/2012
 *
 *  @addtogroup Global
 *  @addtogroup Rendering
 *
 *  This file defines the CameraSceneNodeManager class.
 *
**/
#ifndef APROCAMERASCENENODEMANAGER_H
#define APROCAMERASCENENODEMANAGER_H
/*
#include "CameraSceneNode.h"

namespace APro
{
    class CameraSceneNodeManager : public SceneNode
    {
        APRO_DECLARE_SHAREDPOINTER_CLASS_TYPEDEF(CameraSceneNodeManager)

    public:

        CameraSceneNodeManager(const String& name)
            : SceneNode(name)
        {

        }

        CameraSceneNodeManager(const String& name, const CameraSceneNodeManager& other)
            : SceneNode(name, other)
        {

        }

        ~CameraSceneNodeManager()
        {

        }

    public:

        CameraSceneNode::ptr& getCameraNode(size_t index)
        {
            return spCast<CameraSceneNode::ptr, SceneNode::ptr>(childs.at(index));
        }

        const CameraSceneNode::ptr& getCameraNode(size_t index) const
        {
            return spCast<CameraSceneNode::ptr, SceneNode::ptr>(childs.at(index));
        }

        CameraSceneNode::ptr& getCameraNode(const String& name)
        {
            return spCast<CameraSceneNode::ptr, SceneNode::ptr>(SceneNode::findChild(name));
        }

        const CameraSceneNode::ptr& getCameraNode(const String& name) const
        {
            return spCast<CameraSceneNode::ptr, SceneNode::ptr>(SceneNode::findChild(name));
        }

    public:

        void addCameraNode(const CameraSceneNode::ptr& camera)
        {
            SceneNode::addChild(camera);
        }

        void addCameraNodes(const List<CameraSceneNode::ptr>& cameras)
        {
            SceneNode::addChilds(cameras);
        }

        void removeCameraNode(const String& name)
        {
            SceneNode::removeChild(SceneNode::findChild(name));
        }

        void removeCameraNode(const CameraSceneNode::ptr& light)
        {
            SceneNode::removeChild(light);
        }

    protected:

        void draw(Renderer* renderer)
        {

        }
    };
}
*/
#endif
