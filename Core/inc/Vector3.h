////////////////////////////////////////////////////////////
/** @file Vector3.h
 *  @ingroup Maths
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 5/10/2012
 *
 *  Defines the Vector3 class.
 *
**/
////////////////////////////////////////////////////////////
#ifndef APROVECTOR3_H
#define APROVECTOR3_H

#include "Maths.h"
#include "Vector2.h"

namespace APro
{
    ////////////////////////////////////////////////////////////
    /** @class Vector3
     *  @ingroup Maths
     *  @brief A vector of form (x, y, z).
    **/
    ////////////////////////////////////////////////////////////
    class Vector3
    {
    public:

        Real x;///< X Component.
        Real y;///< Y Component.
        Real z;///< Z Component.

    public: // Constructors

        ////////////////////////////////////////////////////////////
        /** @brief Constructor.
         *  @details Set coordinates to (0,0,0).
        **/
        ////////////////////////////////////////////////////////////
        Vector3();

        ////////////////////////////////////////////////////////////
        /** @brief Copy Constructor.
         *  @details Set coordinates to (v.x, v.y, v.z).
        **/
        ////////////////////////////////////////////////////////////
        Vector3(const Vector3& v);

        ////////////////////////////////////////////////////////////
        /** @brief Constructor.
         *  @details Set coordinates to (n1, n2, n3).
        **/
        ////////////////////////////////////////////////////////////
        Vector3(Real n1, Real n2, Real n3);

        ////////////////////////////////////////////////////////////
        /** @brief Constructor.
         *  @details Set coordinates to (n, n, n).
        **/
        ////////////////////////////////////////////////////////////
        explicit Vector3(Real n);

        ////////////////////////////////////////////////////////////
        /** @brief Constructor from array.
         *  @details Set coordinates to (n[0], n[1], n[2]).
        **/
        ////////////////////////////////////////////////////////////
        explicit Vector3(const Real v[3]);

        ////////////////////////////////////////////////////////////
        /** @brief Destructor.
        **/
        ////////////////////////////////////////////////////////////
        ~Vector3() {}

    public: // Swap

        ////////////////////////////////////////////////////////////
        /** @brief Swap current vector with given one.
         *  @param v : Vector to swap.
         *  @note It use xor swapping.
        **/
        ////////////////////////////////////////////////////////////
        void swap(Vector3& v);

    public: // Egality operators

        ////////////////////////////////////////////////////////////
        /** @brief Tell if 2 vectors are equals.
        **/
        ////////////////////////////////////////////////////////////
        bool equals(const Vector3& v) const;

        ////////////////////////////////////////////////////////////
        /** @brief Tell if vector is equal to 3 given numerics, given to
         *  epsilon.
        **/
        ////////////////////////////////////////////////////////////
        bool equals(const Real& n1, const Real& n2, const Real& n3, Real epsilon = 1e-3f) const;

        inline bool operator == (const Vector3& v) const
        {
            return equals(v.x, v.y, v.z);
        }

        inline bool operator != (const Vector3& v) const
        {
            return !(*this == v);
        }

    public: // Superior / inferior strict operators

        bool operator < ( const Vector3& rhs ) const
        {
            if( x < rhs.x && y < rhs.y && z < rhs.z )
                return true;
            return false;
        }

        bool operator > ( const Vector3& rhs ) const
        {
            if( x > rhs.x && y > rhs.y && z > rhs.z )
                return true;
            return false;
        }

    public: // Superior / inferior operators

        bool operator <= ( const Vector3& rhs ) const
        {
            if( x <= rhs.x && y <= rhs.y && z <= rhs.z )
                return true;
            return false;
        }

        bool operator >= ( const Vector3& rhs ) const
        {
            if( x >= rhs.x && y >= rhs.y && z >= rhs.z )
                return true;
            return false;
        }

    public: // Assignment operators

