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
     *  @note You should use numerical types that have floating
     *  points, as float, double, unit_t.
    **/
    ////////////////////////////////////////////////////////////
    template<typename Numeric>
    class Vector2
    {
    public:

        Numeric x;///< X value of this vector.
        Numeric y;///< Y value of this vector.

    public: // Constructors

        ////////////////////////////////////////////////////////////
        /** @brief Constructor.
         *  @details Set coordinates to (0,0).
        **/
        ////////////////////////////////////////////////////////////
        Vector2() : x(0), y(0)
        {

        }

        ////////////////////////////////////////////////////////////
        /** @brief Copy Constructor.
         *  @details Set coordinates to (v.x, v.y).
        **/
        ////////////////////////////////////////////////////////////
        Vector2(const Vector2<Numeric>& v) : x(v.x), y(v.y)
        {

        }

        ////////////////////////////////////////////////////////////
        /** @brief Constructor.
         *  @details Set coordinates to (n1, n2).
        **/
        ////////////////////////////////////////////////////////////
        Vector2(Numeric n1, Numeric n2) : x(n1), y(n2)
        {

        }

        ////////////////////////////////////////////////////////////
        /** @brief Constructor.
         *  @details Set coordinates to (n, n).
        **/
        ////////////////////////////////////////////////////////////
        explicit Vector2(Numeric n) : x(n), y(n)
        {

        }

        ////////////////////////////////////////////////////////////
        /** @brief Constructor from array.
         *  @details Set coordinates to (n[0], n[1]).
        **/
        ////////////////////////////////////////////////////////////
        explicit Vector2(const Numeric n[2]) : x(n[0]), y(n[1])
        {

        }

        ////////////////////////////////////////////////////////////
        /** @brief Destructor.
        **/
        ////////////////////////////////////////////////////////////
        ~Vector2()
        {

        }

    public: // Swap function

        ////////////////////////////////////////////////////////////
        /** @brief Swap current vector with given one.
         *  @param v : Vector to swap.
         *  @note It use xor swapping.
        **/
        ////////////////////////////////////////////////////////////
        inline void swap(Vector2<Numeric>& v)
        {
            /*
            Vector2<Numeric> cpy(v);
            x = v.x;
            y = v.y;
            v = cpy;
            */

            // Now using xor swap
            swapNumeric_xor(x, v.x);
            swapNumeric_xor(y, v.y);
        }

    public: // Egality operators

        ////////////////////////////////////////////////////////////
        /** @brief Tell if 2 vectors are equals.
        **/
        ////////////////////////////////////////////////////////////
        bool equals(const Vector2<Numeric>& v) const
        {
            return *this == v;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Tell if vector is equal to 2 given numerics.
        **/
        ////////////////////////////////////////////////////////////
        bool equals(const Numeric& n1, const Numeric& n2) const
        {
            return x == n1 && y == n2;
        }

        bool operator == (const Vector2<Numeric>& v) const
        {
            return x == v.x && y == v.y;
        }

        bool operator != (const Vector2<Numeric>& v) const
        {
            return ! (*this == v);
        }

    public: // Superior / inferior strict operators

        bool operator > (const Vector2<Numeric>& v) const
        {
            return x > v.x && y > v.y;
        }

        bool operator < (const Vector2<Numeric>& v) const
        {
            return x < v.x && y < v.y;
        }

    public: // Superior / inferior operators

        bool operator >= (const Vector2<Numeric>& v) const
        {
            return x >= v.x && y >= v.y;
        }

        bool operator <= (const Vector2<Numeric>& v) const
        {
            return x <= v.x && y <= v.y;
        }

    public: // Assignment operators

        ////////////////////////////////////////////////////////////
        /** @brief Set coordinates to given vector.
        **/
        ////////////////////////////////////////////////////////////
        Vector2<Numeric>& set(const Vector2<Numeric>& v)
        {
            x = v.x;
            y = v.y;

            return *this;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Set coordinates to given pair.
        **/
        ////////////////////////////////////////////////////////////
        Vector2<Numeric>& set(const Numeric& n1, const Numeric& n2)
        {
            x = n1;
            y = n2;

            return *this;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Set coordinates to given numeric.
        **/
        ////////////////////////////////////////////////////////////
        Vector2<Numeric>& set(const Numeric& n)
        {
            x = n;
            y = n;

            return *this;
        }

        Vector2<Numeric>& operator = (const Vector2<Numeric>& v)
        {
            x = v.x;
            y = v.y;

            return *this;
        }

        Vector2<Numeric>& operator = (const Numeric& n)
        {
            x = n;
            y = n;

            return *this;
        }

    public: // Floor / ceil

        ////////////////////////////////////////////////////////////
        /** @brief Floor the current vector with given one.
         *
         *  It takes the minimum value for each coordinate and
         *  attriutes it to this vector.
        **/
        ////////////////////////////////////////////////////////////
        void floor(const Vector2<Num>& v)
        {
            if(v.x < x) x = v.x;
            if(v.y < y) y = v.y;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Ceil current vector with given one.
         *
         *  It takes the maximum value for each coordinate and
         *  attriutes it to this vector.
        **/
        ////////////////////////////////////////////////////////////
        void ceil(const Vector2<Num>& v)
        {
            if(v.x > x) x = v.x;
            if(v.y > y) y = v.y;
        }

    public: // Addition

        ////////////////////////////////////////////////////////////
        /** @brief Add a vector to this one.
         *  @param v : Vector to add.
        **/
        ////////////////////////////////////////////////////////////
        Vector2<Numeric>& add(const Vector2<Numeric>& v)
        {
            return *this += v;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Add a numeric to this one.
         *  @param n : Numeric to add.
         *  @return (x + n, y + n)
        **/
        ////////////////////////////////////////////////////////////
        Vector2<Numeric>& add(const Numeric& n)
        {
            return *this += n;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Return the vector when adding given one.
         *  @param v : Vector to add.
        **/
        ////////////////////////////////////////////////////////////
        Vector2<Numeric> added(const Vector2<Numeric>& v) const
        {
            return *this + v;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Return the vector when adding given numeric.
         *  @param n : Numeric to add.
         *  @return (x + n, y + n)
        **/
        ////////////////////////////////////////////////////////////
        Vector2<Numeric> added(const Numeric& n) const
        {
            return *this += n;
        }

        Vector2<Numeric>& operator += (const Vector2<Numeric>& v)
        {
            x += v.x;
            y += v.y;
            return *this;
        }

        Vector2<Numeric>& operator += (const Numeric& n)
        {
            x += n;
            y += n;
            return *this;
        }

        Vector2<Numeric> operator + (const Vector2<Numeric>& v) const
        {
            return Vector2<Numeric>(x + v.x,
                                    y + v.y);
        }

        Vector2<Numeric> operator + (const Numeric& n) const
        {
            return Vector2<Numeric>(x + n,
                                    y + n);
        }

    public: // Substraction

        ////////////////////////////////////////////////////////////
        /** @brief Substract a vector to this one.
         *  @param v : Vector to substract.
        **/
        ////////////////////////////////////////////////////////////
        Vector2<Numeric>& substract(const Vector2<Numeric>& v)
        {
            return *this -= v;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Substract a numeric to this one.
         *  @param n : Numeric to substract.
         *  @return (x - n, y - n)
        **/
        ////////////////////////////////////////////////////////////
        Vector2<Numeric>& substract(const Numeric& n)
        {
            return *this -= n;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Return the vector if a substraction was applied
         *  to this one.
         *  @param v : Vector to substract.
        **/
        ////////////////////////////////////////////////////////////
        Vector2<Numeric> substracted(const Vector2<Numeric>& v) const
        {
            return *this - v;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Return the vector if a substraction was applied
         *  to this one.
         *  @param n : Numeric to substract.
        **/
        ////////////////////////////////////////////////////////////
        Vector2<Numeric> substracted(const Numeric& n) const
        {
            return *this - n;
        }

        Vector2<Numeric>& operator -= (const Vector2<Numeric>& v)
        {
            x -= v.x;
            y -= v.y;
            return *this;
        }

        Vector2<Numeric>& operator -= (const Numeric& n)
        {
            x -= n;
            y -= n;
            return *this;
        }

        Vector2<Numeric> operator - (const Vector2<Numeric>& v) const
        {
            return Vector2<Numeric>(x - v.x,
                                    y - v.y);
        }

        Vector2<Numeric> operator - (const Numeric& n) const
        {
            return Vector2<Numeric>(x - n,
                                    y - n);
        }

    public: // Multiplication

        ////////////////////////////////////////////////////////////
        /** @brief Multiply a vector to this one.
         *  @param v : Vector to Multiply.
        **/
        ////////////////////////////////////////////////////////////
        Vector2<Numeric>& multiply(const Vector2<Numeric>& v)
        {
            return *this *= v;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Multiply a numeric to this one.
         *  @param n : Numeric to Multiply.
         *  @return (x * n, y * n)
        **/
        ////////////////////////////////////////////////////////////
        Vector2<Numeric>& multiply(const Numeric& n)
        {
            return *this *= n;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Return the vector if a multiplication was applied
         *  to this one.
         *  @param v : Vector to Multiply.
        **/
        ////////////////////////////////////////////////////////////
        Vector2<Numeric> multiplied(const Vector2<Numeric>& v) const
        {
            return *this * v;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Return the vector if a multiplication was applied
         *  to this one.
         *  @param n : Numeric to multiply.
        **/
        ////////////////////////////////////////////////////////////
        Vector2<Numeric> multiplied(const Numeric& n) const
        {
            return *this * n;
        }

        Vector2<Numeric>& operator *= (const Vector2<Numeric>& v)
        {
            x *= v.x;
            y *= v.y;
            return *this;
        }

        Vector2<Numeric>& operator *= (const Numeric& n)
        {
            x *= n;
            y *= n;
            return *this;
        }

        Vector2<Numeric> operator * (const Vector2<Numeric>& v) const
        {
            return Vector2<Numeric>(x * v.x,
                                    y * v.y);
        }

        Vector2<Numeric> operator * (const Numeric& n) const
        {
            return Vector2<Numeric>(x * n,
                                    y * n);
        }

    public: // Division

        ////////////////////////////////////////////////////////////
        /** @brief Divide a vector to this one.
         *  @param v : Vector to divide.
        **/
        ////////////////////////////////////////////////////////////
        Vector2<Numeric>& divide(const Vector2<Numeric>& v)
        {
            return *this /= v;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Divide a numeric to this one.
         *  @param n : Numeric to divide.
         *  @return (x / n, y / n)
        **/
        ////////////////////////////////////////////////////////////
        Vector2<Numeric>& divide(const Numeric& n)
        {
            return *this /= n;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Return the vector if a division was applied
         *  to this one.
         *  @param v : Vector to divide.
        **/
        ////////////////////////////////////////////////////////////
        Vector2<Numeric> divided(const Vector2<Numeric>& v) const
        {
            return *this / v;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Return the vector if a division was applied
         *  to this one.
         *  @param n : Numeric to divide.
        **/
        ////////////////////////////////////////////////////////////
        Vector2<Numeric> divided(const Numeric& n) const
        {
            return *this / n;
        }

        Vector2<Numeric>& operator /= (const Vector2<Numeric>& v)
        {
            x /= v.x;
            y /= v.y;
            return *this;
        }

        Vector2<Numeric>& operator /= (const Numeric& n)
        {
            x /= n;
            y /= n;
            return *this;
        }

        Vector2<Numeric> operator / (const Vector2<Numeric>& v) const
        {
            return Vector2<Numeric>(x / v.x,
                                    y / v.y);
        }

        Vector2<Numeric> operator / (const Numeric& n) const
        {
            return Vector2<Numeric>(x / n,
                                    y / n);
        }

    public: // Access

        ////////////////////////////////////////////////////////////
        /** @brief Return either x or y.
        **/
        ////////////////////////////////////////////////////////////
        const Numeric& at(size_t i) const
        {
            return i == 0 ? x : y;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Return either x or y.
        **/
        ////////////////////////////////////////////////////////////
        Numeric& at(size_t i)
        {
            return i == 0 ? x : y;
        }

        const Numeric& operator[](size_t i) const
        {
            return i == 0 ? x : y;
        }

        Numeric& operator[](size_t i)
        {
            return i == 0 ? x : y;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Return a pointer to data.
        **/
        ////////////////////////////////////////////////////////////
        const Numeric* ptr() const
        {
            return &x;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Return a pointer to data.
        **/
        ////////////////////////////////////////////////////////////
        Numeric* ptr()
        {
            return &x;
        }

    public: // Absolute, Negation

        inline Vector2<Numeric> operator + () const
        {
            return *this;
        }

        inline Vector2<Numeric> operator - () const
        {
            return Vector2<Numeric>(-x, -y);
        }

        ////////////////////////////////////////////////////////////
        /** @brief Negate coordinates and return the vector.
        **/
        ////////////////////////////////////////////////////////////
        Vector2<Numeric>& negate()
        {
            x = -x;
            y = -y;
            return -this;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Return a vector from negated one.
        **/
        ////////////////////////////////////////////////////////////
        Vector2<Numeric> negated() const
        {
            return Vector2<Numeric>(-x, -y);
        }

        ////////////////////////////////////////////////////////////
        /** @brief Return a vector from abs coordinates.
        **/
        ////////////////////////////////////////////////////////////
        Vector2<Numeric> absoluted() const
        {
            return Vector2<Numeric>(abs_(x), abs_(y));
        }

        ////////////////////////////////////////////////////////////
        /** @brief Absolute coordinates of this vector and return it.
        **/
        ////////////////////////////////////////////////////////////
        Vector2<Numeric>& absolute()
        {
            x = abs_(x);
            y = abs_(y);
            return *this;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Invert coordinates.
        **/
        ////////////////////////////////////////////////////////////
        Vector2<Numeric>& invert()
        {
            set(x, y);
            return *this;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Return a vector with inverted coordinates.
        **/
        ////////////////////////////////////////////////////////////
        Vector2<Numeric>& inverted() const
        {
            return Vector2<Numeric>(y, x);
        }

    public: // Lenght

        ////////////////////////////////////////////////////////////
        /** @brief Return computed lenght of this vector.
        **/
        ////////////////////////////////////////////////////////////
        Numeric lenght() const
        {
            return Sqrt(x * x + y * y);
        }

        ////////////////////////////////////////////////////////////
        /** @brief Return sqaured computed lenght of this vector.
        **/
        ////////////////////////////////////////////////////////////
        Numeric squaredLenght() const
        {
            return x * x + y * y;
        }

    public: // Distance

        ////////////////////////////////////////////////////////////
        /** @brief Return the distance between 2 Vectors.
        **/
        ////////////////////////////////////////////////////////////
        Numeric distance(const Vector2<Numeric>& v) const
        {
            return (*this - v).lenght();
        }

        ////////////////////////////////////////////////////////////
        /** @brief Return the squared distance between 2 vectors.
        **/
        ////////////////////////////////////////////////////////////
        Numeric squaredDistance(const Vector2<Numeric>& v) const
        {
            return (*this - v).squaredLenght();
        }

        ////////////////////////////////////////////////////////////
        /** @brief Return the point at middle between 2 Vectors.
        **/
        ////////////////////////////////////////////////////////////
        Vector2<Numeric> midPoint(const Vector2<Numeric>& v) const
        {
            return Vector2<Numeric>((x + v.x) * 0.5f,
                                    (y + v.y) * 0.5f);
        }

    public: // Polar coordinates

        ////////////////////////////////////////////////////////////
        /** @brief Set coordinates from polar ones.
        **/
        ////////////////////////////////////////////////////////////
        void setFromPolarCoordinates(const Numeric& theta, const Numeric& len)
        {
            x = Cos(theta) * len;
            y = Sin(theta) * len;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Set coordinates from polar vector.
        **/
        ////////////////////////////////////////////////////////////
        void setFromPolarCoordinates(const Vector2<Numeric>& polar)
        {
            setFromPolarCoordinate(polar.x, polar.y);
        }

        ////////////////////////////////////////////////////////////
        /** @brief Return a vector from polars coordinates.
        **/
        ////////////////////////////////////////////////////////////
        static Vector2<Numeric> FromPolarCoordinates(const Numeric& theta, const Numeric& len)
        {
            Vector2<Numeric> euclidean;
            euclidean.setFromPolarCoordinates(theta, len);
            return euclidean;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Return a vector from polar vector.
        **/
        ////////////////////////////////////////////////////////////
        static Vector2<Numeric> FromPolarCoordinates(const Vector2<Numeric>& polar)
        {
            return Vector2<Numeric>::FromPolarCoordinates(polar.x, polar.y);
        }

        ////////////////////////////////////////////////////////////
        /** @brief Get polar coordinates from euclidean ones.
        **/
        ////////////////////////////////////////////////////////////
        Vector2<Numeric> toPolarCoordinates() const
        {
            Numeric l = lenght();
            if(l > 1e-4f)
                return Vector2<Numeric>(ATan2(y, x), l);
            else
                return Vector2<Numeric>::Zero();
        }

        ////////////////////////////////////////////////////////////
        /** @brief Return the angle in polar coordinates.
        **/
        ////////////////////////////////////////////////////////////
        Numeric aimedAngle() const
        {
            if(!isZero())
                return ATan2(y, x);
            else
                return 0;
        }

    public: // Other

        ////////////////////////////////////////////////////////////
        /** @brief Return the dot product with another vector.
        **/
        ////////////////////////////////////////////////////////////
        Numeric dotProduct(const Vector2<Numeric>& v) const
        {
            return (x * v.x) + (y * v.y);
        }

        ////////////////////////////////////////////////////////////
        /** @brief Return the cross product with another vector.
        **/
        ////////////////////////////////////////////////////////////
        Vector2<Numeric> crossProduct(const Vector2<Numeric>& v) const
        {
            return x * v.y - y * v.x;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Normalise the vector.
        **/
        ////////////////////////////////////////////////////////////
        Numeric normalise()
        {
            Numeric l = lenght();

            if((double) l > 1e-08)
            {
                Numeric invLenght = 1 / l;
                x *= invLenght;
                y *= invLenght;
            }

            return l;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Return a normalised copy of this vector.
        **/
        ////////////////////////////////////////////////////////////
        Vector2<Numeric> normalised() const
        {
            Vector2<Numeric> v(*this);
            v.normalise();
            return v;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Return a vector perpendicular to this one,
         *  after a 90 counter clock-wise rotation.
        **/
        ////////////////////////////////////////////////////////////
        Vector2<Numeric> perpendicular() const
        {
            return Vector2<Numeric>(-y, x);
        }

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
        Vector2<Numeric> reflect(const Vector2<Numeric>& normal) const
        {
            return 2.f * this->projectToNorm(normal) - this;
        }

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
        Vector2<Numeric> refract(const Vector2<Numeric>& normal, float negativSideRefractionIndex, float positiveSideRefractionIndex) const
        {
            float n = negativSideRefractionIndex / positiveSideRefractionIndex;
            float cosI = this->dotProduct(normal);
            float sinT2 = n*n*(1.f - cosI * cosI);
            if(sinT2 > 1.f)
                return (-(*this)).reflect(normal);
            return n * *this - (n + Sqrt(1.f - sinT2)) * normal;
        }

    public: // Rotation

        ////////////////////////////////////////////////////////////
        /** @brief Rotates this vector 90 degrees clock-wise.
         *
         *  This rotation is interpreted in a coordinate system on
         *  a plane where +x extends to the right, and +y extends
         *  upwards.
        **/
        ////////////////////////////////////////////////////////////
        Vector2<Numeric>& rotate90CW()
        {
            Numeric tmp = x;
            x = y;
            y = -tmp;
            return *this;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Return a vector perpendicular to this one (rotated
         *  90 degrees clock-wise).
         *
         *  @note Identical to perpendicular().
        **/
        ////////////////////////////////////////////////////////////
        Vector2<Numeric> rotated90CW() const
        {
            return perpendicular();
        }

        ////////////////////////////////////////////////////////////
        /** @brief Rotates this vector 90 degrees Counter clock-wise.
         *
         *  This rotation is interpreted in a coordinate system on
         *  a plane where +x extends to the right, and +y extends
         *  upwards.
        **/
        ////////////////////////////////////////////////////////////
        Vector2<Numeric>& rotate90CCW()
        {
            Numeric tmp = x;
            x = -y;
            y = tmp;
            return *this;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Return a vector perpendicular to this one (rotated
         *  90 degrees clock-wise).
        **/
        ////////////////////////////////////////////////////////////
        Vector2<Numeric> rotated90CCW() const
        {
            return Vector2<Numeric>(-y, x);
        }

        ////////////////////////////////////////////////////////////
        /** @brief Tell if given triangle a,b,c is oriented Counter
         *  clock-wise.
         *
         *  This function returns true, if the point C lies to the left
		 *  of the directed line AB.
        **/
        ////////////////////////////////////////////////////////////
        static bool isOrientedCCW(const Vector2<Numeric>& a, const Vector2<Numeric>& b, const Vector2<Numeric>& c)
        {
            return (a.x-c.x)*(b.y-c.y) - (a.y-c.y)*(b.x-c.x) >= 0.f;
        }

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
        Vector2<Numeric> projectTo(const vector2<Numeric>& direction) const
        {
            return direction * this->dotProduct(direction) / direction.squaredLenght();
        }

        ////////////////////////////////////////////////////////////
        /** @brief Project this vector onto the normalized direction
         *  vector.
         *
         *  @param direction : The direction vector to project this
         *  vector onto. This vector must be normalized.
        **/
        ////////////////////////////////////////////////////////////
        Vector2<Numeric> projectToNorm(const Vector2<Numeric>& direction) const
        {
            return direction * this->dotProduct(direction);
        }

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
        Vector2<Numeric> angleBetween(const Vector2<Numeric>& other) const
        {
            return ACos(dotProduct(other)) / Sqrt(squaredLenght() * other.squaredLenght());
        }

        ////////////////////////////////////////////////////////////
        /** @brief Return the angle between this vector and the given
         *  normalized vector.
         *
         *  @note This vector must be normalized to call this function.
        **/
        ////////////////////////////////////////////////////////////
        Vector2<Numeric> angleBetweenNorm(const Vector2<Numeric>& other) const
        {
            return ACos(dotProduct(other));
        }

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
        void decompose(const Vector2<Numeric>& direction, Vector2<Numeric>& outParalell, Vector2<Numeric>& outPerpendicular) const
        {
            outParalell = this->dotProduct(direction) * direction;
            outPerpendicular = *this - outParalell;
        }

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
        Vector2<Numeric> linearInterpolate(const Vector2<Numeric>& b, float t) const
        {
            Clamp(t, 0.0f, 1.0f);
            return (1.f - t) * *this + t * b;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Identical to a.linearInterpolate(b, t).
        **/
        ////////////////////////////////////////////////////////////
        static Vector2<Numeric> LinearInterpolate(const Vector2<Numeric>& a, const Vector2<Numeric>& b, float t)
        {
            return a.linearInterpolate(b, t);
        }

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
        static void Orthogonalize(const Vector2<Numeric>& a, Vector2<Numeric>& b)
        {
            if(a.isZero()) return;

            b -= a.dotProduct(b) / a.lenght() * a;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Tell if 2 vectors are perpendicular.
        **/
        ////////////////////////////////////////////////////////////
        static bool AreOrthogonal(const Vector2<Numeric>& a, const Vector2<Numeric>& b, float epsilon = 1e-3f)
        {
            return a.isPerpendicular(b, epsilon);
        }

        ////////////////////////////////////////////////////////////
        /** @brief Makes given vectors linearly independent and
         *  normalized in lenght.
         *  @see Orthogonalize().
        **/
        ////////////////////////////////////////////////////////////
        static void Orthonormalize(Vector2<Numeric>& a, Vector2<Numeric>& b)
        {
            a.normalise();
            b -= a.dotProduct(b) * a;
        }

    protected: // SortByPolarAngle class

        class SortByPolarAngle
        {
        public:
            Vector2<Numeric> perspective;

            int operator () (const Vector2<Numeric>& a, const Vector2<Numeric>& b) const
            {
                Vector2<Numeric> A = a - perspective;
                Vector2<Numeric> B = b - perspective;
                return A.x*B.y - B.x*A.y;
            }
        };

    public: // Convex Hull Computing

        ////////////////////////////////////////////////////////////
        /** @brief Computes the 2D convex hull of the given point
         *  set.
        **/
        ////////////////////////////////////////////////////////////
        static void ConvexHull(const Vector2<Numeric>* pointArray, size_t numPoints, Array<Vector2<Numeric> >& outConvexHull)
        {
            outConvexHull.clear();
            if(numPoints == 0)
                return;

            outConvexHull.append(pointArray, numPoints);
            int convexhullsize = ConvexHullInPlace(&outConvexHull[0], outConvexHull.getSize());
            outConvexHull.resize((size_t) convexhullsize);
        }

        ////////////////////////////////////////////////////////////
        /** @brief Computes the 2D convex hull of the given point
         *  set, in-place.
         *  @return The number of points in the convex hull.
        **/
        ////////////////////////////////////////////////////////////
        static int ConvexHullInPlace(Vector2<Numeric>* pointArray, size_t nPoints)
        {
            if(nPoints <= 3)
                return nPoints;

            // Lowest point of the set
            Vector2<Numeric>* lowest = &pointArray[0];
            for(int i = 1; i < nPoints; ++i)
            {
                if(lowest->y > pointArray[i].y)
                    lowest = &pointArray[i];
            }

            lowest->swap(pointArray[0]);
            SortByPolarAngle pred;
            pred.perspective = pointArray[0];
            quicksort(pointArray + 1, nPoints - 1, pred);
            int nPointsInHull = 2;
            for(int i = 2; i < nPoints; ++i)
            {
                Vector2<Numeric> lineA = pointArray[nPointsInHull - 1] - pointArray[nPointsInHull - 2];
                Vector2<Numeric> lineB = pointArray[i] - pointArray(nPointsInHull - 2);
                Numeric lineAlen = lineA.lenght();
                Numeric lineBlen = lineB.lenght();
                bool dropLastPointFromHull = false;
                if(lineAlen >= 1e-5f)
                    lineA /= Sqrt(lineAlen);
                else
                    dropLastPointFromHull = true;
                if(lineBlen >= 1e-5f)
                    lineB /= Sqrt(lineBlen);

                Vector2<Numeric> normal(-lineA.y, lineA.x);
                if(dropLastPointFromHull || normal.dotProduct(lineB) > 0.f || (normal.dotProduct(lineB) > -1e-4f && lineBlen >= lineAlen))
                {
                    if(nPointsInHull > 2)
                    {
                        --nPointsInHull;
                        --i;
                    }
                    else
                    {
                        pointArray[nPointsInHull - 1] = pointArray[i];
                    }
                }
                else
                {
                    pointArray[nPointsInHull++] = pointArray[i];
                }
            }

            for(int i = 0; i < nPointsInHull && nPointsInHull > 3; ++i)
            {
                if(pointArray[i].equals(pointArray[(i+1)%nPointsInHull]))
                {
                    for(int j = i; j+1 < nPointsInHull; ++j)
                        pointArray[j] = pointArray[j+1];
                    --nPointsInHull;
                    --i;
                    continue;
                }

                Vector2<Numeric> dirA = pointArray[(i+1)%nPointsInHull] - pointArray[i];
                dirA.normalise();
                Vector2<Numeric> dirB = pointArray[i] - pointArray[(i+nPointsInHull-1)%nPointsInHull];
                dirB.normalise();
                if(dirA.dotProduct(dirB) >= 1.f - 1e-3f)
                {
                    for(int j = i; j+1 < nPointsInHull; ++j)
                        pointArray[j] = pointArray[j+1];
                    --nPointsInHull;
                    --i;
                    continue;
                }
            }

            return nPointsInHull;
        }

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
        static float MinAreaRect(const Vector2<Numeric>* pts, int numPoints,
                                 Vector2<Numeric>& center, Vector2<Numeric>& uDir, Vector2<Numeric>& vDir,
                                 Numeric& minU, Numeric& maxU, Numeric& minV, Numeric& maxV)
        {
            if(!pts)
                return 0.f;
            Numeric minArea = 1e35f;

            for(int i = 0, j = numPoints - 1; i < numPoints; j = i, ++i)
            {
                Vector2<Numeric> e0 = pts[i] - pts[j];
                Numeric len = e0.normalise();
                if(len == 0)
                    continue;

                Vector2<Numeric> e1 = e0.rotated90CCW();

                Numeric min0 = 1e35f;
                Numeric min1 = 1e35f;
                Numeric max0 = -1e35f;
                Numeric max1 = -1e35f;
                for(int k = 0; k < numPoints; ++k)
                {
                    Vector2<Numeric> d = pts[k] - pts[j];
                    Numeric dot = d.dotProduct(e0);
                    if(dot < min0) min0 = dot;
                    if(dot > max0) max0 = dot;
                    dot = d.dotProduct(e1);
                    if(dot < min1) min1 = dot;
                    if(dot > max1) max1 = dot;
                }

                Numeric area = (max0 * min0) - (max1 - min1);
                if(area < minArea)
                {
                    minArea = area;
                    center = pts[j] + 0.5f * ((min0 + max0) * e0 + (min1 + max1) * e1);
                    uDir = e0;
                    vDir = e1;
                    minU = min0;
                    maxU = max0;
                    minV = min1;
                    maxV = max1;
                }
            }

            return minArea;
        }

        inline friend Console& operator << (Console& c, const Vector2<Numeric>& v)
        {
            c << "Vector2<" << typeid(Numeric).name() << ">( " << v.x << ", " << v.y << " )";
            return c;
        }

        static Vector2<Numeric> Zero()
        {
            return Vector2<Numeric>(0,0);
        }

        bool isZero() const
        {
            return x == 0 && y == 0;
        }

        bool isPerpendicular(const vector2<Numeric>& b, float epsilon = 1e-3f) const
        {
            return abs_(dotProduct(b)) <= epsilon;
        }
    };

    typedef Vector2<float>  Vector2F;
    typedef Vector2<double> Vector2D;
    typedef Vector2<unit_t> Vector2U;
}

#endif
