////////////////////////////////////////////////////////////
/** @file SceneNode.cpp
 *  @ingroup Rendering
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 02/06/2013
 *
 *  Defines the SceneNode class.
 *
**/
////////////////////////////////////////////////////////////
#include "SceneNode.h"

namespace APro
{
    SceneNode::SceneNode()
        : m_node_type(Type::Unknown)
    {

    }

    SceneNode::SceneNode(SceneNode* parent, Tree_base* parent_tree)
        : Node_base(parent, parent_tree), m_node_type(Type::Unknown)
    {

    }

    SceneNode::SceneNode(Type::t node_type, SceneNode* parent, Tree_base* parent_tree)
        : Node_base(parent, parent_tree), m_node_type(node_type)
    {

    }

    SceneNode::~SceneNode()
    {

    }

    SceneNode::Type::t SceneNode::getType() const
    {
        return m_node_type;
    }
}

