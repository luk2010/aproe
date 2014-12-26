////////////////////////////////////////////////////////////
/** @file Matrix3x3.h
 *  @ingroup Maths
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 12/09/2013
 *
 *  Defines the Matrix3x3 class.
 *
**/
////////////////////////////////////////////////////////////
#ifndef APRO_MATRIX3X3_H
#define APRO_MATRIX3X3_H

#include "Platform.h"
#include "Vector3.h"
#include "Vector4.h"

namespace APro
{
    class Quaternion;
    class Plane;

    ////////////////////////////////////////////////////////////
    /** @class Matrix3x3
     *  @ingroup Maths
     *  @brief A matrix 3 by 3.
     *
     *  This matrix can represent any kind of linear transformations
     *  of 3D geometry, which include rotation, scale, shear, mirroring
     *  and orthographic projection. A 3x3 matrix cannot represent translation
     *  (which requires a 3x4 matrix), or perspective projection (which
     *  requires a 4x4 matrix).
     *
     *  The elements of this matrix are

		m_00, m_01, m_02
		m_10, m_11, m_12
		m_20, m_21, m_22

	 *  The element m_yx is the value on the row y and column x.
	 *  You can access m_yx using the double-bracket notation m[y][x], or
	 *  using the member function m.At(y, x);
	 *
	 *  @note The member functions in this class use the convention that
	 *  transforms are applied to vectors in the form M * v. This means that
	 *  "Matrix3x3 M, M1, M2; M = M1 * M2;" gives a transformation M that applies
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
    class APRO_DLL Matrix3x3
    {
    public:

        /// Specifies the height of this matrix.
        enum { Rows = 3 };

        /// Specifies the width of this matrix.
        enum { Cols = 3 };

        Real v[Rows][Cols]; ///< Stores the data in this matrix in row-major format.

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Creates a new Matrix3x3 with uninitialized member
         *  values.
        **/
        ////////////////////////////////////////////////////////////
        Matrix3x3() {}

        ////////////////////////////////////////////////////////////
        /** @brief Creates a new Matrix3x3 by explicitly specifying
         *  all the matrix elements.
        **/
        ////////////////////////////////////////////////////////////
        Matrix3x3(Real _00, Real _01, Real _02,
                  Real _10, Real _11, Real _12,
                  Real _20, Real _21, Real _22 );

        ////////////////////////////////////////////////////////////
        /** @brief Creates a new Matrix3x3 by explicitly specifying
         *  the three column vectors.
         *
         *  @param col0 : The first column. If this matrix represents a
         *  change-of-basis transformation, this parameter is the world-space
		 *  direction of the local X axis.
		 *
		 *  @param col1 : The second column. If this matrix represents a
         *  change-of-basis transformation, this parameter is the world-space
		 *  direction of the local Y axis.
		 *
		 *  @param col2 : The third column. If this matrix represents a
         *  change-of-basis transformation, this parameter is the world-space
		 *  direction of the local Z axis.
        **/
        ////////////////////////////////////////////////////////////
        Matrix3x3(const Vector3& col0, const Vector3& col1, const Vector3& col2);

        ////////////////////////////////////////////////////////////
        /** @brief Creates a new Matrix3x3 from a quaternion.
        **/
        ////////////////////////////////////////////////////////////
        explicit Matrix3x3(const Quaternion& q);

        ////////////////////////////////////////////////////////////
        /** @brief Creates a new Matrix3x3 from a Matrix3x3.
        **/
        ////////////////////////////////////////////////////////////
        Matrix3x3(const Matrix3x3& other);

        ////////////////////////////////////////////////////////////
        /** @brief Destructs the matrix.
        **/
        ////////////////////////////////////////////////////////////
        ~Matrix3x3() { }

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Copy given matrix into this one.
        **/
        ////////////////////////////////////////////////////////////
        void set(const Matrix3x3& m) { set((const Real*) m.v); }

        ////////////////////////////////////////////////////////////
        /** @brief Sets every values of this Matrix.
        **/
        ////////////////////////////////////////////////////////////
        void set(Real _00, Real _01, Real _02,
                  Real _10, Real _11, Real _12,
                  Real _20, Real _21, Real _22 );


        ////////////////////////////////////////////////////////////
        /** @brief Sets every values of this Matrix by a standard
         *  C multidimensionnal array.
        **/
        ////////////////////////////////////////////////////////////
        void set(const Real* m);

