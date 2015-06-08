////////////////////////////////////////////////////////////
/** @file Matrix4x4.h
 *  @ingroup Maths
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 17/06/2014 - 10/04/2015
 *
 *  @brief
 *  Defines the Matrix4x4 class.
 *
 *  @copyright
 *  Atlanti's Project Engine
 *  Copyright (C) 2012 - 2015  Atlanti's Corp
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
        
        Real* operator[] (uint32_t row) { return v[row]; }
        Real* operator[] (int32_t row) {
        	if(!Numeric::IsInRange(row, 0, Rows - 1))
				throw BadRangeAccessException(String::Build("Matrix4x4::operator[] (%i)", row).toCstChar(), row, 0, Rows);
			return v[row];
        }
    };
}

#endif // APRO_MATRIX3X4_H
