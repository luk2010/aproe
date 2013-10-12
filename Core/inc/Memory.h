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

/// @defgroup Memory Memory
/// @addtogroup Memory
/// @brief Memory management class, and containers.
///
/// The memory system is composed of some functions and class very
/// helpful making memory tracking much easier for the user.
///
/// ### The allocation / deallocation system
///
/// You can manage memory space using AProAllocate, AProReallocate or
/// AProDeallocate macros. This will always track the memory you allocated
/// or deallocated.
///
/// Keep in mind that memory space allocated is returned uninitialized,
/// and zeroed. No constructors can be called by these functions.
///
/// ### The AProNew / AProDelete system
///
/// Three macros make everything easier :
/// - AProNew : Constructs an object.
/// - AProNewA : Constructs an array of object.
/// - AProDelete : Destroys an object or an aray of objects.
///
/// These functions ensure correct calling of constructors and destructors,
/// and are optimized for void pointers too.

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
     *  @note To allocate space for arrays, you should use the
     *  Allocator class.
     *  @note This function always initialize memory space to
     *  zero.
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

    namespace Memory
    {
        APRO_DLL void Copy(void* target, const void* source, size_t sz);
        APRO_DLL void Set (void* target, int value, size_t num);
    }
}

////////////////////////////////////////////////////////////
/** @brief Allocates one or more objects.
 *
 *  @warning This function does not call the constructor of
 *  these objects. You should use the AProNew macro to use
 *  constructors args.
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
    // Allocation of memory.
    size_t sz = n * sizeof(T);
    return (T*) APro::allocate(sz, func_, file_, line_);
}

////////////////////////////////////////////////////////////
/** @brief Delete the given pointer.
 *
 *  @note In the contrary of AProNew, AProDelete calls destructors
 *  for each objects in the array from the given pointer.
 *  The number of objects is known from the MemoryManager which
 *  keep trace of the memory block allocated previously using
 *  AProNew or APro::allocate.
 *  @note If you allocate memory with APro::allocate and
 *  left it uninitialized, you may have some destructors calling
 *  problems if you try to destroy it using AProDelete and you so
 *  should use APro::deallocate or AProDelete with void* .
 *
 *  @note If you delete a void pointer, it will only free the occupied
 *  memory.
 *
 *  @param ptr : Pointer to destroy.
 *  @param func_ : Function calling this one.
 *  @param file_ : File where the function is.
 *  @param line_ : Line of call.
**/
////////////////////////////////////////////////////////////
template <typename T> void AProDelete(T* ptr, const char* func_, const char* file_, int line_)
{
    if(!ptr) return;

    size_t sz_t = sizeof(T);

    // Looking for Block.
    const APro::MemoryManager::MemoryBlock* mblock = APro::MemoryManager::get().retrieveMemoryBlock((ptr_t) ptr);
    if(mblock && mblock->size >= sz_t)
    {
        // If block is valid, we determine how many objects there are in.
        size_t n = (size_t) mblock->size / sz_t;
        while(n)
            ptr[--n]->~T();// Destroy each one in descending order to preserv cannonical destruction order of C++.
    }

    // Destroying the pointer.
    APro::deallocate(ptr, func_, file_, line_);
}

/** void type specialisation of AProDelete. */
template <> void AProDelete<void>(void* ptr, const char* func_, const char* file_, int line_)
{
    if(!ptr) return;

    // As it is a specialisation for the void type, we will not call destructors nor
    // look for number of objects as void is not a real type.

    // Destroying the pointer.
    APro::deallocate(ptr, func_, file_, line_);
}

/// Constructs a new object with given argues.
/// @ingroup Memory
/// @param T : Type of object.
/// @see AProNewA, AProDelete
#define AProNew(T, ...) new (AProNew<T>(1, __FUNCTION__, __FILE__, __LINE__)) T[1] (__VA_ARGS__)

/// Constructs a new array of objects of given size and argues.
/// @ingroup Memory
/// @param T : Type of objects.
/// @param N : Size of array (in number of elements).
/// @see AProNew, AProDelete
#define AProNewA(T, N, ...) new (AProNew<T>(N, __FUNCTION__, __FILE__, __LINE__)) T[N] (__VA_ARGS__)

/// Destroys an array of objects and call destructor if possible.
/// @ingroup Memory
/// @note If type is void, or if object block cannot be found, no destructors is called
/// and you may experience troubles.
/// @param P : Pointer to destroy.
/// @see AProNew, AProNewA
#define AProDelete(P) AProDelete(ptr, __FUNCTION__, __FILE__, __LINE__)

#endif
