/** @file List.h
 *  @ingroup Memory
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 16/07/2012
 *
 *  Defines the List container.
 *
**/
#ifndef APROLIST_H
#define APROLIST_H

#include "Platform.h"
#include "Allocator.h"
#include "Array.h"
#include <typeinfo>

namespace APro
{
    template<typename T>
    class List
    {
    private:

        class Node
        {
        public:
            Node()
            : next(nullptr), previous(nullptr), element(nullptr)
            {

            }

            Node(const T& other)
            {
                element = AProNew(1, T) (other);
                next = previous = nullptr;
            }

            Node(const Node& other)
            {
                element = AProNew(1, T) (other.element);
                next = previous = nullptr;
            }

            ~Node()
            {
                if(element != nullptr)
                    AProDelete(element);
            }

            Node* next;
            Node* previous;
            T*    element;
        };

        class BeginNode : public Node
        {
        public:
            BeginNode()
            {
                Node::element = nullptr;
                Node::next = Node::previous = nullptr;
            }

            ~BeginNode()
            {
                /* Do nothing */
            }
        };

        class EndNode : public Node
        {
        public:
            EndNode()
            {
                Node::element = nullptr;
                Node::next = Node::previous = nullptr;
            }

            ~EndNode()
            {
                /* Do nothing */
            }
        };

    public:

        class ConstIterator;

        class Iterator
        {
        public:

            friend class List<T>;

            Iterator(Node* node_)
            {
                node = node_;
            }

            Iterator(const Iterator& it)
            {
                node = it.node;
            }

            ~Iterator()
            {
                /* Do nothing */
            }

            T& get()
            {
                if(node != nullptr)
                    return *(node->element);

#if APRO_EXCEPTION == APRO_ON

                APRO_THROW("BadIterator", "Iterator have bad node !", "Iterator");

#endif
            }

            bool next()
            {
                if(node == nullptr)
                    return false;

                if(node->next == nullptr)
                    return false;

                node = node->next;
                return true;
            }

            bool previous()
            {
                if(node == nullptr)
                    return false;

                if(node->previous == nullptr)
                    return false;

                node = node->previous;
                return true;
            }

            bool isEnd() const
            {
                if(node == nullptr || node->next == nullptr)
                    return true;
                return false;
            }
            bool isFirst() const
            {
                if(node == nullptr || node->previous == nullptr)
                    return true;
                return false;
            }

            bool operator ++ (int)
            {
                return next();
            }
            bool operator -- (int)
            {
                return previous();
            }

            bool operator == (Iterator i) const
            {
                return i.node == node;
            }

            bool operator != (Iterator i) const
            {
                return !(*this == i);
            }

            bool operator == (ConstIterator i) const
            {
                return i.node == node;
            }

            bool operator != (ConstIterator i) const
            {
                return !(*this == i);
            }

            Iterator& operator + (int i)
            {
                if(i < 0)
                {
                    while(i != 0)
                    {
                        i++;
                        previous();
                    }
                }
                else if(i > 0)
                {
                    while(i != 0)
                    {
                        i--;
                        next();
                    }
                }

                return *this;
            }

            Iterator& operator - (int i)
            {
                if(i < 0)
                {
                    while(i != 0)
                    {
                        i++;
                        next();
                    }
                }
                else if(i > 0)
                {
                    while(i != 0)
                    {
                        i--;
                        previous();
                    }
                }

                return *this;
            }

        private:
            Node* node;
        };

        class ConstIterator
        {
        public:

            friend class List<T>;

            ConstIterator(const Node* node_)
            {
                node = const_cast<Node*>(node_);
            }

            ConstIterator(const ConstIterator& it)
            {
                node = it.node;
            }

            ConstIterator(const Iterator& it)
            {
                node = it.node;
            }

            ~ConstIterator()
            {
                /* Do nothing */
            }

            const T& get() const
            {
                if(node != nullptr)
                    return *(node->element);

#if APRO_EXCEPTION == APRO_ON

                APRO_THROW("BadConstIterator", "Iterator have bad node !", "ConstIterator");

#endif
            }

            bool next()
            {
                if(node == nullptr)
                    return false;

                if(node->next == nullptr)
                    return false;

                node = node->next;
                return true;
            }

            bool previous()
            {
                if(node == nullptr)
                    return false;

                if(node->previous == nullptr)
                    return false;

                node = node->previous;
                return true;
            }

            bool isEnd() const
            {
                if(node == nullptr || node->next == nullptr)
                    return true;
                return false;
            }
            bool isFirst() const
            {
                if(node == nullptr || node->previous == nullptr)
                    return true;
                return false;
            }

            bool operator ++ (int)
            {
                return next();
            }
            bool operator -- (int)
            {
                return previous();
            }