        ////////////////////////////////////////////////////////////
        /** @brief Set coordinates to given vector.
        **/
        ////////////////////////////////////////////////////////////
        Vector3& set(const Vector3& other);

        ////////////////////////////////////////////////////////////
        /** @brief Set coordinates to given pair.
        **/
        ////////////////////////////////////////////////////////////
        Vector3& set(const Real& n1, const Real& n2, const Real& n3);

        ////////////////////////////////////////////////////////////
        /** @brief Set coordinates to given numeric.
        **/
        ////////////////////////////////////////////////////////////
        Vector3& set(const Real& n);

        Vector3& operator = (const Vector3& other)
        {
            x = other.x;
            y = other.y;
            z = other.z;

            return *this;
        }

        Vector3& operator = (const Real& other)
        {
            x = other;
            y = other;
            z = other;

            return *this;
        }

    public: // Floor / Ceil

        ////////////////////////////////////////////////////////////
        /** @brief Floor the current vector with given one.
         *
         *  It takes the minimum value for each coordinate and
         *  attriutes it to this vector.
        **/
        ////////////////////////////////////////////////////////////
        void floor(const Vector3& other);

        ////////////////////////////////////////////////////////////
        /** @brief Ceil current vector with given one.
         *
         *  It takes the maximum value for each coordinate and
         *  attriutes it to this vector.
        **/
        ////////////////////////////////////////////////////////////
        void ceil(const Vector3& other);

    public: // Addition

        ////////////////////////////////////////////////////////////
        /** @brief Add a vector to this one.
         *  @param v : Vector to add.
        **/
        ////////////////////////////////////////////////////////////
        Vector3& add(const Vector3& v);

        ////////////////////////////////////////////////////////////
        /** @brief Add a numeric to this one.
         *  @param n : Numeric to add.
         *  @return (x + n, y + n, z + n)
        **/
        ////////////////////////////////////////////////////////////
        Vector3& add(const Real& n);

        ////////////////////////////////////////////////////////////
        /** @brief Return the vector when adding given one.
         *  @param v : Vector to add.
        **/
        ////////////////////////////////////////////////////////////
        Vector3 added(const Vector3& v) const;

        ////////////////////////////////////////////////////////////
        /** @brief Return the vector when adding given numeric.
         *  @param n : Numeric to add.
         *  @return (x + n, y + n, z + n)
        **/
        ////////////////////////////////////////////////////////////
        Vector3 added(const Real& n) const;

        Vector3& operator += (const Vector3& n)
        {
            return add(n);
        }

        Vector3& operator += (const Real& n)
        {
            return add(n);
        }

        Vector3 operator + (const Vector3& v) const
        {
            return added(v);
        }

        Vector3 operator + (const Real& lhs) const
        {
            return added(lhs);
        }

    public: // Substraction

        ////////////////////////////////////////////////////////////
        /** @brief Substract a vector to this one.
         *  @param v : Vector to substract.
        **/
        ////////////////////////////////////////////////////////////
        Vector3& sub(const Vector3& v);

        ////////////////////////////////////////////////////////////
        /** @brief Substract a numeric to this vector.
         *  @param n : Numeric to substract.
         *  @return (x - n, y - n, z - n)
        **/
        ////////////////////////////////////////////////////////////
        Vector3& sub(const Real& n);

        ////////////////////////////////////////////////////////////
        /** @brief Return the vector when substracting given one.
         *  @param v : Vector to substract.
        **/
        ////////////////////////////////////////////////////////////
        Vector3 subbed(const Vector3& v) const;

        ////////////////////////////////////////////////////////////
        /** @brief Return the vector when substracting given numeric.
         *  @param n : Numeric to substract.
         *  @return (x - n, y + n, z - n)
        **/
        ////////////////////////////////////////////////////////////
        Vector3 subbed(const Real& n) const;

        Vector3& operator -= (const Vector3& v)
        {
            return sub(v);
        }

