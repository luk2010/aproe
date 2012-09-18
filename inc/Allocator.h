/** @file Allocator.h
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 22/05/2012 - 26/05/2012
 *
 *  @addtogroup Memory
 *
 *  This file defines the Allocator system.
 *
**/
#ifndef APROALLOCATOR_H
#define APROALLOCATOR_H

#include "Platform.h"
#include "Memory.h"
#include "MemoryTracker.h"

namespace APro
{
    /** @class Allocator
     *
     *  @addtogroup Memory
     *
     *  This class defines an object that can be used to allocate an amount of data using the type of the data
     *  as the base size.
     *  You should use this class to allocate arrays.
     *
     *  Example :
     *
     *  @code
     *  MyObject* objetArray = APro::Allocator<MyObject>::allocateArray(10);// We allocate space for 10 objects.
     *
     *  APro::Allocator<MyObject>::deallocatePtr(objetArray);// We deallocate space.
     *  @endcode
     *
     *  @warning
     *  You must use dedicated defines to function instead of real function, just to provide Memory Tracker
     *  tracking of real file, line and function.
     *
     *  @note
     *  You can't create an instance of Allocators. It is a static-only class.
     *
    **/
    template<typename T>
    class Allocator
    {

    public:

        typedef T   _type;
        typedef T*  _typePtr;
        typedef T&  _typeRef;

    private:

        Allocator() { /* Do Nothing. */ }
        ~Allocator() { /* Do Nothing. */ }

    public:

        #define allocateOne() allocateOne_(__FUNCTION__, __FILE__, __LINE__)
        #define allocateArray(sz) allocateArray_(sz, __FUNCTION__, __FILE__, __LINE__)
        #define reallocateArray(ptr, sz) reallocateArray_(ptr, sz, __FUNCTION__, __FILE__, __LINE__)
        #define deallocatePtr(ptr) deallocatePtr_(ptr, __FUNCTION__, __FILE__, __LINE__)

        /** Allocate space for a single object.
         *
         *  It is equivalent to AProAllocate, but without telling bytes size.
         *
         *  @return A pointer to your type.
        **/
        static _typePtr allocateOne_(const char* func, const char* file, int line)
        {
            size_t sz = sizeof(_type);
            _typePtr ptr = static_cast<_typePtr>(APro::allocate(sz, func, file, line));

#if APRO_ALLOCATORSTRICT == APRO_ON

            if(ptr == nullptr)
            {
                APRO_THROW("Allocation Failed", "Can't allocate Pointer !", "Allocator");
            }

#endif

            return ptr;
        }

        /** Allocate Space for an array with given size.
         *
         *  @param size : Number of 'case' in the array.
         *
         *  @return A pointer to your type.
         *
        **/
        static _typePtr allocateArray_(size_t size, const char* func, const char* file, int line)
        {
            if(size == 0)
            {
                return nullptr;
            }

            size_t sz = sizeof(_type);
            _typePtr ptr = static_cast<_typePtr>(malloc(size * sz));

#if APRO_ALLOCATORSTRICT == APRO_ON

            if(ptr == nullptr)
            {
                APRO_THROW("Allocation Failed", "Can't allocate Pointer Array !", "Allocator");
            }

#endif

#if APRO_MEMORYTRACKER == APRO_ON

            MemoryTracker::get()->reportAllocation(ptr, sz * size, func, file, line);

#endif
            return ptr;
        }

        /** Reallocate an array of given size
         *
         *  @param oldPtr : Pointer to reallocate.
         *  @param newSz : New size for the pointer.
         *
         *  @return The reallocated Pointer.
         *
         *  @warning
         *  This function may invalid the old pointer, so you
         *  should not use it (the pointer).
         */
        static _typePtr reallocateArray_(T* oldPtr, size_t newSz, const char* func, const char* file, int line)
        {
            if(oldPtr == nullptr)
            {
                if(newSz > 0)
                {
                    _typePtr ptr = allocateArray_(newSz, func, file, line);
                    return ptr;
                }

                return nullptr;
            }

            if(newSz == 0)
            {
                deallocatePtr(oldPtr);
                return nullptr;
            }

            _typePtr newPtr = static_cast<_typePtr>(APro::reallocate((void*&)oldPtr, newSz * sizeof(_type), func, file, line));

#if APRO_ALLOCATORSTRICT == APRO_ON

            if(newPtr == nullptr)
            {
                APRO_THROW("Reallocation Failed", "Can't reallocate pointer !", "Allocator");
            }

#endif

            return newPtr;
        }

        /** Deallocate a pointer.
         *
         *  @remarks
         *  If pointer is null, nothing is done.
         *
         *  @param ptr : Pointer to deallocate.
         *
        **/
        static void deallocatePtr_(_typePtr ptr, const char* func, const char* file, int line)
        {
            if(ptr != nullptr)
                APro::deallocate(ptr, func, file, line);
        }

        /** Swap two blocks of memory.
         *
         *  @param first : First block (array) to swap.
         *  @param second : Second block (array) to swap.
         *  @param sz : Size of the array (in number of object).
         *
         *  @remarks
         *  This funtion use a temporary buffer. Don't try to swap 2 blocks of memory
         *  if you can't allocate a third one with the same size.
         *
         */
        static void swap(_typePtr first, _typePtr second, size_t sz)
        {
            _typePtr tmp = allocateArray(sz);
            size_t size = sz * sizeof(_type);

            memcpy(tmp, first, size);
            memcpy(first, second, size);
            memcpy(second, first, size);

            deallocatePtr(tmp);
        }
    };
}

#endif
