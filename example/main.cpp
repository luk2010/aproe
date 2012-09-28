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
#include "NullLoader.h"
#include "FileLoader.h"
#include "File.h"
#include "NullWriter.h"
#include "FileWriter.h"
#include "Pair.h"
#include "Keyboard.h"
#include "Dialog.h"
#include "DynamicLibraryLoader.h"
#include "Image.h"
#include "Main.h"

int main()
{
    try
    {
        APro::MemoryTracker::get()->setCutFilename(true);
        APro::MemoryTracker::get()->setMaxFilenameSize(30);
        APro::MemoryTracker::get()->setRetain(false);

        APro::Console& console = APro::Main::get().getConsole();

        console.foregroundColor(APro::Console::Color::Green)
                            << "Hello World ! We will test the Memory module. \n";
        console.foregroundColor(APro::Console::Color::Yellow)
                            << "============================================= \n\n";
        console.reset();

        char* buffer = APro::Allocator<char>::allocateArray(7);
        buffer[0] = 'T';
        buffer[1] = 'U';
        buffer[2] = 'R';
        buffer[3] = 'T';
        buffer[4] = 'L';
        buffer[5] = 'E';
        buffer[6] = '\0';

        console << buffer;
        APro::Allocator<char>::deallocatePtr(buffer);

        console << "\n\nTesting Exceptions...\n----------\n\n";

        APRO_THROW("MyType", "This is a fake !", "none");
    }
    catch(APro::Exception const& e)
    {
        APro::Console& console = APro::Main::get().getConsole();
        console << "An exception has been launched : " << e.getFullDescription().c_str() << "\n";

        try
        {
            console << "\n\nTesting arrays...\n----------\n\n";

            APro::Array<char> myArray;
            myArray.append('A');
            myArray.append('B');
            myArray.insert(1, 'C', 3);
            myArray.prepend('D');
            myArray.erase(4);

            myArray << 'B' << 'C' << 'D' << 'E';

            console << myArray[0] << myArray[1] << myArray[2] << myArray[3] << myArray[4] << "\n";
            console << "Current Allocations : " << (int) APro::MemoryTracker::get()->getCurrentBytesAllocated() << "bytes.\n";

            console << "\n\nTesting Strings...\n----------\n\n";
            APro::String str;
            str << "Ceci est une string !";

            str.prepend(APro::String("Bijour ! "));
            str.erase(3, 4);
            str.insert(3, " blabla ", 2);

            console << str.toCstChar();

            console.foregroundColor(APro::Console::Color::Green)
                                .backgroundColor(APro::Console::Color::Yellow)
                                << "\nBijour !!";

            console.reset()
                                << "\n\nTesting Console Screen...\n----------\n\n"
                                << "The screen will diseappar for 5 seconds so don't exit app !";

            //Sleep(2000);

            console.reset().hide();

            //Sleep(5000);

            console.show();

            console << "\n\nTesting lists...\n----------\n\n";

            APro::List<int> l;
            l << 4 << 5 << 7 << 9;

            console << l.at(1);

            console << "\n\nTesting SharedPointer...\n----------\n\n";

            APro::SharedPointer<APro::String> myStrPtr(AProNew(1, APro::String)(APro::String("blabla")));
            console << myStrPtr->toCstChar();
            APro::SharedPointer<APro::String> ptr2 = myStrPtr;
            console << "\n" << ptr2->toCstChar();

            console << "\n\nTesting Map...\n----------\n\n";

            APro::Map<APro::String, APro::String> frToUk;
            frToUk.push(APro::String("Bonjour"), APro::String("Hello"));
            frToUk.push(APro::String("Au Revoir"), APro::String("GoodBye"));
            console << frToUk[APro::String("Bonjour")].toCstChar();

            console << "\n\nTesting Variant...\n----------\n\n";

            APro::Variant myVariant(APro::String("Ceci vient du variant !"));
            console << myVariant.to<APro::String>();

            APro::Variant myVariant2 = myVariant;
            myVariant2.to<APro::String>().erase(2,4);
            console << "\n" << myVariant2.to<APro::String>();

            APro::Variant myVariant3;
            myVariant3 = APro::String("ABCDEF");
            console << "\n" << myVariant3.to<APro::String>();

            console << "\n\nTesting ResourceLoader and ResourceManager...\n----------\n";

            APro::ResourceManager& rmanager = APro::Main::get().getResourceManager();

            rmanager.addLoader(APro::SharedPointer<APro::ResourceLoader>(AProNew(1, APro::NullLoader)));
            rmanager.addLoader(APro::SharedPointer<APro::ResourceLoader>(AProNew(1, APro::FileLoader)));
            rmanager.addLoader(APro::SharedPointer<APro::ResourceLoader>(AProNew(1, APro::DynamicLibraryLoader)));

            rmanager.addWriter(APro::SharedPointer<APro::ResourceWriter>(AProNew(1, APro::FileWriter)));

            APro::SharedPointer<APro::Resource> myResource = rmanager.loadResourceWithLoader(APro::String("MyResource"),
                                                                                             APro::String("leaks.log"),
                                                                                             APro::String("NullLoader"));

            APro::SharedPointer<APro::Resource> myResource2 = rmanager.getResource(APro::String("MyResource"));

            console << "\n" << myResource->getName();
            console << "\n" << myResource2->getName();

            myResource.release();
            myResource2.release();
            rmanager.unloadResource(APro::String("MyResource"));

            console << "\n\n" << rmanager.listLoaders();
            console << "\n\n" << rmanager.listResources() << "\n\n";

            console << "\n\nTesting File... \n----------\n";

            APro::SharedPointer<APro::File> myFile = rmanager.loadResourceWithLoader<APro::File>(APro::String("TestFile"),
                                                                                                 APro::String("test.txt"),
                                                                                                 APro::String("FileLoader"));
            myFile->seek(-4, APro::File::Position::End);
            myFile->put(APro::String(" blabla "));
            console << "\n" << myFile->toString();

            APro::NullWriter writer;
            console << "\n" << writer.name() << " : " << writer.listParameters();

            rmanager.write(APro::String("TestFile"), APro::String("FileWriter"), APro::String("file.txt"));
            console << "\n" << rmanager.listWriters();

            console << "\n\nTesting Window... \n----------\n";

            APro::WindowManager& wmanager = APro::Main::get().getWindowManager();
            APro::SharedPointer<APro::Window> window;

            if(APro::Dialog::ask(APro::String("Fullscreen choice"),
                                 APro::String("Do you want to turn fullscreen mode on ?")) == APro::Dialog::Answer::Yes)
            {
                window = wmanager.create(APro::String("MyWindow"), APro::String("First Window"),
                                                      APro::String("1280x768"), true);
            }
            else
            {
                window = wmanager.create(APro::String("MyWindow"), APro::String("First Window"),
                                                      APro::String("1280x768"), false);
            }

            if(!window.isNull())
            {
                window->show();
                window->move(50, 50, true);
                window->resize(1024, 768);

                console << "\n" << (int) window->position().first() << " : " << (int) window->position().second();
                console << "\n" << (int) window->size().first() << "x" << (int) window->size().second();

                APro::SharedPointer<APro::EventListener> eListener = window->addListener(APro::String("MyWindowListener"));

                console << "\n\n" << window->listParameters();

                APro::SharedPointer<APro::EventListener> keyListener = window->getKeyboard()->addListener(APro::String("MyKeyListener"));
                keyListener->getParam(APro::String("KeyInfos")).to<APro::Keyboard::KeyBoardListenerInfo>().keyInfos[APro::KEY_A].repeat = true;

                window->getKeyboard()->registerKey(APro::KEY_ESC);
                window->getKeyboard()->registerKey(APro::KEY_A);
                window->getKeyboard()->registerKey(APro::KEY_B);

                while(window->status() != APro::Window::Status::Null)
                {
                    wmanager.loop();

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

                        console << "\nWindow Moved ! New Position : " << (int) newPosition.first() << " : "
                                                                             << (int) newPosition.second();
                    }

                    e = eListener->received(APro::String("WindowResizedEvent"));

                    if(!e.isNull())
                    {
                        APro::Pair<size_t, size_t> newSize = e->getParam(APro::String("Size")).to<APro::Pair<size_t, size_t> >();

                        console << "\nWindow Resized ! New Size : " << (int) newSize.first() << " : "
                                                                             << (int) newSize.second();
                    }

                    e = eListener->received(APro::String("WindowClosingEvent"));

                    if(!e.isNull())
                    {
                        console << "\nWindow closed !";
                    }

                    e = eListener->received(APro::String("WindowMinimizedEvent"));

                    if(!e.isNull())
                    {
                        console << "\nWindow Minimized !";
                    }

                    eListener->purge();

                    e = keyListener->received(APro::String("KeyPressedEvent"));
                    if(!e.isNull())
                    {
                        console << "\n" << APro::keyToString(e->getParam(APro::String("Key")).to<APro::KEY>()) << " pressed !";
                        if(e->getParam(APro::String("Key")).to<APro::KEY>() == APro::KEY_ESC && window->isFullScreen())
                        {
                            window->fullscreen(false);
                        }
                    }

                    e = keyListener->received(APro::String("KeyReleasedEvent"));
                    if(!e.isNull())
                    {
                        console << "\n" << APro::keyToString(e->getParam(APro::String("Key")).to<APro::KEY>()) << " released ! " << (int) e.getUses();
                    }

                    keyListener->purge();
                }
            }

            console << "\n\nTesting DynamicLibrary... \n----------\n";

            APro::PluginManager& pmmanager = APro::Main::get().getPluginManager();

            APro::SharedPointer<APro::PluginHandle> plugin = pmmanager.addPluginHandle(APro::String("MyPlugin"),
                                                                                       APro::String("ExamplePlugin.dll"));

            if(!plugin.isNull())
            {
                APro::PluginInfo* info = plugin->getPluginInfo();
                console << "\nName of the plugin is : " << info->name.toCstChar();
                console << "\nDescription is : " << info->description;

                console << "\n" << rmanager.listResources();
            }

            APro::SharedPointer<APro::PluginHandle> devilLoader = pmmanager.addPluginHandle(APro::String("DevILLoaderPlugin"),
                                                                                            APro::String("DevIlLoader.dll"));

            APro::SharedPointer<APro::Image> myImg = rmanager.loadResourceWithLoader<APro::Image>(APro::String("MyImage"),
                                                                                                  APro::String("Screenshot.jpg"),
                                                                                                  APro::String("DevILLoader"));

            console << "\nWidth : " << (int) myImg->width() << ", Height : " << (int) myImg->height() << ".";
            console << "\n" << myImg->get(400, 200);

            rmanager.write(APro::String("MyImage"), APro::String("DevILWriter"), APro::String("myimage.jpg"));

        }
        catch(std::exception const& e2)
        {
            console << "An std exception has been launched : " << e2.what() << "\n";
        }
        catch(APro::Exception const& e2)
        {
            console << "An exception has been launched : " << e2.getFullDescription().c_str() << "\n";
        }
    }

    std::cout << "\nVeuillez appuyer sur entree pour terminer le programme...";
    std::cin.get();

    APro::Main::get().clear();

    APro::Console::get().dump("Log.txt");
    APro::MemoryTracker::get()->dump("Leaks.log");

    std::cout << "\nLeaving. Appuyez sur une touche pour terminer le programme." << APro::EventCounter::get().count;

    std::cin.get();

    return 0;
}
