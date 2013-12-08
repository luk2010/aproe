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
#include "PointerCollector.h"
#include "AbstractObject.h"
#include "IdGenerator.h"

#include <unistd.h>

namespace APro
{
    APRO_IMPLEMENT_SINGLETON(Main)

    class MainException : public Exception
    {
        APRO_MAKE_EXCEPTION(MainException)

        const char* what() const throw() { return "Can't initialize Main class."; }
    };

    Main::Main()
    {
        resourceManager = nullptr;
//      impStore = nullptr;
        impFactory = nullptr;
        pluginManager = nullptr;
        mathManager = nullptr;
        windowManager = nullptr;
        fs = nullptr;
        tmanager = nullptr;
        sharedpointer_collector = nullptr;
        abstract_object_factory = nullptr;
        id_generator = nullptr;
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


        // -- Core ---------------------------------------------------------------------

        id_generator = AProNew(IdGenerator);
        if(id_generator)
        {
            IdGenerator::__curent_IdGenerator = id_generator;
            getConsole() << "\n[Main] Global ID Generator OK.";
        }
        else
        {
            getConsole() << "\n[Main] Can't create Global ID Generator ! Aborting...";
            clear();
            aprothrow(MainException);
        }

        sharedpointer_collector = AProNew(PointerCollector, String("Global"));
        if(sharedpointer_collector)
        {
            PointerCollector::__curent_PointerCollector = sharedpointer_collector;
            getConsole() << "\n[Main] Global Pointer Collector OK.";
        }
        else
        {
            getConsole() << "\n[Main] Can't create Global Pointer Collector ! Aborting...";
            clear();
            aprothrow(MainException);
        }

        // -- Factory ------------------------------------------------------------------

        impFactory = AProNew(ImplementationFactory);
        if(impFactory)
        {
            ImplementationFactory::__curent_ImplementationFactory = impFactory;
            getConsole() << "\n[Main] Implementation Factory OK.";
        }
        else
        {
            getConsole() << "\n[Main] Can't create Implementation Factory ! Aborting...";
            clear();
            aprothrow(MainException);
        }

        abstract_object_factory = AProNew(AbstractObjectFactory);
        if(abstract_object_factory)
        {
            AbstractObjectFactory::__curent_AbstractObjectFactory = abstract_object_factory;
            getConsole() << "\n[Main] Object Factory OK.";
        }
        else
        {
            getConsole() << "\n[Main] Can't create Object Factory ! Aborting...";
            clear();
            aprothrow(MainException);
        }

        // -- Event Uniter -------------------------------------------------------------

        euniter = AProNew(EventUniter, String("GlobalUniter"));
        if(euniter)
        {
            EventUniter::__curent_EventUniter = euniter;
            getConsole() << "\n[Main] EventUniter OK.";
        }
        else
        {
            getConsole() << "\n[Main] Can't create EventUniter ! Aborting...";
            clear();
            aprothrow(MainException);
        }

        // -- Manager ------------------------------------------------------------------

        tmanager = AProNew(ThreadManager);
        if(tmanager)
        {
            ThreadManager::__curent_ThreadManager = tmanager;
            getConsole() << "\n[Main] Thread Manager OK.";
        }
        else
        {
            getConsole() << "\n[Main] Can't create Thread Manager ! Aborting...";
            clear();
            aprothrow(MainException);
        }

        mathManager = AProNew(MathFunctionManager);
        if(mathManager)
        {
            MathFunctionManager::__curent_MathFunctionManager = mathManager;
            getConsole() << "\n[Main] Math Function Manager OK.";
        }
        else
        {
            getConsole() << "\n[Main] Can't create Math Function Manager ! Aborting...";
            clear();
            aprothrow(MainException);
        }

        resourceManager = AProNew(ResourceManager);
        if(resourceManager)
        {
            // Add default loader here.
            resourceManager->addLoader(ResourceLoaderPtr(AProNew(DynamicLibraryLoader)));
            resourceManager->addLoader(ResourceLoaderPtr(AProNew(NullLoader)));

            ResourceManager::__curent_ResourceManager = resourceManager;
            getConsole() << "\n[Main] Resource Manager OK.";
        }
        else
        {
            getConsole() << "\n[Main] Can't create Resource Manager ! Aborting...";
            clear();
            aprothrow(MainException);
        }

        pluginManager = AProNew(PluginManager);
        if(pluginManager)
        {
            PluginManager::__curent_PluginManager = pluginManager;
            getConsole() << "\n[Main] Plugin Manager OK. Loading plugins and implementations in directory \"plugins\".";
            pluginManager->loadDirectory(String("plugins/"));
        }
        else
        {
            getConsole() << "\n[Main] Can't create Plugin Manager ! Aborting...";
            clear();
            aprothrow(MainException);
        }

        windowManager = AProNew(WindowManager);
        if(windowManager)
        {
            WindowManager::__curent_WindowManager = windowManager:
            getConsole() << "\n[Main] Window Manager OK.";
        }
        else
        {
            getConsole() << "\n[Main] Can't create Window Manager ! Aborting...";
            clear();
            aprothrow(MainException);
        }


/*
        impStore = AProNew(ImplementationStore);
        if(impStore)
            getConsole() << "\n[Main] Implementation Store OK.";
        else
        {
            getConsole() << "\n[Main] Can't create Implementation Store ! Aborting...";
            APRO_THROW("Initialization Failed", "Can't Initialize Main Class !", "Main");
        }
 */



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



        fs = AProNew(FileSystem, workingdir, fs);
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

        if(abstract_object_factory)
        {
            AProDelete(abstract_object_factory);
            getConsole() << "\n[Main] Object Factory cleaned !";
        }
        else
        {
            getConsole() << "\n[Main] Can't clean Object Factory because not initialized !";
        }

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
            AProDelete(tmanager);
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

/*
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
 */

        if(impFactory)
        {
            impFactory->clear();
            AProDelete(impFactory);
            impFactory = nullptr;
            getConsole() << "\n[Main] Implementation Factory cleaned !";
        }
        else
        {
            getConsole() << "\n[Main] Can't clean Implementation Factory because not initialized !";
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

        if(sharedpointer_collector)
        {
            AProDelete(sharedpointer_collector);
            sharedpointer_collector = nullptr;
            getConsole() << "\n[Main] Global Pointer Collector cleaned !";
        }
        else
        {
            getConsole() << "\n[Main] Can't clean Global Pointer Collector because not initialized !";
        }

        if(id_generator)
        {
            AProDelete(id_generator);
            id_generator = nullptr;
            getConsole() << "\n[Main] Global ID Generator cleaned !";
        }
        else
        {
            getConsole() << "\n[Main] Can't clean Global ID Generator because not initialized !";
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
