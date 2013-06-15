/** @file Rectangle.h
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 26/09/2012
 *
 *  @addtogroup Global
 *  @addtogroup System
 *
 *  This file defines the Rectangle class.
 *
**/
#ifndef APRORECTANGLE_H
#define APRORECTANGLE_H

#include "Platform.h"
#include "Vector2.h"
#include "Maths.h"

namespace APro
{
    class Intersection
    {
    public:
        enum _
        {
            In,
            Out,
            Between
        };
    };

    template<typename T>
    class Rectangle
    {
    private:

        Vector2<T> origin;
        Vector2<T> end;

    public:

        Rectangle()
        {

        }

        Rectangle(const Rectangle<T>& other)
            : origin(other.origin), end(other.end)
        {

        }

        Rectangle(const Vector2<T>& start, const Vector2<T>& dimension)
            : origin(start), end(start + dimension)
        {

        }

        Rectangle(T left_, T top_, T width_, T height_)
            : origin(left_, top_), end(left_ + width_, top_ + height_)
        {

        }

        ~Rectangle()
        {

        }

        void set(T Left, T Top, T Width, T Height)
        {
            origin.x = Left;
            origin.y = Top;

            end.x = Left + Width;
            end.y = Top + Height;
        }

        void set(const Vector2<T>& start, const Vector2<T>& dimension)
        {
            origin = start;
            end = start + dimension;
        }

        void set(const Rectangle<T>& other)
        {
            origin = other.origin;
            end = other.end;
        }

        T left() const
        {
            return origin.x;
        }

        T right() const
        {
            return end.x;
        }

        T top() const
        {
            return origin.y;
        }

        T bottom() const
        {
            return end.y;
        }

        T width() const
        {
            return end.y - origin.y;
        }

        T height() const
        {
            return end.x - origin.x;
        }

        Vector2<T> size() const
        {
            return end - origin;
        }

        T surface() const
        {
            return width() * height();
        }

        Intersection::_ intersects(const Vector2<T>& pt) const
        {
            if(pt.x >= origin.x && pt.y >= origin.y &&
               pt.x <= end.x && pt.y <= end.y)
            {
                return Intersection::In;
            }
            else
            {
                return Intersection::Out;
            }
        }
        Intersection::_ intersects(const Rectangle<T>& rect) const
        {
            Vector2<T> Start(max_2(origin.x, rect.origin.x), max_2(origin.y, rect.origin.y));
            Vector2<T> End(min_2(end.x, rect.end.x), min_2(end.y, rect.end.y));
            Rectangle<T> Overlap(Start, End - Start);

            if ((Start.x > End.x) || (Start.y > End.y))
                return Intersection::Out;
            else if ((Overlap == *this) || (Overlap == rect))
                return Intersection::In;
            else
                return Intersection::Between;
        }

        bool operator == (const Rectangle& other) const
        {
            return origin == other.origin && end == other.end;
        }

        bool operator != (const Rectangle& other) const
        {
            return !(*this == other);
        }
    };

    typedef Rectangle<float> RectangleF;
    typedef Rectangle<double> RectangleD;
}

#endif
