////////////////////////////////////////////////////////////
/** @file Vector2.h
 *  @ingroup Maths
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 26/09/2012
 *
 *  Defines the Vector2 class.
 *
**/
////////////////////////////////////////////////////////////
#ifndef APROVECTOR2_H
#define APROVECTOR2_H

#include "Platform.h"
#include "Console.h"
#include "SString.h"
#include <typeinfo>

namespace APro
{
    ////////////////////////////////////////////////////////////
    /** @class Vector2
     *  @ingroup Maths
    **/
    ////////////////////////////////////////////////////////////
    class Vector2
    {
    public:

        Real x;///< X value of this vector.
        Real y;///< Y value of this vector.

    public: // Constructors

        ////////////////////////////////////////////////////////////
        /** @brief Constructor.
         *  @details Set coordinates to (0,0).
        **/
        ////////////////////////////////////////////////////////////
        Vector2();

        ////////////////////////////////////////////////////////////
        /** @brief Copy Constructor.
         *  @details Set coordinates to (v.x, v.y).
        **/
        ////////////////////////////////////////////////////////////
        Vector2(const Vector2& v);

        ////////////////////////////////////////////////////////////
        /** @brief Constructor.
         *  @details Set coordinates to (n1, n2).
        **/
        ////////////////////////////////////////////////////////////
        Vector2(const Real& n1, const Real& n2);

        ////////////////////////////////////////////////////////////
        /** @brief Constructor.
         *  @details Set coordinates to (n, n).
        **/
        ////////////////////////////////////////////////////////////
        explicit Vector2(const Real& n);

        ////////////////////////////////////////////////////////////
        /** @brief Constructor from array.
         *  @details Set coordinates to (n[0], n[1]).
        **/
        ////////////////////////////////////////////////////////////
        explicit Vector2(const Real n[2]);

        ////////////////////////////////////////////////////////////
        /** @brief Destructor.
        **/
        ////////////////////////////////////////////////////////////
        ~Vector2();

    public: // Swap function

        ////////////////////////////////////////////////////////////
        /** @brief Swap current vector with given one.
         *  @param v : Vector to swap.
         *  @note It use xor swapping.
        **/
        ////////////////////////////////////////////////////////////
        inline void swap(Vector2& v);

    public: // Egality operators

        ////////////////////////////////////////////////////////////
        /** @brief Tell if 2 vectors are equals.
        **/
        ////////////////////////////////////////////////////////////
        bool equals(const Vector2& v) const;

        ////////////////////////////////////////////////////////////
        /** @brief Tell if vector is equal to 2 given numerics.
        **/
        ////////////////////////////////////////////////////////////
        bool equals(const Real& n1, const Real& n2) const;

        bool operator == (const Vector2& v) const;
        bool operator != (const Vector2& v) const;

    public: // Superior / inferior strict operators

        bool operator > (const Vector2& v) const;
        bool operator < (const Vector2& v) const;

    public: // Superior / inferior operators

        bool operator >= (const Vector2& v) const;
        bool operator <= (const Vector2& v) const;

    public: // Assignment operators

        ////////////////////////////////////////////////////////////
        /** @brief Set coordinates to given vector.
        **/
        ////////////////////////////////////////////////////////////
        Vector2& set(const Vector2& v);

        ////////////////////////////////////////////////////////////
        /** @brief Set coordinates to given pair.
        **/
        ////////////////////////////////////////////////////////////
        Vector2& set(const Real& n1, const Real& n2);

        ////////////////////////////////////////////////////////////
        /** @brief Set coordinates to given numeric.
        **/
        ////////////////////////////////////////////////////////////
        Vector2& set(const Real& n);

        Vector2& operator = (const Vector2& v);
        Vector2& operator = (const Real& n);

    public: // Floor / ceil

        ////////////////////////////////////////////////////////////
        /** @brief Floor the current vector with given one.
         *
         *  It takes the minimum value for each coordinate and
         *  attriutes it to this vector.
        **/
        ////////////////////////////////////////////////////////////
        void floor(const Vector2& v);

