/////////////////////////////////////////////////////////////
/** @file Rectangle.cpp
 *  @ingroup Utils
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 21/04/2014 - 17/02/2015
 *
 *  @brief
 *  Implements the Rectangle class.
 *
 *  @copyright
 *  Atlanti's Project Engine
 *  Copyright (C) 2012 - 2015  Atlanti's Corp
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
/////////////////////////////////////////////////////////////
#include "Rectangle.h"

namespace APro
{
    Rectangle::Rectangle()
        : origin(Vector2::Zero), end(Vector2::Zero)
    {

    }

    Rectangle::Rectangle(const Rectangle& other)
        : origin(other.origin), end(other.end)
    {

    }

   Rectangle::Rectangle(const Vector2& start, const Vector2& dimension)
        : origin(start), end(start + dimension)
    {

    }

    Rectangle::Rectangle(Real left, Real top, Real width, Real height)
        : origin(left, top), end(left + width, top + height)
    {

    }

    Rectangle::~Rectangle()
    {

    }

    void Rectangle::set(Real Left, Real Top, Real Width, Real Height)
    {
        origin.x = Left;
        origin.y = Top;

        end.x = Left + Width;
        end.y = Top + Height;
    }

    void Rectangle::set(const Vector2& start, const Vector2& dimension)
    {
        origin = start;
        end = start + dimension;
    }

    void Rectangle::set(const Rectangle& other)
    {
        origin = other.origin;
        end = other.end;
    }

    Real Rectangle::getSurface() const
    {
        return getWidth() * getHeight();
    }

    bool Rectangle::isInside(const Vector2& pt) const
    {
        return pt.x >= origin.x && pt.x <= end.x && pt.y >= origin.y && pt.y <= end.y;
    }

    Intersection Rectangle::intersects(const Vector2& pt) const
    {
        if(isInside(pt))
            return INTIN;
        else
            return INTOUT;
    }

    Rectangle Rectangle::getIntersection(const Rectangle& rhs) const
    {
        Rectangle r;

        r.origin.x   = origin.x   > rhs.origin.x   ? origin.x   : rhs.origin.x;
        r.origin.y   = origin.y   > rhs.origin.y   ? origin.y   : rhs.origin.y;
        r.end.x      = end.x      < rhs.end.x      ? end.x      : rhs.end.x;
        r.end.y      = end.y      < rhs.end.y      ? end.y      : rhs.end.y;

        return r;
    }

    bool Rectangle::isValid() const
    {
        return origin.x < end.x &&
               origin.y < end.y;
    }

    Intersection Rectangle::intersects(const Rectangle& rect) const
    {
        Rectangle inter = getIntersection(rect);
        if(!inter.isValid())
            return INTOUT;
        else if(inter == *this || inter == rect)
            return INTIN;
        else
            return INTBETWEEN;
    }

    bool Rectangle::operator == (const Rectangle& other) const
    {
        return origin == other.origin && end == other.end;
    }

    bool Rectangle::operator != (const Rectangle& other) const
    {
        return !(*this == other);
    }
}