        Vector3& operator -= (const Real& n)
        {
            return sub(n);
        }

        Vector3 operator - (const Vector3& v) const
        {
            return subbed(v);
        }

        Vector3 operator - (const Real& v) const
        {
            return subbed(v);
        }

    public: // Multiplication

        ////////////////////////////////////////////////////////////
        /** @brief Multiply a vector to this one.
         *  @param v : Vector to Multiply.
        **/
        ////////////////////////////////////////////////////////////
        Vector3& multiply(const Vector3& v);

        ////////////////////////////////////////////////////////////
        /** @brief Multiply a numeric to this one.
         *  @param n : Numeric to Multiply.
         *  @return (x * n, y * n, z * n)
        **/
        ////////////////////////////////////////////////////////////
        Vector3& multiply(const Real& n);

        ////////////////////////////////////////////////////////////
        /** @brief Return the vector if a multiplication was applied
         *  to this one.
         *  @param v : Vector to Multiply.
        **/
        ////////////////////////////////////////////////////////////
        Vector3 multiplied(const Vector3& v) const;

        ////////////////////////////////////////////////////////////
        /** @brief Return the vector if a multiplication was applied
         *  to this one.
         *  @param n : Numeric to multiply.
        **/
        ////////////////////////////////////////////////////////////
        Vector3 multiplied(const Real& n) const;

        Vector3& operator *= (const Vector3& v)
        {
            return multiply(v);
        }

        Vector3& operator *= (const Real& n)
        {
            return multiply(n);
        }

        Vector3 operator * (const Vector3& v) const
        {
            return multiplied(v);
        }

        Vector3 operator * (const Real& n) const
        {
            return multiplied(n);
        }

    public: // Division

        ////////////////////////////////////////////////////////////
        /** @brief Divide a vector to this one.
         *  @param v : Vector to divide.
        **/
        ////////////////////////////////////////////////////////////
        Vector3& divide(const Vector3& v);

        ////////////////////////////////////////////////////////////
        /** @brief Divide a numeric to this one.
         *  @param n : Numeric to divide.
         *  @return (x / n, y / n, z / n)
        **/
        ////////////////////////////////////////////////////////////
        Vector3& divide(const Real& n);

        ////////////////////////////////////////////////////////////
        /** @brief Return the vector if a division was applied
         *  to this one.
         *  @param v : Vector to divide.
        **/
        ////////////////////////////////////////////////////////////
        Vector3 divided(const Vector3& v) const;

        ////////////////////////////////////////////////////////////
        /** @brief Return the vector if a division was applied
         *  to this one.
         *  @param n : Numeric to divide.
        **/
        ////////////////////////////////////////////////////////////
        Vector3 divided(const Real& n) const;

        Vector3& operator /= (const Vector3& v)
        {
            return divide(v);
        }

        Vector3& operator /= (const Real& n)
        {
            return divide(n);
        }

        Vector3 operator / (const Vector3& v) const
        {
            return divided(v);
        }

        Vector3 operator / (const Real& n) const
        {
            return divided(n);
        }

    public: // Access

        ////////////////////////////////////////////////////////////
        /** @brief Return x, y or z.
         *
         *  If value is 0, x is returned. If 1, y is returned, but
         *  if i is superior strict to 1, z is always returned.
        **/
        ////////////////////////////////////////////////////////////
        const Real& at(size_t i) const;

        ////////////////////////////////////////////////////////////
        /** @brief Return x, y or z.
         *
         *  If value is 0, x is returned. If 1, y is returned, but
         *  if i is superior strict to 1, z is always returned.
        **/
        ////////////////////////////////////////////////////////////
        Real& at(size_t i);

        const Real& operator [] (size_t i) const
        {
            return at(i);
        }

        Real& operator [] (size_t i)
        {
            return at(i);
        }

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

        inline Vector3 operator + () const
        {
            return *this;
        }

