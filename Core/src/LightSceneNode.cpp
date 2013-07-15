/** @file LightSceneNode.cpp
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 26/10/2012
 *
 *  @addtogroup Global
 *  @addtogroup Rendering
 *
 *  This file defines the LightSceneNode class.
 *
**/
#include "LightSceneNode.h"
#include "Renderer.h"
/*
namespace APro
{
    LightSceneNode::LightSceneNode(const String& mname)
        : SceneNode(mname)
    {
        light.reset();
    }

    LightSceneNode::LightSceneNode(const String& mname,
                       const Color& ambient, const Color& diffuse, const Color& specular,
                       const Vector3F& position, const Vector3F& direction,
                       double exponent, double angle, float cst_att, float lin_att, float quad_att)
        : SceneNode(mname)
    {
        light.set(ambient, diffuse, specular, position, direction, exponent, angle, cst_att, lin_att, quad_att);
    }

    LightSceneNode::LightSceneNode(const LightSceneNode& other)
        : SceneNode(other), light(other.light)
    {

    }

    LightSceneNode::~LightSceneNode()
    {

    }

    Light& LightSceneNode::get()
    {
        return light;
    }

    const Light& LightSceneNode::get() const
    {
        return light;
    }

    void LightSceneNode::set(const Light& other)
    {
        light = other;
    }

    void LightSceneNode::set(const Color& ambient, const Color& diffuse, const Color& specular,
                       const Vector3F& position, const Vector3F& direction,
                       double exponent, double angle, float cst_att, float lin_att, float quad_att)
    {
        light.set(ambient, diffuse, specular, position, direction, exponent, angle, cst_att, lin_att, quad_att);
    }

    void LightSceneNode::draw(Renderer* renderer)
    {

    }

    void LightSceneNode::clear_intern()
    {
        light.reset();
    }
}

*/
