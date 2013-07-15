/** @file LightSceneNode.h
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
#ifndef APROLIGHTSCENENODE_H
#define APROLIGHTSCENENODE_H
/*
#include "SceneNode.h"
#include "Light.h"

namespace APro
{
    class APRO_DLL LightSceneNode : public SceneNode
    {// Kind of proxy to class Light

        APRO_DECLARE_SHAREDPOINTER_CLASS_TYPEDEF(LightSceneNode)

    public:

        LightSceneNode(const String& mname);
        LightSceneNode(const String& mname,
                       const Color& ambient = Color((unsigned char) 0,0,0,255), const Color& diffuse = Color((unsigned char) 0,0,0,255),
                       const Color& specular = Color((unsigned char) 0,0,0,255),
                       const Vector3F& position = Vector3F(0,0,0) , const Vector3F& direction = Vector3F(1,0,0),
                       double exponent = 0.0, double angle = 180.0,
                       float cst_att = 1.0, float lin_att = 0.0, float quad_att = 0.0);
        LightSceneNode(const LightSceneNode& other);

        ~LightSceneNode();

    public:

        Light& get();
        const Light& get() const;

        void set(const Light& other);
        void set(const Color& ambient = Color((unsigned char) 0,0,0,255), const Color& diffuse = Color((unsigned char) 0,0,0,255),
                 const Color& specular = Color((unsigned char) 0,0,0,255),
                 const Vector3F& position = Vector3F(0,0,0) , const Vector3F& direction = Vector3F(1,0,0),
                 double exponent = 0.0, double angle = 180.0,
                 float cst_att = 1.0, float lin_att = 0.0, float quad_att = 0.0);

    protected:

        void draw(Renderer* renderer);
        void clear_intern();

    protected:

        Light light;
    };
}
*/
#endif
