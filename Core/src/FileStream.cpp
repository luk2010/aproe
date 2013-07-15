/** @file FileStream.cpp
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 03/02/2013
 *
 *  @addtogroup Global
 *
 *  This file defines the FileStream class.
 *
**/
#include "FileStream.h"

namespace APro
{
    FileStream::FileStream()
    {

    }

    FileStream::FileStream(const File::ptr& f)
        : mfile(f)
    {

    }

    FileStream::FileStream(const FileStream& other)
        : StreamInterface(), mfile(other.mfile)
    {
        seek(other.tell());
    }

    FileStream::~FileStream()
    {

    }

    void FileStream::set(const File::ptr& f)
    {
        mfile = f;
    }

    void FileStream::set(const FileStream& other)
    {
        mfile = other.mfile;
    }

    void FileStream::writeChar(char c)
    {
        if(!mfile.isNull())
        {
            mfile->put(c);
        }
    }

    void FileStream::writeString(const String& c)
    {
        if(!mfile.isNull())
        {
            mfile->put(c);
        }
    }

    void FileStream::writeNumber(const Number& n)
    {
        if(!mfile.isNull())
        {
            mfile->put(String::fromDouble(n.toReal()));
        }
    }

    void FileStream::readChar(char& c)
    {
        if(!mfile.isNull())
        {
            mfile->get(c);
        }
    }

    void FileStream::readWord(String& str)
    {
        if(!mfile.isNull())
        {
            str.clear();
            if(mfile->isEOF()) return;

            char c;
            while (mfile->get(c) &&
                   !(c == ' ') && !(c == '\n'))
            {
                str.append(c);
            }
        }
    }

    void FileStream::readString(String& str)
    {
        if(!mfile.isNull())
        {
            str.clear();
            if(mfile->isEOF()) return;

            char c;
            while (mfile->get(c) &&
                   !(c == stringSeparator))
            {
                str.append(c);
            }
        }
    }

    void FileStream::readNumber(Number& n)
    {
        if(!mfile.isNull())
        {
            if(mfile->isEOF()) return;

            String num; readWord(num);
            n.set(String::toDouble(num));
        }
    }

    size_t FileStream::size() const
    {
        if(!mfile.isNull())
            return mfile->getSize();
        else
            return 0;
    }

    bool FileStream::isEOS() const
    {
        if(!mfile.isNull())
            return mfile->isEOF();
        else
            return true;
    }

    void FileStream::seek(size_t pos, Position::_ relative)
    {
        if(!mfile.isNull())
        {
            File::CursorPosition::t p;
            switch(relative)
            {
            case Position::Begin:
                p = File::CursorPosition::AtBegin;
                break;

            case Position::End:
                p = File::CursorPosition::AtEnd;
                break;

            case Position::Current:
            default:
                p = File::CursorPosition::AtCurrent;
                break;
            }

            mfile->seek(p, (Offset) pos);
        }
    }

    size_t FileStream::tell() const
    {
        if(!mfile.isNull())
            return (size_t) mfile->tell();
        else
            return 0;
    }
}
