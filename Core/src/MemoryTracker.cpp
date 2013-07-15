/** @file MemoryTracker.cpp
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 22/05/2012 - 26/05/2012
 *
 *  @addtogroup Memory
 *
 *  This file implements the Memory Tracker.
 *
**/
#include "MemoryTracker.h"
#include "Console.h"
#include "ThreadManager.h"

#if APRO_MEMORYTRACKER == APRO_ON

#include <sstream>
#include <cstdio>
#include <iostream>

#undef new
#undef  delete

namespace APro
{
    namespace
    {
        ThreadMutex::ptr global_mutex = nullptr;
        bool mutex_created = false;
        bool mutex_creating = false;

        void create_global_mutex()
        {
            mutex_creating = true;
            APRO_THREAD_MUTEX_SAFELOCK(global_mutex);
            if(!global_mutex.isNull())
                mutex_created = true;
            mutex_creating = false;
        }

        void lock_global_mutex()
        {
            if(mutex_creating) return;

            if(mutex_created)
                APRO_THREAD_MUTEX_SAFELOCK(global_mutex);
            else
                create_global_mutex();
        }

        void unlock_global_mutex()
        {
            if(mutex_creating) return;

            if(mutex_created)
                APRO_THREAD_MUTEX_SAFEUNLOCK(global_mutex);
            else
                create_global_mutex();
        }
    }

    MemoryManager& MemoryManager::get()
    {
        static MemoryManager memmanager; return memmanager;
    }

    MemoryManager::MemoryManager()
    {
        memstats.bytesallocated  = 0;
        memstats.bytesfreed      = 0;
        memstats.blocksallocated = 0;
        memstats.blocksfreed     = 0;
        m_opeDump                = false;
    }

    MemoryManager::~MemoryManager()
    {

        for(unsigned int i = 0; i < operations.size(); ++i)
        {
            Operation* op = operations.at(i);
            if(op->getType() == Operation::Allocation)
            {
                AllocationOperation* aop = reinterpret_cast<AllocationOperation*>(op);
                delete aop;
            }
            else if (op->getType() == Operation::Deallocation)
            {
                DeallocationOperation* aop = reinterpret_cast<DeallocationOperation*>(op);
                delete aop;
            }
            else if (op->getType() == Operation::Reallocation)
            {
                ReallocationOperation* aop = reinterpret_cast<ReallocationOperation*>(op);
                delete aop;
            }
        }

        operations.clear();
        blocks.clear();

    }

    bool MemoryManager::areOperationsDumped() const
    {
        return m_opeDump;
    }

    void MemoryManager::setOperationsDumping(bool opdmp)
    {
        m_opeDump = opdmp;
    }

    void MemoryManager::reportAllocation(void* ptr, size_t byte, const char* func, const char* file, int line)
    {
        if(ptr && byte)
        {
            lock_global_mutex();

            BlockMap::iterator it = blocks.find((ptr_t) ptr);
            if(it == blocks.end())
            {
                // Ajout du block
                MemoryBlock block;
                block.func = func;
                block.line = line;
                block.file = file;
                block.size = byte;
                blocks[ptr] = block;

                // Ajout d'un nouveau operation
                AllocationOperation* ope = new AllocationOperation;
                ope->block = block;
                ope->ptr   = ptr;
                operations.push_back(ope);
            }
            else
            {
                // On remplace l'ancien block par le nouveau
                it->second.func = func;
                it->second.file = file;
                it->second.line = line;
                it->second.size = byte;

                // Ajout d'un nouveau operation
                AllocationOperation* ope = new AllocationOperation;
                ope->block = it->second;
                ope->ptr   = ptr;
                operations.push_back(ope);
            }

            memstats.blocksallocated++;
            memstats.bytesallocated += byte;

            unlock_global_mutex();
        }
    }

    void MemoryManager::reportReallocation(void* ptr, void* new_ptr, size_t byte, const char* func, const char* file, int line)
    {
        if(ptr && new_ptr && byte)
        {
            lock_global_mutex();

            BlockMap::iterator it = blocks.find((ptr_t) ptr);
            if(it != blocks.end())
            {
                // Sauvegarde de l'ancien block
                MemoryBlock oldblock = it->second;

                // On supprime l'ancien block
                blocks.erase(it);
                memstats.blocksfreed++;
                memstats.bytesfreed += oldblock.size;

                // On cree un nouveau block
                MemoryBlock block;
                block.func = func;
                block.line = line;
                block.file = file;
                block.size = byte;
                blocks[new_ptr] = block;

                // On ajout l'operation Reallocation
                ReallocationOperation* ope = new ReallocationOperation;
                ope->block    = oldblock;
                ope->ptr      = ptr;
                ope->newblock = block;
                ope->new_ptr  = new_ptr;
                operations.push_back(ope);
            }
            else
            {
                // On alloue un nouveau block
                MemoryBlock block;
                block.func = func;
                block.line = line;
                block.file = file;
                block.size = byte;
                blocks[new_ptr] = block;

                // On ajout l'operation Reallocation
                ReallocationOperation* ope = new ReallocationOperation;
                ope->block.size = 0;
                ope->newblock   = block;
                ope->ptr        = ptr;
                operations.push_back(ope);
            }

            memstats.blocksallocated++;
            memstats.bytesallocated += byte;

            unlock_global_mutex();
        }
    }

