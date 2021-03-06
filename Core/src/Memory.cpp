////////////////////////////////////////////////////////////
/** @file Memory.cpp
 *  @ingroup Memory
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 21/05/2012 - 26/01/2015
 *
 *  @brief
 *  Implements basic memory function, like malloc, realloc, free. It is usefull when the engine
 *  use the Memory Tracker.
 *
 *  @copyright
 *  Atlanti's Project Engine
 *  Copyright (C) 2012 - 2015  Atlanti's Corp
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
**/
////////////////////////////////////////////////////////////
#include "Memory.h"
#include "MemoryTracker.h"

#include "Exception.h"
#include "Console.h"

#include <stdio.h>
#include <cstring>

namespace APro
{

    class NotEnoughMemoryException : public Exception
    {
        APRO_MAKE_EXCEPTION(NotEnoughMemoryException)

        const char* what() const throw() { return "Not enough Memory accessible !"; }
    };

    void* allocate(size_t byte, const char* func_, const char* file_, int line_, bool is_arr)
    {
        if(byte == 0)
        {
            return nullptr;
        }

        else
        {
            // Using the malloc function to allocate memory.
            /// @todo Make it more customizable.
            
            // Create sufficient space for the requested memory and the header.
            size_t totbyte = byte + sizeof(MemoryHeader);
            void* ptr = malloc(totbyte);
            if(ptr == nullptr)
            {
                aprodebug("Can't allocate ") << totbyte << " bytes ! Call from \"" << func_ << "\" in file \"" << file_ << "\" and line " << line_ << ".";
                aprothrow(NotEnoughMemoryException);// Throw an exception if available.
                return nullptr;
            }

            Memory::Set(ptr, 0, totbyte);// We assert that memory is clean.
            MemoryManager::get().reportAllocation(ptr, byte, func_, file_, line_, is_arr);
            
            // Initialize the memoryheader.
            MemoryHeader* head = (MemoryHeader*) ptr;
            head->size     = byte;
            head->is_array = is_arr;
            
            return APRO_MEM_VIRTUAL(ptr);
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
                size_t realsz = byte + sizeof(MemoryHeader);
                void* realptr = APRO_MEM_REAL(ptr);
                
                void* ret = realloc(realptr, realsz);
                if(ret == nullptr)
                {
                    aprodebug("Can't reallocate ") << realsz << " bytes ! Call from \"" << func_ << "\" in file \"" << file_ << "\" and line " << line_ << ".";
                    aprothrow(NotEnoughMemoryException);
                    return nullptr;
                }

                MemoryManager::get().reportReallocation(realptr, ret, realsz, func_, file_, line_);
                ptr = APRO_MEM_VIRTUAL(ret);
                return APRO_MEM_VIRTUAL(ret);
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
            ptr = APRO_MEM_REAL(ptr);
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

        void CopyInterlaced(void* target, const void* source, size_t sz)
        {
            char buffer[sz];
            Copy(buffer, source, sz);
            Copy(target, buffer, sz);
        }

        void Set(void* target, int value, size_t num)
        {
            memset(target, value, num);
        }

        int Cmp(const void * s1, const void * s2,size_t n)
        {
            return memcmp(s1, s2, n);
        }
        
        size_t GetBlockSize(void* ptr)
        {
            return APRO_MEM_HEAD(APRO_MEM_REAL(ptr))->size;
        }

    }
}
