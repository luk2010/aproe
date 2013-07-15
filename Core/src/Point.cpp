/////////////////////////////////////////////////////////////
/** @file Point.cpp
 *  @ingroup Utils
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 10/07/2013
 *
 *  Implements a point.
 *
**/
/////////////////////////////////////////////////////////////
#include "Point.h"

namespace APro
{
    Point::Point()
    {
        set(0,0,0);
    }

    Point::Point(const Point& point)
    {
        set(point);
    }

    Point::Point(const vector3U& position)
    {
        set(position);
    }

    Point::Point(const unit_t& x, const unit_t& y, const unit_t& z)
    {
        set(x,y,z);
    }

    Point::~Point()
    {

    }

    const unit_t& Point::getX() const
    {
        return m_x;
    }

    const unit_t& Point::getY() const
    {
        return m_y;
    }

    const unit_t& Point::getZ() const
    {
        return m_z;
    }

    void Point::setX(const unit_t& x)
    {
        m_x = x;
    }

    void Point::setY(const unit_t& y)
    {
        m_y = y;
    }

    void Point::setZ(const unit_t& z)
    {
        m_z = z;
    }

    void Point::set(const unit_t& x, const unit_t& y, const unit_t& z)
    {
        setX(x); setY(y); setZ(z);
    }

    void Point::set(const Vector3U& position)
    {
        set(position.x, position.y, position.z);
    }

    void Point::set(const Point& point)
    {
        set(point.getX(), point.getY(), point.getZ());
    }

    Vector3U Point::getDistance(const Point& other) const
    {
        return this->toVector3().vdistance(other.toVector3());
    }

    Vector3U Point::toVector3() const
    {
        return Vector3U(getX(), getY(), getZ());
    }

    void Point::copyFrom(const Point& other)
    {
        set(other);
    }

    bool Point::operator==(const Point& other) const
    {
        return getX() == other.getX() &&
               getY() == other.getY() &&
               getZ() == other.getZ();
    }

    void Point::print(Console& console) const
    {
        console << "[Point] { " << getX() << " ; " << getY() << " ; " << getZ() << " }";
    }
}
