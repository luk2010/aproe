/////////////////////////////////////////////////////////////
/** @file Allocator.h
 *  @ingroup Memory
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 22/05/2012
 *
 *  Defines the Allocator class.
 *
**/
////////////////////////////////////////////////////////////
#ifndef APROALLOCATOR_H
#define APROALLOCATOR_H

#include "Platform.h"
#include "Memory.h"
#include "MemoryTracker.h"
#include <cstring>

namespace APro
{
    ////////////////////////////////////////////////////////////
    /** @class Allocator
     *  @brief Defines an allocator malloc-based system.
     *
     *  @ingroup Memory
     *
     *  Can be used to allocate an amount of data using the type of the data
     *  as the base size.
     *  You should use this class to allocate arrays.<br />
     *
     *  Example :
     *
     *  @code
     *  MyObject* objetArray = APro::Allocator<MyObject>::allocateArray(10);// We allocate space for 10 objects.
     *
     *  APro::Allocator<MyObject>::deallocatePtr(objetArray);// We deallocate space.
     *  @endcode
     *
     *  ## A note about objects initializations
     *
     *  Objects can be initialized using the construct / destruct functions. When you allocate an object
     *  using the `Allocator::allocateOne_` or similarly function, you should always call the constructor of the newly
     *  created object, using the correct `Allocator::construct` function, depending on how many arguements you
     *  must pass.
     *
     *  @warning
     *  You must use dedicated defines to function instead of real function, just to provide Memory Tracker
     *  tracking of real file, line and function.<br />
     *  More, the allocator use the malloc and free functions. You can use AProNew and AProDelete with correct
     *  arguments, because they use new[] and delete[].<br />
     *
     *  @note
     *  You can't create an instance of Allocators. It is a static-only class.
     *
    **/
    ////////////////////////////////////////////////////////////
    template<typename T>
    class Allocator
    {

    public:

        typedef T   _type;///< Defines the current type.
        typedef T*  _typePtr;///< Pointer to the type.
        typedef T&  _typeRef;///< Reference to the type.

    private:

        ////////////////////////////////////////////////////////////
        /** Default constructor.
        **/
        ////////////////////////////////////////////////////////////
        Allocator() { /* Do Nothing. */ }

        ////////////////////////////////////////////////////////////
        /** Destructor.
        **/
        ////////////////////////////////////////////////////////////
        ~Allocator() { /* Do Nothing. */ }

    public:

        ////////////////////////////////////////////////////////////
        /** @name Allocation defines
         *  @ingroup Memory
         *  @{
        **/
        ////////////////////////////////////////////////////////////

        #define allocateOne() allocateOne_(__FUNCTION__, __FILE__, __LINE__)
        #define allocateArray(sz) allocateArray_(sz, __FUNCTION__, __FILE__, __LINE__)
        #define reallocateArray(ptr, sz) reallocateArray_(ptr, sz, __FUNCTION__, __FILE__, __LINE__)
        #define deallocatePtr(ptr) deallocatePtr_(ptr, __FUNCTION__, __FILE__, __LINE__)

        ////////////////////////////////////////////////////////////
        /** @}
        **/
        ////////////////////////////////////////////////////////////

        ////////////////////////////////////////////////////////////
        /** Allocate space for a single object.
         *
         *  It is equivalent to AProAllocate, but without telling bytes size.
         *
         *  @param func : Function calling.
         *  @param file : File where the function is.
         *  @param line : Line in the file.
         *
         *  @return A pointer to your type.
        **/
        ////////////////////////////////////////////////////////////
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

        ////////////////////////////////////////////////////////////
        /** Allocate Space for an array with given size.
         *
         *  @param size : Number of 'case' in the array.
         *  @param func : Function calling.
         *  @param file : File where the function is.
         *  @param line : Line in the file.
         *
         *  @return A pointer to your type.
         *
        **/
        ////////////////////////////////////////////////////////////
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

            MemoryManager::get().reportAllocation(ptr, sz * size, func, file, line);

#endif

            return ptr;
        }

        ////////////////////////////////////////////////////////////
        /** Reallocate an array of given size
         *
         *  @param oldPtr : Pointer to reallocate.
         *  @param newSz : New size for the pointer.
         *  @param func : Function calling.
         *  @param file : File where the function is.
         *  @param line : Line in the file.
         *
         *  @return The reallocated Pointer.
         *
         *  @warning
         *  This function may invalid the old pointer, so you
         *  should not use it (the pointer).
         */
         ////////////////////////////////////////////////////////////
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

        ////////////////////////////////////////////////////////////
        /** Deallocate a pointer.
         *
         *  @remarks
         *  If pointer is null, nothing is done.
         *
         *  @param ptr : Pointer to deallocate.
         *  @param func : Function calling.
         *  @param file : File where the function is.
         *  @param line : Line in the file.
         *
        **/
        ////////////////////////////////////////////////////////////
        static void deallocatePtr_(_typePtr ptr, const char* func, const char* file, int line)
        {
            if(ptr != nullptr)
                APro::deallocate(ptr, func, file, line);
        }

        ////////////////////////////////////////////////////////////
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
         ////////////////////////////////////////////////////////////
        static void swap(_typePtr first, _typePtr second, size_t sz)
        {
            _typePtr tmp = allocateArray(sz);
            size_t size = sz * sizeof(_type);

            memcpy(tmp, first, size);
            memcpy(first, second, size);
            memcpy(second, first, size);

            deallocatePtr(tmp);
        }

        ////////////////////////////////////////////////////////////
        /** @brief Construct an object without any arguments.
         *  @param object : Object to construct.
        **/
        ////////////////////////////////////////////////////////////
        static void construct(_typePtr object)
        {
            new ((void*) object) _type;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Construct an object with one argument.
         *  @param object : Object to construct.
         *  @param arg1 : First arguement.
        **/
        ////////////////////////////////////////////////////////////
        template <typename Arg1>
        static void construct(_typePtr object, Arg1& arg1)
        {
            new ((void*) object) _type(arg1);
        }

        ////////////////////////////////////////////////////////////
        /** @brief Construct an object with two arguments.
         *  @param object : Object to construct.
         *  @param arg1 : First arguement.
         *  @param arg2 : Second arguement.
        **/
        ////////////////////////////////////////////////////////////
        template <typename Arg1, typename Arg2>
        static void construct(_typePtr object, Arg1& arg1, Arg2& arg2)
        {
            new ((void*) object) _type(arg1, arg2);
        }

        ////////////////////////////////////////////////////////////
        /** @brief Construct an object with three arguments.
         *  @param object : Object to construct.
         *  @param arg1 : First arguement.
         *  @param arg2 : Second arguement.
         *  @param arg3 : Third arguement.
        **/
        ////////////////////////////////////////////////////////////
        template <typename Arg1, typename Arg2, typename Arg3>
        static void construct(_typePtr object, Arg1& arg1, Arg2& arg2, Arg3& arg3)
        {
            new ((void*) object) _type(arg1, arg2, arg3);
        }

        ////////////////////////////////////////////////////////////
        /** @brief Call the destructor of given object.
         *  @param object : Object to call destructor.
        **/
        ////////////////////////////////////////////////////////////
        static void destruct(_typePtr object)
        {
            object->~_type();
        }
    };
}

#endif
