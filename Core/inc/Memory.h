////////////////////////////////////////////////////////////
/** @file Memory.h
 *  @ingroup Memory
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 21/05/2012 - 04/09/2013
 *
 *  Redefines basic memory function, like malloc, realloc, free. It is usefull when the engine
 *  use the Memory Tracker.
 *
**/
////////////////////////////////////////////////////////////
#ifndef APROMEMORY_H
#define APROMEMORY_H

#include "Platform.h"
#include "MemoryTracker.h"

namespace APro
{
    ////////////////////////////////////////////////////////////
    /** @brief Allocate bytes using the malloc function.
     *  @ingroup Memory
     *
     *  @param byte : number of byte to allocate.
     *  @param func_ : function where the allocate was called.
     *  @param file_ : file where the function was called.
     *  @param line_ : line where the function was called.
     *
     *  @return A pointer to allocated bytes.
     *
     *  @note
     *  To allocate space for arrays, you should use the Allocator class.
    **/
    ////////////////////////////////////////////////////////////
    APRO_DLL void* allocate(size_t byte, const char* func_, const char* file_, int line_);

    ////////////////////////////////////////////////////////////
    /** @brief Reallocate bytes using an old pointer.
     *  @ingroup Memory
     *
     *  @param ptr : Old pointer.
     *  @param byte : New numberof bytes.
     *  @param func_ : function where the allocate was called.
     *  @param file_ : file where the function was called.
     *  @param line_ : line where the function was called.
     *
     *  @return A pointer to the newly allocated space.
     *
     *  @remarks
     *  Old pointer is modified, only if reallocation worked. In the case where reallocations doesn't work, an Exception
     *  will be thrown, or, if exceptions are disabled, nullptr is returned.
     *
     *  @note
     *  To reallocate arrays, use Allocator class.
    **/
    ////////////////////////////////////////////////////////////
    APRO_DLL void* reallocate(void*& ptr, size_t byte, const char* func_, const char* file_, int line_);

    ////////////////////////////////////////////////////////////
    /** @brief Deallocate bytes from a given pointer.
     *  @ingroup Memory
     *
     *  @param ptr : Pointer to deallocate.
     *  @param func_ : function where the allocate was called.
     *  @param file_ : file where the function was called.
     *  @param line_ : line where the function was called.
     *
    **/
    ////////////////////////////////////////////////////////////
    APRO_DLL void  deallocate(void* ptr, const char* func_, const char* file_, int line_);

    ////////////////////////////////////////////////////////////
    /** Macro to short up the declarations.
     *  @{
    **/
    ////////////////////////////////////////////////////////////
    #define AProAllocate(sz) APro::allocate(sz, __FUNCTION__, __FILE__, __LINE__)
    #define AProReallocate(ptr, sz) APro::reallocate(ptr, sz, __FUNCTION__, __FILE__, __LINE__)
    #define AProDeallocate(ptr) APro::deallocate(ptr, __FUNCTION__, __FILE__, __LINE__)
    ////////////////////////////////////////////////////////////
    /** @} **/
    ////////////////////////////////////////////////////////////
}

////////////////////////////////////////////////////////////
/** @brief Allocates one or more objects using placement
 *  new.
 *
 *  This function does not construct the object, it only
 *  reserve allocated space for it. Every objects you allocate
 *  with it is considered as an array, even for one object
 *  because it can be constructed more easily using the
 *  AProNew macro.
 *
 *  @param n : Number of objects to allocate.
 *  @param func_ : Function calling this one.
 *  @param file_ : File where the function is.
 *  @param line_ : Line of call.
 *
 *  @return A pointer to newly created object, but not
 *  constructed.
**/
////////////////////////////////////////////////////////////
template <typename T> T* AProNew (size_t n, const char* func_, const char* file_, int line_)
{
    T* ptr = (T*) new (sizeof(T) * n);

#if APRO_MEMORYTRACKER == APRO_ON

    APro::MemoryManager::get().reportAllocation(ptr, sizeof(T) * n, func_, file_, line_);

#endif

    return ptr;
}

////////////////////////////////////////////////////////////
/** @brief Typed deletion of given pointer.
 *
 *  Use it with AProDelete macro to delete your pointers
 *  previously allocated using AProNew macro.
 *
 *  Destructors are called in this function, but only
 *  destructors of the given resolved type.
 *  @see Prototype::operator delete for more explanation
 *  about destruction and destructors.
 *
 *  @note Calling AProDelete on a void pointer only deallocate
 *  the previously allocated memory, and do not call any
 *  destructors.
 *
 *  @param ptr : Pointer to destroy.
 *  @param func_ : Function calling this one.
 *  @param file_ : File where the function is.
 *  @param line_ : Line of call.
**/
////////////////////////////////////////////////////////////
template <typename T> void AProDelete(T* ptr, const char* func_, const char* file_, int line_)
{
#if APRO_MEMORYTRACKER == APRO_ON

    APro::MemoryManager::get().reportDeallocation(ptr, func_, file_, line_);

#endif

    delete[] ptr;
}

////////////////////////////////////////////////////////////
/** @brief Allocate one object.
 *  @deprecated
**/
////////////////////////////////////////////////////////////
template <typename T> T* AProNew_alone(const char* func_, const char* file_, int line_)
{
    T* ptr = new T;

#if APRO_MEMORYTRACKER == APRO_ON

    APro::MemoryManager::get().reportAllocation(ptr, sizeof(T), func_, file_, line_);

#endif

    return ptr;
}

////////////////////////////////////////////////////////////
/** @brief Deallocate one object.
 *  @deprecated
**/
////////////////////////////////////////////////////////////
template <typename T> void AProDelete_alone(T* ptr, const char* func_, const char* file_, int line_)
{
#if APRO_MEMORYTRACKER == APRO_ON

    APro::MemoryManager::get().reportDeallocation(ptr, func_, file_, line_);

#endif

    delete ptr;
}

// Use for arrays
#define AProNew(T) new (AProNew<T>(1, __FUNCTION__, __FILE__, __LINE__)) T[1]
#define AProNew(n, T) new (AProNew<T>(n, __FUNCTION__, __FILE__, __LINE__)) T[n]

#define AProDelete(ptr) AProDelete(ptr, __FUNCTION__, __FILE__, __LINE__)

// Use for placement new with memory manager and 1 argue
#define AProNew2(T, arg, ptr) new T ( arg ); APro::MemoryManager::get().reportAllocation(ptr, sizeof(T), __FUNCTION__, __FILE__, __LINE__);
#define AProDelete2(ptr) APro::MemoryManager::get().reportDeallocation(ptr, __FUNCTION__, __FILE__, __LINE__); delete ptr

// Use for 1 object and argues
#define AProNew3(T) new(AProNew_alone<T>(__FUNCTION__, __FILE__, __LINE__)) T
#define AProDelete3(ptr) AProDelete_alone(ptr, __FUNCTION__, __FILE__, __LINE__)

#endif
