/////////////////////////////////////////////////////////////
/** @file Map.h
 *  @ingroup Utils
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 19/11/2013 - 30/12/2014
 *
 *  @brief
 *  Defines the Map class.
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
#ifndef APROMAP_H
#define APROMAP_H

#include "Platform.h"
#include "Array.h"

namespace APro
{
    /////////////////////////////////////////////////////////////
    /** @class Map
     *  @ingroup Utils
     *  @brief Describe a Map implemented using the Ordered Binary
     *  Tree Concept.
     *
     *  This is an implementation of an Ordered Binary Tree. Elements are ordered
     *  using a function that you can give. You should always use
     *  an inline function for performance.
     *
     *  @note Comparaison function should follow the pattern :
     *  @code template <typename T> bool my_cmp (const T& a, const T& b); @endcode
     *  This function must return true if objects are correctly ordered,
     *  false otherwise. This order should be strict (< and NOT <=).
     *
     *  @note Comparaison is made by :
     *  - if(cmp(a, b)) left is a and b is right
     *  - if(cmp(b, a)) left is b and a is right
     *  - else a = b.
    **/
    /////////////////////////////////////////////////////////////
    template<class key_t, class value_t, class cmp_t = APro::is_less<key_t> >
    class Map
    {
    public:

        typedef Map<key_t, value_t, cmp_t> map_t;///< Typedef to tell current map.

        /////////////////////////////////////////////////////////////
        /** @brief Describe a Node in the Map.
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

            key_t*      m_key;
            value_t*    m_value;

            Node* m_left;
            Node* m_right;
            Node* m_parent;

            Node()
                : m_key(nullptr), m_value(nullptr),
                m_left(nullptr), m_right(nullptr), m_parent(nullptr)
            {

            }

            Node(const key_t& k, const value_t& v)
                : m_key(nullptr), m_value(nullptr),
                m_left(nullptr), m_right(nullptr), m_parent(nullptr)
            {
                m_key = (key_t*) AProAllocate(sizeof(key_t));
                AProConstructedCopy(m_key, k, key_t);

                m_value = (value_t*) AProAllocate(sizeof(value_t));
                AProConstructedCopy(m_value, v, value_t);
            }

            Node(const Node& other)
                : m_key(nullptr), m_value(nullptr),
                m_left(nullptr), m_right(nullptr), m_parent(nullptr)
            {
                m_key = (key_t*) AProAllocate(sizeof(key_t));
                AProConstructedCopy(m_key, other.k, key_t);

                m_value = (value_t*) AProAllocate(sizeof(value_t));
                AProConstructedCopy(m_value, other.v, value_t);
            }

            ~Node()
            {
                AProDestructObject(m_key);
                AProDeallocate(m_key);

                AProDestructObject(m_value);
                AProDeallocate(m_value);
            }

        public:

            /////////////////////////////////////////////////////////////
            /** @brief Return the grandparent of the node, or null if it
             *  doesn't have one.
             *
             *  The grandparent is the parent's parent of this node.
            **/
            /////////////////////////////////////////////////////////////
            Node* grandparent()
            {
                if(m_parent)
                    if(m_parent->m_parent)
                        return m_parent->m_parent;
                return nullptr;
            }

            /////////////////////////////////////////////////////////////
            /** @brief Return the grandparent of the node, or null if it
             *  doesn't have one.
             *
             *  The grandparent is the parent's parent of this node.
            **/
            /////////////////////////////////////////////////////////////
            const Node* grandparent() const
            {
                if(m_parent)
                    if(m_parent->m_parent)
                        return m_parent->m_parent;
                return nullptr;
            }

            /////////////////////////////////////////////////////////////
            /** @brief Return the other child of the parent, if exists.
             *
             *  @note The sibling my be nullptr if parent has only one
             *  child or if node is rootnode.
            **/
            /////////////////////////////////////////////////////////////
            Node* sibling()
            {
                if(m_parent)
                {
                    if(m_parent->m_left == this)
                        return m_parent->m_right;
                    if(m_parent->m_right == this)
                        return m_parent->m_left;
                }
                return nullptr;
            }


            /////////////////////////////////////////////////////////////
            /** @brief Return the other child of the parent, if exists.
             *
             *  @note The sibling my be nullptr if parent has only one
             *  child or if node is rootnode.
            **/
            /////////////////////////////////////////////////////////////
            const Node* sibling() const
            {
                if(m_parent)
                {
                    if(m_parent->m_left == this)
                        return m_parent->m_right;
                    if(m_parent->m_right == this)
                        return m_parent->m_left;
                }
                return nullptr;
            }

            /////////////////////////////////////////////////////////////
            /** @brief Return the sibling of this node's parent.
             *
             *  @note The uncle may be nullptr, if the grandparent has only
             *  one child.
            **/
            /////////////////////////////////////////////////////////////
            Node* uncle()
            {
                if(m_parent)
                    return m_parent->sibling();
                return nullptr;
            }

            /////////////////////////////////////////////////////////////
            /** @brief Return the sibling of this node's parent.
             *
             *  @note The uncle may be nullptr, if the grandparent has only
             *  one child.
            **/
            /////////////////////////////////////////////////////////////
            const Node* uncle() const
            {
                if(m_parent)
                    return m_parent->sibling();
                return nullptr;
            }

        };

    protected:

        Node*  m_root;  ///< Root node.
        Node   nullnode;///< The nulnode, represents the End of the Tree.
        size_t m_sz;    ///< Size of the map.

    protected:

        class node_iterator_preorder
        {
        public:
            map_t* parent;
            Node*  node;

        public:
            node_iterator_preorder() : parent(nullptr), node(nullptr) {}
            node_iterator_preorder(const Node* n, const map_t* p) { parent = const_cast<map_t*>(p); node = const_cast<Node*>(n); }
            node_iterator_preorder(const node_iterator_preorder& it) { parent = it.parent; node = it.node; }
            ~node_iterator_preorder() {}

            node_iterator_preorder& next()
            {
                if(parent && node)
                {
                    Node* p;

                    if(*this == parent->end())
                    { // Increment from end, return begin.
                        node = parent->begin().node;
                    }
                    else
                    {
                        if(node->m_right)
                        {
                            node = node->m_right;
                            while(node->m_left)
                                node = node->m_left;
                        }
                        else
                        {
                            p = node->m_parent;
                            while(p && node == p->m_right)
                            {
                                node = p;
                                p = p->m_parent;
                            }

                            node = p;
                            if(!node) node = parent->end().node;
                        }
                    }
                }

                return *this;
            }

            const node_iterator_preorder& next() const { return const_cast<node_iterator_preorder*>(this)->next(); }

            node_iterator_preorder& operator ++ (int) { return this->next(); }
            const node_iterator_preorder& operator ++ (int) const { return this->next(); }

            value_t& value() { return *(node->m_value); }
            const value_t& value() const { return *(node->m_value); }

            key_t& key() { return *(node->m_key); }
            const key_t& key() const { return *(node->m_key); }

            bool operator == (const node_iterator_preorder& other) const { return node == other.node && parent == other.parent; }
            bool operator != (const node_iterator_preorder& other) const { return !(*this == other); }
        };

    public:

        typedef       node_iterator_preorder iterator;
        typedef const node_iterator_preorder const_iterator;

