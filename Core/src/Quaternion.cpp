////////////////////////////////////////////////////////////
/** @file Quaternion.cpp
 *  @ingroup Maths
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 11/09/2013 - 17/06/2014
 *
 *  Implements the Quaternion class.
 *
**/
////////////////////////////////////////////////////////////

#include "Quaternion.h"
#include "Matrix3x3.h"
#include "Matrix3x4.h"
#include "Matrix4x4.h"

namespace APro
{
    Quaternion::Quaternion(Real x, Real y, Real z, Real w)
            : m_x(x), m_y(y), m_z(z), m_w(w)
    {

    }

    Quaternion::Quaternion(const Real* data)
            : m_x(data[0]), m_y(data[1]), m_z(data[2]), m_w(data[3])
    {

    }

    Quaternion::Quaternion(const Vector3& rotationAxis, Real rotationAngle)
    {
        setFromAxisAngle(rotationAxis, rotationAngle);
    }

    Quaternion::Quaternion(const Vector3& xAxis, const Vector3& yAxis, const Vector3& zAxis)
    {
        setFromAxes(xAxis, yAxis, zAxis);
    }

    Quaternion::Quaternion(const Vector3* axes)
    {
        setFromAxes(axes);
    }

    Quaternion::Quaternion(const Matrix3x3& rotationMatrix)
    {
        setFromRotationMatrix(rotationMatrix);
    }

    Quaternion::Quaternion(const Matrix3x4& rotationMatrix)
    {
        setFromRotationMatrix(rotationMatrix);
    }

    Quaternion::Quaternion(const Matrix4x4& rotationMatrix)
    {
        setFromRotationMatrix(rotationMatrix);
    }

    Quaternion::Quaternion(const Quaternion& other)
            : m_x(other.m_x), m_y(other.m_y), m_z(other.m_z), m_w(other.m_w)
    {

    }

    Vector3 Quaternion::localX() const
    {
//      Real fTx  = 2.0*m_x; // No need there !
        Real fTy  = 2.0f*m_y;
        Real fTz  = 2.0f*m_z;
        Real fTwy = fTy*m_w;
        Real fTwz = fTz*m_w;
        Real fTxy = fTy*m_x;
        Real fTxz = fTz*m_x;
        Real fTyy = fTy*m_y;
        Real fTzz = fTz*m_z;

        return Vector3(1.0f-(fTyy+fTzz), fTxy+fTwz, fTxz-fTwy);
    }

    Vector3 Quaternion::localY() const
    {
        Real fTx  = 2.0f*m_x;
        Real fTy  = 2.0f*m_y;
        Real fTz  = 2.0f*m_z;
        Real fTwx = fTx*m_w;
        Real fTwz = fTz*m_w;
        Real fTxx = fTx*m_x;
        Real fTxy = fTy*m_x;
        Real fTyz = fTz*m_y;
        Real fTzz = fTz*m_z;

        return Vector3(fTxy-fTwz, 1.0f-(fTxx+fTzz), fTyz+fTwx);
    }

    Vector3 Quaternion::localZ() const
    {
        Real fTx  = 2.0f*m_x;
        Real fTy  = 2.0f*m_y;
        Real fTz  = 2.0f*m_z;
        Real fTwx = fTx*m_w;
        Real fTwy = fTy*m_w;
        Real fTxx = fTx*m_x;
        Real fTxz = fTz*m_x;
        Real fTyy = fTy*m_y;
        Real fTyz = fTz*m_y;

        return Vector3(fTxz+fTwy, fTyz-fTwx, 1.0f-(fTxx+fTyy));
    }

    Radian Quaternion::getRoll(bool reprojectAxis) const
    {
        if (reprojectAxis)
        {
//		    Real fTx  = 2.0*m_x;
            Real fTy  = 2.0f*m_y;
            Real fTz  = 2.0f*m_z;
            Real fTwz = fTz*m_w;
            Real fTxy = fTy*m_x;
            Real fTyy = fTy*m_y;
            Real fTzz = fTz*m_z;

            return Angle::ATan2(fTxy+fTwz, 1.0f-(fTyy+fTzz));

        }
        else
        {
            return Angle::ATan2(2*(m_x*m_y + m_w*m_z), m_w*m_w + m_x*m_x - m_y*m_y - m_z*m_z);
        }
    }

