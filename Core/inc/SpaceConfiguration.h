/** @file SpaceConfiguration.h
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 03/10/2012
 *
 *  @addtogroup Global
 *  @addtogroup Rendering
 *
 *  This file defines the SpaceConfiguration class.
 *
**/
#ifndef APROSPACECONFIGURATION_H
#define APROSPACECONFIGURATION_H

#include "Platform.h"

#include "Vector3.h"
#include "Matrix4.h"

namespace APro
{
    typedef struct SpaceConfiguration
    {
        SpaceConfiguration()
            : position(0, 0), matrix(0)
        {
            matrix.toIdentity();
        }

        void scale(float scale)
        {
            matrix.scale(scale);
        }

        void translate(const Vector3F& v)
        {
            position.translate(v);
        }

        void rotate(const Vector3F& axe, double angle)
        {
            matrix.rotate(axe, angle);
        }

        Vector3F position;
        Matrix4F matrix;

    } SpaceConfiguration;
}

#endif
