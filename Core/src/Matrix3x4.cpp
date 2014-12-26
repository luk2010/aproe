////////////////////////////////////////////////////////////
/** @file Matrix3x4.cpp
 *  @ingroup Maths
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 10/05/2014 - 30/06/2014
 *
 *  Implements the Matrix3x4 class.
 *
**/
////////////////////////////////////////////////////////////
#include "Matrix3x4.h"
#include "MatrixUtils.h"

namespace APro
{
    Matrix3x4::Matrix3x4()
    {
        Memory::Set(v, 0, Rows * Cols * sizeof(Real));
    }

    Matrix3x4::Matrix3x4(const Matrix3x4& other)
    {
        Memory::Copy(v, other.v, Rows * Cols * sizeof(Real));
    }

    Matrix3x4::Matrix3x4(Real _00, Real _01, Real _02, Real _03,
                         Real _10, Real _11, Real _12, Real _13,
                         Real _20, Real _21, Real _22, Real _23)
    {
        set(_00, _01, _02, _03,
            _10, _11, _12, _13,
            _20, _21, _22, _23);
    }

    Matrix3x4::Matrix3x4(const Matrix3x3& other)
    {
        setRotatePart(other);
        setTranslatePart(0, 0, 0);
    }

    Matrix3x4::Matrix3x4(const Matrix3x3& other, const Vector3& translation)
    {
        setRotatePart(other);
        setTranslatePart(translation);
    }

    Matrix3x4::Matrix3x4(const Quaternion& other)
    {
        setRotatePart(other);
        setTranslatePart(0, 0, 0);
    }

    Matrix3x4::Matrix3x4(const Quaternion& other, const Vector3& translation)
    {
        setRotatePart(other);
        setTranslatePart(translation);
    }

    Matrix3x4::~Matrix3x4()
    {

    }

    Matrix3x4 Matrix3x4::Translate(Real tx, Real ty, Real tz)
    {
        return Matrix3x4 (
                1, 0, 0, tx,
                0, 1, 0, ty,
                0, 0, 1, tz
            );
    }

    Matrix3x4 Matrix3x4::Translate(const Vector3& tv)
    {
        return Matrix3x4::Translate(tv.x, tv.y, tv.z);
    }

    Matrix3x4 Matrix3x4::Translate(const Vector4& tv)
    {
        return Matrix3x4::Translate(tv.x, tv.y, tv.z);
    }

    Matrix3x4 Matrix3x4::RotateX(Radian angle, const Vector3& pointOnAxis)
    {
        return Matrix3x4::Translate(pointOnAxis) * Matrix3x4::RotateX(angle) * Matrix3x4::Translate(pointOnAxis.negated());
    }

    Matrix3x4 Matrix3x4::RotateX(Radian angle)
    {
        Matrix3x4 ret;
        ret.setRotatePartX(angle);
        ret.setTranslatePart(0, 0, 0);
        return ret;
    }

    Matrix3x4 Matrix3x4::RotateY(Radian angle, const Vector3& pointOnAxis)
    {
        return Matrix3x4::Translate(pointOnAxis) * Matrix3x4::RotateY(angle) * Matrix3x4::Translate(pointOnAxis.negated());
    }

    Matrix3x4 Matrix3x4::RotateY(Radian angle)
    {
        Matrix3x4 ret;
        ret.setRotatePartY(angle);
        ret.setTranslatePart(0, 0, 0);
        return ret;
    }

    Matrix3x4 Matrix3x4::RotateZ(Radian angle, const Vector3& pointOnAxis)
    {
        return Matrix3x4::Translate(pointOnAxis) * Matrix3x4::RotateZ(angle) * Matrix3x4::Translate(pointOnAxis.negated());
    }

    Matrix3x4 Matrix3x4::RotateZ(Radian angle)
    {
        Matrix3x4 ret;
        ret.setRotatePartZ(angle);
        ret.setTranslatePart(0, 0, 0);
        return ret;
    }