        inline Vector3 operator - () const
        {
            return Vector3(-x, -y, -z);
        }

        ////////////////////////////////////////////////////////////
        /** @brief Negate coordinates and return the vector.
        **/
        ////////////////////////////////////////////////////////////
        Vector3& negate();

        ////////////////////////////////////////////////////////////
        /** @brief Return a vector from negated one.
        **/
        ////////////////////////////////////////////////////////////
        Vector3 negated() const;

        ////////////////////////////////////////////////////////////
        /** @brief Return a vector from abs coordinates.
        **/
        ////////////////////////////////////////////////////////////
        Vector3 absoluted() const;

        ////////////////////////////////////////////////////////////
        /** @brief Absolute coordinates of this vector and return it.
        **/
        ////////////////////////////////////////////////////////////
        Vector3& absolute();

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
        /** @brief Computes the distance between this point and the
         *  given object.
         *
         *  This function finds the nearest point to this point on
         *  the given object, and computes its distance to this point.
         *
         *  If this point lies inside the given object, a distance of 0
         *  is returned.
         *
         *  @see squaredDistance()
        **/
        ////////////////////////////////////////////////////////////
        Real distance(const Vector3& v) const;

        ////////////////////////////////////////////////////////////
        /** @brief Computes the squared distance between this and the
         *  given point.
         *
         *  Calling this function is faster than calling Distance(), since
         *  this function avoids computing a square root.
		 *  If you only need to compare distances to each other, but are
		 *  not interested in the actual distance values, you can compare
		 *  by using DistanceSq(), instead of Distance(), since Sqrt()
		 *  is an order-preserving (monotonous and non-decreasing)
		 *  function.
		 *
		 *  @see distance()
        **/
        ////////////////////////////////////////////////////////////
        Real squaredDistance(const Vector3& v) const;

        ////////////////////////////////////////////////////////////
        /** @brief Returns the oint in the exact middle of the segment
         *  described by this point and a given one.
         *
         *  The point returned is computed by the average of the 2
         *  points. If the second point is the same as this one,
         *  this point is returned.
        **/
        ////////////////////////////////////////////////////////////
        Vector3 midPoint(const Vector3& other) const;

    public: // Spherical Coordinates

        ////////////////////////////////////////////////////////////
        /** @brief Converts the given vector represented in spherical
         *  coordinates to an euclidean vector3 (x,y,z) triplet.
         *
         *  @param azimuth : The direction, or yaw, of the vector. This
         *  function uses the convention that the X-Z plane is the 2D
         *  horizontal "map" plane, with the vector (0,0,radius)
         *  corresponding to the vector in the direction azimuth=0 and
         *  inclination=0. This value is typically in the range [-pi, pi]
         *  (, or [0, 2pi]).
         *  @param inclination : The elevation, or pitch, of the vector.
         *  This function uses the convention that the +Y axis points
         *  towards up, i.e. +Y is the "Zenith direction". This value is
         *  typically in the range [-pi/2, pi/2].
         *  @param radius The magnitude of the vector. This is usually >=
         *  0, although passing in the zero vector as radius returns
         *  (0,0,0), and passing in a negative radius mirrors the
         *  coordinate along the origin.
         *
         *  @see FromSphericalCoordinates(), setFromSphericalCoordinates(),
         *  toSphericalCoordinates(), toSphericalCoordinatesNormalized()
        **/
        ////////////////////////////////////////////////////////////
        void setFromSphericalCoordinates(Radian azimuth, Radian inclinaison, Real radius = 1.0f);

        ////////////////////////////////////////////////////////////
        /** @brief Converts the given vector represented in spherical
         *  coordinates to an euclidean vector3 (x,y,z) triplet.
         *
         *  @param spherical : The vector with the 3 parameters in.
         *
         *  @see FromSphericalCoordinates(), setFromSphericalCoordinates(),
         *  toSphericalCoordinates(), toSphericalCoordinatesNormalized()
        **/
        ////////////////////////////////////////////////////////////
        void setFromSphericalCoordinates(const Vector3& spherical);

