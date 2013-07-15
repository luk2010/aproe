/** @file StringStream.h
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
#ifndef APRO_STRINGSTREAM_H
#define APRO_STRINGSTREAM_H

#include "StreamInterface.h"
#include "SString.h"

namespace APro
{
    class APRO_DLL StringStream : public StreamInterface
    {
    public:

        explicit StringStream(String* str);
        StringStream(StringStream& ss);

        virtual ~StringStream();

    private:

        size_t mcursor;
        String* mstr;

    public:

        void set(String& str);
        void set(StringStream& ss);

        const String& str() const;
        String& str();

    public:

        /** Add a character to the stream. */
        virtual void writeChar(char c);
        /** Add a string to the stream. */
        virtual void writeString(const String& c);
        /** Add a Number wit Real precision to the stream. */
        virtual void writeNumber(const Number& n);

        /** Read a character from the stream. */
        virtual void readChar(char& c);
        /** Read a string from the stream. */
        virtual void readString(String& str);
        /** Rpead a word, i.e. a set of character finished by characters ' ', EOL, EOF, or EOS. */
        virtual void readWord(String& str);
        /** Read a number from the stream. */
        virtual void readNumber(Number& n);

    public:

        virtual size_t size() const;
        virtual bool isEOS() const;

        virtual void seek(size_t pos, Position::_ relative = Position::Begin);
        virtual size_t tell() const;
    };
}

#endif // APRO_STRINGSTREAM_H
