////////////////////////////////////////////////////////////
/** @file Vector3.cpp
 *  @ingroup Maths
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 11/09/2013
 *
 *  Implements the Vector3 class.
 *
**/
////////////////////////////////////////////////////////////

#include "Vector3.h"

namespace APro
{
    Vector3::Vector3() : x (0), y (0), z (0)
    {

    }

    Vector3::Vector3(const Vector3& v) : x (v.x), y(v.y), z(v.z)
    {

    }

    Vector3::Vector3(Real n1, Real n2, Real n3) : x(n1), y(n2), z(n3)
    {

    }

    Vector3::Vector3(Real n) : x(n), y(n), z(n)
    {

    }

    Vector3::Vector3(const Real v[3]) : x(v[0]), y(v[1]), z(v[2])
    {

    }

    void Vector3::swap(Vector3& v)
    {
        swapNumeric_xor(x, v.x);
        swapNumeric_xor(y, v.y);
        swapNumeric_xor(z, v.z);
    }

    bool Vector3::equals(const Vector3& v) const
    {
        return *this == v;
    }

    bool Vector3::equals(const Real& n1, const Real& n2) const
    {
        return n1 == x && n2 == y;
    }

    Vector3& Vector3::set(const Vector3& other)
    {
        x = other.x;
        y = other.y;
        z = other.z;
        return *this;
    }

    Vector3& Vector3::set(const Real& n1, const Real& n2, const Real& n3)
    {
        x = n1;
        y = n2;
        z = n3;
        return *this;
    }

    Vector3& Vector3::set(const Real& n)
    {
        x = n;
        y = x;
        z = x;
        return *this;
    }

    void Vector3::floor(const Vector3& other)
    {
        if(other.x < x) x = other.x;
        if(other.y < y) y = other.y;
        if(other.z < z) z = other.z;
    }

    void Vector3::ceil(const Vector3& other)
    {
        if(other.x > x) x = other.x;
        if(other.y > y) y = other.y;
        if(other.z > z) z = other.z;
    }

    Vector3& Vector3::add(const Vector3& v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    Vector3& Vector3::add(const Real& n)
    {
        x += n;
        y += n;
        z += n;
        return *this;
    }

    Vector3 Vector3::added(const Vector3& v) const
    {
        return Vector3(x + v.x,
                        y + v.y,
                        z + v.z);
    }

    Vector3 Vector3::added(const Real& n) const
    {
        return Vector3(x + n,
                        y + n,
                        z + n);
    }

    Vector3& Vector3::sub(const Vector3& v)
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;

        return *this;
    }

    Vector3& Vector3::sub(const Real& n)
    {
        x -= n;
        y -= n;
        z -= n;

        return *this;
    }

    Vector3 Vector3::subbed(const Vector3& v) const
    {
        return Vector3(x - v.x, y - v.y, z - v.z);
    }

    Vector3 Vector3::subbed(const Real& n) const
    {
        return Vector3(x - n,
                        y - n,
                        z - n);
    }

    Vector3& Vector3::multiply(const Vector3& v)
    {
        x *= v.x;
        y *= v.y;
        z *= v.z;

        return *this;
    }

    Vector3& Vector3::multiply(const Real& n)
    {
        x *= n;
        y *= n;
        z *= n;

        return *this;
    }

    Vector3 Vector3::multiplied(const Vector3& v) const
    {
        return Vector3(x *= v.x,
                        y *= v.y,
                        z *= v.z);
    }

    Vector3 Vector3::multiplied(const Real& n) const
    {
        return Vector3(x *= n,
                        y *= n,
                        z *= n);
    }

    Vector3& Vector3::divide(const Vector3& v)
    {
        x /= v.x;
        y /= v.y;
        z /= v.z;

        return *this;
    }

    Vector3& Vector3::divide(const Real& n)
    {
        x /= n;
        y /= n;
        z /= n;

        return *this;
    }

    Vector3 Vector3::divided(const Vector3& v) const
    {
        return Vector3(x / v.x,
                        y / v.y,
                        z / v.z);
    }

    Vector3 Vector3::divided(const Real& n) const
    {
        return Vector3(x / n,
                        y / n,
                        z / n);
    }

    const Real& Vector3::at(size_t i) const
    {
        return i == 0 ? x : i == 1 ? y : z;
    }

    Real& Vector3::at(size_t i)
    {
        return i == 0 ? x : i == 1 ? y : z;
    }

    const Real* Vector3::ptr() const
    {
        return &x;
    }

    Real* Vector3::ptr()
    {
        return &x;
    }

    Vector3& Vector3::negate()
    {
        x = -x;
        y = -y;
        z = -z;
        return -this;
    }

    Vector3 Vector3::negated() const
    {
        return Vector3(-x, -y, -z);
    }

    Vector3 Vector3::absoluted() const
    {
        return Vector3(abs_(x), abs_(y), abs_(z));
    }

    Vector3& Vector3::absolute()
    {
        x = abs_(x);
        y = abs_(y);
        z = abs_(z);
        return *this;
    }

