/** @file RenderingContextSceneNode.h
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 20/10/2012
 *
 *  @addtogroup Global
 *  @addtogroup Rendering
 *
 *  This file defines the RenderingContextSceneNode class.
 *
**/
#ifndef APRORENDERINGCONTEXTSCENENODE_H
#define APRORENDERINGCONTEXTSCENENODE_H
/*
#include "SceneNode.h"
#include "Context.h"
#include "LightSceneNodeManager.h"
#include "CameraSceneNodeManager.h"
#include "EntitySceneNodeManager.h"

namespace APro
{
    class Renderer;

    class APRO_DLL RenderingContextSceneNode : public SceneNode
    {
        APRO_DECLARE_SHAREDPOINTER_CLASS_TYPEDEF(RenderingContextSceneNode)

    public:

        RenderingContextSceneNode(const String& name);
        RenderingContextSceneNode(const String& name, const Context::ptr& ctxt);
        RenderingContextSceneNode(const String& name, const RenderingContextSceneNode& other);

        virtual ~RenderingContextSceneNode();

    public:

        void setContext(const Context::readonlyptr& ctxt);
        const Context::readonlyptr& getContext() const;
        Context::readonlyptr& getContext() const;

        void enable(bool e);
        bool isEnabled() const;

    public:

        const LightSceneNode& getGlobalLight() const;
        LightSceneNode& getGlobalLight();

        const Color& getBackgroundColor() const;
        Color& getBackgroundColor();

    public:

        void addLightNode(const LightSceneNode::ptr& light);
        void addCameraNode(const CameraSceneNode::ptr& camera);
        void addEntityNode(const EntitySceneNode::ptr& entity);

        const LightSceneNode::ptr& getLightNode(const String& name) const;
        LightSceneNode::ptr& getLightNode(const String& name);

        const CameraSceneNode::ptr& getCameraNode(const String& name) const;
        CameraSceneNode::ptr& getCameraNode(const String& name);

        const EntitySceneNode::ptr& findEntityNode(const String& name) const;
        EntitySceneNode::ptr& findEntityNode(const String& name);
        const EntitySceneNode::ptr& findLongEntityNode(const String& name) const;
        EntitySceneNode::ptr& findLongEntityNode(const String& name);

        void removeLightNode(const String& name);
        void removeCameraNode(const String& name);
        void removeEntityNode(const String& name);

    protected:

        virtual void draw(Renderer* renderer) const;
        virtual void clear_intern();

    private:

        void init_managers();

    protected:

        Context::readonlyptr attachedContext;
        bool enabled;
        LightSceneNode globalLight;
        Color backgroundColor;

        LightSceneNodeManager* lsnm;
        CameraSceneNodeManager* csnm;
        EntitySceneNodeManager* esnm;
    };
}
*/
#endif
