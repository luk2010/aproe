////////////////////////////////////////////////////////////
/** @file Vector4.h
 *  @ingroup Maths
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 29/09/2013
 *
 *  Defines the Vector4 class.
 *
**/
////////////////////////////////////////////////////////////
#ifndef APRO_VECTOR4_H
#define APRO_VECTOR4_H

#include "Platform.h"

namespace APro
{
    ////////////////////////////////////////////////////////////
    /** @class Vector4
     *  @ingroup Maths
     *  @brief A vector of form (x, y, z, w).
    **/
    ////////////////////////////////////////////////////////////
    class APRO_DLL Vector4
    {
    public:

        Real x;///< X Component.
        Real y;///< Y Component.
        Real z;///< Z Component.
        Real w;///< W Component.

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Constructor.
         *  @details Set coordinates to (0,0,0,0).
        **/
        ////////////////////////////////////////////////////////////
        Vector4();

        ////////////////////////////////////////////////////////////
        /** @brief Copy Constructor.
         *  @details Set coordinates to (v.x, v.y, v.z, v.w).
        **/
        ////////////////////////////////////////////////////////////
        Vector4(const Vector4& v);

        ////////////////////////////////////////////////////////////
        /** @brief Constructor.
         *  @details Set coordinates to (n1, n2, n3, n4).
        **/
        ////////////////////////////////////////////////////////////
        Vector4(Real n1, Real n2, Real n3, Real n4);

        ////////////////////////////////////////////////////////////
        /** @brief Constructs a Vector4 from a Vector3 and the last
         *  component.
        **/
        ////////////////////////////////////////////////////////////
        Vector4(const Vector3& xyz, Real w_);

        ////////////////////////////////////////////////////////////
        /** @brief Constructs a Vector4 from a Vector2 and the 2 last
         *  components.
        **/
        ////////////////////////////////////////////////////////////
        Vector4(const Vector2& xy, Real z_, Real w_);

        ////////////////////////////////////////////////////////////
        /** @brief Constructor.
         *  @details Set coordinates to (n, n, n, n).
        **/
        ////////////////////////////////////////////////////////////
        explicit Vector4(Real n);

        ////////////////////////////////////////////////////////////
        /** @brief Constructor from array.
         *  @details Set coordinates to (n[0], n[1], n[2], n[3]).
        **/
        ////////////////////////////////////////////////////////////
        explicit Vector4(const Real v[4]);

        ////////////////////////////////////////////////////////////
        /** @brief Destructor.
        **/
        ////////////////////////////////////////////////////////////
        ~Vector4() {}

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Swap current vector with given one.
         *  @param v : Vector to swap.
         *  @note It use xor swapping.
        **/
        ////////////////////////////////////////////////////////////
        void swap(Vector4& v);

    public: // Egality operators

        ////////////////////////////////////////////////////////////
        /** @brief Tell if 2 vectors are equals.
        **/
        ////////////////////////////////////////////////////////////
        bool equals(const Vector4& v) const;

        ////////////////////////////////////////////////////////////
        /** @brief Tell if 2 vectors are equals, compared to epsilon.
        **/
        ////////////////////////////////////////////////////////////
        bool equalsAbs(const Vector4& v, Real epsilon = 1e-3f) const;

        ////////////////////////////////////////////////////////////
        /** @brief Tell if vector is equal to 4 given numerics.
        **/
        ////////////////////////////////////////////////////////////
        bool equals(const Real& n1, const Real& n2, const Real& n3, const Real& n4) const;

        ////////////////////////////////////////////////////////////
        /** @brief Tell if vector is equal to 3 given numerics, given to
         *  epsilon.
        **/
        ////////////////////////////////////////////////////////////
        bool equalsAbs(const Real& n1, const Real& n2, const Real& n3, const Real& n4, Real epsilon = 1e-3f) const;

        inline bool operator == (const Vector3& v) const
        {
            return equals(v);
        }

        inline bool operator != (const Vector3& v) const
        {
            return !(*this == v);
        }

    public:

        bool operator < ( const Vector4& rhs ) const
        {
            if( x < rhs.x && y < rhs.y && z < rhs.z && w < rhs.w )
                return true;
            return false;
        }

        bool operator > ( const Vector4& rhs ) const
        {
            if( x > rhs.x && y > rhs.y && z > rhs.z && w > rhs.w )
                return true;
            return false;
        }

    public: // Superior / inferior operators