    Radian Quaternion::getPitch(bool reprojectAxis) const
    {
        if (reprojectAxis)
        {
            Real fTx  = 2.0f*m_x;
//			Real fTy  = 2.0f*m_y;
            Real fTz  = 2.0f*m_z;
            Real fTwx = fTx*m_w;
            Real fTxx = fTx*m_x;
            Real fTyz = fTz*m_y;
            Real fTzz = fTz*m_z;

            return Angle::ATan2(fTyz+fTwx, 1.0f-(fTxx+fTzz));
        }
        else
        {
            return Angle::ATan2(2*(m_y*m_z + m_w*m_x), m_w*m_w - m_x*m_x - m_y*m_y + m_z*m_z);
        }
    }

    Radian Quaternion::getYaw(bool reprojectAxis) const
    {
        if (reprojectAxis)
        {
            Real fTx  = 2.0f*m_x;
            Real fTy  = 2.0f*m_y;
            Real fTz  = 2.0f*m_z;
            Real fTwy = fTy*m_w;
            Real fTxx = fTx*m_x;
            Real fTxz = fTz*m_x;
            Real fTyy = fTy*m_y;

            return Angle::ATan2(fTxz+fTwy, 1.0f-(fTxx+fTyy));
        }
        else
        {
            return Angle::ASin(-2*(m_x*m_z - m_w*m_y));
        }
    }

    Vector3 Quaternion::getAxis() const
    {
        Vector3 axis;
        Radian  angle;

        toAxisAngle(axis, angle);
        return axis;
    }

    Radian Quaternion::getAngle() const
    {
        return Angle::ACos(m_w) * 2;
    }

    Real Quaternion::lenght() const
    {
        return Math::Sqrt(squaredLenght());
    }

    Real Quaternion::squaredLenght() const
    {
        return m_x*m_x + m_y*m_y + m_z*m_z + m_w*m_w;
    }

    Real Quaternion::normalize()
    {
        Real len = lenght();
        if (len < 1e-4f)
            return 0.f;

        Real rcpLength = 1.f / len;
        m_x *= rcpLength;
        m_y *= rcpLength;
        m_z *= rcpLength;
        m_w *= rcpLength;

        return len;
    }

    Quaternion Quaternion::normalized() const
    {
        Quaternion cpy(*this);
        cpy.normalize();
        return cpy;
    }

    void Quaternion::conjugate()
    {
        m_x = -m_x;
        m_y = -m_y;
        m_z = -m_z;
    }

    Quaternion Quaternion::conjugated() const
    {
        return Quaternion(-m_x, -m_y, -m_z, m_w);
    }

    Real Quaternion::inverseAndNormalize()
    {
        inverse();
        return normalize();
    }

    Quaternion Quaternion::inversedAndNormalized() const
    {
        Quaternion cpy(*this);
        cpy.inverse();
        cpy.normalize();
        return cpy;
    }

    void Quaternion::setFromAxisAngle(const Vector3& axis, const Radian& angle)
    {
        Real cosz = Angle::Cos(angle/2.f);
        Real sinz = Angle::Sin(angle/2.f);
        m_x = axis.x * sinz;
        m_y = axis.y * sinz;
        m_z = axis.z * sinz;
        m_w = cosz;
    }

    void Quaternion::toAxisAngle(Vector3& axis, Radian& angle) const
    {
        angle = Angle::ACos(m_w) * 2.f;
        Real sinz = Angle::Sin(angle/2.f);
        if (Math::Abs(sinz) > 1e-4f)
        {
            sinz = 1.f / sinz;
            axis = Vector3(m_x * sinz, m_y * sinz, m_z * sinz);
        }
        else
        {
            // The quaternion does not produce any rotation. Still, explicitly
            // set the axis so that the user gets a valid normalized vector back.
            angle = 0.f;
            axis = Vector3::UnitX;
        }
    }

    void Quaternion::setFromAxes(const Vector3* axes)
    {
        Matrix3x3 m;

        for(size_t iCol = 0; iCol < 3; ++iCol)
        {
            m[0][iCol] = axes[iCol].x;
            m[1][iCol] = axes[iCol].y;
            m[2][iCol] = axes[iCol].z;
        }

        setFromRotationMatrix(m);
    }

