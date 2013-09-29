////////////////////////////////////////////////////////////
/** @file MatrixUtils.h
 *  @ingroup Maths
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 21/09/20013
 *
 *  Defines some private usefull template matrix functions.
 *
**/
////////////////////////////////////////////////////////////
#ifndef APRO_MATRIXUTILS_H
#define APRO_MATRIXUTILS_H

#include "Platform.h"
#include "Maths.h"

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

            for(int column = 0; column < Numeric::Min(Matrix::Rows, Matrix::Cols); ++column)
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
                    inversed.swapRows(greatest, column);
                    mat.swapRows(greatest, column);
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
    };
}

#endif // APRO_MATRIXUTILS_H
