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
#include <vector>

namespace APro
{
    class MemoryManager
    {
    public:

        typedef struct MemoryBlock
        {
            std::string func;
            std::string file;
            int         line;
            size_t      size;

        } MemoryBlock;

        typedef void* ptr_t;
        typedef std::map<ptr_t, MemoryBlock> BlockMap;

        BlockMap blocks;

    public:

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

    public:

        typedef struct Statistics
        {
            long int bytesallocated;
            long int blocksallocated;
            long int bytesfreed;
            long int blocksfreed;
        } Statistics;

        Statistics memstats;

    public:

        void setOperationsDumping(bool opdmp);
        bool areOperationsDumped() const;

        bool m_opeDump;

    public:

        static MemoryManager& get();

        MemoryManager();
        ~MemoryManager();

    public:

        void reportAllocation(void* ptr, size_t byte, const char* func, const char* file, int line);
        void reportReallocation(void* ptr, void* new_ptr, size_t byte, const char* func, const char* file, int line);
        void reportDeallocation(void* ptr, const char* func, const char* file, int line);

    public:

        const Operation* getLastOperation();
        Statistics getStats();

    public:

        void dump(const std::string& filename);

    protected:

        std::string writeOperation(Operation* ope);


    };
}

#endif

#endif