    void Quaternion::setFromAxes(const Vector3& xAxis, const Vector3& yAxis, const Vector3& zAxis)
    {
        Matrix3x3 m;

        m[0][0] = xAxis.x;
        m[1][0] = xAxis.y;
        m[2][0] = xAxis.z;

        m[0][1] = yAxis.x;
        m[1][1] = yAxis.y;
        m[2][1] = yAxis.z;

        m[0][2] = zAxis.x;
        m[1][2] = zAxis.y;
        m[2][2] = zAxis.z;

        setFromRotationMatrix(m);
    }

    void Quaternion::toAxes(Vector3* axes) const
    {
        Matrix3x3 m;
        toRotationMatrix(m);

        for(size_t iCol = 0; iCol < 3; ++iCol)
        {
            axes[iCol].x = m[0][iCol];
            axes[iCol].y = m[1][iCol];
            axes[iCol].z = m[2][iCol];
        }
    }

    void Quaternion::toAxes(Vector3& xAxis, Vector3& yAxis, Vector3& zAxis) const
    {
        Matrix3x3 m;
        toRotationMatrix(m);

        xAxis.x = m[0][0];
        xAxis.y = m[1][0];
        xAxis.z = m[2][0];

        yAxis.x = m[0][1];
        yAxis.y = m[1][1];
        yAxis.z = m[2][1];

        zAxis.x = m[0][2];
        zAxis.y = m[1][2];
        zAxis.z = m[2][2];
    }

    void Quaternion::setFromRotationMatrix(const Matrix3x3& m)
    {
        // Algorithm in Ken Shoemake's article in 1987 SIGGRAPH course notes
        // article "Quaternion Calculus and Fast Animation".

        Real fTrace = m[0][0] + m[1][1] + m[2][2];
        Real fRoot;

        if ( fTrace > 0.0 )
        {
            // |w| > 1/2, may as well choose w > 1/2
            fRoot = Math::Sqrt(fTrace + 1.0f);  // 2w
            m_w = 0.5f * fRoot;

            fRoot = 0.5f/fRoot;  // 1/(4w)
            m_x = (m[2][1] - m[1][2])*fRoot;
            m_y = (m[0][2] - m[2][0])*fRoot;
            m_z = (m[1][0] - m[0][1])*fRoot;
        }
        else
        {
            // |w| <= 1/2
            static size_t s_iNext[3] = { 1, 2, 0 };
            size_t i = 0;
            if ( m[1][1] > m[0][0] )
                i = 1;
            if ( m[2][2] > m[i][i] )
                i = 2;

            size_t j = s_iNext[i];
            size_t k = s_iNext[j];

            fRoot = Math::Sqrt(m[i][i] - m[j][j] - m[k][k] + 1.0f);

            Real* apkQuat[3] = { &m_x, &m_y, &m_z };
            *apkQuat[i] = 0.5f*fRoot;

            fRoot = 0.5f/fRoot;

            m_w = (m[k][j]-m[j][k])*fRoot;
            *apkQuat[j] = (m[j][i]+m[i][j])*fRoot;
            *apkQuat[k] = (m[k][i]+m[i][k])*fRoot;
        }
    }

