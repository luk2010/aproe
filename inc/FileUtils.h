/** @file FileUtils.h
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 27/08/2012
 *
 *  @addtogroup Global
 *  @addtogroup Memory
 *
 *  This file defines some utilities for Filenames.
 *
**/
#ifndef APROFILEUTILITIES_H
#define APROFILEUTILITIES_H

#include "Platform.h"
#include "SString.h"

namespace APro
{
    class APRO_DLL FileUtilities
    {
    private:
        FileUtilities()
        {

        }

        ~FileUtilities()
        {

        }

    public:

        static String normalize(const String& filename);
        static String extension(const String& filename);
        static String filenameWithoutExtension(const String& filename);
        static String filenameWithoutPath(const String& filename);
        static String path(const String& filename);
        static bool isDirectory(const String& filename);
    };
}

#endif