    void MemoryManager::reportDeallocation(void* ptr, const char* func, const char* file, int line)
    {
        if(ptr)
        {
            lock_global_mutex();

            BlockMap::iterator it = blocks.find((ptr_t) ptr);
            if(it != blocks.end())
            {
                // On sauvegarde l'ancien block
                MemoryBlock oldblock = it->second;

                // On efface l'ancien
                blocks.erase(it);

                // On cree un nouveau block
                MemoryBlock deblock;
                deblock.file = file;
                deblock.func = func;
                deblock.line = line;
                deblock.size = oldblock.size;

                // On cree une nouvelle operation
                DeallocationOperation* ope = new DeallocationOperation;
                ope->block = deblock;
                ope->ptr   = ptr;
                operations.push_back(ope);

                memstats.blocksfreed++;
                memstats.bytesfreed += oldblock.size;
            }

            unlock_global_mutex();
        }
    }

    const MemoryManager::Operation* MemoryManager::getLastOperation()
    {
        if(operations.size() > 0)
            return operations[operations.size() - 1];
        else
            return NULL;
    }

    MemoryManager::Statistics MemoryManager::getStats()
    {
        return memstats;
    }

    void MemoryManager::dump(const std::string& filename)
    {
        FILE* file = fopen(filename.c_str(), "w+");
        if(file)
        {
            fprintf(file, "\nMemoryManager Report Dump File");
            fprintf(file, "\n------------------------------");

            if(m_opeDump)
            {
                fprintf(file, "\n\nReporting every operations.\n");

                for(unsigned int i = 0; i < operations.size(); ++i)
                {
                    Operation* ope = operations[i];
                    fprintf(file, "%s", writeOperation(ope).c_str());
                    fflush(file);
                }
            }

            fprintf(file, "\n\nReporting stats.\n");
            fprintf(file, "\nTotal bytes allocated : %lu bytes.", memstats.bytesallocated);
            fprintf(file, "\nTotal blocks allocated : %lu blocks.", memstats.blocksallocated);
            fprintf(file, "\nTotal bytes freed : %lu bytes.", memstats.bytesfreed);
            fprintf(file, "\nTotal blocks freed : %lu blocks.", memstats.blocksfreed);
            fprintf(file, "\nEstimated leaks : %lu bytes.", memstats.bytesallocated - memstats.bytesfreed);
            fflush(file);

            fclose(file);
        }

    }

    std::string MemoryManager::writeOperation(Operation* ope)
    {
        if(ope)
        {
            if(ope->getType() == Operation::Allocation)
            {
                AllocationOperation* aope = reinterpret_cast<AllocationOperation*>(ope);
                std::string ret;
                std::stringstream stream(ret);
                stream << "\nAllocation (" << aope->ptr << ") [" << aope->block.file << "]{" << aope->block.func << "}|" << aope->block.line << "| of " << aope->block.size << " bytes.";
                return stream.str();
            }
            else if (ope->getType() == Operation::Reallocation)
            {
                ReallocationOperation* rope = reinterpret_cast<ReallocationOperation*>(ope);
                std::string ret;
                std::stringstream stream(ret);
                stream << "\nReallocation (" << rope->ptr << ") [" << rope->block.file << "]{" << rope->block.func << "}|" << rope->block.line << "| of " << rope->block.size << " bytes to "
                                    << "(" << rope->new_ptr << ") [" << rope->newblock.file << "]{" << rope->newblock.func << "}|" << rope->newblock.line << "| of " << rope->newblock.size << " bytes.";
                return stream.str();
            }
            else if (ope->getType() == Operation::Deallocation)
            {
                DeallocationOperation* dope = reinterpret_cast<DeallocationOperation*>(ope);
                std::string ret;
                std::stringstream stream(ret);
                stream << "\nDellocation (" << dope->ptr << ") [" << dope->block.file << "]{" << dope->block.func << "}|" << dope->block.line << "| of " << dope->block.size << " bytes.";
                return stream.str();
            }
            else
            {
                return "";
            }
        }
        else
        {
            return "";
        }
    }
}

#endif