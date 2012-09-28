/** @file Color.h
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 23/09/2012
 *
 *  @addtogroup Global
 *  @addtogroup System
 *
 *  This file defines the Color class.
 *
**/
#ifndef APROCOLOR_H
#define APROCOLOR_H

#include "Platform.h"
#include "Console.h"

namespace APro
{
    class APRO_DLL Color
    {
    public:

        class Format
        {
        public:
            enum _
            {
                RGBA,
                ARGB,
                ABGR
            };
        };

        class Component
        {
        public:
            enum _
            {
                Red,
                Green,
                Blue,
                Alpha
            };
        };

    public:

        Color();
        explicit Color(unsigned long int c, Format::_ f = Format::RGBA);
        Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255);
        Color(const Color& other);

        ~Color();

        void set(unsigned long int c, Format::_ f = Format::RGBA);
        void set(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255);
        void set(Component::_ component, unsigned char c);
        void set(const Color& other);

        unsigned char get(Component::_ c) const;
        float lightness() const;
        float luminance() const;
        float average() const;

        void format(unsigned long int & ret, Format::_ f) const;

        Color& darker();
        Color& lighter();

        bool operator == (const Color& other) const;
        bool operator !=(const Color& other) const;

        Color& operator = (const Color& other);
        Color& operator += (const Color& other);
        Color& operator -= (const Color& other);

        Color operator + (const Color& other) const;
        Color operator - (const Color& other) const;

        operator unsigned char*();
        operator const unsigned char*() const;

        inline friend Console& operator << (Console& c, const Color& v)
        {
            c << "Color( " << (int) v.get(Component::Red) << ", "
                           << (int) v.get(Component::Green) << ", "
                           << (int) v.get(Component::Blue) << ", "
                           << (int) v.get(Component::Alpha) << " )";
            return c;
        }

    private:
        unsigned long int color;
    };
}

#endif
