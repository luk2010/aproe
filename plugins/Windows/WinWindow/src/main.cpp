/*
    Windows Window Plugin

    Provides implementation for Window class, for Windows system.
*/

#include <Main.h>
#include "WinWindowImp.h"

using namespace APro;

PluginInfo info;
bool initialized = false;

extern "C" void* GetPluginInfo(void)
{
    return (void*) &info;
}

extern void StartPlugin(void)
{
    Console & console = Main::get().getConsole();
    ImplementationStore& store = Main::get().getImplementationStore();

    console << "\n[WinWindow] Initializing plugin...";

    if(!store.store(SharedPointer<Implementation>(AProNew(1, WinWindowImp))))
    {
        console << "\n[WinWindow] Couldn't store Windows Implementation ! Perhaps there is already another implementation.";
        return;
    }

    initialized = true;
    console << "\n[WinWindow] Plugin initialized !";
}

extern void EndPlugin(void)
{
    Console & console = Main::get().getConsole();
    ImplementationStore& store = Main::get().getImplementationStore();

    if(initialized)
    {
        store.unstore(Variant(String("APro::Window")));
        console << "\n[WinWindow] Plugin uninitialized !";
    }
}