//      TODO
//      typedef       node_iterator_postorder iterator_postorder;
//      typedef const node_iterator_postorder const_iterator_postorder;

    public:

        Node* _smallest_node() { if(m_root) { Node* ret = m_root; while(ret->m_left) ret = ret->m_left; return ret; } else return &nullnode; }
        const Node* _smallest_node() const { if(m_root) { Node* ret = m_root; while(ret->m_left) ret = ret->m_left; return ret; } else return &nullnode; }

        Node* _biggest_node() { if(m_root) { Node* ret = m_root; while(ret->m_right) ret = ret->m_right; return ret; } else return &nullnode; }
        const Node* _biggest_node() const { if(m_root) { Node* ret = m_root; while(ret->m_right) ret = ret->m_right; return ret; } else return &nullnode; }

    public:

        iterator       begin()       { return iterator(_smallest_node(), this); }
        const_iterator begin() const { return const_iterator(_smallest_node(), this); }
        const_iterator end()   const { return const_iterator(&nullnode, this); }

    public:

        /////////////////////////////////////////////////////////////
        /** @brief Constructs an empty map.
        **/
        /////////////////////////////////////////////////////////////
        Map()
            : m_root(nullptr), m_sz(0)
        {

        }

        /////////////////////////////////////////////////////////////
        /** @brief Constructs a copy of a given map.
        **/
        /////////////////////////////////////////////////////////////
        Map(const map_t& other)
            : m_root(nullptr), m_sz(0)
        {
            const_iterator e = other.end();
            for(const_iterator it = other.begin(); it != e; it++)
            {
                push(it.key(), it.value());
            }
        }

        /////////////////////////////////////////////////////////////
        /** @brief Destructs the map.
        **/
        /////////////////////////////////////////////////////////////
        ~Map()
        {
            clear();
        }

    protected:

        /////////////////////////////////////////////////////////////
        /** @brief Creates a new node.
        **/
        /////////////////////////////////////////////////////////////
        Node* new_node(const key_t& k, const value_t& v, Node* left, Node* right)
        {
            Node* n = AProNew(Node, k, v);

            n->m_right = right;
            n->m_left = left;
            n->m_parent = nullptr;

            if(left) n->m_left->m_parent = n;
            if(right) n->m_right->m_parent = n;

            return n;
        }

    protected:

        /////////////////////////////////////////////////////////////
        /** @brief Look for a node with given key.
         *  @return Nullptr if not found.
        **/
        /////////////////////////////////////////////////////////////
        Node* lookup_node(const key_t& k)
        {
            cmp_t cmp;
            Node* n = m_root;
            while(n != nullptr)
            {
                if(cmp(k, *(n->m_key)))
                   n = n->m_left;
                else if (cmp(*(n->m_key), k))
                    n = n->m_right;
                else
                    return n;
            }

            return n;
        }

        /////////////////////////////////////////////////////////////
        /** @brief Look for a node with given key.
         *  @return Nullptr if not found.
        **/
        /////////////////////////////////////////////////////////////
        const Node* lookup_node(const key_t& k) const
        {
            return (const_cast<map_t*>(this))->lookup_node(k);
        }

    public:

        /////////////////////////////////////////////////////////////
        /** @brief Return the Value at given Key.
         *
         *  @note If no Node is found at given Key, a new Node is created
         *  and his value is returned.
        **/
        /////////////////////////////////////////////////////////////
        value_t& at(const key_t& k)
        {
            Node* n = lookup_node(k);
            if(!n)
            {
                n = push_ret_node(k, value_t());
                return *(n->m_value);
            }

            return *(n->m_value);
        }

        /////////////////////////////////////////////////////////////
        /** @brief Return the Value at given Key.
        **/
        /////////////////////////////////////////////////////////////
        const value_t& at(const key_t& k) const
        {
            const Node* n = lookup_node(k);
            aproassert(n, "Bad key given !");

            return *(n->m_value);
        }

        value_t& operator [] (const key_t& k)
        {
            return at(k);
        }

        const value_t& operator [] (const key_t& k) const
        {
            return at(k);
        }

    protected:

        /////////////////////////////////////////////////////////////
        /** @brief Performs a left subtree rotation.
        **/
        /////////////////////////////////////////////////////////////
        void rotate_left(Node* n)
        {
            if(!n) return;

            Node* r = n->m_right;
            replace_node(n, r);
            n->m_right = r->m_left;
            if(r->m_left)
                r->m_left->m_parent = n;
            r->m_left = n;
            n->m_parent = r;
        }

        /////////////////////////////////////////////////////////////
        /** @brief Performs a right subtree rotation.
        **/
        /////////////////////////////////////////////////////////////
        void rotate_right(Node* n)
        {
            if(!n) return;

            Node* L = n->m_left;
            replace_node(n, L);
            n->m_left = L->m_right;
            if(L->m_right)
                L->m_right->m_parent = n;
            L->m_right = n;
            n->m_parent = L;
        }

        /////////////////////////////////////////////////////////////
        /** @brief Replaces one node by another one.
        **/
        /////////////////////////////////////////////////////////////
        void replace_node(Node* oldn, Node* newn)
        {
            if(oldn->m_parent == nullptr)
                m_root = newn;
            else
                if(oldn->m_parent->m_left == oldn)
                    oldn->m_parent->m_left = newn;
                else
                    oldn->m_parent->m_right = newn;

            if(newn)
                newn->m_parent = oldn->m_parent;
        }

    protected:

        /////////////////////////////////////////////////////////////
        /** @brief Insert a node with given key and value.
        **/
        /////////////////////////////////////////////////////////////
        Node* insert_ret_node(const key_t& k, const value_t& v)
        {
            cmp_t cmp;
            Node* newn = new_node(k, v, nullptr, nullptr);
            if(newn)
            {
                if(m_root == nullptr)
                    m_root == newn;

                else
                {
                    Node* n = m_root;
                    while(1)
                    {
                        if(cmp(k, *(m_root->m_key)))
                        {
                            if(n->m_left == nullptr)
                            {
                                n->m_left = newn;
                                break;
                            }
                            else
                            {
                                n = n->m_left;
                            }
                        }
                        else if(cmp(*(m_root->m_key), k))
                        {
                            if(n->m_right == nullptr)
                            {
                                n->m_right = newn;
                                break;
                            }
                            else
                            {
                                n = n->m_right;
                            }
                        }
                        else
                        {
                            *(n->m_value) = v;
                            AProDelete(newn);// We don't care about it now.
                            return n;
                        }
                    }
                    newn->m_parent = n;
                    m_sz++;
                }
            }

            return newn;
        }

        Node* push_ret_node(const key_t& k, const value_t& v)
        {
            return insert_ret_node(k, v);
        }

    public:

        /////////////////////////////////////////////////////////////
        /** @brief Push a pair [key, value] in the map.
        **/
        /////////////////////////////////////////////////////////////
        void push(const key_t& k, const value_t& v)
        {
            insert_ret_node(k, v);
        }

    public:

        /////////////////////////////////////////////////////////////
        /** @brief Destroy the node given by iterator.
        **/
        /////////////////////////////////////////////////////////////
        void erase(iterator& it) { erase_node(it.node); }

        /////////////////////////////////////////////////////////////
        /** @brief Destroy the node given by key.
        **/
        /////////////////////////////////////////////////////////////
        void erase(const key_t& k)
        {
            erase_node(lookup_node(k));
        }

    protected:

        void erase_node(Node* n)
        {
            if(!n) return;
            if(n == &nullnode) return;

            Node* p = n->m_parent;
            Node* l = n->m_left;
            Node* r = n->m_right;

            if(l && r)
            {
                // Right subtree should be moved to the rightest node of left one, because it is superior to every
                // leftnodes.

                Node* rightest_l = l;
                while(rightest_l->m_right)
                    rightest_l = rightest_l->m_right;

                rightest_l->m_right = r;
                r->m_parent = rightest_l;

                // Left child parent must be the parent's parent.
                l->m_parent = l->grandparent();

                // grandparent child is left.
                if(l->m_parent)
                {
                    if(l->m_parent->m_left == n)
                        l->m_parent->m_left = l;
                    else
                        l->m_parent->m_right = l;
                }
            }
            else if (l)
            {
                // We have left but no right child.
                // l parent must be grandparent.
                l->m_parent = l->grandparent();

                // grandparent child is left.
                if(l->m_parent)
                {
                    if(l->m_parent->m_left == n)
                        l->m_parent->m_left = l;
                    else
                        l->m_parent->m_right = l;
                }
            }
            else if (r)
            {
                // We have right but no left child.
                // right parent must be grandparent.
                r->m_parent = r->grandparent();

                // grandparent child is right.
                if(r->m_parent)
                {
                    if(r->m_parent->m_left == n)
                        r->m_parent->m_left = r;
                    else
                        r->m_parent->m_right = r;
                }
            }

            // delete the node.
            AProDelete(n);
            m_sz--;
        }

    public:

        /////////////////////////////////////////////////////////////
        /** @brief Clear the map by destroying every nodes.
        **/
        /////////////////////////////////////////////////////////////
        void clear()
        {
            recursive_destroy(m_root);
            m_sz = 0;
            m_root = nullptr;
        }

    protected:

        void recursive_destroy(Node* n)
        {
            if(n)
            {
                recursive_destroy(n->m_left);
                recursive_destroy(n->m_right);
            }

            AProDelete(n);
        }

    public:

        /////////////////////////////////////////////////////////////
        /** @brief Return the size of this map (number of nodes).
        **/
        /////////////////////////////////////////////////////////////
        size_t size() const { return m_sz; }

        /////////////////////////////////////////////////////////////
        /** @brief Tell if a node exists.
        **/
        /////////////////////////////////////////////////////////////
        bool keyExists(const key_t& k) const
        {
            return lookup_node(k) != nullptr;
        }
        
        /////////////////////////////////////////////////////////////
        /** @brief Returns an Array with a copy of each keys used in 
         *  this Map.
         *
         *  @note
         *  This operation may be costly as it iterates through every 
         *  Nodes in the Map.
        **/
        /////////////////////////////////////////////////////////////
        Array<key_t> getKeysArray() const
        {
        	Array<key_t> ret;
        	for(const_iterator it = begin(); it != end(); it++)
				ret.append(it.key());
			return ret;
        }

    };
}

#endif
