/** @file RenderingContextSceneNode.cpp
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
#include "RenderingContextSceneNode.h"
/*
namespace APro
{
    RenderingContextSceneNode::RenderingContextSceneNode(const String& name)
        : SceneNode(name), attachedContext(nullptr), enabled(false), globalLight(name + String("_globalLight")), backgroundColor(),
        lsnm(nullptr), csnm(nullptr), esnm(nullptr)
    {
        init_managers();
    }

    RenderingContextSceneNode::RenderingContextSceneNode(const String& name, const Context::ptr& ctxt)
        : SceneNode(name), attachedContext(ctxt), enabled(false), globalLight(name + String("_globalLight")), backgroundColor(),
        lsnm(nullptr), csnm(nullptr), esnm(nullptr)
    {
        enabled = !attachedContext.isNull();
        init_managers();
    }

    RenderingContextSceneNode::RenderingContextSceneNode(const String& name, const RenderingContextSceneNode& other)
        : SceneNode(name, other), attachedContext(other.attachedContext), enabled(false),
        globalLight(name + String("_globalLight"), other.globalLight), backgroundColor(other.backgroundColor),
        lsnm(nullptr), csnm(nullptr), esnm(nullptr)
    {
        enabled = !attachedContext.isNull();
        init_managers();
    }

    RenderingContextSceneNode::~RenderingContextSceneNode()
    {

    }

    void RenderingContextSceneNode::setContext(const Context::readonlyptr& ctxt)
    {
        if(!attachedContext.isNull())
        {
            if(attachedContext->isBinded())
            {
                attachedContext->unbind();
            }
        }

        attachedContext = ctxt;

        if(attachedContext.isNull())
            enabled = false;
    }

    const Context::readonlyptr& RenderingContextSceneNode::getContext() const
    {
        return attachedContext;
    }

    Context::readonlyptr& RenderingContextSceneNode::getContext()
    {
        return attachedContext;
    }

    void RenderingContextSceneNode::enable(bool e)
    {
        if(!attachedContext.isNull())
        {
            enabled = e;
        }
        else
        {
            enabled = false;
        }
    }

    bool RenderingContextSceneNode::isEnabled() const
    {
        return enabled;
    }

    const LightSceneNode& RenderingContextSceneNode::getGlobalLight() const
    {
        return globalLight;
    }

    LightSceneNode& RenderingContextSceneNode::getGlobalLight()
    {
        return globalLight;
    }

    const Color& RenderingContextSceneNode::getBackgroundColor() const
    {
        return backgroundColor;
    }

    Color& RenderingContextSceneNode::getBackgroundColor()
    {
        return backgroundColor;
    }

    void RenderingContextSceneNode::addLightNode(const LightSceneNode::ptr& light)
    {
        if(!light.isNull())
        {
            lsnm->addLightNode(light);
        }
    }

    void RenderingContextSceneNode::addCameraNode(const CameraSceneNode::ptr& camera)
    {
        if(!camera.isNull())
        {
            csnm->addCameraNode(camera);
        }
    }

    void RenderingContextSceneNode::addEntityNode(const EntitySceneNode::ptr& entity)
    {
        if(!entity.isNull())
        {
            esnm->addEntityNode(entity);
        }
    }

    const LightSceneNode::ptr& RenderingContextSceneNode::getLightNode(const String& name) const
    {
        return lsnm->getLightNode(name);
    }

    LightSceneNode::ptr& RenderingContextSceneNode::getLightNode(const String& name)
    {
        return lsnm->getLightNode(name);
    }

    const CameraSceneNode::ptr& RenderingContextSceneNode::getCameraNode(const String& name) const
    {
        return csnm->getCameraNode(name);
    }

    CameraSceneNode::ptr& RenderingContextSceneNode::getCameraNode(const String& name)
    {
        return csnm->getCameraNode(name);
    }

    const EntitySceneNode::ptr& RenderingContextSceneNode::findEntityNode(const String& name) const
    {
        return esnm->getEntityNode(name);
    }

    EntitySceneNode::ptr& RenderingContextSceneNode::findEntityNode(const String& name)
    {
        return esnm->getEntityNode(name);
    }

    const EntitySceneNode::ptr& RenderingContextSceneNode::findLongEntityNode(const String& name) const
    {
        return esnm->getLongEntityNode(name);
    }

    EntitySceneNode::ptr& RenderingContextSceneNode::findLongEntityNode(const String& name)
    {
        return esnm->getLongEntityNode(name);
    }

    void RenderingContextSceneNode::removeLightNode(const String& name)
    {
        lsnm->removeLightNode(name);
    }

    void RenderingContextSceneNode::removeCameraNode(const String& name)
    {
        csnm->removeCameraNode(name);
    }

    void RenderingContextSceneNode::removeEntityNode(const String& name)
    {
        esnm->removeEntityNode(name);
    }

    void RenderingContextSceneNode::draw(Renderer* renderer)
    {
        if(renderer && isEnabled() && !attachedContext.isNull())
        {
            attachedContext->bind();

            for(size_t i = 0; i < attachedContext->getNumViewPorts(); ++i)
            {
                ViewPort::ptr& v = attachedContext->getViewPort(i);

                // TODO : Need to have a method to render nodes..


            }

            attachedContext->unbind();
        }
    }

    void RenderingContextSceneNode::clear_intern()
    {
        lsnm = nullptr;
        csnm = nullptr;
        esnm = nullptr;
        attachedContext = nullptr;
        enabled = false;
        globalLight.reset();
        backgroundColor.set(0,0,0,0);
    }

    void RenderingContextSceneNode::init_managers()
    {
        lsnm = AProNew(1, LightSceneNodeManager) ();
        SceneNode::addChild(LightSceneNodeManager::ptr(lsnm));

        csnm = AProNew(1, CameraSceneNodeManager) ();
        SceneNode::addChild(CameraSceneNodeManager::ptr(csnm));

        esnm = AProNew(1, EntitySceneNodeManager) ();
        SceneNode::addChild(EntitySceneNodeManager::ptr(esnm));
    }
}
*/
