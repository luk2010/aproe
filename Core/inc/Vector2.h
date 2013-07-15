/** @file Vector2.h
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 26/09/2012
 *
 *  @addtogroup Global
 *  @addtogroup System
 *
 *  This file defines the Vector2 class.
 *
**/
#ifndef APROVECTOR2_H
#define APROVECTOR2_H

#include "Platform.h"
#include "Console.h"
#include "SString.h"
#include <typeinfo>

namespace APro
{
    template<typename Numeric>
    class Vector2
    {
    public:

        Numeric x;
        Numeric y;

    public:

        Vector2() : x(0), y(0)
        {

        }

        Vector2(const Vector2<Numeric>& v) : x(v.x), y(v.y)
        {

        }

        Vector2(Numeric n1, Numeric n2) : x(n1), y(n2)
        {

        }

        explicit Vector2(Numeric n) : x(n), y(n)
        {

        }

        explicit Vector2(const Numeric n[2]) : x(n[0]), y(n[1])
        {

        }

        ~Vector2()
        {

        }

        inline void swap(Vector2<Numeric>& v)
        {
            Vector2<Numeric> cpy(v);
            x = v.x;
            y = v.y;
            v = cpy;
        }

        Vector2<Numeric>& operator = (const Vector2<Numeric>& v)
        {
            x = v.x;
            y = v.y;

            return *this;
        }

        Vector2<Numeric>& operator = (Numeric n)
        {
            x = n;
            y = n;

            return *this;
        }

        Numeric operator[](size_t i) const
        {
            return i == 0 ? x : y;
        }

        Numeric& operator[](size_t i)
        {
            return i == 0 ? x : y;
        }

        const Numeric* ptr() const
        {
            return &x;
        }

        Numeric* ptr()
        {
            return &x;
        }

        bool operator == (const Vector2<Numeric>& v) const
        {
            return x == v.x && y == v.y;
        }

        bool operator != (const Vector2<Numeric>& v) const
        {
            return ! (*this == v);
        }

        bool operator > (const Vector2<Numeric>& v) const
        {
            return x > v.x && y > v.y;
        }

        bool operator < (const Vector2<Numeric>& v) const
        {
            return x < v.x && y < v.y;
        }

        bool operator >= (const Vector2<Numeric>& v) const
        {
            return x >= v.x && y >= v.y;
        }

        bool operator <= (const Vector2<Numeric>& v) const
        {
            return x <= v.x && y <= v.y;
        }

        Vector2<Numeric>& operator += (const Vector2<Numeric>& v)
        {
            x += v.x;
            y += v.y;
            return *this;
        }

        Vector2<Numeric>& operator -= (const Vector2<Numeric>& v)
        {
            x -= v.x;
            y -= v.y;
            return *this;
        }

        Vector2<Numeric>& operator /= (const Vector2<Numeric>& v)
        {
            x /= v.x;
            y /= v.y;
            return *this;
        }

        Vector2<Numeric>& operator *= (const Vector2<Numeric>& v)
        {
            x *= v.x;
            y *= v.y;
            return *this;
        }

        Vector2<Numeric>& operator += (const Numeric& n)
        {
            x += n;
            y += n;
            return *this;
        }

        Vector2<Numeric>& operator -= (const Numeric& n)
        {
            x -= n;
            y -= n;
            return *this;
        }

        Vector2<Numeric>& operator /= (const Numeric& n)
        {
            x /= n;
            y /= n;
            return *this;
        }

        Vector2<Numeric>& operator *= (const Numeric& n)
        {
            x *= n;
            y *= n;
            return *this;
        }

        Vector2<Numeric> operator + (const Vector2<Numeric>& v) const
        {
            return Vector2<Numeric>(x + v.x,
                                    y + v.y);
        }

        Vector2<Numeric> operator - (const Vector2<Numeric>& v) const
        {
            return Vector2<Numeric>(x - v.x,
                                    y - v.y);
        }

        Vector2<Numeric> operator * (const Vector2<Numeric>& v) const
        {
            return Vector2<Numeric>(x * v.x,
                                    y * v.y);
        }

        Vector2<Numeric> operator / (const Vector2<Numeric>& v) const
        {
            return Vector2<Numeric>(x / v.x,
                                    y / v.y);
        }

        Vector2<Numeric> operator + (const Numeric& n) const
        {
            return Vector2<Numeric>(x + n,
                                    y + n);
        }

        Vector2<Numeric> operator - (const Numeric& n) const
        {
            return Vector2<Numeric>(x - n,
                                    y - n);
        }

        Vector2<Numeric> operator * (const Numeric& n) const
        {
            return Vector2<Numeric>(x * n,
                                    y * n);
        }

        Vector2<Numeric> operator / (const Numeric& n) const
        {
            return Vector2<Numeric>(x / n,
                                    y / n);
        }

        inline Vector2<Numeric> operator + () const
        {
            return *this;
        }

        inline Vector2<Numeric> operator - () const
        {
            return Vector2<Numeric>(-x, -y);
        }

        Numeric lenght() const
        {
            return Sqrt(x * x + y * y);
        }

        Numeric squaredLenght() const
        {
            return x * x + y * y;
        }

        Numeric distance(const Vector2<Numeric>& v) const
        {
            return (*this - v).lenght();
        }

        Numeric squaredDistance(const Vector2<Numeric>& v) const
        {
            return (*this - v).squaredLenght();
        }

        Vector2<Numeric> midPoint(const Vector2<Numeric>& v) const
        {
            return Vector2<Numeric>((x + v.x) * 0.5f,
                                    (y + v.y) * 0.5f);
        }

        Numeric dotProduct(const Vector2<Numeric>& v) const
        {
            return (x * v.x) + (y * v.y);
        }

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

        Vector2<Numeric> normalisedCopy() const
        {
            Vector2<Numeric> v(*this);
            v.normalise();
            return v;
        }

        Vector2<Numeric> perpendicular() const
        {
            return Vector2<Numeric>(-y, x);
        }

        Vector2<Numeric> crossProduct(const Vector2<Numeric>& v) const
        {
            return x * v.y - y * v.x;
        }

        Vector2<Numeric> reflect(const Vector2<Numeric>& v) const
        {
            return Vector2<Numeric>(*this - (2 * this->dotProduct(v) * v));
        }

        inline friend Console& operator << (Console& c, const Vector2<Numeric>& v)
        {
            c << "Vector2<" << typeid(Numeric).name() << ">( " << v.x << ", " << v.y << " )";
            return c;
        }
    };

    typedef Vector2<int> Vector2I;
    typedef Vector2<float> Vector2F;
    typedef Vector2<double> Vector2D;
}

#endif
