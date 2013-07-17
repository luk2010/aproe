/////////////////////////////////////////////////////////////
/** @file Array.h
 *  @ingroup Memory
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 29/05/2012
 *
 *  Defines the Array class.
 *
**/
////////////////////////////////////////////////////////////
#ifndef APROARRAY_H
#define APROARRAY_H

#include "Platform.h"
#include "Exception.h"
#include "Allocator.h"

#include <cstdio>
#include <cstring>

namespace APro
{
    ////////////////////////////////////////////////////////////
    /** @class Array
     *  @brief Represents a linear Array.
     *
     *  @details This array is a linear array, as an Array in C. It doesn't use the new and delete system for each block,
     *  so we recommend you to use this array only for types that doesn't need to be constructed, i.e. types that
     *  can be memcpy-ed easily like int, doube, char, ...
     *
     *  @note If you need to have the new and delete system for each node, use List instead.
     *
     *  @details Example use of Arrays :
     *  @code
     *  Array<int> my_array(10);// Reserv 10 places to avoid memory reallocation time.
     *  my_array.append(5);
     *  my_array.prepend(4);
     *  my_array.erase(1);
     *  @endcode
    **/
    ////////////////////////////////////////////////////////////
    template <typename T>
    class Array
    {
    private:

        size_t      physicalSize;///< Physical size.
        size_t      size; ///< Logical size.
        T*          first;///< Pointer to the array.

    public:

        ////////////////////////////////////////////////////////////
        /** Default Constructor.
        **/
        ////////////////////////////////////////////////////////////
        Array() : physicalSize(0), size(0), first(NULL)
        {

        }

        ////////////////////////////////////////////////////////////
        /** Constructor with reserve size.
         *
         *  @param reserve_ : Memory to reserve. Use it to avoid memory reallocation
         *  while filling the array.
         *
        **/
        ////////////////////////////////////////////////////////////
        Array(size_t reserve_) : physicalSize(0), size(0), first(NULL)
        {
            if(reserve_ > 0)
            {
                first = Allocator<T>::allocateArray(reserve_);
                physicalSize = reserve_;
                size = 0;
            }
        }

        ////////////////////////////////////////////////////////////
        /** Constructor with an array.
         *
         *  @details You must specify the size of the array.
         *  This function can be used to convert quickly an array to APro::Array,
         *  because it use memcpy in one block.
         *
         *  @param a : Array to copy.
         *  @param sz : Size of the Array.
        **/
        ////////////////////////////////////////////////////////////
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

        ////////////////////////////////////////////////////////////
        /** Constructor by copy.
         *
         *  @detais It also use memcpy in one block, so it's a quite quick function.
         *
         *  @param other : Array to copy.
         *
        **/
        ////////////////////////////////////////////////////////////
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

        ////////////////////////////////////////////////////////////
        /** Destructor.
        **/
        ////////////////////////////////////////////////////////////
        ~Array()
        {
            clear();
        }

        ////////////////////////////////////////////////////////////
        /** Set the content of the array with a C-style array.
         *
         *  @param a : Array to copy.
         *  @param sz : Size of the array.
        **/
        ////////////////////////////////////////////////////////////
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

        ////////////////////////////////////////////////////////////
        /** Set the content of the array with a APro::Array.
         *
         *  @param other : Array to copy.
        **/
        ////////////////////////////////////////////////////////////
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

        ////////////////////////////////////////////////////////////
        /** Return the real size of the array, in number of elements.
         *
         *  @details The real size of the array can be different to the logical size
         *  because it use a 'reserve' system that allow him to reserve space for futur
         *  reallocations to be faster.
         *
         *  @return Real size of the array.
        **/
        ////////////////////////////////////////////////////////////
        size_t getPhysicalSize() const
        {
            return physicalSize;
        }

        ////////////////////////////////////////////////////////////
        /** Return the logical size of the array.
         *  @return Logical size.
         *  @remarks The logical size correspond to the number of
         *  elements in the array.
        **/
        ////////////////////////////////////////////////////////////
        size_t getSize() const
        {
            return size;
        }