        bool operator <= ( const Vector3& rhs ) const
        {
            if( x <= rhs.x && y <= rhs.y && z <= rhs.z && w <= rhs.w )
                return true;
            return false;
        }

        bool operator >= ( const Vector3& rhs ) const
        {
            if( x >= rhs.x && y >= rhs.y && z >= rhs.z && w >= rhs.w )
                return true;
            return false;
        }

    public: // Assignment operators

        ////////////////////////////////////////////////////////////
        /** @brief Set coordinates to given vector.
        **/
        ////////////////////////////////////////////////////////////
        Vector4& set(const Vector4& other);

        ////////////////////////////////////////////////////////////
        /** @brief Set coordinates to given numerics.
        **/
        ////////////////////////////////////////////////////////////
        Vector4& set(const Real& n1, const Real& n2, const Real& n3, const Real& n4);

        ////////////////////////////////////////////////////////////
        /** @brief Set coordinates to given numeric.
        **/
        ////////////////////////////////////////////////////////////
        Vector4& set(const Real& n);

        ////////////////////////////////////////////////////////////
        /** @brief Set coordinates to given numeric.
        **/
        ////////////////////////////////////////////////////////////
        Vector4& set(const Real& xyz, const Real& mw);

        ////////////////////////////////////////////////////////////
        /** @brief Set coordinates to given numeric and vector.
        **/
        ////////////////////////////////////////////////////////////
        Vector4& set(const Vector3& xyz, const Real& mw);

        Vector4& operator = (const Vector4& other)
        {
            return set(other);
        }

        Vector4& operator = (const Real& other)
        {
            return set(other);
        }

    public: // Floor / Ceil

        ////////////////////////////////////////////////////////////
        /** @brief Floor the current vector with given one.
         *
         *  It takes the minimum value for each coordinate and
         *  attriutes it to this vector.
        **/
        ////////////////////////////////////////////////////////////
        void floor(const Vector4& other);

        ////////////////////////////////////////////////////////////
        /** @brief Floor the current vector with given one.
         *
         *  It takes the minimum value for each coordinate and
         *  attriutes it to this vector, except for the w component
         *  wich stay inchanged.
        **/
        ////////////////////////////////////////////////////////////
        void floor3(const Vector3& other);

        ////////////////////////////////////////////////////////////
        /** @brief Ceil current vector with given one.
         *
         *  It takes the maximum value for each coordinate and
         *  attriutes it to this vector.
        **/
        ////////////////////////////////////////////////////////////
        void ceil(const Vector4& other);

        ////////////////////////////////////////////////////////////
        /** @brief Ceil current vector with given one.
         *
         *  It takes the maximum value for each coordinate and
         *  attriutes it to this vector, except for the w component
         *  wich stay inchanged.
        **/
        ////////////////////////////////////////////////////////////
        void ceil3(const Vector3& other);

    public: // Addition

        ////////////////////////////////////////////////////////////
        /** @brief Add a vector to this one.
         *  @param v : Vector to add.
        **/
        ////////////////////////////////////////////////////////////
        Vector4& add(const Vector4& v);

        ////////////////////////////////////////////////////////////
        /** @brief Add a vector3 to this one.
         *  @param v : Vector to add.
        **/
        ////////////////////////////////////////////////////////////
        Vector4& add(const Vector3& v);

        ////////////////////////////////////////////////////////////
        /** @brief Add a numeric to this one.
         *  @param n : Numeric to add.
         *  @return (x + n, y + n, z + n)
        **/
        ////////////////////////////////////////////////////////////
        Vector4& add(const Real& n);

        ////////////////////////////////////////////////////////////
        /** @brief Return the vector when adding given one.
         *  @param v : Vector to add.
        **/
        ////////////////////////////////////////////////////////////
        Vector4 added(const Vector4& v) const;

        ////////////////////////////////////////////////////////////
        /** @brief Return the vector when adding given one.
         *  @param v : Vector to add.
        **/
        ////////////////////////////////////////////////////////////
        Vector4 added(const Vector3& v) const;

        ////////////////////////////////////////////////////////////
        /** @brief Return the vector when adding given numeric.
         *  @param n : Numeric to add.
         *  @return (x + n, y + n, z + n)
        **/
        ////////////////////////////////////////////////////////////
        Vector4 added(const Real& n) const;

        Vector4& operator += (const Vector4& n)
        {
            return add(n);
        }

        Vector4& operator += (const Vector3& n)
        {
            return add(n);
        }

        Vector4& operator += (const Real& n)
        {
            return add(n);
        }

