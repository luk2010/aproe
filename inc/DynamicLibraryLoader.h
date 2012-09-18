/** @file DynamicLibraryLoader.h
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
#ifndef APRODYNAMICLIBRARYLOADER_H
#define APRODYNAMICLIBRARYLOADER_H

#include "ResourceLoader.h"
#include "DynamicLibrary.h"

namespace APro
{
    class APRO_DLL DynamicLibraryLoader : public ResourceLoader
    {
    public:

        DynamicLibraryLoader();
        DynamicLibraryLoader(const DynamicLibraryLoader& other);

        ~DynamicLibraryLoader();

        SharedPointer<Resource> loadResource(const String& filename);
    };
}

#endif
