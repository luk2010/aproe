////////////////////////////////////////////////////////////
/** @file Translatable.h
 *  @ingroup Core
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 05/07/2013
 *
 *  Defines the Translatable interface.
 *
**/
////////////////////////////////////////////////////////////
#ifndef APRO_TRANSLATABLE_H
#define APRO_TRANSLATABLE_H

#include "Platform.h"
#include "Vector3.h"

namespace APro
{
    ////////////////////////////////////////////////////////////
    /** @class Translatable
     *  @ingroup Core
     *  @brief An interface that describe a translatable object.
    **/
    ////////////////////////////////////////////////////////////
    class Translatable
    {
    public:

        Translatable() {}
        virtual ~Translatable() {}

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Translate the object.
        **/
        ////////////////////////////////////////////////////////////
        virtual void translate(const Vector3F& to) = 0;

        ////////////////////////////////////////////////////////////
        /** @brief Rotate the object.
        **/
        ////////////////////////////////////////////////////////////
        virtual void rotate(const Vector3F& axe, angle_t angle) = 0;
    };
}

#endif // APRO_TRANSLATABLE_H
