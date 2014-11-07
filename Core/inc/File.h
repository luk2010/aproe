////////////////////////////////////////////////////////////
/** @file File.h
 *  @ingroup Utils
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 30/08/2012 - 07/11/2014
 *
 *  Defines the File class.
 *
**/
////////////////////////////////////////////////////////////
#ifndef APROFILE_H
#define APROFILE_H

#include "Platform.h"
#include "SString.h"
#include "AutoPointer.h"

namespace APro
{
    ////////////////////////////////////////////////////////////
    /** @class File
     *  @ingroup Utils
     *  @brief Represent a file. Use the Std API, and the File
     *  System to give information about files.
    **/
    ////////////////////////////////////////////////////////////
    class APRO_DLL File
    {

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Describe cursor position type.
        **/
        ////////////////////////////////////////////////////////////
        enum CursorPosition
        {
            C_BEGIN   = 0,///< Cursor is at the beginning of the file.
            C_CURRENT = 1,///< Cursor is at the current position.
            C_END     = 2 ///< Cursor is at the end of the file.
        };

    private:

        Path   m_file_path;      ///< Path to the file.
        FILE*  hFile;            ///< Handle to opened file.
        char*  m_open_mode;      ///< Open mode. Valid if file is opened.
        int    m_last_operation; ///< Last operation. -1 if no operation, 1 if read, 2 if write.
        bool   m_hasbom;         ///< True if file has valid UTF8 BOM. Initialized when file is opened.
        bool   m_saveutf8;       ///< True if file is saved using utf8 encoding.

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Default constructor.
        **/
        ////////////////////////////////////////////////////////////
        File();

        ////////////////////////////////////////////////////////////
        /** @brief Copy constructor.
         *  @note File is not opened.
        **/
        ////////////////////////////////////////////////////////////
        File(const File& other);

        ////////////////////////////////////////////////////////////
        /** @brief Constructs a file from his filename.
        **/
        ////////////////////////////////////////////////////////////
        File(const Path& filename);

        ////////////////////////////////////////////////////////////
        /** @brief Constructs a file and open it if file is valid.
        **/
        ////////////////////////////////////////////////////////////
        File(const Path& filename, const char* open_mode);

        ////////////////////////////////////////////////////////////
        /** @brief Destructs the file Close it if opened.
        **/
        ////////////////////////////////////////////////////////////
        ~File();

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Writes bytes Bytes of size sz to opened file.
        **/
        ////////////////////////////////////////////////////////////
        bool write(const Byte* bytes, size_t sz);
        template <typename T> bool write(const T& value)
        {
            return write(reinterpret_cast<const Byte*>(&value), sizeof(value));
        }

        ////////////////////////////////////////////////////////////
        /** @brief Read sz Bytes from opened file.
        **/
        ////////////////////////////////////////////////////////////
        bool read(Byte* buffer, size_t sz);
        template <typename T> bool read(T& buffer)
        {
            return read(reinterpret_cast<Byte*>(&buffer), sizeof(buffer));
        }

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Open the file with already given filename.
         *  @param open_mode : See the std documentation of fopen()
         *  for a complete list of open modes. By default it is 'rb'.
        **/
        ////////////////////////////////////////////////////////////
        bool open(const char* open_mode = "rb");

        ////////////////////////////////////////////////////////////
        /** @brief Open the file with given filename.
         *  @param filename : If file is already opened with another
         *  file, it il be closed and reopened with given one.
         *  @param open_mode : See the std documentation of fopen()
         *  for a complete list of open modes. By default it is 'rb'.
        **/
        ////////////////////////////////////////////////////////////
        bool open(const Path& filename, const char* open_mode = "rb");

        ////////////////////////////////////////////////////////////
        /** @brief Close the file if opened.
        **/
        ////////////////////////////////////////////////////////////
        bool close();

        ////////////////////////////////////////////////////////////
        /** @brief If opened, flush the file structure for i/o
         *  operations.
        **/
        ////////////////////////////////////////////////////////////
        bool flush();

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Returns true if file exists.
        **/
        ////////////////////////////////////////////////////////////
        bool exists() const;

        ////////////////////////////////////////////////////////////
        /** @brief Returns true if file is opened.
        **/
        ////////////////////////////////////////////////////////////
        bool isOpened() const;

        ////////////////////////////////////////////////////////////
        /** @brief Returns true if cursor is at EOF.
        **/
        ////////////////////////////////////////////////////////////
        bool isEOF() const;
        
        ////////////////////////////////////////////////////////////
        /** @brief Returns true if File has UTF8BOM.
         **/
        ////////////////////////////////////////////////////////////
        bool hasUTF8BOM() const { return m_hasbom; }

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Set the cursor to given offset from given position.
        **/
        ////////////////////////////////////////////////////////////
        void setCursorPos(CursorPosition cp, Offset offset = 0);

        ////////////////////////////////////////////////////////////
        /** @brief Set the cursor to given offset from given position.
        **/
        ////////////////////////////////////////////////////////////
        void seek(CursorPosition cp, Offset offset = 0);

        ////////////////////////////////////////////////////////////
        /** @brief Returns the current cursor position.
        **/
        ////////////////////////////////////////////////////////////
        Offset getCursorPos() const;

        ////////////////////////////////////////////////////////////
        /** @brief Returns the current cursor position.
        **/
        ////////////////////////////////////////////////////////////
        Offset tell() const;

        ////////////////////////////////////////////////////////////
        /** @brief Returns the file size.
        **/
        ////////////////////////////////////////////////////////////
        Offset getSize() const;

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Return the directory object for parent's directory.
        **/
        ////////////////////////////////////////////////////////////
        Directory getDirectory() const;

        ////////////////////////////////////////////////////////////
        /** @brief Returns file name without directory path.
        **/
        ////////////////////////////////////////////////////////////
        String getFileName() const;

        ////////////////////////////////////////////////////////////
        /** @brief Returns file name with directory path.
        **/
        ////////////////////////////////////////////////////////////
        String getFullPath() const;
        
        ////////////////////////////////////////////////////////////
        /** @brief Set the m_saveutf8 property.
         *  
         *  It should be set to true if you want your file to be written
         *  with UTF8 BOM.
         *  This BOM is added to the beginning of the file, when a call
         *  to close() is performed.
        **/
        ////////////////////////////////////////////////////////////
        void setUtf8Writing(bool utf8writing) { m_saveutf8 = utf8writing; }
        
        ////////////////////////////////////////////////////////////
        /** @brief Force the file to read in mode UTF8. 
         *  @note This option is not necessary if file contains a 
         *  UTF8 BOM.
        **/
        ////////////////////////////////////////////////////////////
        void forceUTF8(bool force) { m_hasbom = force ? force : m_hasbom; }
        
    private:
        
        void readbom ();
        void writebom ();
        
    public:

        static File Invalid; ///< An invalid file descriptor.
    };

    typedef AutoPointer<File> FilePtr;
}

#endif