    /// See Schneider, Eberly. Geometric Tools for Computer Graphics, p. 861.
    template<typename M>
    void __setfrom(Quaternion& q, const M& m)
    {
        // The rotation matrix is of form: (Eric Lengyel's Mathematics for 3D Game Programming and Computer Graphics 2nd ed., p. 92)
        // 1 - 2y^2 - 2z^2        2xy - 2wz            2xz + 2wy
        //    2xy + 2wz        1 - 2x^2 - 2z^2         2yz - 2wx
        //    2xz - 2wy           2yz + 2wx         1 - 2x^2 - 2y^2

        Real r = m[0][0] + m[1][1] + m[2][2]; // The element w is easiest picked up as a sum of the diagonals.
        // Above, r == 3 - 4(x^2+y^2+z^2) == 4(1-x^2-y^2-z^2) - 1 == 4*w^2 - 1.
        if (r > 0) // In this case, |w| > 1/2.
        {
            q.m_w = Math::Sqrt(r + 1.f) * 0.5f; // We have two choices for the sign of w, arbitrarily pick the positive.
            Real inv4w = 1.f / (4.f * q.m_w);
            q.m_x = (m[2][1] - m[1][2]) * inv4w;
            q.m_y = (m[0][2] - m[2][0]) * inv4w;
            q.m_z = (m[1][0] - m[0][1]) * inv4w;
        }
        else if (m[0][0] > m[1][1] && m[0][0] > m[2][2]) // If |q.x| is larger than |q.y| and |q.z|, extract it first. This gives
        {                                                // best stability, and we know below x can't be zero.
            q.m_x = Math::Sqrt(1.f + m[0][0] - m[1][1] - m[2][2]) * 0.5f; // We have two choices for the sign of x, arbitrarily pick the positive.
            const Real x4 = 1.f / (4.f * q.m_x);
            q.m_y = (m[0][1] + m[1][0]) * x4;
            q.m_z = (m[0][2] + m[2][0]) * x4;
            q.m_w = (m[2][1] - m[1][2]) * x4;
        }
        else if (m[1][1] > m[2][2]) // |q.y| is larger than |q.x| and |q.z|
        {
            q.m_y = Math::Sqrt(1.f + m[1][1] - m[0][0] - m[2][2]) * 0.5f; // We have two choices for the sign of y, arbitrarily pick the positive.
            const Real y4 = 1.f / (4.f * q.m_y);
            q.m_x = (m[0][1] + m[1][0]) * y4;
            q.m_z = (m[1][2] + m[2][1]) * y4;
            q.m_w = (m[0][2] - m[2][0]) * y4;
        }
        else // |q.z| is larger than |q.x| or |q.y|
        {
            q.m_z = Math::Sqrt(1.f + m[2][2] - m[0][0] - m[1][1]) * 0.5f; // We have two choices for the sign of z, arbitrarily pick the positive.
            const Real z4 = 1.f / (4.f * q.m_z);
            q.m_x = (m[0][2] + m[2][0]) * z4;
            q.m_y = (m[1][2] + m[2][1]) * z4;
            q.m_w = (m[1][0] - m[0][1]) * z4;
        }

        Real oldLength = q.normalize();
    }

    void Quaternion::setFromRotationMatrix(const Matrix3x4& m)
    {
        __setfrom(*this, m);
    }

    void Quaternion::setFromRotationMatrix(const Matrix4x4& m)
    {
        __setfrom(*this, m);
    }

    void Quaternion::toRotationMatrix(Matrix3x3& m) const
    {
        Real fTx  = m_x+m_x;
        Real fTy  = m_y+m_y;
        Real fTz  = m_z+m_z;
        Real fTwx = fTx*m_w;
        Real fTwy = fTy*m_w;
        Real fTwz = fTz*m_w;
        Real fTxx = fTx*m_x;
        Real fTxy = fTy*m_x;
        Real fTxz = fTz*m_x;
        Real fTyy = fTy*m_y;
        Real fTyz = fTz*m_y;
        Real fTzz = fTz*m_z;

        m[0][0] = 1.0f-(fTyy+fTzz);
        m[0][1] = fTxy-fTwz;
        m[0][2] = fTxz+fTwy;
        m[1][0] = fTxy+fTwz;
        m[1][1] = 1.0f-(fTxx+fTzz);
        m[1][2] = fTyz-fTwx;
        m[2][0] = fTxz-fTwy;
        m[2][1] = fTyz+fTwx;
        m[2][2] = 1.0f-(fTxx+fTyy);
    }

    void Quaternion::toRotationMatrix(Matrix3x4& m) const
    {
        // Let the matrix implement it !
        m.fromQuaternion(*this);
    }

    void Quaternion::toRotationMatrix(Matrix4x4& m) const
    {
        // Let the matrix implement it !
        m.fromQuaternion(*this);
    }

    bool Quaternion::isNormalized(Real epsilon) const
    {
        return Math::EqualsAbs(squaredLenght(), 1.f, epsilon);
    }

    bool Quaternion::isInvertible(Real epsilon) const
    {
        return squaredLenght() > epsilon && isFinite();
    }

    bool Quaternion::isFinite() const
    {
        return IsFinite(m_x) &&
                IsFinite(m_y) &&
                IsFinite(m_z) &&
                IsFinite(m_w);
    }

    bool Quaternion::equals(const Quaternion& other, Real epsilon) const
    {
        return Math::EqualsAbs(m_x, other.m_x, epsilon) &&
               Math::EqualsAbs(m_y, other.m_y, epsilon) &&
               Math::EqualsAbs(m_z, other.m_z, epsilon) &&
               Math::EqualsAbs(m_w, other.m_w, epsilon);
    }

