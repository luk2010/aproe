////////////////////////////////////////////////////////////
/** @file Color.h
 *  @ingroup Utils
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 23/09/2012
 *
 *  Defines the Color class.
 *
**/
////////////////////////////////////////////////////////////
#ifndef APROCOLOR_H
#define APROCOLOR_H

#include "Platform.h"
#include "Console.h"

namespace APro
{
    ////////////////////////////////////////////////////////////
    /** @class Color
     *  @ingroup Utils
     *  @brief Represents a color as RGBA in 32 bits ( 8 + 8 + 8
     *  + 8 ).
     *
     *  You can manipulate colors and stock them by using this
     *  class. In this representation, Colors channels are Red, Green,
     *  Blue and Alpha and are from 0 to 255 as they are represented
     *  by a char (8 bits).
     *
     *  @note Color size is 4. It is equivalent to int (32bits).
    **/
    ////////////////////////////////////////////////////////////
    class APRO_DLL Color
    {
    public:

        ////////////////////////////////////////////////////////////
        /** @brief Helper to describe most formats used.
        **/
        ////////////////////////////////////////////////////////////
        class Format
        {
        public:
            enum _
            {
                RGBA, ///< Used by this Engine.
                ARGB, ///< Commonly used by DirectX.
                ABGR  ///< Commonly used by OpenGL.
            };
        };

        ////////////////////////////////////////////////////////////
        /** @brief The four components of the color.
        **/
        ////////////////////////////////////////////////////////////
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

        ////////////////////////////////////////////////////////////
        /** @brief Construct a Color with 0 as initialization. */
        ////////////////////////////////////////////////////////////
        Color();

        ////////////////////////////////////////////////////////////
        /** @brief Construct a color from a 32bit value with given
         *  supported format.
        **/
        ////////////////////////////////////////////////////////////
        explicit Color(unsigned long int c, Format::_ f = Format::RGBA);

        ////////////////////////////////////////////////////////////
        /** @brief Construct a Color from given RGBA value, each one
         *  from 0 to 255.
        **/
        ////////////////////////////////////////////////////////////
        Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255);

        ////////////////////////////////////////////////////////////
        /** @brief Construct a Color from given RGBA, each one from
         *  0.f to 255.f.
         *
         *  @note 0.f corresponds to 0 (no color), and 1.f corresponds
         *  to 255 (full color).
        **/
        ////////////////////////////////////////////////////////////
        explicit Color(float r, float g, float b, float a = 1.0f);

        ////////////////////////////////////////////////////////////
        /** @brief Constructs a Color from another one.
        **/
        ////////////////////////////////////////////////////////////
        Color(const Color& other);

        ////////////////////////////////////////////////////////////
        /** @brief Destructs the Color.
        **/
        ////////////////////////////////////////////////////////////
        ~Color();

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Set this Color to given 32bit value and from given
         *  format.
        **/
        ////////////////////////////////////////////////////////////
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