    Real Vector3::lenght() const
    {
        return Sqrt(squaredLenght());
    }

    Real Vector3::squaredLenght() const
    {
        return x * x + y * y + z * z;
    }

    Real Vector3::distance(const Vector3& v) const
    {
        return Sqrt(squaredDistance(v));
    }

    Real Vector3::squaredDistance(const Vector3& v) const
    {
        Real dx = x - v.x;
        Real dy = y - v.y;
        Real dz = z - v.z;

        return dx*dx + dy*dy + dz*dz;
    }

    Vector3 Vector3::midPoint(const Vector3& other) const
    {
        return Vector3(
            ( x + other.x ) * 0.5f,
            ( y + other.y ) * 0.5f,
            ( z + other.z ) * 0.5f );
    }

    void Vector3::setFromSphericalCoordinates(Radian azimuth, Radian inclinaison, Real radius)
    {
        Real cx = Cos(inclinaison);
        x = cx * Sin(azimuth) * radius;
        y = -Sin(inclinaison) * radius;
        z = cx * Cos(azimuth) * radius;
    }

    void Vector3::setFromSphericalCoordinates(const Vector3& spherical)
    {
        setFromSphericalCoordinates(spherical.x, spherical.y, spherical.z);
    }

    Vector3 Vector3::FromSphericalCoordinates(Radian azimuth, Radian inclinaison, Real radius)
    {
        Vector3 ret;
        ret.setFromSphericalCoordinates(azimuth, inclinaison, radius);
        return ret;
    }

    Vector3 Vector3::FromSphericalCoordinates(const Vector3& spherical)
    {
        Vector3 ret;
        ret.setFromSphericalCoordinates(spherical);
        return ret;
    }

    Vector3 Vector3::toSphericalCoordinates() const
    {
        Vector3 v = *this;

        Real l = v.normalize();
        if((float) l <= 1e-5f)
            return ::Zero();
        Radian azimuth = ATan2(v.x, v.z);
        Radian inclinaison = ASin(-v.y);
        return Vector3((Real)azimuth, (Real)inclinaison, l);
    }

    Vector3 Vector3::toSphericalCoordinatesNormalized() const
    {
        Radian azimuth = ATan2(x, z);
        Radian inclinaison = ASin(-y);
        return Vector3((Real)azimuth, (Real)inclinaison, 1.0f);
    }

    Real Vector3::normalize()
    {
        Real len = lenght();
        if(len > 1e-6f)
        {
            *this *= 1.f / len;
            return len;
        }
        else
        {
            aprodebug("Vector lenght is too short ! Normalization failed.");
            set(1,0,0);
            return 0;
        }
    }

    Vector3& Vector3::normalized() const
    {
        Vector3 copy = *this;
        Real oldLen = copy.normalize();
        aproassert(oldLen > 0, "Cannot normalize vector !");
        return copy;
    }

    Real Vector3::scale(const Real& new_lenght)
    {
        Real len = squaredLenght();
        if(len < 1e-6f)
        {
            aprodebug("Vector lenght is too short ! Scale failed.");
            set(new_lenght, 0,0);
            return 0;
        }
        else
        {
            len = Sqrt(len);
            Real scalar = new_lenght / len;
            *this *= scalar;
            return len;
        }
    }

    Vector3 Vector3::scaled(const Real& new_lenght) const
    {
        Vector3 copy = *this;
        copy.scale(new_lenght);
        return copy;
    }

    bool Vector3::isNormalized(Real epsilon) const
    {
        return abs_(squaredLenght() - 1) <= epsilon;
    }

    bool Vector3::isZero(Real epsilon) const
    {
        return abs_(squaredLenght) <= epsilon;
    }

    bool Vector3::isPerpendicular(const Vector3& other, Real epsilon) const
    {
        return abs_(dot(other)) <= epsilon * length() * other.length();
    }

    bool Vector3::AreCollinear(const Vector3& p1, const Vector3& p2, const Vector3& p3, Real espilon)
    {
        return (p2-p1).cross(p3-p1).squaredLenght() <= epsilon;
    }

    Real Vector3::dot(const Vector3& other) const
    {
        return x * other.x + y * other.y + z * other.z;
    }

    Real Vector3::dotabs(const Vector3& other) const
    {
        return *this.absoluted().dot(other.absoluted());
    }

    Vector3 Vector3::cross(const Vector3& other) const
    {
        return Vector3(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x);
    }

    Vector3 Vector3::perpendicular(const Vector3& hint) const
    {
        Vector3 v = this->cross(hint);
        Real len = v.normalize();
        if(len == 0)
            return ::Zero;
        else
            return v;
    }

    Vector3 anotherPerpendicular(const Vector3& hint) const
    {
        Vector3 first = this->perpendicular(hint);
        Vector3 v = this->cross(first);
        return v.normalized();
    }

    Vector3 Vector3::reflect(const Vector3& normal) const
    {
        return 2 * *this->projectToNorm(normal) - *this;
    }

