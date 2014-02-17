////////////////////////////////////////////////////////////
/** @file AutoPointer.h
 *  @ingroup Memory
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 02/07/2013 - 16/02/2014
 *
 *  Defines the AutoPointer class.
 *
**/
////////////////////////////////////////////////////////////
#ifndef APRO_AUTOPOINTER_H
#define APRO_AUTOPOINTER_H

#include "Platform.h"
#include "PointerCollector.h"

namespace APro
{
    ////////////////////////////////////////////////////////////
    /** @class AutoPointer
     *  @ingroup Memory
     *  @brief Reference a pointer to the given PointerCollector
     *  and destroy it when unused.
     *
     *  The AutoPointer is an object initialized with a pointer
     *  and a PointerCollector. The pointer is grabbed in the
     *  PointerCollector.
     *
     *  When the PointerCollector detects that every instance of
     *  the pointer is destroyed, the pointer is obviously destroyed
     *  by this class, calling the AProDelete function.
     *
     *  Every destructors are called by this class. You do not need
     *  to make a homemade system to bypass the destructors calls.
     *  But you can subclass easily this class by using the
     *  APRO_COPY_AUTOPOINTER_CONSTRUCT() macro and correctly
     *  overwrite the destroy_pointer() function wich must call
     *  deallocate_pointer() at the end.
     *
     *  @note For most case, a simple typedef is sufficient because
     *  the destruction system calls every destructors.
     *
     *  @note AutoPointer can be used also as a normal pointer
     *  because operator T* is overwritten.
    **/
    ////////////////////////////////////////////////////////////
    template <typename T>
    class AutoPointer
    {
    protected:

        T*                  pointer;            ///< pointer referenced
        PointerCollector*   custom_collector;   ///< Collector used by the AutoPointer.

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Constructor.
        **/
        ////////////////////////////////////////////////////////////
        AutoPointer()
            : pointer(nullptr), custom_collector(nullptr)
        {
            custom_collector = &(PointerCollector::Get());
        }

        ////////////////////////////////////////////////////////////
        /** @brief Constructor from adress.
         *  @param pointer_to_init : Pointer to reference.
        **/
        ////////////////////////////////////////////////////////////
        AutoPointer(T* pointer_to_init)
            : pointer(pointer_to_init), custom_collector(nullptr)
        {
            custom_collector = &(PointerCollector::Get());
            init_pointer();
        }

        ////////////////////////////////////////////////////////////
        /** @brief Constructor with pointer and custom collector.
         *  @param pointer_to_init : Poionter to reference.
         *  @param p_collector : Pointer to a custom collector.
        **/
        ////////////////////////////////////////////////////////////
        AutoPointer(T* pointer_to_init, PointerCollector* p_collector)
        {
            pointer = pointer_to_init;
            custom_collector = (p_collector) ? p_collector : &(PointerCollector::Get());
            init_pointer();
        }

        ////////////////////////////////////////////////////////////
        /** @brief Constructor by copy.
         *  @param auto_pointer : Pointer to copy.
         *  @note Custom collector is copied during this constructor.
        **/
        ////////////////////////////////////////////////////////////
        AutoPointer(const AutoPointer<T>& auto_pointer)
        {
            pointer = auto_pointer.pointer;
            custom_collector = auto_pointer.custom_collector;
            init_pointer();
        }

        ////////////////////////////////////////////////////////////
        /** @brief Constructor by copy.
         *  @param auto_pointer : Pointer to copy.
         *  @note The type of the pointer must be directly castable
         *  to the main type of this AutoPointer.
        **/
        ////////////////////////////////////////////////////////////
        template<typename Y>
        AutoPointer(const AutoPointer<Y>& auto_pointer)
        {
            pointer = dynamic_cast<T*>(auto_pointer.pointer);
            custom_collector = auto_pointer.custom_collector;
            init_pointer();
        }

        ////////////////////////////////////////////////////////////
        /** @brief Destructor.
        **/
        ////////////////////////////////////////////////////////////
        virtual ~AutoPointer()
        {
            ungrab_pointer();
        }

    protected:

