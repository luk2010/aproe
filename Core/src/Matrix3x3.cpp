////////////////////////////////////////////////////////////
/** @file Matrix3x3.cpp
 *  @ingroup Maths
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 12/09/2013
 *
 *  Implements the Matrix3x3 class.
 *
**/
////////////////////////////////////////////////////////////

#include "Matrix3x3.h"

namespace APro
{
    Matrix3x3::Matrix3x3(Real _00, Real _01, Real _02,
                  Real _10, Real _11, Real _12,
                  Real _20, Real _21, Real _22 )
    {
        set(_00, _01, _02,
            _10, _11, _12,
            _20, _21, _22);
    }

    Matrix3x3::Matrix3x3(const Vector3& col0, const Vector3& col1, const Vector3& col2)
    {
        setCol(0, col0);
        setCol(1, col1);
        setCol(2, col2);
    }

    Matrix3x3::Matrix3x3(const Quaternion& q)
    {
        setRotatePart(q);
    }

    Matrix3x3::Matrix3x3(const Matrix3x3& other)
    {
        set((const Real*) other.v);
    }

    void Matrix3x3::set(Real _00, Real _01, Real _02,
                  Real _10, Real _11, Real _12,
                  Real _20, Real _21, Real _22 )
    {
        v[0][0] = _00; v[0][1] = _01; v[0][2] = _02;
        v[1][0] = _10; v[1][1] = _11; v[1][2] = _12;
        v[2][0] = _20; v[2][1] = _21; v[2][2] = _22;
    }

    void Matrix3x3::set(const Real* m)
    {
        Memory::Copy((void*) v, (void*) m, sizeof(Real) * Rows * Cols);
    }

    void Matrix3x3::set(size_t row, size_t col, const Real& _v)
    {
        v[row][col] = _v;
    }

    void Matrix3x3::setCol(size_t col, const Vector3& values)
    {
        setCol(col, values.x, values.y, values.z);
    }

    void Matrix3x3::setCol(size_t col, const Real& x, const Real& y, const Real& z)
    {
        v[0][col] = x;
        v[1][col] = y;
        v[2][col] = z;
    }

    void Matrix3x3::setCol(size_t col, const Real* r)
    {
        setCol(col, r[0], r[1], r[2]);
    }

    void Matrix3x3::setRotatePart(const Vector3& axisDirection, const Radian& angle)
    {
        setRotatePart(Quaternion(axisDirection, angle));
    }

    void  Matrix3x3::setRotatePart(const Quaternion& q)
    {
        // See e.g. http://www.geometrictools.com/Documentation/LinearAlgebraicQuaternions.pdf .
        const float x = q.m_x; const float y = q.m_y; const float z = q.m_z; const float w = q.m_w;
        v[0][0] = 1 - 2*(y*y + z*z); v[0][1] =     2*(x*y - z*w); v[0][2] =     2*(x*z + y*w);
        v[1][0] =     2*(x*y + z*w); v[1][1] = 1 - 2*(x*x + z*z); v[1][2] =     2*(y*z - x*w);
        v[2][0] =     2*(x*z - y*w); v[2][1] =     2*(y*z + x*w); v[2][2] = 1 - 2*(x*x + y*y);
    }

    void Matrix3x3::setRow(size_t row, const Vector3& values)
    {
        setRow(row, values.x, values.y, values.z);
    }

    void Matrix3x3::setRow(size_t row, const Real& x, const Real& y, const Real& z)
    {
        v[row][0] = x;
        v[row][1] = y;
        v[row][2] = z;
    }

    void Matrix3x3::setRow(size_t row, const Real* r)
    {
        setRow(row, r[0], r[1], r[2]);
    }

    void Matrix3x3::setRotatePartX(const Radian& a)
    {
        const float cosz = Cos(a);
        const float sinz = Sin(a);

        v[0][0] = 1.f; v[0][1] =  0.f; v[0][2] =   0.f;
        v[1][0] = 0.f; v[1][1] = cosz; v[1][2] = -sinz;
        v[2][0] = 0.f; v[2][1] = sinz; v[2][2] =  cosz;
    }

    void Matrix3x3::setRotatePartY(const Radian& a)
    {
        const float cosz = Cos(a);
        const float sinz = Sin(a);

        v[0][0] =  cosz; v[0][1] = 0.f; v[0][2] = sinz;
        v[1][0] =   0.f; v[1][1] = 1.f; v[1][2] =  0.f;
        v[2][0] = -sinz; v[2][1] = 0.f; v[2][2] = cosz;
    }

