/////////////////////////////////////////////////////////////
/** @file DynamicLibraryLoader.h
 *  @ingroup Core
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 18/09/2012 - 04/02/2014
 *
 *  Defines the DynamicLibraryLoader class.
 *
**/
/////////////////////////////////////////////////////////////
#ifndef APRODYNAMICLIBRARYLOADER_H
#define APRODYNAMICLIBRARYLOADER_H

#include "ResourceLoader.h"
#include "DynamicLibrary.h"

namespace APro
{

    class APRO_DLL DynamicLibraryLoader : public ResourceLoader
    {
//      APRO_DECLARE_SHAREDPOINTER_CLASS_TYPEDEF(DynamicLibraryLoader) DEPRECATED

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Constructs the loader.
        **/
        ////////////////////////////////////////////////////////////
        DynamicLibraryLoader();

        ////////////////////////////////////////////////////////////
        /** @brief Destructs the loader.
        **/
        ////////////////////////////////////////////////////////////
        ~DynamicLibraryLoader();

        ////////////////////////////////////////////////////////////
        /** @brief Load a resource.
         *  @note Create the Resource object and returns it. If an error
         *  occurs, nullptr is returned.
        **/
        ////////////////////////////////////////////////////////////
        ResourcePtr loadResource(const String& filename);
    };
}

#endif
