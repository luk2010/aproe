/** @file DynamicLibraryLoader.cpp
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 18/09/2012
 *
 *  @addtogroup Global
 *  @addtogroup System
 *
 *  This file defines the DynamicLibraryLoader class.
 *
**/
#include "DynamicLibraryLoader.h"
#include "List.h"

namespace APro
{
    DynamicLibraryLoader::DynamicLibraryLoader() : ResourceLoader()
    {
        setParam(String("Name"), Variant(String("DynamicLibraryLoader")));
        setParam(String("Description"), Variant(String("Does nothing itself, create the DynamicLibrary resource object.")));
        setParam(String("IsManual"), Variant(false));

        List<String> exts; exts << String(DYNLIB_EXTENSION);
        setParam(String("Extensions"), Variant(exts));
    }

    DynamicLibraryLoader::DynamicLibraryLoader(const DynamicLibraryLoader& other) : ResourceLoader(other)
    {
        setParam(String("Name"), Variant(String("DynamicLibraryLoader")));
        setParam(String("Description"), Variant(String("Does nothing itself, create the DynamicLibrary resource object.")));
        setParam(String("IsManual"), Variant(false));

        List<String> exts; exts << String(DYNLIB_EXTENSION);
        setParam(String("Extensions"), Variant(exts));
    }

    DynamicLibraryLoader::~DynamicLibraryLoader()
    {

    }

    SharedPointer<Resource> DynamicLibraryLoader::loadResource(const String& filename)
    {
        SharedPointer<DynamicLibrary> dynlib = AProNew(1, DynamicLibrary) (String(), filename);
        dynlib->load();

        return SharedPointer<Resource>(dynlib);
    }
}
