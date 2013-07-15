/** @file SharedPointer.h
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 25/08/2012
 *
 *  @ingroup Global
 *  @ingroup Memory
 *
 *  This file defines the SharedPointer class.
 *
**/
#ifndef APROSHAREDPOINTER_H
#define APROSHAREDPOINTER_H

#include "Platform.h"
#include "Allocator.h"

namespace APro
{
    class Counter
    {
    public:

        Counter() : count(0)
        {

        }

        Counter(const Counter& other)
        {
            count = other.count;
        }

        ~Counter()
        {

        }

        int value() const
        {
            return count;
        }

        void push()
        {
            count ++;
        }

        void pop()
        {
            if(count > 0)
                count --;
        }

    private:
        int count;
    };

    class DeletionMethod
    {
    public:
        enum t
        {
            Delete,
            Delete2,
            Delete3
        };
    };

    template <typename T>
    class SharedPointer
    {

    public:

        SharedPointer() : ptr(nullptr), counter(nullptr), dmethod(DeletionMethod::Delete)
        {

        }

        SharedPointer(T* ptr_) : ptr(ptr_), counter(nullptr), dmethod(DeletionMethod::Delete)
        {
            bind();
        }

        SharedPointer(const SharedPointer<T>& other) : ptr(other.ptr), counter(nullptr), dmethod(other.dmethod)
        {
            if(other.ptr)
            {
                counter = other.counter;
                counter->push();
            }
        }

        template<typename Y>
        SharedPointer(SharedPointer<Y>& other) : ptr(other.getPtr()), counter(nullptr), dmethod(other.getDeletionMethod())
        {
            if(other.getPtr())
            {
                counter = other.getCounter();
                counter->push();
            }
        }

        ~SharedPointer()
        {
            destroy();
        }

        const T* getPtr() const
        {
            return ptr;
        }

        T* getPtr()
        {
            return ptr;
        }

        Counter* getCounter()
        {
            return counter;
        }

        const Counter* getCounter() const
        {
            return counter;
        }

        inline T* operator ->()
        {
            return ptr;
        }

        inline const T* operator ->() const
        {
            return ptr;
        }

        inline T& operator *()
        {
            return *ptr;
        }

        inline const T& operator *() const
        {
            return *ptr;
        }

        void set(T* ptr_)
        {
            destroy();
            ptr = ptr_;
            bind();
        }

        void _force_set(T* ptr_)
        {
            ptr = ptr_;
            destroy_counter();
            bind();
        }

        void release()
        {
            destroy();
        }

        void setDeletionMethod(DeletionMethod::t dm)
        {
            dmethod = dm;
        }

        DeletionMethod::t getDeletionMethod() const
        {
            return dmethod;
        }

        SharedPointer<T>& operator = (const SharedPointer<T>& other)
        {
            destroy();

            ptr = other.ptr;

            counter = other.counter;
            if(counter)
                counter->push();

            dmethod = other.dmethod;

            return *this;
        }

        bool operator == (const SharedPointer<T>& other) const
        {
            return other.ptr == ptr;
        }

        bool operator != (const SharedPointer<T>& other) const
        {
            return !(*this == other);
        }

        bool isNull() const
        {
            return ptr == nullptr;
        }

        int getUses() const
        {
            return counter ? counter->value() : 0;
        }

    private:

        void bind()
        {
            if(ptr && counter)
                return;

            if(ptr)
            {
                counter = AProNew(1, Counter) ;
                counter->push();
            }
        }

        void destroy()
        {
            if(ptr != nullptr)
            {
                if(counter)
                {
                    counter->pop();
                    if(counter->value() == 0)
                    {
                        delete_using_deletion();
                        destroy_counter();
                    }
                }
                else
                {
                    delete_using_deletion();
                }
            }

            ptr = nullptr;
            counter = nullptr;
        }

        void destroy_counter()
        {
            if(counter)
            {
                AProDelete(counter);
                counter = nullptr;
            }
        }

        void delete_using_deletion()
        {
            if(dmethod == DeletionMethod::Delete)
            {
                AProDelete(ptr);
            }

            if(dmethod == DeletionMethod::Delete2)
            {
                AProDelete2(ptr);
            }

            if(dmethod == DeletionMethod::Delete3)
            {
                AProDelete3(ptr);
            }
        }

    private:

        T* ptr;
        Counter* counter;
        DeletionMethod::t dmethod;
    };

    template<typename ValueType, typename ValueType2>
    const SharedPointer<ValueType>& spCstCast(const SharedPointer<ValueType2>& sp)
    {
        return *(reinterpret_cast<SharedPointer<ValueType>*>(const_cast<SharedPointer<ValueType2>* >(&(sp))));
    }

    template<typename ValueType, typename ValueType2>
    SharedPointer<ValueType>& spCast(SharedPointer<ValueType2>& sp)
    {
        return *(reinterpret_cast<SharedPointer<ValueType>*>(&sp));
    }

    #define APRO_DECLARE_SHAREDPOINTER_CLASS_TYPEDEF(class) \
    public:\
    typedef APro::SharedPointer<class> ptr;\
    typedef ptr sharedPtr;\
    typedef class* explicitPtr;\
    typedef APro::ReadOnlyPointer<class> readonlyptr;

    template <typename T>
    class ReadOnlyPointer
    {
    protected:

        T* ptr;

    public:

        ReadOnlyPointer() : ptr(nullptr)
        {

        }

        ReadOnlyPointer(const ReadOnlyPointer<T>& other) : ptr(other.ptr)
        {

        }

        ReadOnlyPointer(T* p) : ptr(p)
        {

        }

        ReadOnlyPointer(SharedPointer<T> p) : ptr(p.getPtr())
        {

        }

        ~ReadOnlyPointer()
        {

        }

        bool operator == (const ReadOnlyPointer<T>& other) const
        {
            return other.ptr == ptr;
        }

        bool operator != (const ReadOnlyPointer<T>& other) const
        {
            return !(*this == other);
        }

        bool isNull() const
        {
            return ptr == nullptr;
        }

        inline T* operator ->()
        {
            return ptr;
        }

        inline const T* operator ->() const
        {
            return ptr;
        }

        inline T& operator *()
        {
            return *ptr;
        }

        inline const T& operator *() const
        {
            return *ptr;
        }

        void set(const T* p)
        {
            ptr = p;
        }

        ReadOnlyPointer<T>& operator = (const ReadOnlyPointer<T>& other)
        {
            ptr = other.ptr;
            return *this;
        }
    };

    template<typename ValueType, typename ValueType2>
    const ReadOnlyPointer<ValueType>& spCstCast_r(const ReadOnlyPointer<ValueType2>& sp)
    {
        return *(reinterpret_cast<ReadOnlyPointer<ValueType>*>(const_cast<ReadOnlyPointer<ValueType2>* >(&(sp))));
    }

    template<typename ValueType, typename ValueType2>
    ReadOnlyPointer<ValueType>& spCast_r(ReadOnlyPointer<ValueType2>& sp)
    {
        return *(reinterpret_cast<ReadOnlyPointer<ValueType>*>(&sp));
    }
}

#endif
