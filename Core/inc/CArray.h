/////////////////////////////////////////////////////////////
/** @file CArray.h
 *  @ingroup Memory
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 25/05/2013 - 15/12/2014
 *
 *  @brief
 *  Defines a C-style array.
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
 *
**/
/////////////////////////////////////////////////////////////
#ifndef APRO_CARRAY_H
#define APRO_CARRAY_H

#include "Platform.h"

#include "BaseObject.h"
#include "Copyable.h"
#include "Swappable.h"
#include "Printable.h"

namespace APro
{
    /////////////////////////////////////////////////////////////
    /** @class CArray
     *  @ingroup Utils
     *  @brief A fixed size array.
     *
     *  Objects in are dynamicly managed as in Array, but the size
     *  of this array is fixed. You cannot change it.
     *
     *  It may be very much more quick to use a CArray instead of
     *  Array if you already know the size and do not need to change
     *  it.
     *
     *  It is managed the same way a classic C-array is managed.
     *  An array is created in the constructor and is destroyed
     *  in the destructor. These operations are made
     *  automaticly in the clear() function.
    **/
    /////////////////////////////////////////////////////////////
    template <typename Type, int S, AllocatorPool PoolNum = AllocatorPool::Default>
    class CArray : public Copyable<CArray<Type, S, PoolNum> >,
                   public Swappable<CArray<Type, S, PoolNum> >,
                   public BaseObject<CArray<Type, S, PoolNum>, PoolNum >,
                   public Printable
    {
    public:

        typedef typename CArray <Type,S,PoolNum> CArrayT;
        Type*  m_array;///< Pointer to the array.
        enum { Size = S; /**< Size of the array. */ };

    public:

        /////////////////////////////////////////////////////////////
        /** @brief Return the size of this array.
        **/
        /////////////////////////////////////////////////////////////
        unsigned int size() const { return Size; }

        /////////////////////////////////////////////////////////////
        /** @brief Return the byte size of the array.
        **/
        /////////////////////////////////////////////////////////////
        unsigned int bitsSize()
        {
            return Size * sizeof(Type);
        }

    public:

        // Iterators and co.

        typedef Type* iterator;
        typedef const Type* const_iterator;

        iterator begin() { return (iterator) m_array; }
        const_iterator begin() const { return (const_iterator) m_array; }

        iterator end() { return (const_iterator) m_array + Size; }
        const_iterator end() const { return (const_iterator) m_array + Size; }

    private:

        /////////////////////////////////////////////////////////////
        /** @brief Allocates the Array.
        **/
        /////////////////////////////////////////////////////////////
        void allocate_array()
        {
            if(!m_array)
            {
                m_array = Allocator<PoolNum>::Get().New<Type>(Size);
            }
        }

        /////////////////////////////////////////////////////////////
        /** @brief Deallocates the Array.
         **/
        /////////////////////////////////////////////////////////////
        void deallocate_array()
        {
            if(m_array)
            {
                Allocator<PoolNum>::Get().Delete(m_array);
                m_array = nullptr;
            }
        }

    public:

        /////////////////////////////////////////////////////////////
        /** @brief Constructor with defined size.
        **/
        /////////////////////////////////////////////////////////////
        CArray()
            : m_array(nullptr)
        {
            allocate_array();
        }

        /////////////////////////////////////////////////////////////
        /** @brief Constructor from other array.
        **/
        /////////////////////////////////////////////////////////////
        CArray(const CArrayT& other)
            : m_array(nullptr)
        {
            allocate_array();
            set(other);
        }
        
        /////////////////////////////////////////////////////////////
        /** @brief Move an Array.
        **/
        /////////////////////////////////////////////////////////////
        CArray(CArrayT&& rhs)
        {
            m_array = rhs.m_array;
            rhs.m_array = nullptr;
        }

        /////////////////////////////////////////////////////////////
        /** @brief Destructor.
        **/
        /////////////////////////////////////////////////////////////
        ~CArray()
        {
            deallocate_array();
        }

        /////////////////////////////////////////////////////////////
        /** @brief Return the physical aadress of the array.
        **/
        /////////////////////////////////////////////////////////////
        Type* getArray()
        {
            return m_array;
        }

        /////////////////////////////////////////////////////////////
        /** @brief Return the physical aadress of the array.
        **/
        /////////////////////////////////////////////////////////////
        const Type* getArray() const
        {
            return m_array;
        }

        operator Type* () { return m_array; }
        operator const Type* () const { return m_array; }

        /////////////////////////////////////////////////////////////
        /** @see Copyable::copyFrom
        **/
        /////////////////////////////////////////////////////////////
        void copyFrom(const CArrayT& other)
        {
            for(unsigned int i = 0; i < S, ++i)
            {
                m_array[i] = other[i];
            }
        }

        /////////////////////////////////////////////////////////////
        /** @see Copyable::operator==
        **/
        /////////////////////////////////////////////////////////////
        bool operator == (const CArrayT& other) const
        {
            if(getSize() != other.getSize())
                return false;

            for(unsigned int i = 0; i < S; ++i)
            {
                if(!(m_array[i] == other[i]))
                    return false;
            }

            return true;
        }

        /////////////////////////////////////////////////////////////
        /** @brief Clear the array.
         *
         *  This function reset every objects in the array, but doesn't
         *  deallocate them.
         *
         *  @note It calls destructors of every objects.
        **/
        /////////////////////////////////////////////////////////////
        void clear()
        {
            deallocate_array();
            allocate_array();
        }

        /////////////////////////////////////////////////////////////
        /** @brief Access the array.
        **/
        /////////////////////////////////////////////////////////////
        Type& operator[] (unsigned int index)
        {
            return m_array[index];
        }

        /////////////////////////////////////////////////////////////
        /** @brief Access the array.
        **/
        /////////////////////////////////////////////////////////////
        const Type& operator[] (unsigned int index) const
        {
            return m_array[index];
        }

        /////////////////////////////////////////////////////////////
        /** @see Printable::print
        **/
        /////////////////////////////////////////////////////////////
        void print(Console& console) const
        {
            console << "CArray { Type = \"" << className<Type>() << "\", Size = \"" << S << "\" } ";
        }
        
        ////////////////////////////////////////////////////////////
        /** @brief Swap this object with another one from the same
         *  kind.
        **/
        ////////////////////////////////////////////////////////////
        void swap(CArrayT& obj)
        {
            std::swap (m_array, obj.m_array);
        }
    };
}

#endif // APRO_CARRAY_H
