////////////////////////////////////////////////////////////
/** @file AutoPointer.h
 *  @ingroup Memory
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 02/07/2013
 *
 *  Defines the AutoPointer class.
 *
**/
////////////////////////////////////////////////////////////
#ifndef APRO_AUTOPOINTER_H
#define APRO_AUTOPOINTER_H

#include "Platform.h"
#include "PointerCollector.h"
#include "Main.h"

namespace APro
{
    ////////////////////////////////////////////////////////////
    /** @class AutoPointer
     *  @ingroup Memory
     *  @brief references a shared pointer and delete it when no
     *  use.
     *  @details AutoPointer references a given adress. Each times
     *  this adress is referenced, it has a given referene counter
     *  (PointerCollector) that tell if the adress is used, or not.
     *
     *  The PointerCollector can be anyone you give, but by default,
     *  it is the Main Global Pointer Collector that is given to
     *  AutoPointer, to provide global pointer referencing.
     *
     *  If the PointerCollector is a custom one, only AutoPointer
     *  copied from original will have the same PointerCollector.
     *
     *  You can customize the deletion of particular objects, in
     *  subclassing a specialization of this class.
     *  @code
     *  class MyIntPointer : public AutoPointer<int>
     *  @endcode
     *
     *  This can be used to reimplement the ::destroy_pointer method,
     *  to perform customized destruction of objects.
     *
     *  @note You must call the ungrab_pointer function from the
     *  destructor of your class. The pointer isn't automaticly
     *  released in the original class.
     *
     *  To create a sub class of this one, you should use the template
     *  as :
     *
     *  @code
     *  class Example {};
     *  
     *  class Example_AutoPointer : public AutoPointer<Example>
     *  {
     *     public:
     *        APRO_COPY_AUTOPOINTER_CONSTRUCT(Example_AutoPointer,
     *                                          Example)
     *        
     *        virtual ~Example_AutoPointer() { ungrab_pointer(); }
     *
     *     protected:
     *        void destroy_pointer() {  Do_your_stuff_here_(); }
     *  };
     *  @endcode
     *
     *  The public part is the standard part, the protected one is 
     *  your customization part. If your object dosen't have specific
     *  destruction (except delete of course), you can use
     *  @code typedef AutoPointer<Example> Example_AutoPointer; @endcode
     *  to quickly perform AutoPointer subclass. 
     *
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
            custom_collector = &(Main::get().getGlobalPointerCollector());
        }

        ////////////////////////////////////////////////////////////
        /** @brief Constructor from adress.
         *  @param pointer_to_init : Pointer to reference.
        **/
        ////////////////////////////////////////////////////////////
        AutoPointer(T* pointer_to_init)
            : pointer(pointer_to_init), custom_collector(nullptr)
        {
            custom_collector = &(Main::get().getGlobalPointerCollector());
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
            custom_collector = (p_collector) ? p_collector : &(Main::get().getGlobalPointerCollector());
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
         *  @note Never delete a pointer from this function.
        **/
        ////////////////////////////////////////////////////////////
        const T* getPointer() const
        {
            return pointer;
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
        /** @brief Set the current pointer to null if not.
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
    };
    
#define APRO_COPY_AUTOPOINTER_CONSTRUCT(type, object) \
    type() : AutoPointer<object>() { } \
    type(object* __o) : AutoPointer<object>(__o) { } \
    type(object* __o, PointerCollector* __p) : AutoPointer<object>(__o, __p) { } \
    type(const type<object>& __p) : AutoPointer<object>(__p) { } \
    template<typename __Y) type(const type<__Y>& __p) : AutoPointer<object>(__p) { }
}

#endif // APRO_AUTOPOINTER_H
