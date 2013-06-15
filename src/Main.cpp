/////////////////////////////////////////////////////////////
/** @file Main.cpp
 *  @ingroup Global
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 20/09/2012
 *
 *  Implements the Main class.
 *
**/
////////////////////////////////////////////////////////////
#include "Main.h"

#include "ResourceManager.h"
#include "WindowManager.h"
#include "PluginManager.h"
#include "Implementation.h"
#include "MathFunctionManager.h"
#include "FileSystem.h"
#include "DynamicLibraryLoader.h"
#include "NullLoader.h"
#include "ThreadManager.h"

#include <unistd.h>

namespace APro
{
    APRO_IMPLEMENT_SINGLETON(Main)

    Main::Main()
    {
        resourceManager = nullptr;
        impStore = nullptr;
        pluginManager = nullptr;
        mathManager = nullptr;
        windowManager = nullptr;
        fs = nullptr;
        tmanager = nullptr;
    }

    Main& Main::init(int argc, const char* argv[])
    {
        getConsole() << "\n[Main] Initializing Main...";

        String workingdir(FileSystem::getWorkingDirectory());

        getConsole() << "\n[Main] Current Working directory is \"" << workingdir << "\".";

        if(argc > 0)
        {
            workingdir = argv[0];
            workingdir = workingdir.extract(0, workingdir.findLast('/'));

            getConsole() << "\n[Main] Setting Working directory to \"" << workingdir << "\".";
            if(FileSystem::setWorkingDirectory(workingdir))
                getConsole() << "OK";
            else
                getConsole() << "FAILED";
        }

        setOption((int) GlobalOption::Debugging_Implementation, false);

        getConsole() << "\nCurrent configuration is : "
                     << "\n - Debugging Implementation = " << (hasOption((int) GlobalOption::Debugging_Implementation) ? "true" : "false");



        resourceManager = AProNew(1, ResourceManager);
        if(resourceManager)
        {
            // Add default loader here.
            resourceManager->addLoader(ResourceLoader::ptr(AProNew(1, DynamicLibraryLoader)));
            resourceManager->addLoader(ResourceLoader::ptr(AProNew(1, NullLoader)));

            getConsole() << "\n[Main] Resource Manager OK.";
        }
        else
        {
            getConsole() << "\n[Main] Can't create Resource Manager ! Aborting...";
            APRO_THROW("Initialization Failed", "Can't Initialize Main Class !", "Main");
        }

        impStore = AProNew(1, ImplementationStore);
        if(impStore)
            getConsole() << "\n[Main] Implementation Store OK.";
        else
        {
            getConsole() << "\n[Main] Can't create Implementation Store ! Aborting...";
            APRO_THROW("Initialization Failed", "Can't Initialize Main Class !", "Main");
        }

/* TODO
        rfm = AProNew(1, RendererFactoryManager) ();
        if(rfm)
            getConsole() << "\n[Main] Renderer Factory Manager OK.";
        else
        {
            getConsole() << "\n[Main] Can't create Renderer Factory Manager ! Aborting...";
            APRO_THROW("Initialization Failed", "Can't Initialize Main Class !", "Main");
        }
*/

        pluginManager = AProNew(1, PluginManager) ();
        if(pluginManager)
        {
            getConsole() << "\n[Main] Plugin Manager OK. Loading plugins and implementations in directory \"plugins\".";
            pluginManager->loadDirectory(String("plugins/"));
        }
        else
        {
            getConsole() << "\n[Main] Can't create Plugin Manager ! Aborting...";
            APRO_THROW("Initialization Failed", "Can't Initialize Main Class !", "Main");
        }

        tmanager = AProNew3(ThreadManager);
        if(tmanager)
        {
            // Create memorytracker mutex
            char* buffer = AProNew(1, char);
            AProDelete(buffer);
            getConsole() << "\n[Main] Thread Manager OK.";
        }
        else
        {
            getConsole() << "\n[Main] Can't create Thread Manager ! Aborting...";
            APRO_THROW("Initialization Failed", "Can't Initialize Main Class !", "Main");
        }

        mathManager = AProNew(1, MathFunctionManager) ();
        if(mathManager)
            getConsole() << "\n[Main] Math Function Manager OK.";
        else
        {
            getConsole() << "\n[Main] Can't create Math Function Manager ! Aborting...";
            APRO_THROW("Initialization Failed", "Can't Initialize Main Class !", "Main");
        }

        windowManager = AProNew(1, WindowManager) ();
        if(windowManager)
            getConsole() << "\n[Main] Window Manager OK.";
        else
        {
            getConsole() << "\n[Main] Can't create Window Manager ! Aborting...";
            APRO_THROW("Initialization Failed", "Can't Initialize Main Class !", "Main");
        }

        fs = AProNew2(FileSystem, workingdir, fs);
        if(fs)
        {
            getConsole() << "\n[Main] File System OK. Base Path is : \"" << workingdir << "\".";
        }
        else
        {
            getConsole() << "\n[Main] Can't create File System ! Aborting...";
            APRO_THROW("Initialization Failed", "Can't Initialize Main Class !", "Main");
        }

        getConsole() << "\n[Main] Main Initialized ! Enjoy ;)";
        return *this;
    }