        ////////////////////////////////////////////////////////////
        /** @brief Ungrab the pointer from the collector.
        **/
        ////////////////////////////////////////////////////////////
        void ungrab_pointer()
        {
            if(pointer && custom_collector)
            {
                custom_collector->pop(pointer);
                if(custom_collector->getPointerUtility(pointer) == 0)
                {
                    destroy_pointer();
                }
            }
            else if(pointer)
            {
                destroy_pointer();
            }

            pointer = nullptr;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Destroy the pointer.
         *  @note re-implement this function to perform specialized
         *  destruction of objects.
         *  This function is called only if the collector tell that use
         *  is 0.
         *
         *  Use it to perform custom destruction as virtual destroy
         *  function object (as in AbstractObject).
         *
         *  @note Never forget to call ::deallocate_pointer at the end
         *  of this function.
        **/
        ////////////////////////////////////////////////////////////
        virtual void destroy_pointer() { deallocate_pointer(); }

        ////////////////////////////////////////////////////////////
        /** @brief Deallocate the pointer and removes it from the
         *  collector.
         *
         *  This function doesn't check the utility of the pointer.
        **/
        ////////////////////////////////////////////////////////////
        void deallocate_pointer()
        {
            if(pointer)
            {
                if(custom_collector)
                {
                    custom_collector->remove(pointer);
                }

                AProDelete(pointer);
                pointer = nullptr;
            }
        }

    protected:

        ////////////////////////////////////////////////////////////
        /** @brief Init the pointer, and reference it to the collector.
        **/
        ////////////////////////////////////////////////////////////
        void init_pointer()
        {
            if(pointer)
            {
                if(custom_collector)
                {
                    custom_collector->push(pointer);
                }
            }
        }

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Change the current pointer.
         *  @details Ungrab the old one if non-null and grab the new
         *  one, if non-null, to collector.
         *  @param ptr : Pointer to set.
        **/
        ////////////////////////////////////////////////////////////
        void set(T* ptr)
        {
            if(pointer)
            {
                ungrab_pointer();
            }

            pointer = ptr;
            init_pointer();
        }

        ////////////////////////////////////////////////////////////
        /** @brief Return the current pointer.
         *  @note Never delete a pointer from this function.
        **/
        ////////////////////////////////////////////////////////////
        T* getPointer()
        {
            return pointer;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Return the current pointer.
         *  @note Never delete a pointer returned by this function.
        **/
        ////////////////////////////////////////////////////////////
        const T* getPointer() const
        {
            return pointer;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Return the number of instance of this pointer,
         *  given by the PointerCollector.
        **/
        ////////////////////////////////////////////////////////////
        size_t getPointerUses() const
        {
            if(pointer)
            {
                if(custom_collector)
                {
                    return custom_collector->getPointerUtility(pointer);
                }
                else
                {
                    return 1;
                }
            }
            else
            {
                return 0;
            }
        }

        ////////////////////////////////////////////////////////////
        /** @brief Return the PointerCollector associated with this
         *  AutoPointer.
        **/
        ////////////////////////////////////////////////////////////
        PointerCollector* getPointerCollector()
        {
            return custom_collector;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Return the PointerCollector associated with this
         *  AutoPointer.
        **/
        ////////////////////////////////////////////////////////////
        const PointerCollector* getPointerCollector() const
        {
            return custom_collector;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Set the current pointer to null if not, and
         *  ungrab it from the PointerCollector.
        **/
        ////////////////////////////////////////////////////////////
        void nullize()
        {
            ungrab_pointer();
        }

        ////////////////////////////////////////////////////////////
        /** @brief Tell if current pointer is null.
        **/
        ////////////////////////////////////////////////////////////
        bool isNull() const
        {
            return pointer == nullptr;
        }

    public:

        inline T* operator ->()
        {
            return pointer;
        }

        inline const T* operator ->() const
        {
            return pointer;
        }

        inline T& operator *()
        {
            return *pointer;
        }

        inline const T& operator *() const
        {
            return *pointer;
        }

        inline T* operator T* ()
        {
            return pointer;
        }

        inline const T* operator T* () const
        {
            return pointer;
        }

    public:

        bool operator == (const AutoPointer<T>& other) const
        {
            return other.pointer == pointer;
        }

        bool operator != (const AutoPointer<T>& other) const
        {
            return !(*this == other);
        }

        AutoPointer& operator = (const AutoPointer<T>& other)
        {
            set(other.pointer);
            return *this;
        }

        AutoPointer& operator = (T* ptr)
        {
            set(ptr);
            return *this;
        }

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Reinterpret current pointer to another class.
         *
         *  You can use this function to reinterpret this pointer to
         *  for exemple, a derived class that you are sure this pointer
         *  refers to.
        **/
        ////////////////////////////////////////////////////////////
        template<typename Y>
        Y* reinterpret()
        {
            return reinterpret_cast<Y*>(pointer);
        }

        ////////////////////////////////////////////////////////////
        /** @brief Reinterpret current pointer to another class.
         *
         *  You can use this function to reinterpret this pointer to
         *  for exemple, a derived class that you are sure this pointer
         *  refers to.
        **/
        ////////////////////////////////////////////////////////////
        template<typename Y>
        const Y* reinterpret() const
        {
            return reinterpret_cast<const Y*>(pointer);
        }
    };

#define APRO_COPY_AUTOPOINTER_CONSTRUCT(type, object) \
    type() : AutoPointer<object>() { } \
    type(object* __o) : AutoPointer<object>(__o) { } \
    type(object* __o, PointerCollector* __p) : AutoPointer<object>(__o, __p) { } \
    type(const type<object>& __p) : AutoPointer<object>(__p) { } \
    template<typename __Y) type(const type<__Y>& __p) : AutoPointer<object>(__p) { }
}

#endif // APRO_AUTOPOINTER_H
