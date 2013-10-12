////////////////////////////////////////////////////////////
/** @file Memory.cpp
 *  @ingroup Memory
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 21/05/2012 - 04/09/2013
 *
 *  Implements basic memory function, like malloc, realloc, free. It is usefull when the engine
 *  use the Memory Tracker.
 *
**/
////////////////////////////////////////////////////////////
#include "Memory.h"
#include "MemoryTracker.h"

#include <stdio.h>

namespace APro
{

    class NotEnoughMemoryException : public Exception
    {
        APRO_MAKE_EXCEPTION(NotEnoughMemoryException)

        const char* what() const throw() { return "Not enough Memory accessible !"; }
    };

    void* allocate(size_t byte, const char* func_, const char* file_, int line_)
    {
        if(byte == 0)
        {
            return nullptr;
        }

        else
        {
            // Using the malloc function to allocate memory.
            /// @todo Make it more customizable.
            void* ptr = malloc(byte);
            if(ptr == nullptr)
            {
                aprodebug("Can't allocate ") << byte << " bytes ! Call from \"" << func_ << "\" in file \"" << file_ << "\" and line " << line_ << ".";
                aprothrow(NotEnoughMemoryException);// Throw an exception if available.
                return nullptr;
            }

            Memory::Set(ptr, 0, byte);
            MemoryManager::get().reportAllocation(ptr, byte, func_, file_, line_);
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
                    aprodebug("Can't reallocate ") << byte << " bytes ! Call from \"" << func_ << "\" in file \"" << file_ << "\" and line " << line_ << ".";
                    aprothrow(NotEnoughMemoryException);
                    return nullptr;
                }

                MemoryManager::get().reportReallocation(ptr, new_ptr, byte, func_, file_, line_);
                ptr = new_ptr;
                return new_ptr;
            }
        }
    }

    void deallocate(void* ptr, const char* func_, const char* file_, int line_)
    {
        if(ptr == nullptr)
        {
            aprodebug("Trying to delete null-pointer ! Call from \"") << func_ << "\" in file \"" << file_ << "\" and line " << line_ << ".";
            return;
        }

        else
        {

            MemoryManager::get().reportDeallocation(ptr, func_, file_, line_);
            free(ptr);
        }
    }

    namespace Memory
    {
        void Copy(void* target, const void* source, size_t sz)
        {
            memcpy(target, source, sz);
        }

        void Set(void* target, int value, size_t num)
        {
            memset(target, value, num);
        }

    }
}
