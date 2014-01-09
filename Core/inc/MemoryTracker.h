////////////////////////////////////////////////////////////
/** @file MemoryTracker.h
 *  @ingroup Memory
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 21/05/2012 - 22/12/2013
 *
 *  Defines the Memory Tracker.
 *
**/
////////////////////////////////////////////////////////////
#ifndef APROMEMORYTRACKER_H
#define APROMEMORYTRACKER_H

#include "Platform.h"

#include <map>
#include <string>
#include <vector>

namespace APro
{
    ////////////////////////////////////////////////////////////
    /** @class MemoryManager
     *  @ingroup Memory
     *  @brief anage allocation, reallocatino and deallocation of
     *  memory blocks.
     *
     *  Depending on your configuration, MemoryManager can also
     *  track every operations performed and then write it in a
     *  file.
    **/
    ////////////////////////////////////////////////////////////
    class MemoryManager
    {
    public:

        /** Describes a Memory Block. */
        typedef struct MemoryBlock
        {
            std::string func;
            std::string file;
            int         line;
            size_t      size;
            bool        is_array;

        } MemoryBlock;

        typedef void* ptr_t;
        typedef std::map<ptr_t, MemoryBlock> BlockMap;

        BlockMap blocks;

    public:

#if APRO_MEMORYTRACKER == APRO_ON

        class Operation
        {
        public:

            enum OperationType
            {
                Allocation,
                Deallocation,
                Reallocation
            };

        public:

            Operation()
            {

            }

            virtual ~Operation()
            {

            }

            virtual OperationType getType() const = 0;

        public:

            MemoryBlock block;
            ptr_t       ptr;

        };

        class AllocationOperation : public Operation
        {
        public:

            OperationType getType() const { return Allocation; }
        };

        class ReallocationOperation : public Operation
        {
        public:

            OperationType getType() const { return Reallocation; }

            MemoryBlock newblock;
            ptr_t       new_ptr;
        };

        class DeallocationOperation : public Operation
        {
        public:

            OperationType getType() const { return Deallocation; }
        };

        std::vector<Operation*> operations;

#endif

    public:

        typedef struct Statistics
        {
            long int bytesallocated;/// Total bytes allocated.
            long int blocksallocated;/// Total blocks allocated.
            long int bytesfreed;/// Total bytes deallocated.
            long int blocksfreed;/// Total blocks deallocated.
        } Statistics;

        Statistics memstats;

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Return the MemoryManager in place.
        **/
        ////////////////////////////////////////////////////////////
        static MemoryManager& get();

        ////////////////////////////////////////////////////////////
        /** @brief Constructs the MemoryManager.
        **/
        ////////////////////////////////////////////////////////////
        MemoryManager();

        ////////////////////////////////////////////////////////////
        /** @brief Destructs the MemoryManager.
        **/
        ////////////////////////////////////////////////////////////
        ~MemoryManager();

    private:

        ////////////////////////////////////////////////////////////
        /** @brief Report an allocation to the Memory Manager.
        **/
        ////////////////////////////////////////////////////////////
        void reportAllocation(void* ptr, size_t byte, const char* func, const char* file, int line, bool is_arr = false);

        ////////////////////////////////////////////////////////////
        /** @brief Report a reallocation to the Memory Manager.
        **/
        ////////////////////////////////////////////////////////////
        void reportReallocation(void* ptr, void* new_ptr, size_t byte, const char* func, const char* file, int line);

        ////////////////////////////////////////////////////////////
        /** @brief Report a deallocation to the Memory Manager.
        **/
        ////////////////////////////////////////////////////////////
        void reportDeallocation(void* ptr, const char* func, const char* file, int line);

        friend APRO_DLL void* allocate(size_t byte, const char* func_, const char* file_, int line_);
        friend APRO_DLL void* reallocate(void*& ptr, size_t byte, const char* func_, const char* file_, int line_);
        friend APRO_DLL void  deallocate(void* ptr, const char* func_, const char* file_, int line_);

    public:

#if APRO_MEMORYTRACKER == APRO_ON

        ////////////////////////////////////////////////////////////
        /** @brief Return the last operation performed by this Manager.
         *
         *  @note You should always take care if the returned pointer
         *  is null, because depending on your configuration this
         *  function might always return null.
        **/
        ////////////////////////////////////////////////////////////
        const Operation* getLastOperation();

#else

        typedef void Operation;
        const Operation* getLastOperation() { return nullptr; }

#endif // APRO_MEMORYTRACKER

        ////////////////////////////////////////////////////////////
        /** @brief Return current statistics for this Manager.
        **/
        ////////////////////////////////////////////////////////////
        Statistics getStats();

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Write every operations in given file.
         *
         *  This function will write operations only if '--with-memorytracker'
         *  option is set. Otherweise, statistics is written.
        **/
        ////////////////////////////////////////////////////////////
        void dump(const std::string& filename);

    public:

        ////////////////////////////////////////////////////////////
        /** @brief retrieve a block from a pointer.
        **/
        ////////////////////////////////////////////////////////////
        const MemoryBlock* retrieveMemoryBlock(ptr_t ptr) const;

#if APRO_MEMORYTRACKER == APRO_ON

    protected:

        std::string writeOperation(Operation* ope);

#endif // APRO_MEMORYTRACKER

    };
}

#endif
