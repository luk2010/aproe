/////////////////////////////////////////////////////////////
/** @file FileStream.cpp
 *  @ingroup Utils
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 03/02/2013 - 03/04/2014
 *
 *  Implements the FileStream class.
 *
**/
/////////////////////////////////////////////////////////////
#include "FileStream.h"

namespace APro
{
    FileStream::FileStream()
        : m_file(nullptr)
    {

    }

    FileStream::FileStream(FileStream& f_stream)
        : m_file(nullptr)
    {
        if(!f_stream.m_file.isNull() && f_stream.m_file->isOpened())
            m_file = f_stream.m_file;
    }

    FileStream::FileStream(File& f)
        : m_file(nullptr)
    {
        if(f.isOpened())
            m_file = &f;
    }

    FileStream::~FileStream()
    {
        // We do nothing as file object musn't be closed.
    }

    bool FileStream::set(File& f)
    {
        if(f.isOpened())
        {
            m_file = &f;
            return true;
        }

        return false;
    }

    bool FileStream::set(FileStream& other)
    {
        if(!other.m_file.isNull() && other.m_file->isOpened())
        {
            m_file = other.m_file;
            return true;
        }

        return false;
    }

    const FilePtr& FileStream::toFilePtr() const
    {
        return m_file;
    }

    FilePtr& FileStream::toFilePtr()
    {
        return m_file;
    }

    bool FileStream::readChar(char& to)
    {
        if(m_file.isNull() || !m_file->isOpened())
        {
            return false;
        }
        else
        {
            return m_file->read((unsigned char*) &to, sizeof(char));
        }
    }

    bool FileStream::readWord(String& str)
    {
        char c;
        if(m_file.isNull() || !m_file->isOpened())
            return false;

        if(skipBlanck(c) < 0)
            return false;

        while(isalpha((int) c))
        {
            str.append(c);
            if(!readChar(c))
                break;
        }

        return true;
    }

    bool FileStream::readUntill(String& str, ByteArray clist)
    {
        char c;
        if(m_file.isNull() || !m_file->isOpened())
            return false;

        if(!readChar(c))
            return false;

        while(!clist.contains((Byte) c))
        {
            str.append(c);
            if(!readChar(c))
                break;
        }

        return true;
    }

    bool FileStream::readReal(Real& r)
    {
        char c;
        if(m_file.isNull() || !m_file->isOpened())
            return false;

        ByteArray authorized_characters;
        authorized_characters << (Byte) '+' << (Byte) '-' << (Byte) '.' << (Byte) 'e' << (Byte) 'E';

        String real;
        if(skipBlanck(c) < 0)
            return false;

        while(isdigit(c) || authorized_characters.contains(c))
        {
            real.append(c);
            if(!readChar(c))
                break;
        }

        r = real.toReal();
        return true;
    }

    bool FileStream::readInt(int& i)
    {
        char c;
        if(m_file.isNull() || !m_file->isOpened())
            return false;

        String real;
        if(skipBlanck(c) < 0)
            return false;

        while(isdigit(c))
        {
            real.append(c);
            if(!readChar(c))
                break;
        }

        i = real.toInt();
        return true;
    }

    int FileStream::skipBlanck(char& c)
    {
        if(m_file.isNull() || !m_file->isOpened())
            return -1;

        int ret = 0;
        if(!readChar(c))
            return -1;
        while(isblank(c))
        {
            if(!readChar(c))
                return ret;
            ret++;
        }
        return ret;
    }

    bool FileStream::write(const String& str)
    {
        if(m_file.isNull() || !m_file->isOpened())
            return false;

        return m_file->write((const Byte*) str.toCstChar(), str.size());
    }

    bool FileStream::write(const Real& str)
    {
        if(m_file.isNull() || !m_file->isOpened())
            return false;

        return write(String::toString(str));
    }

    bool FileStream::write(const int& str)
    {
        if(m_file.isNull() || !m_file->isOpened())
            return false;

        return write(String::toString(str));
    }

    bool FileStream::isEOS() const
    {
        if(m_file.isNull())
            return false;
        return m_file->isEOF();
    }

    size_t FileStream::tell() const
    {
        if(m_file.isNull())
            return 0;
        return m_file->tell();
    }

    void FileStream::seek(size_t pos, CursorPosition cp)
    {
        if(m_file.isNull())
            return;
        m_file->seek( (File::CursorPosition) (File::C_BEGIN + (int) cp), (Offset) pos);
    }

}
