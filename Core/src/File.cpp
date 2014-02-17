/** @file File.h
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 30/08/2012
 *
 *  @addtogroup Global
 *  @addtogroup Resource
 *
 *  This file defines the File resource.
 *
**/
#include "File.h"
#include "Main.h"
#include "FileSystem.h"

#include <stdio.h>
#include <sys/stat.h>

namespace APro
{
    File::File()
        : m_filePath(),
        m_endianness(Endianness::endianness()),
        m_openMode(OpenMode::ReadWrite),
        m_file(NULL)
    {

    }

    File::File(const File& other)
        : m_filePath(other.m_filePath),
        m_endianness(other.m_endianness),
        m_openMode(other.m_openMode),
        m_file(NULL)
    {

    }

    File::File(const String& filename)
        : m_filePath(filename),
        m_endianness(Endianness::endianness()),
        m_openMode(OpenMode::ReadWrite),
        m_file(NULL)
    {

    }

    File::File(const String& filename, OpenMode::t openmode)
        : m_filePath(filename),
        m_endianness(Endianness::endianness()),
        m_openMode(openmode),
        m_file(NULL)
    {

    }

    File::~File()
    {
        if(isOpened())
        {
            close();
        }
    }

    bool File::Copy(const String& newPath)
    {
        long int oldpos = -1;
        if(isOpened() &&  (long) getOpenMode() >= OpenMode::WriteOnly /* Writing enabled ? */ )
        {// Obliger de fermer le fichier.

            oldpos = tell();
            close();
        }

        FileSystem& fs = Main::Get().getFileSystem();
        bool ret = fs.copy(m_filePath, newPath);

        if(oldpos >= 0)
        {// On reouvre le fichier a la meme position

            open(m_openMode);
            seek(oldpos);
        }

        return ret;
    }

    bool File::Rename(const String& newPath)
    {
        if(isOpened())
        {
            close();
        }

        FileSystem& fs = Main::Get().getFileSystem();
        bool ret = fs.rename(m_filePath, newPath);
        setFile(newPath);
        return ret;
    }

    bool File::Delete()
    {
        if(isOpened())
        {
            close();
        }

        FileSystem& fs = Main::Get().getFileSystem();
        return fs.Delete(m_filePath);
    }

    bool File::open(OpenMode::t openmode)
    {
        if(isOpened())
        {
            close();
        }

        if(openmode != OpenMode::Current)
        {
            m_openMode = openmode;
        }

        switch ((int) m_openMode)
        {
        case OpenMode::ReadOnly :
            m_file = fopen(m_filePath.toCstChar(), "r");
            break;
        case OpenMode::WriteOnly :
            m_file = fopen(m_filePath.toCstChar(), "w");
            break;
        case OpenMode::ReadWrite :
            m_file = fopen(m_filePath.toCstChar(), "r+");
            break;
        case OpenMode::Truncate :
            m_file = fopen(m_filePath.toCstChar(), "w+");
            break;
        case OpenMode::Append :
            m_file = fopen(m_filePath.toCstChar(), "a+");
            break;
        }

        if(!m_file)
        {
            Main::Get().getConsole() << "\n[File]{open} Can't open file " << m_filePath << " !";
        }
        else
        {
            Main::Get().getConsole() << "\n[File]{open} Opened file " << m_filePath << ".";
        }

        m_lastOperation = Operation::None;
        return m_file != NULL;
    }

    void File::close()
    {
        if(isOpened())
        {
            fclose(m_file);
            m_file = NULL;
            m_lastOperation = Operation::None;
        }
    }

    void File::flush()
    {
        if(isOpened())
        {
            fflush(m_file);
            m_lastOperation = Operation::None;
        }
    }

    void File::clear()
    {
        if(isOpened())
        {
            close();
        }

        m_openMode = OpenMode::ReadWrite;
        m_endianness = Endianness::endianness();
        m_filePath.clear();
    }

    bool File::exists() const
    {
        if(isOpened())
        {
            return true;
        }

        FileSystem& fs = Main::Get().getFileSystem();
        return fs.exists(m_filePath);
    }

    bool File::isOpened() const
    {
        return m_file != NULL;
    }