        ////////////////////////////////////////////////////////////
        /** @brief Ceil current vector with given one.
         *
         *  It takes the maximum value for each coordinate and
         *  attriutes it to this vector.
        **/
        ////////////////////////////////////////////////////////////
        void ceil(const Vector2& v);

    public: // Addition

        ////////////////////////////////////////////////////////////
        /** @brief Add a vector to this one.
         *  @param v : Vector to add.
        **/
        ////////////////////////////////////////////////////////////
        Vector2& add(const Vector2& v);

        ////////////////////////////////////////////////////////////
        /** @brief Add a numeric to this one.
         *  @param n : Numeric to add.
         *  @return (x + n, y + n)
        **/
        ////////////////////////////////////////////////////////////
        Vector2& add(const Real& n);

        ////////////////////////////////////////////////////////////
        /** @brief Return the vector when adding given one.
         *  @param v : Vector to add.
        **/
        ////////////////////////////////////////////////////////////
        Vector2 added(const Vector2& v) const;

        ////////////////////////////////////////////////////////////
        /** @brief Return the vector when adding given numeric.
         *  @param n : Numeric to add.
         *  @return (x + n, y + n)
        **/
        ////////////////////////////////////////////////////////////
        Vector2 added(const Real& n) const;

        Vector2& operator += (const Vector2& v);
        Vector2& operator += (const Real& n);
        Vector2  operator +  (const Vector2& v) const;
        Vector2  operator +  (const Real& n)    const;

    public: // Substraction

        ////////////////////////////////////////////////////////////
        /** @brief Substract a vector to this one.
         *  @param v : Vector to substract.
        **/
        ////////////////////////////////////////////////////////////
        Vector2& substract(const Vector2& v);

        ////////////////////////////////////////////////////////////
        /** @brief Substract a numeric to this one.
         *  @param n : Numeric to substract.
         *  @return (x - n, y - n)
        **/
        ////////////////////////////////////////////////////////////
        Vector2& substract(const Real& n);

        ////////////////////////////////////////////////////////////
        /** @brief Return the vector if a substraction was applied
         *  to this one.
         *  @param v : Vector to substract.
        **/
        ////////////////////////////////////////////////////////////
        Vector2 substracted(const Vector2& v) const;

        ////////////////////////////////////////////////////////////
        /** @brief Return the vector if a substraction was applied
         *  to this one.
         *  @param n : Numeric to substract.
        **/
        ////////////////////////////////////////////////////////////
        Vector2 substracted(const Real& n) const;

        Vector2& operator -= (const Vector2& v);
        Vector2& operator -= (const Real& n);
        Vector2  operator -  (const Vector2& v)  const;
        Vector2  operator -  (const Real& n)     const;

    public: // Multiplication

        ////////////////////////////////////////////////////////////
        /** @brief Multiply a vector to this one.
         *  @param v : Vector to Multiply.
        **/
        ////////////////////////////////////////////////////////////
        Vector2& multiply(const Vector2& v);

        ////////////////////////////////////////////////////////////
        /** @brief Multiply a numeric to this one.
         *  @param n : Numeric to Multiply.
         *  @return (x * n, y * n)
        **/
        ////////////////////////////////////////////////////////////
        Vector2& multiply(const Real& n);

        ////////////////////////////////////////////////////////////
        /** @brief Return the vector if a multiplication was applied
         *  to this one.
         *  @param v : Vector to Multiply.
        **/
        ////////////////////////////////////////////////////////////
        Vector2 multiplied(const Vector2& v) const;

        ////////////////////////////////////////////////////////////
        /** @brief Return the vector if a multiplication was applied
         *  to this one.
         *  @param n : Numeric to multiply.
        **/
        ////////////////////////////////////////////////////////////
        Vector2 multiplied(const Real& n) const;

        Vector2& operator *= (const Vector2& v);
        Vector2& operator *= (const Real& n);
        Vector2  operator *  (const Vector2& v) const;
        Vector2  operator *  (const Real& n)    const;

    public: // Division

