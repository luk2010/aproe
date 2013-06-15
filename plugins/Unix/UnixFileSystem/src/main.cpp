/*
    Unix File System plugin

    Provide basic file system function to Atlanti's Project Engine.
*/

#include <Main.h>
#include <PluginManager.h>

#include "UnixFSI.h"

using namespace APro;

PluginInfo info;
extern "C" void* GetPluginInfo(void)
{
    return (void*) &info;
}

extern "C" void StartPlugin(void)
{
    Console& console = Main::get().getConsole();
    console << "\n[Unix FileSystem] Starting Unix File System Plugin.";

    info.name = String("UnixFileSystem");
    info.author = String("Luk2010");
    info.date = String("1/04/2013");
    info.description = String("File System Implementation for Unix-like systems !");

    ImplementationStore& impstore = Main::get().getImplementationStore();
    impstore.store(AProNew(1, UnixFSI) ());

    console << "\n[Unix FileSystem] Started successfully !";
}

extern "C" void EndPlugin(void)
{
    Console& console = Main::get().getConsole();
    console << "\n[Unix FileSystem] Ending Unix File System Plugin.";

    ImplementationStore& impstore = Main::get().getImplementationStore();
    impstore.unstore(Variant(String("APro::FileSystem")));

    console << "\n[Unix FileSystem] Ended successfully !";
}
