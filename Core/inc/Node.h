/////////////////////////////////////////////////////////////
/** @file Node.h
 *  @ingroup Utils
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 18/10/2012
 *
 *  Defines the Node class.
 *
**/
/////////////////////////////////////////////////////////////
#ifndef APRONODE_H
#define APRONODE_H

#include "Platform.h"
#include "SharedPointer.h"
#include "Node_base.h"

namespace APro
{
    /////////////////////////////////////////////////////////////
    /** @class Node
     *  @ingroup Utils
     *  @brief A templated class that can store one type of data.
     *  @details This data can be anything you want. For specific
     *  data clearing, just subclass this one and override the clear
     *  function.
    **/
    /////////////////////////////////////////////////////////////
    template <typename DataType>
    class Node : public Node_base
    {
    public:

        typedef Node<DataType> NodeT;

    protected:

        DataType m_data;///< Data to store

    public:

        /////////////////////////////////////////////////////////////
        /** @brief Constructor.
        **/
        /////////////////////////////////////////////////////////////
        Node()
            : Node_base()
        {

        }

        /////////////////////////////////////////////////////////////
        /** @brief Constructor.
         *  @param parent : Parent of this node.
         *  @param parent_tree : Tree that constructed this node.
        **/
        /////////////////////////////////////////////////////////////
        Node(NodeT* parent, Tree_base* parent_tree = nullptr)
            : Node_base(parent, parent_tree)
        {

        }

        /////////////////////////////////////////////////////////////
        /** @brief Constructor.
         *  @param data : Data to store.
         *  @param parent : Parent of this node.
         *  @param parent_tree : Tree that constructed this node.
        **/
        /////////////////////////////////////////////////////////////
        Node(const DataType& data, NodeT* parent, Tree_base* parent_tree = nullptr)
            : Node_base(parent, parent_tree), m_data(data)
        {

        }

        /////////////////////////////////////////////////////////////
        /** @brief Destructor.
         *  @warning No clearing must be done here, this is the tree
         *  who call the @ref reset function.
        **/
        /////////////////////////////////////////////////////////////
        virtual ~Node()
        {

        }

    public:

        /////////////////////////////////////////////////////////////
        /** @brief get the data of this node.
         *  @return the data.
        **/
        /////////////////////////////////////////////////////////////
        DataType& getData()
        {
            return m_data;
        }

        /////////////////////////////////////////////////////////////
        /** @brief get the data of this node.
         *  @return the data.
        **/
        /////////////////////////////////////////////////////////////
        const DataType& getData() const
        {
            return m_data;
        }

        /////////////////////////////////////////////////////////////
        /** @brief Set the data in the node.
         *  @param data : New data.
        **/
        /////////////////////////////////////////////////////////////
        void setData(const DataType& data)
        {
            m_data = data;
        }

        /////////////////////////////////////////////////////////////
        /** @brief Clear the node.
        **/
        /////////////////////////////////////////////////////////////
        virtual void clear()
        {

        }

    };
}

#endif
