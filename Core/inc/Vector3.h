/** @file Vector3.h
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 5/10/2012
 *
 *  @addtogroup Global
 *  @addtogroup System
 *
 *  This file defines the Vector3 class.
 *
**/
#ifndef APROVECTOR3_H
#define APROVECTOR3_H

#include "Maths.h"

namespace APro
{
    /*
        Largely based on Ogre::Vector3 ;)
    */

    template <typename Num>
    class Vector3
    {
    public:

        Num x;
        Num y;
        Num z;

    public:

        Vector3() : x (0), y (0), z (0)
        {

        }

        Vector3(const Vector3<Num>& v) : x (v.x), y(v.y), z(v.z)
        {

        }

        template <typename Num2>
        Vector3(const Vector3<Num2>& v)
        {
            x = static_cast<Num>(v.x);
            y = static_cast<Num>(v.y);
            z = static_cast<Num>(v.z);
        }

        explicit Vector3(Num n) : x(n), y(n), z(n)
        {

        }

        explicit Vector3(const Num v[3]) : x(v[0]), y(v[1]), z(v[2])
        {

        }

        Vector3(Num n1, Num n2, Num n3) : x(n1), y(n2), z(n3)
        {

        }

        void swap(Vector3<Num>& v)
        {
            swapNumeric_xor(x, v.x);
            swapNumeric_xor(y, v.y);
            swapNumeric_xor(z, v.z);
        }

        Num* ptr()
        {
            return &x;
        }

        const Num* ptr() const
        {
            return &x;
        }

        Num& operator [] (size_t i)
        {
            return *((&x) + i);
        }

        const Num& operator [] (size_t i) const
        {
            return *((&x) + i);
        }

        Vector3<Num>& operator = (const Vector3<Num>& other)
        {
            x = other.x;
            y = other.y;
            z = other.z;

            return *this;
        }

        inline bool operator == (const Vector3<Num>& v) const
        {
            return x == v.x && y == v.y && z == v.z;
        }

        inline bool operator != (const Vector3<Num>& v) const
        {
            return !(*this == v);
        }

        Vector3<Num> operator + (const Vector3<Num>& v) const
        {
            return Vector3<Num>(x + v.x, y + v.y, z + v.z);
        }

        Vector3<Num> operator - (const Vector3<Num>& v) const
        {
            return Vector3<Num>(x - v.x, y - v.y, z - v.z);
        }

        Vector3<Num> operator * (const Vector3<Num>& v) const
        {
            return Vector3<Num>(x * v.x, y * v.y, z * v.z);
        }

        Vector3<Num> operator * (Num n) const
        {
            return Vector3<Num>(x*n, y*n, z*n);
        }

        Vector3<Num> operator / (const Vector3<Num>& v) const
        {
            return Vector3<Num>(x / v.x, y / v.y, z / v.z);
        }

        Vector3<Num> operator / (Num n) const
        {
            return Vector3<Num>(x/n, y/n, z/n);
        }

        Vector3<Num> operator + () const
        {
            return Vector3<Num>(*this);
        }

        Vector3<Num> operator - () const
        {
            return Vector3<Num>(-x, -y, -z);
        }

        inline friend Vector3<Num> operator * ( const Num fScalar, const Vector3<Num>& rkVector )
        {
            return Vector3<Num>(
                fScalar * rkVector.x,
                fScalar * rkVector.y,
                fScalar * rkVector.z);
        }

        inline friend Vector3<Num> operator / ( const Num fScalar, const Vector3<Num>& rkVector )
        {
            return Vector3<Num>(
                fScalar / rkVector.x,
                fScalar / rkVector.y,
                fScalar / rkVector.z);
        }

        inline friend Vector3<Num> operator + (const Vector3<Num>& lhs, const Num rhs)
        {
            return Vector3<Num>(
                lhs.x + rhs,
                lhs.y + rhs,
                lhs.z + rhs);
        }

        inline friend Vector3<Num> operator + (const Num lhs, const Vector3<Num>& rhs)
        {
            return Vector3<Num>(
                lhs + rhs.x,
                lhs + rhs.y,
                lhs + rhs.z);
        }

        inline friend Vector3<Num> operator - (const Vector3<Num>& lhs, const Num rhs)
        {
            return Vector3<Num>(
                lhs.x - rhs,
                lhs.y - rhs,
                lhs.z - rhs);
        }

        inline friend Vector3<Num> operator - (const Num lhs, const Vector3<Num>& rhs)
        {
            return Vector3<Num>(
                lhs - rhs.x,
                lhs - rhs.y,
                lhs - rhs.z);
        }