        Vector4 operator + (const Vector4& v) const
        {
            return added(v);
        }

        Vector4 operator + (const Vector3& v) const
        {
            return added(v);
        }

        Vector4 operator + (const Real& lhs) const
        {
            return added(lhs);
        }

    public: // Substraction

        ////////////////////////////////////////////////////////////
        /** @brief Substract a vector to this one.
         *  @param v : Vector to substract.
        **/
        ////////////////////////////////////////////////////////////
        Vector4& sub(const Vector4& v);

        ////////////////////////////////////////////////////////////
        /** @brief Substract a vector to this one.
         *  @param v : Vector to substract.
        **/
        ////////////////////////////////////////////////////////////
        Vector4& sub(const Vector3& v);

        ////////////////////////////////////////////////////////////
        /** @brief Substract a numeric to this vector.
         *  @param n : Numeric to substract.
         *  @return (x - n, y - n, z - n, w - n)
        **/
        ////////////////////////////////////////////////////////////
        Vector4& sub(const Real& n);

        ////////////////////////////////////////////////////////////
        /** @brief Return the vector when substracting given one.
         *  @param v : Vector to substract.
        **/
        ////////////////////////////////////////////////////////////
        Vector4 subbed(const Vector4& v) const;

        ////////////////////////////////////////////////////////////
        /** @brief Return the vector when substracting given one.
         *  @param v : Vector to substract.
        **/
        ////////////////////////////////////////////////////////////
        Vector4 subbed(const Vector3& v) const;

        ////////////////////////////////////////////////////////////
        /** @brief Return the vector when substracting given numeric.
         *  @param n : Numeric to substract.
         *  @return (x - n, y + n, z - n, w - n)
        **/
        ////////////////////////////////////////////////////////////
        Vector4 subbed(const Real& n) const;

        Vector4& operator -= (const Vector4& v)
        {
            return sub(v);
        }

        Vector4& operator -= (const Vector3& v)
        {
            return sub(v);
        }

        Vector4& operator -= (const Real& n)
        {
            return sub(n);
        }

        Vector4 operator - (const Vector4& v) const
        {
            return subbed(v);
        }

        Vector4 operator - (const Vector3& v) const
        {
            return subbed(v);
        }

        Vector4 operator - (const Real& v) const
        {
            return subbed(v);
        }

    public: // Multiplication

        ////////////////////////////////////////////////////////////
        /** @brief Multiply a vector to this one.
         *  @param v : Vector to Multiply.
        **/
        ////////////////////////////////////////////////////////////
        Vector4& multiply(const Vector4& v);

        ////////////////////////////////////////////////////////////
        /** @brief Multiply a vector to this one.
         *  @param v : Vector to Multiply.
        **/
        ////////////////////////////////////////////////////////////
        Vector4& multiply(const Vector3& v);

        ////////////////////////////////////////////////////////////
        /** @brief Multiply a numeric to this one.
         *  @param n : Numeric to Multiply.
         *  @return (x * n, y * n, z * n, w * n)
        **/
        ////////////////////////////////////////////////////////////
        Vector4& multiply(const Real& n);

        ////////////////////////////////////////////////////////////
        /** @brief Return the vector if a multiplication was applied
         *  to this one.
         *  @param v : Vector to Multiply.
        **/
        ////////////////////////////////////////////////////////////
        Vector4 multiplied(const Vector4& v) const;

        ////////////////////////////////////////////////////////////
        /** @brief Return the vector if a multiplication was applied
         *  to this one.
         *  @param v : Vector to Multiply.
        **/
        ////////////////////////////////////////////////////////////
        Vector4 multiplied(const Vector3& v) const;

        ////////////////////////////////////////////////////////////
        /** @brief Return the vector if a multiplication was applied
         *  to this one.
         *  @param n : Numeric to multiply.
        **/
        ////////////////////////////////////////////////////////////
        Vector4 multiplied(const Real& n) const;

        Vector4& operator *= (const Vector4& v)
        {
            return multiply(v);
        }

        Vector4& operator *= (const Vector3& v)
        {
            return multiply(v);
        }

        Vector4& operator *= (const Real& n)
        {
            return multiply(n);
        }

        Vector4 operator * (const Vector4& v) const
        {
            return multiplied(v);
        }

        Vector4 operator * (const Vector3& v) const
        {
            return multiplied(v);
        }

        Vector4 operator * (const Real& n) const
        {
            return multiplied(n);
        }

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Divide a vector to this one.
         *  @param v : Vector to divide.
        **/
        ////////////////////////////////////////////////////////////
        Vector4& divide(const Vector4& v);

