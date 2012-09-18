/** @file NullWriter.cpp
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 01/09/2012
 *
 *  @addtogroup Global
 *  @addtogroup Resource
 *
 *  This file defines the NullWriter class.
 *
**/
#include "NullWriter.h"

namespace APro
{
    NullWriter::NullWriter()
        : ResourceWriter()
    {
        setParam(String("Name"), Variant(String("NullWriter")));
        setParam(String("Description"), Variant(String("A null ResourceWriter, do nothing.")));
    }

    NullWriter::NullWriter(const NullWriter& other)
        : ResourceWriter(other)
    {

    }

    NullWriter::~NullWriter()
    {

    }

    void NullWriter::write(const SharedPointer<Resource> & resource, const String& filename) const
    {
        Console::get() << "\n[NullWriter] Writing object " << resource->getName() << " finished !";
    }
}
