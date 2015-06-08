/////////////////////////////////////////////////////////////
/** @file Queue.h
 *  @ingroup Utils
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 03/07/2013 - 01/03/2015
 *
 *  @brief
 *  Defines a queue.
 *
 *  @copyright
 *  Atlanti's Project Engine
 *  Copyright (C) 2012 - 2015  Atlanti's Corp
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
#ifndef APRO_QUEUE_H
#define APRO_QUEUE_H

#include "Platform.h"
#include "Array.h"

#include "BaseObject.h"
#include "Copyable.h"
#include "Swappable.h"
#include "Printable.h"

namespace APro
{
    /////////////////////////////////////////////////////////////
    /** @class Queue
     *  @ingroup Utils
     *  @brief Defines a regular first-in first-out queue.
     *
     *  The concept of the queue is a classic first-in
     *  first-out container. You stores one by one every objects,
     *  and then you access them in the same order as you pushed
     *  them.
     *
     *  The Queue can have different containers, they just need to
     *  follow the standard containers methods. By defaut, container
     *  used is an Array.
     *
     *  @note Queue is a Copyable object, but objects pushed in the
     *  Queue should be copyable too. It can also be swapped.
    **/
    /////////////////////////////////////////////////////////////
    template<typename T, typename Container = Array<T> >
    class Queue
        : public BaseObject <Queue<T, Container> >,
          public Copyable<Queue<T, Container> >,
          public Swappable<Queue<T, Container> >,
          public Printable
    {
    protected:

        typedef Queue<T, Container> queue_t;
        Container m_queue;///< @brief The container object.

    public:

        /////////////////////////////////////////////////////////////
        /** @brief Constructs a Queue without objects.
        **/
        /////////////////////////////////////////////////////////////
        Queue() { /* Do nothing. */ }

        /////////////////////////////////////////////////////////////
        /** @brief Constructs a Queue from a Container.
        **/
        /////////////////////////////////////////////////////////////
        explicit Queue(const Container& other) : m_queue(other) { }

        /////////////////////////////////////////////////////////////
        /** @brief Constructs from a copy object.
        **/
        /////////////////////////////////////////////////////////////
        Queue(const queue_t& other) : m_queue(other.m_queue) { }
        
        /////////////////////////////////////////////////////////////
        /** @brief Constructs from a moved object.
         **/
        /////////////////////////////////////////////////////////////
        Queue(Queue<T, Container>&& rhs)
            : m_queue(std::move(rhs.m_queue))
        {
            /* Do nothing. */
        }

        /////////////////////////////////////////////////////////////
        /** @brief Destructs the Queue.
        **/
        /////////////////////////////////////////////////////////////
        ~Queue()
        {
            m_queue.clear();
        }

    public: // Print

        /////////////////////////////////////////////////////////////
        /** @see Printable::print
        **/
        /////////////////////////////////////////////////////////////
        void print(Console& console) const
        {
            console << "Queue <" << className<T>() << ", " << className<Container>() << "> { size : " << (int) m_queue.size() << " }";
        }

    public: // Copyable

        /////////////////////////////////////////////////////////////
        /** @see Copyable::copyFrom
        **/
        /////////////////////////////////////////////////////////////
        void copyFrom(const queue_t& other)
        {
            m_queue = other.m_queue;
        }

        /////////////////////////////////////////////////////////////
        /** @see Copyable::operator==
        **/
        /////////////////////////////////////////////////////////////
        bool operator == (const queue_t& other) const
        {
            return m_queue == other.m_queue;
        }
        
    public:
        
        ////////////////////////////////////////////////////////////
        /** @brief Swap this object with another one from the same
         *  kind.
        **/
        ////////////////////////////////////////////////////////////
        void swap(Queue<T, Container>& obj);

    public:

        /////////////////////////////////////////////////////////////
        /** @brief Push an object in the Queue.
         *
         *  It prepends the element in the Container, and it will be the
         *  last popped object.
        **/
        /////////////////////////////////////////////////////////////
        void push(const T& object)
        {
            m_queue.prepend(object);
        }

        /////////////////////////////////////////////////////////////
        /** @brief Remove the last object in the Container.
        **/
        /////////////////////////////////////////////////////////////
        void pop()
        {
            m_queue.erase(m_queue.begin() + (m_queue.size() - 1));
        }

        /////////////////////////////////////////////////////////////
        /** @brief Clear the whole queue.
        **/
        /////////////////////////////////////////////////////////////
        void clear()
        {
            m_queue.clear();
        }

    public:

        /////////////////////////////////////////////////////////////
        /** @brief Return the size of the queue.
        **/
        /////////////////////////////////////////////////////////////
        unsigned int size() const
        {
            return m_queue.size();
        }
        
        /////////////////////////////////////////////////////////////
        /** @brief Return True if empty.
        **/
        /////////////////////////////////////////////////////////////
        bool isEmpty() const
        {
        	return m_queue.isEmpty();
        }

    public:

        /////////////////////////////////////////////////////////////
        /** @brief Return the last object in the Container.
        **/
        /////////////////////////////////////////////////////////////
        T& get()
        {
            return m_queue.at(m_queue.size() - 1);
        }

        /////////////////////////////////////////////////////////////
        /** @brief Return the last object in the Container.
        **/
        /////////////////////////////////////////////////////////////
        const T& get() const
        {
            return m_queue.at(m_queue.size() - 1);
        }

        /////////////////////////////////////////////////////////////
        /** @brief Return the last object and remove it from the queue.
         *
         *  The object given is so a copy of the original object.
         *
         *  @note Using Queue::get() then Queue::pop() is recommended
         *  instead of Queue::popg() because there isn't any copy in the
         *  first method.
        **/
        /////////////////////////////////////////////////////////////
        T popg()
        {
            T ret(get());
            pop();
            return ret;
        }

    };
    
    template<typename T, typename Container>
    void Queue<T, Container>::swap(Queue<T, Container>& obj)
    {
        using std::swap;
        swap(m_queue, obj.m_queue);
    }
}

#endif // APRO_QUEUE_H
