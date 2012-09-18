/** @file FileLoader.cpp
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
#include "File.h"
#include "FileLoader.h"
#include <stdlib.h>
#include <stdio.h>

namespace APro
{
    FileLoader::FileLoader() : ResourceLoader()
    {
        setParam(String("Name"), Variant(String("FileLoader")));
        setParam(String("Description"), Variant(String("A loader that caches any file.")));
        setParam(String("IsManual"), Variant(true));
    }

    FileLoader::FileLoader(const FileLoader& other) : ResourceLoader(other)
    {
        setParam(String("IsManual"), other.getParam(String("IsManual")));
    }

    FileLoader::~FileLoader()
    {

    }

    SharedPointer<Resource> FileLoader::loadResource(const String& filename)
    {
        FILE* file = fopen(filename.toCstChar(), "r");
        if(!file)
        {
            Console::get() << "\n[FileLoader] Can't open file " << filename << " !";
            return SharedPointer<Resource>();
        }

        String f;
        int c = 0;
        while(c != EOF)
        {
            c = fgetc(file);
            f.append((char)c);
        };

        fclose(file);

        return SharedPointer<Resource>(AProNew(1, File) (String(), filename, f, File::OpenMode::ReadWrite));
    }
}
