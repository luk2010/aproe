////////////////////////////////////////////////////////////
/** @file Directory.h
 *  @ingroup Utils
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 23/02/2014 - 06/05/2014
 *
 *  Defines the Directory class.
 *
**/
////////////////////////////////////////////////////////////
#ifndef APRO_DIRECTORY_H
#define APRO_DIRECTORY_H

#include "Platform.h"
#include "SString.h"
#include "Path.h"

namespace APro
{
    ////////////////////////////////////////////////////////////
    /** @class Directory
     *  @ingroup Utils
     *  @brief A handle to a directory in the FileSystem.
     *
     *  This handle autoclose when it is destroyed, but to avoid
     *  resource leaks while program is running, you should use this
     *  class for local Directory objects, so at the scope-end,
     *  directory will be closed.
     *
     *  @warning Using this class while multithreaded is undefined
     *  behavior.
    **/
    ////////////////////////////////////////////////////////////
    class Directory
    {
    private:

        Path m_dir_path;       ///< Directory path.
        DIR* hDir;             ///< Handle to directory.

        bool m_skip_directory; ///< Should skip directories ?
        bool m_skip_dot;       ///< Should skip dots ?
        bool m_skip_files;     ///< Should skip files ?

    public:

        ////////////////////////////////////////////////////////////
        /** @struct Entry
         *  @brief Defines an Entry in the directory.
         *  @note This is a remplacement for struct dirent .
        **/
        ////////////////////////////////////////////////////////////
        typedef struct entry_t
        {
            String name; ///< Name of the entry (generally name of the file/directory).
            Id     d_ino;///< Identifier of the entry.

            static entry_t End;    ///< Entry end.
            static entry_t Invalid;///< Entry invalid.

            bool isValid() { return *this != entry_t::Invalid && !name.isEmpty(); }
            bool isEnd() { return *this != entry_t::End; }
            bool operator == (const entry_t& other) { return name == other.name && d_ino == other.d_ino; }
            bool operator != (const entry_t& other) { return !(*this == other); }

        } Entry;

        static Directory Invalid;///< The invalid directory.

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Constructs an empty directory.
        **/
        ////////////////////////////////////////////////////////////
        Directory();

        ////////////////////////////////////////////////////////////
        /** @brief Constructs a Directory from another, but do not open
         *  it.
        **/
        ////////////////////////////////////////////////////////////
        Directory(const Directory& other);

        ////////////////////////////////////////////////////////////
        /** @brief Constructs a Directory with given path.
         *  @note Directory is opened if path exists.
        **/
        ////////////////////////////////////////////////////////////
        Directory(const Path& dir_path);

        ////////////////////////////////////////////////////////////
        /** @brief Close and destroys the Directory.
        **/
        ////////////////////////////////////////////////////////////
        ~Directory();

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Open a handle to this directory.
        **/
        ////////////////////////////////////////////////////////////
        bool open();

        ////////////////////////////////////////////////////////////
        /** @brief Open a handle to given directory path.
        **/
        ////////////////////////////////////////////////////////////
        bool open(const Path& path);

        ////////////////////////////////////////////////////////////
        /** @brief Close the handle to this directory.
        **/
        ////////////////////////////////////////////////////////////
        bool close();

        ////////////////////////////////////////////////////////////
        /** @brief Returns true if handle is valid.
        **/
        ////////////////////////////////////////////////////////////
        bool isOpened() const;

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Should this directory skip directories entries
         *  when iterating through entries.
        **/
        ////////////////////////////////////////////////////////////
        void skipDirectory(bool skip);

        ////////////////////////////////////////////////////////////
        /** @brief Should this directory skip files entries
         *  when iterating through entries.
        **/
        ////////////////////////////////////////////////////////////
        void skipFiles(bool skip);

        ////////////////////////////////////////////////////////////
        /** @brief Should this directory skip '.' and '..' entries
         *  when iterating through entries.
        **/
        ////////////////////////////////////////////////////////////
        void skipDot(bool skip);

        ////////////////////////////////////////////////////////////
        /** @brief Return the number of entries in current directory.
         *  @warning Read every entries one by one then rewind the
         *  directory. You should not use this function after a call
         *  to next() as it goes to undefined behaviors.
        **/
        ////////////////////////////////////////////////////////////
        int countEntries();

        ////////////////////////////////////////////////////////////
        /** @brief Return true if different from Directory::Invalid.
        **/
        ////////////////////////////////////////////////////////////
        bool isValid() const;

        ////////////////////////////////////////////////////////////
        /** @brief Return true if directory is empty.
        **/
        ////////////////////////////////////////////////////////////
        bool isEmpty();

        ////////////////////////////////////////////////////////////
        /** @brief If not empty, make it so.
         *  @param recursive_mode : If set to true, delete also every
         *  folders by calling their Directory::makeEmpty() function.
        **/
        ////////////////////////////////////////////////////////////
        void makeEmpty(bool recursive_mode = true);

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Return next entry in this directory.
         *  @return Entry::End if end is reached, or Entry::Invalid
         *  if an error occured.
        **/
        ////////////////////////////////////////////////////////////
        Entry next();
        bool operator >> (Entry& e);

        ////////////////////////////////////////////////////////////
        /** @brief Rewind the directory.
        **/
        ////////////////////////////////////////////////////////////
        void rewind();

    public:

        bool operator == (const Directory& other) const;
        bool operator != (const Directory& other) const { return !(*this == other); }
    };
}

#endif // APRO_DIRECTORY_H
