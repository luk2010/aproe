////////////////////////////////////////////////////////////
/** @file NullWriter.cpp
 *  @ingroup Core
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 01/09/2012 - 16/06/2014
 *
 *  This file defines the NullWriter class.
 *
**/
////////////////////////////////////////////////////////////
#include "NullWriter.h"
#include "NullResource.h"

namespace APro
{
    NullWriter::NullWriter(const String& n)
        : ResourceWriter(n, String("A Null Writer (does nothing)."))
    {
        compatible_hash << NullResource::Hash;
    }

    NullWriter::NullWriter(const NullWriter& other)
        : ResourceWriter(other)
    {

    }

    NullWriter::~NullWriter()
    {

    }

    void NullWriter::write(ResourcePtr& resource, const String& filename) const
    {
        /* Do nothing */
    }
}
