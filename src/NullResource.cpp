/** @file NullResource.cpp
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 18/09/2012
 *
 *  @addtogroup Global
 *  @addtogroup Resource
 *
 *  This file defines the NullResource class.
 *
**/
#include "NullResource.h"

namespace APro
{
    NullResource::NullResource() : Resource()
    {
        type = String("NullResource");
    }

    NullResource::NullResource(const String& name_, const String& other) : Resource(name_, other)
    {
        type = String("NullResource");
    }

    NullResource::~NullResource()
    {

    }

    void NullResource::destroy()
    {

    }
}
