/////////////////////////////////////////////////////////////
/** @file List.h
 *  @ingroup Utils
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 18/11/2013
 *
 *  Defines the List container.
 *
**/
/////////////////////////////////////////////////////////////
#ifndef APROLIST_H
#define APROLIST_H

#include "Platform.h"
#include "Allocator.h"
#include "Array.h"
#include <typeinfo>

namespace APro
{
    /////////////////////////////////////////////////////////////
    /** @class List
     *  @ingroup Utils
     *  @brief A Simple Linked List.
     *
     *  This container is a simple linked list. Each Node has
     *  a pointer to the next Node.
     *
     *  This is a different approach from Array, because push_front
     *  will be much quicker, but push_back will be less. You
     *  should use the List when you will have to prepend many objects
     *  quickly.
     *
     *  Access also is less quick than Array.
     *
     *  @note Constructors and Destructor of data are called during
     *  copy and destruction.
    **/
    /////////////////////////////////////////////////////////////
    template <typename T>
    class List
    {
    protected:

        /////////////////////////////////////////////////////////////
        /** @brief Describe a Node in the List.
         *
         *  At construction, Node allocate memory for data and construct
         *  a copy using placement new and AProConstructedCopy.
         *
         *  At destruction, data is destroyed (calling destructor) and
         *  then memory is deallocated.
        **/
        /////////////////////////////////////////////////////////////
        class Node
        {
        public:

            T* data;
            Node* next;

            Node(const T& other)
                : data(nullptr), next(nullptr)
            {
                data = (T*) AProAllocate(sizeof(T));
                AProConstructedCopy(data, other, T);
            }

            Node(const Node<T>& other)
                : data(nullptr), next(nullptr)
            {
                data = (T*) AProAllocate(sizeof(T));
                AProConstructedCopy(data, *(other.data), T);
            }

            ~Node()
            {
                AProDestructObject(data);
                AProDeallocate(data);
            }
        };

        /** @brief An iterator through nodes. */
        class NodeIter
        {
        public:
            Node* n;

            NodeIter() : n(nullptr) {}
            NodeIter(const Node* _node) : n(_node) {}
            NodeIter(const NodeIter& it) : n(it.n) {}

            T* operator T*() { return n ? n->data : nullptr; }
            const T* operator T*() const { return n ? n->data : nullptr; }

            void operator++() { if(n) n = n->next; }
            NodeIter operator + (size_t n) { NodeIter it = *this; while(n) { it++; n--; } return it; }
            const NodeIter operator + (size_t n) const { NodeIter it = *(const_cast<NodeIter*>(this)); while(n) { it++; n--; } return it; }

            T& operator *() { return *(n->data); }
            const T& operator *() const { return *(n->data); }

            T* operator ->() { return n ? n->data : nullptr; }
            const T* operator ->() const { return n ? n->data : nullptr; }

            bool operator == (const NodeIter& it) const { return n == it.n; }
            bool operator != (const NodeIter& it) const { return n != it.n; }

            NodeIter& operator = (const NodeIter& other) { n = other.n; return *this; }
        };

    public:

        Node*  first;///< First Node of the List.
        Node*  last; ///< Last Node of the list.
        size_t sz;   ///< Size of the List (number of elements).

        typedef NodeIter iterator;              ///< Iterator through nodes.
        typedef const NodeIter const_iterator;  ///< Constant Iterator through nodes.

        /** @brief Return an iterator to the first node. */
        iterator begin() { return NodeIter(first); }
        /** @brief Return an iterator to the first node. */
        const_iterator begin() const { return NodeIter(first); }

        /** @brief Return an iterator to the node after the Last node, i.e. always null. */
        iterator end() { return NodeIter(nullptr); }
        /** @brief Return an iterator to the node after the Last node, i.e. always null. */
        const_iterator end() const { return NodeIter(nullptr); }

    public:

        typedef List<T> list_t;

        /////////////////////////////////////////////////////////////
        /** @brief Constructs an empty list.
        **/
        /////////////////////////////////////////////////////////////
        List()
            : first(nullptr), last(nullptr), sz(0)
        { }

        /////////////////////////////////////////////////////////////
        /** @brief Constructs a List copying given one.
        **/
        /////////////////////////////////////////////////////////////
        List(const list_t& other)
            : first(nullptr), last(nullptr), sz(0)
        {
            if(other.sz)
            {
                const_iterator e = other.end();
                for(const_iterator it = other.begin(); it != e; it++)
                {
                    push_back(*it);
                }
            }
        }

        /////////////////////////////////////////////////////////////
        /** @brief Destructs the list.
        **/
        /////////////////////////////////////////////////////////////
        ~List()
        {
            clear();
        }

    private:

        /////////////////////////////////////////////////////////////
        /** @brief Creates a new node from an object.
         *
         *  The object is copied in the constructor of Node.
        **/
        /////////////////////////////////////////////////////////////
        Node* __create_node(const T& obj)
        {
            return AProNew(Node, obj);
        }

