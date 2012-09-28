/** @file ColorConverter.h
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 23/09/2012
 *
 *  @addtogroup Global
 *  @addtogroup System
 *
 *  This file defines the ColorConverter functions.
 *
**/
#ifndef APROCOLORCONVERTER_H
#define APROCOLORCONVERTER_H
/*
#include "Platform.h"

namespace APro
{
    class ColorFormat
    {
    public:
        enum _
        {
            RGBA,
            ARGB,
            BGRA,
            ABGR,
            RGB,
            BGR,
            MONO,

        };
    };

    template<typename From, typename To>
    bool convertColor(char*& color)
    {
        return false;
    }

    template<>
    bool convertColor<Color::Format::RGBA, Color::Format::ARGB>(char*& color)
    {
        char tmpR, tmpG, tmpB, tmpA;
        tmpR = color[0];
        tmpG = color[1];
        tmpB = color[2];
        tmpA = color[3];

        color[0] = tmpA;
        color[1] = tmpR;
        color[2] = tmpG;
        color[3] = tmpB;

        return true;
    }

    template<>
    bool convertColor<Color::Format::RGBA, Color::Format::BGRA>(char*& color)
    {
        char tmp1, tmp3;
        tmp1 = color[0];
        tmp3 = color[2];

        color[0] = tmp3;
        color[2] = tmp1;

        return true;
    }

    template<>
    bool convertColor<Color::Format::RGBA, Color::Format::ABGR>(char*& color)
    {
        char tmpR, tmpG, tmpB, tmpA;
        tmpR = color[0];
        tmpG = color[1];
        tmpB = color[2];
        tmpA = color[3];

        color[0] = tmpA;
        color[1] = tmpB;
        color[2] = tmpG;
        color[3] = tmpR;

        return true;
    }

    template<>
    bool convertColor<Color::Format::RGBA, Color::Format::RGB>(char*& color)
    {
        return true;
    }

    template<>
    bool convertColor<Color::Format::RGBA, Color::Format::BGR>(char*& color)
    {
        char tmpR, tmpG, tmpB, tmpA;
        tmpR = color[0];
        tmpG = color[1];
        tmpB = color[2];

        color[0] = tmpB;
        color[1] = tmpG;
        color[2] = tmpR;

        return true;
    }
}
*/
#endif
