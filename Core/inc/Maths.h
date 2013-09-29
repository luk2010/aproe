////////////////////////////////////////////////////////////
/** @file Maths.h
 *  @ingroup Maths
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 26/09/2012
 *
 *  Defines the Maths basics functions.
 *
**/
////////////////////////////////////////////////////////////
#ifndef APROMATHS_H
#define APROMATHS_H

#include "Platform.h"

namespace APro
{
    /// @ingroup Maths
    /// @brief Performs basics comparaison and functions to every numeric types.
    ///
    /// You might uses these functions on other types than Real.
    namespace Numeric
    {
        ////////////////////////////////////////////////////////////
        /** @brief Tell if two Numerics are equals.
        **/
        ////////////////////////////////////////////////////////////
        template<typename N>
        bool Equals(const N& a, const N& b)
        {
            return a == b;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Tell if three Numerics are equals.
        **/
        ////////////////////////////////////////////////////////////
        template<typename N>
        bool Equals3(const N& a, const N& b, const N& c)
        {
            return a == b
                && a == c;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Tell if two Numerics are differents.
        **/
        ////////////////////////////////////////////////////////////
        template<typename N>
        bool AreDifferent(const N& a, const N& b)
        {
            return !(Equals(a, b));
        }

        ////////////////////////////////////////////////////////////
        /** @brief Tell if three Numerics are differents.
        **/
        ////////////////////////////////////////////////////////////
        template<typename N>
        bool AreDifferent3(const N& a, const N& b, const N& c)
        {
            return AreDifferent(a, b)
                && AreDifferent(a, c)
                && AreDifferent(b, c);
        }

        ////////////////////////////////////////////////////////////
        /** @brief Tell if a Numeric is in given [min, max] range.
        **/
        ////////////////////////////////////////////////////////////
        template<typename N>
        bool IsInRange(const N& a, const N& min, const N& max)
        {
            return a >= min
                && a <= max;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Clamp given real to given range.
        **/
        ////////////////////////////////////////////////////////////
        template<typename N>
        void Clamp(N& a, const N& min, const N& max)
        {
            if(a < min) a = min;
            else if(a > max) a = max;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Return minimum value of given numerics.
        **/
        ////////////////////////////////////////////////////////////
        template<typename N>
        N Min(const N& a, const N& b)
        {
            if(a < b) return a;
            else return b;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Return minimum value of given numerics.
        **/
        ////////////////////////////////////////////////////////////
        template<typename N>
        N Min3(const N& a, const N& b, const N& c)
        {
            return Min(Min(a, b), c);
        }

        ////////////////////////////////////////////////////////////
        /** @brief Return maximum value of given numerics.
        **/
        ////////////////////////////////////////////////////////////
        template<typename N>
        N Max(const N& a, const N& b)
        {
            if(a > b) return a;
            else return b;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Return maximum value of given numerics.
        **/
        ////////////////////////////////////////////////////////////
        template<typename N>
        N Max3(const N& a, const N& b, const N& c)
        {
            return Max(Max(a, b), c);
        }
    }

    /// @ingroup Maths
    /// @brief A namespace that groups every Math-specific functions and constants.
    ///
    /// Use these functions for Real type.
    namespace Math
    {
        static const Real PI;///< PI constant in Real terms.

        static const Real _real_nan;///< Not a Number constant.
        static const Real _real_inf;///< Infinite constant.

        static const Real epsilon_default;///< Basic epsilon for compare functions.
    }

    namespace Math
    {
        ////////////////////////////////////////////////////////////
        /** @brief Tell if two Reals are numerically equal, and with
         *  no errors.
        **/
        ////////////////////////////////////////////////////////////
        bool Equals(const Real& a, const Real& b);

        ////////////////////////////////////////////////////////////
        /** @brief Tell if two Reals are numerically different, and with
         *  no errors.
        **/
        ////////////////////////////////////////////////////////////
        bool AreDifferent(const Real& a, const Real& b);

        ////////////////////////////////////////////////////////////
        /** @brief Tell if three Reals are numerically different, and with
         *  no errors.
        **/
        ////////////////////////////////////////////////////////////
        bool AreDifferent3(const Real& a, const Real& b, const Real& c);

        ////////////////////////////////////////////////////////////
        /** @brief Tell if two Reals are numerically equal, compared
         *  to the given epsilon.
        **/
        ////////////////////////////////////////////////////////////
        bool EqualsAbs(const Real& a, const Real& b, Real epsilon = Math::epsilon_default);

        ////////////////////////////////////////////////////////////
        /** @brief Tell if two Reals are numerically different, compared
         *  to the given epsilon.
        **/
        ////////////////////////////////////////////////////////////
        bool AreDifferentAbs(const Real& a, const Real& b, Real epsilon = Math::epsilon_default);

        ////////////////////////////////////////////////////////////
        /** @brief Tell if three Reals are numerically different, compared
         *  to the given epsilon.
        **/
        ////////////////////////////////////////////////////////////
        bool AreDifferentAbs3(const Real& a, const Real& b, const Real& c, Real epsilon = Math::epsilon_default);

        ////////////////////////////////////////////////////////////
        /** @brief Tell if a Real is in given [min, max] range, without
         *  errors.
        **/
        ////////////////////////////////////////////////////////////
        bool IsInRange(const Real& a, const Real& min, const Real& max);

        ////////////////////////////////////////////////////////////
        /** @brief Tell if a Real is in given [min, max] range, compared
         *  to given epsilon.
        **/
        ////////////////////////////////////////////////////////////
        bool IsInRangeAbs(const Real& a, const Real& min, const Real& max, Real epsilon = Math::epsilon_default);

        ////////////////////////////////////////////////////////////
        /** @brief Clamp given real to given range, without errors.
        **/
        ////////////////////////////////////////////////////////////
        void Clamp(Real& a, const Real& min, const Real& max);

        ////////////////////////////////////////////////////////////
        /** @brief Clamp given real to given range, compared to given
         *  epsilon.
         *
         *  @note If Clamp detect not-in-range value, Real is clamped
         *  exactly to minimum or maximum, not to the epsiloned one.
        **/
        ////////////////////////////////////////////////////////////
        void ClampAbs(Real& a, const Real& min, const Real& max, Real epsilon = Math::epsilon_default);

        ////////////////////////////////////////////////////////////
        /** @brief Return absolute value of given real.
        **/
        ////////////////////////////////////////////////////////////
        Real Abs(const Real& a);

        ////////////////////////////////////////////////////////////
        /** @brief Return minimum value of given reals.
        **/
        ////////////////////////////////////////////////////////////
        Real Min(const Real& a, const Real& b);

        ////////////////////////////////////////////////////////////
        /** @brief Return minimum value of given reals.
        **/
        ////////////////////////////////////////////////////////////
        Real Min3(const Real& a, const Real& b, const Real& c);

        ////////////////////////////////////////////////////////////
        /** @brief Return maximum value of given reals.
        **/
        ////////////////////////////////////////////////////////////
        Real Max(const Real& a, const Real& b);

        ////////////////////////////////////////////////////////////
        /** @brief Return maximum value of given reals.
        **/
        ////////////////////////////////////////////////////////////
        Real Max3(const Real& a, const Real& b, const Real& c);

        ////////////////////////////////////////////////////////////
        /** @brief Return square root of given Real.
        **/
        ////////////////////////////////////////////////////////////
        Real Sqrt(const Real& a);

        ////////////////////////////////////////////////////////////
        /** @brief Rounds x upward, returning the smallest integral
         *  value that is not less than x.
        **/
        ////////////////////////////////////////////////////////////
        Real Ceil(const Real& x);

        ////////////////////////////////////////////////////////////
        /** @brief Rounds x downward, returning the largest integral
         *  value that is not greater than x.
        **/
        ////////////////////////////////////////////////////////////
        Real Floor(const Real& x);

        ////////////////////////////////////////////////////////////
        /** @brief Breaks x into Fractionnal and Integral parts.
         *
         *  @param x : Real to breaks.
         *  @param frac [out] : Fractionnal part of x.
         *  @param intPart [out] : Integral part of x.
        **/
        ////////////////////////////////////////////////////////////
        void Modf(const Real& x, Real& frac, Real& intPart);

        ////////////////////////////////////////////////////////////
        /** @brief Returns the hypotenuse of a right-angled triangle
         *  whose legs are x and y.
        **/
        ////////////////////////////////////////////////////////////
        Real Hypotenuse(const Real& x, const Real& y);
    }

    /// @ingroup Maths
    /// @brief Regroups every Angle related functions.
    namespace Angle
    {
        static const angle_t DEGTORAD;///< Constant to convert degree to radian.
        static const angle_t RADTODEG;///< Constant to convert radian to degree.

        ////////////////////////////////////////////////////////////
        /** @brief Return radian value of given degree angle.
        **/
        ////////////////////////////////////////////////////////////
        Radian toRadian(const Degree& a);

        ////////////////////////////////////////////////////////////
        /** @brief Return degree value of given radian angle.
        **/
        ////////////////////////////////////////////////////////////
        Degree toDegree(const Radian& a);

        ////////////////////////////////////////////////////////////
        /** @brief Return the minimum Radian angle value from given
         *  one.
         *
         *  Exemple : if your radian angle make 3,5 turns, i.e. 9 PI,
         *  it will return % 2PI so PI, 0.5 turns.
        **/
        ////////////////////////////////////////////////////////////
        Radian MinAngle(const Radian& a);

        ////////////////////////////////////////////////////////////
        /** @brief Return the cosinus of given Radian angle.
        **/
        ////////////////////////////////////////////////////////////
        Real Cos(const Radian& a);

        ////////////////////////////////////////////////////////////
        /** @brief Return the sinus of given Radian angle.
        **/
        ////////////////////////////////////////////////////////////
        Real Sin(const Radian& a);

        ////////////////////////////////////////////////////////////
        /** @brief Return the tangent of given Radian angle.
        **/
        ////////////////////////////////////////////////////////////
        Real Tan(const Radian& a);

        ////////////////////////////////////////////////////////////
        /** @brief Return the arc cosinus of given Real, in Radian.
        **/
        ////////////////////////////////////////////////////////////
        Radian ACos(const Real& a);

        ////////////////////////////////////////////////////////////
        /** @brief Return the arc non-negative hyperbolic cosinus of
         *  given Real, in Radian.
        **/
        ////////////////////////////////////////////////////////////
        Radian ACosh(const Real& a);

        ////////////////////////////////////////////////////////////
        /** @brief Return the arc sinus of given Real, in Radian.
        **/
        ////////////////////////////////////////////////////////////
        Radian ASin(const Real& a);

        ////////////////////////////////////////////////////////////
        /** @brief Return the arc non-negative hyperbolic sinus of
         *  given Real, in Radian.
        **/
        ////////////////////////////////////////////////////////////
        Radian ASinh(const Real& a);

        ////////////////////////////////////////////////////////////
        /** @brief Return the arc tangent of given Real, in Radian.
        **/
        ////////////////////////////////////////////////////////////
        Radian ATan(const Real& a);

        ////////////////////////////////////////////////////////////
        /** @brief Return the arc non-negative hyperbolic tangent of
         *  given Real, in Radian.
        **/
        ////////////////////////////////////////////////////////////
        Radian ATanh(const Real& a);

        ////////////////////////////////////////////////////////////
        /** @brief Return the arc tangent of two Reals, in Radian.
        **/
        ////////////////////////////////////////////////////////////
        Radian ATan2(const Real& x, const Real& y);
    }

    /// @ingroup Maths
    /// @brief Use these functions to perform Bits calculs.
    namespace Bits
    {
        ////////////////////////////////////////////////////////////
        /** @brief Return the given bit of the given data.
         *  @param data : Data to get.
         *  @param wich : Number of the bit to get.
         *  @note You should use this function on types that have
         *  bits-to-bits operators.
        **/
        ////////////////////////////////////////////////////////////
        template<typename T>
        u8 get(T data, u32 wich)
        {
            u32 bitcount = sizeof(data) * 8;
            u32 revbit = bitcount - wich;
            return (u8) (data << revbit >> (bitcount - 1));
        }

        ////////////////////////////////////////////////////////////
        /** @brief Return the high bit of the given data.
         *  @param data : Data to get.
         *  @note You should use this function on types that have
         *  bits-to-bits operators.
        **/
        ////////////////////////////////////////////////////////////
        template<typename T>
        u8 getHigh(T data)
        {
            return Bits::get(data, sizeof(data) * 8);
        }

        ////////////////////////////////////////////////////////////
        /** @brief Return the low bit of the given data.
         *  @param data : Data to get.
         *  @note You should use this function on types that have
         *  bits-to-bits operators.
        **/
        ////////////////////////////////////////////////////////////
        template<typename T>
        u8 getLow(T data)
        {
            return Bits::get(data, 0);
        }
    }

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
#define ABSDOT3(v1, v2) (Math::Abs((v1)[0] * (v2)[0]) + Abs((v1)[1] * (v2)[1]) + Abs((v1)[2] * (v2)[2]))

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