    void Matrix3x3::setRotatePartZ(const Radian& a)
    {
        const float cosz = Cos(a);
        const float sinz = Sin(a);

        v[0][0] = cosz; v[0][1] = -sinz; v[0][2] = 0.f;
        v[1][0] = sinz; v[1][1] =  cosz; v[1][2] = 0.f;
        v[2][0] =  0.f; v[2][1] =   0.f; v[2][2] = 1.f;
    }

    void Matrix3x3::fromQuaternion(const Quaternion& q)
    {
        setRotatePart(q);
    }

    Quaternion Matrix3x3::toQuaternion() const
    {
        return Quaternion(*this);
    }

    void Matrix3x3::setZero()
    {
        Memory::Set(v, sizeof(Real) * Rows * Cols, 0);
    }

    void Matrix3x3::setIdentity()
    {
        v[0][0] = 1.0f; v[0][1] = 0.0f; v[0][2] = 0.0f;
        v[1][0] = 0.0f; v[1][1] = 1.0f; v[1][2] = 0.0f;
        v[2][0] = 0.0f; v[2][1] = 0.0f; v[2][2] = 1.0f;
    }

    Vector3 Matrix3x3::getCol(size_t col) const
    {
        return Vector3(v[0][col], v[1][col], v[2][col]);
    }

    Vector3 Matrix3x3::diagonale() const
    {
        return Vector3(v[0][0], v[1][1], v[2][2]);
    }

    Vector3 Matrix3x3::extractScale() const
    {
        return Vector3(getCol(0).lenght(), getCol(1).lenght(), getCol(2).lenght());
    }

    void Matrix3x3::setScale(Real sx, Real sy, Real sz)
    {
        (*this).multiply(Matrix3x3::Scale(sx, sy, sz));
    }

    void Matrix3x3::setScale(const Vector3& scalef)
    {
        (*this).multiply(Matrix3x3::Scale(scalef.x, scalef.y, scalef.z));
    }

    Vector3 Matrix3x3::getScale() const
    {
        return extractScale();
    }

    void Matrix3x3::removeScale()
    {
        getRowRef(0).normalize();
        getRowRef(1).normalize();
        getRowRef(2).normalize();
    }

    void Matrix3x3::scaleRow(size_t row, Real scalar)
    {
        aproassert(IsFinite(scalar),"Scalar given not finite !");
        getRowRef(row) *= scalar;
    }

    void Matrix3x3::scaleCol(size_t col, Real scalar)
    {
        aproassert(IsFinite(scalar),"Scalar given not finite !");
        v[0][col] *= scalar;
        v[1][col] *= scalar;
        v[2][col] *= scalar;
    }

    Matrix3x3 Matrix3x3::Scale(Real sx, Real sy, Real sz)
    {
        return Matrix3x3
        (
            sx, 0, 0,
            0, sy, 0,
            0, 0, sz
        );
    }

    Matrix3x3 Matrix3x3::Scale(const Vector3& scalef)
    {
        return Matrix3x3::Scale(scalef.x, scalef.y, scalef.z);
    }

    Matrix3x3 Matrix3x3::ScaleAlongAxis(const Vector3& axis, Real scalef)
    {
        aproassert(axis.isNormalized(),"Axis given not normalized !");
        aproassert(IsFinite(scalef),"Scalar given not finite !");
        return Matrix3x3::Scale(axis.multiplied(scalef));
    }

    Matrix3x3 Matrix3x3::UniformScale(Real uniformScale)
    {
        aproassert(IsFinite(scalef),"Scalar given not finite !");
        return Matrix3x3::Scale(uniformScale, uniformScale, uniformScale);
    }

    Matrix3x3 Matrix3x3::ShearX(Real yFactor, Real zFactor)
    {
        aproassert(IsFinite(yFactor) && IsFinite(zFactor),"Scalar given not finite !");
        return Matrix3x3
        (
            1.f, yFactor, zFactor,
            0.f,     1.f,     0.f,
            0.f,     0.f,     1.f
        );
    }

    Matrix3x3 Matrix3x3::ShearY(Real xFactor, Real zFactor)
    {
        aproassert(IsFinite(xFactor) && IsFinite(zFactor),"Scalar given not finite !");
        return Matrix3x3
        (
            1.f,     0.f,     0.f,
            xFactor, 1.f, zFactor,
            0.f,     0.f,     1.f
        );
    }

    Matrix3x3 Matrix3x3::ShearZ(Real xFactor, Real yFactor)
    {
        aproassert(IsFinite(xFactor) && IsFinite(yFactor),"Scalar given not finite !");
        return Matrix3x3
        (
            1.f,     0.f,     0.f,
            0.f,     1.f,     0.f,
            xFactor, yFactor, 1.f
        );
    }