        ////////////////////////////////////////////////////////////
        /** @brief Divide a vector to this one.
         *  @param v : Vector to divide.
        **/
        ////////////////////////////////////////////////////////////
        Vector2& divide(const Vector2& v);

        ////////////////////////////////////////////////////////////
        /** @brief Divide a numeric to this one.
         *  @param n : Numeric to divide.
         *  @return (x / n, y / n)
        **/
        ////////////////////////////////////////////////////////////
        Vector2& divide(const Real& n);

        ////////////////////////////////////////////////////////////
        /** @brief Return the vector if a division was applied
         *  to this one.
         *  @param v : Vector to divide.
        **/
        ////////////////////////////////////////////////////////////
        Vector2 divided(const Vector2& v) const;

        ////////////////////////////////////////////////////////////
        /** @brief Return the vector if a division was applied
         *  to this one.
         *  @param n : Numeric to divide.
        **/
        ////////////////////////////////////////////////////////////
        Vector2 divided(const Real& n) const;

        Vector2& operator /= (const Vector2& v);
        Vector2& operator /= (const Real& n);

        Vector2 operator / (const Vector2& v) const;
        Vector2 operator / (const Real& n)    const;

    public: // Access

        ////////////////////////////////////////////////////////////
        /** @brief Return either x or y.
         *  @note If i = 0, x is returned, otherweise y is returned
         *  for any value of i superior to 0.
        **/
        ////////////////////////////////////////////////////////////
        const Real& at(size_t i) const;

        ////////////////////////////////////////////////////////////
        /** @brief Return either x or y.
         *  @note If i = 0, x is returned, otherweise y is returned
         *  for any value of i superior to 0.
        **/
        ////////////////////////////////////////////////////////////
        Real& at(size_t i);

        const Real& operator[](size_t i) const;
        Real& operator[](size_t i);

        ////////////////////////////////////////////////////////////
        /** @brief Return a pointer to data.
        **/
        ////////////////////////////////////////////////////////////
        const Real* ptr() const;

        ////////////////////////////////////////////////////////////
        /** @brief Return a pointer to data.
        **/
        ////////////////////////////////////////////////////////////
        Real* ptr();

    public: // Absolute, Negation

        inline Vector2 operator + () const;
        inline Vector2 operator - () const;

        ////////////////////////////////////////////////////////////
        /** @brief Negate coordinates and return the vector.
        **/
        ////////////////////////////////////////////////////////////
        Vector2& negate();

        ////////////////////////////////////////////////////////////
        /** @brief Return a vector from negated one.
        **/
        ////////////////////////////////////////////////////////////
        Vector2 negated() const;

        ////////////////////////////////////////////////////////////
        /** @brief Return a vector from abs coordinates.
        **/
        ////////////////////////////////////////////////////////////
        Vector2 absoluted() const;

        ////////////////////////////////////////////////////////////
        /** @brief Absolute coordinates of this vector and return it.
        **/
        ////////////////////////////////////////////////////////////
        Vector2& absolute();

        ////////////////////////////////////////////////////////////
        /** @brief Invert coordinates.
        **/
        ////////////////////////////////////////////////////////////
        Vector2& invert();

        ////////////////////////////////////////////////////////////
        /** @brief Return a vector with inverted coordinates.
        **/
        ////////////////////////////////////////////////////////////
        Vector2& inverted() const;

    public: // Lenght

        ////////////////////////////////////////////////////////////
        /** @brief Return computed lenght of this vector.
        **/
        ////////////////////////////////////////////////////////////
        Real lenght() const;

        ////////////////////////////////////////////////////////////
        /** @brief Return squared computed lenght of this vector.
        **/
        ////////////////////////////////////////////////////////////
        Real squaredLenght() const;

    public: // Distance

        ////////////////////////////////////////////////////////////
        /** @brief Return the distance between 2 Vectors.
        **/
        ////////////////////////////////////////////////////////////
        Real distance(const Vector2& v) const;

