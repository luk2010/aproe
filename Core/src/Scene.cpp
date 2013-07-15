////////////////////////////////////////////////////////////
/** @file Scene.cpp
 *  @ingroup Rendering
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 12/05/2013
 *
 *  Defines the Scene object.
 *
**/
////////////////////////////////////////////////////////////
#include "Scene.h"

namespace APro
{
    Scene::Scene(const String& name)
        : m_name(name)
    {

    }

    Scene::~Scene()
    {
        m_scene_tree.clear();
    }
}