    Matrix3x3 Matrix3x3::Mirror(const Plane& p)
    {
        aproassert(p.passThroughOrigin(), "A 3x3 matrix cannot represent mirroring about planes which do not pass through the origin ! Use Matrix3x4::Mirror instead!");
        return Matrix3x3
        (
            1.f - 2.f * p.normal.x * p.normal.x,       -2.f * p.normal.y * p.normal.x,       -2.f * p.normal.z * p.normal.x,
           -2.f * p.normal.x * p.normal.y,              1.f - 2.f * p.normal.y * p.normal.y, -2.f * p.normal.y * p.normal.z,
           -2.f * p.normal.x * p.normal.z,             -2.f * p.normal.y * p.normal.z,        1.f - 2.f * p.normal.z * p.normal.z
        );
    }

    Matrix3x3 Matrix3x3::OrthographicProjection(const Plane& target)
    {
        aproassert(p.normal.isNormalized(), "Normal must be normalized !");
        aproassert(p.passThroughOrigin(), "A 3x3 matrix cannot represent mirroring about planes which do not pass through the origin ! Use Matrix3x4::Mirror instead!");

        Matrix3x3 m;
        Real x = p.normal.x;
        Real y = p.normal.y;
        Real z = p.normal.z;

        m[0][0] = 1.f - x*x; m[0][1] =      -y*x; m[0][2] =      -z*x;
        m[1][0] =      -x*y; m[1][1] = 1.f - y*y; m[1][2] =      -y*z;
        m[2][0] =      -x*z; m[2][1] =      -y*z; m[2][2] = 1.f - z*z;

        return m;
    }

    Matrix3x3 Matrix3x3::OrthographicProjectionYZ()
    {
        Matrix3x3 v(Identity);
        v[0][0] = 0.f;
        return v;
    }

    Matrix3x3 Matrix3x3::OrthographicProjectionXZ()
    {
        Matrix3x3 v(Identity);
        v[1][1] = 0.f;
        return v;
    }

    Matrix3x3 Matrix3x3::OrthographicProjectionXY()
    {
        Matrix3x3 v(Identity);
        v[2][2] = 0.f;
        return v;
    }

    void Matrix3x3::swapRow(size_t row1, size_t row2)
    {
        aproassert(Math::is_in_range(row1, 0, Rows) && Math::is_in_range(row2, 0, Rows), "Bad rows values !");
        swapNumeric(v[row1][0], v[row2][0]);
        swapNumeric(v[row1][1], v[row2][1]);
        swapNumeric(v[row1][2], v[row2][2]);
    }

    void Matrix3x3::swapCol(size_t col1, size_t col2)
    {
        aproassert(Math::is_in_range(col1, 0, Cols) && Math::is_in_range(col2, 0, Cols), "Bad Columns values !");
        swapNumeric(v[0][col1], v[0][col2]);
        swapNumeric(v[1][col1], v[1][col2]);
        swapNumeric(v[2][col1], v[2][col2]);
    }

    Real Matrix3x3::determinant() const
    {
        aproassert(isFinite(), "Can't get determinant of non-finite matrix !");

        // Defines make no LOADs instructions.
#       define __a v[0][0]
#       define __b v[0][1]
#       define __c v[0][2]
#       define __d v[1][0]
#       define __e v[1][1]
#       define __f v[1][2]
#       define __g v[2][0]
#       define __h v[2][1]
#       define __i v[2][2]

        Real result = __a*(__e*__i - __f*__h) + __b*(__f*__g - __d*__i) + __c*(__d*__h - __e*__g);

#       undef __a
#       undef __b
#       undef __c
#       undef __d
#       undef __e
#       undef __f
#       undef __g
#       undef __h
#       undef __i

        return result;
    }

    Real Matrix3x3::determinantSymmetric() const
    {
        aproassert(isSymmetric(), "Can't get determinant symmetric of non symmetric matrix ! Use Matrix3x3::determinant() instead.");

        // Defines make no LOADs instructions.
#       define __a v[0][0]
#       define __b v[0][1]
#       define __c v[0][2]
#       define __d v[1][0]
#       define __e v[1][1]
#       define __f v[1][2]

        // A direct cofactor expansion gives
        // det = a * (df - ee) -b * (bf - ce) + c * (be-dc)
        //     = adf - aee - bbf + bce + bce - ccd
        //     = adf - aee - bbf - ccd + 2*bce
        //     = a(df-ee) + b(2*ce - bf) - ccd


        Real result = __a * (__d*__f - __e*__e) + __b * (2.f * __c * __e - __b * __f) - __c*__c*__d;

#       undef __a
#       undef __b
#       undef __c
#       undef __d
#       undef __e
#       undef __f

        return result;
    }

