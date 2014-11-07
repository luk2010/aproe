/////////////////////////////////////////////////////////////
/** @file FileStream.h
 *  @ingroup Utils
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 03/02/2013 - 07/04/2014
 *
 *  Defines the FileStream class.
 *
**/
/////////////////////////////////////////////////////////////
#ifndef APRO_FILESTREAM_H
#define APRO_FILESTREAM_H

#include "StreamInterface.h"
#include "File.h"

#include "UTF8String.h"

namespace APro
{
    /////////////////////////////////////////////////////////////
    /** @class FileStream
     *  @ingroup Utils
     *  @brief A stream associated to a File.
     *
     *  Use this stream to interact easily with already opened
     *  File. No-opened files will always be wrong.
     *
     *  @sa InputStream, OutputStream, File
    **/
    /////////////////////////////////////////////////////////////
    class FileStream : public InputStream,
                       public OutputStream
    {
    protected:

        FilePtr m_file;

    public:

        /////////////////////////////////////////////////////////////
        /** @brief Constructs an empty Stream.
         *  @note You must set a correct opened File object to use this
         *  stream.
        **/
        /////////////////////////////////////////////////////////////
        FileStream();

        /////////////////////////////////////////////////////////////
        /** @brief Constructs a FileStream with the same file object as
         *  given one.
        **/
        /////////////////////////////////////////////////////////////
        FileStream(FileStream& f_stream);

        /////////////////////////////////////////////////////////////
        /** @brief Constructs a Stream with given File.
         *
         *  This File object must be already opened.
        **/
        /////////////////////////////////////////////////////////////
        explicit FileStream(File& f);

        /////////////////////////////////////////////////////////////
        /** @brief Destructs the Stream.
         *  @note It doesn't close the file object.
        **/
        /////////////////////////////////////////////////////////////
        ~FileStream();

    public:

        /////////////////////////////////////////////////////////////
        /** @brief Set the File object to given one.
         *  @return True if given file is valid and setted.
        **/
        /////////////////////////////////////////////////////////////
        bool set(File& f);

        /////////////////////////////////////////////////////////////
        /** @brief Set the File object to given one in FileStream.
         *  @return True if given file is valid and setted.
        **/
        /////////////////////////////////////////////////////////////
        bool set(FileStream& other);

        /////////////////////////////////////////////////////////////
        /** @brief Return the File object involved in this Stream.
        **/
        /////////////////////////////////////////////////////////////
        const FilePtr& toFilePtr() const;

        /////////////////////////////////////////////////////////////
        /** @brief Return the File object involved in this Stream.
        **/
        /////////////////////////////////////////////////////////////
        FilePtr& toFilePtr();

    public:

        // Copied from InputStream

        /////////////////////////////////////////////////////////////
        /** @brief Reads one character.
        **/
        /////////////////////////////////////////////////////////////
        bool readChar(char& to);

        /////////////////////////////////////////////////////////////
        /** @brief Reads a word.
        **/
        /////////////////////////////////////////////////////////////
        bool readWord(String& str);

        /////////////////////////////////////////////////////////////
        /** @brief Reads a line.
        **/
        /////////////////////////////////////////////////////////////
        bool readLine(String& str);

        /////////////////////////////////////////////////////////////
        /** @brief Reads untill one of the given character is reached.
        **/
        /////////////////////////////////////////////////////////////
        bool readUntill(String& str, ByteArray clist);

        /////////////////////////////////////////////////////////////
        /** @brief Reads a Real number.
        **/
        /////////////////////////////////////////////////////////////
        bool readReal(Real& r);

        /////////////////////////////////////////////////////////////
        /** @brief Reads an Integer.
        **/
        /////////////////////////////////////////////////////////////
        bool readInt(int& i);
        
        /////////////////////////////////////////////////////////////
        /** @brief Read a UTF8 Word in the file.
         *
         *  @note
         *  The given file must be in UTF8 mode. This is checked with
         *  the File::m_hasbom property (set to true if file has UTF8
         *  BOM). You also can make this property true if you are sure
         *  the file is encoded with UTF8, but does not have any BOM,
         *  using File::forceUTF8().
         *
         *  @param ret : Returned UTF8 CodePoint.
        **/
        /////////////////////////////////////////////////////////////
        bool readUTF8Char(UTF8Char::CodePoint& ret);
        
        /////////////////////////////////////////////////////////////
        /** @brief Read a UTF8 Word in the file.
         *  
         *  @note
         *  The given file must be in UTF8 mode. This is checked with
         *  the File::m_hasbom property (set to true if file has UTF8
         *  BOM). You also can make this property true if you are sure
         *  the file is encoded with UTF8, but does not have any BOM, 
         *  using File::forceUTF8(). 
         *
         *  @param str : The returned word. The word read is from the
         *  first encountered character ( UTF8Char::isText() ) to the first 
         *  space encountered after this character ( UTF8::isSpace() ), 
         *  limited to the given size. 
         *  @param maxsz : Max size of the word. If 0 (default value), 
         *  then no limit is given to the lenght of the word returned.
        **/
        /////////////////////////////////////////////////////////////
        bool readUTF8Word(UTF8String& str, size_t maxsz = 0);

        /////////////////////////////////////////////////////////////
        /** @brief Reads blanck characters to the next non-blanck
         *  one.
         *  @param c : [out] next non-blanck character.
         *  @return Number of blanck characters skipped. -1 if error
         *  occured.
        **/
        /////////////////////////////////////////////////////////////
        int skipBlanck(char& c);

    public:

        // Copied from OutputStream

        /////////////////////////////////////////////////////////////
        /** @brief Write a String.
        **/
        /////////////////////////////////////////////////////////////
        bool write(const String& str);

        /////////////////////////////////////////////////////////////
        /** @brief Write a Real.
        **/
        /////////////////////////////////////////////////////////////
        bool write(const Real& str);

        /////////////////////////////////////////////////////////////
        /** @brief Write an integer.
        **/
        /////////////////////////////////////////////////////////////
        bool write(const int& str);
        
        /////////////////////////////////////////////////////////////
        /** @brief Write an UTF8 CodePoint.
        **/
        /////////////////////////////////////////////////////////////
        bool write(const UTF8Char::CodePoint& cp);
        
        /////////////////////////////////////////////////////////////
        /** @brief Write an UTF8 String.
         **/
        /////////////////////////////////////////////////////////////
        bool write(const UTF8String& str);

    public:

        // Copied from CursorStream

        /////////////////////////////////////////////////////////////
        /** @brief Returns true if End Of Stream (EOS) is reached.
        **/
        /////////////////////////////////////////////////////////////
        bool isEOS() const;

        /////////////////////////////////////////////////////////////
        /** @brief Returns the current position of the cursor in the
         *  Stream.
        **/
        /////////////////////////////////////////////////////////////
        size_t tell() const;

        /////////////////////////////////////////////////////////////
        /** @brief Set a new position for thhe cursor in the Stream.
        **/
        /////////////////////////////////////////////////////////////
        void seek(size_t pos, CursorPosition cp = CP_BEGIN);
    };
}

#endif // APRO_FILESTREAM_H
