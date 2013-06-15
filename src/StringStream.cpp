/** @file StringStream.cpp
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 30/01/2013
 *
 *  @addtogroup Global
 *
 *  This file defines the StringStream class.
 *
**/
#include "StringStream.h"

namespace APro
{
    StringStream::StringStream(String* str)
        : mcursor(0), mstr(str)
    {

    }

    StringStream::StringStream(StringStream& ss)
        : StreamInterface(), mcursor(0), mstr(&(ss.str()))
    {

    }

    StringStream::~StringStream()
    {

    }

    void StringStream::set(String& str)
    {
        mcursor = 0;
        mstr = &str;
    }

    void StringStream::set(StringStream& ss)
    {
        mcursor = 0;
        mstr = &(ss.str());
    }

    const String& StringStream::str() const
    {
        return *mstr;
    }

    String& StringStream::str()
    {
        return *mstr;
    }

    void StringStream::writeChar(char c)
    {
        mstr->insert(mcursor + 1, c);
        mcursor++;
    }

    void StringStream::writeString(const String& c)
    {
        for(unsigned int i = 0; i < c.size(); ++i)
            writeChar(c[i]);
    }

    void StringStream::writeNumber(const Number& n)
    {
        double d = n.toReal();
        writeString(String::fromDouble(d));
    }

    void StringStream::readChar(char& c)
    {
        if(!isEOS())
        {
            c = mstr->at(mcursor);
            mcursor++;
        }
    }

    void StringStream::readString(String& str)
    {
        str.clear(); if(isEOS()) return;

        char c; readChar(c);
        while(!(c == stringSeparator))
        {
            str.append(c);

            if(isEOS()) break;
            readChar(c);
        }
    }

    void StringStream::readWord(String& str)
    {
        str.clear(); if(isEOS()) return;

        char c; readChar(c);
        while(!(c == ' ') && !(c == '\n'))
        {
            str.append(c);

            if(isEOS()) break;
            readChar(c);
        }
    }

    void StringStream::readNumber(Number& n)
    {
        String num;
        readWord(num);

        if(!num.isEmpty())
        {
            n.set(String::toDouble(num));
        }
    }

    size_t StringStream::size() const
    {
        return mstr->size();
    }

    bool StringStream::isEOS() const
    {
        return (mcursor + 1) >= mstr->size();
    }

    void StringStream::seek(size_t pos, Position::_ relative)
    {
        size_t fpos = pos;

        if(relative == Position::Current)
            fpos += mcursor;
        else if (relative == Position::End)
            fpos += size() - 1;

        if(fpos >= size()) fpos = size() - 1;

        mcursor = fpos;
    }

    size_t StringStream::tell() const
    {
        return mcursor;
    }
}
