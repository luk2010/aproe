/////////////////////////////////////////////////////////////
/** @file FileSystem.h
 *  @ingroup Utils
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 05/07/2012 - 26/12/2014
 *
 *  @brief
 *  Defines the FileSystem class.
 *
 *  @copyright
 *  Atlanti's Project Engine
 *  Copyright (C) 2012 - 2014  Atlanti's Corp
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
**/
/////////////////////////////////////////////////////////////
#ifndef AROFILESYSTEM_H
#define AROFILESYSTEM_H

#include "SString.h"
#include "File.h"

namespace APro
{
    /////////////////////////////////////////////////////////////
    /** @class FileSystem
     *  @ingroup Utils
     *  @brief A set of functions utilities for filesystem.
     *
     *  This implementation uses functions in common files in
     *  every operating system. So we are not dependant of
     *  operating systems.
     *
     *  @note On Windows systems, the specific Windows library is
     *  used to manipulate files.
    **/
    /////////////////////////////////////////////////////////////
    class APRO_DLL FileSystem
    {
    public:

        /////////////////////////////////////////////////////////////
        /** @brief Returns true if path exists (either file or
         *  directory).
        **/
        /////////////////////////////////////////////////////////////
        static bool Exists(const String& path);

        /////////////////////////////////////////////////////////////
        /** @brief Returns true if path exists and is a directory.
         *  @note A directory is a path without extension.
        **/
        /////////////////////////////////////////////////////////////
        static bool IsDirectory(const String& path);

        /////////////////////////////////////////////////////////////
        /** @brief Returns true if path exists and is a file.
         *  @note A file is a path with extension.
        **/
        /////////////////////////////////////////////////////////////
        static bool IsFile(const String& path);

        /////////////////////////////////////////////////////////////
        /** @brief Returns true if path has extension.
        **/
        /////////////////////////////////////////////////////////////
        static bool HasExtension(const String& path);

    public:

        /////////////////////////////////////////////////////////////
        /** @brief Returns '\' on Windows systems and '/' on others.
        **/
        /////////////////////////////////////////////////////////////
        static char GetSeparator();

        /////////////////////////////////////////////////////////////
        /** @brief Extract Filename from path.
        **/
        /////////////////////////////////////////////////////////////
        static String ExtractFilename(const String& path);

        /////////////////////////////////////////////////////////////
        /** @brief Extract Extension from path.
        **/
        /////////////////////////////////////////////////////////////
        static String ExtractExtension(const String& path);

    public:

        /////////////////////////////////////////////////////////////
        /** @brief Create a file.
         *
         *  @param path : Path to create the file. Can be relative or
         *  absolute.
         *  @param overwrite : True if you want to overwrite the file
         *  if it already exists.
         *  @return true on success.
        **/
        /////////////////////////////////////////////////////////////
        static bool CreateFile(const String& path, bool overwrite = false);

        /////////////////////////////////////////////////////////////
        /** @brief Create a directory.
         *
         *  @param path : Path to create the directory. Can be relative or
         *  absolute.
         *  @return true on success. Note that if directory already exists,
         *  this function returns true.
        **/
        /////////////////////////////////////////////////////////////
        static bool CreateDirectory(const String& path);

        /////////////////////////////////////////////////////////////
        /** @brief Remove a given file.
         *  @return True if file doesn't exists or on sucess.
        **/
        /////////////////////////////////////////////////////////////
        static bool RemoveFile(const String& path);

        /////////////////////////////////////////////////////////////
        /** @brief Remove a given directory.
         *  @param path : Path to directory.
         *  @param recursive : If set to false, only empty directory
         *  will be removed. If set to true, directory will be emptied
         *  before being removed.
        **/
        /////////////////////////////////////////////////////////////
        static bool RemoveDirectory(const String& path, bool recursive = false);

        /////////////////////////////////////////////////////////////
        /** @brief Copy file given from to file to.
         *  @param failIfExists : If file already exists, does the
         *  function fail (true) or overwrite it (false).
        **/
        /////////////////////////////////////////////////////////////
        static bool CopyFile(const String& from, const String& to, bool failIfExists = true);

    public:

        /////////////////////////////////////////////////////////////
        /** @brief Returns the current working directory.
        **/
        /////////////////////////////////////////////////////////////
        static String GetCurrentWorkingDirectory();

        /////////////////////////////////////////////////////////////
        /** @brief Set the current working directory.
        **/
        /////////////////////////////////////////////////////////////
        static bool SetCurrentWorkingDirectory(const String& path);

        /////////////////////////////////////////////////////////////
        /** @brief Returns true if path is relative.
         *
         *  @note On Unix-like systems, absolute path are beginning
         *  with '~/' for home and with '/' for root.
         *  Paths beginning with a letter or with '\' are relative.
        **/
        /////////////////////////////////////////////////////////////
        static bool IsRelative(const String& path);

        /////////////////////////////////////////////////////////////
        /** @brief Returns true if path is absolute.
         *
         *  @note On Unix-like systems, absolute path are beginning
         *  with '~/' for home and with '/' for root.
         *  Paths beginning with a letter or with '\' are relative.
        **/
        /////////////////////////////////////////////////////////////
        static bool IsAbsolute(const String& path);

        /////////////////////////////////////////////////////////////
        /** @brief Returns Absolute path from relative path.
         *  @note On Unix Systems, the path given must exists.
        **/
        /////////////////////////////////////////////////////////////
        static String GetAbsolutePath(const String& relative);

         /////////////////////////////////////////////////////////////
        /** @brief Returns Absolute path for home.
        **/
        /////////////////////////////////////////////////////////////
        static String GetHomeAbsolutePath();

    };
}

#endif
