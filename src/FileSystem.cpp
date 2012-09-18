/** @file FileSystem.cpp
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 13/07/2012
 *
 *  @addtogroup Global
 *  @addtogroup IO
 *
 *  This file defines the FileSystem Singleton.
 *
**/
#include "FileSystem.h"
/*
namespace APro
{
    FileSystem::FileSystem()
        : basepath("")
    {
    }

    FileSystem::~FileSystem()
    {
    }

    FileSystem& FileSystem::init(const String & base)
    {
        if(base.isEmpty())
        {
            char dossier[4096];
            getcwd(dossier, 4096);
            basepath = dossier;
        }
        else
        {
            basepath = base;
            chdir(base.toCstChar());
        }

        return *this;
    }

    File& FileSystem::create(const String & filepath)
    {
        return FileSystem::open(filepath, OpenMode::ReadWrite, OpenOption::Truncate);
    }

    File& FileSystem::open(const String& filepath, OpenMode::_ om, OpenOption::_ op)
    {

    }
}
*/
