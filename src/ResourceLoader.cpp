/** @file ResourceLoader.h
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 27/08/2012
 *
 *  @addtogroup Global
 *  @addtogroup Resource
 *
 *  This file defines the ResourceLoader class.
 *
**/
#include "ResourceLoader.h"
#include "Variant.h"

namespace APro
{
    ResourceLoader::ResourceLoader()
        : ParametedObject()
    {
        setParam(String("Name"), Variant(String("ResourceLoader")), String("Name of the loader."));
        setParam(String("Description"), Variant(String("A Basic ResourceLoader.")), String("Description or Usage of the loader."));
        setParam(String("Extensions"), Variant(List<String>()), String("Extensions supported by the loader. If empty, all extensions are supported."));
        setParam(String("IsManual"), Variant(false), String("Tell if loader must be manually specified or automaticly managed by the ResourceManager."));
    }

    ResourceLoader::ResourceLoader(const ResourceLoader& loader)
        : ParametedObject(loader)
    {
        setParam(String("Name"), loader.getParam(String("Name")), String("Name of the loader."));
        setParam(String("Description"), loader.getParam(String("Description")), String("Description or Usage of the loader."));
        setParam(String("Extensions"), loader.getParam(String("Extensions")), String("Extensions supported by the loader. If empty, all extensions are supported."));
        setParam(String("IsManual"), loader.getParam(String("IsManual")), String("Tell if loader must be manually specified or automaticly managed by the ResourceManager."));
    }

    ResourceLoader::~ResourceLoader()
    {

    }

    String ResourceLoader::name() const
    {
        return getParam(String("Name")).to<String>();
    }

    String ResourceLoader::description() const
    {
        return getParam(String("Description")).to<String>();
    }

    const List<String>& ResourceLoader::extensions() const
    {
        return getParam(String("Extensions")).to<List<String> >();
    }

    bool ResourceLoader::isManual() const
    {
        return getParam(String("IsManual")).to<bool>();
    }
}
