////////////////////////////////////////////////////////////
/** @file Vector4.cpp
 *  @ingroup Maths
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 29/09/2013
 *
 *  Implements the Vector4 class.
 *
**/
////////////////////////////////////////////////////////////
#include "Vector4.h"

namespace APro
{
    Vector4::Vector4()
        : x(0), y(0), z(0), w(0)
    {

    }

    Vector4::Vector4(const Vector4& v)
        : x(v.x), y(v.y), z(v.z), w(v.w)
    {

    }

    Vector4::Vector4(Real n1, Real n2, Real n3, Real n4)
        : x(n1), y(n2), z(n3), w(n4)
    {

    }

    Vector4::Vector4(const Vector3& xyz, Real w_)
        : x(xyz.x), y(xyz.y), z(xyz.z), w(w_)
    {

    }

    Vector4::Vector4(const Vector2& xy, Real z_, Real w_)
        : x(xy.x), y(xy.y), z(z_), w(w_)
    {

    }

    Vector4::Vector4(Real n)
        : x(n), y(n), z(n), w(n)
    {

    }

    Vector4::Vector4(const Real v[4])
        : x(v[0]), y(v[1]), z(v[2]), w(v[3])
    {

    }

    void Vector4::swap(Vector4& v)
    {
        swapNumeric_xor(x, v.x);
        swapNumeric_xor(y, v.y);
        swapNumeric_xor(z, v.z);
        swapNumeric_xor(w, v.w);
    }

    bool Vector4::equals(const Vector4& v) const
    {
        return Math::Equals(x, v.x)
            && Math::Equals(y, v.y)
            && Math::Equals(z, v.z)
            && Math::Equals(w, v.w);
    }

    bool Vector4::equalsAbs(const Vector4& v, Real epsilon) const
    {
        return Math::EqualsAbs(x, v.x, epsilon)
            && Math::EqualsAbs(y, v.y, epsilon)
            && Math::EqualsAbs(z, v.z, epsilon)
            && Math::EqualsAbs(w, v.w, epsilon);
    }

    bool Vector4::equals(const Real& n1, const Real& n2, const Real& n3, const Real& n4) const
    {
        return Math::Equals(x, n1)
            && Math::Equals(y, n2)
            && Math::Equals(z, n3)
            && Math::Equals(w, n4);
    }

    bool Vector4::equalsAbs(const Real& n1, const Real& n2, const Real& n3, const Real& n4, Real epsilon = 1e-3f) const
    {
        return Math::EqualsAbs(x, n1, epsilon)
            && Math::EqualsAbs(y, n2, epsilon)
            && Math::EqualsAbs(z, n3, epsilon)
            && Math::EqualsAbs(w, n4, epsilon);
    }

    Vector4& Vector4::set(const Vector4& other)
    {
        x = other.x;
        y = other.y;
        z = other.z;
        w = other.w;
        return *this;
    }

    Vector4& Vector4::set(const Real& n1, const Real& n2, const Real& n3, const Real& n4)
    {
        x = n1;
        y = n2;
        z = n3;
        w = n4;
        return *this;
    }

    Vector4& Vector4::set(const Real& n)
    {
        x = n;
        y = n;
        z = n;
        w = n;
        return *this;
    }

    Vector4& Vector4::set(const Real& xyz, const Real& mw)
    {
        x = xyz;
        y = xyz;
        z = xyz;
        w = mw;
        return *this;
    }

    Vector4& Vector4::set(const Vector3& xyz, const Real& mw)
    {
        x = xyz.x;
        y = xyz.y;
        z = xyz.z;
        w = mw;
        return *this;
    }

    void Vector4::floor(const Vector4& other)
    {
        x = Math::Min(x, other.x);
        y = Math::Min(y, other.y);
        z = Math::Min(z, other.z);
        w = Math::Min(w, other.w);
    }

    void Vector4::floor3(const Vector3& other)
    {
        x = Math::Min(x, other.x);
        y = Math::Min(y, other.y);
        z = Math::Min(z, other.z);
    }

    void Vector4::ceil(const Vector4& other)
    {
        x = Math::Max(x, other.x);
        y = Math::Max(y, other.y);
        z = Math::Max(z, other.z);
        w = Math::Max(w, other.w);
    }

    void Vector4::ceil3(const Vector3& other)
    {
        x = Math::Max(x, other.x);
        y = Math::Max(y, other.y);
        z = Math::Max(z, other.z);
    }

    Vector4& Vector4::add(const Vector4& v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
        w += v.w;
        return *this;
    }