    bool Matrix3x3::inverse(Real epsilon)
    {
        Matrix3x3 i = *this;
        if(!MatrixUtils::InverseMatrix(i, epsilon))
            return false;

        *this = i;
        return true;
    }

    Matrix3x3 Matrix3x3::inversed(Real epsilon) const
    {
        Matrix3x3 result = *this;
        result.inverse(epsilon);
        return result;
    }

    bool Matrix3x3::inverseFast(Real epsilon)
    {
        // Compute the inverse directly using Cramer's rule.
        // Warning: This method is numerically very unstable!
        float d = determinant();
        if (Math::equal_real(d, 0.f, epsilon))
            return false;

        d = 1.f / d;
        Matrix3x3 i;
        i[0][0] = d * (v[1][1] * v[2][2] - v[1][2] * v[2][1]);
        i[0][1] = d * (v[0][2] * v[2][1] - v[0][1] * v[2][2]);
        i[0][2] = d * (v[0][1] * v[1][2] - v[0][2] * v[1][1]);

        i[1][0] = d * (v[1][2] * v[2][0] - v[1][0] * v[2][2]);
        i[1][1] = d * (v[0][0] * v[2][2] - v[0][2] * v[2][0]);
        i[1][2] = d * (v[0][2] * v[1][0] - v[0][0] * v[1][2]);

        i[2][0] = d * (v[1][0] * v[2][1] - v[1][1] * v[2][0]);
        i[2][1] = d * (v[2][0] * v[0][1] - v[0][0] * v[2][1]);
        i[2][2] = d * (v[0][0] * v[1][1] - v[0][1] * v[1][0]);

        *this = i;
        return true;
    }

    Matrix3x3 Matrix3x3::inversedFast(Real epsilon) const
    {
        Matrix3x3 result = *this;
        result.inversedFast(epsilon);
        return result;
    }

    bool Matrix3x3::inverseColOrthogonal()
    {
        aproassert(isColOrthogonal(), "Can't inverse a non column-orthogonal matrix with this function ! Use Matrix3x3::inverse instead.");

        Real s1 = getCol(0).squaredLenght();
        Real s2 = getCol(1).squaredLenght();
        Real s3 = getCol(2).squaredLenght();

        if (s1 < 1e-8f || s2 < 1e-8f || s3 < 1e-8f)
            return false;

        s1 = 1.f / s1;
        s2 = 1.f / s2;
        s3 = 1.f / s3;

        swapNumeric(v[0][1], v[1][0]);
        swapNumeric(v[0][2], v[2][0]);
        swapNumeric(v[1][2], v[2][1]);

        v[0][0] *= s1; v[0][1] *= s1; v[0][2] *= s1;
        v[1][0] *= s2; v[1][1] *= s2; v[1][2] *= s2;
        v[2][0] *= s3; v[2][1] *= s3; v[2][2] *= s3;

        return true;
    }

    bool Matrix3x3::inverseOrthogonalUniformScale()
    {
        aproassert(isColOrthogonal(), "Can't inverse a non column-orthogonal matrix with this function ! Use Matrix3x3::inverse instead.");
        aproassert(hasUniformScale(), "Matrix given does not have a uniform scale !");

        Real s = getCol(0).squaredLenght();
        if(s < 1e-8f)
            return false;

        s = 1.f / s;
        swapNumeric(v[0][1], v[1][0]);
        swapNumeric(v[0][2], v[2][0]);
        swapNumeric(v[1][2], v[2][1]);

        v[0][0] *= s; v[0][1] *= s; v[0][2] *= s;
        v[1][0] *= s; v[1][1] *= s; v[1][2] *= s;
        v[2][0] *= s; v[2][1] *= s; v[2][2] *= s;

        return true;
    }

    void Matrix3x3::inverseOrthonormal()
    {
        aproassert(isOrthonormal(), "Can't inverse a non orthonormal matrix with this function ! Use Matrix3x3::inverse instead.");
        transpose();
    }

    bool Matrix3x3::inverseSymmetric()
    {
        aproassert(isSymmetric(), "Can't inverse a non symmetric matrix with this function ! Use Matrix3x3::inverse instead.");

        const Real a = v[0][0];
        const Real b = v[0][1];
        const Real c = v[0][2];
        const Real d = v[1][1];
        const Real e = v[1][2];
        const Real f = v[2][2];

        // A direct cofactor expansion gives
        // det = a * (df - ee) + b * (ce - bf) + c * (be-dc)

        const Real df_ee = d*f - e*e;
        const Real ce_bf = c*e - b*f;
        const Real be_dc = b*e - d*c;

        Real det = a * df_ee + b * ce_bf + c * be_dc; // = DeterminantSymmetric();
        if (Math::equal_real(det, 0.f))
            return false;
        det = 1.f / det;

        // The inverse of a symmetric matrix will also be symmetric, so can avoid some computations altogether.

        v[0][0] = det * df_ee;
        v[1][0] = v[0][1] = det * ce_bf;
        v[0][2] = v[2][0] = det * be_dc;
        v[1][1] = det * (a*f - c*c);
        v[1][2] = v[2][1] = det * (c*b - a*e);
        v[2][2] = det * (a*d - b*b);

        return true;
    }

