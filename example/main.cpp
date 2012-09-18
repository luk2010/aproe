/** @file main.cpp
 *
 *  @addtogroup Memory
 *
 *  This file is an example of what you can easily do with the Memory module
 *  of Atlanti's Project Engine.
 *  It use the following modules :
 *  + Memory
 *
**/
#include <iostream>

#include "MemoryTracker.h"
#include "Memory.h"
#include "Allocator.h"
#include "Exception.h"
#include "Array.h"
#include "SString.h"
#include "Console.h"
#include "List.h"
#include "SharedPointer.h"
#include "ResourceManager.h"
#include "NullLoader.h"
#include "FileLoader.h"
#include "File.h"
#include "NullWriter.h"
#include "FileWriter.h"
#include "WindowManager.h"
#include "Pair.h"
#include "Keyboard.h"
#include "Dialog.h"
#include "PluginManager.h"
#include "DynamicLibraryLoader.h"

int main()
{
    try
    {
        APro::MemoryTracker::get()->setCutFilename(true);
        APro::MemoryTracker::get()->setMaxFilenameSize(30);
        APro::MemoryTracker::get()->setRetain(false);

        APro::Console::get().foregroundColor(APro::Console::Color::Green)
                            << "Hello World ! We will test the Memory module. \n";
        APro::Console::get().foregroundColor(APro::Console::Color::Yellow)
                            << "============================================= \n\n";
        APro::Console::get().reset();

        char* buffer = APro::Allocator<char>::allocateArray(7);
        buffer[0] = 'T';
        buffer[1] = 'U';
        buffer[2] = 'R';
        buffer[3] = 'T';
        buffer[4] = 'L';
        buffer[5] = 'E';
        buffer[6] = '\0';

        APro::Console::get() << buffer;
        APro::Allocator<char>::deallocatePtr(buffer);

        APro::Console::get() << "\n\nTesting Exceptions...\n----------\n\n";

        APRO_THROW("MyType", "This is a fake !", "none");
    }
    catch(APro::Exception const& e)
    {
        APro::Console::get() << "An exception has been launched : " << e.getFullDescription().c_str() << "\n";

        try
        {
            APro::Console::get() << "\n\nTesting arrays...\n----------\n\n";

            APro::Array<char> myArray;
            myArray.append('A');
            myArray.append('B');
            myArray.insert(1, 'C', 3);
            myArray.prepend('D');
            myArray.erase(4);

            myArray << 'B' << 'C' << 'D' << 'E';

            APro::Console::get() << myArray[0] << myArray[1] << myArray[2] << myArray[3] << myArray[4] << "\n";
            APro::Console::get() << "Current Allocations : " << (int) APro::MemoryTracker::get()->getCurrentBytesAllocated() << "bytes.\n";

            APro::Console::get() << "\n\nTesting Strings...\n----------\n\n";
            APro::String str;
            str << "Ceci est une string !";

            str.prepend(APro::String("Bijour ! "));
            str.erase(3, 4);
            str.insert(3, " blabla ", 2);

            APro::Console::get() << str.toCstChar();

            APro::Console::get().foregroundColor(APro::Console::Color::Green)
                                .backgroundColor(APro::Console::Color::Yellow)
                                << "\nBijour !!";

            APro::Console::get().reset()
                                << "\n\nTesting Console Screen...\n----------\n\n"
                                << "The screen will diseappar for 5 seconds so don't exit app !";

            //Sleep(2000);

            APro::Console::get().reset().hide();

            //Sleep(5000);

            APro::Console::get().show();

            APro::Console::get() << "\n\nTesting lists...\n----------\n\n";

            APro::List<int> l;
            l << 4 << 5 << 7 << 9;

            APro::Console::get() << l.at(1);

            APro::Console::get() << "\n\nTesting SharedPointer...\n----------\n\n";

            APro::SharedPointer<APro::String> myStrPtr(AProNew(1, APro::String)(APro::String("blabla")));
            APro::Console::get() << myStrPtr->toCstChar();
            APro::SharedPointer<APro::String> ptr2 = myStrPtr;
            APro::Console::get() << "\n" << ptr2->toCstChar();

            APro::Console::get() << "\n\nTesting Map...\n----------\n\n";

            APro::Map<APro::String, APro::String> frToUk;
            frToUk.push(APro::String("Bonjour"), APro::String("Hello"));
            frToUk.push(APro::String("Au Revoir"), APro::String("GoodBye"));
            APro::Console::get() << frToUk[APro::String("Bonjour")].toCstChar();

            APro::Console::get() << "\n\nTesting Variant...\n----------\n\n";

            APro::Variant myVariant(APro::String("Ceci vient du variant !"));
            APro::Console::get() << myVariant.to<APro::String>();

            APro::Variant myVariant2 = myVariant;
            myVariant2.to<APro::String>().erase(2,4);
            APro::Console::get() << "\n" << myVariant2.to<APro::String>();

            APro::Variant myVariant3;
            myVariant3 = APro::String("ABCDEF");
            APro::Console::get() << "\n" << myVariant3.to<APro::String>();

            APro::Console::get() << "\n\nTesting ResourceLoader and ResourceManager...\n----------\n";

            APro::ResourceManager::get().addLoader(APro::SharedPointer<APro::ResourceLoader>(AProNew(1, APro::NullLoader)));
            APro::ResourceManager::get().addLoader(APro::SharedPointer<APro::ResourceLoader>(AProNew(1, APro::FileLoader)));
            APro::ResourceManager::get().addLoader(APro::SharedPointer<APro::ResourceLoader>(AProNew(1, APro::DynamicLibraryLoader)));

            APro::ResourceManager::get().addWriter(APro::SharedPointer<APro::ResourceWriter>(AProNew(1, APro::FileWriter)));

            APro::SharedPointer<APro::Resource> myResource = APro::ResourceManager::get().loadResourceWithLoader(APro::String("MyResource"),
                                                                                                                 APro::String("leaks.log"),
                                                                                                                 APro::String("NullLoader"));

            APro::SharedPointer<APro::Resource> myResource2 = APro::ResourceManager::get().getResource(APro::String("MyResource"));

            APro::Console::get() << "\n" << myResource->getName();
            APro::Console::get() << "\n" << myResource2->getName();

            myResource.release();
            myResource2.release();
            APro::ResourceManager::get().unloadResource(APro::String("MyResource"));

            APro::Console::get() << "\n\n" << APro::ResourceManager::get().listLoaders();
            APro::Console::get() << "\n\n" << APro::ResourceManager::get().listResources() << "\n\n";

            APro::Console::get() << "\n\nTesting File... \n----------\n";

            APro::SharedPointer<APro::File> myFile = APro::ResourceManager::get().loadResourceWithLoader<APro::File>(APro::String("TestFile"),
                                                                                                                     APro::String("test.txt"),
                                                                                                                     APro::String("FileLoader"));
            myFile->seek(-4, APro::File::Position::End);
            myFile->put(APro::String(" blabla "));
            APro::Console::get() << "\n" << myFile->toString();

            APro::NullWriter writer;
            APro::Console::get() << "\n" << writer.name() << " : " << writer.listParameters();

            APro::ResourceManager::get().write(APro::String("TestFile"), APro::String("FileWriter"), APro::String("file.txt"));
            APro::Console::get() << "\n" << APro::ResourceManager::get().listWriters();

            APro::Console::get() << "\n\nTesting Window... \n----------\n";

            APro::SharedPointer<APro::Window> window;

            if(APro::Dialog::ask(APro::String("Fullscreen choice"),
                                 APro::String("Do you want to turn fullscreen mode on ?")) == APro::Dialog::Answer::Yes)
            {
                window = APro::WindowManager::get().create(APro::String("MyWindow"),
                                                           APro::String("First Window"),
                                                           APro::String("1280x768"),
                                                           true);
            }
            else
            {
                window = APro::WindowManager::get().create(APro::String("MyWindow"),
                                                           APro::String("First Window"),
                                                           APro::String("1280x768"),
                                                           false);
            }

            if(!window.isNull())
            {
                window->show();
                window->move(50, 50, true);
                window->resize(1024, 768);

                APro::Console::get() << "\n" << (int) window->position().first() << " : " << (int) window->position().second();
                APro::Console::get() << "\n" << (int) window->size().first() << "x" << (int) window->size().second();

                APro::SharedPointer<APro::EventListener> eListener = window->addListener(APro::String("MyWindowListener"));

                APro::Console::get() << "\n\n" << window->listParameters();

                APro::SharedPointer<APro::EventListener> keyListener = window->getKeyboard()->addListener(APro::String("MyKeyListener"));
                keyListener->getParam(APro::String("KeyInfos")).to<APro::Keyboard::KeyBoardListenerInfo>().keyInfos[APro::KEY_A].repeat = true;

                window->getKeyboard()->registerKey(APro::KEY_ESC);
                window->getKeyboard()->registerKey(APro::KEY_A);
                window->getKeyboard()->registerKey(APro::KEY_B);

                while(window->status() != APro::Window::Status::Null)
                {
                    APro::WindowManager::get().loop();

                    if(window->status() == APro::Window::Status::HasToBeReset)
                    {
                        window->reset();
                        window->show();
                    }

                    APro::SharedPointer<APro::Event> e;

                    e = eListener->received(APro::String("WindowMovedEvent"));

                    if(!e.isNull())
                    {
                        APro::Pair<size_t, size_t> newPosition = e->getParam(APro::String("Position")).to<APro::Pair<size_t, size_t> >();

                        APro::Console::get() << "\nWindow Moved ! New Position : " << (int) newPosition.first() << " : "
                                                                             << (int) newPosition.second();
                    }

                    e = eListener->received(APro::String("WindowResizedEvent"));

                    if(!e.isNull())
                    {
                        APro::Pair<size_t, size_t> newSize = e->getParam(APro::String("Size")).to<APro::Pair<size_t, size_t> >();

                        APro::Console::get() << "\nWindow Resized ! New Size : " << (int) newSize.first() << " : "
                                                                             << (int) newSize.second();
                    }

                    e = eListener->received(APro::String("WindowClosingEvent"));

                    if(!e.isNull())
                    {
                        APro::Console::get() << "\nWindow closed !";
                    }

                    e = eListener->received(APro::String("WindowMinimizedEvent"));

                    if(!e.isNull())
                    {
                        APro::Console::get() << "\nWindow Minimized !";
                    }

                    eListener->purge();

                    e = keyListener->received(APro::String("KeyPressedEvent"));
                    if(!e.isNull())
                    {
                        APro::Console::get() << "\n" << APro::keyToString(e->getParam(APro::String("Key")).to<APro::KEY>()) << " pressed !";
                        if(e->getParam(APro::String("Key")).to<APro::KEY>() == APro::KEY_ESC && window->isFullScreen())
                        {
                            window->fullscreen(false);
                        }
                    }

                    e = keyListener->received(APro::String("KeyReleasedEvent"));
                    if(!e.isNull())
                    {
                        APro::Console::get() << "\n" << APro::keyToString(e->getParam(APro::String("Key")).to<APro::KEY>()) << " released ! " << (int) e.getUses();
                    }

                    keyListener->purge();
                }
            }

            APro::Console::get() << "\n\nTesting DynamicLibrary... \n----------\n";

            APro::SharedPointer<APro::PluginHandle> plugin = APro::PluginManager::get().addPluginHandle(APro::String("MyPlugin"),
                                                                                                        APro::String("ExamplePlugin.dll"));

            if(!plugin.isNull())
            {
                APro::PluginInfo* info = plugin->getPluginInfo();
                APro::Console::get() << "\nName of the plugin is : " << info->name.toCstChar();
                APro::Console::get() << "\nDescription is : " << info->description;

                APro::Console::get() << "\n" << APro::ResourceManager::get().listResources();
            }

        }
        catch(std::exception const& e2)
        {
            APro::Console::get() << "An std exception has been launched : " << e2.what() << "\n";
        }
        catch(APro::Exception const& e2)
        {
            APro::Console::get() << "An exception has been launched : " << e2.getFullDescription().c_str() << "\n";
        }
    }

    std::cout << "\nVeuillez appuyer sur entree pour terminer le programme...";
    std::cin.get();

    APro::PluginManager::get().clear();
    APro::ResourceManager::get().clear();
    APro::WindowManager::get().clear();

    APro::Console::get().dump("Log.txt");
    APro::MemoryTracker::get()->dump("Leaks.log");

    std::cout << "\nLeaving. Appuyez sur une touche pour terminer le programme." << APro::EventCounter::get().count;

    std::cin.get();

    return 0;
}
