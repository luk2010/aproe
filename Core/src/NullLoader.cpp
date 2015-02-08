/** @file NullLoader.cpp
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 27/08/2012 - 07/05/2014
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
    NullLoader::NullLoader()
        : ResourceLoader(String("NullLoader"), String("Null Loader for Tests"))
    {

    }

    NullLoader::NullLoader(const NullLoader& loader)
        : ResourceLoader(loader)
    {

    }

    NullLoader::~NullLoader()
    {

    }

    ResourcePtr NullLoader::loadResource(const String& filename)
    {
        return ResourcePtr(AProNew(NullResource, filename));
    }
}
