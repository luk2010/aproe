/** @file SharedPointer.h
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 25/08/2012
 *
 *  @addtogroup Global
 *  @addtogroup Memory
 *
 *  This file defines the SharedPointer class.
 *
**/
#ifndef APROSHAREDPOINTER_H
#define APROSHAREDPOINTER_H

#include "Platform.h"
#include "Map.h"
#include "Console.h"
#include "Singleton.h"
#include "Variant.h"

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

    template <typename T>
    class SharedPointer
    {
    public:

        SharedPointer() : ptr(nullptr), counter(nullptr)
        {

        }

        SharedPointer(T* ptr_) : ptr(ptr_), counter(nullptr)
        {
            bind();
        }

        SharedPointer(const SharedPointer<T>& other) : ptr(other.ptr), counter(nullptr)
        {
            if(other.ptr)
            {
                counter = other.counter;
                counter->push();
            }
        }

        template<typename Y>
        SharedPointer(SharedPointer<Y>& other) : ptr(other.getPtr()), counter(nullptr)
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

        void release()
        {
            destroy();
        }

        SharedPointer<T>& operator = (const SharedPointer<T>& other)
        {
            destroy();

            ptr = other.ptr;

            counter = other.counter;
            if(counter)
                counter->push();

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
                        AProDelete(ptr);
                        AProDelete(counter);
                    }
                }
                else
                {
                    AProDelete(ptr);
                }
            }

            ptr = nullptr;
            counter = nullptr;
        }

    private:

        T* ptr;
        Counter* counter;
    };

    template<typename ValueType, typename ValueType2>
    const SharedPointer<ValueType> spCstCast(const SharedPointer<ValueType2>& sp)
    {
        return *(reinterpret_cast<SharedPointer<ValueType>*>(const_cast<SharedPointer<ValueType2>* >(&(sp))));
    }

    template<typename ValueType, typename ValueType2>
    SharedPointer<ValueType> spCast(SharedPointer<ValueType2> sp)
    {
        return *(reinterpret_cast<SharedPointer<ValueType>*>(&sp));
    }
}

#endif
