/** @file ViewPort.h
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 23/10/2012
 *
 *  @addtogroup Global
 *  @addtogroup Rendering
 *
 *  This file defines the ViewPort class.
 *
**/
#ifndef APROVIEWPORT_H
#define APROVIEWPORT_H

#include "Platform.h"
#include "SharedPointer.h"
#include "Rectangle.h"

namespace APro
{
    class ViewPort
    {
        APRO_DECLARE_SHAREDPOINTER_CLASS_TYPEDEF(ViewPort)

    public:

        ViewPort();
        ViewPort(const String& _name);
        ViewPort(const String& _name, const ViewPort& other);
        ViewPort(const String& _name, const RectangleF& z);

        ~ViewPort();

    public:

        RectangleF& getZone();
        const RectangleF& getZone() const;

        RectangleF& getCurrentZone();
        const RectangleF& getCurrentZone() const;

    public:

        void setZone(const RectangleF& z);
        void setCurrentZone(const RectangleF& c);

        void reset();

    public:

        float getLeft() const;
        float getTop() const;

        float getHeight() const;
        float getWidth() const;

        float getCurrentLeft() const;
        float getCurrentTop() const;

        float getCurrentHeight() const;
        float getCurrentWidth() const;

    public:

        bool isVisible() const;
        void setVisible(bool v);

    public:

        void linkToCamera(const String& cname);
        String getCameraLinked() const;

    public:

        void setName(const String& n);
        String getName() const;

    protected:

        RectangleF zone;
        RectangleF currentZone;
        bool visible;
        String cameraName;
        String name;
    };
}

#endif