        ////////////////////////////////////////////////////////////
        /** @brief Divide a vector to this one.
         *  @param v : Vector to divide.
        **/
        ////////////////////////////////////////////////////////////
        Vector4& divide(const Vector3& v);

        ////////////////////////////////////////////////////////////
        /** @brief Divide a numeric to this one.
         *  @param n : Numeric to divide.
         *  @return (x / n, y / n, z / n, w / n)
        **/
        ////////////////////////////////////////////////////////////
        Vector4& divide(const Real& n);

        ////////////////////////////////////////////////////////////
        /** @brief Return the vector if a division was applied
         *  to this one.
         *  @param v : Vector to divide.
        **/
        ////////////////////////////////////////////////////////////
        Vector4 divided(const Vector4& v) const;

        ////////////////////////////////////////////////////////////
        /** @brief Return the vector if a division was applied
         *  to this one.
         *  @param v : Vector to divide.
        **/
        ////////////////////////////////////////////////////////////
        Vector4 divided(const Vector3& v) const;

        ////////////////////////////////////////////////////////////
        /** @brief Return the vector if a division was applied
         *  to this one.
         *  @param n : Numeric to divide.
        **/
        ////////////////////////////////////////////////////////////
        Vector4 divided(const Real& n) const;

        Vector4& operator /= (const Vector4& v)
        {
            return divide(v);
        }

        Vector4& operator /= (const Vector3& v)
        {
            return divide(v);
        }

        Vector4& operator /= (const Real& n)
        {
            return divide(n);
        }

        Vector4 operator / (const Vector4& v) const
        {
            return divided(v);
        }

        Vector4 operator / (const Vector3& v) const
        {
            return divided(v);
        }

        Vector4 operator / (const Real& n) const
        {
            return divided(n);
        }

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Return x, y, z or w.
         *
         *  If value is 0, x is returned. If 1, y is returned, but
         *  if i is superior strict to 2, w is always returned.
        **/
        ////////////////////////////////////////////////////////////
        const Real& at(size_t i) const;

        ////////////////////////////////////////////////////////////
        /** @brief Return x, y, z or w.
         *
         *  If value is 0, x is returned. If 1, y is returned, but
         *  if i is superior strict to 2, w is always returned.
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
        const Real* ptr() const { return &x; }

        ////////////////////////////////////////////////////////////
        /** @brief Return a pointer to data.
        **/
        ////////////////////////////////////////////////////////////
        Real* ptr() { return &x; }

        ////////////////////////////////////////////////////////////
        /** @brief Return the Vector3 part of this vector.
        **/
        ////////////////////////////////////////////////////////////
        Vector3& toVector3() { return *reinterpret_cast<Vector3*>(this); }

        ////////////////////////////////////////////////////////////
        /** @brief Return the Vector3 part of this vector.
        **/
        ////////////////////////////////////////////////////////////
        const Vector3& toVector3() const { return *reinterpret_cast<Vector3*>(this); }

    public:

        inline Vector4 operator + () const
        {
            return *this;
        }

        inline Vector4 operator - () const
        {
            return negated();
        }

        ////////////////////////////////////////////////////////////
        /** @brief Negate coordinates and return the vector.
        **/
        ////////////////////////////////////////////////////////////
        Vector4& negate();

        ////////////////////////////////////////////////////////////
        /** @brief Negate coordinates except w and return the vector.
        **/
        ////////////////////////////////////////////////////////////
        Vector4& negate3();

        ////////////////////////////////////////////////////////////
        /** @brief Return a vector from negated one.
        **/
        ////////////////////////////////////////////////////////////
        Vector4 negated() const;

        ////////////////////////////////////////////////////////////
        /** @brief Return a vector from negated one.
        **/
        ////////////////////////////////////////////////////////////
        Vector4 negated3() const;

        ////////////////////////////////////////////////////////////
        /** @brief Return a vector from absolute coordinates.
        **/
        ////////////////////////////////////////////////////////////
        Vector4 absoluted() const;

        ////////////////////////////////////////////////////////////
        /** @brief Absolute coordinates of this vector and return it.
        **/
        ////////////////////////////////////////////////////////////
        Vector4& absolute();

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Return computed lenght of this vector.
        **/
        ////////////////////////////////////////////////////////////
        Real lenght() const;

        ////////////////////////////////////////////////////////////
        /** @brief Return computed lenght of this vector (xyz components.)
        **/
        ////////////////////////////////////////////////////////////
        Real lenght3() const;

