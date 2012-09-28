/** @file Array.h
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 29/05/2012
 *
 *  @addtogroup Global
 *  @addtogroup Memory
 *
 *  This file defines the basic Array class.
 *  An Array is a dynamic C-style array. Its size is dynamicly reallocated.
 *
**/
#ifndef APROARRAY_H
#define APROARRAY_H

#include "Platform.h"
#include "Exception.h"
#include "Allocator.h"

#include <cstdio>

namespace APro
{
    //! \class Array
    /** Represents a linear Array.
     *
     *  This array is a linear rray, as an Array in C. It doesn't use the nw and delete system for each block,
     *  so we recommend you to use this array only for types that doesn't need to be constructed, i.e. types that
     *  can be memccpy easily like int, doube, char, ...
     *
     *  \note If you need to have the new and delete system for each node, use List instead.
     */
    template <typename T>
    class Array
    {
    private:

        size_t      physicalSize;///< Physical size
        size_t      size; ///< Logical size
        T*    first;

    public:

        /** Empty Constructor. */
        Array() : physicalSize(0), size(0), first(NULL)
        {

        }


        /** \brief Constructor with reserve size.
         *
         *  \param reserve_ Memory to reserve. Use it to avoid memory reallocation
         *  while filling the array.
         *
         */
        Array(size_t reserve_) : physicalSize(0), size(0), first(NULL)
        {
            if(reserve_ > 0)
            {
                first = Allocator<T>::allocateArray(reserve_);
                physicalSize = reserve_;
                size = 0;
            }
        }

        Array(const T* a, size_t sz) : physicalSize(0), size(0), first(NULL)
        {
            if(a)
            {
                reserve(sz);
                if(first)
                {
                    memcpy(first, a, sz * sizeof(T));
                    size = sz;
                }
            }
        }

        /** \brief Constructor by copy.
         *
         */
        Array(const Array<T> & other) : physicalSize(0), size(0), first(NULL)
        {
            if(!other.isEmpty())
            {
                reserve(other.getPhysicalSize());
                if(first != NULL)
                {
                    memcpy(first, other.first, sizeof(T) * other.getPhysicalSize());
                    size = other.getSize();
                }
            }
        }

        ~Array()
        {
            clear();
        }

        void set(const T* a, size_t sz)
        {
            clear();

            if(a)
            {
                reserve(sz);
                if(first)
                {
                    memcpy(first, a, sz * sizeof(T));
                    size = sz;
                }
            }
        }

        void set(const Array<T>& other)
        {
            clear();

            if(!other.isEmpty())
            {
                reserve(other.getPhysicalSize());
                if(first != NULL)
                {
                    memcpy(first, other.first, sizeof(T) * other.getPhysicalSize());
                    size = other.getSize();
                }
            }
        }

        size_t getPhysicalSize() const
        {
            return physicalSize;
        }

        size_t getSize() const
        {
            return size;
        }

        bool isEmpty() const
        {
            return size == 0;
        }

        void append(const T& obj)
        {
            if(physicalSize == size)
            {
                reserve(physicalSize + 1);
            }

            memcpy(first + size, &obj, sizeof(T));
            size += 1;
        }

        void push_back(const T& obj)
        {
            append(obj);
        }

        void append(const Array<T>& array)
        {
            if(physicalSize < size + array.getSize())
            {
                reserve(size + array.getSize());
            }

            memcpy(first + size, array.first, sizeof(T) * array.getSize());
            size += array.getSize();
        }

        void push_back(const Array<T>& array)
        {
            append(array);
        }

        void prepend(const T& obj)
        {
            insert(0, obj);
        }

        void push_front(const T& obj)
        {
            prepend(obj);
        }

        void insert(size_t before, const T& obj, size_t number = 1)
        {
            if(physicalSize < size + number)
            {
                reserve(size + number);
            }

            for(int i = size - 1; i >= (int) before; i--)
            {
                memcpy(first + i + number, first + i, sizeof(T));
            }

            for(int i = (int) before; i < (int) (before + number); i++)
            {
                memcpy(first + i, &obj, sizeof(T));
            }

            size += number;
        }

        void reserve(size_t physicalNewSize)
        {
            if(physicalNewSize > physicalSize)
            {
                if(first == nullptr)
                {
                    first = Allocator<T>::allocateArray(physicalNewSize);
                    physicalSize = physicalNewSize;
                    size = 0;
                }
                else
                {
                    first = Allocator<T>::reallocateArray(first, physicalNewSize);
                    physicalSize = physicalNewSize;
                }
            }
        }

        void erase(size_t firstIndex, size_t lastIndex = 0)
        {
            if(lastIndex == 0)
            {
                lastIndex = firstIndex;
            }

            if(firstIndex > lastIndex)
            {
                Allocator<size_t>::swap(&firstIndex, &lastIndex, 1);
            }

            if(size <= firstIndex)
            {
                APRO_THROW("Out of range", "Array::erase has detected out of range index !", "Array");
            }

            if(size <= lastIndex)
            {
                lastIndex = size - 1;
            }

            size_t sizedeleted = lastIndex - firstIndex + 1;
            size_t sizemoved = sizeof(T) * (size - lastIndex + 1);
            memcpy(first + firstIndex, first + lastIndex + 1, sizemoved);

            size -= sizedeleted;
        }

        void clear()
        {
            if(first != nullptr)
            {
                Allocator<T>::deallocatePtr(first);
                first = nullptr;
            }

            size = 0;
            physicalSize = 0;
        }

        T& at(size_t index)
        {
            assertIndex(index);
            return *(first + index);
        }

        const T& at(size_t index) const
        {
            assertIndex(index);
            return *(first + index);
        }

        T& operator [] (size_t index)
        {
            assertIndex(index);
            return *(first + index);
        }

        const T& operator [] (size_t index) const
        {
            assertIndex(index);
            return *(first + index);
        }

        size_t lastIndex() const
        {
            return size - 1;
        }

        bool assertIndex(size_t index) const
        {
            if(index < size)
                return true;
            else
            {
#if APRO_EXCEPTION == APRO_ON

                char buffer[APRO_EXCEPTIONMAXBUFFERSIZE];

                sprintf(buffer, "Array::assertIndex has detected out of range index ! Index was : %d.", index);

                APRO_THROW("Out of range", buffer, "Array");

#endif

                return false;
            }
        }

        Array<T>& operator << (const T& obj)
        {
            append(obj);
            return *this;
        }

        Array<T>& operator << (const Array<T>& array)
        {
            append(array);
            return *this;
        }

        Array<T>& operator = (const Array<T>& array)
        {
            clear();
            append(array);
            return *this;
        }

        bool operator == (const Array<T>& array) const
        {
            if(getSize() != array.getSize())
                return false;

            for(size_t i = 0; i < getSize(); i++)
            {
                if(at(i) != array.at(i))
                    return false;
            }

            return true;
        }

        bool operator != (const Array<T>& array) const
        {
            return !(*this == array);
        }

        int find(const T& obj) const
        {
            for(size_t i = 0; i < size; i++)
            {
                if(at(i) == obj)
                    return i;
            }

            return -1;
        }

    };
}

#endif
