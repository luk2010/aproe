/** @file DynamicLibrary.h
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 18/09/2012
 *
 *  @addtogroup Global
 *  @addtogroup System
 *
 *  This file defines the DynamicLibrary class.
 *
**/
#ifndef APRODYNAMICLIBRARY_H
#define APRODYNAMICLIBRARY_H

#include "Resource.h"
#include "SharedPointer.h"

#if APRO_PLATFORM == APRO_WINDOWS
#   define DYNLIB_HANDLE hInstance
#   define DYNLIB_GETSYM( a, b ) GetProcAddress( a, b )
#   define DYNLIB_LOAD( a ) LoadLibraryEx( a, NULL, LOAD_WITH_ALTERED_SEARCH_PATH )
#   define DYNLIB_UNLOAD( a ) FreeLibrary( a )
#   define DYNLIB_EXTENSION "dll"

struct HINSTANCE__;
typedef struct HINSTANCE__ * hInstance;

#elif APRO_PLATFORM == APRO_LINUX
#   define DYNLIB_HANDLE void*
#   define DYNLIB_GETSYM( a, b ) dlsym( a, b )
#   define DYNLIB_LOAD( a ) dlopen( a, RTLD_LAZY | RTLD_GLOBAL)
#   define DYNLIB_UNLOAD( a ) !dlclose( a )
#   define DYNLIB_EXTENSION "so"
#   include <dlfcn.h>

#elif APRO_PLATFORM == APRO_OSX
#   define DYNLIB_HANDLE void*
#   define DYNLIB_GETSYM( a, b ) dlsym( a, b )
#   define DYNLIB_LOAD( a ) mac_loadDylib( a )
#   define DYNLIB_UNLOAD( a ) !dlclose( a )
#   define DYNLIB_EXTENSION "dynlib"

#endif

namespace APro
{
    class APRO_DLL DynamicLibrary : public Resource
    {
        APRO_DECLARE_SHAREDPOINTER_CLASS_TYPEDEF(DynamicLibrary)

    public:

        DynamicLibrary();
        DynamicLibrary(const String& mname, const String& mfilename);

        ~DynamicLibrary();

        void* getSymbol(const String& sym) const;

        void load();
        void unload();

        bool isLoaded() const;

        void destroy();

    protected:

        bool loaded;
        DYNLIB_HANDLE handle;
    };
}

#endif
