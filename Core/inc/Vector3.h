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
    template <typename Num>
    class Vector3
    {
    public:

        Num x;///< X Component.
        Num y;///< Y Component.
        Num z;///< Z Component.

    public: // Constructors

        ////////////////////////////////////////////////////////////
        /** @brief Constructor.
         *  @details Set coordinates to (0,0,0).
        **/
        ////////////////////////////////////////////////////////////
        Vector3() : x (0), y (0), z (0)
        {

        }

        ////////////////////////////////////////////////////////////
        /** @brief Copy Constructor.
         *  @details Set coordinates to (v.x, v.y, v.z).
        **/
        ////////////////////////////////////////////////////////////
        Vector3(const Vector3<Num>& v) : x (v.x), y(v.y), z(v.z)
        {

        }

        ////////////////////////////////////////////////////////////
        /** @brief Constructor.
         *  @details Set coordinates to (n1, n2, n3).
        **/
        ////////////////////////////////////////////////////////////
        Vector3(Num n1, Num n2, Num n3) : x(n1), y(n2), z(n3)
        {

        }

        ////////////////////////////////////////////////////////////
        /** @brief Constructor.
         *  @details Set coordinates to (n, n, n).
        **/
        ////////////////////////////////////////////////////////////
        explicit Vector3(Num n) : x(n), y(n), z(n)
        {

        }

        ////////////////////////////////////////////////////////////
        /** @brief Constructor from array.
         *  @details Set coordinates to (n[0], n[1], n[2]).
        **/
        ////////////////////////////////////////////////////////////
        explicit Vector3(const Num v[3]) : x(v[0]), y(v[1]), z(v[2])
        {

        }

        ////////////////////////////////////////////////////////////
        /** @brief Destructor.
        **/
        ////////////////////////////////////////////////////////////
        ~Vector3()
        {

        }

    public: // Swap

        ////////////////////////////////////////////////////////////
        /** @brief Swap current vector with given one.
         *  @param v : Vector to swap.
         *  @note It use xor swapping.
        **/
        ////////////////////////////////////////////////////////////
        void swap(Vector3<Num>& v)
        {
            swapNumeric_xor(x, v.x);
            swapNumeric_xor(y, v.y);
            swapNumeric_xor(z, v.z);
        }

    public: // Egality operators

        ////////////////////////////////////////////////////////////
        /** @brief Tell if 2 vectors are equals.
        **/
        ////////////////////////////////////////////////////////////
        bool equals(const Vector3<Num>& v) const
        {
            return *this == v;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Tell if vector is equal to 2 given numerics.
        **/
        ////////////////////////////////////////////////////////////
        bool equals(const Num& n1, const Num& n2) const
        {
            return n1 == x && n2 == y;
        }

        inline bool operator == (const Vector3<Num>& v) const
        {
            return x == v.x && y == v.y && z == v.z;
        }

        inline bool operator != (const Vector3<Num>& v) const
        {
            return !(*this == v);
        }

    public: // Superior / inferior strict operators

        bool operator < ( const Vector3<Num>& rhs ) const
        {
            if( x < rhs.x && y < rhs.y && z < rhs.z )
                return true;
            return false;
        }

        bool operator > ( const Vector3<Num>& rhs ) const
        {
            if( x > rhs.x && y > rhs.y && z > rhs.z )
                return true;
            return false;
        }

    public: // Superior / inferior operators

        bool operator <= ( const Vector3<Num>& rhs ) const
        {
            if( x <= rhs.x && y <= rhs.y && z <= rhs.z )
                return true;
            return false;
        }

        bool operator >= ( const Vector3<Num>& rhs ) const
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
        Vector3<Num>& set(const Vector3<Num>& other)
        {
            x = other.x;
            y = other.y;
            z = other.z;
            return *this;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Set coordinates to given pair.
        **/
        ////////////////////////////////////////////////////////////
        Vector3<Num>& set(const Num& n1, const Num& n2, const Num& n3)
        {
            x = n1;
            y = n2;
            z = n3;
            return *this;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Set coordinates to given numeric.
        **/
        ////////////////////////////////////////////////////////////
        Vector3<Num>& set(const Num& n)
        {
            x = n;
            y = x;
            z = x;
            return *this;
        }

        Vector3<Num>& operator = (const Vector3<Num>& other)
        {
            x = other.x;
            y = other.y;
            z = other.z;

            return *this;
        }

        Vector3<Num>& operator = (const Num& other)
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
        void floor(const Vector3<Num>& other)
        {
            if(other.x < x) x = other.x;
            if(other.y < y) y = other.y;
            if(other.z < z) z = other.z;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Ceil current vector with given one.
         *
         *  It takes the maximum value for each coordinate and
         *  attriutes it to this vector.
        **/
        ////////////////////////////////////////////////////////////
        void ceil(const Vector3<Num>& other)
        {
            if(other.x > x) x = other.x;
            if(other.y > y) y = other.y;
            if(other.z > z) z = other.z;
        }

    public: // Addition

        ////////////////////////////////////////////////////////////
        /** @brief Add a vector to this one.
         *  @param v : Vector to add.
        **/
        ////////////////////////////////////////////////////////////
        Vector3<Num>& add(const Vector3<Num>& v)
        {
            x += v.x;
            y += v.y;
            z += v.z;
            return *this;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Add a numeric to this one.
         *  @param n : Numeric to add.
         *  @return (x + n, y + n, z + n)
        **/
        ////////////////////////////////////////////////////////////
        Vector3<Num>& add(const Num& n)
        {
            x += n;
            y += n;
            z += n;
            return *this;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Return the vector when adding given one.
         *  @param v : Vector to add.
        **/
        ////////////////////////////////////////////////////////////
        Vector3<Num> added(const Vector3<Num>& v) const
        {
            return Vector3<Num>(x + v.x,
                                y + v.y,
                                z + v.z);
        }

        ////////////////////////////////////////////////////////////
        /** @brief Return the vector when adding given numeric.
         *  @param n : Numeric to add.
         *  @return (x + n, y + n, z + n)
        **/
        ////////////////////////////////////////////////////////////
        Vector3<Num> added(const Num& n) const
        {
            return Vector3<Num>(x + n,
                                y + n,
                                z + n);
        }

        Vector3<Num>& operator += (const Vector3<Num>& n)
        {
            return add(n);
        }

        Vector3<Num>& operator += (const Num n)
        {
            return add(n);
        }

        Vector3<Num> operator + (const Vector3<Num>& v) const
        {
            return added(v);
        }

        Vector3<Num> operator + (const Num lhs) const
        {
            return added(lhs);
        }

    public: // Substraction

        ////////////////////////////////////////////////////////////
        /** @brief Substract a vector to this one.
         *  @param v : Vector to substract.
        **/
        ////////////////////////////////////////////////////////////
        Vector3<Num>& sub(const Vector3<Num>& v)
        {
            x -= v.x;
            y -= v.y;
            z -= v.z;

            return *this;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Substract a numeric to this vector.
         *  @param n : Numeric to substract.
         *  @return (x - n, y - n, z - n)
        **/
        ////////////////////////////////////////////////////////////
        Vector3<Num>& sub(const Num& n)
        {
            x -= n;
            y -= n;
            z -= n;

            return *this;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Return the vector when substracting given one.
         *  @param v : Vector to substract.
        **/
        ////////////////////////////////////////////////////////////
        Vector3<Num> subbed(const Vector3<Num>& v) const
        {
            return Vector3<Num>(x - v.x, y - v.y, z - v.z);
        }

        ////////////////////////////////////////////////////////////
        /** @brief Return the vector when substracting given numeric.
         *  @param n : Numeric to substract.
         *  @return (x - n, y + n, z - n)
        **/
        ////////////////////////////////////////////////////////////
        Vector3<Num> subbed(const Num& n) const
        {
            return Vector3<Num>(x - n,
                                y - n,
                                z - n);
        }

        Vector3<Num>& operator -= (const Vector3<Num>& v)
        {
            return sub(v);
        }

        Vector3<Num>& operator -= (const Num& n)
        {
            return sub(n);
        }

        Vector3<Num> operator - (const Vector3<Num>& v) const
        {
            return subbed(v);
        }

        Vector3<Num> operator - (const Num& v) const
        {
            return subbed(v);
        }

    public: // Multiplication

        ////////////////////////////////////////////////////////////
        /** @brief Multiply a vector to this one.
         *  @param v : Vector to Multiply.
        **/
        ////////////////////////////////////////////////////////////
        Vector3<Num>& multiply(const Vector3<Num>& v)
        {
            x *= v.x;
            y *= v.y;
            z *= v.z;

            return *this;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Multiply a numeric to this one.
         *  @param n : Numeric to Multiply.
         *  @return (x * n, y * n, z * n)
        **/
        ////////////////////////////////////////////////////////////
        Vector3<Num>& multiply(const Num& n)
        {
            x *= n;
            y *= n;
            z *= n;

            return *this;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Return the vector if a multiplication was applied
         *  to this one.
         *  @param v : Vector to Multiply.
        **/
        ////////////////////////////////////////////////////////////
        Vector3<Num> multiplied(const Vector3<Num>& v) const
        {
            return Vector3<Num>(x *= v.x,
                                y *= v.y,
                                z *= v.z);
        }

        ////////////////////////////////////////////////////////////
        /** @brief Return the vector if a multiplication was applied
         *  to this one.
         *  @param n : Numeric to multiply.
        **/
        ////////////////////////////////////////////////////////////
        Vector3<Num> multiplied(const Num& n) const
        {
            return Vector3<Num>(x *= n,
                                y *= n,
                                z *= n);
        }

        Vector3<Num>& operator *= (const Vector3<Num>& v)
        {
            return multiply(v);
        }

        Vector3<Num>& operator *= (const Num& n)
        {
            return multiply(n);
        }

        Vector3<Num> operator * (const Vector3<Num>& v) const
        {
            return multiplied(v);
        }

        Vector3<Num> operator * (const Num& n) const
        {
            return multiplied(n);
        }

    public: // Division

        ////////////////////////////////////////////////////////////
        /** @brief Divide a vector to this one.
         *  @param v : Vector to divide.
        **/
        ////////////////////////////////////////////////////////////
        Vector3<Num>& divide(const Vector3<Num>& v)
        {
            x /= v.x;
            y /= v.y;
            z /= v.z;

            return *this;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Divide a numeric to this one.
         *  @param n : Numeric to divide.
         *  @return (x / n, y / n, z / n)
        **/
        ////////////////////////////////////////////////////////////
        Vector3<Num>& divide(const Num& n)
        {
            x /= n;
            y /= n;
            z /= n;

            return *this;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Return the vector if a division was applied
         *  to this one.
         *  @param v : Vector to divide.
        **/
        ////////////////////////////////////////////////////////////
        Vector3<Num> divided(const Vector3<Num>& v) const
        {
            return Vector3<Num>(x / v.x,
                                y / v.y,
                                z / v.z);
        }

        ////////////////////////////////////////////////////////////
        /** @brief Return the vector if a division was applied
         *  to this one.
         *  @param n : Numeric to divide.
        **/
        ////////////////////////////////////////////////////////////
        Vector3<Num> divided(const Num& n) const
        {
            return Vector3<Num>(x / n,
                                y / n,
                                z / n);
        }

        Vector3<Num>& operator /= (const Vector3<Num>& v)
        {
            return divide(v);
        }

        Vector3<Num>& operator /= (const Num& n)
        {
            return divide(n);
        }

        Vector3<Num> operator / (const Vector3<Num>& v) const
        {
            return divided(v);
        }

        Vector3<Num> operator / (const Num& n) const
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
        const Num& at(size_t i) const
        {
            return i == 0 ? x : i == 1 ? y : z;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Return x, y or z.
         *
         *  If value is 0, x is returned. If 1, y is returned, but
         *  if i is superior strict to 1, z is always returned.
        **/
        ////////////////////////////////////////////////////////////
        Num& at(size_t i)
        {
            return i == 0 ? x : i == 1 ? y : z;
        }

        const Num& operator [] (size_t i) const
        {
            return at(i);
        }

        Num& operator [] (size_t i)
        {
            return at(i);
        }

        ////////////////////////////////////////////////////////////
        /** @brief Return a pointer to data.
        **/
        ////////////////////////////////////////////////////////////
        const Num* ptr() const
        {
            return &x;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Return a pointer to data.
        **/
        ////////////////////////////////////////////////////////////
        Num* ptr()
        {
            return &x;
        }

    public: // Absolute, Negation

        inline Vector3<Numeric> operator + () const
        {
            return *this;
        }

        inline Vector3<Numeric> operator - () const
        {
            return Vector3<Numeric>(-x, -y, -z);
        }

        ////////////////////////////////////////////////////////////
        /** @brief Negate coordinates and return the vector.
        **/
        ////////////////////////////////////////////////////////////
        Vector3<Numeric>& negate()
        {
            x = -x;
            y = -y;
            z = -z;
            return -this;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Return a vector from negated one.
        **/
        ////////////////////////////////////////////////////////////
        Vector3<Numeric> negated() const
        {
            return Vector3<Numeric>(-x, -y, -z);
        }

        ////////////////////////////////////////////////////////////
        /** @brief Return a vector from abs coordinates.
        **/
        ////////////////////////////////////////////////////////////
        Vector3<Numeric> absoluted() const
        {
            return Vector3<Numeric>(abs_(x), abs_(y), abs_(z));
        }

        ////////////////////////////////////////////////////////////
        /** @brief Absolute coordinates of this vector and return it.
        **/
        ////////////////////////////////////////////////////////////
        Vector3<Numeric>& absolute()
        {
            x = abs_(x);
            y = abs_(y);
            z = abs_(z);
            return *this;
        }

    public: // Lenght

        ////////////////////////////////////////////////////////////
        /** @brief Return computed lenght of this vector.
        **/
        ////////////////////////////////////////////////////////////
        Num lenght() const
        {
            return Sqrt(squaredLenght());
        }

        ////////////////////////////////////////////////////////////
        /** @brief Return squared computed lenght of this vector.
        **/
        ////////////////////////////////////////////////////////////
        Num squaredLenght() const
        {
            return x * x + y * y + z * z;
        }

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
        Num distance(const Vector3<Num>& v) const
        {
            return Sqrt(squaredDistance(v));
        }

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
        Num squaredDistance(const Vector3<Num>& v) const
        {
            float dx = x - v.x;
            float dy = y - v.y;
            float dz = z - v.z;

            return dx*dx + dy*dy + dz*dz;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Returns the oint in the exact middle of the segment
         *  described by this point and a given one.
         *
         *  The point returned is computed by the average of the 2
         *  points. If the second point is the same as this one,
         *  this point is returned.
        **/
        ////////////////////////////////////////////////////////////
        Vector3<Num> midPoint(const Vector3<Num>& other) const
        {
            return Vector3<Num>(
                ( x + other.x ) * 0.5f,
                ( y + other.y ) * 0.5f,
                ( z + other.z ) * 0.5f );
        }

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
        void setFromSphericalCoordinates(float azimuth, float inclinaison, float radius = 1.0f)
        {
            float cx = Cos(inclinaison);
            x = cx * Sin(azimuth) * radius;
            y = -Sin(inclinaison) * radius;
            z = cx * Cos(azimuth) * radius;
        }

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
        void setFromSphericalCoordinates(const Vector3<Num>& spherical)
        {
            setFromSphericalCoordinates(spherical.x, spherical.y, spherical.z);
        }

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
        static Vector3<Num> FromSphericalCoordinates(float azimuth, float inclinaison, float radius = 1.0f)
        {
            Vector3<Num> ret;
            ret.setFromSphericalCoordinates(azimuth, inclinaison, radius);
            return ret;
        }

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
        static Vector3<Num> FromSphericalCoordinates(const Vector3<Num>& spherical)
        {
            Vector3<Num> ret;
            ret.setFromSphericalCoordinates(spherical);
            return ret;
        }

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
        Vector3<Num> toSphericalCoordinates() const
        {
            Vector3<Num> v = *this;

            Num l = v.normalize();
            if((float) l <= 1e-5f)
                return ::Zero();
            Num azimuth = ATan2(v.x, v.z);
            Num inclinaison = ASin(-v.y);
            return Vector3<Num>(azimuth, inclinaison, l);
        }

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
        Vector3<Num> toSphericalCoordinatesNormalized() const
        {
            Num azimuth = ATan2(x, z);
            Num inclinaison = ASin(-y);
            return Vector3<Num>(azimuth, inclinaison, 1.0f);
        }

    public: // Lenght operations

        ////////////////////////////////////////////////////////////
        /** @brief Normalize this vector.
         *
         *  If an error occured, 0 is returned and vector is set to
         *  (1,0,0).
         *  @return The old lenght of the vector.
        **/
        ////////////////////////////////////////////////////////////
        Num normalize()
        {
            float len = (float) lenght();
            if(len > 1e-6f)
            {
                *this *= 1.f / len;
                return len;
            }
            else
            {
                aprodebug("Vector lenght is too short ! Normalization failed.");
                set(1,0,0);
                return 0;
            }
        }

        ////////////////////////////////////////////////////////////
        /** @brief Returns a normalized copy of this vector.
         *
         *  If Vector cannot be normalized, vector (1,0,0) is returned
         *  and error message is printed.
        **/
        ////////////////////////////////////////////////////////////
        Vector3<Num>& normalized() const
        {
            Vector3<Num> copy = *this;
            float oldLen = copy.normalize();
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
        Num scale(const Num& new_lenght)
        {
            Num len = squaredLenght();
            if((float) len < 1e-6f)
            {
                aprodebug("Vector lenght is too short ! Scale failed.");
                set(new_lenght, 0,0);
                return 0;
            }
            else
            {
                len = Sqrt(len);
                Num scalar = new_lenght / len;
                *this *= scalar;
                return len;
            }
        }

        ////////////////////////////////////////////////////////////
        /** @brief Return a scaled copy of this vector.
         *
         *  If an error occured, a message is printed and a vector
         *  with given lenght is producted.
        **/
        ////////////////////////////////////////////////////////////
        Vector3<Num> scaled(const Num& new_lenght) const
        {
            Vector3<Num> copy = *this;
            copy.scale(new_lenght);
            return copy;
        }

    public: // Boolean operations

        ////////////////////////////////////////////////////////////
        /** @brief Tests if the length of this vector is one, up to
         *  the given epsilon.
        **/
        ////////////////////////////////////////////////////////////
        bool isNormalized(float epsilon = 1e-6f) const
        {
            return abs_(squaredLenght() - 1) <= epsilon;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Tests if the length of this vector is zero, up to
         *  the given epsilon.
        **/
        ////////////////////////////////////////////////////////////
        bool isZero(float epsilon = 1e-6f) const
        {
            return abs_(squaredLenght) <= epsilon;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Tests if this vector is perpendicular to given
         *  one.
        **/
        ////////////////////////////////////////////////////////////
        bool isPerpendicular(const Vector3<Num>& other, float epsilon = 1e-3f) const
        {
            return abs_(dot(other)) <= epsilon * length() * other.length();
        }

        ////////////////////////////////////////////////////////////
        /** @brief Tells if the points p1, p2 and p3 lie on a straight
         *  line, up to the given epsilon.
        **/
        ////////////////////////////////////////////////////////////
        static bool AreCollinear(const Vector3<Num>& p1, const Vector3<Num>& p2, const Vector3<Num>& p3, float espilon = 1e-4f)
        {
            return (p2-p1).cross(p3-p1).squaredLenght() <= epsilon;
        }

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
        Num dot(const Vector3<Num>& other) const
        {
            return x * other.x + y * other.y + z * other.z;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Computes an absoluted dot product between this
         *  vector and given one.
        **/
        ////////////////////////////////////////////////////////////
        Num dotabs(const Vector3<Num>& other) const
        {
            return *this.absoluted().dot(other.absoluted());
        }

        ////////////////////////////////////////////////////////////
        /** @brief Coputes the cross product between this vector and
         *  given one.
         *
         *  Unless this vector and the given vector are linearly dependent,
         *  the cross product returns a vector that is perpendicular to
         *  both vectors.
        **/
        ////////////////////////////////////////////////////////////
        Vector3<Num> cross(const Vector3<Num>& other) const
        {
            return Vector3<Num>(
                y * other.z - z * other.y,
                z * other.x - x * other.z,
                x * other.y - y * other.x);
        }

    public: // Perpendicular

        ////////////////////////////////////////////////////////////
        /** @brief Computes a new normalized direction vector that is
         *  perpendicular to this vector and the specified hint vector.
         *
         *  If this vector points toward the hint vector, the vector
         *  null is returned instead.
        **/
        ////////////////////////////////////////////////////////////
        Vector3<Num> perpendicular(const Vector3<Num>& hint) const
        {
            Vector3<Num> v = this->cross(hint);
            Num len = v.normalize();
            if(len == 0)
                return Vector3<Num>(0,0,0);
            else
                return v;
        }

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
        Vector3<Num> anotherPerpendicular(const Vector3<Num>& hint) const
        {
            Vector3<Num> first = this->perpendicular(hint);
            Vector3<Num> v = this->cross(first);
            return v.normalized();
        }

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
        Vector3<Num> reflect(const Vector3<Num>& normal) const
        {
            return 2 * *this->projectToNorm(normal) - *this;
        }

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
        Vector3<Num> refract(const Vector3<Num>& normal, float negativSideRefractionIndex, float positiveSideRefractionIndex) const
        {
            // Duplicate from Vector2::refract
            float n = negativSideRefractionIndex / positiveSideRefractionIndex;
            float cosI = this->dotProduct(normal);
            float sinT2 = n*n*(1.f - cosI * cosI);
            if(sinT2 > 1.f)
                return (-(*this)).reflect(normal);
            return n * *this - (n + Sqrt(1.f - sinT2)) * normal;
        }

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
        Vector3<Num> projectTo(const Vector3<Num>& direction) const
        {
            return direction * this->dot(direction) / direction.squaredLenght();
        }

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
        Vector3<Num> projectToNorm(const Vector3<Num>& direction) const
        {
            return direction * this->dot(direction);
        }

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
        Num angleBetween(const Vector3<Num>& other) const
        {
            float cosa = (float) (dot(other) / Sqrt(squaredLenght() * other.squaredLenght()));
            if (cosa >= 1.f)
                return (Num) 0.f;
            else if (cosa <= -1.f)
                return (Num) Math::PI_32;
            else
                return (Num) ACos(cosa);
        }

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
        Num angleBetweenNorm(const Vector3<Num>& normalizedVector) const
        {
            float cosa = (float) dot(other);
            if (cosa >= 1.f)
                return (Num) 0.f;
            else if (cosa <= -1.f)
                return (Num) Math::PI_32;
            else
                return (Num) ACos(cosa);
        }

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
        void decompose(const Vector3<Num>& direction, Vector3<Num>& outParallel, Vector3<Num>& outPerpendicular) const
        {
            outParallel = this>projectToNorm(direction);
            outPerpendicular = *this - outParallel;
        }

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
        Vector3<Num> linearInterpolate(const Vector3<Num>& b, float t) const
        {
            Clamp(t, 0.0f, 1.0f);
            return (1.f - t) * *this + t * b;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Identical to a.linearInterpolate(b, t).
        **/
        ////////////////////////////////////////////////////////////
        static Vector3<Num> LinearInterpolate(const Vector3<Num>& a, const Vector3<Num>& b, float t)
        {
            return a.linearInterpolate(b, t);
        }

    public: // Ortho

        ////////////////////////////////////////////////////////////
        /** @brief Makes the given vectors linearly independent.
         *
         *  This function directly follows the Gram-Schmidt procedure
         *  on the input vectors. The vector a is kept unmodified, and
         *  vector b is modified to be perpendicular to a.
        **/
        ////////////////////////////////////////////////////////////
        static void Orthogonalize(const Vector3<Num>& a, Vector3<Num>& b)
        {
            if (!a.isZero())
                b -= b.projectTo(a);
        }

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
        static void Orthogonalize(const Vector3<Num>& a, Vector3<Num>& b, Vector3<Num>& c)
        {
            if (!a.isZero())
            {
                b -= b.projectTo(a);
                c -= c.projectTo(a);
            }

            if (!b.IsZero())
                c -= c.projectTo(b);
        }

        ////////////////////////////////////////////////////////////
        /** @brief Returns true if the given vectors are orthogonal
         *  to each other.
        **/
        ////////////////////////////////////////////////////////////
        static bool AreOrthogonal(const Vector3<Num>& a, const Vector3<Num>& b, float epsilon = 1e-3f)
        {
            return a.isPerpendicular(b, epsilon);
        }

        ////////////////////////////////////////////////////////////
        /** @brief Returns true if the given vectors are orthogonal
         *  to each other.
        **/
        ////////////////////////////////////////////////////////////
        static bool AreOrthogonal(const Vector3<Num>& a, const Vector3<Num>& b, const Vector3<Num>& c, float epsilon = 1e-3f)
        {
            return a.isPerpendicular(b, epsilon) &&
                   a.isPerpendicular(c, epsilon) &&
                   b.isPerpendicular(c, epsilon);
        }

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
        static bool Orthonormalize(Vector3<Num>& a, Vector3<Num>& b)
        {
            if(a.isZero() || b.isZero())
                return false;

            a.normalize();
            b -= b.projectTo(a);
            b.normalize();
            return true;
        }

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
        static bool Orthonormalize(Vector3<Num>& a, Vector3<Num>& b, Vector3<Num>& c)
        {
            if(a.isZero() || b.isZero() || c.isZero())
                return false;

            a.normalize();
            b -= b.projectTo(a);
            b.normalize();
            c -= c.projectTo(a);
            c -= c.projectTo(b);
            c.normalize();
            return true;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Returns true if the given vectors are orthogonal
         *  to each other and normalized.
        **/
        ////////////////////////////////////////////////////////////
        static bool AreOrthonormal(const Vector3<Num>& a, const Vector3<Num>& b, float epsilon = 1e-3f)
        {
            return a.isPerpendicular(b, epsilon) && a.isNormalized(epsilon*epsilon) && b.isNormalized(epsilon*epsilon);
        }

        ////////////////////////////////////////////////////////////
        /** @brief Returns true if the given vectors are orthogonal
         *  to each other and normalized.
        **/
        ////////////////////////////////////////////////////////////
        static bool AreOrthonormal(const Vector3<Num>& a, const Vector3<Num>& b, const Vector3<Num>& c, float epsilon = 1e-3f)
        {
            return a.isPerpendicular(b, epsilon) &&
                   a.isPerpendicular(c, epsilon) &&
                   b.isPerpendicular(c, epsilon) &&
                   a.isNormalized(epsilon*epsilon) &&
                   b.isNormalized(epsilon*epsilon) &&
                   c.isNormalized(epsilon*epsilon);
        }

        inline friend Console& operator << (Console& c, const Vector3<Num>& v)
        {
            c << "Vector3<" << className<Num>() << ">( " << v.x << ", " << v.y << ", " << v.z << " )";
            return c;
        }
    };

    typedef Vector3<float> Vector3F;
    typedef Vector3<double> Vector3D;
    typedef Vector3<unit_t> Vector3U;
}

#endif
