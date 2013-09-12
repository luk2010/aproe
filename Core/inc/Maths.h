/** @file Maths.h
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 26/09/2012
 *
 *  @addtogroup Global
 *  @addtogroup System
 *
 *  This file defines the Maths functions.
 *
**/
#ifndef APROMATHS_H
#define APROMATHS_H

#include "Platform.h"

namespace APro
{
    namespace Math
    {
        const float PI_32 = 3.14159265359f;
        const double PI_64 = 3.1415926535897932384626433832795028841971693993751;

        const float DEGTORAD = PI_32/180.0f;
        const float RADTODEG = 180.0f/PI_32;
        const double DEGTORAD64 = PI_64/180.0;
        const double RADTODEG64 = 180.0/PI_64;

        static const _real_nan;
        static const _real_inf;
    }

    namespace Math
    {
        inline bool egal32(float a, float b, float error = 0.0f)
        {
            return (a + error >= b) && (a - error <= b);
        }

        inline bool egal64(double a, double b, double error = 0.0)
        {
            return (a + error >= b) && (a - error <= b);
        }

        bool equal_real(Real a, Real b, Real epsilon = 0.f)
        {
            return (a + epsilon >= b) && (a - epsilon <= b);
        }
    }



    inline float toRadian32(float deg)
    {
        return Math::DEGTORAD * deg;
    }

    inline double toRadian64(double deg)
    {
        return Math::DEGTORAD64 * deg;
    }

    inline float toDegree32(float rad)
    {
        return Math::RADTODEG * rad;
    }

    inline double toDegree64(double rad)
    {
        return Math::RADTODEG64 * rad;
    }

    template<typename T> T max_2(T value1, T value2)
    {
        return (value1 > value2) ? value1 : value2 ;
    }

    template<typename T> T max_3(T value1, T value2, T value3)
    {
        if(max_2(value1,value2) > max_2(value2,value3))
            return max_2(value1,value2);
        else if(max_2(value1,value2) == max_2(value2,value3))
            return max_2(value1,value2);
        else
            return max_2(value2,value3);
    }

    template<typename T> T min_2(T value1, T value2)
    {
        return (value1 > value2) ? value2 : value1;
    }

    template<typename T> T min_3(T value1, T value2, T value3)
    {
        if(min_2(value1,value2) < min_2(value2,value3))
            return max_2(value1,value2);
        else if(max_2(value1,value2) == max_2(value2,value3))
            return max_2(value1,value2);
        else
            return max_2(value2,value3);
    }

    template<typename T> T abs_(T v)
    {
        return v > 0 ? v : -v;
    }

    template<typename T> unsigned char getBit(T numericdata, int bitnumber)
    {
        int bitcount = sizeof(numericdata) * 8;
        int revbit = bitcount - bitnumber;

        return (unsigned char) (numericdata << revbit >> (bitcount - 1 ));
    }

    template<typename T> unsigned char getHighBit(T numericdata)
    {
        return getBit<T>(numericdata, sizeof(numericdata) * 8);
    }

    template<typename T> unsigned char getLowBit(T numericdata)
    {
        return getBit<T>(numericdata, 0);
    }

    APRO_DLL int    Sqrt (int v);
    APRO_DLL float  Sqrt (float v);
    APRO_DLL double Sqrt (double v);

    APRO_DLL double Cos(double v);
    APRO_DLL double Sin(double v);
    APRO_DLL double Tan(double v);

    APRO_DLL double ACos(double v);
    APRO_DLL double ASin(double v);
    APRO_DLL double ATan(double v);
    APRO_DLL double ATan2(double v, double v2);

    template <typename T> void swapNumeric(T& num1, T& num2)
    {
        static T tmp;
        tmp = num1; num1 = num2; num2 = tmp;
    }

    template <typename T> void swapNumeric_xor(T& num1, T& num2)
    {
        if(num1 != num2) {
            num1 ^= num2;
            num2 ^= num1;
            num1 ^= num2;
        }
    }

    template <typename T> T Clamp(const T& value, const T min, const T max)
    {
        return max_2(min_2(value, max), min);
    }

    APRO_DLL float min_angle_32(float a);
    APRO_DLL double min_angle_64(double a);

    unsigned char colorvaluefromfloat(float v);
    float         floatfromcolorvalue(unsigned char c);
    template <typename T> T proportionnal(const T& value, const T base, const T to)
    {
        return value * to / base;
    }

    template<typename Type, typename Compare>
    void quicksort(Type* array, size_t num, Compare cmpfunc)
    {
        custom_quicksort(array, 0, num - 1, cmpfunc);
    }

    template <typename Type, typename Compare>
    void custom_quicksort(Type* t_array, size_t beg, size_t end, Compare cmpfunc)
    {
        Type piv, tmp;
        int l, r, p;

        while(beg < end)
        {
            l = beg; p = beg + (end-beg)/2; r = end;
            piv = t_array[p];

            while(1)
            {
                while ( (l<=r) && (cmpfunc(t_array[l], piv) <= 0) ) l++;
                while ( (l<=r) && (cmpfunc(t_array[r], piv) > 0) ) r--;

                if(l>r) break;

                tmp = t_array[l]; t_array[l] = t_array[r]; t_array[r] = tmp;

                if(p == r) p = l;
                l++; r--;
            }

            t_array[p] = t_array[r]; t_array[r] = piv;
            r--;

            if((r-beg) < (end-l))
            {
                custom_quicksort(t_array, beg, r, cmpfunc);
                beg = l;
            }
            else
            {
                custom_quicksort(t_array, l, end, cmpfunc);
                end = r;
            }
        }
    }

    /// Returns true if the given value is not an inf or a nan.
    template<typename T> bool IsFinite(T /*value*/) { return true; }

    template<> bool IsFinite<float>(float f) { return (ReinterpretAsU32(f) << 1) < 0xFF000000u; }
    template<> bool IsFinite<double>(double d) { return (ReinterpretAsU64(d) << 1) < 0xFFE0000000000000ULL; }
    template<> bool IsFinite<long double>(long double value) { return IsFinite<double>((double)value); }

    /// Returns true if the given value is a not-a-number.
    bool IsNan(float f) { return (ReinterpretAsU32(f) << 1) > 0xFF000000u; }
    bool IsNan(double d) { return (ReinterpretAsU64(d) << 1) > 0xFFE0000000000000ULL; }
    bool IsNan(long double value) { return IsNan((double)value); }

    /// Returns true if the given value is +inf or -inf.
    bool IsInf(float f) { return (ReinterpretAsU32(f) << 1) == 0xFF000000u; }
    bool IsInf(double d) { return (ReinterpretAsU64(d) << 1) == 0xFFE0000000000000ULL; }
    bool IsInf(long double value) { return IsInf((double)value); }
}

#endif
