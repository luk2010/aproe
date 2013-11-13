////////////////////////////////////////////////////////////
/** @file Vector2.cpp
 *  @ingroup Maths
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 11/09/2013
 *
 *  Implements the Vector2 class.
 *
**/
////////////////////////////////////////////////////////////

#include "Vector2.h"

namespace APro
{
    // Usefull class to... sort by polar angle Vectors.
    class SortByPolarAngle
    {
    public:
        Vector2 perspective;

        int operator () (const Vector2& a, const Vector2& b) const
        {
            Vector2 A = a - perspective;
            Vector2 B = b - perspective;
            return A.x*B.y - B.x*A.y;
        }
    };


    Vector2::Vector2() : x(0), y(0)
    {

    }

    Vector2::Vector2(const Vector2& v) : x(v.x), y(v.y)
    {

    }

    Vector2::Vector2(const Real& n1, const Real& n2) : x(n1), y(n2)
    {

    }

    Vector2::Vector2(const Real& n) : x(n), y(n)
    {

    }

    Vector2::Vector2(const Real n[2]) : x(n[0]), y(n[1])
    {

    }

    Vector2::~Vector2()
    {

    }

    void Vector2::swap(Vector2& v)
    {
        // Now using xor swap
        swapNumeric_xor(x, v.x);
        swapNumeric_xor(y, v.y);
    }

    bool Vector2::equals(const Vector2& v) const
    {
        return *this == v;
    }

    bool Vector2::equals(const Real& n1, const Real& n2) const
    {
        return x == n1 && y == n2;
    }

    bool Vector2::operator == (const Vector2& v) const
    {
        return x == v.x && y == v.y;
    }

    bool Vector2::operator != (const Vector2& v) const
    {
        return ! (*this == v);
    }

    bool Vector2::operator > (const Vector2& v) const
    {
        return x > v.x && y > v.y;
    }

    bool Vector2::operator < (const Vector2& v) const
    {
        return x < v.x && y < v.y;
    }

    bool Vector2::operator >= (const Vector2& v) const
    {
        return x >= v.x && y >= v.y;
    }

    bool Vector2::operator <= (const Vector2& v) const
    {
        return x <= v.x && y <= v.y;
    }

    Vector2& Vector2::set(const Vector2& v)
    {
        x = v.x;
        y = v.y;

        return *this;
    }

    Vector2& Vector2::set(const Real& n1, const Real& n2)
    {
        x = n1;
        y = n2;

        return *this;
    }

    Vector2& Vector2::set(const Real& n)
    {
        x = n;
        y = n;

        return *this;
    }

    Vector2& Vector2::operator = (const Vector2& v)
    {
        x = v.x;
        y = v.y;

        return *this;
    }

    Vector2& Vector2::operator = (const Real& n)
    {
        x = n;
        y = n;

        return *this;
    }

    void Vector2::floor(const Vector2& v)
    {
        if(v.x < x) x = v.x;
        if(v.y < y) y = v.y;
    }

    void Vector2::ceil(const Vector2& v)
    {
        if(v.x > x) x = v.x;
        if(v.y > y) y = v.y;
    }

    Vector2& Vector2::add(const Vector2& v)
    {
        return *this += v;
    }

    Vector2& Vector2::add(const Real& n)
    {
        return *this += n;
    }

    Vector2 Vector2::added(const Vector2& v) const
    {
        return *this + v;
    }

    Vector2 Vector2::added(const Real& n) const
    {
        return *this += n;
    }

    Vector2& Vector2::operator += (const Vector2& v)
    {
        x += v.x;
        y += v.y;
        return *this;
    }

    Vector2& Vector2::operator += (const Real& n)
    {
        x += n;
        y += n;
        return *this;
    }

    Vector2 Vector2::operator + (const Vector2& v) const
    {
        return Vector2(x + v.x,
                       y + v.y);
    }

    Vector2 Vector2::operator + (const Real& n) const
    {
        return Vector2(x + n,
                       y + n);
    }

    Vector2& Vector2::substract(const Vector2& v)
    {
        return *this -= v;
    }

    Vector2& Vector2::substract(const Real& n)
    {
        return *this -= n;
    }

    Vector2 Vector2::substracted(const Vector2& v) const
    {
        return *this - v;
    }