        ////////////////////////////////////////////////////////////
        /** @brief Set the specified value in given row/col.
        **/
        ////////////////////////////////////////////////////////////
        void set(size_t row, size_t col, const Real& _v);

        ////////////////////////////////////////////////////////////
        /** @brief Sets the specified column values to given Vector3.
        **/
        ////////////////////////////////////////////////////////////
        void setCol(size_t col, const Vector3& values);

        ////////////////////////////////////////////////////////////
        /** @brief Sets the specified column values.
        **/
        ////////////////////////////////////////////////////////////
        void setCol(size_t col, const Real& x, const Real& y, const Real& z);

        ////////////////////////////////////////////////////////////
        /** @brief Sets the specified column values.
        **/
        ////////////////////////////////////////////////////////////
        void setCol(size_t col, const Real* r);

        ////////////////////////////////////////////////////////////
        /** @brief Sets the specified row values.
        **/
        ////////////////////////////////////////////////////////////
        void setRow(size_t row, const Vector3& values);

        ////////////////////////////////////////////////////////////
        /** @brief Sets the specified row values.
        **/
        ////////////////////////////////////////////////////////////
        void setRow(size_t row, const Real& x, const Real& y, const Real& z);

        ////////////////////////////////////////////////////////////
        /** @brief Sets the specified row values.
        **/
        ////////////////////////////////////////////////////////////
        void setRow(size_t row, const Real* r);

        ////////////////////////////////////////////////////////////
        /** @brief Sets this matrix to perform the rotation expressed
         *  by the given quaternion.
        **/
        ////////////////////////////////////////////////////////////
        void setRotatePart(const Quaternion& q);

        ////////////////////////////////////////////////////////////
        /** @brief Sets this matrix to perform the rotation expressed
         *  by the given direction axis and the given angle.
        **/
        ////////////////////////////////////////////////////////////
        void setRotatePart(const Vector3& axisDirection, const Radian& angle);

        ////////////////////////////////////////////////////////////
        /** @brief Sets this matrix to perform rotation about the positive
         *  X axis which passes through the origin.
        **/
        ////////////////////////////////////////////////////////////
        void setRotatePartX(const Radian& a);

        ////////////////////////////////////////////////////////////
        /** @brief Sets this matrix to perform rotation about the positive
         *  Y axis which passes through the origin.
        **/
        ////////////////////////////////////////////////////////////
        void setRotatePartY(const Radian& a);

        ////////////////////////////////////////////////////////////
        /** @brief Sets this matrix to perform rotation about the positive
         *  Z axis which passes through the origin.
        **/
        ////////////////////////////////////////////////////////////
        void setRotatePartZ(const Radian& a);

