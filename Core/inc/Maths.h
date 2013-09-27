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
        template<typename T>
        bool equalErr(T a, T b, T epsilon = 0)
        {
            return (a + epsilon >= b) && (a - epsilon <= b);
        }

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

        template<typename T>
        bool are_different(T a, T b, T c, T epsilon = 0)
        {
            return (!equalErr<T>(a, b, epsilon) &&
                    !equalErr<T>(a, c, epsilon) &&
                    !equalErr<T>(b, c, epsilon));
        }

        template<typename T>
        inline bool is_in_range(T a, T _min, T _max)
        {
            return a >= _min && a <= _max;
        }
    }

    Real Abs(Real a)
    {
        return abs_(a);
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
    template<> bool IsFinite<Real>(Real r) { return sizeof(Real) == sizeof(float) ? IsFinite<float>((float)r) : IsFinite<double>((double)r); }

    /// Returns true if the given value is a not-a-number.
    bool IsNan(float f) { return (ReinterpretAsU32(f) << 1) > 0xFF000000u; }
    bool IsNan(double d) { return (ReinterpretAsU64(d) << 1) > 0xFFE0000000000000ULL; }
    bool IsNan(long double value) { return IsNan((double)value); }
    bool IsNan(Real r) { return sizeof(Real) == sizeof(float) ? IsNan((float)r) : IsNan((double)r); }

    /// Returns true if the given value is +inf or -inf.
    bool IsInf(float f) { return (ReinterpretAsU32(f) << 1) == 0xFF000000u; }
    bool IsInf(double d) { return (ReinterpretAsU64(d) << 1) == 0xFFE0000000000000ULL; }
    bool IsInf(long double value) { return IsInf((double)value); }
    bool IsInf(Real r) { return sizeof(Real) == sizeof(float) ? IsInf((float)r) : IsInf((double)r); }

// Macros defining some inline utilities
// See MathGeoLib, MathFunc.h
//
/// Computes the dot product of two 2D vectors, the elements are accessed using array notation.
/// @param v1 A vector of type Vector2, or a C array of two elements.
/// @param v2 A vector of type Vector2, or a C array of two elements.
/// @see DOT3(), DOT4().
#define DOT2(v1, v2) ((v1)[0] * (v2)[0] + (v1)[1] * (v2)[1])

/// Computes the dot product of two 3D vectors, the elements are accessed using array notation.
/// @param v1 A vector of type Vector3, or a C array of three elements.
/// @param v2 A vector of type Vector3, or a C array of three elements.
/// @see DOT2(), DOT4(), ABSDOT3(), DOT3_xyz(), DOT3STRIDED().
#define DOT3(v1, v2) ((v1)[0] * (v2)[0] + (v1)[1] * (v2)[1] + (v1)[2] * (v2)[2])

/// Computes the dot product of two 3D vectors, but takes the absolute value of each element before summation.
/// @param v1 A vector of type Vector3, or a C array of three elements.
/// @param v2 A vector of type Vector3, or a C array of three elements.
/// @see DOT3(), DOT3_xyz(), DOT3STRIDED().
#define ABSDOT3(v1, v2) (Abs((v1)[0] * (v2)[0]) + Abs((v1)[1] * (v2)[1]) + Abs((v1)[2] * (v2)[2]))

/// Computes the dot product of a Vector3 and another vector given by three floats.
/// @param v1 A vector of type Vector3, or a C array of three elements.
/// @param x The x component of a second vector.
/// @param y The y component of a second vector.
/// @param z The z component of a second vector.
/// @see DOT3(), ABSDOT3(), DOT3STRIDED().
#define DOT3_xyz(v1, x, y, z) ((v1)[0] * (x) + (v1)[1] * (y) + (v1)[2] * (z))

/// Computes the dot product of two 3D vectors, but with the elements of the second vector being scattered noncontiguous in memory.
/// @param v1 The first vector in the dot product. This can either be a C array or a Vector3.
/// @param v2 The second vector in the dot product. As opposed to the DOT3() macro, which accesses the elements of this vector
///	 as v2[0], v2[1], v2[2], this function accesses the elements as v2[0], v2[stride], v2[2*stride].
/// @param stride The distance between between the subsequent vector elements in the array v2.
/// @see DOT3(), ABSDOT3(), DOT3_xyz(), DOT4STRIDED().
#define DOT3STRIDED(v1, v2, stride) ((v1)[0] * (v2)[0] + (v1)[1] * (v2)[stride] + (v1)[2] * (v2)[2*stride])

/// Computes the dot product of two 4D vectors, the elements are accessed using array notation.
/// @param v1 A vector of type Vector4, or a C array of four elements.
/// @param v2 A vector of type Vector4, or a C array of four elements.
/// @see DOT2(), DOT3(), DOT4STRIDED(), DOT4POS(), DOT4POS_xyz(), DOT4DIR(), DOT4DIR_xyz().
#define DOT4(v1, v2) ((v1)[0] * (v2)[0] + (v1)[1] * (v2)[1] + (v1)[2] * (v2)[2] + (v1)[3] * (v2)[3])

/// Computes the dot product of two 4D vectors, but with the elements of the second vector being scattered noncontiguous in memory.
/// @param v1 The first vector in the dot product. This can either be a C array or a Vector4.
/// @param v2 The second vector in the dot product. As opposed to the DOT4() macro, which accesses the elements of this vector
///	 as v2[0], v2[1], v2[2], v2[3], this function accesses the elements as v2[0], v2[stride], v2[2*stride], v2[3*stride].
/// @param stride The distance between between the subsequent vector elements in the array v2.
/// @see DOT4(), DOT4POS(), DOT4POS_xyz(), DOT4DIR(), DOT4DIR_xyz().
#define DOT4STRIDED(v1, v2, stride) ((v1)[0] * (v2)[0] + (v1)[1] * (v2)[stride] + (v1)[2] * (v2)[2*stride] + (v1)[3] * (v2)[3*stride])

/// Computes the dot product of a 4D vector and a 3D position vector (w == 1).
/// @param vec4D The 4D vector in the dot product, or a C array of four elements.
/// @param vecPos The 3D vector in the dot product. This vector is expanded to a 4D vector by setting w == 1.
/// @see DOT4(), DOT4STRIDED(), DOT4POS_xyz(), DOT4DIR(), DOT4DIR_xyz().
#define DOT4POS(vec4D, vecPos) ((vec4D)[0] * (vecPos)[0] + (vec4D)[1] * (vecPos)[1] + (vec4D)[2] * (vecPos)[2] + (vec4D)[3])

/// Computes the dot product of a 4D vector and a position vector (x,y,z,1).
/// @param vec4D The 4D vector in the dot product, or a C array of four elements.
/// @param x The x component of the second vector.
/// @param y The y component of the second vector.
/// @param z The z component of the second vector.
/// @see DOT4(), DOT4STRIDED(), DOT4POS(), DOT4DIR(), DOT4DIR_xyz().
#define DOT4POS_xyz(vec4D, x, y, z) ((vec4D)[0] * (x) + (vec4D)[1] * (y) + (vec4D)[2] * (z) + (vec4D)[3])

/// Computes the dot product of a 4D vector and a direction vector (x,y,z,0).
/// @note This function is only provided for convenience, since this is identical to DOT3.
/// @see DOT3(), DOT4(), DOT4STRIDED(), DOT4POS(), DOT4POS_xyz().
#define DOT4DIR(vec4D, vecDir) DOT3(vec4D, vecDir)

/// Computes the dot product of a 4D vector and a direction vector (x,y,z,0).
/// @note This function is only provided for convenience, since this is identical to DOT3_xyz.
/// @see DOT3_xyz(), DOT4(), DOT4STRIDED(), DOT4POS(), DOT4POS_xyz(), DOT4DIR().
#define DOT4DIR_xyz(vec4D, x, y, z) DOT3_xyz(vec4D, x, y, z)

}

#endif
