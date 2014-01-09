////////////////////////////////////////////////////////////
/** @file ResourceLoader.cpp
 *  @ingroup Core
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 25/08/2012 - 26/12/2013
 *
 *  Implements the ResourceLoader class.
 *
**/
////////////////////////////////////////////////////////////
#include "ResourceLoader.h"
#include "Variant.h"

namespace APro
{
    ResourceLoader::ResourceLoader()
        : ParametedObject()
    {

    }

    ResourceLoader::ResourceLoader(const String& n, const String& desc)
        : ParametedObject(), name(n), description(desc)
    {

    }

    ResourceLoader::ResourceLoader(const ResourceLoader& loader)
        : ParametedObject(loader), name(loader.name), description(loader.description)
    {

    }

    ResourceLoader::~ResourceLoader()
    {

    }

    const String& ResourceLoader::getName() const
    {
        return name;
    }

    const String& ResourceLoader::getDescription() const
    {
        return description;
    }
}
