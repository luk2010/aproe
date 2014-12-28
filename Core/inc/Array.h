/////////////////////////////////////////////////////////////
/** @file Array.h
 *  @ingroup Utils
 *  @brief Defines the Array class.
 *
 *  @author Luk2010
 *  @date 29/05/2012 - 28/12/2014
 *
 *  @copyright
 *  Atlanti's Project Engine
 *  Copyright (C) 2012 - 2014  Atlanti's Corp
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
**/
////////////////////////////////////////////////////////////
#ifndef APROARRAY_H
#define APROARRAY_H

#include "Platform.h"
#include "Swappable.h"
#include "BaseObject.h"

namespace APro
{
    ////////////////////////////////////////////////////////////
    /** @class Array
     *  @ingroup Utils
     *  @brief A dynamicly managed array.
     *
     *  Every elements are in a contiguous memory area, so you
     *  can access it as a normal C-style array.
     *
     *  Size is managed with a reserved space management. Because
     *  reallocation is very time-consuming, you can reserve space
     *  before pushing objects, so they will just be added as quick
     *  as a simple copy.
     *
     *  @note Constructors and destructors are called during every
     *  process. When you push an object, you copy this object and
     *  so the copy constructor will be called. If none found, or
     *  if object is not copy-constructible, only a basic memory
     *  copy will be performed.
     *
     *  @note If reserved space isn't set, and/or physical size of the
     *  array is equal to logical size, then erasing objects will reduce
     *  the size of it and will give a reallocation of the memory space.
     *
     *  The Array object can be used using the following pattern 
     *  (example is shown using ByteArray) :
     *  ```
     *  {
     *      ByteArray myarray; 
     *      myarray << Byte (0) << Byte (1) << Byte (2);
     *      // The Array is destroyed at the end of the scope.
     *  }
     *  
     *  {
     *      ByteArray* myarrayptr = ByteArray::New({Byte(0),Byte(1),Byte(2)});
     *      ByteArray::Delete(myarrayptr);
     *      // Using the BaseObject pattern.
     *  }
     *
     *  {
     *		typedef AutoPointer<ByteArray> ByteArrayPtr;
     *      ByteArrayPtr myarrayglblptr = ByteArray::New({Byte(0),Byte(1),Byte(2)});
     *      // The AutoPointer class release correctly the pointer, calling
     *      // ByteArray::Delete () function.
     *  }
     *  ```
    **/
    ////////////////////////////////////////////////////////////
    template <typename T, AllocatorPool PoolNum = AllocatorPool::Default>
    class Array : public BaseObject<Array<T, PoolNum> , PoolNum>,
                  public Swappable <Array<T, PoolNum> >
    {
    public:
        
        typedef typename Array<T, PoolNum> ArrayT;
        typedef char* ArrayData;
        
    protected:

        T* ptr;

        size_t logical_size;
        size_t physical_size;

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Constructs an empty array.
        **/
        ////////////////////////////////////////////////////////////
        Array() : ptr(nullptr), logical_size(0), physical_size(0) {}

        ////////////////////////////////////////////////////////////
        /** @brief Constructs an empty array and allocate some
         *  uninitialized space.
         *
         *  Use this constructor to benefit from big allocation to
         *  prevent numerous reallocation, that are slow.
         *
         *  @param r : Size to reserve, in number of elements.
        **/
        ////////////////////////////////////////////////////////////
        Array(size_t r) : ptr(nullptr), logical_size(0), physical_size(0)
        {
            aproassert(r > 0, "Initializing Array with null size !");
            reserve(r);
        }

        ////////////////////////////////////////////////////////////
        /** @brief Constructs an Array from C-style array.
         *
         *  Use this function to copy big array. But think that
         *  constructors will always be called for constructible objects.
        **/
        ////////////////////////////////////////////////////////////
        Array(const T* a, size_t sz) : ptr(nullptr), logical_size(0), physical_size(0)
        {
            aproassert(a && sz, "Initializing Array with invalid pointer.");
            reserve(sz);
            __assign_array(a, sz);
        }

        ////////////////////////////////////////////////////////////
        /** @brief Constructs an Array from another one.
        **/
        ////////////////////////////////////////////////////////////
        Array(const ArrayT& rhs) : ptr(nullptr), logical_size(0), physical_size(0)
        {
            if(rhs.size() > 0)
            {
                reserve(rhs.size());
                __assign_array(rhs.pointer(), rhs.size());
            }
        }
        
        ////////////////////////////////////////////////////////////
        /** @brief Move an Array of same type to this one.
         *  The given Array is let empty.
        **/
        ////////////////////////////////////////////////////////////
        Array(ArrayT&& rhs)
        {
            if(rhs.size() > 0)
            {
                ptr               = rhs.ptr;
                logical_size      = rhs.logical_size;
                physical_size     = rhs.physical_size;
                
                rhs.ptr           = nullptr;
                rhs.logical_size  = 0;
                rhs.physical_size = 0;
            }
        }
        
        ////////////////////////////////////////////////////////////
        /** @brief Initialize this Array with a given initializer_list.
        **/
        ////////////////////////////////////////////////////////////
        Array(std::initializer_list<T> l) : ptr(nullptr), logical_size(0), physical_size(0)
        {
            if(l.size() > 0)
            {
                reserve(l.size());
                if(Types::IsCopyConstructible<T>()) {
                    for(std::initializer_list<T>::const_iterator it = l.begin(); it != l.end(); it++) {
                        AProConstructedCopy (ptr + (it - l.begin), it, T);
                    }
                }
                else {
                    for(std::initializer_list<T>::const_iterator it = l.begin(); it != l.end(); it++) {
                        Memory::Copy (ptr + (it - l.begin), it, T);
                    }
                }
            }
        }

        ~Array()
        {
            clear();
        }

    private:
        
        ////////////////////////////////////////////////////////////
        /** @brief Allocate new memory space for the Array.
         *  @internal
         *
         *  @note
         *  This function use the Allocator<> system, allowing us to 
         *  keep track more easily of the memory allocated. We also
         *  can keep memory of our pointer in differents pools.
        **/
        ////////////////////////////////////////////////////////////
        T* __allocate (size_t* sz)
        {
            return (T*) Allocator<PoolNum>::Get().New<ArrayData>(sizeof(T) * sz);
        }

        ////////////////////////////////////////////////////////////
        /** @brief Assign an array of fixed size to this array.
         *  @internal
        **/
        ////////////////////////////////////////////////////////////
        void __assign_array(const T* a, size_t sz)
        {
            if(ptr && physical_size >= sz)
            {
                if(Types::IsCopyConstructible<T>())
                {
                    for(unsigned int i = 0; i < sz; ++i)
                    {
                        // Construct each object by copy.
                        AProConstructedCopy(&(ptr[i]), a[i], T);
                    }
                }
                else
                {
                    // Performs a Memory copy.
                    Memory::Copy(ptr, a, sz * sizeof(T));
                }

                logical_size = sz;
            }
        }

        ////////////////////////////////////////////////////////////
        /** @brief Copy an object to given array entry.
         *  @internal
        **/
        ////////////////////////////////////////////////////////////
        void __copy_object(const T& o, size_t index)
        {
            if(Types::IsCopyConstructible<T>())
            {
                AProConstructedCopy(ptr + index, o, T);
            }
            else
            {
                // Performs a Memory copy.
                Memory::Copy(ptr + index, &o, sizeof(T));
            }
        }

        ////////////////////////////////////////////////////////////
        /** @brief Destruct the array.
         *  @internal
         *
         *  @note
         *  As we use the Allocator<> system, we can keep track more 
         *  easily of our memory management. We use char* type to destroy
         *  the array but destructors are already called by 
         *  AProDestructObject<T> so we just need to release the memory.
        **/
        ////////////////////////////////////////////////////////////
        void __destroy_array()
        {
            if(ptr && logical_size)
            {
                // First call destructors on logical size.
                AProDestructObject<T>(ptr, logical_size, true);

                // Then release the array.
                //AProDelete((void*) ptr);
                Allocator<PoolNum>::Get().Delete<char>(ptr);
            }
        }

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Push an object to the end of the array.
         *
         *  @note The object is copied if possible, or only Byte
         *  copied.
        **/
        ////////////////////////////////////////////////////////////
        void push_back(const T& obj)
        {
            reserve(logical_size + 1);
            __copy_object(obj, logical_size);
            logical_size++;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Push an object to the end of the array.
         *
         *  @note The object is copied if possible, or only Byte
         *  copied.
        **/
        ////////////////////////////////////////////////////////////
        void append(const T& obj)
        {
            push_back(obj);
        }

        Array& operator << (const T& obj)
        {
            push_back(obj);
            return *this;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Push an object to the begin of the array.
         *
         *  This function might be long as it performs 2 Memory copy
         *  of the whole array (to move it to the right).
         *
         *  @note The object is copied if possible, or only Byte
         *  copied.
        **/
        ////////////////////////////////////////////////////////////
        void push_front(const T& obj)
        {
            reserve(logical_size + 1);

            // Moving memory to the right.
            Memory::CopyInterlaced(ptr + 1, ptr, logical_size * sizeof(T));

            // Now first block is empty, copying object.
            __copy_object(obj, 0);
            logical_size++;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Push an object to the begin of the array.
         *
         *  This function might be long as it performs 2 Memory copy
         *  of the whole array (to move it to the right).
         *
         *  @note The object is copied if possible, or only Byte
         *  copied.
        **/
        ////////////////////////////////////////////////////////////
        void prepend(const T& obj)
        {
            push_front(obj);
        }

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Push an array to the end of this array.
        **/
        ////////////////////////////////////////////////////////////
        void push_back(const Array<T>& a)
        {
            if(a.size())
            {
                reserve(a.size());
                for(unsigned int i = 0; i < a.size(); ++i)
                {
                    push_back(a[i]);
                }
            }
        }

        ////////////////////////////////////////////////////////////
        /** @brief Push an array to the end of this array.
        **/
        ////////////////////////////////////////////////////////////
        void append(const Array<T>& a) { push_back(a); }

        Array& operator << (const Array<T>& a)
        {
            push_back(a);
            return *this;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Push an array to the begin of this array.
         *
         *  A big move to the right of the memory is performed during
         *  this process.
        **/
        ////////////////////////////////////////////////////////////
        void push_front(const Array<T>& a)
        {
            push_front(a.pointer(), a.size());
        }

        ////////////////////////////////////////////////////////////
        /** @brief Push an array to the begin of this array.
         *
         *  A big move to the right of the memory is performed during
         *  this process.
        **/
        ////////////////////////////////////////////////////////////
        void prepend(const Array<T>& a)
        {
            push_front(a);
        }

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Push an array to the end of this array.
        **/
        ////////////////////////////////////////////////////////////
        void push_back(const T* a, size_t sz)
        {
            if(sz && a)
            {
                reserve(sz);
                for(unsigned int i = 0; i < sz; ++i)
                {
                    push_back(a[i]);
                }
            }
        }

        ////////////////////////////////////////////////////////////
        /** @brief Push an array to the end of this array.
        **/
        ////////////////////////////////////////////////////////////
        void append(const T* a, size_t sz) { push_back(a, sz); }

        ////////////////////////////////////////////////////////////
        /** @brief Push an array to the begin of this array.
         *
         *  A big move to the right of the memory is performed during
         *  this process.
        **/
        ////////////////////////////////////////////////////////////
        void push_front(const T* a, size_t sz)
        {
            if(!a || !sz) return;

            reserve(logical_size + sz);

            // Moving memory to the right.
            Memory::CopyInterlaced(ptr + sz, ptr, logical_size * sizeof(T));

            // Now block is empty, copying object.
            for(unsigned int i = 0; i < sz; ++i)
                __copy_object(*a, i);

            logical_size += sz;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Push an array to the begin of this array.
         *
         *  A big move to the right of the memory is performed during
         *  this process.
        **/
        ////////////////////////////////////////////////////////////
        void prepend(const T* a, size_t sz)
        {
            push_front(a, sz);
        }

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Return the number of object in this array.
        **/
        ////////////////////////////////////////////////////////////
        size_t size() const
        {
            return logical_size;
        }
        
        ////////////////////////////////////////////////////////////
        /** @brief Return the real size of this object (in number of
         *  objects).
        **/
        ////////////////////////////////////////////////////////////
        size_t physicalSize() const { return physical_size; }

        ////////////////////////////////////////////////////////////
        /** @brief Return the number of space available without
         *  reallocation in this array.
        **/
        ////////////////////////////////////////////////////////////
        size_t reservedSpaceAvailable() const { return physical_size - logical_size; }

        ////////////////////////////////////////////////////////////
        /** @brief Return a pointer to this array.
        **/
        ////////////////////////////////////////////////////////////
        T* pointer() { return ptr; }

        ////////////////////////////////////////////////////////////
        /** @brief Return a pointer to this array.
        **/
        ////////////////////////////////////////////////////////////
        const T* pointer() const { return ptr; }

    public:

        typedef T* iterator;
        typedef const T* const_iterator;

        iterator begin() { return pointer(); }
        const_iterator begin() const { return pointer(); }

        iterator end() { return begin() + logical_size; }
        const_iterator end() const { return begin() + logical_size; }

        iterator last() { return begin() + logical_size - 1; }
        const_iterator last() const { return begin() + logical_size - 1; }

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Reserve space for this array.
         *
         *  The reserved space take in account the logical size of
         *  the array. Use reservedSpaceAvailable() to know how much
         *  reserved space the array has.
         *
         *  @note
         *  If wanted reserved space is inferior to 2 times the physical
         *  size, the array will be reducted to that size even if objects
         *  are in this range, and will be destroyed.
        **/
        ////////////////////////////////////////////////////////////
        void reserve(size_t new_physical_size)
        {
            if(ptr)
            {
                if(new_physical_size > physical_size)
                {
                    // Reallocation of array.
                    T* tmp_array = (T*) Allocator<PoolNum>::Get().New<ArrayData>(new_physical_size * sizeof(T));

                    Memory::Copy(tmp_array, ptr, logical_size * sizeof(T));
                    AProDeallocate(ptr);

                    ptr = tmp_array;
                    physical_size = new_physical_size;
                }
                else if(new_physical_size == 0)
                {
                    // Destruction of array
                    clear();
                }
                else if(new_physical_size <= physical_size)
                {
                    // Erase object only if logical_size > new_physical_size so they will
                    // be destroyed and available if new_physical_size * 2 > physical_size.
                    if(new_physical_size < logical_size)
                    {
                        erase(begin() + new_physical_size, end());
                        logical_size = new_physical_size;
                    }
                }
            }
            else
            {
                // Allocate memory for the array.
                ptr = (T*) Allocator<PoolNum>::Get().New<ArrayData>(new_physical_size * sizeof(T));
                physical_size = new_physical_size;
            }
        }

        ////////////////////////////////////////////////////////////
        /** @brief Resize this array to fit given size, and fill
         *  new entries with given object.
        **/
        ////////////////////////////////////////////////////////////
        void resize(size_t new_size, const T& _cpy = T())
        {
            if(new_size > logical_size)
            {
                size_t old_size = logical_size;
                reserve(new_size);

                for(unsigned int i = old_size; i < new_size; ++i)
                {
                    push_back(_cpy);
                }
            }
            else if(new_size < logical_size)
            {
                if(new_size == 0)
                {
                    clear();
                }
                else
                {
                    erase(begin() + new_size, end());
                }
            }
        }

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Destruct the element at the given position and move
         *  the memory to the left by reducing the size by 1.
         *
         *  @note This function add a reserved space of 1 block.
        **/
        ////////////////////////////////////////////////////////////
        void erase(iterator position)
        {
            aproassert(position && position != end(), "Given position invalid !");

            // Destruct the object and set the size down of 1.
            if(ptr && logical_size)
            {
                AProDestructObject<T>(position, 1, false);
                Memory::CopyInterlaced(position, position + 1, (size_t) (end() - position + 1));

                logical_size -= 1;
            }
        }

        ////////////////////////////////////////////////////////////
        /** @brief Destruct the elements in the range [first, last[.
         *
         *  This function call destructors for each entry in the range
         *  from first wich is included to last <b>wich is not included</b>.
         *
         *  @note You should use the end() function to erase from somewhere
         *  to the end of the array.
        **/
        ////////////////////////////////////////////////////////////
        void erase(iterator first, iterator last)
        {
            aproassert(first && last && first != end() && first != last, "Given positions invalid !");

            if(first == begin() && last == end())
            {
                clear();
                return;
            }

            // Destruct objects between first and last and reduce the size.
            size_t number_of_elements = (size_t) (last - first);// Number of elements in bytes.
            number_of_elements /= sizeof(T);                  // Number of elements in objects.

            AProDestructObject<T>(first, number_of_elements, true);
            if(last != end())
                Memory::CopyInterlaced(first, last, (size_t) (end() - last));

            if(!reservedSpaceAvailable())
            {
                // Allocate just a new array of less big size.
                T* buffer = (T*) AProAllocate((logical_size - number_of_elements) * sizeof(T));
                Memory::Copy(buffer, ptr, (logical_size - number_of_elements) * sizeof(T));

                AProDeallocate(ptr);
                ptr = buffer;
            }

            logical_size -= number_of_elements;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Destroy the array.
         *
         *  Equivalent to erase(begin(), end()).
        **/
        ////////////////////////////////////////////////////////////
        void clear()
        {
            __destroy_array();
        }

        ////////////////////////////////////////////////////////////
        /** @brief Erase the reserved free space available.
        **/
        ////////////////////////////////////////////////////////////
        void clearReserve()
        {
            if(logical_size > 0)
            {
                T* tmp_array = (T*) AProAllocate(sizeof(T) * logical_size);
                Memory::Copy(tmp_array, ptr, sizeof(T) * logical_size);

                AProDeallocate(ptr);
                ptr = tmp_array;
                physical_size = logical_size;
            }
        }

    public:

        T& at(size_t index) {
            aproassert1(index < logical_size);
            return *(begin() + index);
        }
        const T& at(size_t index) const {
            aproassert1(index < logical_size);
            return *(begin() + index);
        }

        T& operator [] (size_t index) { return at(index); }
        const T& operator [] (size_t index) const { return at(index); }

        size_t toIndex(const_iterator& it) const { return ((size_t)(it - begin())) / sizeof(T); }

    public:

        bool isEmpty() const { return logical_size == 0; }

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Insert an object before the given position.
        **/
        ////////////////////////////////////////////////////////////
        void insert(iterator position, const T& obj)
        {
            if(position != end())
            {
                if(position == begin())
                {
                    push_front(obj);
                }
                else
                {
                    // Reserve space
                    reserve(logical_size + 1);

                    // Move memory to the right.
                    Memory::CopyInterlaced(position + 1, position, end() - position);

                    // Copy object
                    __copy_object(obj, toIndex(position));
                }
            }
            else
            {
                push_back(obj);
            }
        }

        ////////////////////////////////////////////////////////////
        /** @brief Insert numerous copy of objects before the given
         *  position.
         *
         *  @todo Performs a specialized CopyInterlaced instead of
         *  repeated Memory::Copy.
        **/
        ////////////////////////////////////////////////////////////
        void insert(iterator position, size_t n, const T& obj)
        {
            for(unsigned int i = 0; i < n; ++i)
                insert(position, obj);
        }

    public:

        Array<T>& operator = (const Array<T>& rhs)
        {
            clear();

            if(rhs.size())
            {
                reserve(rhs.size());
                __assign_array(rhs.pointer(), rhs.size());
            }

            return *this;
        }
        
        Array<T>& operator = (Array<T> rhs)
        {
            move(rhs);
            return *this;
        }
        
        ////////////////////////////////////////////////////////////
        /** @brief Swap two Arrays of same type.
         *  @note This is less efficient than using the operator =
         *  or Array::move() with std::move() to copy a returned 
         *  value.
        **/
        ////////////////////////////////////////////////////////////
        void swap (Array<T>& rhs)
        {
            std::swap(ptr,           rhs.ptr);
            std::swap(logical_size,  rhs.logical_size);
            std::swap(physical_size, rhs.physical_size);
        }

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Tells if an aray is equal to this one.
         *
         *  @note Objects must have a correct equality operator to
         *  performs this function.
        **/
        ////////////////////////////////////////////////////////////
        bool equals(const Array<T>& a) const
        {
            if (a.size() != size()) return false;
            else
            {
                for(unsigned int i = 0; i < size(); ++i)
                {
                    if(at(i) != a.at(i))
                        return false;
                }
            }

            return true;
        }

        bool operator == (const Array<T>& rhs) const { return equals(rhs); }

        ////////////////////////////////////////////////////////////
        /** @brief Return an iterator if given object is found in this
         *  array.
         *
         *  Objects must have a correct comparison function.
        **/
        ////////////////////////////////////////////////////////////
        const_iterator find(const T& obj) const
        {
            const_iterator it = begin();
            const_iterator it_e = end();

            while(it != it_e)
                if((*it) == obj)
                    return it;
                else
                    it++;

            return it_e;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Return an iterator if given object is found in this
         *  array.
         *
         *  Objects must have a correct comparison function.
        **/
        ////////////////////////////////////////////////////////////
        iterator find(const T& obj)
        {
            iterator it = begin();
            iterator it_e = end();

            while(it != it_e)
                if((*it) == obj)
                    return it;
                else
                    it++;

            return it_e;
        }
        
        ////////////////////////////////////////////////////////////
        /** @brief Returns true if this array contains given object
         *  caracteristic, according to the given compareason function.
         *
         *  @param rhs : The object to compare with.
         *  @param cmp : A function to use to compare objects in this array 
		 *  with the given object.
		 *
		 *  @note
		 *  This is equivalent to a Batch Compareason.
		 *
		 *  @return The iterator where the found object is, end() otherwise.
        **/
        ////////////////////////////////////////////////////////////
        template <typename T2>
        iterator find(const T2& rhs, std::function<bool(const T&, const T2)> cmp)
        {
        	for(iterator it = begin(); it != end(); it++) {
				if(cmp(*it, rhs)) {
					return it;
				}
        	}
        }
        
        ////////////////////////////////////////////////////////////
        /** @brief Returns true if this array contains given object
         *  caracteristic, according to the given compareason function.
         *
         *  @param rhs : The object to compare with.
         *  @param cmp : A function to use to compare objects in this array 
		 *  with the given object.
		 *
		 *  @note
		 *  This is equivalent to a Batch Compareason.
		 *
		 *  @return The iterator where the found object is, end() otherwise.
        **/
        ////////////////////////////////////////////////////////////
        template <typename T2>
        const_iterator find(const T2& rhs, std::function<bool(const T&, const T2)> cmp) const
        {
        	for(const_iterator it = begin(); it != end(); it++) {
				if(cmp(*it, rhs)) {
					return it;
				}
        	}
        }

        ////////////////////////////////////////////////////////////
        /** @brief Returns true if array contains given object.
        **/
        ////////////////////////////////////////////////////////////
        bool contains(const T& obj) const
        {
            return find(obj) != end();
        }
        
    public:
        
        ////////////////////////////////////////////////////////////
        /** @brief Set the data of this array to given one. 
         *  
         *  This array take ownership of the given pointer, assuming
         *  given size and deleting him at destruction.
         *
         *  @note Think to clear the array before using this function, 
         *  or your previous allocated memory will never be freed ! Use :
         *  ``` 
         *  if(!array.isEmpty()) array.clear();
         *  ```
        **/
        ////////////////////////////////////////////////////////////
        void acquireData(T* data, size_t lsz, size_t psz)
        {
            ptr = data;
            logical_size = lsz;
            physical_size = psz;
        }

    };

    typedef Array<HashType> HashArray;///< @brief An array of HashType.
    typedef Array<Byte>     ByteArray;///< @brief An array of Byte.
    typedef Array<char>     CharArray;///< @brief An Array of char.
}

#endif