        ////////////////////////////////////////////////////////////
        /** @brief Creates a matrix from a quaternion.
        **/
        ////////////////////////////////////////////////////////////
        void fromQuaternion(const Quaternion& q);
        static Matrix3x3 FromQuaternion(const Quaternion& q)
        {
            Matrix3x3 result;
            result.fromQuaternion(q);
            return result;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Creates a quaternion from this matrix.
         *
         *  This function assumes that the matrix is orthonormal (no shear
         *  or scaling) and does not perform any mirroring (determinant > 0).
        **/
        ////////////////////////////////////////////////////////////
        Quaternion toQuaternion() const;
        static Quaternion ToQuaternion(const Matrix3x3& m);

        ////////////////////////////////////////////////////////////
        /** @brief Sets every entries of this matrix to 0.
        **/
        ////////////////////////////////////////////////////////////
        void setZero();

        ////////////////////////////////////////////////////////////
        /** @brief Sets this matrix to the identity matrix.
        **/
        ////////////////////////////////////////////////////////////
        void setIdentity();

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Returns a pointer to a row of this matrix.
        **/
        ////////////////////////////////////////////////////////////
        Real* getRow(size_t row) { return v[row]; }
        Real* operator [](size_t row)
        {
            return getRow(row);
        }

        ////////////////////////////////////////////////////////////
        /** @brief Returns a pointer to a row of this matrix.
        **/
        ////////////////////////////////////////////////////////////
        const Real* getRow(size_t row) const { return v[row]; }
        const Real* operator [](size_t row) const
        {
            return getRow(row);
        }

        ////////////////////////////////////////////////////////////
        /** @brief Returns given row as a Vector3.
        **/
        ////////////////////////////////////////////////////////////
        Vector3& getRowRef(size_t row) { return *(reinterpret_cast<Vector3*>(getRow(row))); }

        ////////////////////////////////////////////////////////////
        /** @brief Returns given row as a Vector3.
        **/
        ////////////////////////////////////////////////////////////
        const Vector3& getRowRef(size_t row) const { return *(reinterpret_cast<const Vector3*>(getRow(row))); }

        ////////////////////////////////////////////////////////////
        /** @brief Returns a reference to a case of the matrix.
        **/
        ////////////////////////////////////////////////////////////
        Real& getRowCol(size_t row, size_t col) { return v[row][col]; }

        ////////////////////////////////////////////////////////////
        /** @brief Returns a reference to a case of the matrix.
        **/
        ////////////////////////////////////////////////////////////
        const Real& getRowCol(size_t row, size_t col) const { return v[row][col]; }

        ////////////////////////////////////////////////////////////
        /** @brief Returns the three values of a given column.
        **/
        ////////////////////////////////////////////////////////////
        Vector3 getCol(size_t col) const;

        ////////////////////////////////////////////////////////////
        /** @brief Returns the Diagonal of this matrix.
        **/
        ////////////////////////////////////////////////////////////
        Vector3 diagonale() const;

        Real* ptr() { return &v[0][0]; }
        const Real* ptr() const { return &v[0][0]; }

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Returns the scale components of this matrix.
         *
         *  This function decomposes this matrix M into a form M = M' * S,
         *  where M' has unitary column vectors and S is a diagonal matrix.
         *
		 *  @return extractScale returns the diagonal entries of S, i.e.
		 *  the scale of the columns of this matrix . If this matrix represents
		 *  a local->world space transformation for an object, then this scale
		 *  represents a 'local scale', i.e. scaling that is performed before
		 *  translating and rotating the object from its local coordinate system
		 *  to its world position.
        **/
        ////////////////////////////////////////////////////////////
        Vector3 extractScale() const;

        ////////////////////////////////////////////////////////////
        /** @brief Scale this matrix with the given scalars.
         *
         *  This function multiply this matrix by the matrix created
         *  using the given scale factors.
        **/
        ////////////////////////////////////////////////////////////
        void setScale(Real sx, Real sy, Real sz);

        ////////////////////////////////////////////////////////////
        /** @brief Scale this matrix with the given scalars.
         *
         *  This function multiply this matrix by the matrix created
         *  using the given scale factors.
        **/
        ////////////////////////////////////////////////////////////
        void setScale(const Vector3& scalef);

        ////////////////////////////////////////////////////////////
        /** @brief Returns the scaling performed by this matrix.
         *
         *  getScale().x specifies the amount of scaling applied to the
         *  local x direction vector when it is transformed by this matrix.
        **/
        ////////////////////////////////////////////////////////////
        Vector3 getScale() const;

        ////////////////////////////////////////////////////////////
        /** @brief Removes the scaling performed by this matrix.
         *
         *  That is, decomposes this matrix M into a form M = M' * S,
         *  where M' has unitary column vectors and S is a diagonal matrix.
         *  Then replaces this matrix with M'.
        **/
        ////////////////////////////////////////////////////////////
        void removeScale();

        ////////////////////////////////////////////////////////////
        /** @brief Scale a row by a given scalar.
        **/
        ////////////////////////////////////////////////////////////
        void scaleRow(size_t row, Real scalar);

        ////////////////////////////////////////////////////////////
        /** @brief Scale a column by a given scalar.
        **/
        ////////////////////////////////////////////////////////////
        void scaleCol(size_t col, Real scalar);

        ////////////////////////////////////////////////////////////
        /** @brief Returns a scaling matrix.
        **/
        ////////////////////////////////////////////////////////////
        static Matrix3x3 Scale(Real sx, Real sy, Real sz);

        ////////////////////////////////////////////////////////////
        /** @brief Returns a scaling matrix.
        **/
        ////////////////////////////////////////////////////////////
        static Matrix3x3 Scale(const Vector3& scalef);

        ////////////////////////////////////////////////////////////
        /** @brief reates a new Matrix3x3 that scales points along the
         *  given axis.
         *
         *  @param axis : A normalized direction vector that specifies
         *  the direction of scaling.
         *  @param scalef : The amount of scaling to apply along the
         *  specified axis.
        **/
        ////////////////////////////////////////////////////////////
        static Matrix3x3 ScaleAlongAxis(const Vector3& axis, Real scalef);

        ////////////////////////////////////////////////////////////
        /** @brief Creates a new Matrix3x3 that performs uniform scaling
         *  by the given amount.
        **/
        ////////////////////////////////////////////////////////////
        static Matrix3x3 UniformScale(Real uniformScale);

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Produces a matrix that shears along a principal axis.
         *
         *  The shear matrix offsets the two other axes according to the
		 *  position of the point along the shear axis.
        **/
        ////////////////////////////////////////////////////////////
        static Matrix3x3 ShearX(Real yFactor, Real zFactor);

        ////////////////////////////////////////////////////////////
        /** @brief Produces a matrix that shears along a principal axis.
         *
         *  The shear matrix offsets the two other axes according to the
		 *  position of the point along the shear axis.
        **/
        ////////////////////////////////////////////////////////////
        static Matrix3x3 ShearY(Real xFactor, Real zFactor);

        ////////////////////////////////////////////////////////////
        /** @brief Produces a matrix that shears along a principal axis.
         *
         *  The shear matrix offsets the two other axes according to the
		 *  position of the point along the shear axis.
        **/
        ////////////////////////////////////////////////////////////
        static Matrix3x3 ShearZ(Real xFactor, Real yFactor);

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Creates a new matrix that mirrors with respect to
         *  the given plane.
         *
         *  Points lying on one side of the plane will end up at the
         *  opposite side of the plane, at the same distance of the plane
		 *  they were.
        **/
        ////////////////////////////////////////////////////////////
        static Matrix3x3 Mirror(const Plane& p);

        ////////////////////////////////////////////////////////////
        /** @brief Creates a new Matrix3x3 that performs orthographic
         *  projection.
        **/
        ////////////////////////////////////////////////////////////
        static Matrix3x3 OrthographicProjection(const Plane& target);

        ////////////////////////////////////////////////////////////
        /** @brief Creates a new Matrix3x3 that performs orthographic
         *  projection.
        **/
        ////////////////////////////////////////////////////////////
        static Matrix3x3 OrthographicProjectionYZ();

        ////////////////////////////////////////////////////////////
        /** @brief Creates a new Matrix3x3 that performs orthographic
         *  projection.
        **/
        ////////////////////////////////////////////////////////////
        static Matrix3x3 OrthographicProjectionXZ();

        ////////////////////////////////////////////////////////////
        /** @brief Creates a new Matrix3x3 that performs orthographic
         *  projection.
        **/
        ////////////////////////////////////////////////////////////
        static Matrix3x3 OrthographicProjectionXY();

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Swap two rows.
        **/
        ////////////////////////////////////////////////////////////
        void swapRow(size_t row1, size_t row2);

        ////////////////////////////////////////////////////////////
        /** @brief Swap two columns.
        **/
        ////////////////////////////////////////////////////////////
        void swapCol(size_t col1, size_t col2);

    public:

        Matrix3x3& operator = (const Matrix3x3& m) { set(m); return *this; }
        Matrix3x3& operator = (const Quaternion& q) { fromQuaternion(q); return *this; }

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Computes the determinant of this matrix.
         *
         *  If the determinant is nonzero, this matrix is invertible.
		 *  If the determinant is negative, this matrix performs reflection
		 *  about some axis.
		 *
		 *  From http://msdn.microsoft.com/en-us/library/bb204853(VS.85).aspx :
		 *  "If the determinant is positive, the basis is said to be "positively"
		 *  oriented (or right-handed).
		 *  If the determinant is negative, the basis is said to be "negatively"
		 *  oriented (or left-handed)."
		 *
		 *  @note This function computes 9 MULs and 5 ADDs.
        **/
        ////////////////////////////////////////////////////////////
        Real determinant() const;

        ////////////////////////////////////////////////////////////
        /** @brief Computes the determinant of a symmetric matrix.
         *
         *  This function can be used to compute the determinant of a
         *  matrix in the case the matrix is known beforehand to be
         *  symmetric. This function is slightly faster than Determinant().
         *
         *  @note This function computes 9 MULs and 4 ADDs.
        **/
        ////////////////////////////////////////////////////////////
        Real determinantSymmetric() const;

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Invert this matrix using gaussian elimination.
        **/
        ////////////////////////////////////////////////////////////
        bool inverse(Real epsilon = 1e-3f);

        ////////////////////////////////////////////////////////////
        /** @brief Return an inverted copy of this matrix.
        **/
        ////////////////////////////////////////////////////////////
        Matrix3x3 inversed(Real epsilon = 1e-3f) const;

        ////////////////////////////////////////////////////////////
        /** @brief Invert this matrix using Cramer's rule.
         *
         *  This function is faster than Matrix3x3::inverse, but it is
         *  also highly unsure !
        **/
        ////////////////////////////////////////////////////////////
        bool inverseFast(Real epsilon = 1e-3f);

        ////////////////////////////////////////////////////////////
        /** @brief Return a fast inverted copy of this matrix.
         *
         *  @see inverseFast()
        **/
        ////////////////////////////////////////////////////////////
        Matrix3x3 inversedFast(Real epsilon = 1e-3f) const;

        ////////////////////////////////////////////////////////////
        /** @brief Inverts a column-orthogonal matrix.
         *
         *  If a matrix is of form M=R*S, where R is a rotation matrix
         *  and S is a diagonal matrix with non-zero but potentially non-uniform
         *  scaling factors (possibly mirroring), then the matrix M is column-orthogonal
         *  and this function can be used to compute the inverse.
	     *
	     *  Calling this function is faster than the calling the generic matrix
	     *  inverse() function.
	     *
	     *  @return True on success. On failure, the matrix is not modified. This
	     *  function fails if any of the elements of this vector are not finite,
	     *  or if the matrix contains a zero scaling factor on X, Y or Z.
	     *
	     *  @note The returned matrix will be row-orthogonal, but not column-orthogonal
	     *  in general. The returned matrix will be column-orthogonal if the original
	     *  matrix M was row-orthogonal as well. (in which case S had uniform scale,
         *  inverseOrthogonalUniformScale() could have been used instead)
        **/
        ////////////////////////////////////////////////////////////
        bool inverseColOrthogonal();

        ////////////////////////////////////////////////////////////
        /** @brief Inverts a matrix that is a concatenation of only
         *  rotate and uniform scale operations.
         *
         *  If a matrix is of form M=R*S, where R is a rotation matrix and
         *  S is a diagonal matrix with non-zero and uniform scaling factors
         *  (possibly mirroring), then the matrix M is both column- and
         *  row-orthogonal and this function can be used to compute the inverse.
         *
	     *  This function is faster than calling inverseColOrthogonal() or
	     *  the generic inverse().
	     *
	     *  @return True on success. On failure, the matrix is not modified.
	     *  This function fails if any of the elements of this vector are not
	     *  finite, or if the matrix contains a zero scaling factor on X, Y or Z.
	     *
         *  @note This function may not be called if this matrix contains any
         *  shearing or nonuniform scaling.
        **/
        ////////////////////////////////////////////////////////////
        bool inverseOrthogonalUniformScale();

        ////////////////////////////////////////////////////////////
        /** @brief Inverts a rotation matrix.
         *
         *  If a matrix is of form M=R*S, where R is a rotation matrix
         *  and S is either identity or a mirroring matrix, then the matrix
         *  M is orthonormal and this function can be used to compute the
         *  inverse.
         *
	     *  This function is faster than calling inverseOrthogonalUniformScale(),
	     *  inverseColOrthogonal() or the generic inverse().
	     *
	     *  @note This function may not be called if this matrix contains any
	     *  scaling or shearing, but it may contain mirroring.
        **/
        ////////////////////////////////////////////////////////////
        void inverseOrthonormal();

        ////////////////////////////////////////////////////////////
        /** @brief Inverts a symmetric matrix.
         *
         *  This function is faster than directly calling inverse().
		 *  It computes 6 LOADs, 9 STOREs, 21 MULs, 1 DIV, 1 CMP and
		 *  8 ADDs.
		 *
		 *  @return True if computing the inverse succeeded, false
		 *  otherwise (determinant was zero). If this function fails,
         *  the original matrix is not modified.
         *
		 *  @note This function operates in-place.
        **/
        ////////////////////////////////////////////////////////////
        bool inverseSymmetric();

        ////////////////////////////////////////////////////////////
        /** @brief Transposes this matrix.
         *
         *  This operation swaps all elements with respect to the diagonal.
        **/
        ////////////////////////////////////////////////////////////
        void transpose();

        ////////////////////////////////////////////////////////////
        /** @brief Returns a transposed copy of this matrix.
        **/
        ////////////////////////////////////////////////////////////
        Matrix3x3 transposed() const;

        ////////////////////////////////////////////////////////////
        /** @brief Computes the inverse transpose of this matrix in-place.
         *
         *  Use the inverse transpose to transform covariant vectors
         *  (normal vectors).
        **/
        ////////////////////////////////////////////////////////////
        bool inverseTranspose();

        ////////////////////////////////////////////////////////////
        /** @brief Return an inverse transposed copy of this matrix.
         *
         *  Use the inverse transpose to transform covariant vectors
         *  (normal vectors).
        **/
        ////////////////////////////////////////////////////////////
        Matrix3x3 inverseTransposed() const;

        ////////////////////////////////////////////////////////////
        /** @brief Solves the linear equation Ax=b.
         *
         *  The matrix A in the equations is this matrix.
        **/
        ////////////////////////////////////////////////////////////
        bool solveAxb(Vector3 b, Vector3& x) const;

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Return the sum of the diagonal elements of this
         *  matrix.
        **/
        ////////////////////////////////////////////////////////////
        Real trace() const;

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Orthonormalizes the basis formed by the column vectors
         *  of this matrix.
        **/
        ////////////////////////////////////////////////////////////
        void orthonormalize(size_t firstColumn, size_t secondColumn, size_t thirdColumn);

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Transforms the given 3-vector by this matrix M, i.e.
         *  returns M * (x, y, z).
        **/
        ////////////////////////////////////////////////////////////
        Vector3 transform(const Vector3& vec) const;

        ////////////////////////////////////////////////////////////
        /** @brief Transforms the given 3-vector by this matrix M, i.e.
         *  returns M * (x, y, z).
        **/
        ////////////////////////////////////////////////////////////
        Vector3 transform(Real x, Real y, Real z) const;

        ////////////////////////////////////////////////////////////
        /** @brief Transforms the given 3-vector by this matrix M so
         *  that the vector occurs on the left-hand side.
        **/
        ////////////////////////////////////////////////////////////
        Vector3 transformLeft(const Vector3& vec) const;

        ////////////////////////////////////////////////////////////
        /** @brief Transforms the given 4-vector by this matrix M, i.e.
         *  returns M * (x, y, z, w).
         *
         *  This function ignores the w component of the given input
         *  vector. This component is assumed to be either 0 or 1.
        **/
        ////////////////////////////////////////////////////////////
        Vector4 transform(const Vector4& vec) const;

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Performs a batch transform of the given array.
        **/
        ////////////////////////////////////////////////////////////
        void batchTransform(Vector3* points, int numPoints) const;

        ////////////////////////////////////////////////////////////
        /** @brief Performs a batch transform of the given array.
        **/
        ////////////////////////////////////////////////////////////
        void batchTransform(Vector3* points, int numPoints, int stride) const;

        ////////////////////////////////////////////////////////////
        /** @brief Performs a batch transform of the given array.
        **/
        ////////////////////////////////////////////////////////////
        void batchTransform(Vector4* points, int numPoints) const;

        ////////////////////////////////////////////////////////////
        /** @brief Performs a batch transform of the given array.
        **/
        ////////////////////////////////////////////////////////////
        void batchTransform(Vector4* points, int numPoints, int stride) const;

    public:

        Matrix3x3 operator * (const Matrix3x3& rhs) const;
        Matrix3x3 operator * (const Quaternion& rhs) const;

        Vector3 operator * (const Vector3& rhs) const;
        Vector4 operator * (const Vector4& rhs) const;

        Matrix3x3 operator * (const Real& scalar) const;
        Matrix3x3 operator / (const Real& scalar) const;
        Matrix3x3 operator + (const Matrix3x3& rhs) const;
        Matrix3x3 operator - (const Matrix3x3& rhs) const;

        ////////////////////////////////////////////////////////////
        /** @brief Negate every members of this matrix.
        **/
        ////////////////////////////////////////////////////////////
        Matrix3x3& negate();

        ////////////////////////////////////////////////////////////
        /** @brief Returns a negated copy of this matrix.
        **/
        ////////////////////////////////////////////////////////////
        Matrix3x3 negated() const;
        Matrix3x3 operator -() const
        {
            return negated();
        }

        Matrix3x3& operator *= (const Real& scalar);
        Matrix3x3& operator *= (const Matrix3x3& scalar);
        Matrix3x3& operator /= (const Real& scalar);
        Matrix3x3& operator += (const Matrix3x3& rhs);
        Matrix3x3& operator -= (const Matrix3x3& rhs);

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Tests if this matrix does not contain any NaNs or infs.
        **/
        ////////////////////////////////////////////////////////////
        bool isFinite() const;

        ////////////////////////////////////////////////////////////
        /** @brief Tests if this matrix corresponds to the Identity
         *  matrix.
        **/
        ////////////////////////////////////////////////////////////
        bool isIdentity(Real epsilon = 1e-3f) const;

        ////////////////////////////////////////////////////////////
        /** @brief Tests if this matrix is in lower triangular form.
        **/
        ////////////////////////////////////////////////////////////
        bool isLowerTriangular(Real epsilon = 1e-3f) const;

        ////////////////////////////////////////////////////////////
        /** @brief Tests if this matrix is in upper triangular form.
        **/
        ////////////////////////////////////////////////////////////
        bool isUpperTriangular(Real epsilon = 1e-3f) const;

        ////////////////////////////////////////////////////////////
        /** @brief Tests if this matrix is invertible.
        **/
        ////////////////////////////////////////////////////////////
        bool isInvertible(Real epsilon = 1e-3f) const;

        ////////////////////////////////////////////////////////////
        /** @brief Tests if this matrix is symmetric.
         *
         *  The test compares the elements for equality, up to the given
         *  epsilon. A matrix is symmetric if it is its own transpose.
        **/
        ////////////////////////////////////////////////////////////
        bool isSymmetric(Real epsilon = 1e-3f) const;

        ////////////////////////////////////////////////////////////
        /** @brief Tests if this matrix is skew symmetric.
         *
         *  The test compares the floating point elements of this matrix
         *  up to the given epsilon. A matrix M is skew-symmetric the identity
         *  M=-M^T holds.
        **/
        ////////////////////////////////////////////////////////////
        bool isSkewSymmetric(Real epsilon = 1e-3f) const;

        ////////////////////////////////////////////////////////////
        /** @brief Returns true if this matrix does not perform any
         *  scaling.
         *
         *  A matrix does not do any scaling if the column vectors of
         *  this matrix are normalized in length, compared to the given
         *  epsilon. Note that this matrix may still perform reflection,
         *  i.e. it has a -1 scale along some axis.
        **/
        ////////////////////////////////////////////////////////////
        bool hasUnitaryScale(Real epsilon = 1e-3f) const;

        ////////////////////////////////////////////////////////////
        /** @brief Returns true if this matrix performs a reflection
         *  along some plane.
         *
         *  In 3D space, an even number of reflections corresponds to
         *  a rotation about some axis, so a matrix consisting of an
         *  odd number of consecutive mirror operations can only reflect
         *  about one axis. A matrix that contains reflection reverses
         *  the handedness of the coordinate system. This function tests
         *  if this matrix does perform mirroring. This occurs if this
         *  matrix has a negative determinant.
        **/
        ////////////////////////////////////////////////////////////
        bool hasNegativeScale() const;

        ////////////////////////////////////////////////////////////
        /** @brief Returns true if this matrix contains only uniform
         *  scaling, compared to the given epsilon.
         *
         *  @note If the matrix does not really do any scaling, this
         *  function returns true (scaling uniformly by a factor of 1).
        **/
        ////////////////////////////////////////////////////////////
        bool hasUniformScale(Real epsilon = 1e-3f) const;

        ////////////////////////////////////////////////////////////
        /** @brief Returns true if the row vectors of this matrix are
         *  all perpendicular to each other.
        **/
        ////////////////////////////////////////////////////////////
        bool isRowOrthogonal(Real epsilon = 1e-3f) const;

        ////////////////////////////////////////////////////////////
        /** @brief Returns true if the column vectors of this matrix are
         *  all perpendicular to each other.
        **/
        ////////////////////////////////////////////////////////////
        bool isColOrthogonal(Real epsilon = 1e-3f) const;

        ////////////////////////////////////////////////////////////
        /** @brief Returns true if the column and row vectors of this
         *  matrix form an orthonormal set.
         *
         *  @note A matrix is orthonormal if the column and row vectors
         *  are orthonormal.
        **/
        ////////////////////////////////////////////////////////////
        bool isOrthonormal(Real epsilon = 1e-3f) const;

        ////////////////////////////////////////////////////////////
        /** @brief Returns true if this matrix equals to the given
         *  matrix, compared to the given epsilon.
        **/
        ////////////////////////////////////////////////////////////
        bool equals(const Matrix3x3& rhs, Real epsilon = 1e-3f) const;

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Creates a look-at matrix.
         *
         *  A LookAt matrix is a rotation matrix that orients an object
         *  to face towards a specified target direction.
         *
		 *  @param localForward : Specifies the forward direction in the
		 *  local space of the object. This is the direction the model is
		 *  facing at in its own local/object space, often +X (1,0,0),
		 *  +Y (0,1,0) or +Z (0,0,1). The vector to pass in here depends
		 *  on the conventions you or your modeling software is using, and
		 *  it is best pick one convention for all your objects, and be consistent.
         *  This input parameter must be a normalized vector.
         *
		 *  @param targetDirection : Specifies the desired world space direction
		 *  the object should look at. This function will compute a rotation
		 *  matrix which will rotate the localForward vector to orient towards
		 *  this targetDirection vector.
		 *  This input parameter must be a normalized vector.
		 *
		 *  @param localUp : Specifies the up direction in the local space of
		 *  the object. This is the up direction the model was authored in, often
		 *  +Y (0,1,0) or +Z (0,0,1). The vector to pass in here depends on the
		 *  conventions you or your modeling software is using, and it is best to
		 *  pick one convention for all your objects, and be consistent.
		 *  This input parameter must be a normalized vector.
		 *  This vector must be perpendicular to the vector localForward, i.e.
		 *  localForward.dot(localUp) == 0.
		 *
		 *  @param worldUp : Specifies the global up direction of the scene in
		 *  world space. Simply rotating one vector to coincide with another
		 *  (localForward->targetDirection) would cause the up direction of the resulting
         *  orientation to drift (e.g. the model could be looking at its target its
         *  head slanted sideways). To keep the up direction straight, this function orients
         *  the localUp direction of the model to point towards the specified worldUp
         *  direction (as closely as possible). The worldUp and targetDirection vectors
         *  cannot be collinear, but they do not need to be perpendicular either.
         *
		 *  @return A matrix that maps the given local space forward direction vector to
		 *  point towards the given target direction, and the given local up
		 *  direction towards the given target world up direction. This matrix can
		 *  be used as the 'world transform' of an object. The returned matrix M
		 *  is orthonormal with a determinant of +1. For the matrix M it holds that
		 *  M * localForward = targetDirection, and M * localUp lies in the plane spanned
		 *  by the vectors targetDirection and worldUp.
		 *
		 *  @see RotateFromTo().
		 *
		 *  @note The returned matrix is a mapping from local space to world space, meaning
		 *  that the returned matrix can be used as the 'world transform' for any 3D object
		 *  (camera or not). The view space is the local space of the camera, so this function
		 *  returns the mapping view->world. In GLM, the LookAt function is tied to cameras
		 *  only, and it returns the inverse mapping world->view.
        **/
        ////////////////////////////////////////////////////////////
        static Matrix3x3 LookAt(const Vector3 &localForward, const Vector3 &targetDirection, const Vector3 &localUp, const Vector3 &worldUp);

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Decomposes this matrix to rotate and scale parts.
         *
         *  This function decomposes this matrix M to a form M = R * S,
         *  where R a rotation matrix and S a scale matrix.
         *
         *  @note Remember that in the convention of this class, transforms
         *  are applied in the order M * v, so scale is applied first, then
         *  rotation, and finally the translation last.
         *
         *  @param rotation [out] : This object receives the rotation part
         *  of this transform.
		 *  @param scale [out] : This vector receives the scaling along the
		 *  local (before transformation by R) X, Y and Z axes performed by
		 *  this matrix.
        **/
        ////////////////////////////////////////////////////////////
        void decompose(Quaternion& rotation, Vector3& scale) const;

        ////////////////////////////////////////////////////////////
        /** @brief Decomposes this matrix to rotate and scale parts.
         *
         *  This function decomposes this matrix M to a form M = R * S,
         *  where R a rotation matrix and S a scale matrix.
         *
         *  @note Remember that in the convention of this class, transforms
         *  are applied in the order M * v, so scale is applied first, then
         *  rotation, and finally the translation last.
         *
         *  @param rotation [out] : This object receives the rotation part
         *  of this transform.
		 *  @param scale [out] : This vector receives the scaling along the
		 *  local (before transformation by R) X, Y and Z axes performed by
		 *  this matrix.
        **/
        ////////////////////////////////////////////////////////////
        void decompose(Matrix3x3& rotation, Vector3& scale) const;

    public:

        static const Matrix3x3 Zero;
        static const Matrix3x3 Identity;
        static const Matrix3x3 Nan;
    };
}

#endif // APRO_MATRIX3X3_H
