////////////////////////////////////////////////////////////
/** @file Matrix4x4.h
 *  @ingroup Maths
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 17/06/2014 - 30/06/2014
 *
 *  Defines the Matrix4x4 class.
 *
**/
////////////////////////////////////////////////////////////
#ifndef APRO_MATRIX3X4_H
#define APRO_MATRIX3X4_H

#include "Platform.h"

namespace APro
{
    class Quaternion;

    ////////////////////////////////////////////////////////////
    /** @class Matrix4x4
     *  @ingroup Maths
     *  @brief A 4-by-4 matrix for affine transformations and perspective
     *  projections of 3D geometry.
     *
     *  This matrix can represent the most generic form of transformations
     *  for 3D objects, including perspective projections, which Matrix3x4
     *  cannot store, and translations, which float3x3 cannot represent.
     *
     *  The elements of this matrix are

		m_00, m_01, m_02, m_03
		m_10, m_11, m_12, m_13
		m_20, m_21, m_22, m_23
		m_30, m_31, m_32, m_33

	 *  The element m_yx is the value on the row y and column x.
	 *  You can access m_yx using the double-bracket notation m[y][x], or
	 *  using the member function m.At(y, x);
	 *
	 *  @note The member functions in this class use the convention that
	 *  transforms are applied to vectors in the form M * v. This means that
	 *  "Matrix4x4 M, M1, M2; M = M1 * M2;" gives a transformation M that applies
	 *  M2 first, followed by M1 second, i.e. M * v = M1 * M2 * v = M1 * (M2 * v).
	 *  This is the convention commonly used with OpenGL. The opposing convention
	 *  (v * M) is commonly used with Direct3D.
    **/
    ////////////////////////////////////////////////////////////
    class APRO_DLL Matrix4x4
    {
    public:

        /// Specifies the height of this matrix.
        enum { Rows = 4 };

        /// Specifies the width of this matrix.
        enum { Cols = 4 };

        Real v[Rows][Cols]; ///< Stores the data in this matrix in row-major format.

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Constructs an empty Matrix4x4.
        **/
        ////////////////////////////////////////////////////////////
        Matrix4x4() {}

    public:

        void fromQuaternion(const Quaternion& quat) {}
    };
}

#endif // APRO_MATRIX3X4_H
