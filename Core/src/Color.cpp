/** @file Color.h
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 24/09/2012
 *
 *  @addtogroup Global
 *  @addtogroup System
 *
 *  This file defines the Color class.
 *
**/
#include "Color.h"
#include "Maths.h"

namespace APro
{
    Color Color::Black((unsigned char) 0,0,0,255);
    Color Color::White((unsigned char) 255,255,255,255);
    Color Color::Red((unsigned char) 255,0,0,255);
    Color Color::Green((unsigned char) 0,255,0,255);
    Color Color::Blue((unsigned char) 0,0,255,255);

    Color Color::rgb(unsigned char r, unsigned char g, unsigned char b)
    {
        return Color(r,g,b,255);
    }

    Color Color::rgba(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
    {
        return Color(r,g,b,a);
    }

    Color::Color()
        : color(0)
    {

    }

    Color::Color(unsigned long int c, Format::_ f)
        : color(0)
    {
        set(c, f);
    }

    Color::Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
        : color(0)
    {
        set(r, g, b, a);
    }

    Color::Color(float r, float g, float b, float a)
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

    Color::~Color()
    {

    }

    void Color::set(unsigned long int c, Format::_ f)
    {
        if(f == Format::RGBA)
        {
            color = c;
        }
        else if(f == Format::ARGB)
        {
            unsigned char* c_ = (unsigned char*) &c;
            set(c_[1], c_[2], c_[3], c_[0]);
        }
        else if(f == Format::ABGR)
        {
            unsigned char* c_ = (unsigned char*) &c;
            set(c_[3], c_[2], c_[1], c_[0]);
        }
        else
        {
#if APRO_EXCEPTION == APRO_ON
            APRO_THROW("WrongEnum", "Wrong Color enum given to function set !", "Color");
#endif
        }
    }

    void Color::set(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
    {
        unsigned char* c = (unsigned char*) &color;
        c[0] = r;
        c[1] = g;
        c[2] = b;
        c[3] = a;
    }

    void Color::set(float r, float g, float b, float a)
    {
        set(colorvaluefromfloat(r),
            colorvaluefromfloat(g),
            colorvaluefromfloat(b),
            colorvaluefromfloat(a));
    }

    void Color::set(Component::_ component, unsigned char c)
    {
        unsigned char* c_ = (unsigned char*) &color;

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

    unsigned char Color::get(Component::_ c) const
    {
        if(c == Component::Red)
        {
            return ((const unsigned char*) &color) [0];
        }
        else if(c == Component::Green)
        {
            return ((const unsigned char*) &color) [1];
        }
        else if(c == Component::Blue)
        {
            return ((const unsigned char*) &color) [2];
        }
        else
        {
            return ((const unsigned char*) &color) [3];
        }
    }

    float Color::lightness() const
    {
        const unsigned char* c = (const unsigned char*) &color;
        return 0.5f + (max_3(c[0], c[1], c[2]) + min_3(c[0], c[1], c[2]));
    }

    float Color::luminance() const
    {
        const unsigned char* c = (const unsigned char*) &color;
        return 0.3f * (float) c[0] + 0.59f * (float) c[1] + 0.11f * (float) c[2];
    }

    float Color::average() const
    {
        const unsigned char* c = (const unsigned char*) &color;
        return ((int) c[0] + (int) c[1] + (int) c[2])/3;
    }

    void Color::format(unsigned long int & ret, Format::_ f) const
    {
        if(f == Format::RGBA)
        {
            ret = color;
            return;
        }
        else
        {
            const unsigned char* c = (const unsigned char*) &color;
            unsigned char* cret = (unsigned char*) &ret;

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
        unsigned char* c = (unsigned char*) &color;

        c[0] -= 10;
        c[1] -= 10;
        c[2] -= 10;

        return *this;
    }

    Color& Color::lighter()
    {
        unsigned char* c = (unsigned char*) &color;

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

    Color& Color::operator = (const Color& other)
    {
        color = other.color;
        return *this;
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

    Color::operator const unsigned char* () const
    {
        return (const unsigned char*) &color;
    }

    Color::operator unsigned char* ()
    {
        return (unsigned char*) &color;
    }
}
