/** @file UntexturedMaterial.cpp
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 20/11/2012
 *
 *  @addtogroup Global
 *  @addtogroup Rendering
 *
 *  This file defines the UntexturedMaterial class.
 *
**/
#include "UntexturedMaterial.h"

namespace APro
{
    UntexturedMaterial::UntexturedMaterial()
        : name("NONAME")
    {
        reset();
    }

    UntexturedMaterial::UntexturedMaterial(const String& mname)
        : name(mname)
    {
        reset();
    }

    UntexturedMaterial::UntexturedMaterial(const String& mname, const UntexturedMaterial& other)
        : name(mname)
    {
        set(other);
    }

    const String& UntexturedMaterial::getName() const
    {
        return name;
    }

    const Color& UntexturedMaterial::getAmbient() const
    {
        return ambient;
    }

    Color& UntexturedMaterial::getAmbient()
    {
        return ambient;
    }

    const Color& UntexturedMaterial::getDiffuse() const
    {
        return diffuse;
    }

    Color& UntexturedMaterial::getDiffuse()
    {
        return diffuse;
    }

    const Color& UntexturedMaterial::getEmission() const
    {
        return emission;
    }

    Color& UntexturedMaterial::getEmission()
    {
        return emission;
    }

    float UntexturedMaterial::getShininess() const
    {
        return shininess;
    }

    void UntexturedMaterial::setAmbient(const Color& c)
    {
        ambient = c;
    }

    void UntexturedMaterial::setDiffuse(const Color& c)
    {
        diffuse = c;
    }

    void UntexturedMaterial::setAmbientAndDiffuse(const Color& c)
    {
        ambient = c;
        diffuse = c;
    }

    void UntexturedMaterial::setSpecular(const Color& c)
    {
        specular = c;
    }

    void UntexturedMaterial::setEmission(const Color& c)
    {
        emission = c;
    }

    void UntexturedMaterial::setShininess(const float& s)
    {
        shininess = s;
    }

    UntexturedMaterial& UntexturedMaterial::set(const UntexturedMaterial& other)
    {
        ambient = other.ambient;
        diffuse = other.diffuse;
        specular = other.specular;
        emission = other.emission;
        shininess = other.shininess;

        return *this;
    }

    UntexturedMaterial& UntexturedMaterial::reset()
    {
        ambient = Color(0.2f, 0.2f, 0.2f, 1.0f);
        diffuse = Color(0.8f, 0.8f, 0.8f, 1.0f);
        specular = Color(0.0f, 0.0f, 0.0f, 1.0f);
        emission = Color(0.0f, 0.0f, 0.0f, 1.0f);
        shininess = 0;

        return *this;
    }

    bool UntexturedMaterial::isEgal(const UntexturedMaterial& other) const
    {
        return ambient == other.ambient &&
            diffuse == other.diffuse &&
            specular == other.specular &&
            emission == other.emission &&
            shininess == other.shininess;
    }

    bool UntexturedMaterial::isDifferent(const UntexturedMaterial& other) const
    {
        return !isEgal(other);
    }

    bool UntexturedMaterial::operator == (const UntexturedMaterial& other) const
    {
        return isEgal(other);
    }

    bool UntexturedMaterial::operator != (const UntexturedMaterial& other) const
    {
        return isDifferent(other);
    }

    UntexturedMaterial& UntexturedMaterial::operator = (const UntexturedMaterial& other)
    {
        return set(other);
    }
}
