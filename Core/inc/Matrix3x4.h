////////////////////////////////////////////////////////////
/** @file Matrix3x4.h
 *  @ingroup Maths
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 7/10/2013 - 30/06/2014
 *
 *  Defines the Matrix3x4 class.
 *
**/
////////////////////////////////////////////////////////////
#ifndef APRO_MATRIX3X4_H
#define APRO_MATRIX3X4_H

#include "Platform.h"
#include "Matrix3x3.h"

namespace APro
{
    class Quaternion;

    ////////////////////////////////////////////////////////////
    /** @class Matrix3x4
     *  @ingroup Maths
     *  @brief A matrix 3 by 4.
     *
     *  This matrix type can represent affine operations in addition
     *  to linear ones. Affine operations translate the geometry with
     *  respect to the origin point, whereas linear transformations retain
     *  the origin of the coordinate system in place.
     *
     *  The elements of this matrix are

		m_00, m_01, m_02, m_03
		m_10, m_11, m_12, m_13
		m_20, m_21, m_22, m_23

	 *  The element m_yx is the value on the row y and column x.
	 *  You can access m_yx using the double-bracket notation m[y][x], or
	 *  using the member function m.At(y, x);
	 *
	 *  @note The member functions in this class use the convention that
	 *  transforms are applied to vectors in the form M * v. This means that
	 *  "Matrix3x4 M, M1, M2; M = M1 * M2;" gives a transformation M that applies
	 *  M2 first, followed by M1 second, i.e. M * v = M1 * M2 * v = M1 * (M2 * v).
	 *  This is the convention commonly used with OpenGL. The opposing convention
	 *  (v * M) is commonly used with Direct3D.
     *
	 *  @note This class uses row-major storage, which means that the elements are
	 *  packed in memory in order m[0][0], m[0][1], m[0][2], m[0][3], m[1][0], m[1][1], ...
     *  The elements for a single row of the matrix hold successive memory addresses.
     *  This is the same memory layout as with C++ multidimensional arrays.
    **/
    ////////////////////////////////////////////////////////////
    class APRO_DLL Matrix3x4
    {
    public:

        /// Specifies the height of this matrix.
        enum { Rows = 3 };

        /// Specifies the width of this matrix.
        enum { Cols = 4 };

        Real v[Rows][Cols]; ///< Stores the data in this matrix in row-major format.

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Constructs an empty Matrix3x4.
        **/
        ////////////////////////////////////////////////////////////
        Matrix3x4();

        ////////////////////////////////////////////////////////////
        /** @brief Constructs a Matrix3x4 from a copy.
        **/
        ////////////////////////////////////////////////////////////
        Matrix3x4(const Matrix3x4& other);


        ////////////////////////////////////////////////////////////
        /** @brief Constructs a new Mattrix3x4 by explicitly specifying
         *  all the matrix elements.
        **/
        ////////////////////////////////////////////////////////////
        Matrix3x4(Real _00, Real _01, Real _02, Real _03,
                  Real _10, Real _11, Real _12, Real _13,
                  Real _20, Real _21, Real _22, Real _23);

        ////////////////////////////////////////////////////////////
        /** @brief Constructs a new Matrix3x4 to represent the same
         *  transformation of given Matrix3x3.
        **/
        ////////////////////////////////////////////////////////////
        Matrix3x4(const Matrix3x3& other);

        ////////////////////////////////////////////////////////////
        /** @brief Constructs a new Matrix3x4 to represent the same
         *  transformation of given Matrix3x3 and Vector3 translation.
        **/
        ////////////////////////////////////////////////////////////
        Matrix3x4(const Matrix3x3& other, const Vector3& translation);

        ////////////////////////////////////////////////////////////
        /** @brief Constructs a new Matrix3x4 to represent the same
         *  transformation as Quaternion.
        **/
        ////////////////////////////////////////////////////////////
        explicit Matrix3x4(const Quaternion& other);

        ////////////////////////////////////////////////////////////
        /** @brief Constructs a new Matrix3x4 to represent the same
         *  transformation as Quaternion and given translation.
        **/
        ////////////////////////////////////////////////////////////
        Matrix3x4(const Quaternion& other, const Vector3& translation);