    Vector2 Vector2::substracted(const Real& n) const
    {
        return *this - n;
    }

    Vector2& Vector2::operator -= (const Vector2& v)
    {
        x -= v.x;
        y -= v.y;
        return *this;
    }

    Vector2& Vector2::operator -= (const Real& n)
    {
        x -= n;
        y -= n;
        return *this;
    }

    Vector2 Vector2::operator - (const Vector2& v) const
    {
        return Vector2(x - v.x,
                       y - v.y);
    }

    Vector2 Vector2::operator - (const Real& n) const
    {
        return Vector2(x - n,
                       y - n);
    }

    Vector2& Vector2::multiply(const Vector2& v)
    {
        return *this *= v;
    }

    Vector2& Vector2::multiply(const Real& n)
    {
        return *this *= n;
    }

    Vector2 Vector2::multiplied(const Vector2& v) const
    {
        return *this * v;
    }

    Vector2 Vector2::multiplied(const Real& n) const
    {
        return *this * n;
    }

    Vector2& Vector2::operator *= (const Vector2& v)
    {
        x *= v.x;
        y *= v.y;
        return *this;
    }

    Vector2& Vector2::operator *= (const Real& n)
    {
        x *= n;
        y *= n;
        return *this;
    }

    Vector2 Vector2::operator * (const Vector2& v) const
    {
        return Vector2(x * v.x,
                       y * v.y);
    }

    Vector2 Vector2::operator * (const Real& n) const
    {
        return Vector2(x * n,
                       y * n);
    }

    Vector2& Vector2::divide(const Vector2& v)
    {
        return *this /= v;
    }

    Vector2& Vector2::divide(const Real& n)
    {
        return *this /= n;
    }

    Vector2 Vector2::divided(const Vector2& v) const
    {
        return *this / v;
    }

    Vector2 Vector2::divided(const Real& n) const
    {
        return *this / n;
    }

    Vector2& Vector2::operator /= (const Vector2& v)
    {
        x /= v.x;
        y /= v.y;
        return *this;
    }

    Vector2& Vector2::operator /= (const Real& n)
    {
        x /= n;
        y /= n;
        return *this;
    }

    Vector2 Vector2::operator / (const Vector2& v) const
    {
        return Vector2(x / v.x,
                       y / v.y);
    }

    Vector2 Vector2::operator / (const Real& n) const
    {
        return Vector2(x / n,
                       y / n);
    }

    const Real& Vector2::at(size_t i) const
    {
        return i == 0 ? x : y;
    }

    Real& Vector2::at(size_t i)
    {
        return i == 0 ? x : y;
    }

    const Real& Vector2::operator[](size_t i) const
    {
        return i == 0 ? x : y;
    }

    Real& Vector2::operator[](size_t i)
    {
        return i == 0 ? x : y;
    }

    const Real* Vector2::ptr() const
    {
        return &x;
    }

    Real* Vector2::ptr()
    {
        return &x;
    }

    inline Vector2 Vector2::operator + () const
    {
        return *this;
    }

    inline Vector2 Vector2::operator - () const
    {
        return Vector2(-x, -y);
    }

    Vector2& Vector2::negate()
    {
        x = -x;
        y = -y;
        return -this;
    }

    Vector2 Vector2::negated() const
    {
        return Vector2(-x, -y);
    }

    Vector2 Vector2::absoluted() const
    {
        return Vector2(Math::Abs(x), Math::Abs(y));
    }

    Vector2& Vector2::absolute()
    {
        x = Math::Abs(x);
        y = Math::Abs(y);
        return *this;
    }

    Vector2& Vector2::invert()
    {
        swapNumeric(x, y);
        return *this;
    }

    Vector2& Vector2::inverted() const
    {
        return Vector2(y, x);
    }

    Real Vector2::lenght() const
    {
        return Math::Sqrt(x * x + y * y);
    }

    Real Vector2::squaredLenght() const
    {
        return x * x + y * y;
    }

    Real Vector2::distance(const Vector2& v) const
    {
        return (*this - v).lenght();
    }

    Real Vector2::squaredDistance(const Vector2& v) const
    {
        return (*this - v).squaredLenght();
    }