    Quaternion& Quaternion::multiply(const Quaternion& rkQ)
    {
        Real x = m_w * rkQ.m_x + m_x * rkQ.m_w + m_y * rkQ.m_z - m_z * rkQ.m_y;
        Real y = m_w * rkQ.m_y + m_y * rkQ.m_w + m_z * rkQ.m_x - m_x * rkQ.m_z;
        Real z = m_w * rkQ.m_z + m_z * rkQ.m_w + m_x * rkQ.m_y - m_y * rkQ.m_x;
        Real w = m_w * rkQ.m_w - m_x * rkQ.m_x - m_y * rkQ.m_y - m_z * rkQ.m_z;


        m_x = x; m_y = y; m_z = z; m_w = w;
        return *this;
    }

    Quaternion Quaternion::multiplied(const Quaternion& rkQ) const
    {
        return Quaternion
        (
            m_w * rkQ.m_x + m_x * rkQ.m_w + m_y * rkQ.m_z - m_z * rkQ.m_y,
            m_w * rkQ.m_y + m_y * rkQ.m_w + m_z * rkQ.m_x - m_x * rkQ.m_z,
            m_w * rkQ.m_z + m_z * rkQ.m_w + m_x * rkQ.m_y - m_y * rkQ.m_x,
            m_w * rkQ.m_w - m_x * rkQ.m_x - m_y * rkQ.m_y - m_z * rkQ.m_z
        );
    }

    Vector3 Quaternion::transformed(const Real& x, const Real& y, const Real& z) const
    {
        return transformed(Vector3(x,y,z));
    }

    Vector3 Quaternion::transformed(const Vector3& other) const
    {
        Vector3 cpy = other;
        transform(cpy);
        return cpy;
    }

    void Quaternion::transform(Vector3& vec) const
    {
        // nVidia SDK implementation
		Vector3 uv, uuv;
		Vector3 qvec(m_x, m_y, m_z);

		uv = qvec.cross(vec);
		uuv = qvec.cross(uv);

		uv *= (2.0f * m_w);
		uuv *= 2.0f;

		vec = (vec + uv + uuv);
    }

    Quaternion& Quaternion::add(const Quaternion& other)
    {
        m_x += other.m_x;
        m_y += other.m_y;
        m_z += other.m_z;
        m_w += other.m_w;
        return *this;
    }

    Quaternion Quaternion::added(const Quaternion& other) const
    {
        return Quaternion
        (
            m_x + other.m_x,
            m_y + other.m_y,
            m_z + other.m_z,
            m_w + other.m_w
        );
    }

    Quaternion& Quaternion::substract(const Quaternion& other)
    {
        m_x -= other.m_x;
        m_y -= other.m_y;
        m_z -= other.m_z;
        m_w -= other.m_w;
        return *this;
    }

    Quaternion Quaternion::substracted(const Quaternion& other) const
    {
        return Quaternion
        (
            m_x - other.m_x,
            m_y - other.m_y,
            m_z - other.m_z,
            m_w - other.m_w
        );
    }

    Quaternion& Quaternion::multiply(const Real& scalar)
    {
        m_x *= scalar;
        m_y *= scalar;
        m_z *= scalar;
        m_w *= scalar;
        return *this;
    }

    Quaternion Quaternion::multiplied(const Real& scalar) const
    {
        return Quaternion
        (
            m_x * scalar,
            m_y * scalar,
            m_z * scalar,
            m_w * scalar
        );
    }

    Real Quaternion::dot(const Quaternion& other) const
    {
        return m_x*other.m_x + m_y*other.m_y + m_z*other.m_z + m_w*other.m_w;
    }

    Quaternion Quaternion::negated() const
    {
        return Quaternion(-m_x, -m_y, -m_z, -m_w);
    }

    Quaternion Quaternion::linearInterpolate(const Quaternion& target, Real t) const
    {
        Math::Clamp(t, 0.f, 1.f);
        return *this * (1.f - t)  + target * t;
    }

