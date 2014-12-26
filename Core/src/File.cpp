////////////////////////////////////////////////////////////
/** @file File.h
 *  @ingroup Utils
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 30/08/2012 - 04/11/2014
 *
 *  Implements the File class.
 *
**/
////////////////////////////////////////////////////////////
#include "File.h"
#include "FileSystem.h"
#include "UTF8String.h"

namespace APro
{
    File::File()
    : m_file_path(), hFile(nullptr), m_open_mode(nullptr), m_last_operation(-1), m_hasbom(false), m_saveutf8(false)
    {

    }

    File::File(const File& other)
        : m_file_path(other.m_file_path), hFile(nullptr), m_open_mode(nullptr), m_last_operation(-1), m_hasbom(false), m_saveutf8(false)
    {

    }

    File::File(const Path& filename)
        : m_file_path(filename), hFile(nullptr), m_open_mode(nullptr), m_last_operation(-1), m_hasbom(false), m_saveutf8(false)
    {

    }

    File::File(const Path& filename, const char* open_mode)
        : m_file_path(filename), hFile(nullptr), m_open_mode(nullptr), m_last_operation(-1), m_hasbom(false), m_saveutf8(false)
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
                Console::Get() << "\n[File]{write} Can't write '" << (int) (sz * sizeof(Byte)) << "' bytes to file '" << getFileName() << "' !";
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
                Console::Get() << "\n[File]{write} Can't read '" << (int) (sz * sizeof(Byte)) << "' bytes from file '" << getFileName() << "' !";
                ret = false;
            }

            m_last_operation = 1;
            return ret;
        }

        return false;
    }
    
    void File::readbom()
    {
        // Try to read UTF8 BOM
        UTF8Char::BOM bom;
        if(!read(&bom, sizeof(bom)))
            m_hasbom = false;
        
        if (bom.byte1 == UTF8Char::CPBOM.byte1 &&
            bom.byte2 == UTF8Char::CPBOM.byte2 &&
            bom.byte3 == UTF8Char::CPBOM.byte3) {
            m_hasbom = true;
            
            // If we found BOM, skip it as user doesn't want to
            // see it.
        }
        
        else
        {
            // Now we have to rewind file cursor.
            seek (C_BEGIN);
        }
    }
    
    void File::writebom()
    {
        if(isOpened())
        {
            seek(C_BEGIN);
            write(&UTF8Char::CPBOM, sizeof(UTF8Char::CPBom));
        }
    }

    bool File::open(const char* open_mode)
    {
        if(isOpened())
            close();

        if(open_mode)
        {
            int sz = String::Size(open_mode) + 1;
            m_open_mode = (char*) AProAllocate(sizeof(char) * sz);
            Memory::Copy(m_open_mode, open_mode, sz);
        }
        else
        {
            m_open_mode = (char*) AProAllocate(sizeof(char) * 3);
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
        
        readbom();
        m_last_operation = -1;
        return true;
    }

    bool File::open(const Path& filename, const char* open_mode)
    {
        if(isOpened())
            close();

        if(open_mode)
        {
            int sz      = String::Size(open_mode) + 1;
            m_open_mode = (char*) AProAllocate(sizeof(char) * sz);
            Memory::Copy(m_open_mode, open_mode, sz);
        }
        else
        {
            m_open_mode    = (char*) AProAllocate(sizeof(char) * 3);
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
        
        readbom();
        m_last_operation = -1;
        return true;
    }

    bool File::close()
    {
        if(!isOpened())
            return true;
        
        if(m_saveutf8)
            writebom();

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
            File* _this = const_cast<File*>(this);
            Offset cur = _this->tell();
            _this->seek(C_END);
            Offset ret = _this->tell();
            _this->seek(C_BEGIN, cur);
            return ret;
        }

        return -1;
    }

    Directory File::getDirectory() const
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
        return m_file_path;
    }

    File File::Invalid = File(Path::Invalid);
}