    Vector4& Vector4::add(const Vector3& v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    Vector4& Vector4::add(const Real& n)
    {
        x += n;
        y += n;
        z += n;
        w += n;
        return *this;
    }

    Vector4 Vector4::added(const Vector4& v) const
    {
        Vector4 r(*this);
        return r.add(v);
    }

    Vector4 Vector4::added(const Vector3& v) const
    {
        Vector4 r(*this);
        return r.add(v);
    }

    Vector4 Vector4::added(const Real& n) const
    {
        Vector4 r(*this);
        return r.add(n);
    }

    Vector4& Vector4::sub(const Vector4& v)
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        w -= v.w;
        return *this;
    }

    Vector4& Vector4::sub(const Vector3& v)
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    Vector4& Vector4::sub(const Real& n)
    {
        x -= n;
        y -= n;
        z -= n;
        w -= n;
        return *this;
    }

    Vector4 Vector4::subbed(const Vector4& v) const
    {
        Vector4 r(*this);
        return r.sub(v);
    }

    Vector4 Vector4::subbed(const Vector3& v) const
    {
        Vector4 r(*this);
        return r.sub(v);
    }

    Vector4 Vector4::subbed(const Real& n) const
    {
        Vector4 r(*this);
        return r.sub(n);
    }

    Vector4& Vector4::multiply(const Vector4& v)
    {
        x *= v.x;
        y *= v.y;
        z *= v.z;
        w *= v.w;
        return *this;
    }

    Vector4& Vector4::multiply(const Vector3& v)
    {
        x *= v.x;
        y *= v.y;
        z *= v.z;
        return *this;
    }

    Vector4& Vector4::multiply(const Real& n)
    {
        x *= n;
        y *= n;
        z *= n;
        w *= n;
        return *this;
    }

    Vector4 Vector4::multiplied(const Vector4& v) const
    {
        Vector4 r(*this);
        return r.multiply(v);
    }

    Vector4 Vector4::multiplied(const Vector3& v) const
    {
        Vector4 r(*this);
        return r.multiply(v);
    }

    Vector4 Vector4::multiplied(const Real& n) const
    {
        Vector4 r(*this);
        return r.multiply(n);
    }

    Vector4& Vector4::divide(const Vector4& v)
    {
        aproassert(!Math::Equals(v.x, 0) && !Math::Equals(v.y, 0) && !Math::Equals(v.z, 0) && !Math::Equals(v.w, 0), "Can't divide Vector4 by zero component !");
        x /= v.x;
        y /= v.y;
        z /= v.z;
        w /= v.w;
        return *this;
    }

    Vector4& Vector4::divide(const Vector3& v)
    {
        aproassert(!Math::Equals(v.x, 0) && !Math::Equals(v.y, 0) && !Math::Equals(v.z, 0), "Can't divide Vector4 by zero component !");
        x /= v.x;
        y /= v.y;
        z /= v.z;
        return *this;
    }

    Vector4& Vector4::divide(const Real& n)
    {
        aproassert(!Math::Equals(n, 0), "Can't divide Vector4 by zero component !");
        x /= n;
        y /= n;
        z /= n;
        w /= n;
        return *this;
    }

    Vector4 Vector4::divided(const Vector4& v) const
    {
        Vector4 r(*this);
        return r.divide(v);
    }

    Vector4 Vector4::divided(const Vector3& v) const
    {
        Vector4 r(*this);
        return r.divide(v);
    }

    Vector4 Vector4::divided(const Real& n) const
    {
        Vector4 r(*this);
        return r.divide(v);
    }

    const Real& Vector4::at(size_t i) const
    {
        Numeric::Clamp(i, 0, 2);
        return *(ptr() + i);
    }

    Real& Vector4::at(size_t i)
    {
        Numeric::Clamp(i, 0, 2);
        return *(ptr() + i);
    }

    Vector4& Vector4::negate()
    {
        x = -x;
        y = -y;
        z = -z;
        w = -w;
        return *this;
    }

    Vector4& Vector4::negate3()
    {
        x = -x;
        y = -y;
        z = -z;
        return *this;
    }

    Vector4 Vector4::negated() const
    {
        Vector4 r(*this);
        return r.negate();
    }

    Vector4 Vector4::negated3() const
    {
        Vector4 r(*this);
        return r.negate3();
    }

    Vector4 Vector4::absoluted() const
    {
        Vector4 r(*this);
        return r.absolute();
    }

