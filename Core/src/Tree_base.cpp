////////////////////////////////////////////////////////////
/** @file Tree_base.cpp
 *  @ingroup Utils
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 11/05/2013
 *
 *  Implements a Tree_base generic interface.
 *
**/
////////////////////////////////////////////////////////////
#include "Tree_base.h"

namespace APro
{
    Tree_base::Tree_base(int max_child_level, int max_depth_level)
    {
        /* m_root_node = createRootNode(); Can't do this as the create node function hasn't been done yet. */
        m_max_child_level = max_child_level;
        m_max_depth_level = max_depth_level;
    }

    Tree_base::Tree_base(const Tree_base& other)
    {
        m_max_child_level = other.getMaxChildLevel();
        m_max_depth_level = other.getMaxDepthLevel();
    }

    Tree_base::~Tree_base()
    {
        clear();
    }

    Node_base* Tree_base::copyNode(const Node_base* other, Node_base* new_parent, bool recursive)
    {
        if(other)
        {
            Node_base* new_node = createNode(other->getData(), new_parent);
            if(new_node && recursive)
            {
                for(unsigned int i = 0; i < other->getNumChildren(); ++i)
                {
                    Node_base* copy_child = copyNode(other->getChild(i), new_node, recursive);
                    if(copy_child)
                        new_node->addChild(copy_child);
                }
            }

            return new_node;
        }

        return nullptr;
    }

    Node_t* Tree_base::createRootNode()
    {
        return /* AProNew3(Node_base) ();*/ nullptr;
    }

    void destroyNode(Node_base* node)
    {
        if(node)
        {
            node->reset();
            deallocate_node_internal(node);
        }
    }

    void deallocate_node_internal(Node_base* node)
    {
        AProDelete3(node);
    }

    void clear()
    {
        destroyNode(m_root_node);
        m_root_node = createRootNode();
    }

    int getMaxDepthLevel() const
    {
        return m_max_depth_level;
    }

    void setMaxDepthLevel(int max_depth_level)
    {
        m_max_depth_level = max_depth_level;
    }

    int getMaxChildLevel() const
    {
        return m_max_child_level;
    }

    void setMaxChildLevel(int max_child_level)
    {
        m_max_child_level = max_child_level;
    }

    void changeRootNode(Node_base* root_node)
    {
        if(m_root_node)
        {
            clear();
        }

        m_root_node = root_node;
        if(!m_root_node)
        {
            m_root_node = createRootNode();
        }
    }

    Node_base* getRootNode()
    {
        if(!m_root_node)
            m_root_node = createRootNode();

        return m_root_node;
    }

    const Node_base* getRootNode() const
    {
        return m_root_node;
    }

    int findDepthLevel(Node_base* node, Node_base* from = 0)
    {
        if(!node)
            return -1;

        Node_base* node_parent = node->m_parent;
        int depth = 0;
        while(node_parent != from && node_parent)
        {
            depth++;
            node_parent = node_parent->m_parent;
        }

        if(node_parent != from)
            return -1;

        return depth;
    }

}
