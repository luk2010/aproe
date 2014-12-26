/////////////////////////////////////////////////////////////
/** @file Main.h
 *  @ingroup Global
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 20/09/2012 - 18/04/2014
 *
 *  Defines the Main class.
 *
**/
////////////////////////////////////////////////////////////
#ifndef APROMAIN_H
#define APROMAIN_H

#include "Platform.h"
#include "Singleton.h"
#include "Console.h"
#include "RenderingAPI.h"
#include "IdGenerator.h"
#include "PointerCollector.h"
#include "Console.h"
#include "WindowManager.h"
#include "ResourceManager.h"
#include "PluginManager.h"
#include "MathFunctionManager.h"
#include "Implementation.h"
#include "ThreadManager.h"
#include "AbstractObject.h"

namespace APro
{
    ////////////////////////////////////////////////////////////
    /** @class Main
     *  @ingroup Global
     *  @brief Main class for every instance of the Engine.
     *  @details This class let you manage every implementation, plugin,
     *  add-on, etc of the engine. You can access from everywhere
     *  every things in the Engine, like the file system, the window manager,
     *  the console, etc...
     *  @note This class is automaticly created in an executable,
     *  and automaticly loaded in a library. However, at the end of
     *  your program, you must use the clear() function to "clear"
     *  everything.
    **/
    ////////////////////////////////////////////////////////////
    class APRO_DLL Main : public Singleton<Main>
    {
        APRO_DECLARE_SINGLETON(Main)

    protected:

        ////////////////////////////////////////////////////////////
        /** Default constructor.
          * @note The constructor is involved at the firt use of Main::Get()
          * function. Please be sure to call every Main::Get() function in a
          * try / catch block, to catch exception that may be thrown during
          * the initialization process.
        **/
        ////////////////////////////////////////////////////////////
        Main();

        ////////////////////////////////////////////////////////////
        /** Destructor.
        **/
        ////////////////////////////////////////////////////////////
        ~Main();

    public:

        ////////////////////////////////////////////////////////////
        /** Initialize the Engine.
         *  @note Call this function the first time you use the get()
         *  command.
         *  @param argc : Argument count
         *  @param argv : Arguments.
         *  @return The Main object.
        **/
        ////////////////////////////////////////////////////////////
        Main& init(int argc, const char* argv[]);

        ////////////////////////////////////////////////////////////
        /** Clean the Engine.
         *  @note Call the functioon at the end of your program.
        **/
        ////////////////////////////////////////////////////////////
        void clear();

    public:

        ////////////////////////////////////////////////////////////
        /** Describes a set of global options.
        **/
        ////////////////////////////////////////////////////////////
        class GlobalOption
        {
            public: enum t
            {
                Debugging_Implementation = 1
            };
        };

        ////////////////////////////////////////////////////////////
        /** Set an option to given state.
         *  @param option : Option to set the state.
         *  @param state : New state of the option.
        **/
        ////////////////////////////////////////////////////////////
        void setOption(unsigned int option, bool state);

        ////////////////////////////////////////////////////////////
        /** Tell if an option is activated or not.
         *  @param option : Option to tell.
         *  @return If the option is activated.
        **/
        ////////////////////////////////////////////////////////////
        bool hasOption(unsigned int option) const;

    public:

        const IdGenerator& getIdGenerator() const
        {
            return *id_generator;
        }

        IdGenerator& getIdGenerator()
        {
            return *id_generator;
        }

        const PointerCollector& getGlobalPointerCollector() const
        {
            return *sharedpointer_collector;
        }

        PointerCollector& getGlobalPointerCollector()
        {
            return *sharedpointer_collector;
        }

        const Console& getConsole() const
        {
            return Console::Get();
        }

        Console& getConsole()
        {
            return Console::Get();
        }

        const WindowManager& getWindowManager() const
        {
            return *windowManager;
        }

        WindowManager& getWindowManager()
        {
            return *windowManager;
        }

        const ResourceManager& getResourceManager() const
        {
            return *resourceManager;
        }

        ResourceManager& getResourceManager()
        {
            return *resourceManager;
        }

        const PluginManager& getPluginManager() const
        {
            return *pluginManager;
        }

        PluginManager& getPluginManager()
        {
            return *pluginManager;
        }

        const MathFunctionManager& getMathManager() const
        {
            return *mathManager;
        }

        MathFunctionManager& getMathManager()
        {
            return *mathManager;
        }

        const ImplementationFactory& getImplementations() const
        {
            return *impFactory;
        }

        ImplementationFactory& getImplementations()
        {
            return *impFactory;
        }

        const ThreadManager& getThreadManager() const
        {
            return *tmanager;
        }

        ThreadManager& getThreadManager()
        {
            return *tmanager;
        }

        const AbstractObjectFactory& getObjectFactory() const
        {
            return *abstract_object_factory;
        }

        AbstractObjectFactory& getObjectFactory()
        {
            return *abstract_object_factory;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Creates a RenderingAPI object.
         *  @note An Implementation must be available to creates a new
         *  RenderingAPI Object.
        **/
        ////////////////////////////////////////////////////////////
        RenderingAPIPtr createRenderingAPI();

    private:
        // In activation order ! Don't change

        // Core
        /* 1. The Idgenerator, because it is needed by almost
        everyone and no needs for himself. */
        IdGenerator* id_generator;
        /* 2. The PointerCollector. It doesn't need anything
        as the IdGenerator.*/
        PointerCollector* sharedpointer_collector;

        // Factory
        /* 3. The ImplementationFactory. Needs only the Manager, wich needs
        ThreadSafe and AutoPointer. */
        ImplementationFactory* impFactory;
        /* 4. The AbstractObjectFactory. Needs only the Manager, wich needs
        ThreadSafe and AutoPointer. */
        AbstractObjectFactory* abstract_object_factory;

        // EventUniter
        /* 5. The EventUniter. Needs Thread implementation but no ThreadManager.
        Needs what is above. */
        EventUniter* euniter;

        // Manager
        /* 6. The ThreadManager. It needs only the IdGenerator
        and the PointerCollector. */
        ThreadManager* tmanager;
        /* 7. The MathFunctionManager. It needs only the IdGenerator
        and the PointerCollector. */
        MathFunctionManager* mathManager;
        /* 8. The ResourceManager. Needs only the Manager, wich needs
        ThreadSafe and AutoPointer and the ThreadManager, as resources loading
        and writing is done multi-threaded. */
        ResourceManager* resourceManager;
        /* 9. The PluginManager. Needs almost everything above. */
        PluginManager* pluginManager;
        /* 10. The WindowManager. Needs a window plugin loaded. */
        WindowManager* windowManager;

    private:

        Map<int, bool> options;
    };
}

#endif
