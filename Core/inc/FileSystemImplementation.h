/** @file FileSystemImplementation.h
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 29/03/2013
 *
 *  @addtogroup Global
 *  @addtogroup IO
 *
 *  This file defines the FileSystem Implementation.
 *
**/
#ifndef APRO_FILESYSTEMIMPLEMENTATION_H
#define APRO_FILESYSTEMIMPLEMENTATION_H

#include "Implementation.h"

namespace APro
{
    /** @class FileSystemImplementation
      * @brief The default class to inherit to provide an implementation
      * of file system n different platform.
    **/
    class APRO_DLL FileSystemImplementation : public Implementation
    {
        APRO_DECLARE_SHAREDPOINTER_CLASS_TYPEDEF(FileSystemImplementation)

    public:

        const String getClassImplementation() const
        {
            return String("APro::FileSystem");
        }

    public:

        FileSystemImplementation()
        {

        }

        virtual ~FileSystemImplementation()
        {

        }

    public:

        virtual String generateRelative(const String& from, const String& path) const = 0;
        virtual String generateAbsolute(const String& base, const String& relativepath) const = 0;

        virtual bool isAbsolute(const String & path) const = 0;
        virtual bool isRelative(const String & path) const = 0;

        virtual char pathSeparator() const = 0;

        virtual bool copy(const String& source, const String& target) const = 0;
        virtual bool f_delete(const String& filepath) const = 0;
        virtual bool exists(const String& filepath) const = 0;

        virtual bool rename(const String& source, const String& target) const = 0;

    };
}

#endif // APRO_FILESYSTEMIMPLEMENTATION_H
