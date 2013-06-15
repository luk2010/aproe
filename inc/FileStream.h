/** @file FileStream.h
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
#ifndef APRO_FILESTREAM_H
#define APRO_FILESTREAM_H

#include "StreamInterface.h"
#include "File.h"

namespace APro
{
    class FileStream : public StreamInterface
    {
    public:

        FileStream();
        explicit FileStream(const File::ptr& f);
        FileStream(const FileStream& other);

        virtual ~FileStream();

    public:

        void set(const File::ptr& f);
        void set(const FileStream& other);

        const File::ptr& file() const;
        File::ptr& file();

    protected:

        File::ptr mfile;

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
        /** Read a word, i.e. a set of character finished by characters ' ', EOL, EOF, or EOS. */
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

#endif // APRO_FILESTREAM_H
