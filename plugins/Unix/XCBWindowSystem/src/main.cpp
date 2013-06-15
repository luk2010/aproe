/*
    XCB Windowing System Implementation
*/

#include <Main.h>
#include <PluginHandle.h>

#include "XCBWindowImp.h"

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
        console << "\n[XCBWindow] Starting plugin...";

        info.name = String("XCBWindow");
        info.author = String("Luk2010");
        info.date = String("01/04/2013");
        info.description = String("XCB Window System Implementation. As XCB is avalaible only on Unix-like system, OpenGL (Mesa) Context is set.");

        ImplementationStore& impstore = Main::get().getImplementationStore();
        impstore.store(AProNew(1, XCBWindowImp) ());

        console << "\n[XCBWindow] Plugin started.";
    }

    void EndPlugin(void)
    {
        Console& console = Console::get();
        console << "\n[XCBWindow] Ending plugin...";

        ImplementationStore& impstore = Main::get().getImplementationStore();
        impstore.unstore(Variant(String("APro::Window")));

        console << "\n[XCBWindow] Plugin ended.";
    }
}
