////////////////////////////////////////////////////////////
/** @file Plane.h
 *  @ingroup Maths
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 05/05/2014 - 09/06/2014
 *
 *  Defines the Plane class.
 *
**/
////////////////////////////////////////////////////////////
#ifndef APRO_PLANE_H
#define APRO_PLANE_H

#include "Platform.h"
#include "Vector3.h"

namespace APro
{
    ////////////////////////////////////////////////////////////
    /** @class Plane
     *  @ingroup Maths
     *  @brief An object representing a plane in 3D space.
     *
     *  Its sides extend to infinity, and it does not necessarily
     *  pass through the origin.
     *
     *  ### A note on the ::d param
     *
     *  The value -d gives the signed distance of this plane from origin.
     *  Denoting normal=(a,b,c), this class uses the convention ax+by+cz = d,
     *  which means that:
     *  - If this variable is positive, the vector space origin (0,0,0) is
     *    on the negative side of this plane.
     *  - If this variable is negative, the vector space origin (0,0,0) is
     *    on the on the positive side of this plane.
     *
     *  @note Some sources use the opposite convention ax+by+cz+d = 0 to define
     *  the variable d. When comparing equations and algorithm regarding planes,
     *  always make sure you know which convention is being used, since it affects
     *  the sign of d.
    **/
    ////////////////////////////////////////////////////////////
    class Plane
    {
    public:

        Vector3 normal; ///< The direction this plane is facing at. @note This direction vector is always normalized.
                        ///  If you assign to this directly, please remember to only assign normalized direction
                        ///  vectors.

        Real d; ///< The offset of this plane from the origin.

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Default constructor.
         *
         *  This constructor doesn't initialize anything so value
         *  normal and d are not guarenteed to be 0.
        **/
        ////////////////////////////////////////////////////////////
        Plane();

        ////////////////////////////////////////////////////////////
        /** @brief Constructs a plane from its normal and d factor.
         *
         *  @param normal : The direction the plane is facing. This
         *  vector must have been normalized in advance.
         *  @param d : The offset of this plane from the origin. The
         *  value -d gives the signed distance of this plane from the
         *  origin.
        **/
        ////////////////////////////////////////////////////////////
        Plane(const Vector3& normal, Real d);

        ////////////////////////////////////////////////////////////
        /** @brief Constructs a plane.
         *
         *  The normal of the plane will point to the halfspace from
         *  which the points are observed to be oriented in counter-clockwise
         *  order.
         *  @note The points v1, v2 and v3 must not all lie on the same
         *  line.
        **/
        ////////////////////////////////////////////////////////////
        Plane(const Vector3& v1, const Vector3& v2, const Vector3& v3);

        ////////////////////////////////////////////////////////////
        /** @brief Constructs a plane by specifying a single point on
         *  the plane, and the surface normal.
         *
         *  @param normal : The direction the plane is facing. This
         *  vector must have been normalized in advance.
        **/
        ////////////////////////////////////////////////////////////
        Plane(const Vector3& point, const Vector3& normal);

        ////////////////////////////////////////////////////////////
        /** @brief Destructs the Plane object.
        **/
        ////////////////////////////////////////////////////////////
        ~Plane();

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Sets this plane by specifying three points on the
         *  plane.
         *
         *  The normal of the plane will point to the halfspace from
         *  which the points are observed to be oriented in counter-clockwise
         *  order.
         *  @note The points v1, v2 and v3 must not all lie on the same
         *  line.
        **/
        ////////////////////////////////////////////////////////////
        void set(const Vector3& v1, const Vector3& v2, const Vector3& v3);

        ////////////////////////////////////////////////////////////
        /** @brief Sets this plane by specifying a single point on
         *  the plane, and the surface normal.
         *
         *  @param normal : The direction the plane is facing. This
         *  vector must have been normalized in advance.
        **/
        ////////////////////////////////////////////////////////////
        void set(const Vector3& point, const Vector3& normal);

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Returns true if this plane passes through the
         *  origin.
         *  @note A plane passes through the origin if and only if
         *  d == 0 for the plane.
        **/
        ////////////////////////////////////////////////////////////
        bool passesThroughOrigin(Real epsilon = 1e-3f) const;
    };
}

#endif // APRO_PLANE_H
