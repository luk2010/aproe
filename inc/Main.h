/** @file Main.h
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 20/09/2012
 *
 *  @addtogroup Global
 *  @addtogroup System
 *
 *  This file defines the Main class.
 *
**/
#ifndef APROMAIN_H
#define APROMAIN_H

#include "Platform.h"
#include "Singleton.h"
#include "Context.h"
#include "ResourceManager.h"
#include "WindowManager.h"
#include "PluginManager.h"
#include "Console.h"

namespace APro
{
    class APRO_DLL Main : public Singleton<Main>
    {
        APRO_DECLARE_SINGLETON(Main)

    protected:

        Main()
        {

        }

        ~Main()
        {

        }

    public:

        void clear()
        {
            pluginManager.clear();
            contextFactoryManager.clear();
            resourceManager.clear();
            windowManager.clear();
        }

        ContextFactoryManager& getContextFactoryManager()
        {
            return contextFactoryManager;
        }

        Console& getConsole()
        {
            return Console::get();
        }

        WindowManager& getWindowManager()
        {
            return windowManager;
        }

        ResourceManager& getResourceManager()
        {
            return resourceManager;
        }

        PluginManager& getPluginManager()
        {
            return pluginManager;
        }

    private:

        ContextFactoryManager contextFactoryManager;
        PluginManager pluginManager;
        ResourceManager resourceManager;
        WindowManager windowManager;
    };
}

#endif
