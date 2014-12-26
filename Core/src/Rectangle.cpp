/////////////////////////////////////////////////////////////
/** @file Rectangle.cpp
 *  @ingroup Utils
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 21/04/2014 - 22/04/2014
 *
 *  Implements the Rectangle class.
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
        return width() * height();
    }

    bool Rectangle::isInside(const Vector2& pt) const
    {
        return pt.x >= origin.x && x <= end.x && y >= origin.y && y <= end.y;
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
