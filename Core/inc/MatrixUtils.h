////////////////////////////////////////////////////////////
/** @file MatrixUtils.h
 *  @ingroup Maths
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 21/09/2013 - 10/06/2014
 *
 *  Defines some private usefull template matrix functions.
 *
**/
////////////////////////////////////////////////////////////
#ifndef APRO_MATRIXUTILS_H
#define APRO_MATRIXUTILS_H

#include "Platform.h"
#include "Maths.h"
#include "Quaternion.h"

namespace APro
{
    template <typename Matrix>
    class MatrixUtils
    {
    public:

        ////////////////////////////////////////////////////////////
        /** @brief Inverse the given matrix with an error of epsilon.
        **/
        ////////////////////////////////////////////////////////////
        static bool InverseMatrix(Matrix& mat, Real epsilon)
        {
            Matrix inversed = Matrix::Identity; // will contain the inverse matrix

            for(int column = 0; column < Numeric::Min((int) Matrix::Rows, (int) Matrix::Cols); ++column)
            {
                // find the row i with i >= j such that M has the largest absolute value.
                int greatest = column;
                for(int i = column; i < Matrix::Rows; i++)
                    if (Math::Abs(mat[i][column]) > Math::Abs(mat[greatest][column]))
                        greatest = i;

                if (Math::EqualsAbs(mat[greatest][column], 0, epsilon))
                {
                    mat = inversed;
                    return false;
                }

                // exchange rows
                if (greatest != column)
                {
                    inversed.swapRow(greatest, column);
                    mat.swapRow(greatest, column);
                }

                // multiply rows
                aproassert(!Math::EqualsAbs(mat[column][column], 0.f, epsilon), "Error in Matrix Inversion !");
                inversed.scaleRow(column, 1.f / mat[column][column]);
                mat.scaleRow(column, 1.f / mat[column][column]);

                // add rows
                for(int i = 0; i < Matrix::Rows; i++)
                    if (i != column)
                    {
                        inversed.setRow(i, inversed.getRowRef(i) - inversed.getRowRef(column) * mat[i][column]);
                        mat.setRow(i, mat.getRowRef(i) - mat.getRowRef(column) * mat[i][column]);
                    }
            }
            mat = inversed;

            return true;
        }

        static void SetMatrixRotatePart(Matrix& m, const Quaternion& quat)
        {
            // See e.g. http://www.geometrictools.com/Documentation/LinearAlgebraicQuaternions.pdf .

            aproassert1(quat.isNormalized());
            const Real x = quat.m_x; const Real y = quat.m_y; const Real z = quat.m_z; const Real w = quat.m_w;
            m[0][0] = 1 - 2*(y*y + z*z); m[0][1] =     2*(x*y - z*w); m[0][2] =     2*(x*z + y*w);
            m[1][0] =     2*(x*y + z*w); m[1][1] = 1 - 2*(x*x + z*z); m[1][2] =     2*(y*z - x*w);
            m[2][0] =     2*(x*z - y*w); m[2][1] =     2*(y*z + x*w); m[2][2] = 1 - 2*(x*x + y*y);
        }

        static void Set3x3RotatePartX(Matrix& m, Radian angle)
        {
            Real sinz, cosz;
            sinz = Angle::Sin(angle);
            cosz = Angle::Cos(angle);

            m[0][0] = 1.f; m[0][1] =  0.f; m[0][2] =   0.f;
            m[1][0] = 0.f; m[1][1] = cosz; m[1][2] = -sinz;
            m[2][0] = 0.f; m[2][1] = sinz; m[2][2] =  cosz;
        }

        static void Set3x3RotatePartY(Matrix& m, Radian angle)
        {
            Real sinz, cosz;
            sinz = Angle::Sin(angle);
            cosz = Angle::Cos(angle);

            m[0][0] =  cosz; m[0][1] = 0.f; m[0][2] = sinz;
            m[1][0] =   0.f; m[1][1] = 1.f; m[1][2] =  0.f;
            m[2][0] = -sinz; m[2][1] = 0.f; m[2][2] = cosz;
        }

        static void Set3x3RotatePartZ(Matrix& m, Radian angle)
        {
            Real sinz, cosz;
            sinz = Angle::Sin(angle);
            cosz = Angle::Cos(angle);

            m[0][0] = cosz; m[0][1] = -sinz; m[0][2] = 0.f;
            m[1][0] = sinz; m[1][1] =  cosz; m[1][2] = 0.f;
            m[2][0] =  0.f; m[2][1] =   0.f; m[2][2] = 1.f;
        }

    };
}

#endif // APRO_MATRIXUTILS_H
