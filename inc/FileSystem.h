/** @file FileSystem.h
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 05/07/2012
 *
 *  @addtogroup Global
 *  @addtogroup IO
 *
 *  This file defines the FileSystem Singleton.
 *
**/
#ifndef AROFILESYSTEM_H
#define AROFILESYSTEM_H

#include "Singleton.h"
#include "SString.h"
/*
namespace APro
{
    class APRO_DLL FileSystem : public Singleton<FileSystem>
    {
        friend class Singleton<FileSystem>;

    public:

        class OpenMode
        {
        public:
            enum _
            {
                ReadWrite,
                ReadOnly,
                WriteOnly
            };
        };

        class OpenOption
        {
        public:
            enum _
            {
                Append,
                Truncate,
                None
            };
        };

    protected:

        FileSystem();
        ~FileSystem();

    public:

        FileSystem& init(const String& base = String());

        File&       open(const String& filepath, OpenMode::_ om = ReadOnly, OpenOption::_ op = None);
        File&       create(const String& filepath);

        File&       getLaunchDirectory();

    private:

        String basepath;
    };
}
*/
#endif
