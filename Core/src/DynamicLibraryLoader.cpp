/////////////////////////////////////////////////////////////
/** @file DynamicLibraryLoader.cpp
 *  @ingroup Core
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 18/09/2012 - 06/02/2014
 *
 *  Implements the DynamicLibraryLoader class.
 *
**/
/////////////////////////////////////////////////////////////
#include "DynamicLibraryLoader.h"

namespace APro
{
    DynamicLibraryLoader::DynamicLibraryLoader()
    : ResourceLoader(String("DynamicLibraryLoader"), String("Loads Dynamic Library Object"))
    {

    }

    DynamicLibraryLoader::~DynamicLibraryLoader()
    {

    }

    ResourcePtr DynamicLibraryLoader::loadResource(const String& filename)
    {
        DynamicLibrary* dynlib = AProNew(DynamicLibrary, filename);

        if(dynlib->isLoaded())
            return ResourcePtr(dynlib);
        else
            return ResourcePtr();
    }
}
