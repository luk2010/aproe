/** @file UntexturedMaterial.h
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 17/11/2012
 *
 *  @addtogroup Global
 *  @addtogroup Rendering
 *
 *  This file defines the UntexturedMaterial class.
 *
**/
#ifndef APRO_UNTEXTUREDMATERIAL_H
#define APRO_UNTEXTUREDMATERIAL_H

#include "Platform.h"
#include "Color.h"
#include "SharedPointer.h"

namespace APro
{
    class APRO_DLL UntexturedMaterial
    {
        APRO_DECLARE_SHAREDPOINTER_CLASS_TYPEDEF(UntexturedMaterial)

    public:

        UntexturedMaterial();
        UntexturedMaterial(const String& mname);
        UntexturedMaterial(const String& mname, const UntexturedMaterial& other);

        ~UntexturedMaterial();

    public:

        const String& getName() const;

        const Color& getAmbient() const;
        Color& getAmbient();

        const Color& getDiffuse() const;
        Color& getDiffuse();

        const Color& getSpecular() const;
        Color& getSpecular();

        const Color& getEmission() const;
        Color& getEmission();

        float getShininess() const;

    public:

        void setAmbient(const Color& c);
        void setDiffuse(const Color& c);
        void setAmbientAndDiffuse(const Color& c);
        void setSpecular(const Color& c);
        void setEmission(const Color& c);
        void setShininess(const float& s);

    public:

        UntexturedMaterial& set(const UntexturedMaterial& other);
        UntexturedMaterial& reset();

        bool isEgal(const UntexturedMaterial& other) const;
        bool isDifferent(const UntexturedMaterial& other) const;

    public:

        bool operator == (const UntexturedMaterial& other) const;
        bool operator != (const UntexturedMaterial& other) const;

        UntexturedMaterial& operator = (const UntexturedMaterial& other);

    protected:

        String name;

        Color ambient;
        Color diffuse;
        Color specular;
        Color emission;

        float shininess;
    };
}

#endif