            bool operator == (Iterator i) const
            {
                return i.node == node;
            }

            bool operator == (ConstIterator i) const
            {
                return i.node == node;
            }

            bool operator != (ConstIterator i) const
            {
                return !(*this == i);
            }

            bool operator != (Iterator i) const
            {
                return !(*this == i);
            }

            ConstIterator& operator + (int i)
            {
                if(i < 0)
                {
                    while(i != 0)
                    {
                        i++;
                        previous();
                    }
                }
                else if(i > 0)
                {
                    while(i != 0)
                    {
                        i--;
                        next();
                    }
                }

                return *this;
            }

            ConstIterator& operator - (int i)
            {
                if(i < 0)
                {
                    while(i != 0)
                    {
                        i++;
                        next();
                    }
                }
                else if(i > 0)
                {
                    while(i != 0)
                    {
                        i--;
                        previous();
                    }
                }

                return *this;
            }

        private:
            Node* node;
        };

    private:

          BeginNode     firstNode;
          EndNode       lastNode;
          size_t msize;

    public:

        List()
            : msize(0)
        {
            lastNode.previous = &firstNode;
            firstNode.next = &lastNode;
        }
        List(const List<T>& l)
            : msize(0)
        {
            lastNode.previous = &firstNode;
            firstNode.next = &lastNode;
            append(l);
        }

        List<T>& operator = (const List<T>& other)
        {
            clear();
            lastNode.previous = &firstNode;
            firstNode.next = &lastNode;
            append(l);
        }

        ~List()
        {
            clear();
        }

        void append(const T& obj)
        {
            Node* rlastNode = lastNode.previous;

            if(rlastNode == nullptr)
            {
                repairLastNode();

                rlastNode = lastNode.previous;
                if(rlastNode == nullptr)
                {
#if APRO_EXCEPTION == APRO_ON

                    APRO_THROW("BadInitializationList", "List has been bad initialized and couldn't be fixed !", "List");

#endif

                    return;
                }
            }

            Node* newNode = AProNew(1, Node) (obj);
            newNode->previous = rlastNode;
            newNode->next = &lastNode;

            lastNode.previous = newNode;
            rlastNode->next = newNode;

            msize ++;
        }

        void append(const List<T>& obj)
        {
            for(List<T>::ConstIterator it(obj.begin()); !it.isEnd(); it++)
            {
                append(it.get());
            }
        }

        void push_back(const T& obj)
        {
            append(obj);
        }

        void push_back(const List<T>& obj)
        {
            append(obj);
        }

        void prepend(const T& obj)
        {
            Node* rfirstNode = firstNode.next;

            if(rfirstNode == nullptr)
            {
                repairFirstNode();

                rfirstNode = firstNode.next;
                if(rfirstNode == nullptr)
                {
#if APRO_EXCEPTION == APRO_ON

                    APRO_THROW("BadInitializationList", "List has been bad initialized and couldn't be fixed !", "List");

#endif

                    return;
                }
            }

            Node* newNode = AProNew(1, Node) (obj);
            newNode->previous = &firstNode;
            newNode->next = rfirstNode;

            firstNode.next = newNode;
            rfirstNode.previous = newNode;

            msize ++;
        }

        void prepend(const List<T>& obj)
        {
            for(List<T>::ConstIterator it(obj.end()); !it.isFirst(); it--)
            {
                prepend(it.get());
            }
        }

        void push_front(const T& obj)
        {
            prepend(obj);
        }

        void push_front(const List<T>& obj)
        {
            prepend(obj);
        }

        void insert(size_t before, const T& obj, size_t copy = 1)
        {
            if(before >= msize) return;
            if(copy == 0) return;

            Iterator i = it(before);
            if(i == begin() || i == (begin() ++))
            {
                while(copy > 0)
                {
                    prepend(obj);
                    copy--;
                }

                return;
            }

            if(i == end())
            {
                while(copy > 0)
                {
                    append(obj);
                    copy--;
                }

                return;
            }

            Node* nextNode = (begin() + before).node;
            Node* previousNode = nextNode->previous;

            Node* newNode = AProNew(1, Node) (obj);
            newNode->previous = previousNode;
            newNode->next = nextNode;

            previousNode->next = newNode;
            nextNode->previous = newNode;

            msize ++;

            if(copy > 1)
            {
                insert(before, obj, copy - 1);
            }
        }

        void insert(size_t before, const List<T>& obj, size_t copy = 1)
        {
            if(before >= msize) return;
            if(copy == 0) return;

            for(List<T>::ConstIterator i(obj.end()); !(i.isFirst()); i--)
            {
                insert(before, i.get(), 1);
            }

            if(copy > 1)
                insert(before, obj, copy - 1);
        }