    void Matrix3x3::transpose()
    {
        swapNumeric(v[0][1], v[1][0]);
        swapNumeric(v[0][2], v[2][0]);
        swapNumeric(v[1][2], v[2][1]);
    }

    Matrix3x3 Matrix3x3::transposed() const
    {
        Matrix3x3 result = *this;
        result.transpose();
        return result;
    }

    bool Matrix3x3::inverseTranspose()
    {
        bool success = inverse();
        transpose();
        return success;
    }

    Matrix3x3 Matrix3x3::inverseTransposed() const
    {
        Matrix3x3 result(*this);
        result.inverseTranspose();
        return result;
    }

    bool Matrix3x3::solveAxb(Vector3 b, Vector3& x) const
    {
        // Solve by pivotization.
        Real v00 = v[0][0];
        Real v10 = v[1][0];
        Real v20 = v[2][0];

        Real v01 = v[0][1];
        Real v11 = v[1][1];
        Real v21 = v[2][1];

        Real v02 = v[0][2];
        Real v12 = v[1][2];
        Real v22 = v[2][2];

        Real av00 = abs_(v00);
        Real av10 = abs_(v10);
        Real av20 = abs_(v20);

        // Find which item in first column has largest absolute value.
        if (av10 >= av00 && av10 >= av20)
        {
            swapNumeric(v00, v10);
            swapNumeric(v01, v11);
            swapNumeric(v02, v12);
            swapNumeric(b[0], b[1]);
        }
        else if (v20 >= v00)
        {
            swapNumeric(v00, v20);
            swapNumeric(v01, v21);
            swapNumeric(v02, v22);
            swapNumeric(b[0], b[2]);
        }

        /* a b c | x
           d e f | y
           g h i | z , where |a| >= |d| && |a| >= |g| */

        if (Math::equal_real(v00, 0.f))
            return false;

        // Scale row so that leading element is one.
        Real denom = 1.f / v00;
//	    v00 = 1.f;
        v01 *= denom;
        v02 *= denom;
        b[0] *= denom;

        /* 1 b c | x
           d e f | y
           g h i | z */

        // Zero first column of second and third rows.
        v11 -= v10 * v01;
        v12 -= v10 * v02;
        b[1] -= v10 * b[0];

        v21 -= v20 * v01;
        v22 -= v20 * v02;
        b[2] -= v20 * b[0];

        /* 1 b c | x
           0 e f | y
           0 h i | z */

        // Pivotize again.
        if (abs_(v21) > abs_(v11))
        {
            swapNumeric(v11, v21);
            swapNumeric(v12, v22);
            swapNumeric(b[1], b[2]);
        }

        if (Math::equal_real(v11, 0.f))
            return false;

        /* 1 b c | x
           0 e f | y
           0 h i | z, where |e| >= |h| */

        denom = 1.f / v11;
//	    v11 = 1.f;
        v12 *= denom;
        b[1] *= denom;

        /* 1 b c | x
           0 1 f | y
           0 h i | z */

        v22 -= v21 * v12;
        b[2] -= v21 * b[1];

        /* 1 b c | x
           0 1 f | y
           0 0 i | z */

        if (Math::equal_real(v22, 0.f))
            return false;

        x[2] = b[2] / v22;
        x[1] = b[1] - x[2] * v12;
        x[0] = b[0] - x[2] * v02 - x[1] * v01;

        return true;
    }

    Real Matrix3x3::trace() const
    {
        return v[0][0] + v[1][1] + v[2][2];
    }

    void Matrix3x3::orthonormalize(size_t c0, size_t c1, size_t c2)
    {
        aproassert(Math::are_different(c0, c1, c2), "Three columns must be different !");
        aproassert(c0 < Cols && c1 < Cols && c2 < Cols, "The columns are invalid !");

        Vector3 v0 = getCol(c0);
        Vector3 v1 = getCol(c1);
        Vector3 v2 = getCol(c2);

        Vector3::Orthonormalize(v0, v1, v2);

        setCol(c0, v0);
        setCol(c1, v1);
        setCol(c2, v2);
    }

