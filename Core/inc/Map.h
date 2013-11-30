/////////////////////////////////////////////////////////////
/** @file Map.h
 *  @ingroup Utils
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 19/11/2013
 *
 *  Defines the Map class.
 *
**/
/////////////////////////////////////////////////////////////
#ifndef APROMAP_H
#define APROMAP_H

#include "Platform.h"
#include "List.h"
#include "Console.h"

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
    template<typename key_t, typename value_t, typename cmp_t = APro::is_less<key_t> >
    class Map
    {
    public:

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

            Node* m_left,
                  m_right,
                  m_parent;

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
                : data(nullptr), next(nullptr)
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
            node_iterator_preorder(const Node* n, const map_t* p) { parent = p; node = n; }
            node_iterator_preorder(const node_iterator_preorder& it) { parent = it.parent; node = it.n; }
            ~node_iterator_preorder() {}

            node_iterator_preorder& next()
            {
                if(parent && node)
                {
                    Node* p;

                    if(*this == end())
                    { // Increment from end, return begin.
                        node = begin().node;
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
                            while(p && node = p->m_right)
                            {
                                node = p;
                                p = p->m_parent;
                            }

                            node = p;
                            if(!node) node = end();
                        }
                    }
                }

                return *this;
            }

            const node_iterator_preorder& next() const { return const_cast<node_iterator_preorder*>(*this)->next(); }

            node_iterator_preorder& operator ++ () { return *this->next(); }
            const node_iterator_preorder& operator ++ () const { return *this->next(); }

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

        Node* _smallest_node() { m_root ? { Node* ret = m_root; while(ret->m_left) ret = ret->m_left; return ret; } : return nullnode; }
        const Node* _smallest_node() const { m_root ? { Node* ret = m_root; while(ret->m_left) ret = ret->m_left; return ret; } : return nullnode; }

        Node* _biggest_node() { m_root ? { Node* ret = m_root; while(ret->m_right) ret = ret->m_right; return ret; } : return nullnode; }
        const Node* _biggest_node() const { m_root ? { Node* ret = m_root; while(ret->m_right) ret = ret->m_right; return ret; } : return nullnode; }

    public:

        iterator       begin()       { return iterator(_smallest_node()); }
        const_iterator begin() const { return const_iterator(_smallest_node()); }
        const_iterator end()   const { return const_iterator(&nullnode); }

    public:

        typedef Map<key_t, value_t, cmp_t> map_t;///< Typedef to tell current map.

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
            Node* n = m_root;
            while(n != nullptr)
            {
                if(cmp_t(k, *(n->m_key))
                   n = n->m_left;
                else if (cmp_t(*(n->m_key), k))
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
            Node* n = lookup_node(k);
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
                        if(cmp_t(k, *(m_root->m_key)))
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
                        else if(cmp_t(*(m_root->m_key), k))
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
                            n->m_value = v;
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
            sz--;
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

    };
}

#endif
