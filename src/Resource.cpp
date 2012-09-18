/** @file Resource.cpp
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 25/08/2012
 *
 *  @addtogroup Global
 *  @addtogroup Resource
 *
 *  This file defines the Resource class.
 *
**/
#include "Resource.h"
#include "SharedPointer.h"

namespace APro
{
    Resource::Resource() : name(""), filename(""), type("Resource")
    {

    }

    Resource::Resource(const String& name_, const String& other) : name(name_), filename(other), type("Resource")
    {

    }

    Resource::Resource(const Resource& other) : name(""), filename(other.filename), type("Resource")
    {

    }

    Resource::~Resource()
    {

    }

    Resource& Resource::operator = (const Resource& other)
    {
        name = other.name;
        filename = other.filename;
        type = other.type;

        return *this;
    }

    String Resource::getName() const
    {
        return name;
    }

    void Resource::setName(const String& other)
    {
        name = other;
    }

    String Resource::getFilename() const
    {
        return filename;
    }

    void Resource::setFilename(const String& other)
    {
        filename = other;
    }

    String Resource::getType() const
    {
        return type;
    }
}