        ////////////////////////////////////////////////////////////
        /** @brief Return squared computed lenght of this vector.
        **/
        ////////////////////////////////////////////////////////////
        Real squaredLenght() const;

        ////////////////////////////////////////////////////////////
        /** @brief Return squared computed lenght of this vector.(xyz components.)
        **/
        ////////////////////////////////////////////////////////////
        Real squaredLenght3() const;

    public:

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
        Real distance(const Vector4& v) const;

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
        Real squaredDistance(const Vector4& v) const;


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
        Real distance3(const Vector3& v) const;

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
        Real squaredDistance3(const Vector3& v) const;

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Normalize this vector.
         *
         *  If an error occured, 0 is returned and vector is set to
         *  (1,0,0,0).
         *  @return The old lenght of the vector.
        **/
        ////////////////////////////////////////////////////////////
        Real normalize();

        ////////////////////////////////////////////////////////////
        /** @brief Normalize this vector.
         *
         *  If an error occured, 0 is returned and vector is set to
         *  (1,0,0,0).
         *  @return The old lenght of the vector.
        **/
        ////////////////////////////////////////////////////////////
        Real normalize3();

        ////////////////////////////////////////////////////////////
        /** @brief Returns a normalized copy of this vector.
         *
         *  If Vector cannot be normalized, vector (1,0,0,0) is returned
         *  and error message is printed.
        **/
        ////////////////////////////////////////////////////////////
        Vector4& normalized() const;

        ////////////////////////////////////////////////////////////
        /** @brief Returns a normalized copy of this vector.
         *
         *  If Vector cannot be normalized, vector (1,0,0,0) is returned
         *  and error message is printed.
        **/
        ////////////////////////////////////////////////////////////
        Vector4& normalized3() const;

        ////////////////////////////////////////////////////////////
        /** @brief Divides each element by w to produce a Vector4 of
         *  form (x, y, z, 1).
         *
         *  This function performs the <b>perspective divide</b> or the
         *  <b>homogeneous divide</b> on this vector, which is the process
         *  of dividing each element of this vector by w. If the w component
         *  of this vector is zero before division, the result of this vector
         *  will be undefined.
        **/
        ////////////////////////////////////////////////////////////
        Vector4& normalizeW();

        ////////////////////////////////////////////////////////////
        /** @brief Scale the (x, y, z) part of this vector.
        **/
        ////////////////////////////////////////////////////////////
        void scale(const Real& scalar);

        ////////////////////////////////////////////////////////////
        /** @brief Scale the (x, y, z) part of this vector so the new
         *  lenght is as given.
         *
         *  This is effectively the same as normalizing the vector first
         *  and then multiplying by new_length.
        **/
        ////////////////////////////////////////////////////////////
        Real scaleToLenght(const Real& new_lenght);

        ////////////////////////////////////////////////////////////
        /** @brief Return a scaled copy of this vector.
        **/
        ////////////////////////////////////////////////////////////
        Vector4 scaled(const Real& scalar) const;

        ////////////////////////////////////////////////////////////
        /** @brief Return a scaled copy of this vector.
         *
         *  This is effectively the same as normalizing the vector first
         *  and then multiplying by new_length.
        **/
        ////////////////////////////////////////////////////////////
        Vector4 scaledToLenght(const Real& new_lenght) const;

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Return true if the w component is either 0 or 1.
         *
         *  This is a required condition for several functions to work
         *  correctly.
        **/
        ////////////////////////////////////////////////////////////
        bool isWZeroOrOne(Real epsilon = 1e-6f) const;

        ////////////////////////////////////////////////////////////
        /** @brief Return true if all components of this vector are
         *  0.
        **/
        ////////////////////////////////////////////////////////////
        bool isZero(Real epsilon = 1e-6f) const;

        ////////////////////////////////////////////////////////////
        /** @brief Return true if the (x,y,z) part of this vector is
         *  0.
        **/
        ////////////////////////////////////////////////////////////
        bool isZero3(Real epsilon = 1e-6f) const;

        ////////////////////////////////////////////////////////////
        /** @brief Return true if the lenght of this vector is 1, up
         *  to the given epsilon.
        **/
        ////////////////////////////////////////////////////////////
        bool isNormalized(Real epsilon = 1e-6f) const;

        ////////////////////////////////////////////////////////////
        /** @brief Return true if the lenght of the (x,y,z) part of
         *  this vector is 1, up to the given epsilon.
        **/
        ////////////////////////////////////////////////////////////
        bool isNormalized3(Real epsilon = 1e-6f) const;

