////////////////////////////////////////////////////////////
/** @file Region.cpp
 *  @ingroup Utils
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 04/07/2013
 *
 *  Implements the Region class.
 *
**/
////////////////////////////////////////////////////////////
#include "Region.h"

namespace APro
{
    Region::Region()
        : m_start(0,0,0)
    {
        m_borders[0] =
        m_borders[1] =
        m_borders[2] = 0;
    }

    Region::Region(const Region& other)
        : m_start(other.m_start)
    {
        m_borders[0] = other.m_borders[0];
        m_borders[1] = other.m_borders[1];
        m_borders[2] = other.m_borders[2];
    }

    Region::Region(const Point& start, const Point& end)
    {
        m_start = start;
        m_borders[0] = end.x - start.x;
        m_borders[1] = end.y - start.y;
        m_borders[2] = end.z - start.z;
    }

    Region::Region(const Point& start, const unit_t& borders[3])
        : m_start(start)
    {
        m_borders[0] = borders[0];
        m_borders[1] = borders[1];
        m_borders[2] = borders[2];
    }

    Region::Region(const Point& start, const Region& other_translated)
        : m_start(start)
    {
        m_borders[0] = other_translated.m_borders[0];
        m_borders[1] = other_translated.m_borders[1];
        m_borders[2] = other_translated.m_borders[2];
    }

    Region Region::createAxisRegion(const unit_t& borders[3])
    {
        return Region(Point(0,0,0), borders);
    }

    Region::~Region()
    {

    }

    void Region::checkBordersAndStart()
    {
        if(m_borders[0] < 0)
        {
            m_borders[0] = -m_borders[0];
            m_start.x = m_start.x + m_borders[0];
        }
    }
}
