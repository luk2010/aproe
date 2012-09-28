/*
    DevIL Image Loader / Writer for Atlanti's Project Engine.

    Luk2010 2012 - 2013
*/

#ifndef DEVILLOADER_H
#define DEVILLOADER_H

#include <ResourceLoader.h>

using namespace APro;

class DevILLoader : public ResourceLoader
{
public:

    DevILLoader();
    DevILLoader(const DevILLoader& loader);

    ~DevILLoader();

    SharedPointer<Resource> loadResource(const String& filename);

public:

    static void initializeDevIL();

    static bool is_devil_initialized;
};

#endif