        Vector3<Num>& operator += (const Num n)
        {
            x += n;
            y += n;
            z += n;

            return *this;
        }

        Vector3<Num>& operator -= (const Num n)
        {
            x -= n;
            y -= n;
            z -= n;

            return *this;
        }

        Vector3<Num>& operator *= (const Num n)
        {
            x *= n;
            y *= n;
            z *= n;

            return *this;
        }

        Vector3<Num>& operator /= (const Num n)
        {
            x /= n;
            y /= n;
            z /= n;

            return *this;
        }

        Vector3<Num>& operator += (const Vector3<Num>& n)
        {
            x += n.x;
            y += n.y;
            z += n.z;

            return *this;
        }

        Vector3<Num>& operator -= (const Vector3<Num>& n)
        {
            x -= n.x;
            y -= n.y;
            z -= n.z;

            return *this;
        }

        Vector3<Num>& operator *= (const Vector3<Num>& n)
        {
            x *= n.x;
            y *= n.y;
            z *= n.z;

            return *this;
        }

        Vector3<Num>& operator /= (const Vector3<Num>& n)
        {
            x /= n.x;
            y /= n.y;
            z /= n.z;

            return *this;
        }

        Num lenght() const
        {
            return Sqrt(x * x + y * y + z * z);
        }

        Num squaredLenght() const
        {
            return x * x + y * y + z * z;
        }

        Num distance(const Vector3<Num>& other) const
        {
            return (*this - other).lenght();
        }

        Vector3<Num> vdistance(const Vector3<Num>& other) const
        {
            Vector3<Num> tmp = *this - other;
            if(tmp.x < 0) tmp.x = -tmp.x;
            if(tmp.y < 0) tmp.y = -tmp.y;
            if(tmp.z < 0) tmp.z = -tmp.z;

            return tmp;
        }

        Num squaredDistance(const Vector3<Num>& other) const
        {
            return (*this - other).lenght();
        }

        Num dotProduct(const Vector3<Num>& other) const
        {
            return x * other.x + y * other.y + z * other.z;
        }

        Num absDotProduct(const Vector3<Num>& other) const
        {
            return abs_(x * other.x) + abs_(y * other.y) + abs_(z * other.z);
        }

        Num normalise()
        {
            Num len = lenght();

            if(len > 1e-08)
            {
                Num invLenght = 1.0 / len;
                x *= invLenght;
                y *= invLenght;
                z *= invLenght;
            }

            return len;
        }

        Vector3<Num> crossProduct(const Vector3<Num>& other) const
        {
            return Vector3<Num>(
                y * other.z - z * other.y,
                z * other.x - x * other.z,
                x * other.y - y * other.x);
        }

        Vector3<Num> midPoint(const Vector3<Num>& other) const
        {
            return Vector3<Num>(
                ( x + other.x ) * 0.5f,
                ( y + other.y ) * 0.5f,
                ( z + other.z ) * 0.5f );
        }

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

        void floor(const Vector3<Num>& other)
        {
            if(other.x < x) x = other.x;
            if(other.y < y) y = other.y;
            if(other.z < z) z = other.z;
        }

        void ceil(const Vector3<Num>& other)
        {
            if(other.x > x) x = other.x;
            if(other.y > y) y = other.y;
            if(other.z > z) z = other.z;
        }

        Vector3<Num> perpendicular() const
        {
            static const float fSquareZero = (float)(1e-06 * 1e-06);

            Vector3<Num> perp = this->crossProduct(Vector3<Num>::UNIT_X);

            if((float) perp.squaredLenght() < fSquareZero)
            {
                perp = this->crossProduct(Vector3<Num>::UNIT_Y);
            }

            perp.normalise();
            return perp;
        }

        double angleBetween(const Vector3<Num>& v)
        {
            Num len = lenght() * v.lenght();

            if(len < 1e-06)
                len = 1e-06;

            Num f = dotProduct(v) / len;

            f = Clamp(f, (Real)-1.0, (Real)1.0);
			return ACos(f);
        }

        inline friend Console& operator << (Console& c, const Vector3<Num>& v)
        {
            c << "Vector3<" << typeid(Num).name() << ">( " << v.x << ", " << v.y << ", " << v.z << " )";
            return c;
        }
    };

    typedef Vector3<float> Vector3F;
    typedef Vector3<double> Vector3D;
    typedef Vector3<unit_t> Vector3U;
}

#endif