    bool File::isEOF() const
    {
        if(isOpened())
        {
            return feof(m_file) != 0;
        }

        return false;
    }

    void File::setCursorPos(CursorPosition::t cp, Offset offset)
    {
        if(isOpened())
        {
            int origin;
            switch (cp)
            {
            case CursorPosition::AtBegin :
                origin = SEEK_SET;
                break;

            case CursorPosition::AtEnd :
                origin = SEEK_END;
                break;

            case CursorPosition::AtCurrent :
            default:
                origin = SEEK_CUR;
            }

            fseek(m_file, (long int) offset, origin);
        }
    }

    void File::seek(CursorPosition::t cp, Offset offset)
    {
        setCursorPos(cp, offset);
    }

    void File::setCursorPos(Offset offset)
    {
        if(isOpened())
        {
            fseek(m_file, offset, SEEK_SET);
        }
    }

    void File::seek(Offset offset)
    {
        setCursorPos(offset);
    }

    Offset File::getCursorPos() const
    {
        if(isOpened())
        {
            return (Offset) ftell(m_file);
        }

        return 0;
    }

    Offset File::tell() const
    {
        return getCursorPos();
    }

    Offset File::getSize() const
    {
        // Utilisation de stat
        struct FSTAT fstat;
        FSTAT(m_filePath.toCstChar(), &fstat);

        return fstat.st_size;
    }

    void File::setEndianness(Endianness::t e)
    {
        m_endianness = e;
    }

    Endianness::t File::getEndianness() const
    {
        return m_endianness;
    }

    void File::setFile(const String& filepath)
    {
        if(isOpened())
        {
            close();
        }

        m_filePath = filepath;
    }

    void File::setOpenMode(File::OpenMode::t om)
    {
        if(isOpened())
        {
            close();
        }

        m_openMode = om;
    }

    String File::getFile() const
    {
        return m_filePath;
    }

    File::OpenMode::t File::getOpenMode() const
    {
        return m_openMode;
    }

    String File::getDirectory() const
    {
        String dir = Main::get().getFileSystem().directoryOf(m_filePath);
        if(dir.isEmpty())
            return dir;

        return dir.extract(dir.findLast(Main::get().getFileSystem().pathSeparator()), dir.size());
    }

    String File::getPath() const
    {
        return Main::get().getFileSystem().directoryOf(m_filePath);
    }

    String File::getFileName() const
    {
        return m_filePath.extract(m_filePath.findLast(Main::get().getFileSystem().pathSeparator()), m_filePath.size());
    }

    String File::getFullPath() const
    {
        return Main::get().getFileSystem().absolutePath(m_filePath);
    }

    String File::getFilePath() const
    {
        return m_filePath;
    }

    void File::put(char c)
    {
        if(isOpened() && m_openMode >= OpenMode::WriteOnly)
        {
            write(&c, 1);
        }
    }

    void File::put(const String& str)
    {
        if(isOpened() && m_openMode >= OpenMode::WriteOnly)
        {
            write(str.toCstChar(), str.size());
        }
    }

    bool File::get(char& c)
    {
        if(isOpened())
        {
            return read(&c, 1);
        }

        return false;
    }

    void File::write(const char* bytes, size_t sz)
    {
        if(isOpened() && m_openMode >= OpenMode::WriteOnly)
        {
            if(m_lastOperation == Operation::Read)
            {
                flush();
            }

            if(fwrite(bytes, sizeof(char), sz, m_file) != sz)
            {
                Main::get().getConsole() << "\n[File]{write} Can't write " << (int) (sz * sizeof(char)) << " bytes to file " << getFileName() << " !";
            }

            m_lastOperation = Operation::Write;
        }
    }

    bool File::read(char* buffer, size_t sz)
    {
        if(isOpened())
        {
            if(m_lastOperation == Operation::Write)
            {
                flush();
            }

            m_lastOperation = Operation::Read;

            if(fread(buffer, sizeof(char), sz, m_file) != sz)
            {
                Main::get().getConsole() << "\n[File]{write} Can't read " << (int) (sz * sizeof(char)) << " bytes from file " << getFileName() << " !";
                return false;
            }

            return true;
        }

        return false;
    }
}
