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
#include "Main.h"

#include <unistd.h>

namespace APro
{
    FileSystem::FileSystem(const String& basepath)
        : Implementable(String("APro::FileSystem")), m_basepath(basepath)
    {
        createImplementation();
        if(!isAbsolutePath(basepath))
        {
            Main::get().getConsole() << "\n[FileSystem] Initializing FileSystem with relative path \"" << basepath << "\" is dangerous !";
            setBasePath(absolutePath(basepath));
        }
    }

    FileSystem::FileSystem(const FileSystem& other)
        : Implementable(String("APro::FileSystem")), m_basepath(other.getBasePath())
    {
        createImplementation();
    }

    FileSystem::~FileSystem()
    {

    }

    void FileSystem::clear()
    {

    }

    void FileSystem::setBasePath(const String& basepath)
    {
        m_basepath = basepath;
    }

    String FileSystem::getBasePath() const
    {
        return m_basepath;
    }

    String FileSystem::getRelativePath(const String& absolutepath) const
    {
        if(!exists(absolutepath))
            return String();

        if(!implement.isNull())
        {
            return implement->generateRelative(m_basepath, absolutepath);
        }

        return String();
    }

    File::ptr FileSystem::get(const String& path, bool /* relative */)
    {
        //if(exists(path))
        {
            return File::ptr(AProNew(1, File) (path));
        }

        return File::ptr();
    }

    String FileSystem::absolutePath(const String& filepath) const
    {
        if(!exists(filepath))
            return String();

        if(!implement.isNull())
        {
            return implement->generateAbsolute(m_basepath, filepath);
        }

        return String();
    }

    bool FileSystem::isAbsolutePath(const String& filepath) const
    {
        if(filepath.isEmpty())
        {
            return false;
        }

        if(!implement.isNull())
        {
            return implement->isAbsolute(filepath);
        }

        return false;
    }

    String FileSystem::directoryOf(const String& filepath) const
    {
        String apath = absolutePath(filepath);
        if(!apath.isEmpty())
        {
            return apath.extract(0, apath.findLast(pathSeparator()));
        }

        return String();
    }

    String FileSystem::normalizePath(const String& filepath, char sep) const
    {
        String path = normalizeSeparators(filepath, sep);
        if(!isAbsolutePath(path))
        {
            path = absolutePath(path);
        }

        return path;
    }

    String FileSystem::normalizeSeparators(const String& filepath, char sep) const
    {
        if(!implement.isNull())
        {
            char ps = implement->pathSeparator();
            String ret(filepath);
            ret.replaceEvery(sep, ps);
            return ret;
        }

        return filepath;
    }

    bool FileSystem::copy(const String& source, const String& target)
    {
        if(!implement.isNull())
        {
            if(exists(source))
            {
                return implement->copy(source, target);
            }

            else
            {
                Main::get().getConsole() << "\n[FileSystem]{copy} Can't copy file \"" << source << "\" to file \"" << target << "\" because source path doesn't exist !";
            }
        }

        return false;
    }

    bool FileSystem::Delete(const String& filepath)
    {
        if(!implement.isNull())
        {
            if(exists(filepath))
            {
                return implement->f_delete(filepath);
            }

            else
            {
                Main::get().getConsole() << "\n[FileSystem]{delete} Can't delete file \"" << filepath << "\" because it doesn't exist !";
            }
        }

        return false;
    }

    bool FileSystem::exists(const String& filepath) const
    {
        if(!implement.isNull())
        {
            return implement->exists(filepath);
        }

        return false;
    }

    bool FileSystem::rename(const String& source, const String& target)
    {
        if(!implement.isNull())
        {
            if(exists(source))
            {
                return implement->rename(source, target);
            }

            else
            {
                Main::get().getConsole() << "\n[FileSystem]{delete} Can't rename file \"" << source << "\" because it doesn't exist !";
            }
        }

        return false;
    }

    char FileSystem::pathSeparator() const
    {
        if(!implement.isNull())
        {
            return implement->pathSeparator();
        }

        return '\\';
    }

    String FileSystem::extension(const String& filepath)
    {
        return filepath.extract(filepath.findLast('.') + 1, filepath.size() - 1);
    }

    void FileSystem::initImplementation()
    {

    }
    
    String FileSystem::getWorkingDirectory()
    {
        char working_dir[256];
        working_dir[255] = '\0';
        if(getcwd(working_dir, 256) == working_dir)
            return String(working_dir);
        else
            return String();
    }
    
    bool FileSystem::setWorkingDirectory(const String& working_directory)
    {
        return chdir(working_directory.toCstChar()) == 0;
    }
}