        ////////////////////////////////////////////////////////////
        /** @brief Computes given spherical coordinates to an euclidean
         *  vector.
         *
         *  @param azimuth : The direction, or yaw, of the vector. This
         *  function uses the convention that the X-Z plane is the 2D
         *  horizontal "map" plane, with the vector (0,0,radius)
         *  corresponding to the vector in the direction azimuth=0 and
         *  inclination=0. This value is typically in the range [-pi, pi]
         *  (, or [0, 2pi]).
         *  @param inclination : The elevation, or pitch, of the vector.
         *  This function uses the convention that the +Y axis points
         *  towards up, i.e. +Y is the "Zenith direction". This value is
         *  typically in the range [-pi/2, pi/2].
         *  @param radius The magnitude of the vector. This is usually >=
         *  0, although passing in the zero vector as radius returns
         *  (0,0,0), and passing in a negative radius mirrors the
         *  coordinate along the origin.
         *
         *  @see FromSphericalCoordinates(), setFromSphericalCoordinates(),
         *  toSphericalCoordinates(), toSphericalCoordinatesNormalized()
        **/
        ////////////////////////////////////////////////////////////
        static Vector3 FromSphericalCoordinates(Radian azimuth, Radian inclinaison, Real radius = 1.0f);

        ////////////////////////////////////////////////////////////
        /** @brief Computes given spherical coordinates to an euclidean
         *  vector.
         *
         *  @param spherical : The vector with the 3 parameters in.
         *
         *  @see FromSphericalCoordinates(), setFromSphericalCoordinates(),
         *  toSphericalCoordinates(), toSphericalCoordinatesNormalized()
        **/
        ////////////////////////////////////////////////////////////
        static Vector3 FromSphericalCoordinates(const Vector3& spherical);

        ////////////////////////////////////////////////////////////
        /** @brief Converts this euclidean (x,y,z) vector3 to spherical
         *  coordinates representation in the form (azimuth, inclination,
         *  radius).
         *
         *  @note It is valid for the magnitude of this vector to be
         *  (very close to) zero, in which case the return value is the
         *  zero vector.
        **/
        ////////////////////////////////////////////////////////////
        Vector3 toSphericalCoordinates() const;

        ////////////////////////////////////////////////////////////
        /** @brief Converts this normalized euclidean (x,y,z) vector3 to
         *  spherical coordinates representation in the form (azimuth,
         *  inclination, 1.0f).
         *
         *  @note This function requires that this vector3 is normalized.
         *  This function is identical to ToSphericalCoordinates, but is
         *  slightly faster in the case this vector is known to be
         *  normalized in advance.
        **/
        ////////////////////////////////////////////////////////////
        Vector3 toSphericalCoordinatesNormalized() const;

    public: // Lenght operations

        ////////////////////////////////////////////////////////////
        /** @brief Normalize this vector.
         *
         *  If an error occured, 0 is returned and vector is set to
         *  (1,0,0).
         *  @return The old lenght of the vector.
        **/
        ////////////////////////////////////////////////////////////
        Real normalize();