    Quaternion Quaternion::sphericalInterpolate(const Quaternion& target, Real t, bool shortestPath) const
    {
        Math::Clamp(t, 0.f, 1.f);

        Real fCos = this->dot(target);
        Quaternion rkT;

        // Do we need to invert rotation?
        if (fCos < 0.0f && shortestPath)
        {
            fCos = -fCos;
            rkT = -target;
        }
        else
        {
            rkT = target;
        }

        if (Math::Abs(fCos) < 1 - 1e-3f)
        {
            // Standard case (slerp)
            Real   fSin    = Math::Sqrt(1 - (fCos * fCos));
            Radian fAngle  = Angle::ATan2(fSin, fCos);
            Real   fInvSin = 1.0f / fSin;
            Real   fCoeff0 = Angle::Sin((1.0f - t) * fAngle) * fInvSin;
            Real   fCoeff1 = Angle::Sin(t * fAngle) * fInvSin;
            return fCoeff0 * (*this) + fCoeff1 * rkT;
        }
        else
        {
            // There are two situations:
            // 1. "source" and "target" are very close (fCos ~= +1), so we can do a linear
            //    interpolation safely.
            // 2. "source" and "target" are almost inverse of each other (fCos ~= -1), there
            //    are an infinite number of possibilities interpolation. but we haven't
            //    any method to fix this case, so just use linear interpolation here.
            Quaternion t = (1.0f - t) * (*this) + t * target;
            // taking the complement requires renormalisation
            t.normalize();
            return t;
        }
    }

    Vector3 Quaternion::SlerpVector(const Vector3& from, const Vector3& to, Real t)
    {
        Quaternion q = Quaternion::RotateFromTo(from, to);
        q = Quaternion::SphericalInterpolation(Quaternion::Identity, q, t);

        Vector3 r(from);
        q.transform(r);
        return r;
    }

    Vector3 Quaternion::SlerpVectorAbs(const Vector3& from, const Vector3& to, Radian a)
    {
        if(a <= 0.f)
            return from;

        Quaternion q = Quaternion::RotateFromTo(from, to);
        Radian a2 = q.getAngle();
        if(a2 <= a)
            return to;
        Real t = a / a2;
        q = Quaternion::SphericalInterpolation(Quaternion::Identity, q, t);
        return q.transformed(from);
    }

    Quaternion Quaternion::normalizedInterpolate(const Quaternion& target, Real t, bool shortestPath) const
    {
        Quaternion result;
        Real fCos = this->dot(target);
        if(fCos < 0.0f && shortestPath)
        {
            result = (*this) + t * ((-target) - (*this));
        }
        else
        {
            result = (*this) + t * (target - (*this));
        }
        result.normalize();
        return result;
    }

    Quaternion Quaternion::divided(const Quaternion& r) const
    {
        return Quaternion
        (
            m_x*r.m_w - m_y*r.m_z + m_z*r.m_y - m_w*r.m_x,
            m_x*r.m_z + m_y*r.m_w - m_z*r.m_x - m_w*r.m_y,
           -m_x*r.m_y + m_y*r.m_x + m_z*r.m_w - m_w*r.m_z,
            m_x*r.m_x + m_y*r.m_y + m_z*r.m_z + m_w*r.m_w
        );
    }

    Radian Quaternion::angleBetween(const Quaternion& target) const
    {
        Quaternion q = target / *this;
        return q.getAngle();
    }

    Vector3 Quaternion::axisFromTo(const Quaternion& target) const
    {
        Quaternion q = target / *this;
        return q.getAxis();
    }

    Quaternion Quaternion::LookAt(const Vector3& localForward, const Vector3& targetDirection, const Vector3& localUp, const Vector3& worldUp)
    {
        return Matrix3x3::LookAt(localForward, targetDirection, localUp, worldUp).toQuaternion();
    }

    Quaternion Quaternion::RotateX(Radian a)
    {
        return Quaternion(Vector3::UnitX, a);
    }

    Quaternion Quaternion::RotateY(Radian a)
    {
        return Quaternion(Vector3::UnitY, a);
    }

    Quaternion Quaternion::RotateZ(Radian a)
    {
        return Quaternion(Vector3::UnitZ, a);
    }

    Quaternion Quaternion::RotateAxisAngle(const Vector3& axis, Radian angle)
    {
        return Quaternion(axis, angle);
    }

    Quaternion Quaternion::RotateFromTo(const Vector3& sourceDirection, const Vector3& targetDirection)
    {
        Radian angle = sourceDirection.angleBetweenNorm(targetDirection);
        Vector3 axis = sourceDirection.cross(targetDirection);

        Real oldLenght = axis.normalize();
        if(oldLenght == 0)
            axis = Vector3::UnitX;

        return Quaternion(axis, angle);
    }

    const Quaternion Quaternion::Identity = Quaternion(0.0f, 0.0f, 0.0f, 1.0f);
    const Quaternion Quaternion::Nan      = Quaternion(Math::_real_nan, Math::_real_nan, Math::_real_nan, Math::_real_nan);

}