    Vector2 Vector2::midPoint(const Vector2& v) const
    {
        return Vector2((x + v.x) * 0.5f,
                        (y + v.y) * 0.5f);
    }

    void Vector2::setFromPolarCoordinates(const Radian& theta, const Real& len)
    {
        x = Angle::Cos(theta) * len;
        y = Angle::Sin(theta) * len;
    }

    void Vector2::setFromPolarCoordinates(const Vector2& polar)
    {
        setFromPolarCoordinate((Radian)polar.x, polar.y);
    }

    Vector2 Vector2::FromPolarCoordinates(const Radian& theta, const Real& len)
    {
        Vector2 euclidean;
        euclidean.setFromPolarCoordinates(theta, len);
        return euclidean;
    }

    Vector2 Vector2::FromPolarCoordinates(const Vector2& polar)
    {
        return Vector2::FromPolarCoordinates((Radian)polar.x, polar.y);
    }

    Vector2 Vector2::toPolarCoordinates() const
    {
        Real l = lenght();
        if(l > 1e-4f)
            return Vector2(Angle::ATan2(y, x), l);
        else
            return Vector2::Zero;
    }

    Radian Vector2::aimedAngle() const
    {
        if(!isZero())
            return Angle::ATan2(y, x);
        else
            return 0;
    }

    Real Vector2::dotProduct(const Vector2& v) const
    {
        return (x * v.x) + (y * v.y);
    }

    Vector2 Vector2::crossProduct(const Vector2& v) const
    {
        return x * v.y - y * v.x;
    }

    Real Vector2::normalize()
    {
        Real l = lenght();

        if(l > 1e-08)
        {
            Real invLenght = 1 / l;
            x *= invLenght;
            y *= invLenght;
        }

        return l;
    }

    Vector2 Vector2::normalized() const
    {
        Vector2 v(*this);
        v.normalize();
        return v;
    }

    Vector2 Vector2::perpendicular() const
    {
        return Vector2(-y, x);
    }

    Vector2 Vector2::reflect(const Vector2& normal) const
    {
        return 2.f * this->projectToNorm(normal) - this;
    }

    Vector2 Vector2::refract(const Vector2& normal, Real negativSideRefractionIndex, Real positiveSideRefractionIndex) const
    {
        Real n = negativSideRefractionIndex / positiveSideRefractionIndex;
        Real cosI = this->dotProduct(normal);
        Real sinT2 = n*n*(1.f - cosI * cosI);

        if(sinT2 > 1.f)
            return (-(*this)).reflect(normal);
        return n * *this - (n + Math::Sqrt(1.f - sinT2)) * normal;
    }

    Vector2& Vector2::rotate90CW()
    {
        Real tmp = x;
        x = y;
        y = -tmp;
        return *this;
    }

    Vector2 Vector2::rotated90CW() const
    {
        return perpendicular();
    }

    Vector2& Vector2::rotate90CCW()
    {
        Real tmp = x;
        x = -y;
        y = tmp;
        return *this;
    }

    Vector2 Vector2::rotated90CCW() const
    {
        return Vector2(-y, x);
    }

    bool Vector2::isOrientedCCW(const Vector2& a, const Vector2& b, const Vector2& c)
    {
        return (a.x-c.x)*(b.y-c.y) - (a.y-c.y)*(b.x-c.x) >= 0.f;
    }

    Vector2 Vector2::projectTo(const Vector2& direction) const
    {
        return direction * this->dotProduct(direction) / direction.squaredLenght();
    }

    Vector2 Vector2::projectToNorm(const Vector2& direction) const
    {
        return direction * this->dotProduct(direction);
    }

    Vector2 Vector2::angleBetween(const Vector2& other) const
    {
        return Angle::ACos(dotProduct(other)) / Math::Sqrt(squaredLenght() * other.squaredLenght());
    }

    Vector2 Vector2::angleBetweenNorm(const Vector2& other) const
    {
        return Angle::ACos(dotProduct(other));
    }

    void Vector2::decompose(const Vector2& direction, Vector2& outParalell, Vector2& outPerpendicular) const
    {
        outParalell = this->dotProduct(direction) * direction;
        outPerpendicular = *this - outParalell;
    }

    Vector2 Vector2::linearInterpolate(const Vector2& b, Real t) const
    {
        Math::Clamp(t, 0.0f, 1.0f);
        return (1.f - t) * *this + t * b;
    }

