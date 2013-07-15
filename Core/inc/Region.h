////////////////////////////////////////////////////////////
/** @file Region.h
 *  @ingroup Utils
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 03/07/2013
 *
 *  Defines the Region class.
 *
**/
////////////////////////////////////////////////////////////
#ifndef APRO_REGION_H
#define APRO_REGION_H

#include "Platform.h"
#include "Printable.h"
#include "Vector3.h"
#include "Rectangle.h"
#include "Translatable.h"
#include "Printable.h"
#include "Copyable.h"

namespace APro
{
    ////////////////////////////////////////////////////////////
    /** @class Region
     *  @ingroup Utils
     *  @brief A tridimensionnal volume, axis-aligned.
     *  @details Describes a tridimensionnal space axis-aligned.
     *
     *  It is composed by 2 points, the max point and the min
     *  point.
    **/
    ////////////////////////////////////////////////////////////
    class APRO_DLL Region : public Translatable,
                            public Printable,
                            public Copyable<Region>
    {
    protected:

        Point  m_start;///< Start of the region.
        unit_t m_borders[3];///< Width of every border.

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Constructor.
        **/
        ////////////////////////////////////////////////////////////
        Region();

        ////////////////////////////////////////////////////////////
        /** @brief Copy constructor.
        **/
        ////////////////////////////////////////////////////////////
        Region(const Region& other);

        ////////////////////////////////////////////////////////////
        /** @brief Construct a region with a start point and a
         *  end point.
        **/
        ////////////////////////////////////////////////////////////
        Region(const Point& start, const Point& end);

        ////////////////////////////////////////////////////////////
        /** @brief Construct a regioni with start point and borders.
        **/
        ////////////////////////////////////////////////////////////
        Region(const Point& start, const unit_t& borders[3]);

        ////////////////////////////////////////////////////////////
        /** @brief Construct a region with start point and other region
         *  borders.
        **/
        ////////////////////////////////////////////////////////////
        Region(const Point& start, const Region& other_translated);

        ////////////////////////////////////////////////////////////
        /** @brief Create a region with Point(0,0,0).
        **/
        ////////////////////////////////////////////////////////////
        static Region createAxisRegion(const unit_t& borders[3]);

        ////////////////////////////////////////////////////////////
        /** @brief Destructor.
        **/
        ////////////////////////////////////////////////////////////
        ~Region();

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Set new coordinates.
         *  @param start : Start point of the region.
         *  @param end : End point of the region.
        **/
        ////////////////////////////////////////////////////////////
        void setCoordinate(const Point& start, const Point& end);


        void setCoordinate(const Point& start, const unit_t& borders[3]);

        void setCoordinate(const Region& other);

        const Point& getStart() const;
        Point& getStart();

        const Point& getEnd() const;
        Point& getEnd();

        RectangleF getTopFace() const;
        RectangleF getSideFace() const;

    public:

        bool isIn(const Point& point) const;
        bool isOut(const Point& point) const;
        bool touch(const Point& point) const;

    public:

        bool touch(const Ray& ray) const;

    public:

        bool isIn(const Line& line) const;
        bool isOut(const Line& line) const;
        bool touch(const Line& line) const;

    public:

        bool touch(const Plane& plane) const;

    public:

        bool isIn(const BoundedPlane& bplane) const;
        bool isOut(const BoundedPlane& bplane) const;
        bool touch(const BoundedPlane& bplane) const;

    public:

        bool isIn(const Region& region) const;
        bool isOut(const Region& region) const;
        bool touch(const Region& region) const;

        bool operator == (const Region& region) const;

        bool operator > (const Region& region) const;
        bool operator >= (const Region& region) const;

        bool operator < (const Region& region) const;
        bool operator <= (const Region& region) const;

    public:

        Region& add(const Region& other);

        Region operator + (const Region& other) const;
        Region& operator += (const Region& other);

    public:

        double volume();

    protected:

        void checkBordersAndStart();
    };
}

#endif // APRO_REGION_H