        ////////////////////////////////////////////////////////////
        /** @brief Return the squared distance between 2 vectors.
        **/
        ////////////////////////////////////////////////////////////
        Real squaredDistance(const Vector2& v) const;

        ////////////////////////////////////////////////////////////
        /** @brief Return the point at middle between 2 Vectors.
        **/
        ////////////////////////////////////////////////////////////
        Vector2 midPoint(const Vector2& v) const;

    public: // Polar coordinates

        ////////////////////////////////////////////////////////////
        /** @brief Set coordinates from polar ones.
        **/
        ////////////////////////////////////////////////////////////
        void setFromPolarCoordinates(const Radian& theta, const Real& len);

        ////////////////////////////////////////////////////////////
        /** @brief Set coordinates from polar vector.
        **/
        ////////////////////////////////////////////////////////////
        void setFromPolarCoordinates(const Vector2& polar);

        ////////////////////////////////////////////////////////////
        /** @brief Return a vector from polars coordinates.
        **/
        ////////////////////////////////////////////////////////////
        static Vector2 FromPolarCoordinates(const Radian& theta, const Real& len);

        ////////////////////////////////////////////////////////////
        /** @brief Return a vector from polar vector.
        **/
        ////////////////////////////////////////////////////////////
        static Vector2 FromPolarCoordinates(const Vector2& polar);

        ////////////////////////////////////////////////////////////
        /** @brief Get polar coordinates from euclidean ones.
        **/
        ////////////////////////////////////////////////////////////
        Vector2 toPolarCoordinates() const;

        ////////////////////////////////////////////////////////////
        /** @brief Return the angle in polar coordinates.
        **/
        ////////////////////////////////////////////////////////////
        Radian aimedAngle() const;

    public: // Other

        ////////////////////////////////////////////////////////////
        /** @brief Return the dot product with another vector.
        **/
        ////////////////////////////////////////////////////////////
        Real dotProduct(const Vector2& v) const;

        ////////////////////////////////////////////////////////////
        /** @brief Return the cross product with another vector.
        **/
        ////////////////////////////////////////////////////////////
        Vector2 crossProduct(const Vector2& v) const;

        ////////////////////////////////////////////////////////////
        /** @brief Normalize the vector.
         *  @return Old lenght of the vector.
        **/
        ////////////////////////////////////////////////////////////
        Real normalize();

        ////////////////////////////////////////////////////////////
        /** @brief Return a normalized copy of this vector.
        **/
        ////////////////////////////////////////////////////////////
        Vector2 normalized() const;

        ////////////////////////////////////////////////////////////
        /** @brief Return a vector perpendicular to this one,
         *  after a 90 counter clock-wise rotation.
        **/
        ////////////////////////////////////////////////////////////
        Vector2 perpendicular() const;

        ////////////////////////////////////////////////////////////
        /** @brief Return this vector reflected about a plane with
         *  the given normal.
         *
         *  Both this and the reflected vector point away from the
         *  plane with the given normal.
         *
         *  @see refract()
        **/
        ////////////////////////////////////////////////////////////
        Vector2 reflect(const Vector2& normal) const;

        ////////////////////////////////////////////////////////////
        /** @brief Refracts this vector about a plane with the given
         *  normal.
         *
         *  By convention, the this vector points towards the plane,
         *  and the returned vector points away from the plane.
		 *  When the ray is going from a denser material to a lighter
		 *  one, total internal reflection can occur.
		 *  In this case, this function will just return a reflected
		 *  vector from a call to reflect().
		 *
		 *  @param normal : Specifies the plane normal direction.
		 *  @param negativSideRefractionIndex : The refraction index
		 *  of the material we are exiting.
		 *  @param positiveSideRefractionIndex : The refraction index
		 *  of the material we are entering.
		 *
		 *  @see reflect()
        **/
        ////////////////////////////////////////////////////////////
        Vector2 refract(const Vector2& normal, Real negativSideRefractionIndex, Real positiveSideRefractionIndex) const;

    public: // Rotation

