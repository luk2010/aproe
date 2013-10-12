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

#include "STDUtils.h"

namespace APro
{
    /////////////////////////////////////////////////////////////
    /** @class CArray
     *  @ingroup Memory
     *  @brief A C-style array.
     *  @details This array has a fixed size. If you change the size,
     *  you reallocate the whole array and destroy the previous
     *  content.
     *  @note Destructors are called when destroying each object.
     *  @note Use the changeSize method to reallocate the Array
     *  without destroying his content.
    **/
    /////////////////////////////////////////////////////////////
    template <typename Type>
    class CArray : public Copyable<CArray<Type> >,
                   public Printable
    {
    private:

        Type*        m_array;///< Pointer to the array.
        unsigned int m_size;///< Size of the array.

    private:

        /////////////////////////////////////////////////////////////
        /** @brief Allocate a new array.
         *  @internal
        **/
        /////////////////////////////////////////////////////////////
        void _allocate_array()
        {
            if(m_size > 0)
            {
                if(m_array)
                {
                    _deallocate_array();
                }

                m_array = AProNewA(Type, m_size);

                if(!m_array)
                {
                    m_size = 0;
                    m_array = nullptr;
                }
            }
        }

        /////////////////////////////////////////////////////////////
        /** @brief Copy the content of an size-equally array.
         *  @internal
        **/
        /////////////////////////////////////////////////////////////
        void _copy_content(const Type* array)
        {
            if(m_size > 0 && m_array)
            {
                Std::Memcpy(m_array, array, _real_size());
            }
        }

        /////////////////////////////////////////////////////////////
        /** @brief Deallocate current array.
        **/
        /////////////////////////////////////////////////////////////
        void _deallocate_array()
        {
            if(m_array && m_size > 0)
            {
                for(unsigned int i = 0; i < m_size; ++i)
                {
                    (&(m_array[i]))->~Type();
                }

                AProDelete(m_array);
                m_array = nullptr;
                m_size = 0;
            }
        }

        /////////////////////////////////////////////////////////////
        /** @brief Return the byte size of the array.
        **/
        /////////////////////////////////////////////////////////////
        unsigned int _real_size()
        {
            return m_size * sizeof(Type);
        }

    public:

        /////////////////////////////////////////////////////////////
        /** @brief Constructor with defined size.
        **/
        /////////////////////////////////////////////////////////////
        CArray(unsigned int size)
            : m_array(nullptr), m_size(size)
        {
            _allocate_array();
        }

        /////////////////////////////////////////////////////////////
        /** @brief Constructor from other array.
        **/
        /////////////////////////////////////////////////////////////
        CArray(const CArray<Type>& other)
            : m_array(nullptr), m_size(other.getSize())
        {
            _allocate_array();
            _copy_content(other.getArray());
        }

        /////////////////////////////////////////////////////////////
        /** @brief Destructor.
        **/
        /////////////////////////////////////////////////////////////
        ~CArray()
        {
            _deallocate_array();
        }

        /////////////////////////////////////////////////////////////
        /** @brief Return the size of the array, in Object unit.
        **/
        /////////////////////////////////////////////////////////////
        unsigned int getSize() const
        {
            return m_size;
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

        /////////////////////////////////////////////////////////////
        /** @see Copyable::copyFrom
        **/
        /////////////////////////////////////////////////////////////
        void copyFrom(const CArray<Type>& other)
        {
            _deallocate_array();
            m_size = other.getSize();
            _allocate_array();
            _copy_content(other.getArray());
        }

        /////////////////////////////////////////////////////////////
        /** @see Copyable::operator==
        **/
        /////////////////////////////////////////////////////////////
        bool operator == (const CArray<Type>& other) const
        {
            if(getSize() != other.getSize())
                return false;

            return Std::Memcmp(m_array, other.getArray(), _real_size());
        }

        /////////////////////////////////////////////////////////////
        /** @brief Clear the array.
        **/
        /////////////////////////////////////////////////////////////
        void clear()
        {
            _deallocate_array();
        }

        /////////////////////////////////////////////////////////////
        /** @brief Change the current size of the array.
         *  @param size : new size
        **/
        /////////////////////////////////////////////////////////////
        void changeSize(unsigned int size)
        {
            if(size == 0)
                clear();

            Type* tmp = m_array;
            unsigned int tmp_sz = m_size;

            // Allocate new array
            m_size = size;
            m_array = nullptr;
            _allocate_array();

            // Copy old array
            if(size > tmp_sz)
                m_size = tmp_sz;
            _copy_content(tmp);

            // Delete old array
            m_size = tmp_sz;
            Type* tmp2 = m_array;
            m_array = tmp;
            _deallocate_array();

            m_size = size;
            m_array = tmp2;
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
            console << "C Array { Size = " << getSize() << " } ";
        }
    };
}

#endif // APRO_CARRAY_H
