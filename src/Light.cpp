/** @file Light.cpp
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 26/10/2012
 *
 *  @addtogroup Global
 *  @addtogroup Rendering
 *
 *  This file defines the Light class.
 *
**/
#include "Light.h"

namespace APro
{
    Light::Light()
    {

    }

    Light::Light(const Light& other)
    {
        copyFrom(other);
    }

    Light::Light(const Light::LightData& data)
    {
        setData(data);
    }

    Light::~Light()
    {

    }

    void Light::copyFrom(const Light& other)
    {
        setData(other.getData());
    }

    bool Light::operator==(const Light& other) const
    {

    }

}
