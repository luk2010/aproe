/////////////////////////////////////////////////////////////
/** @file Point.h
 *  @ingroup Utils
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 10/07/2013
 *
 *  Defines a point.
 *
**/
/////////////////////////////////////////////////////////////
#ifndef APRO_POINT_H
#define APRO_POINT_H

#include "Platform.h"
#include "Copyable.h"
#include "Printable.h"

namespace APro
{
    /////////////////////////////////////////////////////////////
    /** @class Point
     *  @ingroup Utils
     *  @brief Describes a point.
     *  @details A point is a positionnable object that have
     *  3 coordinates : X, Y and Z. you can convert it to or from
     *  a Vector3U.
     *
     *  Point is used for rendering points or to perform some
     *  intersections.
     *
     *  @note A point is not a vector as the differene that a
     *  point is a renderable object (a dot in space) whereas
     *  a vector is a distance.
    **/
    /////////////////////////////////////////////////////////////
    class APRO_DLL Point :
        public Copyable<Point>,
        public Printable
    {
    private:

        unit_t m_x;///< X coordinate.
        unit_t m_y;///< Y coordinate.
        unit_t m_z;///< Z coordinate.

    public:

        /////////////////////////////////////////////////////////////
        /** @brief Constructor.
         *  @note Set x, y and z to 0.
        **/
        /////////////////////////////////////////////////////////////
        Point();

        /////////////////////////////////////////////////////////////
        /** @brief Copy constructor.
         *  @param point : Point to copy.
        **/
        /////////////////////////////////////////////////////////////
        Point(const Point& point);

        /////////////////////////////////////////////////////////////
        /** @brief Constructor with coordinates.
         *  @param x : X coordinate.
         *  @param y : Y coordinate.
         *  @param z : Z coordinate.
        **/
        /////////////////////////////////////////////////////////////
        Point(const unit_t& x, const unit_t& y, const unit_t& z);

        /////////////////////////////////////////////////////////////
        /** @brief Constructor from vector3U.
         *  @param position : Position of the point.
        **/
        /////////////////////////////////////////////////////////////
        explicit Point(const Vector3U& position);

        /////////////////////////////////////////////////////////////
        /** @brief Destructor.
        **/
        /////////////////////////////////////////////////////////////
        ~Point();

    public:

        /////////////////////////////////////////////////////////////
        /** @return The X coordinate.
        **/
        /////////////////////////////////////////////////////////////
        const unit_t& getX() const;

        /////////////////////////////////////////////////////////////
        /** @return The Y coordinate.
        **/
        /////////////////////////////////////////////////////////////
        const unit_t& getY() const;

        /////////////////////////////////////////////////////////////
        /** @return The Z coordinate.
        **/
        /////////////////////////////////////////////////////////////
        const unit_t& getZ() const;

        /////////////////////////////////////////////////////////////
        /** @brief Set the x parameter of this point.
         *  @param x : new X coordinate.
        **/
        /////////////////////////////////////////////////////////////
        void setX(const unit_t& x);

        /////////////////////////////////////////////////////////////
        /** @brief Set the y parameter of this point.
         *  @param y : new Y coordinate.
        **/
        /////////////////////////////////////////////////////////////
        void setY(const unit_t& y);

        /////////////////////////////////////////////////////////////
        /** @brief Set the z parameter of this point.
         *  @param z : new Z coordinate.
        **/
        /////////////////////////////////////////////////////////////
        void setZ(const unit_t& z);

        /////////////////////////////////////////////////////////////
        /** @brief Set all 3 coordinates of this point.
         *  @param x : X coordinate.
         *  @param y : Y coordinate.
         *  @param z : Z coordinate.
        **/
        /////////////////////////////////////////////////////////////
        void set(const unit_t& x, const unit_t& y, const unit_t& z);

        /////////////////////////////////////////////////////////////
        /** @brief Set coordinates from position.
         *  @param position : Position of the point.
        **/
        /////////////////////////////////////////////////////////////
        void set(const Vector3U& position);

        /////////////////////////////////////////////////////////////
        /** @brief Set coordinates from other point.
         *  @param point : Poinnt to copy.
        **/
        /////////////////////////////////////////////////////////////
        void set(const Point& point);

    public:

        /////////////////////////////////////////////////////////////
        /** @brief Get distance between this point and an other.
         *  @param other : Point to get the distance from.
         *  @return the distance.
        **/
        /////////////////////////////////////////////////////////////
        Vector3U getDistance(const Point& other) const;

    public:

        /////////////////////////////////////////////////////////////
        /** @brief Convert this point to a Vector3U.
        **/
        /////////////////////////////////////////////////////////////
        Vector3U toVector3() const;

    public: // Copyable

        void copyFrom(const Point& other);
        bool operator == (const Point& other) const;

    public: // Printabe

        void print(Console& console) const;
    };
}

#endif // APRO_POINT_H
