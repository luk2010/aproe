////////////////////////////////////////////////////////////
/** @file Memory.h
 *  @ingroup Memory
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 21/05/2012 - 26/12/2014
 *
 *  Redefines basic memory function, like malloc, realloc, free. It is usefull when the engine
 *  use the Memory Tracker.
 *
**/
////////////////////////////////////////////////////////////
#ifndef APROMEMORY_H
#define APROMEMORY_H

#include "MemoryTracker.h"
#include "Types.h"

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
    /** @struct MemoryHeader
     *  @ingroup Memory
     *  @brief A memory Header made to simplify memory organization.
    **/
    ////////////////////////////////////////////////////////////
    struct MemoryHeader
    {
        size_t size;     ///< @brief Size of the block
        bool   is_array; ///< @brief True if block is an array.
    } __attribute__ ((packed));
    
    ////////////////////////////////////////////////////////////
    /** @brief Allocate bytes using the malloc function.
     *  @ingroup Memory
     *
     *  @param byte : number of byte to allocate.
     *  @param func_ : function where the allocate was called.
     *  @param file_ : file where the function was called.
     *  @param line_ : line where the function was called.
     *  @param is_arr : True if call is to allocate an array, false
     *  otherweise. This argue may be used with the AProNewA
     *  function as it informs the MemoryManager that the block
     *  will be an array.
     *
     *  @return A pointer to allocated bytes.
     *  @throw NotEnoughMemoryException if memory could not be 
     *  allocated.
     *
     *  @note 
     *  This function always initialize memory space to
     *  zero.
     * 
     *  @note
     *  The allocation system need to allocate a few more memory
     *  to hold the block size and the array attribute. This make 
     *  the system much more quicker as it does not have to get the
     *  MemoryManager to get those informations. But this also
     *  involve that the returned pointer is not actually the pointer
     *  memory malloc() returned, this pointer can be retrieved using
     *  the macro APRO_MEM_REAL (ptr) or APRO_CONSTMEM_REAL depending
     *  on memory access.
     *  
     *  @see ::reallocate(), ::deallocate()
    **/
    ////////////////////////////////////////////////////////////
    APRO_DLL void* allocate(size_t byte, const char* func_, const char* file_, int line_, bool is_arr = false);

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
#define AProAllocate(sz)            APro::allocate(sz, __FUNCTION__, __FILE__, __LINE__)
#define AProReallocate(ptr, sz)     APro::reallocate(ptr, sz, __FUNCTION__, __FILE__, __LINE__)
#define AProDeallocate(ptr)         APro::deallocate(ptr, __FUNCTION__, __FILE__, __LINE__)
    
/// @brief Convert given Real -> MemoryHeader pointer
#define APRO_MEM_HEAD(ptr)          (MemoryHeader*) ((void*)ptr)
/// @brief Convert Virtual -> Real
#define APRO_MEM_REAL (ptr)         (((char*)ptr) - sizeof(APro::MemoryHeader))
/// @brief Convert Real -> Virtual
#define APRO_MEM_VIRTUAL (ptr)      (((char*)ptr) + sizeof(APro::MemoryHeader))

