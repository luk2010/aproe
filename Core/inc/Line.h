/////////////////////////////////////////////////////////////
/** @file Line.h
 *  @ingroup Utils
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 0/07/2013
 *
 *  Defines an inifinite line.
 *
**/
/////////////////////////////////////////////////////////////
#ifndef APRO_LINE_H
#define APRO_LINE_H

#include "Platform.h"
#include "Point.h"

#include "Copyable.h"
#include "Printable.h"

namespace APro
{
    /////////////////////////////////////////////////////////////
    /** @class Line
     *  @ingroup Utils
     *  @brief An inifinite line extending in 2 directions.
     *  @details It is defined by an origine and a direction.
    **/
    /////////////////////////////////////////////////////////////
    class APRO_DLL Line : public Copyable<Line>,
                          public Printable
    {
    protected:

        Vector3U m_direction;///< Direction of the line.
        Point    m_origin;   ///< Origin of the line.

    public:

        Line();
        Line(const Point& origin, const Vector3U& direction);
        Line(const Point& p1, const Point& p);

        ~Line();

    public:

        const Vector3U& getDirection() const;
        const Point& getOrigin() const;

        void setDirection(const Vector3U& direction);
        void setOrigin(const Point& origin);

    public:

        Point getPoint(const unit_t& distance);

    public:

        void translate(const Vector3U& vec);
        void transform(const Matrix4U& m4x4);

    };
}

#endif // APRO_LINE_H
