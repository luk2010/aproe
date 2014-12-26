////////////////////////////////////////////////////////////
/** @file Atomic.h
 *  @ingroup Thread
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 01/12/2013 - 11/12/2014
 *
 *  @brief
 *  Defines the Atomic class.
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
////////////////////////////////////////////////////////////
#ifndef APRO_ATOMIC_H
#define APRO_ATOMIC_H

#include "Platform.h"
#include "ThreadMutexLockGuard.h"

namespace APro
{
    ////////////////////////////////////////////////////////////
    /** @class Atomic
     *  @ingroup Thread
     *  @brief A variable holding a mutex and a value.
     *
     *  An atomic object is an object that can automaticly used in
     *  threaded applications. It holds base type objects, and can
     *  be used normally without taking care of mutexes locks.
    **/
    ////////////////////////////////////////////////////////////
    template<typename T>
    class Atomic : public Swappable<Atomic<T> >
    {
    protected:

        mutable  ThreadMutexI mutex;///< Mutex holding the value.
        volatile T            value;///< Value of our atomic.

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Constructs an empty atomic object.
        **/
        ////////////////////////////////////////////////////////////
        Atomic()
        {

        }

        ////////////////////////////////////////////////////////////
        /** @brief Constructs an atomic object from a given value.
        **/
        ////////////////////////////////////////////////////////////
        Atomic(const T& v)
            : value(v)
        {

        }

        ////////////////////////////////////////////////////////////
        /** @brief Constructs an atomic object from a given atomic.
        **/
        ////////////////////////////////////////////////////////////
        Atomic(const Atomic<T>& atom)
            : value(atom.get())
        {

        }
        
        ////////////////////////////////////////////////////////////
        /** @brief Construct this atomic from moving the given one.
         *  
         *  @note
         *  Given Atomic is unvalidated after this operation.
        **/
        ////////////////////////////////////////////////////////////
        Atomic(Atomic<T>&& rhs)
        {
            swap(rhs);
        }

        ////////////////////////////////////////////////////////////
        /** @brief Destructs the atomic.
        **/
        ////////////////////////////////////////////////////////////
        ~Atomic()
        {

        }
        
        ////////////////////////////////////////////////////////////
        /** @brief Swap this object with another one from the same
         *  kind.
         *
         *  @note
         *  The lhs and rhs mutex are both locked during this process.
        **/
        ////////////////////////////////////////////////////////////
        void swap(Atomic<T>& rhs)
        {
            THREADMUTEXAUTOLOCK(mutex);
            THREADMUTEXAUTOLOCK(rhs.mutex);
            using std::swap;
            swap(value, rhs.value);
        }

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Returns the value of this atomic.
        **/
        ////////////////////////////////////////////////////////////
        T get() const
        {
            THREADMUTEXAUTOLOCK(mutex);
            return value;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Change the value of this atomic.
        **/
        ////////////////////////////////////////////////////////////
        void set(const T& v)
        {
            THREADMUTEXAUTOLOCK(mutex);
            value = v;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Returns true if holded value is equal to given one.
        **/
        ////////////////////////////////////////////////////////////
        bool equals(const T& v)
        {
            THREADMUTEXAUTOLOCK(mutex);
            return value == v;
        }

    public:

        Atomic<T>& operator = (const Atomic<T>& atom)
        {
            set(atom.get());
            return *this;
        }

        Atomic<T>& operator = (const T& v)
        {
            set(v);
            return *this;
        }

    public:

        bool operator == (const Atomic<T>& atom) const
        {
            return equals(atom.get());
        }

        bool operator == (const T& atom) const
        {
            return equals(atom);
        }

        operator T() const
        {
            return get();
        }
    };

    typedef Atomic<bool> AtomicBool;

    ////////////////////////////////////////////////////////////
    /** @class AtomicNum
     *  @ingroup Thread
     *  @brief An Atomic specialization for every numeric type.
    **/
    ////////////////////////////////////////////////////////////
    template<typename T>
    class AtomicNum : public Atomic<T>
    {
    public:

        ////////////////////////////////////////////////////////////
        /** @brief Constructs an empty AtomicNum.
         *  @note Value is setted to 0.
        **/
        ////////////////////////////////////////////////////////////
        AtomicNum()
            : Atomic<T>(0)
        {

        }

        ////////////////////////////////////////////////////////////
        /** @brief Constructs an AtomicNum from given value.
        **/
        ////////////////////////////////////////////////////////////
        AtomicNum(const T& v)
            : Atomic<T>(v)
        {

        }

        ////////////////////////////////////////////////////////////
        /** @brief Destructs the AtomicNum.
        **/
        ////////////////////////////////////////////////////////////
        ~AtomicNum()
        {

        }

    public:

#define MAKEOP(op) \
    AtomicNum<T> operator op (const T& v)               const { THREADMUTEXAUTOLOCK( Atomic<T>::mutex ); return AtomicNum(Atomic<T>::value op v); } \
    AtomicNum<T> operator op (const AtomicNum<T>& atom) const { return *this op atom.get(); }

        MAKEOP(+)
        MAKEOP(-)
        MAKEOP(/)
        MAKEOP(*)

#undef  MAKEOP
#define MAKEOP(op) \
    AtomicNum<T>& operator op (const T& v)               { THREADMUTEXAUTOLOCK( Atomic<T>::mutex ); Atomic<T>::value = v; return *this; } \
    AtomicNum<T>& operator op (const AtomicNum<T>& atom) { return *this op atom.get(); }

        MAKEOP(+=)
        MAKEOP(-=)
        MAKEOP(/=)
        MAKEOP(*=)

#undef MAKEOP

    };

    typedef AtomicNum<int>    AtomicInt;
    typedef AtomicNum<float>  AtomicFloat;
    typedef AtomicNum<double> AtomicDouble;
}

#endif // APRO_ATOMIC_H