        ////////////////////////////////////////////////////////////
        /** Tell if the array is empty.
         *
         *  @note Return if the number of element is 0.
         *  @return Is array empty ?
        **/
        ////////////////////////////////////////////////////////////
        bool isEmpty() const
        {
            return size == 0;
        }

        ////////////////////////////////////////////////////////////
        /** Copy an element to the end of the array.
         *
         *  @param obj : Object to append.
        **/
        ////////////////////////////////////////////////////////////
        void append(const T& obj)
        {
            if(physicalSize == size)
            {
                reserve(physicalSize + 1);
            }

            memcpy(first + size, &obj, sizeof(T));
            size += 1;
        }

        ////////////////////////////////////////////////////////////
        /** Push an object to the end of the array.
         *  @see append .
         *  @param obj : Object to append.
        **/
        ////////////////////////////////////////////////////////////
        void push_back(const T& obj)
        {
            append(obj);
        }

        ////////////////////////////////////////////////////////////
        /** Append an array to the end of this one.
         *  @param array : Array to copy.
        **/
        ////////////////////////////////////////////////////////////
        void append(const Array<T>& array)
        {
            if(physicalSize < size + array.getSize())
            {
                reserve(size + array.getSize());
            }

            memcpy(first + size, array.first, sizeof(T) * array.getSize());
            size += array.getSize();
        }

        ////////////////////////////////////////////////////////////
        /** Append an array to the end of this one.
         *  @see append
         *  @param array : Array to append.
        **/
        ////////////////////////////////////////////////////////////
        void push_back(const Array<T>& array)
        {
            append(array);
        }

        ////////////////////////////////////////////////////////////
        /** Append a C-style array at the end.
         *  @param array : Pointer to the array.
         *  @param sz : Number of element.
        **/
        ////////////////////////////////////////////////////////////
        void append(const T* array, size_t sz)
        {
            if(array != NULL && sz > 0)
            {
                if(physicalSize < size + sz)
                {
                    reserve(size + sz);
                }

                memcpy(first + size, array, sizeof(T) * sz);
                size += sz;
            }
        }

        ////////////////////////////////////////////////////////////
        /** Append a C-style array at the end.
         *  @see append
         *  @param array : Pointer to the array.
         *  @param sz : Number of element.
        **/
        ////////////////////////////////////////////////////////////
        void push_back(const T* array, size_t sz)
        {
            append(array, sz);
        }

        ////////////////////////////////////////////////////////////
        /** Prepend an object.
         *  @param obj : Object to prepend.
        **/
        ////////////////////////////////////////////////////////////
        void prepend(const T& obj)
        {
            insert(0, obj);
        }

        ////////////////////////////////////////////////////////////
        /** Prepend an object.
         *  @see prepend
         *  @param obj : Object to prepend.
        **/
        ////////////////////////////////////////////////////////////
        void push_front(const T& obj)
        {
            prepend(obj);
        }

        ////////////////////////////////////////////////////////////
        /** Prepend an array to this one.
         *  @param array : Array to copy.
         *  @note On big arrays, this function is slow.
        **/
        ////////////////////////////////////////////////////////////
        void prepend(const Array<T>& array)
        {
            if(physicalSize < size + array.getSize())
            {
                reserve(size + array.getSize());
            }

            for(unsigned int i = 0; i < array.getSize(); ++i)
            {
                insert(0 + i, array.at(i));
            }
        }

        ////////////////////////////////////////////////////////////
        /** Prepend an array to this one.
         *  @see prepend
         *  @param array : Array to copy.
         *  @note On big arrays, this function is slow.
        **/
        ////////////////////////////////////////////////////////////
        void push_front(const Array<T>& array)
        {
            prepend(array);
        }

        ////////////////////////////////////////////////////////////
        /** Prepend a C-style array.
         *  @param array : Pointer to the array.
         *  @param sz : Number of element.
        **/
        ////////////////////////////////////////////////////////////
        void prepend(const T* array, size_t sz)
        {
            if(array != NULL && sz > 0)
            {
                if(physicalSize < size + sz)
                {
                    reserve(size + sz);
                }

                for(unsigned int i = 0; i < sz; ++i)
                {
                    insert(0 + i, array[i]);
                }
            }
        }

