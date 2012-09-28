/*
    DevIL Image Loader / Writer for Atlanti's Project Engine.

    Luk2010 2012 - 2013
*/

#ifndef DEVILWRITER_H
#define DEVILWRITER_H

#include <ResourceWriter.h>

#include "Loader.h"

using namespace APro;

class DevILWriter : public ResourceWriter
{
public:

    DevILWriter();
    DevILWriter(const DevILWriter& other);

    ~DevILWriter();

    void write(const SharedPointer<Resource> & resource, const String& filename) const;
};

#endif
