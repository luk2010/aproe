////////////////////////////////////////////////////////////
/** @file Plane.cpp
 *  @ingroup Maths
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 09/06/2014
 *
 *  Defines the Plane class.
 *
**/
////////////////////////////////////////////////////////////
#include "Plane.h"

namespace APro
{
    Plane::Plane()
    {

    }

    Plane::Plane(const Vector3& normal_, Real d_)
        : normal(normal_), d(d_)
    {
        aproassert1(normal.isNormalized());
    }

    Plane::Plane(const Vector3& v1, const Vector3& v2, const Vector3& v3)
    {
        set(v1, v2, v3);
    }

    Plane::Plane(const Vector3& point, const Vector3& normal)
    {
        set(point, normal);
    }

    Plane::~Plane()
    {

    }

    void Plane::set(const Vector3& v1, const Vector3& v2, const Vector3& v3)
    {
        normal = (v2-v1).cross(v3-v1);

        Real len = normal.lenght();
        aproassert1(len > 1e-10f);

        normal /= len;
        aproassert1(normal.isNormalized());
        d = normal.dot(v1);
    }

    void Plane::set(const Vector3& point_, const Vector3& normal_)
    {
        normal = normal_;
        aproassert1(normal.isNormalized());
        d = point_.dot(normal);
    }

    bool Plane::passesThroughOrigin(Real epsilon) const
    {
        return Math::Abs(d) <= epsilon;
    }
}
