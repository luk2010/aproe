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
}
