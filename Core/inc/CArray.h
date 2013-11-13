/////////////////////////////////////////////////////////////
/** @file CArray.h
 *  @ingroup Memory
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 25/05/2013
 *
 *  Defines a C-style array.
 *
**/
/////////////////////////////////////////////////////////////
#ifndef APRO_CARRAY_H
#define APRO_CARRAY_H

#include "Platform.h"

#include "Copyable.h"
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
    template <typename Type, int S>
    class CArray : public Copyable<CArray<Type, S> >,
                   public Printable
    {
    public:

        Type   m_array;///< Pointer to the array.
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

        void allocate_array()
        {
            if(!m_array)
            {
                m_array = AProNewA(Type, Size);
            }
        }

        void deallocate_array()
        {
            if(m_array)
            {
                AProDelete(m_array);
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
        CArray(const CArray<Type, S>& other)
            : m_array(nullptr)
        {
            allocate_array();
            set(other);
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

        Type* operator Type* () { return m_array; }
        const Type* operator Type* const () { return m_array; }

        /////////////////////////////////////////////////////////////
        /** @see Copyable::copyFrom
        **/
        /////////////////////////////////////////////////////////////
        void copyFrom(const CArray<Type, S>& other)
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
        bool operator == (const CArray<Type>& other) const
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
            console << "C Array { Type = \"" << className<Type>() << "\", Size = \"" << S << "\" } ";
        }
    };
}

#endif // APRO_CARRAY_H
