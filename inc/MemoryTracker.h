/** @file MemoryTracker.h
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 21/05/2012 - 26/05/2012
 *
 *  @addtogroup Memory
 *
 *  This file defines the Memory Tracker.
 *
**/
#ifndef APROMEMORYTRACKER_H
#define APROMEMORYTRACKER_H

#include "Platform.h"

#if APRO_MEMORYTRACKER == APRO_ON

#include <map>
#include <string>

namespace APro
{
    /** @class MemoryTracker
     *
     *  This classe is used to store informations about allocations, desallocations and reallocations. It can store
     *  datas in a big buffer, and write it periodically, or it can also write informations live, but live-writing is
     *  very expensive and is not recommended for final applications.
     *  You can tell the tracker wich type of writing you want, wich file to write, and you can get live-informations to.
     *
     *  @addtogroup Memory
     *
     *  @note
     *  This is a singleton. No instance can be constructed by the user.
     *
     *  @remarks
     *  This class is stl-dependent, due to maps and arrays.
    **/
    class APRO_DLL MemoryTracker
    {
    private:

        /** Describe a Memory Block. */
        struct MemoryBlock
        {
            std::string func;
            std::string file;
            int         line;
            size_t      bytes;
        };

        typedef std::map<void*, MemoryBlock> MemoryBlockMap;

        /** Stores statistics. */
        struct MemoryStatistics
        {
            double  totalBytesAllocated;
            int     objectNumber;
        };

        /** Stores data about file. */
        struct MemoryFile
        {
            bool        liveWriting;
            std::string filename;
            FILE*       file;
        };

        /** Stores the stack. */
        struct MemoryStack
        {
            std::string dumper;
            std::string buffer;

            bool cutFilename;
                int maxSize;
            bool retain;
        };

    private:

        /** Global Constructor. */
        MemoryTracker();
        /** Destructor. */
        ~MemoryTracker();

    public:

        /** Get access to the global instance of the Memory Tracker. */
        static MemoryTracker* get();

    public:

        /** Reports a new allocation.
         *
         *  @param ptr : Pointer to the new memory block.
         *  @param byte : Amount of byte.
         *  @param func : Function where this one is called.
         *  @param file : File where this function is called.
         *  @param line : Line where this function is called.
         *
         *  @remarks
         *  This function is automaticly called by @ref APro::allocate and @ref APro::Allocator.
        **/
        void reportAllocation(void* ptr, size_t byte, const char* func, const char* file, int line);

        /** Reports a reallocation.
         *
         *  This function must be called to handle a reallocation of an old pointer to a new one,
         *  including byte size change.
         *
         *  @param ptr : old pointer.
         *  @param new_ptr : new pointer.
         *  @param byte : Amount of byte.
         *  @param func : Function where this one is called.
         *  @param file : File where this function is called.
         *  @param line : Line where this function is called.
         *
         *  @remarks
         *  This function is automaticly called by @ref APro::reallocate and @ref APro::Allocator.
         *
        **/
        void reportReallocation(void* ptr, void* new_ptr, size_t byte, const char* func, const char* file, int line);

        /** Reports a deallocation.
         *
         *  @param ptr : old pointer.
         *  @param func : Function where this one is called.
         *  @param file : File where this function is called.
         *  @param line : Line where this function is called.
         *
         *  @remarks
         *  This function is automaticly called by @ref APro::deallocate and @ref APro::Allocator.
         *
        **/
        void reportDeallocation(void* ptr, const char* func, const char* file, int line);

        /** Return the name of the file where the Memory Tracker logs informations. */
        std::string getFilename() const;
        /** Set the name of the file where the Memory Tracker logs informations.
         *
         *  This function reinitialize the stack, and write a header in the file.
         *
         *  @param filename : Name of the file.
        **/
        void setFilename(const std::string & filename);

        /** Tell if writing mode is to live or async. */
        bool isLiveWriting() const;
        /** Set writing mode. */
        void setLiveWriting(bool liveWriting);

        /** Return the total size allocated using the APro Memory System. */
        double getTotalBytesAllocated() const;
        /** Return the average size allocated by object. This is a total-based average. */
        double getAverageBytesAllocated() const;
        /** Return number of allocated blocks. */
        int getObjectAllocatedNumber() const;

        /** Return thhe current amount of bytes allocated with the APro Memory System. */
        double getCurrentBytesAllocated() const;
        /** Return the current number of object (block) allocated with the APro Memory System. */
        int getCurrentObjectAllocated() const;

        /** Tell if Memory Tracker truncate filename when writing. */
        bool isCuttingFilename() const;
        /** Tell what is the max filename size before cutting. */
        int maxFilenameSize() const;

        /** Set if Memory Tracker truncate filename. */
        void setCutFilename(bool cut);
        /** Set the max filename size if cutting is enabled. */
        void setMaxFilenameSize(int sz);

        void dump(const std::string& filename);

        void setRetain(bool r);

    private:

        /** Report leaks when destructor is called. */
        void reportLeaks();
        /** Update the 'stack' buffer. Init file if null.
         *  @param bypass : Used by destructor.
        **/
        void updateStack(bool bypass = false);
        /** Release and close the file pointer. */
        void deinitfile();
        /** Open the file given by MemoryFile::filename. */
        void initfile();
        /** Find a block by his pointer. */
        MemoryBlock* findBlock(void* ptr);
        /** Cut a filename if needed. */
        std::string processFilename(const char* file);

    private:

        MemoryBlockMap      blockMap;
        MemoryStatistics    statistics;
        MemoryStatistics    totalStats;
        MemoryFile          file;
        MemoryStack         stack;

    };
}

#endif

#endif
