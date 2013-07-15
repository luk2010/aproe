/** @file EntitySceneNodeManager.h
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 20/10/2012
 *
 *  @addtogroup Global
 *  @addtogroup Rendering
 *
 *  This file defines the EntitySceneNodeManager class.
 *
**/
#ifndef APROENTITYSCENENODEMANAGER_H
#define APROENTITYSCENENODEMANAGER_H
/*
#include "EntitySceneNode.h"

namespace APro
{
    class EntitySceneNodeManager : public SceneNode
    {
        APRO_DECLARE_SHAREDPOINTER_CLASS_TYPEDEF(EntitySceneNodeManager)

    public:

        EntitySceneNodeManager(const String& name)
            : SceneNode(name)
        {

        }

        EntitySceneNodeManager(const String& name, const EntitySceneNodeManager& other)
            : SceneNode(name, other)
        {

        }

        ~EntitySceneNodeManager()
        {

        }

    public:

        EntitySceneNode::ptr& getEntityNode(size_t index)
        {
            return spCast<EntitySceneNode::ptr, SceneNode::ptr>(childs.at(index));
        }

        const EntitySceneNode::ptr& getEntityNode(size_t index) const
        {
            return spCast<EntitySceneNode::ptr, SceneNode::ptr>(childs.at(index));
        }

        EntitySceneNode::ptr& getEntityNode(const String& name)
        {
            return spCast<EntitySceneNode::ptr, SceneNode::ptr>(SceneNode::findChild(name));
        }

        const EntitySceneNode::ptr& getEntityNode(const String& name) const
        {
            return spCast<EntitySceneNode::ptr, SceneNode::ptr>(SceneNode::findChild(name));
        }

        EntitySceneNode::ptr& getLongEntityNode(const String& name)
        {
            return spCast<EntitySceneNode::ptr, SceneNode::ptr>(SceneNode::findLongChild(name));
        }

        const EntitySceneNode::ptr& getLongEntityNode(const String& name) const
        {
            return spCast<EntitySceneNode::ptr, SceneNode::ptr>(SceneNode::findLongChild(name));
        }

    public:

        void addEntityNode(const EntitySceneNode::ptr& entity)
        {
            SceneNode::addChild(entity);
        }

        void addEntityNodes(const List<EntitySceneNode::ptr>& entities)
        {
            SceneNode::addChilds(entities);
        }

        void removeEntityNode(const String& name)
        {
            SceneNode::removeChild(SceneNode::findChild(name));
        }

        void removeEntityNode(const EntitySceneNode::ptr& light)
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