    Vector4& Vector4::absolute()
    {
        x = Math::Abs(x);
        y = Math::Abs(y);
        z = Math::Abs(z);
        w = Math::Abs(w);
        return *this;
    }

    Real Vector4::lenght() const
    {
        return Math::Sqrt(squaredLenght());
    }

    Real Vector4::lenght3() const
    {
        return Math::Sqrt(squaredLenght3());
    }

    Real Vector4::squaredLenght() const
    {
        return x*x + y*y + z*z + w*w;
    }

    Real Vector4::squaredLenght3() const
    {
        return x*x + y*y + z*z;
    }

    Real Vector4::distance(const Vector4& v) const
    {
        return Math::Sqrt(squaredDistance(v));
    }

    Real Vector4::squaredDistance(const Vector4& v) const
    {
        Real dx = x . v.x;
        Real dy = y . v.y;
        Real dz = z . v.z;
        Real dw = w . v.w;
        return dx*dx + dy*dy + dz*dz + dw*dw;
    }

    Real Vector4::distance3(const Vector3& v) const
    {
        return toVector3().distance(v);
    }

    Real Vector4::squaredDistance3(const Vector3& v) const
    {
        return toVector3().squaredDistance(v);
    }

    Real Vector4::normalize()
    {
        aproassert(isFinite(), "Vector4 not finite !");

        Real lenghtSq = squaredLenght();
        if(lenghtSq > 1e-6f)
        {
            Real l = Math::Sqrt(lenghtSq);
            *this *= 1.f / l;
            return l;
        }
        else
        {
            set(1.f, 0.f, 0.f, 0.f);
            return 0;
        }
    }

    Real Vector4::normalize3()
    {
        return toVector3().normalize();
    }

    Vector4& Vector4::normalized() const
    {
        Vector4 r(*this);
        r.normalize();
        return r;
    }

    Vector4& Vector4::normalized3() const
    {
        Vector4 r(*this);
        r.normalize3();
        return r;
    }

    Vector4& Vector4::normalizeW()
    {
        if(Math::Abs(w) > 1e-6f)
        {
            toVector3() *= 1.f / w;
            w = 1.f;
        }
    }

    void Vector4::scale(const Real& scalar)
    {
        toVector3() *= scalar;
    }

    Real Vector4::scaleToLenght(const Real& new_lenght)
    {
        Real l = squaredLenght3();
        if(l < 1e-6f)
            return 0.f;

        l = Math::Sqrt(l);
        Real scalar = new_lenght / l;
        scale(scalar);
        return l;
    }

    Vector4 Vector4::scaled(const Real& scalar) const
    {
        Vector4 r(*this);
        r.scale(scalar);
        return r;
    }

    Vector4 Vector4::scaledToLenght(const Real& new_lenght) const
    {
        Vector4 r(*this);
        r.scaleToLenght(new_lenght);
        return r;
    }

    bool Vector4::isWZeroOrOne(Real epsilon) const
    {
        return Math::EqualsAbs(w, 0.f, epsilon)
            || Math::EqualsAbs(w, 1.f, epsilon);
    }

    bool Vector4::isZero(Real epsilon) const
    {
        return squaredLenght() <= epsilon;
    }

    bool Vector4::isZero3(Real epsilon) const
    {
        return squaredLenght3() <= epsilon;
    }

    bool Vector4::isNormalized(Real epsilon) const
    {
        return Math::EqualsAbs(Math::Abs(squaredLenght()), 1.f, epsilon);
    }

    bool Vector4::isNormalized3(Real epsilon) const
    {
        return Math::EqualsAbs(Math::Abs(squaredLenght3()), 1.f, epsilon);
    }

    bool Vector4::isFinite() const
    {
        return Math::IsFinite(x)
            && Math::IsFinite(y)
            && Math::IsFinite(z)
            && Math::IsFinite(w);
    }

    bool Vector4::isPerpendicular3(const Vector4& other, Real epsilon) const
    {
        return Math::Abs(this->dot3(other)) < epsilon;
    }

    Real Vector4::dot(const Vector4& other) const
    {
        return x * other.x + y * other.y + z * other.z + w * other.w;
    }

    Real Vector4::dot3(const Vector3& other) const
    {
        return toVector3().dot(other);
    }

    Real Vector4::dot3(const Vector4& other) const
    {
        return dot3(other.toVector3());
    }

    Real Vector4::dotabs(const Vector4& other) const
    {
        return Math::Abs(dot(other));
    }

    Real Vector4::dotabs3(const Vector3& other) const
    {
        return Math::Abs(dot3(other));
    }