    public:

        /////////////////////////////////////////////////////////////
        /** @brief Push an object at the end of the List.
        **/
        /////////////////////////////////////////////////////////////
        void push_back(const T& obj)
        {
            Node* n = __create_node(obj);

            if(n)
            {
                if(!first)
                {
                    first = n;
                    last = n;
                    n->next = nullptr;
                }
                else
                {
                    Node* tmp = last;
                    last = n;
                    tmp->next = last;
                    n->next = nullptr;
                }

                sz++;
            }
            else
            {
                aprodebug("Can't create Node.");
            }
        }

        /////////////////////////////////////////////////////////////
        /** @brief Push an object at the end of the List.
        **/
        /////////////////////////////////////////////////////////////
        void append(const T& obj)
        {
            push_back(obj);
        }

        list_t& operator << (const T& obj)
        {
            push_back(obj);
            return *this;
        }

        /////////////////////////////////////////////////////////////
        /** @brief Push an object at the beginning of the list.
        **/
        /////////////////////////////////////////////////////////////
        void push_front(const T& obj)
        {
            Node* n = __create_node(obj);

            if(n)
            {
                if(!first)
                {
                    first = n;
                    last = n;
                    n->next = nullptr;
                }
                else
                {
                    Node* tmp = first;
                    first = n;
                    n->next = tmp;
                }

                sz++;
            }
            else
            {
                aprodebug("Can't create Node.");
            }
        }

        /////////////////////////////////////////////////////////////
        /** @brief Push an object at the beginning of the list.
        **/
        /////////////////////////////////////////////////////////////
        void prepend(const T& obj)
        {
            push_front(obj);
        }

        /////////////////////////////////////////////////////////////
        /** @brief Insert an object before the given iterator.
         *
         *  @note insert(obj, begin()) == push_front(obj) and
                  insert(obj, end())   == push_back(obj).
        **/
        /////////////////////////////////////////////////////////////
        void insert(const T& obj, iterator before)
        {
            if(before == end())
                push_back(obj);
            else if(before == begin())
                push_front(obj);
            else
            {
                Node* n = __create_node(obj);

                if(n)
                {
                    Node* bef = first;
                    while(bef->next != before && bef) bef = bef->next;

                    if(bef)
                        bef->next = n;
                    n->next = before;
                }
            }
        }

    public:

        /////////////////////////////////////////////////////////////
        /** @brief Erase the object at given position.
        **/
        /////////////////////////////////////////////////////////////
        void erase(iterator pos)
        {
            if(pos != end())
            {
                Node* toerr = pos.n;

                if(first != toerr)
                {
                    Node* aft = toerr->next;

                    Node* bef = first;
                    while(bef->next != toerr && bef) bef = bef->next;

                    if(bef)
                        bef->next = aft;

                    if(pos.n == last)
                        last = bef;
                }

                AProDelete(toerr);
                sz--;
            }
        }

        /////////////////////////////////////////////////////////////
        /** @brief Erase the objects in range [from, to).
         *
         *  Elements between from (included) and to (excluded) are
         *  destroyed. erase(begin(), end()) is equivalent to clear().
        **/
        /////////////////////////////////////////////////////////////
        void erase(iterator from, const_iterator to)
        {
            iterator cpy;
            while(from != to && from != end())
            {
                cpy = from;
                cpy++;
                erase(from);
                from = cpy;
            }
        }

        /////////////////////////////////////////////////////////////
        /** @brief Clear the list.
         *
         *  It also clean the properties of the List.
        **/
        /////////////////////////////////////////////////////////////
        void clear()
        {
            erase(begin(), end());

            sz = 0;
            first = nullptr;
            last = nullptr;
        }

    public:

        T& at(size_t index) { return *(begin() + index); }
        const T& at(size_t index) const { return *(begin() + index); }

        T& operator [] (size_t index) { return *(begin() + index); }
        const T& operator [] (size_t index) const { return *(begin() + index); }

    public:

        /////////////////////////////////////////////////////////////
        /** @brief Returns the size of the List.
        **/
        /////////////////////////////////////////////////////////////
        size_t size() const { return sz; }

        /////////////////////////////////////////////////////////////
        /** @brief Return true if List is empty.
        **/
        /////////////////////////////////////////////////////////////
        bool isEmpty() const { return sz == 0; }

        bool operator == (const list_t& other) const
        {
            if(size() != other.size()) return false;

            for(unsigned int i = 0; i < size(); ++i)
            {
                if(other[i] != (*this)[i])
                    return false;
            }

            return true;
        }

        /////////////////////////////////////////////////////////////
        /** @brief Return the index of the object if it is found in
         *  the List, -1 otherweise.
        **/
        /////////////////////////////////////////////////////////////
        int find(const T& obj) const
        {
            const_iterator e = end();
            size_t i = 0;
            for(const_iterator it = begin(); it != e; it++, i++)
                if((*it) == obj)
                    return i;

            return -1;
        }

    };
}



#endif