#define APRO_CONSTMEM_HEAD(ptr)     (const MemoryHeader*) ((const void*)ptr)
#define APRO_CONSTMEM_REAL (ptr)    (((const char*)ptr) - sizeof(APro::MemoryHeader))
#define APRO_CONSTMEM_VIRTUAL (ptr) (((const char*)ptr) + sizeof(APro::MemoryHeader))
    ////////////////////////////////////////////////////////////
    /** @} **/
    ////////////////////////////////////////////////////////////

    namespace Memory
    {
        APRO_DLL void Copy(void* target, const void* source, size_t sz);

        /** Use a temporary buffer to copy 2 interlaced data streams. */
        APRO_DLL void CopyInterlaced(void* target, const void* source, size_t sz);

        APRO_DLL void Set (void* target, int value, size_t num);

        /////////////////////////////////////////////////////////////
        /** @brief The memcmp() function compares the first n characters
         *  of the object pointed to by s1 to the first n characters of
         *  the object pointed to by s2.
         *
         *  @return The memcmp() function returns an integer greater than,
         *  equal to, or less than zero, accordingly as the object pointed
         *  to by s1 is greater than, equal to, or less than the object
         *  pointed to by s2.
        **/
        /////////////////////////////////////////////////////////////
        APRO_DLL int Cmp(const void * s1, const void * s2, size_t n);
        
        ////////////////////////////////////////////////////////////
        /** @brief Returns the size of a block allocated using the
         *  AProAllocate / AProDeallocate system.
         *
         *  @note 
         *  Behaviour of this function is undefined on blocks not 
         *  allocated using APro System.
        **/
        ////////////////////////////////////////////////////////////
        APRO_DLL size_t GetBlockSize(void* block);
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
 *  @param is_arr : True if call is an allocation of array,
 *  false otherweise. We could use the n argue but we so are
 *  sure for 1-sized array (you could allocate an array of
 *  size 1, unnecessary but could be a problem).
 *
 *  @return A pointer to newly created object, but not
 *  constructed.
**/
////////////////////////////////////////////////////////////
template <typename T> T* AProNew (size_t n, const char* func_, const char* file_, int line_, bool is_arr = false)
{
    // Allocation of memory.
    size_t sz = n * sizeof(T);
    return (T*) APro::allocate(sz, func_, file_, line_, is_arr);
}

////////////////////////////////////////////////////////////
/** @brief Delete the given pointer and call destructors if
 *  possible.
 *
 *  @note In the contrary of AProNew, AProDelete calls destructors
 *  for each objects in the array from the given pointer.
 *  The number of objects is known by the MemoryHeader, so you
 *  have to use AProEngine allocation system.
 *
 *  @note If you allocate memory with APro::allocate and
 *  left it uninitialized, you may have some destructors calling
 *  problems if you try to destroy it using AProDelete and you so
 *  should use APro::deallocate or AProDelete with void* .
 *
 *  @note If you delete a void pointer, it will only free the occupied
 *  memory.
 *
 *  @param ptr : Pointer to destroy. This pointer is VIRTUAL.
 *  @param func_ : Function calling this one.
 *  @param file_ : File where the function is.
 *  @param line_ : Line of call.
**/
////////////////////////////////////////////////////////////
template <typename T> void AProDelete(T* ptr, const char* func_, const char* file_, int line_)
{
    if(!ptr) return;

    // We can call destructors only if type is destructible.
    // This feature is available only since C++11 so we must have a correct C++11 compiler.
    if(APro::Types::IsDestructible<T>())
    {
        size_t sz_t = sizeof(T);
        // Looking for Header.
        MemoryHeader* head = APRO_MEM_HEAD(ptr);

        // Looking for Block. We try to avoid this function at it is too much costs.
        // const APro::MemoryManager::MemoryBlock* mblock = APro::MemoryManager::get().retrieveMemoryBlock((ptr_t) ptr);
        if(head && head->is_array)
        {
            // If block is valid and it is an array (# of objects superior or equal to 2), we determine how many objects there are in.
            // Each blocks should have been initialized. As this function is called with AProNewA, this is what is done with placement.
            // This is necessary as every allocation using AProNew uses placement new.
            size_t n = (size_t) head->size / sz_t;
            while(n)
                ptr[--n].~T();// Destroy each one in descending order to preserv cannonical destruction order of C++.
        }
        else
        {
            // Block is not an array. We call the destructor as delete would have done it.
            ptr->~T();
        }
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
#define AProNew(T, ...) new (AProNew<T>(1, __FUNCTION__, __FILE__, __LINE__)) T[1] ( __VA_ARGS__ )

/// Constructs a new array of objects of given size and argues.
/// @ingroup Memory
/// @param T : Type of objects.
/// @param N : Size of array (in number of elements).
/// @see AProNew, AProDelete
#define AProNewA(T, N, ...) new (AProNew<T>(N, __FUNCTION__, __FILE__, __LINE__, true)) T[N] ( __VA_ARGS__ )

/// Destroys an array of objects and call destructor if possible.
/// @ingroup Memory
/// @note If type is void, or if object block cannot be found, no destructors is called
/// and you may experience troubles.
/// @param P : Pointer to destroy.
/// @see AProNew, AProNewA
#define AProDelete(P) AProDelete(ptr, __FUNCTION__, __FILE__, __LINE__)

/// Constructs an object by calling the copy constructor and placement new.
/// @ingroup Utils
/// @param to : Pointer to a memory space that may contain the copy.
/// @param from : Constant Reference to an object that will be copied.
/// @param Type : Type of the objects.
#define AProConstructedCopy(to, from, Type) new (to) Type(from)

////////////////////////////////////////////////////////////
/** @brief Call object destructor if possible.
 *
 *  If object is array, destructors for every object will
 *  be called.
**/
////////////////////////////////////////////////////////////
template<typename T> void AProDestructObject(T* object, size_t sz = 1, bool _is_array = false)
{
    if(APro::Types::IsDestructible<T>())
    {
        if(_is_array && sz)
        {
            // If it is an array, call destructor for each entry.
            while (sz)
                object[--sz].~T();
        }
        else
        {
            // Else call the destructor.
            ptr->~T();
        }
    }
}

#endif
