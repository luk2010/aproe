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

#include "SString.h"
#include "Implementable.h"
#include "Implementation.h"
#include "SharedPointer.h"
#include "File.h"
#include "FileSystemImplementation.h"

namespace APro
{
    /** @class FileSystem
      * @brief Main-generated class able to give access to files.
      * @note A platform-dependant implementation is required
      * to use this class. If none provided, no files will be used !
      * @note The file system is based on a path and can use relative path to open
      * files.
    **/
    class APRO_DLL FileSystem : public Implementable<FileSystemImplementation>
    {
        APRO_DECLARE_SHAREDPOINTER_CLASS_TYPEDEF(FileSystem)

    public:

        FileSystem(const String& basepath);
        FileSystem(const FileSystem& other);

        ~FileSystem();

        void clear();

    public:

        void setBasePath(const String & basepath);
        String getBasePath() const;

    public:

        String getRelativePath(const String & absolutepath) const;
        File::ptr get(const String& path, bool relative = true);

    public:

        String   absolutePath(const String& filepath) const;
        bool     isAbsolutePath(const String& filepath) const;

        String   directoryOf(const String& filepath) const;
        String   normalizePath(const String& filepath, char sep) const;
        String   normalizeSeparators(const String& filepath, char sep) const;

        bool     copy(const String& source, const String& target);
        bool     Delete(const String& filepath);
        bool     exists(const String& filepath) const;

        bool     rename(const String& source, const String& target);

        char     pathSeparator() const;

    public:

        static String extension(const String& filepath);
        static String getWorkingDirectory();
        static bool   setWorkingDirectory(const String& working_directory);

    protected:

        void initImplementation();

    protected:

        String m_basepath;
    };
}

#endif
