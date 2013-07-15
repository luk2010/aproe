/** @file Memory.cpp
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 21/05/2012 - 22/05/2012
 *
 *  @addtogroup Global
 *  @addtogroup Memory
 *
 *  This file implements basic memory function, like malloc, realloc, free. It is usefull when the engine
 *  use the Memory Tracker.
 *
**/
#include "Memory.h"

#if APRO_MEMORYTRACKER == APRO_ON
#   include "MemoryTracker.h"
#endif

#include <stdio.h>

namespace APro
{
    void* allocate(size_t byte, const char* func_, const char* file_, int line_)
    {
        if(byte == 0)
        {
            return nullptr;
        }

        else
        {
            void* ptr = malloc(byte);
            if(ptr == nullptr)
            {
#if APRO_EXCEPTION == APRO_ON

                char buffer[APRO_EXCEPTIONMAXBUFFERSIZE];
                sprintf(buffer, "Allocation of %li bytes failed in file %s at line %d", byte, file_, line_);

                APRO_THROW("Allocation Failed", buffer, "Memory");

#else

                return nullptr;

#endif
            }

#if APRO_MEMORYTRACKER == APRO_ON

            MemoryManager::get().reportAllocation(ptr, byte, func_, file_, line_);

#endif

            return ptr;
        }
    }

    void* reallocate(void*& ptr, size_t byte, const char* func_, const char* file_, int line_)
    {
        if(byte == 0)
        {
            return nullptr;
        }

        else
        {
            if(ptr == nullptr)
            {
                ptr = allocate(byte, func_, file_, line_);
                return ptr;
            }

            else
            {
                void* new_ptr = realloc(ptr, byte);
                if(new_ptr == nullptr)
                {
#if APRO_EXCEPTION == APRO_ON

                    char buffer[APRO_EXCEPTIONMAXBUFFERSIZE];
                    sprintf(buffer, "Reallocation of %li bytes failed in file %s at line %d", byte, file_, line_);

                    APRO_THROW("Reallocation Failed", buffer, "Memory");

#else

                    return nullptr;

#endif
                }

#if APRO_MEMORYTRACKER == APRO_ON

                MemoryManager::get().reportReallocation(ptr, new_ptr, byte, func_, file_, line_);

#endif

                ptr = new_ptr;
                return new_ptr;
            }
        }
    }

    void deallocate(void* ptr, const char* func_, const char* file_, int line_)
    {
        if(ptr == nullptr)
        {
            return;
        }

        else
        {

#if APRO_MEMORYTRACKER == APRO_ON

            MemoryManager::get().reportDeallocation(ptr, func_, file_, line_);

#endif

            free(ptr);
        }
    }
}
