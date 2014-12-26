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
    APRO_IMPLEMENT_HASHEDTYPE(NullResource);

    NullResource::NullResource() : Resource()
    {

    }

    NullResource::NullResource(const String& filename) : Resource(filename)
    {

    }

    NullResource::~NullResource()
    {

    }
}