    Vector3 Vector3::refract(const Vector3& normal, Real negativSideRefractionIndex, Real positiveSideRefractionIndex) const
    {
        // Duplicate from Vector2::refract
        Real n = negativSideRefractionIndex / positiveSideRefractionIndex;
        Real cosI = this->dotProduct(normal);
        Real sinT2 = n*n*(1.f - cosI * cosI);
        if(sinT2 > 1.f)
            return (-(*this)).reflect(normal);
        return n * *this - (n + Sqrt(1.f - sinT2)) * normal;
    }

    Vector3 Vector3::projectTo(const Vector3& direction) const
    {
        return direction * this->dot(direction) / direction.squaredLenght();
    }

    Vector3 Vector3::projectToNorm(const Vector3& direction) const
    {
        return direction * this->dot(direction);
    }

    Radian Vector3::angleBetween(const Vector3& other) const
    {
        Real cosa = dot(other) / Sqrt(squaredLenght() * other.squaredLenght());
        if (cosa >= 1.f)
            return (Radian) 0.f;
        else if (cosa <= -1.f)
            return (Radian) Math::PI_32;
        else
            return (Radian) ACos(cosa);
    }

    Radian Vector3::angleBetweenNorm(const Vector3& normalizedVector) const
    {
        Radian cosa = dot(other);
        if (cosa >= 1.f)
            return (Radian) 0.f;
        else if (cosa <= -1.f)
            return (Radian) Math::PI_32;
        else
            return (Radian) ACos(cosa);
    }

    void Vector3::decompose(const Vector3& direction, Vector3& outParallel, Vector3& outPerpendicular) const
    {
        outParallel = this>projectToNorm(direction);
        outPerpendicular = *this - outParallel;
    }

    Vector3 Vector3::linearInterpolate(const Vector3& b, Real t) const
    {
        Clamp(t, 0.0f, 1.0f);
        return (1.f - t) * *this + t * b;
    }

    Vector3 Vector3::LinearInterpolate(const Vector3& a, const Vector3& b, Real t)
    {
        return a.linearInterpolate(b, t);
    }

    void Vector3::Orthogonalize(const Vector3& a, Vector3& b)
    {
        if (!a.isZero())
            b -= b.projectTo(a);
    }

    void Vector3::Orthogonalize(const Vector3& a, Vector3& b, Vector3& c)
    {
        if (!a.isZero())
        {
            b -= b.projectTo(a);
            c -= c.projectTo(a);
        }

        if (!b.IsZero())
            c -= c.projectTo(b);
    }

    bool Vector3::AreOrthogonal(const Vector3& a, const Vector3& b, Real epsilon)
    {
        return a.isPerpendicular(b, epsilon);
    }

    bool Vector3::AreOrthogonal(const Vector3& a, const Vector3& b, const Vector3& c, Real epsilon)
    {
        return a.isPerpendicular(b, epsilon) &&
                a.isPerpendicular(c, epsilon) &&
                b.isPerpendicular(c, epsilon);
    }

    bool Vector3::Orthonormalize(Vector3& a, Vector3& b)
    {
        if(a.isZero() || b.isZero())
            return false;

        a.normalize();
        b -= b.projectTo(a);
        b.normalize();
        return true;
    }

    bool Vector3::Orthonormalize(Vector3& a, Vector3& b, Vector3& c)
    {
        if(a.isZero() || b.isZero() || c.isZero())
            return false;

        a.normalize();
        b -= b.projectTo(a);
        b.normalize();
        c -= c.projectTo(a);
        c -= c.projectTo(b);
        c.normalize();
        return true;
    }

    bool Vector3::AreOrthonormal(const Vector3& a, const Vector3& b, Real epsilon)
    {
        return a.isPerpendicular(b, epsilon) && a.isNormalized(epsilon*epsilon) && b.isNormalized(epsilon*epsilon);
    }

    bool Vector3::AreOrthonormal(const Vector3& a, const Vector3& b, const Vector3& c, Real epsilon)
    {
        return a.isPerpendicular(b, epsilon) &&
                a.isPerpendicular(c, epsilon) &&
                b.isPerpendicular(c, epsilon) &&
                a.isNormalized(epsilon*epsilon) &&
                b.isNormalized(epsilon*epsilon) &&
                c.isNormalized(epsilon*epsilon);
    }

    bool Vector3::isFinite() const
    {
        return IsFinite(x) && IsFinite(y) && IsFinite(z);
    }

    Vector2& Vector3::toVec2()
    {
        return *reinterpret_cast<Vector2* >(this);
    }

    const Vector2& Vector3::toVec2() const
    {
        return *reinterpret_cast<const Vector2* >(this);
    }

    const Vector3 Vector3::Zero = Vector3(0,0,0);
    const Vector3 Vector3::UnitX = Vector3(1,0,0);
    const Vector3 Vector3::UnitY = Vector3(0,1,0);
    const Vector3 Vector3::UnitZ = Vector3(0,0,1);
    const Vector3 Vector3::Nan = Vector3(Math::_real_nan, Math::_real_nan, Math::_real_nan);
    const Vector3 Vector3::Inf = Vector3(Math::_real_inf, Math::_real_inf, Math::_real_inf);
}
