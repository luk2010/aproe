////////////////////////////////////////////////////////////
/** @file Maths.cpp
 *  @ingroup Maths
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 26/09/2012
 *
 *  Implements the Maths basics functions.
 *
**/
////////////////////////////////////////////////////////////
#include "Maths.h"
#include <ctgmath>
#include <limits>

namespace APro
{
     const Real Math::PI = 3.14159265359f;
     const Real Math::_real_nan = std::numeric_limits<Real>::quiet_NaN();
     const Real Math::_real_inf = std::numeric_limits<Real>::infinity();
     const Real Math::epsilon_default = 1e-6f;

     const Real Angle::DEGTORAD = Math::PI / 180.0f;
     const Real Angle::RADTODEG = 180.0f / Math::PI;

    namespace Math
    {
        bool Equals(const Real& a, const Real& b)
        {
            return a == b;
        }

        bool AreDifferent(const Real& a, const Real& b)
        {
            return a != b;
        }

        bool AreDifferent3(const Real& a, const Real& b, const Real& c)
        {
            return a != b
                && a != c
                && b != c;
        }

        bool EqualsAbs(const Real& a, const Real& b, Real epsilon)
        {
            return (a + epsilon >= b) && (a - epsilon <= b);
        }

        bool AreDifferentAbs(const Real& a, const Real& b, Real epsilon)
        {
            return !(EqualsAbs(a, b, epsilon));
        }

        bool AreDifferentAbs3(const Real& a, const Real& b, const Real& c, Real epsilon)
        {
            return !(EqualsAbs(a, b, epsilon))
                && !(EqualsAbs(a, c, epsilon))
                && !(EqualsAbs(b, c, epsilon));
        }

        bool IsInRange(const Real& a, const Real& min, const Real& max)
        {
            return a >= min
                && a <= max;
        }

        bool IsInRangeAbs(const Real& a, const Real& min, const Real& max, Real epsilon)
        {
            return ((a + epsilon) >= min)
                && ((a - epsilon) <= max);
        }

        void Clamp(Real& a, const Real& min, const Real& max)
        {
            if(a < min) a = min;
            else if (a > max) a = max;
        }

        void ClampAbs(Real& a, const Real& min, const Real& max, Real epsilon)
        {
            if((a + epsilon) < min) a = min;
            if((a - epsilon) > max) a = max;
        }

        Real Abs(const Real& a)
        {
            if(a > 0.f) return a;
            else return -a;
        }

        Real Min(const Real& a, const Real& b)
        {
            if(a < b) return a;
            else return b;
        }

        Real Min3(const Real& a, const Real& b, const Real& c)
        {
            return Min(Min(a, b), c);
        }

        Real Max(const Real& a, const Real& b)
        {
            if(a > b) return a;
            else return b;
        }

        Real Max3(const Real& a, const Real& b, const Real& c)
        {
            return Max(Max(a, b), c);
        }

        Real Sqrt(const Real& a)
        {
            return sqrt(a);
        }

        Real Ceil(const Real& x)
        {
            return ceil(x);
        }

        Real Floor(const Real& x)
        {
            return floor(x);
        }

        void Modf(const Real& x, Real& frac, Real& intPart)
        {
            Real __i, __f;

#ifdef _USE_DOUBLEREAL_
            __f = modf(x, &__i);
#else
            __f = modff(x, &__i);
#endif // _USE_DOUBLEREAL_

            frac = __f;
            intPart = __i;
        }

        Real Hypotenuse(const Real& x, const Real& y)
        {
            return hypot(x, y);
        }

        bool IsFinite(Real r)
        {
#ifdef _USE_DOUBLEREAL_
            return IsFinite((double)r);
#else
            return IsFinite((float)r);
#endif // _USE_DOUBLEREAL_
        }

        bool IsNan(Real r)
        {
            return sizeof(Real) == sizeof(float) ?
                IsNan((float)r) :
                IsNan((double)r);
        }

        bool IsInf(Real r)
        {
            return sizeof(Real) == sizeof(float) ?
                IsInf((float)r) :
                IsInf((double)r);
        }
    }

    namespace Angle
    {
        Radian toRadian(const Degree& a)
        {
            return Angle::DEGTORAD * a;
        }

        Degree toDegree(const Radian& a)
        {
            return Angle::RADTODEG * a;
        }

        Radian MinAngle(const Radian& a)
        {
            return fmod(a, 2 * Math::PI);
        }

        Real Cos(const Radian& a)
        {
            return (Real) cos(a);
        }

        Real Sin(const Radian& a)
        {
            return (Real) sin(a);
        }

        Real Tan(const Radian& a)
        {
            return (Real) tan(a);
        }

        Radian ACos(const Real& a)
        {
            return (Radian) acos(a);
        }

        Radian ACosh(const Real& a)
        {
            return (Radian) acosh(a);
        }

        Radian ASin(const Real& a)
        {
            return (Radian) asin(a);
        }

        Radian ASinh(const Real& a)
        {
            return (Radian) asinh(a);
        }

        Radian ATan(const Real& a)
        {
            return (Radian) atan(a);
        }

        Radian ATanh(const Real& a)
        {
            return (Radian) atanh(a);
        }
    }

    double ACos(double v)
    {
        return acos(v);
    }

    double ASin(double v)
    {
        return asin(v);
    }

    double ATan(double v)
    {
        return atan(v);
    }

    double ATan2(double v, double v2)
    {
        return atan2(v, v2);
    }

    unsigned char colorvaluefromfloat(float v)
    {
        Numeric::Clamp(v, 0.0f, 1.0f);
        return (unsigned char) proportionnal(v, 1.0f, 255.0f);
    }

    float floatfromcolorvalue(unsigned char c)
    {
        return proportionnal((float) c, 255.0f, 1.0f);
    }
}
