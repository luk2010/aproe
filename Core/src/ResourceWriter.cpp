////////////////////////////////////////////////////////////
/** @file ResourceWriter.cpp
 *  @ingroup Core
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 01/09/2012 - 03/02/2014
 *
 *  Defines the ResourceWriter class.
 *
**/
////////////////////////////////////////////////////////////
#include "ResourceWriter.h"

namespace APro
{
    ResourceWriter::ResourceWriter()
        : name(""), description("")
    {

    }

    ResourceWriter::ResourceWriter(const String& n, const String& desc)
        : name(n), description(desc)
    {

    }

    ResourceWriter::ResourceWriter(const ResourceWriter& other)
        : name(""), description("")
    {
        name = other.getName();
        description = other.getDescription();
        compatible_hash = other.compatible_hash;
    }

    ResourceWriter::~ResourceWriter()
    {

    }

    bool ResourceWriter::isCompatible(const ResourcePtr& resource) const
    {
        HashType h = resource->getHash();
        return compatible_hash.contains(h);
    }

    const String& ResourceWriter::getName() const
    {
        return name;
    }

    const String& ResourceWriter::getDescription() const
    {
        return description;
    }
}
