/** @file StreamInterface.h
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 04/01/2013
 *
 *  @addtogroup Global
 *
 *  This file defines the StreamInterface class.
 *
**/
#ifndef APRO_STREAMINTERFACE_H
#define APRO_STREAMINTERFACE_H

#include "Platform.h"
#include "SString.h"
#include "Number.h"

namespace APro
{
    //! @class StreamInterface
    /** Interface to create stream. */
    class APRO_DLL StreamInterface
    {
    public:

        StreamInterface();
        StreamInterface(const StreamInterface& other);

        virtual ~StreamInterface();

    public:

        class Position
        {
        public:
            enum _
            {
                Begin,
                Current,
                End
            };
        };

    public:

        /** Add a character to the stream. */
        virtual void writeChar(char c) = 0;
        /** Add a string to the stream. */
        virtual void writeString(const String& c) = 0;
        /** Add a Number wit Real precision to the stream. */
        virtual void writeNumber(const Number& n) = 0;

        /** Read a character from the stream. */
        virtual void readChar(char& c) = 0;
        /** Read a string from the stream. */
        virtual void readString(String& str) = 0;
        /** Read a word, i.e. a set of character finished by characters ' ', EOL, EOF, or EOS. */
        virtual void readWord(String& str) = 0;
        /** Read a number from the stream. */
        virtual void readNumber(Number& n) = 0;

        StreamInterface& operator << (char c);
        StreamInterface& operator << (const char* str);
        StreamInterface& operator << (const String& str);
        StreamInterface& operator << (const Number& n);

        StreamInterface& operator >> (char& c);
        StreamInterface& operator >> (String& str);
        StreamInterface& operator >> (Number& n);

    public:

        /** Size of the stream. */
        virtual size_t size() const = 0;

        /** Set the position of the cursor in the stream. */
        virtual void seek(size_t pos, Position::_ relative = Position::Begin) = 0;

        /** Get Current cursor position in the stream. */
        virtual size_t tell() const = 0;

        /** Tell if end of stream. Equivalent to EOF when stream is file. */
        virtual bool isEOS() const = 0;

    protected:

        char stringSeparator;

    public:
        /** Set separator to read strings. By default, separator is the '.' character. Characters EOF and EOS are separators as well. */
        StreamInterface& setStringSeparator(char sep);
        /** Return the current String separator. */
        char getStringSeparator() const;
    };
}

#endif // APRO_STREAMINTERFACE_H
