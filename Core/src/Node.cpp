/** @file Node.cpp
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 18/10/2012
 *
 *  @addtogroup Global
 *  @addtogroup System
 *
 *  This file defines the Node class.
 *
**/
#include "Node.h"
/*
namespace APro
{
    Node::Node()
        : ParametedObject(), parent(nullptr)
    {

    }

    Node::Node(const Node& other)
        : ParametedObject(other), parent(nullptr)
    {

    }

    Node::~Node()
    {

    }

    void Node::setParent(const Node::ptr& p)
    {
        parent = p;
    }

    const Node::ptr& Node::getParent() const
    {
        return parent;
    }

    Node::ptr& Node::getParent()
    {
        return parent;
    }

    void Node::addChild(const Node::ptr& child)
    {
        if(!child.isNull())
        {
            if(!isChild(child))
            {
                childs.append(child);
                childs.last()->setParent(ReadOnlyPointer<Node>(this));
            }
        }
    }

    void Node::addChilds(const List<Node::ptr>& children)
    {
        for(size_t i = 0; i < children.size(); ++i)
        {
            addChild(children.at(i));
        }
    }

    void Node::removeChild(const Node::ptr& child)
    {
        if(isChild(child))
        {
            childs.erase(childs.find(child));
        }
    }

    void Node::clear()
    {
        parent.release();

        while(childs.size() > 0)
        {
            childs.at(0)->clear();
            childs.erase(0);
        }

        clear_intern();
    }

    bool Node::isChild(const Node::ptr& child)
    {
        if(child.isNull())
            return false;

        for(size_t i = 0; i < childs.size(); ++i)
        {
            if(childs.at(i) == child)
                return true;
        }

        return false;
    }

    bool Node::isLongChild(const Node::ptr& child) const
    {
        if(child.isNull())
            return false;

        for(size_t i = 0; i < childs.size(); ++i)
        {
            if(childs.at(i) == child)
                return true;
            else if(childs.at(i)->isLongChild(child))
                return true;
        }

        return false;
    }

    size_t Node::getChildNumber() const
    {
        return childs.size();
    }
}
*/
