////////////////////////////////////////////////////////////
/** @file Tree_base.h
 *  @ingroup Utils
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 11/05/2013
 *
 *  Defines a Tree generic interface.
 *
**/
////////////////////////////////////////////////////////////
#ifndef APRO_TREE_BASE_H
#define APRO_TREE_BASE_H

#include "Platform.h"
#include "SharedPointer.h"
#include "Node_base.h"

namespace APro
{
    ////////////////////////////////////////////////////////////
    /** @class Tree_base
     *  @ingroup Utils
     *  @brief Defines a base class for every Tree in the engine.
     *  @details A tree always has a root node, and this class let
     *  you choose the max evel of depth and children by node.
     *  @note As each node is different, you must use the Tree
     *  template class to create it.
     *  @note A tree has a Depth level (maximum number of vertical child)
     *  and a Child level (maximum number of child by node).
    **/
    ////////////////////////////////////////////////////////////
    class APRO_DLL Tree_base
    {
    protected:

        Node_base*          m_root_node;///< Root Node.
        int                 m_max_depth_level;///< Max Depth level.
        int                 m_max_child_level;///< Max Child level.

        static const int    s_max_child_level_infinite : -1;
        static const int    s_max_depth_level_infinite : -1;

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Default constructor.
         *  @param max_child_level : The max child level to apply to
         *  this tree.
         *  @param max_depth_level : The max depth level to apply to
         *  this tree.
        **/
        ////////////////////////////////////////////////////////////
        Tree_base(int max_child_level = s_max_child_level_infinite,
                  int max_depth_level = s_max_depth_level_infinite);

        ////////////////////////////////////////////////////////////
        /** @brief Copy Constructor.
         *  @note Nodes aren't copied. You must use the changeRootNode
         *  function to do it.
         *  @code
         *  mytree.changeRootNode(myothertree.copyNode(myothertree.getRootNode()));
         *  @endcode
         *  @param other : Tree to copy parameters.
        **/
        ////////////////////////////////////////////////////////////
        Tree_base(const Tree_base& other);

        ////////////////////////////////////////////////////////////
        /** @brief Destructor.
        **/
        ////////////////////////////////////////////////////////////
        virtual ~Tree_base();

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Create a node with data and parent.
         *  @details Use it to create a new node for this tree.
         *
         *  @note The parent will be set by the Node_base::addChild
         *  function if it doesn't match.
         *  @note This function verify the creatibility of the node.
         *
         *  @param data : Data to apply to the node.
         *  @param parent : Parent node to newly created one.
         *  @return Created node.
        **/
        ////////////////////////////////////////////////////////////
        template <typename TypeData>
        Node_base* createNode(const TypeData& data, Node_base* parent = 0)
        {
            if(parent)
            {
                if(parent->getNumChildren() >= m_max_child_level)
                    return nullptr;

                int depth_level = findDepthLevel(parent);
                if(depth_level >= m_max_depth_level)
                    return nullptr;
            }

            Node_base* new_node = createNode_internal(data, parent);
            return new_node;
        }

    protected:

        ////////////////////////////////////////////////////////////
        /** @brief Allocate a new node.
         *  @internal
         *
         *  @details This function shall (and must) be overriden by
         *  Tree subclass to allocate custom node type.
         *
         *  @param data : Data to apply to the node.
         *  @param parent : Parent node to newly created one.
         *  @return Created node.
         *
         *  @sa Tree_base::deallocate_node_internal
        **/
        ////////////////////////////////////////////////////////////
        template <typename TypeData>
        virtual Node_base* createNode_internal(const TypeData& data, Node_base* parent)
        {
            return nullptr;
        }

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Copy a node.
         *  @details Use the createNode method. Return null if didn't
         *  succeed.
         *
         *  @param other : Node to copy.
         *  @param new_parent : Parent to the copied node.
         *  @param recursive : If true, children will be copied. If false,
         *  they won't.
         *  @return Copied node.
        **/
        ////////////////////////////////////////////////////////////
        Node_base* copyNode(const Node_base* other, Node_base* new_parent = 0, bool recursive = true);

    protected:

        ////////////////////////////////////////////////////////////
        /** @brief Allocate the root node.
         *  @internal
         *  @details This function can be overriden by subclass to provide
         *  custom root node construction.
         *
         *  @return Root node.
        **/
        ////////////////////////////////////////////////////////////
        virtual Node_t* createRootNode();

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Destroy a node.
         *  @details A valid deallocation must be avalaible.
         *
         *  @note Every node custom destruction are in the Node_base::clear
         *  function.
         *
         *  @param node : Node to destroy.
        **/
        ////////////////////////////////////////////////////////////
        void destroyNode(Node_base* node);

    protected:

        ////////////////////////////////////////////////////////////
        /** @brief Deallocate a node.
         *  @details You shall use the AProDelete system, with the AProNew one.
         *  You shall also correctly cast the node to appropriate type
         *  to avoid bad type deallocation.
         *
         *  @param node : Node to deallocate.
        **/
        ////////////////////////////////////////////////////////////
        virtual void deallocate_node_internal(Node_base* node);

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Clear the root node and create a new one.
        **/
        ////////////////////////////////////////////////////////////
        void clear();

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Get the Max depth level of this tree.
         *  @return Max Depth Level.
        **/
        ////////////////////////////////////////////////////////////
        int getMaxDepthLevel() const;

        ////////////////////////////////////////////////////////////
        /** @brief Set the Max depth level of this tree.
         *  @param max_depth_level : Max depth level.
        **/
        ////////////////////////////////////////////////////////////
        void setMaxDepthLevel(int max_depth_level);

        ////////////////////////////////////////////////////////////
        /** @brief Get the Max Child level of this tree.
         *  @return Max Child Level.
        **/
        ////////////////////////////////////////////////////////////
        int getMaxChildLevel() const;

        ////////////////////////////////////////////////////////////
        /** @brief Set the Max Child Level of this tree.
         *  @param max_child_level : Max Child level.
        **/
        ////////////////////////////////////////////////////////////
        void setMaxChildLevel(int max_child_level);

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Change the root node.
         *  @details Clear the old one if it existed, and copy given node.
         *
         *  @note If given node is null, a new one is created, and effect
         *  is equivalent to Tree_base::clear.
         *
         *  @param root_node : Node to copy as root.
        **/
        ////////////////////////////////////////////////////////////
        void changeRootNode(Node_base* root_node);

        ////////////////////////////////////////////////////////////
        /** @brief Get the Root Node of this tree.
         *  @return Root Node.
        **/
        ////////////////////////////////////////////////////////////
        Node_base* getRootNode();

        ////////////////////////////////////////////////////////////
        /** @brief Get the Root Node of this tree.
         *  @return Root Node.
        **/
        ////////////////////////////////////////////////////////////
        const Node_base* getRootNode() const;

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Get the Depth level of a node in the tree.
         *  @details The depth Level of a node is how many parents does this node
         *  have before root node. This is a vertical approach.
         *
         *  @param node : Node to find
         *  @param from : Node to interpret as root node. If null, root node
         *  is taken.
         *  @return Depth level. if negativ, an error has occured.
        **/
        ////////////////////////////////////////////////////////////
        int findDepthLevel(Node_base* node, Node_base* from = 0);

    };
}

#endif // APRO_TREE_BASE_H
