/////////////////////////////////////////////////////////////
/** @file DynamicLibrary.h
 *  @ingroup Core
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 18/09/2012 - 06/02/2014
 *
 *  Defines the DynamicLibrary class.
 *
**/
/////////////////////////////////////////////////////////////
#ifndef APRODYNAMICLIBRARY_H
#define APRODYNAMICLIBRARY_H

#include "Atomic.h"
#include "Resource.h"
#include "EventEmitter.h"

#if APRO_PLATFORM == APRO_WINDOWS
#   define DYNLIB_HANDLE hInstance
#   define DYNLIB_GETSYM( a, b ) GetProcAddress( a, b )
#   define DYNLIB_LOAD( a ) LoadLibraryEx( a, NULL, LOAD_WITH_ALTERED_SEARCH_PATH )
#   define DYNLIB_UNLOAD( a ) FreeLibrary( a )
#   define DYNLIB_EXTENSION "dll"
#   define DYNLIB_LASTERROR dlerror

struct HINSTANCE__;
typedef struct HINSTANCE__ * hInstance;

/* We provide custom dlerror for Windows(tm).
 * https://mail.python.org/pipermail//pypy-commit/2012-October/066804.html
*/
static const char *dlerror(void)
{
    static char buf[32];
    DWORD dw = GetLastError();
    if (dw == 0)
        return NULL;
    sprintf(buf, "error 0x%x", (unsigned int)dw);
    return buf;
}

#elif APRO_PLATFORM == APRO_OSX
#   define DYNLIB_HANDLE void*
#   define DYNLIB_GETSYM( a, b ) dlsym( a, b )
#   define DYNLIB_LOAD( a ) mac_loadDylib( a )
#   define DYNLIB_UNLOAD( a ) !dlclose( a )
#   define DYNLIB_EXTENSION "dynlib"
#   define DYNLIB_LASTERROR dlerror
#   include <dlfcn.h>

#else
#   define DYNLIB_HANDLE void*
#   define DYNLIB_GETSYM( a, b ) dlsym( a, b )
#   define DYNLIB_LOAD( a ) dlopen( a, RTLD_LAZY | RTLD_GLOBAL)
#   define DYNLIB_UNLOAD( a ) !dlclose( a )
#   define DYNLIB_EXTENSION "so"
#   define DYNLIB_LASTERROR dlerror
#   include <dlfcn.h>

#endif

namespace APro
{
    /////////////////////////////////////////////////////////////
    /** @class DynamicLibrary
     *  @ingroup Core
     *  @brief A handler to a dynamicly loaded object.
     *
     *  Object is loaded during construction in the
     *  DynamicLibraryLoader and is automaticly unloaded during
     *  destruction process.
     *
     *  You can load/unload the dynamic object whenever you want,
     *  and you can call every function you want in the library.
     *
     *  @note DynamicLibrary is dependant to the system API. This
     *  is specific for OS X and Windows, but other platforms uses
     *  default Unix load system.
     *
     *  ### DynamicLibrary Event
     *
     *  - DynamicLibraryLoadedEvent : Sent when a DynamicLibrary is
     *  loaded, after it is loaded successfully.
     *  - DynamicLibraryUnloadedEvent : Sentt just before a DynamicLibrary
     *  is unloaded.
     *
     *  Use these events to control post and pre loading/unloading
     *  libraries.
    **/
    /////////////////////////////////////////////////////////////
    class APRO_DLL DynamicLibrary : public Resource,
                                    public EventEmitter
    {

        APRO_DECLARE_HASHEDTYPE;

    public:

        /////////////////////////////////////////////////////////////
        /** @brief Constructs an empty DynamicLibrary object.
        **/
        /////////////////////////////////////////////////////////////
        DynamicLibrary();

        /////////////////////////////////////////////////////////////
        /** @brief Constructs a DynamicLibrary object from his
         *  filename.
         *  @note Dynamic Loaded Object is loaded in the constructor,
         *  if possible.
        **/
        /////////////////////////////////////////////////////////////
        DynamicLibrary(const String& mfilename);

        /////////////////////////////////////////////////////////////
        /** @brief Destructs the Dynamic Library object.
         *  @note If loaded, the object is unloaded.
        **/
        /////////////////////////////////////////////////////////////
        ~DynamicLibrary();

    public:

        /////////////////////////////////////////////////////////////
        /** @brief Return the adress of the function described by
         *  sym.
         *  @return Null if sym is incorrect (bad or null value).
        **/
        /////////////////////////////////////////////////////////////
        void* getSymbol(const char* sym);

    public:

        /////////////////////////////////////////////////////////////
        /** @brief Load the Dynamic Library Object in memory.
         *  @return True on success or if already loaded, false if an
         *  an error occured.
        **/
        /////////////////////////////////////////////////////////////
        bool load();

        /////////////////////////////////////////////////////////////
        /** @brief Unload the Dynamic Library Object in memory.
         *  @return True on success or if already unloaded, false if an
         *  an error occured.
         *  @note On failure, loaded state is still set to false, but
         *  function returns false too.
        **/
        /////////////////////////////////////////////////////////////
        bool unload();

        /////////////////////////////////////////////////////////////
        /** @brief Tells if library is loaded.
        **/
        /////////////////////////////////////////////////////////////
        bool isLoaded() const;

    protected:

        /////////////////////////////////////////////////////////////
        /** @brief Create an event recognized by his hash type.
         *  @see EventEmitter::createEvent
        **/
        /////////////////////////////////////////////////////////////
        EventPtr createEvent(const HashType& e_type) const;

    protected:

        AtomicBool    loaded;///< True if library is loaded.
        DYNLIB_HANDLE handle;///< Handle to the object.
    };

    /** @brief Event send after a DynamicLibrary is loaded successfully. */
    APRO_DECLARE_EVENT_NOCONTENT(DynamicLibraryLoadedEvent);

    /** @brief Event send before a DynamicLibrary is unloaded. */
    APRO_DECLARE_EVENT_NOCONTENT(DynamicLibraryUnloadedEvent);

    typedef AutoPointer<DynamicLibrary> DynamicLibraryPtr;
}

#endif
