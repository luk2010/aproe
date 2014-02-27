////////////////////////////////////////////////////////////
/** @file File.h
 *  @ingroup Utils
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 30/08/2012 - 23/02/2014
 *
 *  Implements the File class.
 *
**/
////////////////////////////////////////////////////////////
#include "File.h"
#include "FileSystem.h"

namespace APro
{
    File::File()
        : m_file_path(), hFile(nullptr), m_open_mode(nullptr), m_last_operation(-1)
    {

    }

    File::File(const File& other)
        : m_file_path(other.m_file_path), hFile(nullptr), m_open_mode(nullptr), m_last_operation(-1)
    {

    }

    File::File(const Path& filename)
        : m_file_path(filename), hFile(nullptr), m_open_mode(nullptr), m_last_operation(-1)
    {

    }

    File::File(const Path& filename, const char* open_mode)
        : m_file_path(filename), hFile(nullptr), m_open_mode(nullptr), m_last_operation(-1)
    {
        open(open_mode);
    }

    File::~File()
    {
        if(isOpened())
            close();
    }

    bool File::write(const Byte* bytes, size_t sz)
    {
        if(isOpened())
        {
            if(m_last_operation == 1)
                flush();

            bool ret = true;
            if(fwrite(bytes, sizeof(Byte), sz, hFile) != sz)
            {
                Main::get().getConsole() << "\n[File]{write} Can't write '" << (int) (sz * sizeof(Byte)) << "' bytes to file '" << getFilename() << "' !";
                ret = false;
            }

            m_last_operation = 2;
            return ret;
        }

        return false;
    }

    bool File::read(Byte* buffer, size_t sz)
    {
        if(isOpened())
        {
            if(m_last_operation == 2)
                flush();

            bool ret = true;
            if(fread(buffer, sizeof(Byte), sz, hFile) != sz)
            {
                Main::get().getConsole() << "\n[File]{write} Can't read '" << (int) (sz * sizeof(Byte)) << "' bytes from file '" << getFilename() << "' !";
                ret = false;
            }

            m_last_operation = 1;
            return ret;
        }

        return false;
    }

    bool File::open(const char* open_mode)
    {
        if(isOpened())
            close();

        if(open_mode)
        {
            int sz = String::Size(open_mode);
            m_open_mode = AProAllocate(sizeof(char) * sz);
            Memory::Copy(m_open_mode, open_mode);
        }
        else
        {
            m_open_mode = AProAllocate(sizeof(char) * 3);
            m_open_mode[0] = 'r'; m_open_mode[1] = 'b'; m_open_mode[2] = '\0';
        }

        hFile = fopen(m_file_path.toCstChar(), m_open_mode);
        if(!hFile)
        {
            aprodebug("Can't open file path '") << m_file_path << "'.";
            AProDeallocate(m_open_mode);
            m_open_mode = nullptr;
            hFile = nullptr;
            return false;
        }

        m_last_operation = -1;
        return true;
    }

    bool File::open(const String& filename, const char* open_mode)
    {
        if(isOpened())
            close();

        if(open_mode)
        {
            int sz      = String::Size(open_mode);
            m_open_mode = AProAllocate(sizeof(char) * sz);
            Memory::Copy(m_open_mode, open_mode);
        }
        else
        {
            m_open_mode    = AProAllocate(sizeof(char) * 3);
            m_open_mode[0] = 'r';
            m_open_mode[1] = 'b';
            m_open_mode[2] = '\0';
        }

        hFile = fopen(filename.toCstChar(), m_open_mode);
        if(!hFile)
        {
            aprodebug("Can't open file path '") << m_file_path << "'.";
            AProDeallocate(m_open_mode);
            m_open_mode = nullptr;
            hFile       = nullptr;
            return false;
        }

        m_file_path      = filename;
        m_last_operation = -1;
        return true;
    }

    bool File::close()
    {
        if(!isOpened())
            return true;

        bool ret = true;
        if(fclose(hFile) != 0)
        {
            aprodebug("Can't close file '") << m_file_path << "'.";
            ret = false;
        }

        if(m_open_mode)
        {
            AProDeallocate(m_open_mode);
            m_open_mode = nullptr;
        }

        hFile = nullptr;
        m_last_operation = -1;
        return ret;
    }

    bool File::flush()
    {
        return fflush(hFile) == 0;
    }

    bool File::exists() const
    {
        if(isOpened())
            return true;

        return FileSystem::Exists(m_file_path);
    }

    bool File::isOpened() const
    {
        return hFile != nullptr;
    }

    bool File::isEOF() const
    {
        if(isOpened())
            return feof(hFile) != 0;

        return false;
    }

    void File::setCursorPos(CursorPosition cp, Offset offset)
    {
        if(isOpened())
        {
            int origin;
            switch (cp)
            {
            case C_BEGIN:
                origin = SEEK_SET;
                break;

            case C_END:
                origin = SEEK_END;
                break;

            case C_CURRENT:
            default:
                origin = SEEK_CUR;
            }

            fseek(hFile, (long int) offset, origin);
        }
    }

    void File::seek(CursorPosition cp, Offset offset)
    {
        setCursorPos(cp, offset);
    }

    Offset File::getCursorPos() const
    {
        if(isOpened())
            return (Offset) ftell(hFile);

        return -1;
    }

    Offset File::tell() const
    {
        return getCursorPos();
    }

    Offset File::getSize() const
    {
        if(isOpened())
        {
            Offset cur = tell();
            seek(C_END);
            Offset ret = tell();
            seek(C_BEGIN, cur);
            return ret;
        }

        return -1;
    }

    Directory File::getDirectory()
    {
        if(m_file_path.isEmpty())
            return Directory::Invalid;

        return Directory(m_file_path);
    }

    String File::getFileName() const
    {
        return m_file_path.getLastElement();
    }

    String File::getFullPath() const
    {
        return m_file_path.toString();
    }

    File File::Invalid = File(Path::Invalid);
}
