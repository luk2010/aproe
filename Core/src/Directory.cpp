////////////////////////////////////////////////////////////
/** @file Directory.cpp
 *  @ingroup Utils
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 25/02/2014 - 06/05/2014
 *
 *  Implements the Directory class.
 *
**/
////////////////////////////////////////////////////////////
#include "Directory.h"
#include "Console.h"
#include "FileSystem.h"

namespace APro
{
    Directory::Directory()
        : m_dir_path(), hDir(nullptr)
    {
        m_skip_directory = false;
        m_skip_dot       = false;
        m_skip_files     = false;
    }

    Directory::Directory(const Directory& other)
        : m_dir_path(other.m_dir_path), hDir(nullptr)
    {
        m_skip_directory = false;
        m_skip_dot       = false;
        m_skip_files     = false;
    }

    Directory::Directory(const Path& dir_path)
        : m_dir_path(dir_path), hDir(nullptr)
    {
        m_skip_directory = false;
        m_skip_dot       = false;
        m_skip_files     = false;

        if(m_dir_path.exists())
            open();
    }

    Directory::~Directory()
    {
        if(isOpened())
            close();
    }

    bool Directory::open()
    {
        if(isOpened())
            return true;

        hDir = opendir(m_dir_path.toCstChar());
        if(!hDir)
        {
            aprodebug("Can't open directory '") << m_dir_path << "'.";
            return false;
        }

        return true;
    }

    bool Directory::open(const Path& path)
    {
        if(isOpened())
        {
            if(path != m_dir_path)
            {
                close();
            }
            else
            {
                return true;
            }
        }

        hDir = opendir(path.toCstChar());
        if(!hDir)
        {
            m_dir_path = Path::Invalid;
            aprodebug("Can't open directory '") << path << "'.";
            return false;
        }

        m_dir_path = path;
        return true;
    }

    bool Directory::close()
    {
        if(!isOpened())
            return true;

        if(closedir(hDir) != 0)
        {
            aprodebug("Can't close directory '") << m_dir_path << "'.";
            return false;
        }

        hDir = nullptr;
        return true;
    }

    bool Directory::isOpened() const
    {
        return hDir != nullptr;
    }

    void Directory::skipDirectory(bool skip)
    {
        m_skip_directory = skip;
    }

    void Directory::skipFiles(bool skip)
    {
        m_skip_files = skip;
    }

    void Directory::skipDot(bool skip)
    {
        m_skip_dot = skip;
    }

    int Directory::countEntries()
    {
        if(isOpened())
        {
            rewind();

            int i = 0;
            Entry e = next();
            while(!e.isEnd())
            {
                ++i;
                *this >> e;
            }

            rewind();
            return i;
        }

        return -1;
    }

    Directory::Entry Directory::next()
    {
        if(isOpened())
        {
            int err = errno;
            struct dirent* _e = readdir(hDir);
            if(!_e)
            {
                {
                    if(err == errno)
                    {
                        // end is reached
                        return Entry::End;
                    }
                    else
                    {
                        return Entry::Invalid;
                    }
                }
            }

            Entry ret;
            ret.name  = _e->d_name;
            ret.d_ino = _e->d_ino;
            return ret;
        }

        return Entry::Invalid;
    }

    bool Directory::operator >> (Entry& e)
    {
        if(isOpened())
        {
            int err = errno;
            struct dirent* _e = readdir(hDir);
            if(!_e)
            {
                {
                    if(err == errno)
                    {
                        // end is reached
                        e = Entry::End;
                        return false;
                    }
                    else
                    {
                        e = Entry::Invalid;
                        return false;
                    }
                }
            }

            e.name  = _e->d_name;
            e.d_ino = _e->d_ino;
            return true;
        }

        return false;
    }

    void Directory::rewind()
    {
        rewinddir(hDir);
    }

    bool Directory::isValid() const
    {
        return *this != Directory::Invalid;
    }

    bool Directory::isEmpty()
    {
        return countEntries() == 0;
    }

    void Directory::makeEmpty(bool recursive_mode)
    {
        if(isOpened())
        {
            Entry e = Entry::Invalid;
            while (e != Entry::End)
            {
                *this >> e;
                if(e == Entry::Invalid)
                    break;

                if (FileSystem::IsDirectory(e.name))
                    FileSystem::RemoveDirectory(e.name, recursive_mode);
                else
                    FileSystem::RemoveFile(e.name);

            }
        }
    }

    bool Directory::operator==(const Directory& other) const
    {
        return m_dir_path == other.m_dir_path;
    }

    Directory::Entry Directory::Entry::End     = { String("End"),     -1 };
    Directory::Entry Directory::Entry::Invalid = { String("Invalid"), -2 };
    Directory        Directory::Invalid        = Directory(Path::Invalid);
}
