/** @file Maths.cpp
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 27/09/2012
 *
 *  @addtogroup Global
 *  @addtogroup System
 *
 *  This file defines the Maths functions.
 *
**/
#include "Maths.h"
#include <math.h>

namespace APro
{
    int Sqrt (int v)
    {
        return static_cast <int> (sqrt(static_cast<double>(v)));
    }

    float Sqrt (float v)
    {
        return static_cast <float> (sqrt(static_cast<double>(v)));
    }

    double Sqrt (double v)
    {
        return sqrt(v);
    }

    double Cos(double v)
    {
        return cos(v);
    }

    double Sin(double v)
    {
        return sin(v);
    }

    double Tan(double v)
    {
        return tan(v);
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

    float min_angle_32(float a)
    {
        float c = a;
        if(c < 0)
        {
            while((c+=2*Math::PI_32) < -2*Math::PI_32);
            return c;
        }
        else if(c > 0)
        {
            while((c-=2*Math::PI_32) > 2*Math::PI_32);
            return c;
        }
        else
            return c;
    }

    double min_angle_64(double a)
    {
        double c = a;
        if(c < 0)
        {
            while((c+=2*Math::PI_64) < -2*Math::PI_64);
            return c;
        }
        else if(c > 0)
        {
            while((c-=2*Math::PI_64) > 2*Math::PI_64);
            return c;
        }
        else
            return c;
    }

    unsigned char colorvaluefromfloat(float v)
    {
        v = Clamp(v, 0.0f, 1.0f);
        return (unsigned char) proportionnal(v, 1.0f, 255.0f);
    }

    float floatfromcolorvalue(unsigned char c)
    {
        return proportionnal((float) c, 255.0f, 1.0f);
    }
}
