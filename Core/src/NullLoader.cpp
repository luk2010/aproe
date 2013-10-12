/** @file NullLoader.cpp
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 27/08/2012
 *
 *  @addtogroup Global
 *  @addtogroup Memory
 *
 *  This file defines the NullLoader class.
 *
**/
#include "NullLoader.h"
#include "NullResource.h"

namespace APro
{
    NullLoader::NullLoader() : ResourceLoader()
    {
        setParam(String("Name"), Variant(String("NullLoader")));
        setParam(String("Description"), Variant(String("A Null Loader for testing purpose.")));
        setParam(String("IsManual"), Variant(true));
    }

    NullLoader::NullLoader(const NullLoader& loader) : ResourceLoader(loader)
    {
        setParam(String("Name"), Variant(String("NullLoader")));
        setParam(String("Description"), Variant(String("A Null Loader for testing purpose.")));
        setParam(String("IsManual"), Variant(true));
    }

    NullLoader::~NullLoader()
    {

    }

    SharedPointer<Resource> NullLoader::loadResource(const String& filename)
    {
        return SharedPointer<Resource>(AProNew(NullResource, String(), filename));
    }
}
