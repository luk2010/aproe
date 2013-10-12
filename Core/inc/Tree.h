////////////////////////////////////////////////////////////
/** @file Tree.h
 *  @ingroup Utils
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 06/05/2013
 *
 *  Defines a Tree generic interface.
 *
**/
////////////////////////////////////////////////////////////
#ifndef APRO_TREE_H
#define APRO_TREE_H

#include "Platform.h"
#include "SharedPointer.h"
#include "Tree_base.h"

namespace APro
{
    /////////////////////////////////////////////////////////////
    /** @class Tree
     *  @ingroup Utils
     *  @brief A Templated tree class that can store any given
     *  Node.
     *  @details This class should be used as a node store. You must
     *  use it to create node, and to destroy it.
    **/
    /////////////////////////////////////////////////////////////
    template <typename NodeType>
    class Tree : public Tree_base
    {
    public:

        typedef NodeType Node;

        template <typename TypeData>
        virtual Node_base* createNode_internal(const TypeData& data, Node_base* parent)
        {
            return AProNew(NodeType, data, parent, this);
        }

        virtual Node_base* createRootNode()
        {
            return static_cast<Node_base*>(AProNew(NodeType));
        }

    protected:

        virtual void deallocate_node_internal(Node_base* node)
        {
            AProDelete(reinterpret_cast<NodeType*>(node));
        }

    public:

        NodeType* getTypedRootNode()
        {
            if(!m_root_node)
                m_root_node = createRootNode();

            return m_root_node;
        }

        const NodeType* getTypedRootNode() const
        {
            return m_root_node;
        }
    };

    /* Utilisation
    typedef Tree<Node<int> > TreeInt;
    TreeInt mon_arbre;
    TreeInt::Node* rootNode = mon_arbre.getRootNode();
    rootNode->addChild(mon_arbre.createNode<int>(12));
    */

}

#endif // APRO_TREE_H