        void erase(size_t first, int last = -1)
        {
            if(last == -1) last = first;

            if((int) first > last)
            {
                size_t tmp = first;
                first = last;
                last = tmp;
            }

            if(first >= msize) return;
            if(last >= (int) msize) last = (int) msize - 1;

            Node* nodeToErase = (begin() + first).node;

            Node* previousNode = nodeToErase->previous;
            Node* nextNode = nodeToErase->next;

            nextNode->previous = previousNode;
            previousNode->next = nextNode;

            AProDelete(nodeToErase);
            msize--;

            if(last - first >= 1)
            {
                erase(first, last - 1);
            }
        }

        void erase(Iterator& it)
        {
            ConstIterator endd = end();
            if(it == endd)
                return;

            Node* nodeToErase = it.node;
            it++;

            Node* previousNode = nodeToErase->previous;
            Node* nextNode = nodeToErase->next;

            nextNode->previous = previousNode;
            previousNode->next = nextNode;

            AProDelete(nodeToErase);
            msize--;
        }

        void clear()
        {
            erase(0, msize);
        }

        T& at(size_t index)
        {
            return (begin() + index).get();
        }

        const T& at(size_t index) const
        {
            return (begin() + index).get();
        }

        T& operator [] (size_t index)
        {
            return at(index);
        }

        const T& operator [] (size_t index) const
        {
            return at(index);
        }

        Iterator begin()
        {
            Iterator i (&firstNode); i++;
            return i;
        }
        ConstIterator begin() const
        {
            ConstIterator i (&firstNode); i++;
            return i;
        }

        Iterator end()
        {
            return Iterator(&lastNode);
        }

        ConstIterator end() const
        {
            return ConstIterator(&lastNode);
        }

        Iterator it(size_t index)
        {
            return begin() + index;
        }

        ConstIterator cstit(size_t index) const
        {
            return begin() + index;
        }

        size_t size() const
        {
            return msize;
        }

        size_t allocatedSize() const
        {
            return (sizeof(Node) + sizeof(T)) * (msize + 2) - sizeof(T) * 2;
        }

        bool isEmpty() const
        {
            return size() == 0;
        }

        void repair()
        {
            findHole();
            fixSize();
        }

        List<T> & operator << (const T& obj)
        {
            append(obj);
            return *this;
        }

        List<T> & operator << (const List<T>& list)
        {
            append(list);
            return *this;
        }

        int find(const T& obj) const
        {
            for(size_t i = 0; i < size(); i++)
            {
                if(at(i) == obj)
                {
                    return (int) i;
                }
            }

            return -1;
        }

        T& last()
        {
            Iterator it(end()); it--;
            return it.get();
        }

        const T& last() const
        {
            ConstIterator it(end()); it--;
            return it.get();
        }

        T& first()
        {
            return begin().get();
        }

        const T& first() const
        {
            return begin().get();
        }

    private:

        void repairLastNode()
        {
            Iterator i(&firstNode);
            while(i++) {};

            if(i.node != &lastNode && (i.node->next == nullptr || lastNode.previous == nullptr))
            {
                i.node->next = &lastNode;
                lastNode.previous = i.node;
            }

            fixSize();
        }

        void repairFirstNode()
        {
            Iterator i(&lastNode);
            while(i--) {};

            if(i.node != &firstNode && (i.node->previous == nullptr || firstNode.next == nullptr))
            {
                i.node->previous = &firstNode;
                firstNode.next = i.node;
            }

            fixSize();
        }

        void fixSize()
        {
            Iterator i(&firstNode);
            size_t sz = 0;

            while(i++) sz++;

            msize = sz;
        }

        void findHole()
        {
            if(firstNode.next == nullptr && lastNode.previous == nullptr)
            {
                firstNode.next = &lastNode;
                lastNode.previous = &firstNode;

#if APRO_EXCEPTION == ARO_ON

                APRO_THROW("CorruptedList", "List is definitivly corrupted ! Repairing will lost all data in memory...", "List");

#endif
            }

            if(firstNode.next == nullptr)
                repairFirstNode();
            if(lastNode.previous == nullptr)
                repairLastNode();

            Node* tmpNode = nullptr;
            for(Iterator i2 (lastNode.previous); i2.node != &firstNode; i2--)
            {
                if(i2.node->next == nullptr)
                {
                    i2.node->next = tmpNode;
                }

                tmpNode = i2.node;
            }

            tmpNode = nullptr;
            for(Iterator i2 (firstNode.next); i2.node != &lastNode; i2++)
            {
                if(i2.node->previous == nullptr)
                {
                    i2.node->previous = tmpNode;
                }

                tmpNode = i2.node;
            }
        }
    };
}

#endif