        ////////////////////////////////////////////////////////////
        /** @brief Return true if the elements of this vector are
         *  all finite.
        **/
        ////////////////////////////////////////////////////////////
        bool isFinite() const;

        ////////////////////////////////////////////////////////////
        /** @brief Returns true if the (x, y, z) parts of two vectors
         *  are perpendicular to each other.
        **/
        ////////////////////////////////////////////////////////////
        bool isPerpendicular3(const Vector4& other, Real epsilon = 1e-6f) const;

    public:

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
        Real dot(const Vector4& other) const;

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
        Real dot3(const Vector3& other) const;

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
        Real dot3(const Vector4& other) const;

        ////////////////////////////////////////////////////////////
        /** @brief Computes an absoluted dot product between this
         *  vector and given one.
        **/
        ////////////////////////////////////////////////////////////
        Real dotabs(const Vector4& other) const;

        ////////////////////////////////////////////////////////////
        /** @brief Computes an absoluted dot product between this
         *  vector and given one.
        **/
        ////////////////////////////////////////////////////////////
        Real dotabs3(const Vector3& other) const;

        ////////////////////////////////////////////////////////////
        /** @brief Computes the cross product between this vector and
         *  given one.
         *
         *  Unless this vector and the given vector are linearly dependent,
         *  the cross product returns a vector that is perpendicular to
         *  both vectors.
         *
         *  @return A vector4 with w=0.
        **/
        ////////////////////////////////////////////////////////////
        Vector4 cross3(const Vector4& other) const;

        ////////////////////////////////////////////////////////////
        /** @brief Computes the cross product between this vector and
         *  given one.
         *
         *  Unless this vector and the given vector are linearly dependent,
         *  the cross product returns a vector that is perpendicular to
         *  both vectors.
         *
         *  @return A vector4 with w=0.
        **/
        ////////////////////////////////////////////////////////////
        Vector4 cross3(const Vector3& other) const;

        ////////////////////////////////////////////////////////////
        /** @brief Computes the outer product between this vector and
         *  given one.
        **/
        ////////////////////////////////////////////////////////////
        Matrix4x4 outerProduct(const Vector4& rhs) const;

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Returns a new normalized direction vector that points
         *  as close as possible towards the given hint vector.
        **/
        ////////////////////////////////////////////////////////////
        Vector4 perpendicular3(const Vector3& hint = Vector3(0,1,0), const Vector3& hint2 = Vector3(0,0,1)) const;

        ////////////////////////////////////////////////////////////
        /** @brief Returns another vector that is perpendicular to this
         *  vector and the vector returned by perpendicular3(hint).
        **/
        ////////////////////////////////////////////////////////////
        Vector4 anotherPerpendicular3(const Vector3& hint = Vector3(0,1,0), const Vector3& hint2 = Vector3(0,0,1)) const;

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
        Vector4 reflect(const Vector3& normal) const;

    public:

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
        Radian angleBetween(const Vector4& other) const;

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
        Radian angleBetweenNorm(const Vector4& normalizedVector) const;

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
        Radian angleBetween3(const Vector4& other) const;

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
        Radian angleBetweenNorm3(const Vector4& normalizedVector) const;

    public:

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
        Vector4 projectTo3(const Vector3& direction) const;

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
        Vector4 projectToNorm3(const Vector3& direction) const;

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Linearly interpolates between this and the vector
         *  b.
         *
         *  This function assumes that the w components of this and the
         *  other vector are equal.
         *
         *  @param b : The target endpoint.
         *  @param t : The interpolation weight, in range [0, 1].
         *
         *  @return (b, 0) returns this vector, (b, 1) returns b.
        **/
        ////////////////////////////////////////////////////////////
        Vector4 linearInterpolate(const Vector4& b, Real t) const;

        ////////////////////////////////////////////////////////////
        /** @brief Identical to a.linearInterpolate(b, t).
        **/
        ////////////////////////////////////////////////////////////
        static Vector4 LinearInterpolate(const Vector4& a, const Vector4& b, Real t) { return a.linearInterpolate(b, t); }

    public:

        static const Vector4 Zero;
        static const Vector4 One;
        static const Vector4 UnitX;
        static const Vector4 UnitY;
        static const Vector4 UnitZ;
        static const Vector4 UnitW;
        static const Vector4 Inf;
        static const Vector4 nan;

    };
}

#endif // APRO_VECTOR4_H
