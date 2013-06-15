/*
    Posix Thread System.
*/

#include <Main.h>
#include <Implementation.h>
#include <PluginHandle.h>

#include "PosixThread.h"
#include "PosixThreadCondition.h"
#include "PosixThreadMutex.h"

using namespace APro;
PluginInfo info;

extern "C"
{
    void* GetPluginInfo(void)
    {
        return (void*) &info;
    }

    void StartPlugin(void)
    {
        Console& console = Console::get();
        console << "\n[PosixThread] Starting plugin...";

        info.name = String("PosixThread");
        info.author = String("Luk2010");
        info.date = String("08/04/2013");
        info.description = String("Implements full threading system, i.e. Thread, Condition and Mutex.");

        ImplementationStore& impstore = Main::get().getImplementationStore();
        impstore.store(AProNew(1, PosixThread));
        impstore.store(AProNew(1, PosixThreadCondition));
        impstore.store(AProNew(1, PosixThreadMutex));

        console << "\n[PosixThread] Plugin started.";
    }

    void EndPlugin(void)
    {
        Console& console = Console::get();
        console << "\n[PosixThread] Stopping plugin...";

        ImplementationStore& impstore = Main::get().getImplementationStore();
        impstore.unstore(Variant(String("APro::Thread")));
        impstore.unstore(Variant(String("APro::ThreadCondition")));
        impstore.unstore(Variant(String("APro::ThreadMutex")));

        console << "\n[PosixThread] Plugin stopped.";
    }
}
