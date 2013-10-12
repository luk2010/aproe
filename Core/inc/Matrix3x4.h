////////////////////////////////////////////////////////////
/** @file Matrix3x4.h
 *  @ingroup Maths
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 7/10/2013
 *
 *  Defines the Matrix3x4 class.
 *
**/
////////////////////////////////////////////////////////////
#ifndef APRO_MATRIX3X4_H
#define APRO_MATRIX3X4_H

#include "Platform.h"

namespace APro
{
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



    public:

        static const Matrix3x4 Zero;
        static const Matrix3x4 Identity;
        static const Matrix3x4 Nan;
    };
}

#endif // APRO_MATRIX3X4_H