        ////////////////////////////////////////////////////////////
        /** @brief Rotates this vector 90 degrees clock-wise.
         *
         *  This rotation is interpreted in a coordinate system on
         *  a plane where +x extends to the right, and +y extends
         *  upwards.
        **/
        ////////////////////////////////////////////////////////////
        Vector2& rotate90CW();

        ////////////////////////////////////////////////////////////
        /** @brief Return a vector perpendicular to this one (rotated
         *  90 degrees clock-wise).
         *
         *  @note Identical to perpendicular().
        **/
        ////////////////////////////////////////////////////////////
        Vector2 rotated90CW() const;

        ////////////////////////////////////////////////////////////
        /** @brief Rotates this vector 90 degrees Counter clock-wise.
         *
         *  This rotation is interpreted in a coordinate system on
         *  a plane where +x extends to the right, and +y extends
         *  upwards.
        **/
        ////////////////////////////////////////////////////////////
        Vector2& rotate90CCW();

        ////////////////////////////////////////////////////////////
        /** @brief Return a vector perpendicular to this one (rotated
         *  90 degrees clock-wise).
        **/
        ////////////////////////////////////////////////////////////
        Vector2 rotated90CCW() const;

        ////////////////////////////////////////////////////////////
        /** @brief Tell if given triangle a,b,c is oriented Counter
         *  clock-wise.
         *
         *  This function returns true, if the point C lies to the left
		 *  of the directed line AB.
        **/
        ////////////////////////////////////////////////////////////
        static bool isOrientedCCW(const Vector2& a, const Vector2& b, const Vector2& c);

    public: // Projection

        ////////////////////////////////////////////////////////////
        /** @brief Project this vector onto the unnormalized direction
         *  vector.
         *
         *  @param direction : The direction vector to project this
         *  vector onto. The vector will be normalized during the
         *  process so you can pass unnormalized ones.
        **/
        ////////////////////////////////////////////////////////////
        Vector2 projectTo(const Vector2& direction) const;

        ////////////////////////////////////////////////////////////
        /** @brief Project this vector onto the normalized direction
         *  vector.
         *
         *  @param direction : The direction vector to project this
         *  vector onto. This vector must be normalized.
        **/
        ////////////////////////////////////////////////////////////
        Vector2 projectToNorm(const Vector2& direction) const;

    public: // Angle

        ////////////////////////////////////////////////////////////
        /** @brief Returns the angle between this vector and given
         *  unnormalized vector, in radians.
         *
         *  @note This function takes into account that given vector
         *  is unnormalized and will normalie it during the process.
         *  If you want to use already normalized ones, use angleBetweenNorm()
         *  instead.
        **/
        ////////////////////////////////////////////////////////////
        Vector2 angleBetween(const Vector2& other) const;

        ////////////////////////////////////////////////////////////
        /** @brief Return the angle between this vector and the given
         *  normalized vector.
         *
         *  @note This vector must be normalized to call this function.
        **/
        ////////////////////////////////////////////////////////////
        Vector2 angleBetweenNorm(const Vector2& other) const;

        ////////////////////////////////////////////////////////////
        /** @brief Breaks this vector down into parallel and
         *  perpendicular components with respect to the given
         *  direction.
         *
         *  @param direction : The direction the decomposition is to
         *  be computed. This vector must be normalized.
         *  @param outParallel [out] : Receives the part of this vector
         *  that is parallel to given direction.
         *  @param outPerpendicular [out] : Receives the part of this
         *  vector that is perpendicular to given direction.
        **/
        ////////////////////////////////////////////////////////////
        void decompose(const Vector2& direction, Vector2& outParalell, Vector2& outPerpendicular) const;

    public: // Interpolation

        ////////////////////////////////////////////////////////////
        /** @brief Linearly interpolates between this and the vector
         *  b.
         *
         *  @param b : The target endpoint.
         *  @param t : The interpolation weight, in range [0, 1].
         *
         *  @return (b, 0) returns this vector, (b, 1) returns b.
        **/
        ////////////////////////////////////////////////////////////
        Vector2 linearInterpolate(const Vector2& b, Real t) const;

