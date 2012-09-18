/*

    This program is an example on how to create a pugin for Atlanti's Projet Engine.

    Copyright @Luk2010 2010-2012

*/

#include <Platform.h>
#include <PluginHandle.h>
#include <Console.h>
#include <SString.h>
#include <ResourceManager.h>

using namespace APro;

PluginInfo info;

extern "C" void* GetPluginInfo(void)
{
    return (void*) &info;
}

extern "C" void StartPlugin(void)
{
    Console::get() << "\n[ExamplePlugin] This is a message from the plugin ;) ! START ";

    info.name = String("ExamplePlugin");
    info.description = String("This program is an example on how to create a pugin for Atlanti's Projet Engine.");

    SharedPointer<Resource> myresource = ResourceManager::get().loadResourceWithLoader(String("MyResource"), String("leaks.log"),
                                                                                       String("NullLoader"));
}

extern "C" void EndPlugin(void)
{
    Console::get() << "\n[ExamplePlugin] This is a message from the plugin ;) ! END ";
}
