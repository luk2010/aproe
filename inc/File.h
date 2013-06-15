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
#ifndef APROFILE_H
#define APROFILE_H

#include "Platform.h"
#include "Resource.h"
#include "Array.h"
#include "SString.h"
#include "SharedPointer.h"
#include "Number.h"

namespace APro
{
    /** @class File
      * @brief Represent a file. Use the Std API, and the File System to give information
      * about files.
      * @note A valid File System must be avalaible.
    **/
    class APRO_DLL File
    {
        APRO_DECLARE_SHAREDPOINTER_CLASS_TYPEDEF(File)

    public:

        class CursorPosition
        {
        public:
            enum t
            {
                AtBegin     = 0x00,
                AtCurrent   = 0x01,
                AtEnd       = 0x02
            };
        };

        class OpenMode
        {
        public:
            enum t
            {
                Current     = 0x00, // Default open mode

                ReadOnly    = 0x01, // Read-Only open mode
                WriteOnly   = 0x02,

                ReadWrite   = 0x04,

                Truncate    = 0x08, // Create new file and overwrite it if already exists.
                Append      = 0x10  // Set cursor to end
            };
        };

    public:

        File();
        File(const File& other);
        File(const String& filename);
        File(const String& filename, OpenMode::t openMode);

        ~File();

    public:

        bool Copy(const String& newPath);
        bool Rename(const String& newPath);
        bool Delete();

        bool open(OpenMode::t openMode = OpenMode::Current);
        void close();

        void flush();
        void clear();

    public:

        bool exists() const;
        bool isOpened() const;
        bool isEOF() const;

    public:

        void setCursorPos(CursorPosition::t cp, Offset offset = 0);
        void seek(CursorPosition::t cp, Offset offset = 0);
        void setCursorPos(Offset offset);
        void seek(Offset offset);

        Offset getCursorPos() const;
        Offset tell() const;
        Offset getSize() const;

    public:

        void setEndianness(Endianness::t e);
        Endianness::t getEndianness() const;

    public:

        void setFile(const String& filepath);
        void setOpenMode(OpenMode::t om);

        String getFile() const;
        OpenMode::t getOpenMode() const;

    public:
        /** Give only the name of the directory. To get the directory path, use getPath(). */
        String getDirectory() const;
        /** Give the path to the file, without the filename. */
        String getPath() const;
        /** Give the filename without the path. */
        String getFileName() const;
        /** Give the filename with the path. */
        String getFullPath() const;
        /** Give the filepath you gave. */
        String getFilePath() const;

    public:

        void put(char c);
        void put(const String& str);

        bool get(char& c);

        void write(const char* bytes, size_t sz);
        template <typename T> void write(const T& value)
        {
            write(reinterpret_cast<const char*>(&value), sizeof(value));
        }

        /** Basic function to read bytes in file. */
        bool read(char* buffer, size_t sz);
        template <typename T> bool read(T& buffer)
        {
            return read(reinterpret_cast<char*>(&buffer), sizeof(buffer));
        }

    protected:

        class Operation
        {
        public:
            enum t
            {
                Write,
                Read,
                None
            };
        };

    protected:

        String          m_filePath;
        Endianness::t   m_endianness;
        OpenMode::t     m_openMode;
        FILE*           m_file;
        Operation::t    m_lastOperation;
    };
}

#endif