    Main::~Main()
    {
        /*
        Les singleton doivent etre detruits dans l'ordre inverse ou ils ont ete crees
        afin d'etre sur de ne pas causer de troubles pendant leur destruction.
        NOTE : Leur destructeur devrait ne rien faire.
        */
    }

    void Main::clear()
    {
        /*
            Les singleton doivent etre detruits dans l'ordre inverse ou ils ont ete crees
            afin d'etre sur de ne pas causer de troubles pendant leur destruction.
        */

        getConsole() << "\n[Main] Clearing everything...";

        if(fs)
        {
            fs->clear();
            AProDelete2(fs);
            fs = nullptr;
            getConsole() << "\n[Main] File System cleaned !";
        }
        else
        {
            getConsole() << "\n[Main] Can't clean File System because not initialized !";
        }

        if(windowManager)
        {
            windowManager->clear();
            AProDelete(windowManager);
            windowManager = nullptr;
            getConsole() << "\n[Main] Window Manager cleaned !";
        }
        else
        {
            getConsole() << "\n[Main] Can't clean Window Manager because not initialized !";
        }

        if(mathManager)
        {
            mathManager->clear();
            AProDelete(mathManager);
            mathManager = nullptr;
            getConsole() << "\n[Main] Math Manager cleaned !";
        }
        else
        {
            getConsole() << "\n[Main] Can't clean Math Manager because not initialized !";
        }

        if(tmanager)
        {
            tmanager->stopAllThreads();
            tmanager->clear();
            AProDelete3(tmanager);
            tmanager = nullptr;
            ThreadManager::currentThreadManager = NULL;
            getConsole() << "\n[Main] Thread Manager cleaned !";
        }
        else
        {
            getConsole() << "\n[Main] Can't clean Thread Manager because not initialized !";
        }

        if(pluginManager)
        {
            pluginManager->clear();
            AProDelete(pluginManager);
            pluginManager = nullptr;
            getConsole() << "\n[Main] Plugin Manager cleaned !";
        }
        else
        {
            getConsole() << "\n[Main] Can't clean Plugin Manager because not initialized !";
        }

/*
        if(rfm)
        {
            rfm->clear();
            getConsole() << "\n[Main] Renderer Factory Manager cleaned !";
        }
        else
        {
            getConsole() << "\n[Main] Can't clean Renderer Factory Manager because not initialized !";
        }
 */

        if(impStore)
        {
            impStore->clear();
            AProDelete(impStore);
            impStore = nullptr;
            getConsole() << "\n[Main] Implementation Store cleaned !";
        }
        else
        {
            getConsole() << "\n[Main] Can't clean Implementation Store because not initialized !";
        }

        if(resourceManager)
        {
            resourceManager->clear();
            AProDelete(resourceManager);
            resourceManager = nullptr;
            getConsole() << "\n[Main] Resource Manager cleaned !";
        }
        else
        {
            getConsole() << "\n[Main] Can't clean Resource Manager because not initialized !";
        }

        getConsole() << "\n[Main] Cleaned !";
    }

    void Main::setOption(unsigned int option, bool state)
    {
        options[option] = state;
    }

    bool Main::hasOption(unsigned int option) const
    {
        return options[option];
    }
}
