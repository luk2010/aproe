/** @file LightSceneNodeManager.h
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 20/10/2012
 *
 *  @addtogroup Global
 *  @addtogroup Rendering
 *
 *  This file defines the LightSceneNodeManager class.
 *
**/
#ifndef APROLIGHTSCENENODEMANAGER_H
#define APROLIGHTSCENENODEMANAGER_H
/*
#include "LightSceneNode.h"

namespace APro
{
    class LightSceneNodeManager : public SceneNode
    {
        APRO_DECLARE_SHAREDPOINTER_CLASS_TYPEDEF(LightSceneNodeManager)

    public:

        LightSceneNodeManager(const String& name)
            : SceneNode(name)
        {

        }

        LightSceneNodeManager(const String& name, const LightSceneNodeManager& other)
            : SceneNode(name, other)
        {

        }

        ~LightSceneNodeManager()
        {

        }

    public:

        LightSceneNode::ptr& getLightNode(size_t index)
        {
            return spCast<LightSceneNode::ptr, SceneNode::ptr>(childs.at(index));
        }

        const LightSceneNode::ptr& getLightNode(size_t index) const
        {
            return spCast<LightSceneNode::ptr, SceneNode::ptr>(childs.at(index));
        }

        LightSceneNode::ptr& getLightNode(const String& name)
        {
            return spCast<LightSceneNode::ptr, SceneNode::ptr>(SceneNode::findChild(name));
        }

        const LightSceneNode::ptr& getLightNode(const String& name) const
        {
            return spCast<LightSceneNode::ptr, SceneNode::ptr>(SceneNode::findChild(name));
        }

    public:

        void addLightNode(const LightSceneNode::ptr& light)
        {
            SceneNode::addChild(light);
        }

        void addLightNodes(const List<LightSceneNode::ptr>& lights)
        {
            SceneNode::addChilds(lights);
        }

        void removeLightNode(const String& name)
        {
            SceneNode::removeChild(SceneNode::findChild(name));
        }

        void removeLightNode(const LightSceneNode::ptr& light)
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