    Vector3 Matrix3x3::transform(const Vector3& vec) const
    {
        return transform(vec.x, vec.y, vec.z);
    }

    Vector3 Matrix3x3::transform(Real x, Real y, Real z) const
    {
        return Vector3
        (
            DOT3_xyz(getRow(0), x, y, z),
            DOT3_xyz(getRow(1), x, y, z),
            DOT3_xyz(getRow(2), x, y, z)
        );
    }

    Vector3 Matrix3x3::transformLeft(const Vector3& v) const
    {
        return Vector3
        (
            DOT3STRIDED(vec, ptr(), 3),
            DOT3STRIDED(vec, ptr() + 1, 3),
            DOT3STRIDED(vec, ptr() + 2, 3)
        );
    }

    Vector4 Matrix3x3::transform(const Vector4& vec) const
    {
        return Vector4
        (
            DOT3(getRow(0), vec),
            DOT3(getRow(1), vec),
            DOT3(getRow(2), vec),
            vec.w
        );
    }

    void Matrix3x3::batchTransform(Vector3* points, int numPoints) const
    {
        if(!points || numPoints <= 0)
            return;

        for(int i = 0; i < numPoints; ++i)
        {
            points[i] = *this * points[i];
        }
    }

    void Matrix3x3::batchTransform(Vector3* points, int numPoints, int stride) const
    {
        if(!points || numPoints <= 0)
            return;
        aproassert(stride >= sizeof(Vector3));

        u8* data = reinterpret_cast<u8*>(points);
        for(int i = 0; i < numPoints; ++i)
        {
            Vector3* vec = reinterpret_cast<Vector3*>(data + stride * i);
            *vec = *this * *vec;
        }
    }

    void Matrix3x3::batchTransform(Vector4* points, int numPoints) const
    {
        if(!points || numPoints <= 0)
            return;

        for(int i = 0; i < numPoints; ++i)
        {
            points[i] = *this * points[i];
        }
    }

    void Matrix3x3::batchTransform(Vector4* points, int numPoints, int stride) const
    {
        if(!points || numPoints <= 0)
            return;
        aproassert(stride >= sizeof(Vector4));

        u8* data = reinterpret_cast<u8*>(points);
        for(int i = 0; i < numPoints; ++i)
        {
            Vector4* vec = reinterpret_cast<Vector4*>(data + stride * i);
            *vec = *this * *vec;
        }
    }

    Matrix3x3 Matrix3x3::operator * (const Matrix3x3& rhs) const
    {
        aproassert(isFinite(), "Matrix isn't finite !");
        aproassert(rhs.isFinite(), "Matrix given not finite !");

        Matrix3x3 r;
        const Real *c0 = rhs.ptr();
        const Real *c1 = rhs.ptr() + 1;
        const Real *c2 = rhs.ptr() + 2;
        r[0][0] = DOT3STRIDED(v[0], c0, 3);
        r[0][1] = DOT3STRIDED(v[0], c1, 3);
        r[0][2] = DOT3STRIDED(v[0], c2, 3);

        r[1][0] = DOT3STRIDED(v[1], c0, 3);
        r[1][1] = DOT3STRIDED(v[1], c1, 3);
        r[1][2] = DOT3STRIDED(v[1], c2, 3);

        r[2][0] = DOT3STRIDED(v[2], c0, 3);
        r[2][1] = DOT3STRIDED(v[2], c1, 3);
        r[2][2] = DOT3STRIDED(v[2], c2, 3);

        return r;
    }

    Matrix3x3 Matrix3x3::operator * (const Quaternion& rhs) const
    {
        return *this * Matrix3x3(rhs);
    }

    Vector3 Matrix3x3::operator * (const Vector3& rhs) const
    {
        return Vector3
        (
            DOT3(v[0], rhs),
            DOT3(v[1], rhs),
            DOT3(v[2], rhs)
        );
    }

    Vector4 Matrix3x3::operator * (const Vector4& rhs) const
    {
        return Vector4
        (
            DOT3(v[0], rhs),
            DOT3(v[1], rhs),
            DOT3(v[2], rhs),
            rhs.w
        );
    }

    Matrix3x3 Matrix3x3::operator * (const Real& scalar) const
    {
        Matrix3x3 r(*this);
        r *= scalar;
        return r;
    }

    Matrix3x3 Matrix3x3::operator / (const Real& scalar) const
    {
        Matrix3x3 r(*this);
        r /= scalar;
        return r;
    }

    Matrix3x3 Matrix3x3::operator + (const Matrix3x3& rhs) const
    {
        Matrix3x3 r(*this);
        r += rhs;
        return r;
    }

    Matrix3x3 Matrix3x3::operator - (const Matrix3x3& rhs) const
    {
        Matrix3x3 r(*this);
        r -= rhs;
        return r;
    }