        ////////////////////////////////////////////////////////////
        /** @brief Destructs the Matrix3x4 object.
        **/
        ////////////////////////////////////////////////////////////
        ~Matrix3x4();

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Creates a new Matrix3x4 object that translates by
         *  the given offset.
        **/
        ////////////////////////////////////////////////////////////
        static Matrix3x4 Translate(Real tx, Real ty, Real tz);

        ////////////////////////////////////////////////////////////
        /** @brief Creates a new Matrix3x4 object that translates by
         *  the given offset.
        **/
        ////////////////////////////////////////////////////////////
        static Matrix3x4 Translate(const Vector3& tv);

        ////////////////////////////////////////////////////////////
        /** @brief Creates a new Matrix3x4 object that translates by
         *  the given offset.
         *  @note The w component is ignored.
        **/
        ////////////////////////////////////////////////////////////
        static Matrix3x4 Translate(const Vector4& tv);

        ////////////////////////////////////////////////////////////
        /** @brief Creates a new Matrix3x4 object that rotates about
         *  the X axis.
         *  @param angle : The angle to rotate by, in radians. For example,
         *  Pi/4.f equals to 45 degrees, Pi/2.f is 90 degrees, and Pi is 180
         *  degrees.
         *  @param pointOnAxis : The rotation is performed about an axis that
         *  passes through this point, and not through the origin. The returned
         *  matrix will not be a pure rotation matrix, but will also contain
         *  translation.
        **/
        ////////////////////////////////////////////////////////////
        static Matrix3x4 RotateX(Radian angle, const Vector3& pointOnAxis);

        ////////////////////////////////////////////////////////////
        /** @brief Creates a new Matrix3x4 object that rotates about
         *  the X axis.
         *  @param angle : The angle to rotate by, in radians. For example,
         *  Pi/4.f equals to 45 degrees, Pi/2.f is 90 degrees, and Pi is 180
         *  degrees.
        **/
        ////////////////////////////////////////////////////////////
        static Matrix3x4 RotateX(Radian angle);

        ////////////////////////////////////////////////////////////
        /** @brief Creates a new Matrix3x4 object that rotates about
         *  the Y axis.
         *  @param angle : The angle to rotate by, in radians. For example,
         *  Pi/4.f equals to 45 degrees, Pi/2.f is 90 degrees, and Pi is 180
         *  degrees.
         *  @param pointOnAxis : The rotation is performed about an axis that
         *  passes through this point, and not through the origin. The returned
         *  matrix will not be a pure rotation matrix, but will also contain
         *  translation.
        **/
        ////////////////////////////////////////////////////////////
        static Matrix3x4 RotateY(Radian angle, const Vector3& pointOnAxis);

        ////////////////////////////////////////////////////////////
        /** @brief Creates a new Matrix3x4 object that rotates about
         *  the Y axis.
         *  @param angle : The angle to rotate by, in radians. For example,
         *  Pi/4.f equals to 45 degrees, Pi/2.f is 90 degrees, and Pi is 180
         *  degrees.
        **/
        ////////////////////////////////////////////////////////////
        static Matrix3x4 RotateY(Radian angle);

        ////////////////////////////////////////////////////////////
        /** @brief Creates a new Matrix3x4 object that rotates about
         *  the Z axis.
         *  @param angle : The angle to rotate by, in radians. For example,
         *  Pi/4.f equals to 45 degrees, Pi/2.f is 90 degrees, and Pi is 180
         *  degrees.
         *  @param pointOnAxis : The rotation is performed about an axis that
         *  passes through this point, and not through the origin. The returned
         *  matrix will not be a pure rotation matrix, but will also contain
         *  translation.
        **/
        ////////////////////////////////////////////////////////////
        static Matrix3x4 RotateZ(Radian angle, const Vector3& pointOnAxis);

        ////////////////////////////////////////////////////////////
        /** @brief Creates a new Matrix3x4 object that rotates about
         *  the Z axis.
         *  @param angle : The angle to rotate by, in radians. For example,
         *  Pi/4.f equals to 45 degrees, Pi/2.f is 90 degrees, and Pi is 180
         *  degrees.
        **/
        ////////////////////////////////////////////////////////////
        static Matrix3x4 RotateZ(Radian angle);