        ////////////////////////////////////////////////////////////
        /** @brief Identical to a.linearInterpolate(b, t).
        **/
        ////////////////////////////////////////////////////////////
        static Vector2 LinearInterpolate(const Vector2& a, const Vector2& b, Real t);

    public: // Orthogonality

        ////////////////////////////////////////////////////////////
        /** @brief Makes given vectors linearly independent.
         *
         *  The vector a is kept unmodified, but vector b is modified
         *  to be perpendicular to a.
         *
         *  @note none of the given vectors can be 0.
        **/
        ////////////////////////////////////////////////////////////
        static void Orthogonalize(const Vector2& a, Vector2& b);

        ////////////////////////////////////////////////////////////
        /** @brief Tell if 2 vectors are perpendicular.
        **/
        ////////////////////////////////////////////////////////////
        static bool AreOrthogonal(const Vector2& a, const Vector2& b, Real epsilon = 1e-3f);

        ////////////////////////////////////////////////////////////
        /** @brief Makes given vectors linearly independent and
         *  normalized in lenght.
         *  @see Orthogonalize().
        **/
        ////////////////////////////////////////////////////////////
        static void Orthonormalize(Vector2& a, Vector2& b);

    public: // Convex Hull Computing

        ////////////////////////////////////////////////////////////
        /** @brief Computes the 2D convex hull of the given point
         *  set.
        **/
        ////////////////////////////////////////////////////////////
        static void ConvexHull(const Vector2* pointArray, size_t numPoints, Array<Vector2>& outConvexHull);

        ////////////////////////////////////////////////////////////
        /** @brief Computes the 2D convex hull of the given point
         *  set, in-place.
         *  @return The number of points in the convex hull.
        **/
        ////////////////////////////////////////////////////////////
        static int ConvexHullInPlace(Vector2* pointArray, size_t nPoints);

        ////////////////////////////////////////////////////////////
        /** @brief Computes the minimum-area rectangle that bounds
         *  the given point set.
         *
         *  @param pts : A pointer to an array of point to process.
         *  @param numPoints : The number of elements pointed by pts.
         *  @param center [out] : This variable will receive the center
         *  point of the rectangle.
         *  @param uDir [out] : This variable will receive a normalized
         *  direction vector pointing one of the side directionss of the
         *  rectangle.
		 *  @param vDir [out] : This variable will receive a normalized
		 *  direction vector pointing the other side direction of the
		 *  rectangle.
		 *  @param minU [out] :  Receives the minimum extent of the
		 *  processed point set along the u direction.
		 *  @param maxU [out] :  Receives the maximum extent of the
		 *  processed point set along the u direction.
		 *  @param minV [out] :  Receives the minimum extent of the
		 *  processed point set along the v direction.
		 *  @param maxV [out] :  Receives the maximum extent of the
		 *  processed point set along the v direction.
		 *  @note This algorithm runs in O(n^2) time to the number of
		 *  points in the input.
		 *  @note For best performance, the input point array should contain
         *  only the points in the convex hull of the point set. This algorithm
         *  does not compute the convex hull for you.
		 *  @return The area of the resulting rectangle.
        **/
        ////////////////////////////////////////////////////////////
        static float MinAreaRect(const Vector2* pts, int numPoints,
                                 Vector2& center, Vector2& uDir, Vector2& vDir,
                                 Real& minU, Real& maxU, Real& minV, Real& maxV);

        inline friend Console& operator << (Console& c, const Vector2& v)
        {
            c << "Vector2( " << v.x << ", " << v.y << " )";
            return c;
        }

        bool isZero() const;

        ////////////////////////////////////////////////////////////
        /** @brief Return true if every entries are finite.
        **/
        ////////////////////////////////////////////////////////////
        bool isFinite() const;

        bool isPerpendicular(const Vector2& b, Real epsilon = 1e-3f) const;

        static const Vector2 Zero;
        static const Vector2 UnitX;
        static const Vector2 UnitY;
        static const Vector2 Nan;
        static const Vector2 Inf;
    };
}

#endif