        /** @brief As prepend(T*, size_t) . */
        void push_front(const T* array, size_t sz)
        {
            prepend(array, sz);
        }

        /** @brief Insert an object before given position.
         *
         *  @param before : Position to insert before.
         *  @param obj : Object to copy.
         *  @param number : Number of copy.
         */
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

        /** @brief Reserve space for the array
         *
         *  You can use it to reserve space before a big insertion, so the array won't need
         *  to reallocate many times.
         *
         *  @note
         *  This space does not count on Size.
         *
         *  @param physicalNewSize : Size of the reserved space (entirely), in number of element.
         */
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

        /** @brief Erase objects from positio given to other position.
         *
         *  @note
         *  Index given are included in the deletion.
         *
         *  @param firstIndex : Position to start deletion.
         *  @param lastIndex : Position to end deletion.
         */
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

        /** @brief Clear the array. */
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

        /** @brief Return the object at given index. */
        T& at(size_t index)
        {
            assertIndex(index);
            return *(first + index);
        }

        /** @brief Return the object at given index. */
        const T& at(size_t index) const
        {
            assertIndex(index);
            return *(first + index);
        }

        /** @brief Return the object at given index. */
        T& operator [] (size_t index)
        {
            assertIndex(index);
            return *(first + index);
        }

        /** @brief Return the object at given index. */
        const T& operator [] (size_t index) const
        {
            assertIndex(index);
            return *(first + index);
        }

        /** @brief Return last object in the array. */
        size_t lastIndex() const
        {
            return size - 1;
        }

        /** @brief Throw an exception if index is not in correct range. */
        bool assertIndex(size_t index) const
        {
            if(index < size)
                return true;
            else
            {
#if APRO_EXCEPTION == APRO_ON

                char buffer[APRO_EXCEPTIONMAXBUFFERSIZE];

                sprintf(buffer, "Array::assertIndex has detected out of range index ! Index was : %d.", (int) index);

                APRO_THROW("Out of range", buffer, "Array");

#endif

                return false;
            }
        }

        /** @brief Append an object to the array. */
        Array<T>& operator << (const T& obj)
        {
            append(obj);
            return *this;
        }

        /** @brief Append an array to this one. */
        Array<T>& operator << (const Array<T>& array)
        {
            append(array);
            return *this;
        }

        /** @brief Set the content of this array to given one. */
        Array<T>& operator = (const Array<T>& array)
        {
            clear();
            append(array);
            return *this;
        }

        /** @brief Tell if array is same as given. */
        bool operator == (const Array<T>& array) const
        {
            if(getSize() != array.getSize())
                return false;

            /*

            for(size_t i = 0; i < getSize(); i++)
            {
                if(at(i) != array.at(i))
                    return false;
            }

            */

            return memcmp(first, array.first, getSize()) == 0;
        }

        /** @brief Contrary of operator == . */
        bool operator != (const Array<T>& array) const
        {
            return !(*this == array);
        }

        /** @brief Find the index of an object in the array.
         *  @note Might return -1 if not found.
         *  @warning Object must have a == operator.
         */
        int find(const T& obj) const
        {
            for(size_t i = 0; i < size; i++)
            {
                if(at(i) == obj)
                    return i;
            }

            return -1;
        }

        /** @brief Return an array of object from given position. */
        Array<T> extractArray(size_t position, size_t sz)
        {
            Array<T> ret;

            if(position >= size)
                return ret;

            if(position + sz > size)
                sz = size - position;

            ret.append(first + position, sz);
        }

        void resize(size_t new_size)
        {
            if(new_size == 0)
            {
                clear();
                return;
            }

            if(first)
            {
                if(new_size > size)
                {
                    reserve(new_size);
                    for(i = 0; i < new_size - size; ++i)
                        push_back(T());
                }
                else if(new_size < size)
                {
                    if(new_size * 2 < size)
                    {
                        size_t size_to_erase = size - new_size * 2;
                        erase(new_size * 2 - 1, size - 1);
                    }

                    size = new_size;
                }
            }
            else
            {
                reserve(new_size);
                for(i = 0; i < new_size; ++i)
                    push_back(T());
            }
        }

    };

    typedef Array<Byte> ByteArray;
}

#endif
