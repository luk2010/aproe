/////////////////////////////////////////////////////////////
/** @file Main.cpp
 *  @ingroup Global
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 20/09/2012 - 26/12/2014
 *
 *  @brief
 *  Implements the Main class.
 *
 *  @copyright
 *  Atlanti's Project Engine
 *  Copyright (C) 2012 - 2014  Atlanti's Corp
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
**/
////////////////////////////////////////////////////////////
#include "Main.h"

#include "FileSystem.h"
#include "DynamicLibraryLoader.h"
#include "NullLoader.h"
#include "EventUniter.h"

// ==============================================================
// Some useful defines

#define FACTORY_CREATE(class,name) 						    \
	name = AProNew (class); 								\
	if(name) 												\
	{ 													 	\
		class::__current_##class = name;					\
		getConsole() << "\n[Main] class OK."                \
	}														\
	else													\
	{														\
		getConsole() << "\n[Main] Can't create class !";    \
		clear(); aprothrow(MainException);                  \
	}
	
#define FACTORY_CLEAN(class,name)							\
	if(name)												\
	{														\
		AProDelete(name);									\
		name = nullptr;										\
		class::__current_##class = nullptr;                 \
		getConsole() << "\n[Main] class cleaned.";          \
	}

#define SINGLETON_CLEAN(class,name) 						\
	FACTORY_CLEAN(class,name)
#define SINGLETON_CREATE(class,name)						\
	FACTORY_CREATE(class,name)
	
#define GENERIC_CHECK(class,name)                           \
	if(name) 												\
	{ 													 	\
		class::__current_##class = name;					\
		getConsole() << "\n[Main] class OK."                \
	}														\
	else													\
	{														\
		getConsole() << "\n[Main] Can't create class !";    \
		clear(); aprothrow(MainException);                  \
	}

// ==============================================================

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
        resourceManager 		= nullptr;
        impFactory				= nullptr;
        pluginManager 			= nullptr;
        mathManager 			= nullptr;
        windowManager 			= nullptr;
        tmanager			 	= nullptr;
        sharedpointer_collector = nullptr;
        abstract_object_factory = nullptr;
        id_generator 			= nullptr;
        rendererfactory 		= nullptr;
    }

    Main& Main::init(int argc, const char** argv)
    {
        getConsole() << "\n[Main] Initializing Main...";

        getConsole() << "\n[Main] Platform : ";
        getConsole() << "\n - OS        = " << Platform::ToString(Platform::Get());
        getConsole() << "\n - DebugMode = " << String::toString(Platform::IsDebugMode());

        String workingdir(FileSystem::GetCurrentWorkingDirectory());
        getConsole() << "\n[Main] Current Working directory is \"" << workingdir << "\".";

        if(argc > 1 && String("--auto-set-cwd") == argv[1])
        {
            // We set the Working directory to the current executable only if argv[1] is "--auto-set-cwd"
            workingdir = argv[0];
            workingdir = workingdir.extract(0, workingdir.findLast(FileSystem::GetSeparator()));

            getConsole() << "\n[Main] Setting Working directory to \"" << workingdir << "\".";
            if(FileSystem::SetCurrentWorkingDirectory(workingdir))
                getConsole() << "OK";
            else
                getConsole() << "FAILED";
        }

/* Main Options are now obsolete.
        setOption((int) GlobalOption::Debugging_Implementation, Platform::IsDebugMode());
        getConsole() << "\n[Main] Current configuration is : "
                     << "\n - Debugging Implementation = " << (hasOption((int) GlobalOption::Debugging_Implementation) ? "True" : "False");
*/

        // -- Core ---------------------------------------------------------------------

        SINGLETON_CREATE(IdGenerator, id_generator)

        sharedpointer_collector = AProNew(PointerCollector, String("Global"));
        GENERIC_CHECK(PointerCollector, sharedpointer_collector)

        // -- Factory ------------------------------------------------------------------

        FACTORY_CREATE(ImplementationFactory, impFactory)
        FACTORY_CREATE(AbstractObjectFactory, abstract_object_factory)
        FACTORY_CREATE(RenderingAPIFactory,   rendererfactory)

        // -- Event Uniter -------------------------------------------------------------

        euniter = AProNew(EventUniter, String("GlobalUniter"));
        GENERIC_CHECK(EventUniter, euniter)
        euniter->start();

        // -- Manager ------------------------------------------------------------------

        SINGLETON_CREATE(ThreadManager, tmanager)
        SINGLETON_CREATE(MathManager,   mathManager)

        SINGLETON_CREATE(ResourceManager, resourceManager)
        // Default loader for libraries.
		resourceManager->addLoader(ResourceLoaderPtr(AProNew(DynamicLibraryLoader)));
		resourceManager->setDefaultLoader(DYNLIB_EXTENSION, "DynamicLibraryLoader");
		// Exemple Null Loader.
		resourceManager->addLoader(ResourceLoaderPtr(AProNew(NullLoader)));

        SINGLETON_CREATE(PluginManager, pluginManager)
        getConsole() << "\n[Main] Loading plugins and implementations in directory \"plugins\"."
        pluginManager->loadDirectory(String("plugins/"));

        windowManager = AProNew(WindowManager);
        if(windowManager)
        {
            WindowManager::__current_WindowManager = windowManager;
            getConsole() << "\n[Main] Window Manager OK.";
        }
        else
        {
            getConsole() << "\n[Main] Can't create Window Manager ! Aborting...";
            clear();
            aprothrow(MainException);
        }

        getConsole() << "\n[Main] Main Initialized ! Enjoy ;)";
        return *this;
    }

    Main::~Main()
    {
        /*
        Les singleton doivent etre detruits dans l'ordre inverse ou ils ont ete crees
        afin d'etre sur de ne pas causer de troubles pendant leur destruction.
        */
    }

    void Main::clear()
    {
        /*
            Les singleton doivent etre detruits dans l'ordre inverse ou ils ont ete crees
            afin d'etre sur de ne pas causer de troubles pendant leur destruction.
        */

        getConsole() << "\n[Main] Clearing everything...";

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


        SINGLETON_CLEAN(PluginManager,   	 pluginManager)
		SINGLETON_CLEAN(ResourceManager, 	 resourceManager)
		SINGLETON_CLEAN(MathManager,     	 mathManager)
		SINGLETON_CLEAN(ThreadManager,   	 tmanager)
        SINGLETON_CLEAN(EventUniter,    	 euniter)
        
        FACTORY_CLEAN(ImplementationFactory, impFactory)
        FACTORY_CLEAN(AbstractObjectFactory, abstract_object_factory)
        FACTORY_CLEAN(RenderingAPIFactory,   rendererfactory)

        SINGLETON_CLEAN(PointerCollector, 	 sharedpointer_collector)
        SINGLETON_CLEAN(IdGenerator, 		 id_generator)

        getConsole() << "\n[Main] Cleaned !";
    }

    RenderingAPIPtr Main::createRenderingAPI()
    {
        if(ImplementationFactory::Get().hasPrototype(className<RenderingAPI>()))
            return RenderingAPIPtr(reinterpret_cast<RenderingAPI*>(ImplementationFactory::Get().create(className<RenderingAPI>())));
        else
            return RenderingAPIPtr(nullptr);
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
