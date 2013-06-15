/////////////////////////////////////////////////////////////
/** @file Node_base.h
 *  @ingroup Utils
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 10/05/2013
 *
 *  Defines the Node_base class.
 *
**/
/////////////////////////////////////////////////////////////
#ifndef APRO_NODE_BASE_H
#define APRO_NODE_BASE_H

#include "Platform.h"
#include "Array.h"
#include "SharedPointer.h"

namespace APro
{
    class Tree_base;

    /////////////////////////////////////////////////////////////
    /** @class Node_base
     *  @ingroup Utils
     *  @brief Base class for every node that enters in a Tree.
     *  @details This class can't be instantiate. You must use the
     *  templated class Node to create a Node.
     *  Or you can create your own Node implementation, to store
     *  specific data that you would like to manage differently.
     *  Every Node class that inherit this one can be stored
     *  in a specific Tree.
     *  @see Tree_base for more.
    **/
    /////////////////////////////////////////////////////////////
    class APRO_DLL Node_base
    {
        Tree_base*        m_parent_tree;///< Parent Tree.
        Node_base*        m_parent;///< Parent Node.
        Array<Node_base*> m_children;///< Children.

    public:
        /////////////////////////////////////////////////////////////
        /** @brief Constructor.
        **/
        /////////////////////////////////////////////////////////////
        Node_base();

        /////////////////////////////////////////////////////////////
        /** @brief Constructor.
         *
         *  @param parent : Parent of this node.
         *  @param parent_tree : Tree that constructed this node.
        **/
        /////////////////////////////////////////////////////////////
        Node_base(Node_base* parent, Tree_base* parent_tree = nullptr);

        /////////////////////////////////////////////////////////////
        /** @brief Destructor.
        **/
        /////////////////////////////////////////////////////////////
        virtual ~Node_base();

    public:

        /////////////////////////////////////////////////////////////
        /** @brief Reset the node.
         *  @details Use this instead of clear. Clear is internal.
        **/
        /////////////////////////////////////////////////////////////
        void reset();

        /////////////////////////////////////////////////////////////
        /** @brief Clear the node.
         *  @internal
         *  @note Use this function to clear specific content in the
         *  node.
        **/
        /////////////////////////////////////////////////////////////
        virtual void clear() = 0;

    public:

        /////////////////////////////////////////////////////////////
        /** @brief Return the tree that construct the node.
         *  @return Parent tree.
        **/
        /////////////////////////////////////////////////////////////
        Tree_base* getParentTree();

        /////////////////////////////////////////////////////////////
        /** @brief Return the tree that construct the node.
         *  @return Parent tree.
        **/
        /////////////////////////////////////////////////////////////
        const Tree_base* getParentTree() const;

        /////////////////////////////////////////////////////////////
        /** @brief Return the parent node.
         *  @return Parent node.
        **/
        /////////////////////////////////////////////////////////////
        Node_base* getParentNode();

        /////////////////////////////////////////////////////////////
        /** @brief Return the parent node.
         *  @return Parent node.
        **/
        /////////////////////////////////////////////////////////////
        const Node_base* getParentNode() const;

    public:

        /////////////////////////////////////////////////////////////
        /** @brief Add a child to the node.
         *
         *  @note The child must be construct by the same Tree that
         *  constructed this node. Use getParentTree if you don't
         *  have it.
         *  @note The child node is destructed only by thhe Tree, not
         *  by the Node !
         *
         *  @param node : Node to add.
        **/
        /////////////////////////////////////////////////////////////
        virtual void addChild(Node_base* node);

        /////////////////////////////////////////////////////////////
        /** @brief Remove a child.
         *
         *  @note Index can be given by indexForChild function.
         *
         *  @param index : Index of the child in the chidren list.
        **/
        /////////////////////////////////////////////////////////////
        virtual void removeChild(size_t index);

        /////////////////////////////////////////////////////////////
        /** @brief Return the index in the children list for a given node.
         *  @details If it doesn't existt in the list, return -1.
         *  @return The index.
        **/
        /////////////////////////////////////////////////////////////
        int indexForChild(Node_base* node);

        /////////////////////////////////////////////////////////////
        /** @return The children list size.
        **/
        /////////////////////////////////////////////////////////////
        size_t getNumChildren() const;

        /////////////////////////////////////////////////////////////
        /** @return Child at given index.
        **/
        /////////////////////////////////////////////////////////////
        Node_base* getChild(size_t index);

        /////////////////////////////////////////////////////////////
        /** @return Child at given index.
        **/
        /////////////////////////////////////////////////////////////
        const Node_base* getChild(size_t index) const;

    };
}

#endif // APRO_NODE_BASE_H
