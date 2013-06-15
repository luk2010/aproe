////////////////////////////////////////////////////////////
/** @file SceneNode.h
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
#ifndef APROSCENENODE_H
#define APROSCENENODE_H

#include "Platform.h"
#include "SharedPointer.h"
#include "Tree.h"

namespace APro
{
    ////////////////////////////////////////////////////////////
    /** @class SceneNode
     *  @ingroup Rendering
     *  @brief Defines a Node that can be introducted in
     *  a Scene.
     *  @details Any SceneNode that subclass this one will
     *  be able to be rendered by a Renderer when stocked in
     *  a Scene.
     *
     *  A SceneNode type is the usability of the node. The renderer
     *  and the scene will interpret differently the node if it is
     *  a renderable node, a light, a camera or a viewport.
    **/
    ////////////////////////////////////////////////////////////
    class APRO_DLL SceneNode : public Node_base
    {
        APRO_DECLARE_SHAREDPOINTER_CLASS_TYPEDEF(SceneNode)

    public:

        class Type
        {
            public: enum t
            {
                Renderable,///< A node that will be rendered.
                Light,///< A node used as a light.
                Camera,///< A camera node.
                Viewport,///< A viewport node.
                Unknown///< Unknown node type. Unused.
            };
        };

    protected:

        Type::t m_node_type;///< Type of node.

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Default constructor.
        **/
        ////////////////////////////////////////////////////////////
        SceneNode();

        ////////////////////////////////////////////////////////////
        /** @brief Node_base Constructor.
        **/
        ////////////////////////////////////////////////////////////
        SceneNode(SceneNode* parent, Tree_base* parent_tree = nullptr);

        ////////////////////////////////////////////////////////////
        /** @brief SceneNode constructor.
         *
         *  @param node_type : Type of node. Generally given by
         *  subclass.
        **/
        ////////////////////////////////////////////////////////////
        SceneNode(Type::t node_type, SceneNode* parent, Tree_base* parent_tree = nullptr);

        ////////////////////////////////////////////////////////////
        /** @brief Destructor.
        **/
        ////////////////////////////////////////////////////////////
        virtual ~SceneNode();

        ////////////////////////////////////////////////////////////
        /** @brief Return the type of node.
        **/
        ////////////////////////////////////////////////////////////
        Type::t getType() const;

        ////////////////////////////////////////////////////////////
        /** @see Node_base::clear.
        **/
        ////////////////////////////////////////////////////////////
        virtual void clear()
        {

        }
    };

    typedef Tree<SceneNode> SceneTree;
}

#endif
