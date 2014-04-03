////////////////////////////////////////////////////////////
/** @file Platform.h
 *  @ingroup Global
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 21/05/2012 - 28/02/2014
 *
 *  This file defines some constants to be used on different platform.
 *
**/
////////////////////////////////////////////////////////////
#ifndef APROPLATFORM_H
#define APROPLATFORM_H

/** Complete version name of the @ref Memory Module. */
#define APRO_MEMORY_VERSION "0.1A"

#include "Base.h"

#if APRO_EXCEPTION == APRO_ON
#   include "Exception.h"
#endif

#include "Memory.h"

////////////////////////////////////////////////////////////
/** @class Platform
 *  @ingroup Global
 *  @brief Give the current Operating System supported by
 *  the engine.
**/
////////////////////////////////////////////////////////////
class Platform
{
public:

    enum
    {
        Unknown     = 0,
        Windows     = APRO_WINDOWS,
        WindowsCE   = APRO_WINDOWSCE,
        Linux       = APRO_LINUX,
        Apple       = APRO_OSX
    };

    ////////////////////////////////////////////////////////////
    /** @brief Return the current builded platform.
     *  @note This might be different to the current running
     *  platform.
    **/
    ////////////////////////////////////////////////////////////
    static const int Get()
    {
#if APRO_PLATFORM == APRO_WINDOWS
        return (int) Windows;
#elif APRO_PLATFORM == APRO_WINDOWSCE
        return (int) WindowsCE;
#elif APRO_PLATFORM == APRO_LINUX
        return (int) Linux;
#elif APRO_PLATFORM == APRO_OSX
        return (int) Apple;
#else
       return Unknown;
#endif
    }

    ////////////////////////////////////////////////////////////
    /** @brief Converts a platform identifier to a plain string.
    **/
    ////////////////////////////////////////////////////////////
    static const char* ToString(const int& platform)
    {
        if(platform == Unknown) return "Unknown";
        if(platform == Windows) return "Windows";
        if(platform == WindowsCE) return "WindowsCE";
        if(platform == Linux) return "Linux";
        if(platform == Apple) return "Apple";
        return "Bad platform id !";
    }

    ////////////////////////////////////////////////////////////
    /** @brief Tells if build is in debug mode.
    **/
    ////////////////////////////////////////////////////////////
    static bool IsDebugMode()
    {
#if APRO_DEBUG == APRO_ON
        return true;
#else
        return false;
#endif // APRO_DEBUG
    }
};

// Basic directory functions
#if APRO_PLATFORM == APRO_WINDOWS
#include <io.h>

// On Windows we have to implement a basic opendir/readdir/closedir
// functions to be more Posix-complient.

struct dirent {
    char d_name[BUFSIZ];
    Id   d_ino;
};

typedef struct {
    struct _finddata_t _data;
    char*              _first_entry_code;
    int                _cur_id;
    int                _handle;
    struct dirent      _entry;
} DIR;

extern "C" DIR*           opendir  (const char * _dir_name);
extern "C" int            closedir (DIR* _dir_p);
extern "C" struct dirent* readdir  (DIR* _dir_p);
extern "C" void           rewinddir(DIR* _dir_p);

#endif // WINDOWS

#endif // APROPLATFORM_H
