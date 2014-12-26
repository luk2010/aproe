/** @file ViewPort.h
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 23/10/2012 - 22/04/2014
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
#include "Rectangle.h"
#include "AutoPointer.h"

namespace APro
{
    class ViewPort
    {

    public:

        ViewPort();
        ViewPort(const String& _name);
        ViewPort(const String& _name, const ViewPort& other);
        ViewPort(const String& _name, const Rectangle& z);

        ~ViewPort();

    public:

        Rectangle& getZone();
        const Rectangle& getZone() const;

        Rectangle& getCurrentZone();
        const Rectangle& getCurrentZone() const;

    public:

        void setZone(const Rectangle& z);
        void setCurrentZone(const Rectangle& c);

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

        Rectangle zone;
        Rectangle currentZone;
        bool visible;
        String cameraName;
        String name;
    };

    typedef AutoPointer<ViewPort> ViewPortPtr;
}

#endif
