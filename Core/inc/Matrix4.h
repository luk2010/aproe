/////////////////////////////////////////////////////////////
/** @file Matrix4.h
 *  @ingroup Utils
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 9/11/2012
 *
 *  Defines the Matrix4 class.
 *
**/
/////////////////////////////////////////////////////////////
#ifndef APROMATRIX4_H
#define APROMATRIX4_H

#include "Platform.h"
#include "Maths.h"
#include "Vector3.h"

namespace APro
{
    /////////////////////////////////////////////////////////////
    /** @class Matrix4x4
     *  @ingroup Utils
     *  @brief A 4 by 4 matrix.
     *  @details This matrix can represent the most generic form
     *  of transformation of a 3D object in space, including
     *  perspective projection, rotation, and translation.
    **/
    /////////////////////////////////////////////////////////////
    template <typename n>
    class Matrix4x4
    {
    protected:

        /// Specifies the height of the matrix.
        enum { Rows = 4 };

        /// Specifies the width of the matrix.
        enum { Cols = 4 };

        n v[Rows][Cols];

    public:

        /// A constant matrix that has zero in all his entries.
        static const Matrix4x4<n> zero;

        /// An identity matrix.
        static const Matrix4x4<n> identity;

    public:

        /////////////////////////////////////////////////////////////
        /** @brief Constructor.
        **/
        /////////////////////////////////////////////////////////////
        Matrix4x4();

        /////////////////////////////////////////////////////////////
        /** @brief Copy Constructor.
        **/
        /////////////////////////////////////////////////////////////
        Matrix4x4(const Matrix4x4<n>& other);

        /////////////////////////////////////////////////////////////
        /** @brief Constructor with all parameters.
        **/
        /////////////////////////////////////////////////////////////
        Matrix4x4(const n& _00, const n& _01, const n& _02, const n& _03,
                  const n& _10, const n& _11, const n& _12, const n& _13,
                  const n& _20, const n& _21, const n& _22, const n& _23,
                  const n& _30, const n& _31, const n& _32, const n& _33);



    };
}

#endif
