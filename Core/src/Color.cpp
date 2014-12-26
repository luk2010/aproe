////////////////////////////////////////////////////////////
/** @file Color.h
 *  @ingroup Utils
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 24/09/2012 - 15/12/2014
 *
 *  @brief
 *  This file implements the Color class.
 *
 *  @copyright
 *  Atlanti's Project Engine
 *  Copyright (C) 2012 - 2014  Atlanti's Corp
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
**/
////////////////////////////////////////////////////////////
#include "Color.h"
#include "Maths.h"

namespace APro
{
    Color Color::Black  ((uint8_t) 0,   0,   0,   255);
    Color Color::White  ((uint8_t) 255, 255, 255, 255);
    Color Color::Red    ((uint8_t) 255, 0,   0,   255);
    Color Color::Green  ((uint8_t) 0,   255, 0,   255);
    Color Color::Blue   ((uint8_t) 0,   0,   255, 255);

    Color Color::rgb(uint8_t r, uint8_t g, uint8_t b)
    {
        return Color(r,g,b,255);
    }

    Color Color::rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    {
        return Color(r,g,b,a);
    }

    Color::Color()
        : color(0)
    {

    }

    Color::Color(uint32_t c, Format f)
        : color(0)
    {
        set(c, f);
    }

    Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
        : color(0)
    {
        set(r, g, b, a);
    }

    Color::Color(Real r, Real g, Real b, Real a)
    {
        set(colorvaluefromfloat(r),
            colorvaluefromfloat(g),
            colorvaluefromfloat(b),
            colorvaluefromfloat(a));
    }

    Color::Color(const Color& other)
        : color(other.color)
    {

    }
    
    Color::Color(Color&& rhs)
    : color (0)
    {
        color = rhs.color;
        rhs.color = 0;
    }

    Color::~Color()
    {

    }

    void Color::set(uint32_t c, Format f)
    {
        if(f == Format::RGBA)
        {
            color = c;
        }
        else if(f == Format::ARGB)
        {
            uint8_t* c_ = (uint8_t*) &c;
            set(c_[1], c_[2], c_[3], c_[0]);
        }
        else if(f == Format::ABGR)
        {
            uint8_t* c_ = (uint8_t*) &c;
            set(c_[3], c_[2], c_[1], c_[0]);
        }
        else
        {
            aprothrow_ce("Wrong Color enum given to function set !");
        }
    }

    void Color::set(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    {
        uint8_t* c = (uint8_t*) &color;
        c[0] = r;
        c[1] = g;
        c[2] = b;
        c[3] = a;
    }

    void Color::set(Real r, Real g, Real b, Real a)
    {
        set(colorvaluefromfloat(r),
            colorvaluefromfloat(g),
            colorvaluefromfloat(b),
            colorvaluefromfloat(a));
    }

    void Color::set(Component component, uint8_t c)
    {
        uint8_t* c_ = (uint8_t*) &color;

        if(component == Component::Red)
        {
            c_[0] = c;
        }
        else if(component == Component::Green)
        {
            c_[1] = c;
        }
        else if(component == Component::Blue)
        {
            c_[2] = c;
        }
        else
        {
            c_[3] = c;
        }
    }

    void Color::set(const Color& other)
    {
        color = other.color;
    }

    uint8_t Color::get(Component c) const
    {
        if(c == Component::Red)
        {
            return ((const uint8_t*) &color) [0];
        }
        else if(c == Component::Green)
        {
            return ((const uint8_t*) &color) [1];
        }
        else if(c == Component::Blue)
        {
            return ((const uint8_t*) &color) [2];
        }
        else
        {
            return ((const uint8_t*) &color) [3];
        }
    }

    Real Color::lightness() const
    {
        const uint8_t* c = (const uint8_t*) &color;
        return 0.5f + (Numeric::Max3(c[0], c[1], c[2]) + Numeric::Min3(c[0], c[1], c[2]));
    }

    Real Color::luminance() const
    {
        const uint8_t* c = (const uint8_t*) &color;
        return 0.3f * (Real) c[0] + 0.59f * (Real) c[1] + 0.11f * (Real) c[2];
    }

    Real Color::average() const
    {
        const uint8_t* c = (const uint8_t*) &color;
        return ((uint32_t) c[0] + (uint32_t) c[1] + (uint32_t) c[2])/3;
    }

    void Color::format(uint32_t & ret, Format f) const
    {
        if(f == Format::RGBA)
        {
            ret = color;
            return;
        }
        else
        {
            const uint8_t* c = (const uint8_t*) &color;
            uint8_t* cret    = (uint8_t*)       &ret;

            if(f == Format::ARGB)
            {
                cret[0] = c[3];
                cret[1] = c[0];
                cret[2] = c[1];
                cret[3] = c[2];
            }
            else
            {
                cret[0] = c[3];
                cret[1] = c[2];
                cret[2] = c[1];
                cret[3] = c[0];
            }

            return;
        }
    }

    Color& Color::darker()
    {
        uint8_t* c = (uint8_t*) &color;

        c[0] -= 10;
        c[1] -= 10;
        c[2] -= 10;

        return *this;
    }

    Color& Color::lighter()
    {
        uint8_t* c = (uint8_t*) &color;

        c[0] += 10;
        c[1] += 10;
        c[2] += 10;

        return *this;
    }

    bool Color::operator == (const Color& other) const
    {
        return other.color == color;
    }

    bool Color::operator != (const Color& other) const
    {
        return other.color != color;
    }

    Color& Color::operator += (const Color& other)
    {
        unsigned char* c = (unsigned char*) &color;
        const unsigned char* cadd = (const unsigned char*) &(other.color);

        c[0] += cadd[0];
        c[1] += cadd[1];
        c[2] += cadd[2];

        return *this;
    }

    Color& Color::operator -= (const Color& other)
    {
        unsigned char* c = (unsigned char*) &color;
        const unsigned char* cadd = (const unsigned char*) &(other.color);

        c[0] -= cadd[0];
        c[1] -= cadd[1];
        c[2] -= cadd[2];

        return *this;
    }

    Color Color::operator + (const Color& other) const
    {
        Color cret(other);
        return cret += *this;
    }

    Color Color::operator - (const Color& other) const
    {
        Color cret(other);
        return cret += *this;
    }

    
}
