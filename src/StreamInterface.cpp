/** @file StreamInterface.cpp
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 03/02/2013
 *
 *  @addtogroup Global
 *
 *  This file defines the StreamInterface class.
 *
**/
#include "StreamInterface.h"

namespace APro
{
    StreamInterface::StreamInterface()
        : stringSeparator('.')
    {

    }

    StreamInterface::StreamInterface(const StreamInterface& other)
        : stringSeparator(other.stringSeparator)
    {

    }

    StreamInterface::~StreamInterface()
    {

    }

    StreamInterface& StreamInterface::operator << (char c)
    {
        writeChar(c);
        return *this;
    }

    StreamInterface& StreamInterface::operator<< (const char* str)
    {
        writeString(String(str));
        return *this;
    }

    StreamInterface& StreamInterface::operator << (const String& str)
    {
        writeString(str);
        return *this;
    }

    StreamInterface& StreamInterface::operator << (const Number& n)
    {
        writeNumber(n);
        return *this;
    }

    StreamInterface& StreamInterface::operator >> (char& c)
    {
        readChar(c);
        return *this;
    }

    StreamInterface& StreamInterface::operator >> (String& str)
    {
        readWord(str);
        return *this;
    }

    StreamInterface& StreamInterface::operator >> (Number& n)
    {
        readNumber(n);
        return *this;
    }

    StreamInterface& StreamInterface::setStringSeparator(char sep)
    {
        stringSeparator = sep;
        return *this;
    }

    char StreamInterface::getStringSeparator() const
    {
        return stringSeparator;
    }
}