    Vector2 Vector2::LinearInterpolate(const Vector2& a, const Vector2& b, Real t)
    {
        return a.linearInterpolate(b, t);
    }

    void Vector2::Orthogonalize(const Vector2& a, Vector2& b)
    {
        if(a.isZero()) return;

        b -= a.dotProduct(b) / a.lenght() * a;
    }

    bool Vector2::AreOrthogonal(const Vector2& a, const Vector2& b, Real epsilon)
    {
        return a.isPerpendicular(b, epsilon);
    }

    void Vector2::Orthonormalize(Vector2& a, Vector2& b)
    {
        a.normalize();
        b -= a.dotProduct(b) * a;
    }

    void Vector2::ConvexHull(const Vector2* pointArray, size_t numPoints, Array<Vector2>& outConvexHull)
    {
        outConvexHull.clear();
        if(numPoints == 0)
            return;

        outConvexHull.append(pointArray, numPoints);
        int convexhullsize = ConvexHullInPlace(&outConvexHull[0], outConvexHull.size());
        outConvexHull.resize((size_t) convexhullsize);
    }

    int Vector2::ConvexHullInPlace(Vector2* pointArray, size_t nPoints)
    {
        if(nPoints <= 3)
            return nPoints;

        // Lowest point of the set
        Vector2* lowest = &pointArray[0];
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
            Vector2 lineA = pointArray[nPointsInHull - 1] - pointArray[nPointsInHull - 2];
            Vector2 lineB = pointArray[i] - pointArray(nPointsInHull - 2);
            Real lineAlen = lineA.lenght();
            Real lineBlen = lineB.lenght();
            bool dropLastPointFromHull = false;
            if(lineAlen >= 1e-5f)
                lineA /= Math::Sqrt(lineAlen);
            else
                dropLastPointFromHull = true;
            if(lineBlen >= 1e-5f)
                lineB /= Math::Sqrt(lineBlen);

            Vector2 normal(-lineA.y, lineA.x);
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

            Vector2 dirA = pointArray[(i+1)%nPointsInHull] - pointArray[i];
            dirA.normalize();
            Vector2 dirB = pointArray[i] - pointArray[(i+nPointsInHull-1)%nPointsInHull];
            dirB.normalize();
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

    float Vector2::MinAreaRect(const Vector2* pts, int numPoints,
                                 Vector2& center, Vector2& uDir, Vector2& vDir,
                                 Real& minU, Real& maxU, Real& minV, Real& maxV)
    {
        if(!pts)
            return 0.f;
        Real minArea = 1e35f;

        for(int i = 0, j = numPoints - 1; i < numPoints; j = i, ++i)
        {
            Vector2 e0 = pts[i] - pts[j];
            Real len = e0.normalize();
            if(len == 0)
                continue;

            Vector2 e1 = e0.rotated90CCW();

            Real min0 = 1e35f;
            Real min1 = 1e35f;
            Real max0 = -1e35f;
            Real max1 = -1e35f;
            for(int k = 0; k < numPoints; ++k)
            {
                Vector2 d = pts[k] - pts[j];
                Real dot = d.dotProduct(e0);
                if(dot < min0) min0 = dot;
                if(dot > max0) max0 = dot;
                dot = d.dotProduct(e1);
                if(dot < min1) min1 = dot;
                if(dot > max1) max1 = dot;
            }

            Real area = (max0 * min0) - (max1 - min1);
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

    bool Vector2::isZero() const
    {
        return x == 0 && y == 0;
    }

    bool Vector2::isFinite() const
    {
        return IsFinite(x) && IsFinite(y);
    }

    bool Vector2::isPerpendicular(const Vector2& b, Real epsilon = 1e-3f) const
    {
        return Math::Abs(dotProduct(b)) <= epsilon;
    }

    const Vector2 Vector2::Zero = Vector2(0,0);
    const Vector2 Vector2::UnitX = Vector2(1,0);
    const Vector2 Vector2::UnitY = Vector2(0,1);
    const Vector2 Vector2::Nan = Vector2(Math::_real_nan, Math::_real_nan);
    const Vector2 Vector2::Inf = Vector2(Math::_real_inf, Math::_real_inf);

}