    public:

        ////////////////////////////////////////////////////////////
        /** @brief Sets all values of this matrix.
        **/
        ////////////////////////////////////////////////////////////
        void set(Real _00, Real _01, Real _02, Real _03,
                  Real _10, Real _11, Real _12, Real _13,
                  Real _20, Real _21, Real _22, Real _23);

        ////////////////////////////////////////////////////////////
        /** @brief Sets the 3-by-3 part of this matrix.
         *  @note This is a convenience function which calls Set3x3Part.
         *  @note This function erases the previous top-left 3x3 part of
         *  this matrix (any previous rotation, scaling and shearing, etc.).
         *  Translation is unaffected.
        **/
        ////////////////////////////////////////////////////////////
        void setRotatePart(const Matrix3x3& rotation);

        ////////////////////////////////////////////////////////////
        /** @brief Sets the 3-by-3 part of this matrix to perform the
         *  rotation expressed by the given quaternion.
         *  @note Leaves all other entries of this matrix untouched.
        **/
        ////////////////////////////////////////////////////////////
        void setRotatePart(const Quaternion& orientation);

        ////////////////////////////////////////////////////////////
        /** @brief Sets the 3-by-3 part of this matrix to perform rotation
         *  about the positive X axis which passes through the origin.
         *  @note Leaves all other entries of this matrix untouched.
        **/
        ////////////////////////////////////////////////////////////
        void setRotatePartX(Radian angle);

        ////////////////////////////////////////////////////////////
        /** @brief Sets the 3-by-3 part of this matrix to perform rotation
         *  about the positive Y axis which passes through the origin.
         *  @note Leaves all other entries of this matrix untouched.
        **/
        ////////////////////////////////////////////////////////////
        void setRotatePartY(Radian angle);

        ////////////////////////////////////////////////////////////
        /** @brief Sets the 3-by-3 part of this matrix to perform rotation
         *  about the positive Z axis which passes through the origin.
         *  @note Leaves all other entries of this matrix untouched.
        **/
        ////////////////////////////////////////////////////////////
        void setRotatePartZ(Radian angle);

        ////////////////////////////////////////////////////////////
        /** @brief Sets the 3-by-3 part of this matrix.
         *  @note This function erases the previous top-left 3x3 part of
         *  this matrix (any previous rotation, scaling and shearing, etc.).
         *  Translation is unaffected.
        **/
        ////////////////////////////////////////////////////////////
        void set3x3Part(const Matrix3x3& part);

        ////////////////////////////////////////////////////////////
        /** @brief Sets the translate part of this matrix.
        **/
        ////////////////////////////////////////////////////////////
        void setTranslatePart(Real tx, Real ty, Real tz);

        ////////////////////////////////////////////////////////////
        /** @brief Sets the translate part of this matrix.
        **/
        ////////////////////////////////////////////////////////////
        void setTranslatePart(const Vector3& translation);

        ////////////////////////////////////////////////////////////
        /** @brief Sets the given column.
        **/
        ////////////////////////////////////////////////////////////
        void setCol(int idx, Real t1, Real t2, Real t3);

        ////////////////////////////////////////////////////////////
        /** @brief Sets this matrix representing the rotation expressed
         *  by given quaternion.
        **/
        ////////////////////////////////////////////////////////////
        void fromQuaternion(const Quaternion& quat);
        static Matrix3x4 FromQuaternion(const Quaternion& quat);

        ////////////////////////////////////////////////////////////
        /** @brief Sets this matrix representing the rotation expressed
         *  by given quaternion centered by given point.
        **/
        ////////////////////////////////////////////////////////////
        static Matrix3x4 FromQuaternion(const Quaternion& quat, const Vector3& pointOnAxis);

    public:

        Real* ptr() { return v[0]; }
        const Real* ptr() const { return v[0]; }

        Real* operator [] (int idx) { return v[idx]; }
        const Real* operator [] (int idx) const { return v[idx]; }

        Matrix3x4 operator * (const Matrix3x4& m);


    public:

        static const Matrix3x4 Zero;
        static const Matrix3x4 Identity;
        static const Matrix3x4 Nan;
    };
}

#endif // APRO_MATRIX3X4_H
