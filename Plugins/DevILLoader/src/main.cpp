/*
    DevIL Image Loader / Writer for Atlanti's Project Engine.
    The plugin is compiled with the static DevIL library.

    All you have to do is load the plugin. It automaticly
    register the loader and writer.

    Available Loader : DevIL Loader
    Available Writer : DevIL Writer

    luk2010 2012 - 2013
*/

#include <Main.h>

#include "Loader.h"
#include "Writer.h"

using namespace APro;

PluginInfo info;

extern "C" void* GetPluginInfo(void)
{
    return (void*) &info;
}

extern "C" void StartPlugin(void)
{
    Console & console = Main::get().getConsole();
    console << "\n[DevIL Image Loader] Initializing plugin...";

    ResourceManager& rmanager = Main::get().getResourceManager();

    rmanager.addLoader(SharedPointer<ResourceLoader>(AProNew(1, DevILLoader)));
    rmanager.addWriter(SharedPointer<ResourceWriter>(AProNew(1, DevILWriter)));

    console << "\n[DevIL Image Loader] Plugin initialized !";
}

extern "C" void EndPlugin(void)
{
    Console & console = Main::get().getConsole();
    ResourceManager& rmanager = Main::get().getResourceManager();

    rmanager.removeLoader(rmanager.getLoader(String("DevILLoader")));
    rmanager.removeWriter(rmanager.getWriter(String("DevILWriter")));

    console << "\n[DevIL Image Loader] Plugin disabled !";
}
