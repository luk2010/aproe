////////////////////////////////////////////////////////////
/** @file Color.h
 *  @ingroup Utils
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 23/09/2012 - 15/12/2014
 *
 *  @brief
 *  Defines the Color class.
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
#ifndef APROCOLOR_H
#define APROCOLOR_H

#include "Platform.h"
#include "Console.h"

#include "BaseObject.h"
#include "Copyable.h"
#include "Swappable.h"
#include "Printable.h"

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
     *  @note 
     *  Color data size is uint32_t (32bits). Each channel occupie 
     *  8 bits. The Color object size is sizeof(Color), and is greater
     *  than uint32_t because of virtual class inheritance.
    **/
    ////////////////////////////////////////////////////////////
    class APRO_DLL Color : public BaseObject<Color, AllocatorPool::Default>,
                           public Copyable<Color>,
                           public Swappable<Color>,
                           public Printable
    {
    public:

        ////////////////////////////////////////////////////////////
        /** @brief Helper to describe most formats used.
        **/
        ////////////////////////////////////////////////////////////
        enum class Format
        {
            RGBA, ///< Used by this Engine.
            ARGB, ///< Commonly used by DirectX.
            ABGR  ///< Commonly used by OpenGL.
        };

        ////////////////////////////////////////////////////////////
        /** @brief The four components of the color.
        **/
        ////////////////////////////////////////////////////////////
        enum class Component
        {
            Red,
            Green,
            Blue,
            Alpha
        };

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Construct a Color with 0 as initialization. 
        **/
        ////////////////////////////////////////////////////////////
        Color();

        ////////////////////////////////////////////////////////////
        /** @brief Construct a color from a 32bit value with given
         *  supported format.
        **/
        ////////////////////////////////////////////////////////////
        explicit Color(uint32_t c, Format f = Format::RGBA);

        ////////////////////////////////////////////////////////////
        /** @brief Construct a Color from given RGBA value, each one
         *  from 0 to 255.
        **/
        ////////////////////////////////////////////////////////////
        Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);

        ////////////////////////////////////////////////////////////
        /** @brief Construct a Color from given RGBA, each one from
         *  0.0 to 1.0.
         *
         *  @note 
         *  0.0f corresponds to 0 (no color), and 1.0f corresponds
         *  to 255 (full color).
        **/
        ////////////////////////////////////////////////////////////
        explicit Color(Real r, Real g, Real b, Real a = 1.0);

        ////////////////////////////////////////////////////////////
        /** @brief Constructs a Color from another one.
        **/
        ////////////////////////////////////////////////////////////
        Color(const Color& other);
        
        ////////////////////////////////////////////////////////////
        /** @brief Constructs a Color from a move semantic.
        **/
        ////////////////////////////////////////////////////////////
        Color(Color&& rhs);

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
        void set(uint32_t c, Format f = Format::RGBA);
        
        ////////////////////////////////////////////////////////////
        /** @brief Set this Color.
         **/
        ////////////////////////////////////////////////////////////
        void set(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
        
        ////////////////////////////////////////////////////////////
        /** @brief Set this Color.
         **/
        ////////////////////////////////////////////////////////////
        void set(Real r, Real g, Real b, Real a = 1.0f);
        
        ////////////////////////////////////////////////////////////
        /** @brief Set a Color Component.
         **/
        ////////////////////////////////////////////////////////////
        void set(Component component, uint8_t c);
        
        ////////////////////////////////////////////////////////////
        /** @brief Set this Color.
         **/
        ////////////////////////////////////////////////////////////
        void set(const Color& other);
        
        ////////////////////////////////////////////////////////////
        /** @brief Get a Color Component.
         **/
        ////////////////////////////////////////////////////////////
        uint8_t get(Component c) const;
        
        ////////////////////////////////////////////////////////////
        /** @brief Returns the Color Lightness.
        **/
        ////////////////////////////////////////////////////////////
        Real lightness() const;
        
        ////////////////////////////////////////////////////////////
        /** @brief Returns the Color Luminance.
         **/
        ////////////////////////////////////////////////////////////
        Real luminance() const;
        
        ////////////////////////////////////////////////////////////
        /** @brief Returns the Color Average.
         **/
        ////////////////////////////////////////////////////////////
        Real average() const;

        ////////////////////////////////////////////////////////////
        /** @brief Format the given 32 bit pattern to given format.
         **/
        ////////////////////////////////////////////////////////////
        void format(uint32_t & ret, Format f) const;

        ////////////////////////////////////////////////////////////
        /** @brief Returns the Color Darkered by 10.
         **/
        ////////////////////////////////////////////////////////////
        Color& darker();
        
        ////////////////////////////////////////////////////////////
        /** @brief Returns the Color Lightered by 10.
         **/
        ////////////////////////////////////////////////////////////
        Color& lighter();

        bool operator == (const Color& other) const;
        bool operator !=(const Color& other) const;

//      Color& operator = (const Color& other);
        Color& operator += (const Color& other);
        Color& operator -= (const Color& other);

        Color operator + (const Color& other) const;
        Color operator - (const Color& other) const;

/* Deprecated. Please use ::ptr().
        operator unsigned char*();
        operator const unsigned char*() const;
 */
        ////////////////////////////////////////////////////////////
        /** @brief Returns the Color data pointer.
         **/
        ////////////////////////////////////////////////////////////
        uint8_t* ptr() { return (uint8_t*) &color; }
        
        ////////////////////////////////////////////////////////////
        /** @brief Returns the Color data pointer.
         **/
        ////////////////////////////////////////////////////////////
        const uint8_t* ptr() const { return (const uint8_t*) &color; }

        /////////////////////////////////////////////////////////////
        /** @brief Print information about this object in the console.
         **/
        /////////////////////////////////////////////////////////////
        void print(Console& c) const
        {
            c << "Color( "  << (int) get(Component::Red)    << ", "
                            << (int) get(Component::Green)  << ", "
                            << (int) get(Component::Blue)   << ", "
                            << (int) get(Component::Alpha)  << " )";
        }

        ////////////////////////////////////////////////////////////
        /** @brief Returns a Color giving its R,G and B channels.
         *  @param r : Red Channel (0-255).
         *  @param g : Green Channel (0-255).
         *  @param b : Blue Channel (0-255).
        **/
        ////////////////////////////////////////////////////////////
        static Color rgb(uint8_t r, uint8_t g, uint8_t b);
        
        ////////////////////////////////////////////////////////////
        /** @brief Returns a Color giving its R, G, B and A channels.
         *  @param r : Red Channel (0-255).
         *  @param g : Green Channel (0-255).
         *  @param b : Blue Channel (0-255).
         *  @param a : Alpha Channel (0-255).
        **/
        ////////////////////////////////////////////////////////////
        static Color rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

        static Color Black;
        static Color White;
        static Color Green;
        static Color Blue;
        static Color Red;
        
    public:
        
        /////////////////////////////////////////////////////////////
        /** @brief Copy this object from another object of same kind.
         *  @param other : Object to copy.
         **/
        /////////////////////////////////////////////////////////////
        void copyFrom(const Color& other) { color = other.color; }
        
        ////////////////////////////////////////////////////////////
        /** @brief Swap this object with another one from the same
         *  kind.
         **/
        ////////////////////////////////////////////////////////////
        void swap(Color& obj) { std::swap (color, obj.color); }

    private:
        uint32_t color;
    };
}

#endif
