/** @file SceneNodeManager.h
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 03/10/2012
 *
 *  @addtogroup Global
 *  @addtogroup Rendering
 *
 *  This file defines the SceneNodeManager class.
 *
**/
#ifndef APROSCENENODEMANAGER_H
#define APROSCENENODEMANAGER_H
/*
#include "Platform.h"
#include "SceneNode.h"
#include "NodeManager.h"
#include "RenderingContextSceneNode.h"

namespace APro
{
    class APRO_DLL SceneNodeManager : public NodeManager<SceneNode>
    {
        APRO_DECLARE_SHAREDPOINTER_CLASS_TYPEDEF(SceneNodeManager)

    public:

        SceneNodeManager();

        virtual ~SceneNodeManager();

    public:

        SceneNode::ptr createEmptyNode(const String& name) const;

        RenderingContextSceneNode::ptr createRenderingContextNode(const String& name, const Context::ptr& ctxt) const;
        CameraSceneNode::ptr createCameraNode(const String& name,
                                              const Vector3F& position = Vector3F(0,0,0) ,
                                              const Vector3F& direction = Vector3F(1,0,0)) const;
        LightSceneNode::ptr createLightNode(const String& name,
                                            const Color& ambient = Color(0,0,0,255), const Color& diffuse = Color(0,0,0,255),
                                            const Color& specular = Color(0,0,0,255),
                                            const Vector3F& position = Vector3F(0,0,0) , const Vector3F& direction = Vector3F(1,0,0),
                                            double exponent = 0.0, double angle = 180.0,
                                            float cst_att = 1.0, float lin_att = 0.0, float quad_att = 0.0) const;
        EntitySceneNode::ptr createEntityNode(const String& name, const Entity::ptr& entity) const;
    };
}
*/
#endif
