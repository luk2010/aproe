/** @file ViewPort.cpp
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
#include "ViewPort.h"

namespace APro
{
    ViewPort::ViewPort()
        : zone(0,0,0,0), currentZone(0,0,0,0),
        visible(false),
        cameraName(""), name("")
    {

    }

    ViewPort::ViewPort(const String& _name)
        : zone(0,0,0,0), currentZone(0,0,0,0),
        visible(false),
        cameraName(""), name(_name)
    {

    }

    ViewPort::ViewPort(const String& _name, const ViewPort& other)
        : zone(other.zone), currentZone(other.currentZone),
        visible(other.visible),
        cameraName(""), name(_name)
    {

    }

    ViewPort::ViewPort(const String& _name, const RectangleF& z)
        : zone(z), currentZone(z),
        visible(false),
        cameraName(""), name(_name)
    {

    }

    ViewPort::~ViewPort()
    {

    }

    RectangleF& ViewPort::getZone()
    {
        return zone;
    }

    const RectangleF& ViewPort::getZone() const
    {
        return zone;
    }

    RectangleF& ViewPort::getCurrentZone()
    {
        return currentZone;
    }

    const RectangleF& ViewPort::getCurrentZone() const
    {
        return currentZone;
    }

    void ViewPort::setZone(const RectangleF& z)
    {
        zone.set(z);
    }

    void ViewPort::setCurrentZone(const RectangleF& z)
    {
        currentZone.set(z);
    }

    void ViewPort::reset()
    {
        zone.set(0,0,0,0);
        currentZone.set(0,0,0,0);
    }

    float ViewPort::getLeft() const
    {
        return zone.left();
    }

    float ViewPort::getTop() const
    {
        return zone.top();
    }

    float ViewPort::getHeight() const
    {
        return zone.height();
    }

    float ViewPort::getWidth() const
    {
        return zone.width();
    }

    float ViewPort::getCurrentLeft() const
    {
        return currentZone.left();
    }

    float ViewPort::getCurrentTop() const
    {
        return currentZone.top();
    }

    float ViewPort::getCurrentHeight() const
    {
        return currentZone.height();
    }

    float ViewPort::getCurrentWidth() const
    {
        return currentZone.width();
    }

    bool ViewPort::isVisible() const
    {
        return visible;
    }

    void ViewPort::setVisible(bool v)
    {
        visible = v;
    }

    void ViewPort::linkToCamera(const String& cname)
    {
        cameraName = cname;
    }

    String ViewPort::getCameraLinked() const
    {
        return cameraName;
    }

    void ViewPort::setName(const String& n)
    {
        name = n;
    }

    String ViewPort::getName() const
    {
        return name;
    }
}