    void Matrix3x4::set(Real _00, Real _01, Real _02, Real _03,
                  Real _10, Real _11, Real _12, Real _13,
                  Real _20, Real _21, Real _22, Real _23)
    {
        v[0][0] = _00; v[0][1] = _01; v[0][2] = _02; v[0][3] = _03;
        v[1][0] = _10; v[1][1] = _11; v[1][2] = _12; v[1][3] = _13;
        v[2][0] = _20; v[2][1] = _21; v[2][2] = _22; v[2][3] = _23;
    }

    void Matrix3x4::setRotatePart(const Matrix3x3& rotation)
    {
        set3x3Part(rotation);
    }

    void Matrix3x4::setRotatePart(const Quaternion& orientation)
    {
        MatrixUtils<Matrix3x4>::SetMatrixRotatePart(*this, orientation);
    }

    void Matrix3x4::set3x3Part(const Matrix3x3& r)
    {
        aproassert1(r.isFinite());
        v[0][0] = r[0][0]; v[0][1] = r[0][1]; v[0][2] = r[0][2];
        v[1][0] = r[1][0]; v[1][1] = r[1][1]; v[1][2] = r[1][2];
        v[2][0] = r[2][0]; v[2][1] = r[2][1]; v[2][2] = r[2][2];
    }

    void Matrix3x4::setTranslatePart(Real tx, Real ty, Real tz)
    {
        setCol(3, tx, ty, tz);
    }

    void Matrix3x4::setTranslatePart(const Vector3& translation)
    {
        setTranslatePart(translation.x, translation.y, translation.z);
    }

    void Matrix3x4::setCol(int idx, Real t1, Real t2, Real t3)
    {
        aproassert1(idx >= 0 && idx < Cols);
        aproassert1(Math::IsFinite(t1) && Math::IsFinite(t2) && Math::IsFinite(t3));

        v[0][idx] = t1;
        v[1][idx] = t2;
        v[2][idx] = t3;
    }

    Matrix3x4 Matrix3x4::operator * (const Matrix3x4& m)
    {
        Matrix3x4 r;

        const Real *c0 = m.ptr();
        const Real *c1 = m.ptr() + 1;
        const Real *c2 = m.ptr() + 2;
        const Real *c3 = m.ptr() + 3;
        r[0][0] = DOT3STRIDED(v[0], c0, 4);
        r[0][1] = DOT3STRIDED(v[0], c1, 4);
        r[0][2] = DOT3STRIDED(v[0], c2, 4);
        r[0][3] = DOT3STRIDED(v[0], c3, 4) + v[0][3];

        r[1][0] = DOT3STRIDED(v[1], c0, 4);
        r[1][1] = DOT3STRIDED(v[1], c1, 4);
        r[1][2] = DOT3STRIDED(v[1], c2, 4);
        r[1][3] = DOT3STRIDED(v[1], c3, 4) + v[1][3];

        r[2][0] = DOT3STRIDED(v[2], c0, 4);
        r[2][1] = DOT3STRIDED(v[2], c1, 4);
        r[2][2] = DOT3STRIDED(v[2], c2, 4);
        r[2][3] = DOT3STRIDED(v[2], c3, 4) + v[2][3];

        return r;
    }

    void Matrix3x4::setRotatePartX(Radian angle)
    {
        MatrixUtils<Matrix3x4>::Set3x3RotatePartX(*this, angle);
    }

    void Matrix3x4::setRotatePartY(Radian angle)
    {
        MatrixUtils<Matrix3x4>::Set3x3RotatePartY(*this, angle);
    }

    void Matrix3x4::setRotatePartZ(Radian angle)
    {
        MatrixUtils<Matrix3x4>::Set3x3RotatePartZ(*this, angle);
    }

    void Matrix3x4::fromQuaternion(const Quaternion& quat)
    {
        setRotatePart(quat);
        setTranslatePart(0,0,0);
    }

    Matrix3x4 Matrix3x4::FromQuaternion(const Quaternion& quat)
    {
        Matrix3x4 r;
        r.fromQuaternion(quat);
        return r;
    }

    Matrix3x4 Matrix3x4::FromQuaternion(const Quaternion& quat, const Vector3& pointOnAxis)
    {
        return Matrix3x4::Translate(pointOnAxis) * Matrix3x4::FromQuaternion(quat) * Matrix3x4::Translate(-pointOnAxis);
    }
}
