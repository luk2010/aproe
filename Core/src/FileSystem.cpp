/////////////////////////////////////////////////////////////
/** @file FileSystem.cpp
 *  @ingroup Utils
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 05/07/2012 - 27/02/2014
 *
 *  Implements the FileSystem class.
 *
**/
/////////////////////////////////////////////////////////////
#include "FileSystem.h"

namespace APro
{
    bool FileSystem::Exists(const String& path)
    {
#if APRO_PLATFORM == APRO_WINDOWS

        return PathFileExists((LPCTSTR) path.toCstChar()) == TRUE;

#else

        return access(path, F_OK) == 0;

#endif
    }

    bool FileSystem::IsDirectory(const String& path)
    {
#if APRO_PLATFORM == APRO_WINDOWS

        return PathIsDirectory((LPCTSTR) path.toCstChar()) == TRUE;

#else

        if(!FileSystem::Exists(path))
            return false;

        struct FSTAT s;
        if(FSTAT(path.toCstChar(), &s) == 0)
            return s.st_mode & S_IFDIR;
        else
            return false;

#endif // APRO_PLATFORM
    }

    bool FileSystem::IsFile(const String& path)
    {
        return !FileSystem::IsDirectory(path);
    }

    bool FileSystem::HasExtension(const String& path)
    {
        String filename = FileSystem::ExtractFilename(path);
        return filename.findFirst('.') == path.size();
    }

    char FileSystem::GetSeparator()
    {
        if(Platform::Get() == Platform::Windows ||
           Platform::Get() == Platform::WindowsCE)
            return '\\';
        else
            return '/';
    }

    String FileSystem::ExtractFilename(const String& path)
    {
        return path.extract(path.findLast(FileSystem::GetSeparator()), path.size());
    }

    String FileSystem::ExtractExtension(const String& path)
    {
        return path.extract(path.findLast('.'), path.size());
    }

    bool FileSystem::CreateFile(const String& path, bool overwrite)
    {
        if(FileSystem::Exists(path) &&
           !overwrite)
        {
            return false;
        }

        // We truncate the file and create it if it
        // doesn't exists.
        FILE* fp = fopen(path, "wb");
        if(fp)
        {
            fclose(fp);
            return true;
        }

        return false;
    }

    bool FileSystem::CreateDirectory(const String& path)
    {
        if(FileSystem::Exists(path))
            return true;

#if APRO_PLATFORM == APRO_WINDOWS

        return CreateDirectory((LPCTSTR) path.toCstChar()) == TRUE;

#else

        if(mkdir(path, S_IRWXG | S_IRWXO | S_IRWXU) == 0)
            return true;

        return false;

#endif
    }

    bool FileSystem::RemoveFile(const String& path)
    {
        if(!FileSystem::Exists(path))
            return true;

#if APRO_PLATFORM == APRO_WINDOWS

        return DeleteFile((LPCTSTR) path.toCstChar()) == TRUE;

#else

        return remove(path) == 0;

#endif
    }

    bool FileSystem::RemoveDirectory(const String& path, bool recursive)
    {
        if(!FileSystem::Exists(path))
            return true;

        Directory dir(path);
        if(dir.isValid())
        {
            if(!dir.isEmpty())
            {
                if(recursive)
                {
                    dir.makeEmpty();
                }
                else
                {
                    return false;
                }
            }

            dir.close();

#if APRO_PLATFORM == APRO_WINDOWS

            return RemoveDirectory((LPCTSTR) path.toCstChar()) == TRUE;

#else

            return rmdir(path);

#endif


        }

        return false;
    }

    bool FileSystem::CopyFile(const String& from, const String& to, bool failIfExists)
    {
#if APRO_PLATFORM == APRO_WINDOWS

        return CopyFile((LPCTSTR) from.toCstChar(), (LPCTSTR) to.toCstChar(), (BOOL) failIfExists) == TRUE;

#else

        if(failIfExists && FileSystem::Exists(to))
            return false;

        char buf[BUFSIZ];
        size_t size;

        int source = open(from.toCstChar(), O_RDONLY, 0);
        int dest   = open(to.toCstChar(), O_WRONLY | O_CREAT | O_TRUNC, 0644);

        if(source == -1 || dest == -1)
        {
            close(source);
            close(dest);
            return false;
        }

        while((size = read(source, buf, BUFSIZ)) > 0)
        {
            write(dest, buf, BUFSIZ);
        }

        close(source);
        close(dest);
        return true;

#endif // APRO_PLATFORM
    }

    String FileSystem::GetCurrentWorkingDirectory()
    {
#if APRO_PLATFORM == APRO_WINDOWS

        char wd[256];
        GetCurrentDirectory(256, wd);
        return String(wd);

#else

        char wd[256];
        getcwd(wd, 256);
        return String(wd);

#endif // APRO_PLATFORM
    }

    bool FileSystem::SetCurrentWorkingDirectory(const String& path)
    {
#if APRO_PLATFORM == APRO_WINDOWS

        return SetCurrentDirectory((LPCTSTR) path.toCstChar()) == TRUE;

#else

        return chdir(path) == 0;

#endif
    }

    bool FileSystem::IsRelative(const String& path)
    {
#if APRO_PLATFORM == APRO_WINDOWS

        return PathIsRelative((LPCTSTR) path.toCstChar()) == TRUE;

#else

        return !FileSystem::IsAbsolute(path);

#endif
    }

    bool FileSystem::IsAbsolute(const String& path)
    {
#if APRO_PLATFORM == APRO_WINDOWS

        return !FileSystem::IsRelative(path);

#else

        if(path.isEmpty()) return false;
        else if (path[0] == '~' && path[1] == '/') return true;
        else if (path[0] == '/') return true;
        else return false;

#endif
    }

    String FileSystem::GetAbsolutePath(const String& relative)
    {
#if APRO_PLATFORM == APRO_WINDOWS

        TCHAR  buffer[BUFSIZ] = TEXT("");
        TCHAR** lppPart       = { NULL };

        GetFullPathName(relative.toCstChar(), BUFSIZ, buffer, lppPart);
        return String(buffer);

#else

        char* actualpath = NULL;
        actualpath = realpath(relative.toCstChar(), NULL);
        if(actualpath)
        {
            String ret(actualpath);

            // This is a rare case where we must use free() instead
            // of AProFree. realpath(3) uses malloc() function to allocate
            // perfect buffer size.
            free(actualpath);
            return ret;
        }
        else
        {
            return String();
        }

#endif // APRO_PLATFORM
    }

    String FileSystem::GetHomeAbsolutePath()
    {
#if APRO_PLATFORM == APRO_WINDOWS

        char* buf[BUFSIZ];
        HANDLE hToken;

        if(!OpenProcessToken(GetCurrentProcess(), TOKEN_READ, &hToken))
            return String();

        GetUserProfileDirectory(hToken, buf, BUFSIZ);
        CloseHandle(hToken);
        return String(buf);

#else

        return String("~/");

#endif // APRO_PLATFORM
    }

}
