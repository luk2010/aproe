/////////////////////////////////////////////////////////////
/** @file Main.h
 *  @ingroup Global
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 20/09/2012
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
#include "Context.h"
#include "Map.h"

namespace APro
{
    class WindowManager;
    class ImplementationStore;
    class ResourceManager;
    class PluginManager;
    class MathFunctionManager;
    class FileSystem;
    class ThreadManager;

    ////////////////////////////////////////////////////////////
    /** @class Main
     *  @brief Main class for every instance of the Engine.
     *  @details This class let you manage every implementation, plugin,
     *  add-on, etc of the engine. You can access from everywhere
     *  every things in the Engine, like the file system, the window manager,
     *  the console, etc...
     *  @note This class is autmaticly created in an executable,
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
          * @note The constructor is involved at the firt use of Main::get()
          * function. Please be sure to call every Main::get() function in a
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

        const Console& getConsole() const
        {
            return Console::get();
        }

        Console& getConsole()
        {
            return Console::get();
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

        const ImplementationStore& getImplementationStore() const
        {
            return *impStore;
        }

        ImplementationStore& getImplementationStore()
        {
            return *impStore;
        }

        const FileSystem& getFileSystem() const
        {
            return *fs;
        }

        FileSystem& getFileSystem()
        {
            return *fs;
        }

        const ThreadManager& getThreadManager() const
        {
            return *tmanager;
        }

        ThreadManager& getThreadManager()
        {
            return *tmanager;
        }

    private:
        // In activation order ! Don't change
        ResourceManager* resourceManager;
        ImplementationStore* impStore;
//      RendererFactoryManager* rfm;
        PluginManager* pluginManager;
        MathFunctionManager* mathManager;
        WindowManager* windowManager;
        FileSystem* fs;
        ThreadManager* tmanager;

    private:
    
        Map<int, bool> options;
    };
}

#endif
