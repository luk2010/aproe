/** @file Platform.h
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 21/05/2012 - 29/05/2012
 *
 *  @addtogroup Global
 *  @addtogroup Memory
 *
 *  This file defines some constants to be used on different platform. This constants are Memory-specific.
 *
**/
#ifndef APROPLATFORM_H
#define APROPLATFORM_H

/** Complete version name of the @ref Memory Module. */
#define APRO_MEMORY_VERSION "0.1A"

#include "Base.h"

#if APRO_EXCEPTION == APRO_ON
#   include "Exception.h"
#endif

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

    static const int get()
    {
#if APRO_PLATFORM == APRO_WINDOWS
        return (int) Windows;
#elif APRO_PLATFORM == APRO_WINDOWSCE
        return (int) WindowsCE;
#elif APRO_PLATFORM == APRO_LINUX
        return (int) Linux;
#elif APRO_PLATFORM == APRO_OSX
        return (int) Apple;
#endif
       return Unknown;
    }

    static const char* toString(const int& platform)
    {
        if(platform == Unknown) return "Unknown";
        if(platform == Windows) return "Windows";
        if(platform == WindowsCE) return "WindowsCE";
        if(platform == Linux) return "Linux";
        if(platform == Apple) return "Apple";
        return "Bad platform id !";
    }
};

#endif