    Matrix3x3& Matrix3x3::negate()
    {
        for(int i = 0; i < Rows; ++i)
            for(int j = 0; j < Cols; ++j)
                v[i][j] = -(v[i][j]);
        return *this;
    }

    Matrix3x3 Matrix3x3::negated() const
    {
        Matrix3x3 r(*this);
        return r.negate();
    }

    Matrix3x3& Matrix3x3::operator *= (const Real& scalar)
    {
        aproassert(IsFinite(scalar), "Scalar not finite !");

        for(int i = 0; i < Rows; ++i)
            for(int j = 0; j < Cols; ++j)
                v[i][j] *= scalar;

        return *this;
    }

    Matrix3x3& Matrix3x3::operator /= (const Real& scalar)
    {
        aproassert(IsFinite(scalar), "Scalar not finite !");
        aproassert(!(Math::equalErr<Real>(scalar, 0.f)), "Scalar is zero ! Can't divide by zero.");

        Real invScalar = 1.f / scalar;
        for(int i = 0; i < Rows; ++i)
            for(int j = 0; j < Cols; ++j)
                v[i][j] /= invScalar;

        return *this;
    }

    Matrix3x3& Matrix3x3::operator += (const Matrix3x3& rhs)
    {
        aproassert(rhhs.isFinite(), "Matrix not finite !");

        for(int i = 0; i < Rows; ++i)
            for(int j = 0; j < Cols; ++j)
                v[i][j] += rhs[i][j];

        return *this;
    }

    Matrix3x3& Matrix3x3::operator -= (const Matrix3x3& rhs)
    {
        aproassert(rhhs.isFinite(), "Matrix not finite !");

        for(int i = 0; i < Rows; ++i)
            for(int j = 0; j < Cols; ++j)
                v[i][j] -= rhs[i][j];

        return *this;
    }

    bool Matrix3x3::isFinite() const
    {
        for(int i = 0; i < Rows; ++i)
            for(int j = 0; j < Cols; ++j)
                if(!IsFinite(v[i][j]))
                    return false;
        return true;
    }

    bool Matrix3x3::isIdentity(Real epsilon) const
    {
        return this->equals(Matrix3x3::Identity, epsilon);
    }

    bool Matrix3x3::isLowerTriangular(Real epsilon) const
    {
        return Math::equalErr<Real>(v[0][1], 0.f, epsilon)
            && Math::equalErr<Real>(v[0][2], 0.f, epsilon)
            && Math::equalErr<Real>(v[1][2], 0.f, epsilon);
    }

    bool Matrix3x3::isUpperTriangular(Real epsilon) const
    {
        return Math::equalErr<Real>(v[1][0], 0.f, epsilon)
            && Math::equalErr<Real>(v[2][0], 0.f, epsilon)
            && Math::equalErr<Real>(v[2][1], 0.f, epsilon);
    }

    bool Matrix3x3::isInvertible(Real epsilon) const
    {
        return Math::equalErr<Real>(determinant(), 0.f, epsilon);
    }

    bool Matrix3x3::isSymmetric(Real epsilon) const
    {
        return Math::equalErr<Real>(v[0][1], v[1][0], epsilon)
            && Math::equalErr<Real>(v[0][2], v[2][0], epsilon)
            && Math::equalErr<Real>(v[1][2], v[2][1], epsilon);
    }

    bool Matrix3x3::isSkewSymmetric(Real epsilon) const
    {
        return Math::equalErr<Real>(v[0][0], 0.f, epsilon)
            && Math::equalErr<Real>(v[1][1], 0.f, epsilon)
            && Math::equalErr<Real>(v[2][2], 0.f, epsilon)
            && Math::equalErr<Real>(v[0][1], -v[1][0], epsilon)
            && Math::equalErr<Real>(v[0][2], -v[2][0], epsilon)
            && Math::equalErr<Real>(v[1][2], -v[2][1], epsilon);
    }

    bool Matrix3x3::hasUnitaryScale(Real epsilon) const
    {
        Vector3 scale = this->extractScale();
        return scale.equals(1.f, 1.f, 1.f, epsilon);
    }

    bool Matrix3x3::hasNegativeScale() const
    {
        return this->determinant() < 0.f;
    }

    bool Matrix3x3::hasUniformScale(Real epsilon) const
    {
        Vector3 scale = this->extractScale();
        return Math::equalErr<Real>(scale.x, scale.y, epsilon)
            && Math::equalErr<Real>(scale.x, scale.z, epsilon);
    }

