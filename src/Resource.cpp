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
#include "ThreadMutex.h"
#include "ThreadMutexLockGuard.h"

namespace APro
{
    Resource::Resource() : ThreadSafe(), name(""), filename(""), type("Resource")
    {

    }

    Resource::Resource(const String& name_, const String& other) : ThreadSafe(), name(name_), filename(other), type("Resource")
    {

    }

    Resource::Resource(const Resource& other) : ThreadSafe(), name(""), filename(other.filename), type("Resource")
    {

    }

    Resource::~Resource()
    {

    }

    Resource& Resource::operator = (const Resource& other)
    {
        APRO_THREADSAFE_AUTOLOCK

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
        APRO_THREADSAFE_AUTOLOCK

        name = other;
    }

    String Resource::getFilename() const
    {
        return filename;
    }

    void Resource::setFilename(const String& other)
    {
        APRO_THREADSAFE_AUTOLOCK

        filename = other;
    }

    String Resource::getType() const
    {
        return type;
    }
}
