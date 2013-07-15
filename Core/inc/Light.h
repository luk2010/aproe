////////////////////////////////////////////////////////////
/** @file Light.h
 *  @ingroup Rendering
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 26/10/2012
 *
 *  Defines the Light class.
 *
**/
////////////////////////////////////////////////////////////
#ifndef APROLIGHT_H
#define APROLIGHT_H

#include "Platform.h"
#include "Color.h"
#include "Vector3.h"
#include "SharedPointer.h"
#include "Copyable.h"

namespace APro
{
    ////////////////////////////////////////////////////////////
    /** @class Light
     *  @ingroup Rendering
     *  @brief represents a light object.
     *  @details This structure is used to define a light.
    **/
    ////////////////////////////////////////////////////////////
    class Light : public Copyable<Light>
    {
        APRO_DECLARE_SHAREDPOINTER_CLASS_TYPEDEF(Light)

    public:

        class Type
        {
        public:
            enum t
            {
                Point,///< A light that emit in every directions.
                Directionnal,///< A directionnal light.
                SpotLight///< A spotlight.
            };
        };

        struct LightData
        {
            Color ambient;///< Ambient color of this light.
            Color diffuse;///< Diffuse color.
            Color specular;///< Specular color.

            Vector3F position;///< Position of this light.
            Vector3F direction;///< Direction of the light. Doesn't affect Point lights.

            double exponent;///< Exponent of the light.
            double innerAngle;///< Inner angle. Affects only spotlight.
            double outerAngle;///< Outer angle. Affects only spotlight.

            float attenuationConstant;///< Constant attenuation of this light.
            float attenuationLinear;///< Linear attenuation of this light.
            float attenuationQuadric;///< Quadric attenuation of this light.

            float spotLightFallOff;///< Spot light fall off. Affects only spotlight.

            Type::_ type;///< Light type.
        };

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Constructor.
        **/
        ////////////////////////////////////////////////////////////
        Light();

        ////////////////////////////////////////////////////////////
        /** @brief Copy Constructor.
         *  @param other : Light to copy.
        **/
        ////////////////////////////////////////////////////////////
        Light(const Light& other);

        ////////////////////////////////////////////////////////////
        /** @brief Data Constructor.
         *  @param light_data : Data for the light.
        **/
        ////////////////////////////////////////////////////////////
        Light(const LightData& light_data);

        ////////////////////////////////////////////////////////////
        /** @brief Destructor.
        **/
        ////////////////////////////////////////////////////////////
        ~Light();

    public:

        void copyFrom(const Light& other);
        bool operator == (const Light& other) const;

    protected:

        LightData m_data;

    public:

        void setData(const LightData& data);
        const LightData& getData() const;
        LightData& getData();

    };
}

#endif
