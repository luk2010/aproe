/////////////////////////////////////////////////////////////
/** @file Queue.h
 *  @ingroup Utils
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 03/07/2013
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
     *  @details The concept of the queue is a classic first-in
     *  first-out container. You stores one by one every objects,
     *  and then you access them in the same order as you pushed
     *  them.
    **/
    /////////////////////////////////////////////////////////////
    template<typename T>
    class Queue : public Copyable<QUeue>,
                  public Printable
    {
    protected:

        Array<T> m_queue;

    public:

        /////////////////////////////////////////////////////////////
        /** @brief Constructor.
         *
         *  You can specify the capacity of the queue, i.e. a reserved
         *  space to allocate quicker objects.
        **/
        /////////////////////////////////////////////////////////////
        Queue(unsigned int capacity = 0)
        {
            if(capacity)
                m_queue.reserve(capacity);
        }

        /////////////////////////////////////////////////////////////
        /** @brief Constructor from classic array.
        **/
        /////////////////////////////////////////////////////////////
        explicit Queue(const Array<T>& other)
        {
            m_queue = other;
        }

        /////////////////////////////////////////////////////////////
        /** @brief Constructor for copy.
         *
         *  This function use the regular Array copy function, so copy
         *  constructors are not called.
        **/
        /////////////////////////////////////////////////////////////
        Queue(const Queue<T>& other)
        {
            m_queue = other.m_queue;
        }

        /////////////////////////////////////////////////////////////
        /** @brief Constructor from a C style array.
         *
         *  @param c_queue : pointer to the first element of the
         *  queue.
         *  @param sz : Size of the queue.
        **/
        /////////////////////////////////////////////////////////////
        explicit Queue(const T* c_queue, unsigned int sz)
        {
            m_queue.append(c_queue, sz);
        }

        /////////////////////////////////////////////////////////////
        /** @brief Destructor.
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
            console << "Queue <" << className<T>() << "> { size : " << m_queue.getSize() << ", capacity : " << m_queue.getPhysicalSize() << " }";
        }

    public: // Copyable

        /////////////////////////////////////////////////////////////
        /** @see Copyable::copyFrom
        **/
        /////////////////////////////////////////////////////////////
        void copyFrom(const Queue<T>& other)
        {
            m_queue = other.m_queue;
        }

        /////////////////////////////////////////////////////////////
        /** @see Copyable::operator==
        **/
        /////////////////////////////////////////////////////////////
        bool operator == (const Queue<T>& other) const
        {
            return m_queue == other;
        }

    public:

        /////////////////////////////////////////////////////////////
        /** @brief Add an object at the beginning of the queue.
         *
         *  In this order, this object will be the last given with the
         *  ::popg function.
        **/
        /////////////////////////////////////////////////////////////
        void push(const T& object)
        {
            m_queue.prepend(object);
        }

        /////////////////////////////////////////////////////////////
        /** @brief Remove the firts object in the queue.
        **/
        /////////////////////////////////////////////////////////////
        void pop()
        {
            m_queue.erase(m_queue.getSize() - 1);
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
            return m_queue.getSize();
        }

        /////////////////////////////////////////////////////////////
        /** @brief Return the capacity of the queue.
        **/
        /////////////////////////////////////////////////////////////
        unsigned int capacity() const
        {
            return m_queue.getPhysicalSize();
        }

    public:

        /////////////////////////////////////////////////////////////
        /** @brief Return the current first object in the queue.
        **/
        /////////////////////////////////////////////////////////////
        T& get()
        {
            return m_queue.at(m_queue.getSize() - 1);
        }

        /////////////////////////////////////////////////////////////
        /** @brief Return the current first object in the queue.
        **/
        /////////////////////////////////////////////////////////////
        const T& get() const
        {
            return m_queue.at(m_queue.getSize() - 1);
        }

        /////////////////////////////////////////////////////////////
        /** @brief Return the last object and remove it from the queue.
         *
         *  The object given is so a copy of the original object.
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