        ////////////////////////////////////////////////////////////
        /** @brief Returns a normalized copy of this vector.
         *
         *  If Vector cannot be normalized, vector (1,0,0) is returned
         *  and error message is printed.
        **/
        ////////////////////////////////////////////////////////////
        Vector3& normalized() const
        {
            Vector3 copy = *this;
            Real oldLen = copy.normalize();
            aproassert(oldLen > 0, "Cannot normalize vector !");
            return copy;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Make this vector have given new lenght.
         *
         *  The direction of this vector isn't changed during the
         *  process, so normalize() function will give the same
         *  result.
         *
         *  If an error occured, a message is printed and a vector
         *  with given lenght is producted, but 0 is returned.
        **/
        ////////////////////////////////////////////////////////////
        Real scale(const Real& new_lenght);

        ////////////////////////////////////////////////////////////
        /** @brief Return a scaled copy of this vector.
         *
         *  If an error occured, a message is printed and a vector
         *  with given lenght is producted.
        **/
        ////////////////////////////////////////////////////////////
        Vector3 scaled(const Real& new_lenght) const;

    public: // Boolean operations

        ////////////////////////////////////////////////////////////
        /** @brief Tests if the length of this vector is one, up to
         *  the given epsilon.
        **/
        ////////////////////////////////////////////////////////////
        bool isNormalized(Real epsilon = 1e-6f) const;

        ////////////////////////////////////////////////////////////
        /** @brief Tests if the length of this vector is zero, up to
         *  the given epsilon.
        **/
        ////////////////////////////////////////////////////////////
        bool isZero(Real epsilon = 1e-6f) const;

        ////////////////////////////////////////////////////////////
        /** @brief Tests if this vector is perpendicular to given
         *  one.
        **/
        ////////////////////////////////////////////////////////////
        bool isPerpendicular(const Vector3& other, Real epsilon = 1e-3f) const;

        ////////////////////////////////////////////////////////////
        /** @brief Tells if the points p1, p2 and p3 lie on a straight
         *  line, up to the given epsilon.
        **/
        ////////////////////////////////////////////////////////////
        static bool AreCollinear(const Vector3& p1, const Vector3& p2, const Vector3& p3, Real espilon = 1e-4f);

    public: // others

        ////////////////////////////////////////////////////////////
        /** @brief Computes the dot product between this vector and
         *  given one.
         *
         *  The dot product has a geometric interpretation of measuring
         *  how close two direction vectors are to pointing in the same
         *  direction, computing angles between vectors, or the length
         *  of a projection of one vector to another.
        **/
        ////////////////////////////////////////////////////////////
        Real dot(const Vector3& other) const;

        ////////////////////////////////////////////////////////////
        /** @brief Computes an absoluted dot product between this
         *  vector and given one.
        **/
        ////////////////////////////////////////////////////////////
        Real dotabs(const Vector3& other) const;

        ////////////////////////////////////////////////////////////
        /** @brief Coputes the cross product between this vector and
         *  given one.
         *
         *  Unless this vector and the given vector are linearly dependent,
         *  the cross product returns a vector that is perpendicular to
         *  both vectors.
        **/
        ////////////////////////////////////////////////////////////
        Vector3 cross(const Vector3& other) const;

    public: // Perpendicular

        ////////////////////////////////////////////////////////////
        /** @brief Computes a new normalized direction vector that is
         *  perpendicular to this vector and the specified hint vector.
         *
         *  If this vector points toward the hint vector, the vector
         *  null is returned instead.
        **/
        ////////////////////////////////////////////////////////////
        Vector3 perpendicular(const Vector3& hint) const;

        ////////////////////////////////////////////////////////////
        /** @brief Computes another normalized direction vector that is
         *  perpendicular to this vector and the specified hint vector.
         *
         *  If this vector points toward the hint vector, the vector
         *  null is returned instead.
         *
         *  @note The set (this, perpendicular(), anotherPerpendicular())
         *  forms a right-handed normalized 3D basis.
        **/
        ////////////////////////////////////////////////////////////
        Vector3 anotherPerpendicular(const Vector3& hint) const;

    public: // Reflect / Refract

        ////////////////////////////////////////////////////////////
        /** @brief Returns this vector reflected about a plane with
         *  the given normal.
         *
         *  By convention, both this and the reflected vector point
         *  away from the plane with the given normal.
         *
         *  @see refract()
        **/
        ////////////////////////////////////////////////////////////
        Vector3 reflect(const Vector3& normal) const;

        ////////////////////////////////////////////////////////////
        /** @brief Refracts this vector about a plane with the given
         *  normal.
         *
         *  By convention, the this vector points towards the plane,
         *  and the returned vector points away from the plane.
         *  When the ray is going from a denser material to a lighter
         *  one, total internal reflection can occur. In this case,
         *  this function will just return a reflected vector from a
         *  call to Reflect().
         *
         *  @param normal : Specifies the plane normal direction.
         *  @param negativSideRefractionIndex : The refraction index of
         *  the material we are exiting.
         *  @param positiveSideRefractionIndex : The refraction index of
         *  the material we are entering.
         *
         *  @see reflect()
        **/
        ////////////////////////////////////////////////////////////
        Vector3 refract(const Vector3& normal, Real negativSideRefractionIndex, Real positiveSideRefractionIndex) const;

    public: // Projection

        ////////////////////////////////////////////////////////////
        /** @brief Projects this vector onto the given unnormalized
         *  direction vector.
         *
         *  @param direction The direction vector to project this vector
         *  onto. This function will normalize this vector, so you can
         *  pass in an unnormalized vector.
         *
         *  @see projectToNorm().
        **/
        ////////////////////////////////////////////////////////////
        Vector3 projectTo(const Vector3& direction) const;

        ////////////////////////////////////////////////////////////
        /** @brief Projects this vector onto the given normalized
         *  direction vector.
         *
         *  @param direction The direction vector to project this vector
         *  onto. This vector must be normalized.
         *
         *  @see projectTo()
        **/
        ////////////////////////////////////////////////////////////
        Vector3 projectToNorm(const Vector3& direction) const;

        ////////////////////////////////////////////////////////////
        /** @brief Computes the angle between this vector and the
         *  specified vector, in radians.
         *
         *  This function takes into account that this vector or the
         *  other vector can be unnormalized, and normalizes the computations.
         *  If you are computing the angle between two normalized vectors,
         *  it is better to use angleBetweenNorm().
         *
         *  @see angleBetweenNorm()
        **/
        ////////////////////////////////////////////////////////////
        Radian angleBetween(const Vector3& other) const;

        ////////////////////////////////////////////////////////////
        /** @brief Returns the angle between this vector and the
         *  specified normalized vector, in radians.
         *
         *  This vector must be normalized to call this function.
         *
         *  @param normalizedVector : The direction vector to compute
         *  the angle against. This vector must be normalized.
         *
         *  @see angleBetween()
        **/
        ////////////////////////////////////////////////////////////
        Radian angleBetweenNorm(const Vector3& normalizedVector) const;

        ////////////////////////////////////////////////////////////
        /** @brief Breaks this vector down into parallel and perpendicular
         *  components with respect to the given direction.
         *
         *  @param direction : The direction the decomposition is to
         *  be computed. This vector must be normalized.
		 *  @param outParallel [out] : Receives the part of this vector
		 *  that is parallel to the given direction vector.
		 *  @param outPerpendicular [out] : Receives the part of this
		 *  vector that is perpendicular to the given direction vector.
        **/
        ////////////////////////////////////////////////////////////
        void decompose(const Vector3& direction, Vector3& outParallel, Vector3& outPerpendicular) const;

    public: // Linear interpolation

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
        Vector3 linearInterpolate(const Vector3& b, Real t) const;

        ////////////////////////////////////////////////////////////
        /** @brief Identical to a.linearInterpolate(b, t).
        **/
        ////////////////////////////////////////////////////////////
        static Vector3 LinearInterpolate(const Vector3& a, const Vector3& b, Real t);

    public: // Ortho

        ////////////////////////////////////////////////////////////
        /** @brief Makes the given vectors linearly independent.
         *
         *  This function directly follows the Gram-Schmidt procedure
         *  on the input vectors. The vector a is kept unmodified, and
         *  vector b is modified to be perpendicular to a.
        **/
        ////////////////////////////////////////////////////////////
        static void Orthogonalize(const Vector3& a, Vector3& b);

        ////////////////////////////////////////////////////////////
        /** @brief Makes the given vectors linearly independent.
         *
         *  This function directly follows the Gram-Schmidt procedure
         *  on the input vectors. The vector a is kept unmodified, and
         *  vector b is modified to be perpendicular to a.
         *
         *  The vector c is adjusted to be perpendicular to a and b.
        **/
        ////////////////////////////////////////////////////////////
        static void Orthogonalize(const Vector3& a, Vector3& b, Vector3& c);

        ////////////////////////////////////////////////////////////
        /** @brief Returns true if the given vectors are orthogonal
         *  to each other.
        **/
        ////////////////////////////////////////////////////////////
        static bool AreOrthogonal(const Vector3& a, const Vector3& b, Real epsilon = 1e-3f);

        ////////////////////////////////////////////////////////////
        /** @brief Returns true if the given vectors are orthogonal
         *  to each other.
        **/
        ////////////////////////////////////////////////////////////
        static bool AreOrthogonal(const Vector3& a, const Vector3& b, const Vector3& c, Real epsilon = 1e-3f);

        ////////////////////////////////////////////////////////////
        /** @brief Makes the given vectors linearly independent and
         *  normalized in length.
         *
         *  This function directly follows the Gram-Schmidt procedure
         *  on the input vectors. The vector a is first normalized,
         *  and vector b is modified to be perpendicular to a, and also
         *  normalized.
         *
         *  @return False if one of the given vectors is zero, true
         *  if they can be orthonormalized.
        **/
        ////////////////////////////////////////////////////////////
        static bool Orthonormalize(Vector3& a, Vector3& b);

        ////////////////////////////////////////////////////////////
        /** @brief Makes the given vectors linearly independent and
         *  normalized in length.
         *
         *  This function directly follows the Gram-Schmidt procedure
         *  on the input vectors. The vector a is first normalized,
         *  and vector b is modified to be perpendicular to a, and also
         *  normalized.
         *
         *  The vector c is adjusted to be perpendicular to a and b,
         *  and normalized.
         *
         *  @return False if one of the given vectors is zero, true
         *  if they can be orthonormalized.
        **/
        ////////////////////////////////////////////////////////////
        static bool Orthonormalize(Vector3& a, Vector3& b, Vector3& c);

        ////////////////////////////////////////////////////////////
        /** @brief Returns true if the given vectors are orthogonal
         *  to each other and normalized.
        **/
        ////////////////////////////////////////////////////////////
        static bool AreOrthonormal(const Vector3& a, const Vector3& b, Real epsilon = 1e-3f);

        ////////////////////////////////////////////////////////////
        /** @brief Returns true if the given vectors are orthogonal
         *  to each other and normalized.
        **/
        ////////////////////////////////////////////////////////////
        static bool AreOrthonormal(const Vector3& a, const Vector3& b, const Vector3& c, Real epsilon = 1e-3f);

    public: // Other

        ////////////////////////////////////////////////////////////
        /** @brief Return true if every entries are finite.
        **/
        ////////////////////////////////////////////////////////////
        bool isFinite() const;

        ////////////////////////////////////////////////////////////
        /** @brief Return the Vector2 part of this Vector3.
        **/
        ////////////////////////////////////////////////////////////
        Vector2& toVec2();

        ////////////////////////////////////////////////////////////
        /** @brief Return the Vector2 part of this Vector3.
        **/
        ////////////////////////////////////////////////////////////
        const Vector2& toVec2() const;

        inline friend Console& operator << (Console& c, const Vector3& v)
        {
            c << "Vector3( " << v.x << ", " << v.y << ", " << v.z << " )";
            return c;
        }

        static const Vector3 Zero;
        static const Vector3 UnitX;
        static const Vector3 UnitY;
        static const Vector3 UnitZ;
        static const Vector3 Nan;
        static const Vector3 Inf;
    };
}

#endif
