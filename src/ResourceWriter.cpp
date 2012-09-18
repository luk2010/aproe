/** @file ResourceWriter.cpp
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 01/09/2012
 *
 *  @addtogroup Global
 *  @addtogroup Resource
 *
 *  This file defines the ResourceWriter class.
 *
**/
#include "ResourceWriter.h"

namespace APro
{
    ResourceWriter::ResourceWriter()
        : ParametedObject()
    {
        setParam(String("Name"), Variant(String("ResourceWriter")), String("Name of the writer."));
        setParam(String("Description"), Variant(String("A Basic ResourceWriter.")), String("Description or Usage of the writer."));
        setParam(String("DefaultFile"), Variant(String("")), String("Default file to write resource."));
    }

    ResourceWriter::ResourceWriter(const ResourceWriter& other)
        : ParametedObject(other)
    {

    }

    ResourceWriter::~ResourceWriter()
    {

    }

    String ResourceWriter::name() const
    {
        return getParam(String("Name")).to<String>();
    }

    String ResourceWriter::description() const
    {
        return getParam(String("Description")).to<String>();
    }

    ResourceWriter& ResourceWriter::operator<<(const SharedPointer<Resource> & resource)
    {
        ResourceWriter::write(resource, getParam(String("DefaultFile")).to<String>());
        return *this;
    }

    void ResourceWriter::write(const SharedPointer<Resource> & resource, const String& filename) const
    {

    }
}
