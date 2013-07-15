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
    //! @class Color
    /** @brief Represents a color as RGBA in 32 bits ( 8 + 8 + 8 + 8 ).
     *
     * This class help manipulating colors.
     *
     * @note Colors can be stored in a Array<Color> without any problems, so you should
     * use this storage system instead of List.
     *
     * @note Color size is 4. It is equivalent to int (32bits).
     *
     */
    class APRO_DLL Color
    {
    public:

        /** @brief Helper to describe most formats used. */
        class Format
        {
        public:
            enum _
            {
                RGBA, ///< Used by this Engine.
                ARGB, ///< Used by DirectX.
                ABGR  ///< Usd by OpenGL.
            };
        };

        /** @brief The four components of the color. */
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
        explicit Color(float r, float g, float b, float a = 1.0f);
        Color(const Color& other);

        ~Color();

        void set(unsigned long int c, Format::_ f = Format::RGBA);
        void set(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255);
        void set(float r, float g, float b, float a = 1.0f);
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

        static Color rgb(unsigned char r, unsigned char g, unsigned char b);
        static Color rgba(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

        static Color Black;
        static Color White;
        static Color Green;
        static Color Blue;
        static Color Red;

    private:
        unsigned long int color;
    };
}

#endif
