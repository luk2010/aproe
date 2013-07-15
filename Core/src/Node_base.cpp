/////////////////////////////////////////////////////////////
/** @file Node_base.cpp
 *  @ingroup Utils
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 10/05/2013
 *
 *  Implements the Node_base class.
 *
**/
/////////////////////////////////////////////////////////////
#include "Node_base.h"
#include "Tree.h"

namespace APro
{
    Node_base::Node_base()
        : m_parent_tree(nullptr), m_parent(nullptr)
    {

    }

    Node_base::Node_base(Node_base* parent = nullptr, Tree_base* parent_tree = nullptr)
        : m_parent_tree(parent_tree), m_parent(parent)
    {

    }

    Node_base:: ~Node_base()
    {

    }

    void Node_base::reset()
    {
        clear();

        for(unsigned int i = 0; i < m_children.size(); ++i)
            m_parent_tree->destroyNode(m_children.at(i));

        m_children.clear();
        m_parent = nullptr;
        m_parent_tree = nullptr;
    }

    Tree* Node_base::getParentTree()
    {
        return m_parent_tree;
    }

    const Tree* Node_base::getParentTree() const
    {
        return m_parent_tree;
    }

    Node_base* Node_base::getParentNode()
    {
        return m_parent;
    }

    const Node_base* Node_base::getParentNode() const
    {
        return m_parent;
    }

    void Node_base::addChild(Node_base* node)
    {
        if(m_children.find(node) == -1 && m_parent_tree &&
           m_parent_tree->getMaxChildLevel() > m_children.size())
        {
            m_children.append(node);
            if(node->m_parent != this)
                node->m_parent = this;
        }
    }

    void Node_base::removeChild(size_t index)
    {
        m_children.erase(index);
    }

    int Node_base::indexForChild(Node_base* node)
    {
        return m_children.find(node);
    }

    size_t Node_base::getNumChildren() const
    {
        return m_children.size();
    }

    Node_base* Node_base::getChild(size_t index)
    {
        return m_children.at(index);
    }

    const Node_base* Node_base::getChild(size_t index) const;
    {
        return m_children.at(index);
    }
}
