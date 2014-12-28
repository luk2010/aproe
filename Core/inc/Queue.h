/////////////////////////////////////////////////////////////
/** @file Queue.h
 *  @ingroup Utils
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 03/07/2013 - 28/12/2014
 *
 *  Defines a queue.
 *
 **/
/////////////////////////////////////////////////////////////
#ifndef APRO_QUEUE_H
#define APRO_QUEUE_H

#include <Array.h>
#include <Copyable.h>
#include <Printable.h>

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
     *  Queue should be copyable too.
    **/
    /////////////////////////////////////////////////////////////
    template<typename T, typename Container = Array<T> >
    class Queue : public Copyable<Queue <T, Container> >,
                  public Printable
    {
    protected:

        typedef Queue<T, Container> queue_t;
        Container m_queue;///< The container object.

    public:

        /////////////////////////////////////////////////////////////
        /** @brief Constructs a Queue without objects.
        **/
        /////////////////////////////////////////////////////////////
        Queue() { }

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
}

#endif // APRO_QUEUE_H
