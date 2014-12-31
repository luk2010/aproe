/////////////////////////////////////////////////////////////
/** @file Main.h
 *  @ingroup Global
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 20/09/2012 - 30/12/2014
 *
 *  @brief
 *  Defines the Main class.
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
        
	public:
		
		////////////////////////////////////////////////////////////
        /** @enum UpdateCallback
         *  An UpdateCallback can be called before or after the update 
         *  function.
        **/
        ////////////////////////////////////////////////////////////
		enum class UpdateCallback
		{
			Before,
			After
		};

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
        Main& init(int argc, const char** argv);
        
        ////////////////////////////////////////////////////////////
        /** @brief Updates the Engine.
         *  For now, it does nothing.
        **/
        ////////////////////////////////////////////////////////////
        void update() {}

        ////////////////////////////////////////////////////////////
        /** Clean the Engine.
         *  @note Call the functioon at the end of your program.
        **/
        ////////////////////////////////////////////////////////////
        void clear();

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
        /* RenderingAPI Factory. Needs only the Manager, wich needs
        ThreadSafe and AutoPointer. */
        RenderingAPIFactory* rendererfactory;

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
    
#if 0

	/// This is an example class to show you how to divide your program using this Engine.
	/* 
		Use it like :
		main() 
		{
			try {
				
				Example::Start(argc,argv);
				
				while(1)
					Example::Update();
				
			} catch (std::exception& e) {
				std::cout << e.what() << std::endl;
			}
		}
	*/
	class Example
	{
	public:
		
		static void Start(int argc, char ** argv)
		{
			Main::init(argc, argv);
			
			// We list every rendering api, and ask for user which one to choose.
			StringArray apis = RenderingAPIFactory::Get().getRenderersList();
			RenderingAPIFactory::Get().listRegisteredRenderers();
			
			Console::Get() << "\nPlease choose one API by typing its name : \n";
			String in = Console::Get().waitInput();
			
			if(apis.find(in) == apis.end()) {
				Console::Get() << "\nWrong API. Please restart program.";
				// We exit prematurly
				Main::Get().clear();
				exit(-1);
			}
			
			// Creating the Renderer
			RenderingAPIPtr renderer = RenderingAPIFactory::Get().createRenderer(in, String("MyRenderer"));
			if(renderer.isNull()) {
				Console::Get() << "\nCould not create API " << in << "...";
				// We exit prematurly
				Main::Get().clear();
				exit(-2);
			}
			
			Console::Get() << "\nInfo : " << renderer->getRendererInfo();
			
			// Creating a cool Window
			WindowPtr window = renderer->createWindowWithContext(String("MyWindow"), String("MyFirstContext"));
			if(window.isNull()) {
				Console::Get() << "\nCould not create Window MyWindow...";
				// We exit prematurly
				Main::Get().clear();
				exit(-3);
			}
			
			// Getting Scene and setting background color to Green.
			ScenePtr scene = renderer->getRoot();
			scene->setBackgroundColor(Color::Green);
			scene->setSize(SizeString("2048x2048"));
			
			// Showing the window
			window->show();
			
			// Registering Listeners to Hardware keyboard
			EventListenerPtr keyboard = Hardware::Get().getListener("Keyboard");
			keyboard->addCallback(KeyDownEvent::Hash, [&] (EventRef e) {
				KeyDownEvent& kde = e.to<KeyDownEvent>();
				if(kde.key == Key::Up) {
					scene->setBackgroundColor(scene->getBackgroundColor().lighter());
				}
				else if(kde.key == Key::Down) {
					scene->setBackgroundColor(scene->getBackgroundColor().darker());
				}
			});
			
			EventListenerPtr mouse = Hardware::Get().getListener("Mouse");
			mouse->addCallback(MouseDoubleClickEvent::Hash, [&] (EventRef e) {
				MouseDoubleClickEvent& mdce = e.to<MouseDoubleClickEvent>();
				if(mdce.button == MouseButton::Left) {
					Example::Stop();
				}
			});
			
			EventListenerPtr windowlst = window->registerListener("MyCloseListener", { WindowClosingEvent::Hash } );
			windowlst->addCallback(WindowClosingEvent::Hash, [&] (EventRef e) {
				Main::Get().addUpdateCallback(Main::UpdateCallback::After, [] (){
					Example::Stop();
				});
			});
		}
		
		static void Update()
		{
			Main::Get().update();
		}
		
		static void Stop()
		{
			Console::Get() << "\nStopping Example !";
			Main::Get().clear();
			exit(0);
		}
	};

#endif
}

#endif
