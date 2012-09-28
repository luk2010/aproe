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
    }

    inline bool egal32(float a, float b, float error = 0.0f)
    {
        return (a + error >= b) && (a - error <= b);
    }

    inline bool egal64(double a, double b, double error = 0.0)
    {
        return (a + error >= b) && (a - error <= b);
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
}

#endif