    Vector4 Vector4::cross3(const Vector4& other) const
    {
        Vector3 r = toVector3().cross(other.toVector3());
        return Vector4(r, 0.f);
    }

    Vector4 Vector4::cross3(const Vector3& other) const
    {
        Vector3 r = toVector3().cross(other);
        return Vector4(r, 0.f);
    }

    Matrix4x4 Vector4::outerProduct(const Vector4& rhs) const
    {
        const float4 &u = *this;
        const float4 &v = rhs;
        return Matrix4x4(u[0]*v[0], u[0]*v[1], u[0]*v[2], u[0]*v[3],
                         u[1]*v[0], u[1]*v[1], u[1]*v[2], u[1]*v[3],
                         u[2]*v[0], u[2]*v[1], u[2]*v[2], u[2]*v[3],
                         u[3]*v[0], u[3]*v[1], u[3]*v[2], u[3]*v[3]);
    }

    Vector4 Vector4::perpendicular3(const Vector3& hint, const Vector3& hint2) const
    {
        aproassert(!this->isZero3(), "Vector is zero !");
        aproassert(Math::EqualsAbs(w, 0.f), "w component is non null !");
        aproassert(hint.isNormalized() && hint2.isNormalized(), "Vectors given not normalized !");

        Vector3 v = this->cross3(hint).toVector3();
        Real len = v.normalize();
        if (len == 0)
            return Vector4(hint2, 0.f);
        else
            return Vector4(v, 0.f);
    }

    Vector4 Vector4::anotherPerpendicular3(const Vector3& hint, const Vector3& hint2) const
    {
        Vector4 firstPerp = perpendicular3(hint, hint2);
        Vector4 v = cross3(firstPerp);
        return v.normalized3();
    }

    Vector4 Vector4::reflect(const Vector3& normal) const
    {
        aproassert(normal.isNormalized(), "Given vector must be normalized !");
        if(!Math::EqualsAbs(w, 0.f))
            return Vector4::Zero;

        return 2.f * this->projectToNorm3(normal) - *this;
    }

    Radian Vector4::angleBetween(const Vector4& other) const
    {
        Real cosa = dot(other) / Math::Sqrt(squaredLenght() * other.squaredLenght());
        if(cosa >= 1.f)
            return 0.f;
        else if (cosa <= -1.f)
            return (Radian) Math::PI;
        else
            return Angle::ACos(cosa);
    }

    Radian Vector4::angleBetweenNorm(const Vector4& normalizedVector) const
    {
        aproassert(isNormalized() && normalizedVector.isNormalized(), "Vectors are not normalized !");
        return Angle::ACos(dot(normalizedVector));
    }

    Radian Vector4::angleBetween3(const Vector4& other) const
    {
        return toVector3().angleBetween(other.toVector3());
    }

    Radian Vector4::angleBetweenNorm3(const Vector4& normalizedVector) const
    {
        return toVector3().angleBetweenNorm(normalizedVector.toVector3());
    }

    Vector4 Vector4::projectTo3(const Vector3& direction) const
    {
        return Vector4(toVector3().projectTo(direction), w);
    }

    Vector4 Vector4::projectToNorm3(const Vector3& direction) const
    {
        return Vector4(toVector3().projectToNorm(direction), w);
    }

    Vector4 Vector4::linearInterpolate(const Vector4& b, Real t) const
    {
        aproassert(Math::EqualsAbs(w, b.w), "W components of thwo vectors not equal !");
        aproassert(Math::IsInRange(t, 0.f, 1.f), "Invalid t value !");

        return *this * (1.f - t) + b * t;
    }

    const Vector4 Vector4::Zero   = Vector4(0.f, 0.f, 0.f, 0.f);
    const Vector4 Vector4::One    = Vector4(1.f, 1.f, 1.f, 1.f);
    const Vector4 Vector4::UnitX  = Vector4(1.f, 0.f, 0.f, 0.f);
    const Vector4 Vector4::UnitY  = Vector4(0.f, 1.f, 0.f, 0.f);
    const Vector4 Vector4::UnitZ  = Vector4(0.f, 0.f, 1.f, 0.f);
    const Vector4 Vector4::UnitW  = Vector4(0.f, 0.f, 0.f, 1.f);
    const Vector4 Vector4::Inf    = Vector4(Math::_real_inf, Math::_real_inf, Math::_real_inf, Math::_real_inf);
    const Vector4 Vector4::nan;   = Vector4(Math::_real_nan, Math::_real_nan, Math::_real_nan, Math::_real_nan);
}