    bool Matrix3x3::isRowOrthogonal(Real epsilon) const
    {
        return getRowRef(0).isPerpendicular(getRowRef(1), epsilon),
            && getRowRef(0).isPerpendicular(getRowRef(2), epsilon),
            && getRowRef(1).isPerpendicular(getRowRef(2), epsilon);
    }

    bool Matrix3x3::isColOrthogonal(Real epsilon) const
    {
        return getCol(0).isPerpendicular(getCol(1), epsilon),
            && getCol(0).isPerpendicular(getCol(2), epsilon),
            && getCol(1).isPerpendicular(getCol(2), epsilon);
    }

    bool Matrix3x3::isOrthonormal(Real epsilon) const
    {
        return isColOrthogonal(epsilon)
            && getRowRef(0).isNormalized(epsilon)
            && getRowRef(1).isNormalized(epsilon)
            && getRowRef(2).isNormalized(epsilon);
    }

    bool Matrix3x3::equals(const Matrix3x3& rhs, Real epsilon) const
    {
        for(int i = 0; i < Rows; ++i)
            for(int j = 0; j < Cols; ++j)
                if(!Math::equalErr<Real>(v[i][j], rhs[i][j], epsilon))
                    return false;
        return true;
    }

    Matrix3x3 Matrix3x3::LookAt(const Vector3 &localForward, const Vector3 &targetDirection, const Vector3 &localUp, const Vector3 &worldUp)
    {
        aproassert(localForward.isNormalized()
                && targetDirection.isNormalized()
                && localUp.isNormalized()
                && worldUp.isNormalized(),
                   "Can't create a lookAt matrix with non normalized vectors !");
        aproassert(localForward.isPerpendicular(localUp), "localForward and localUp argues not perpendicular !");

        Vector3 localRight = localUp.cross(localForward).normalized();
        Vector3 worldRight = worldUp.cross(targetDirection).normalized();
        Vector3 perpWorldUp = targetDirection.cross(worldRight).normalized();

        // We want to build a matrix M that performs the following mapping:
        // 1. localRight must be mapped to worldRight.        (M * localRight = worldRight)
        // 2. localUp must be mapped to perpWorldUp.          (M * localUp = perpWorldUp)
        // 3. localForward must be mapped to targetDirection. (M * localForward = targetDirection)

        // This matrix M exists, and it is an orthonormal rotation matrix with a determinant of +1, because
        // the bases A and B are orthonormal with the same handedness.

        // Below, use the notation that (a,b,c) is a 3x3 matrix with a as its first column, b second, and c third.

        // By algebraic manipulation, we can rewrite conditions 1, 2 and 3 in a matrix form:
        //        M * (localRight, localUp, localForward) = (worldRight, perpWorldUp, targetDirection)
        // or     M = (worldRight, perpWorldUp, targetDirection) * (localRight, localUp, localForward)^{-1}.

        Matrix3x3 m1(worldRight, perpWorldUp, targetDirection);

        Matrix3x3 m2;
        m2.setRow(0, localRight);
        m2.setRow(1, localUp);
        m2.setRow(2, localForward);

        m2 = m1 * m2;
        m2.orthonormalize(0,1,2);
        return m2;
    }

    void Matrix3x3::decompose(Quaternion& rotation, Vector3& scale) const
    {
        aproassert(this->isColOrthogonal(), "Matrix is not column orthogonal !");

        Matrix3x3 r;
        decompose(r, scale);
        rotation = Quaternion(r);
    }

    void Matrix3x3::decompose(Matrix3x3& rotation, Vector3& scale) const
    {
        aproassert(this->isColOrthogonal(), "Matrix is not column orthogonal !");

        rotation = *this;
        scale.x = rotation.getCol(0).lenght();
        scale.y = rotation.getCol(1).lenght();
        scale.z = rotation.getCol(2).lenght();

        if(!Math::equalErr<Real>(scale.x, 0))
            rotation.scaleCol(0, 1.f / scale.x);
        if(!Math::equalErr<Real>(scale.y, 0))
            rotation.scaleCol(1, 1.f / scale.y);
        if(!Math::equalErr<Real>(scale.z, 0))
            rotation.scaleCol(2, 1.f / scale.z);
    }

    const Matrix3x3 Matrix3x3::Zero     = Matrix3x3(0,0,0, 0,0,0, 0,0,0);
    const Matrix3x3 Matrix3x3::Identity = Matrix3x3(1,0,0, 0,1,0, 0,0,1);
    const Matrix3x3 Matrix3x3::Nan      = Matrix3x3(Math::_real_nan, Math::_real_nan, Math::_real_nan,
                                                    Math::_real_nan, Math::_real_nan, Math::_real_nan,
                                                    Math::_real_nan, Math::_real_nan, Math::_real_nan);

}
