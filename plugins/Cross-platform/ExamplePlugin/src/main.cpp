/*

    This program is an example on how to create a pugin for Atlanti's Projet Engine.

    Copyright @Luk2010 2010-2012

*/

#include <Platform.h>
#include <PluginHandle.h>
#include <Console.h>
#include <SString.h>
#include <Main.h>
#include <ResourceManager.h>

using namespace APro;

PluginInfo info;

extern "C" void* GetPluginInfo(void)
{
    return (void*) &info;
}

extern "C" void StartPlugin(void)
{
    Console::get().backgroundColor(Console::Color::Green)
                  .foregroundColor(Console::Color::White)
                  << "\n[ExamplePlugin] This is a message from the plugin ;) ! START ";
    Console::get().reset();

    info.name = String("ExamplePlugin");
    info.description = String("This program is an example on how to create a pugin for Atlanti's Projet Engine.");

    SharedPointer<Resource> myresource = Main::get().getResourceManager().loadResourceWithLoader(String("MyResource"), String("leaks.log"),
                                                                                       String("NullLoader"));
}

extern "C" void EndPlugin(void)
{
    Console::get().backgroundColor(Console::Color::Red)
                  .foregroundColor(Console::Color::White)
                  << "\n[ExamplePlugin] This is a message from the plugin ;) ! END ";

    Console::get().reset();
}
