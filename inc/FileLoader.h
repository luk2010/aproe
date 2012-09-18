/** @file FileLoader.h
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 30/08/2012
 *
 *  @addtogroup Global
 *  @addtogroup Resource
 *
 *  This file defines the FileLoader class.
 *
**/
#ifndef APROFILELOADER_H
#define APROFILELOADER_H

#include "ResourceLoader.h"

namespace APro
{
    class APRO_DLL FileLoader : public ResourceLoader
    {
    public:

        FileLoader();
        FileLoader(const FileLoader& other);

        ~FileLoader();

        SharedPointer<Resource> loadResource(const String& filename);
    };
}

#endif
