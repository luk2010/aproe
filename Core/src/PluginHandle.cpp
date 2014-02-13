/////////////////////////////////////////////////////////////
/** @file PluginHandle.h
 *  @ingroup Plugin
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 17/09/2012 - 13/02/2014
 *
 *  Implements the PluginHandle class.
 *
**/
/////////////////////////////////////////////////////////////
#include "PluginHandle.h"
#include "Console.h"

namespace APro
{
    typedef void  (*DLL_START_PLUGIN)  (void);
    typedef void  (*DLL_END_PLUGIN)    (void);
    typedef void* (*DLL_GET_PLUGININFO)(void);

    APRO_REGISTER_EVENT_NOCONTENT(PluginStartedEvent);
    APRO_REGISTER_EVENT_NOCONTENT(PluginStoppingEvent);
    APRO_REGISTER_EVENT_NOCONTENT(PluginStoppedEvent);

    PluginHandle::PluginHandle(const String& mname, const String& library_file)
    {
        name       = mname;
        dynLib     = nullptr;
        info       = nullptr;
        started    = false;
        terminated = false;

        ResourceEntryPtr e = ResourceManager::loadResourceWithLoader(mname, library_file, "DynamicLibraryLoader");
        if(e)
        {
            dynLib = e->getResource<DynamicLibraryPtr>();
            if(!dynLib.isNull())
            {
                dynLib->setEmitPolicy(EventEmitter::EP_NONE);
                if(!dynLib->isLoaded())
                    dynLib->load();
            }
        }
    }

    PluginHandle::PluginHandle(const String& mname, const DynamicLibraryPtr& lib)
    {
        name       = mname;
        dynLib     = lib;
        info       = nullptr;
        started    = false;
        terminated = false;

        if(!dynLib.isNull())
        {
            dynLib->setEmitPolicy(EventEmitter::EP_NONE);
            if(!dynLib->isLoaded())
                dynLib->load();
        }
    }

    PluginHandle::~PluginHandle()
    {
        // We detroy the plugin and the library file.
        end(true);
    }

    const String& PluginHandle::getName() const
    {
        return name;
    }

    bool PluginHandle::initialize()
    {
        if(dynLib.isNull())
            return false;

        APRO_THREADSAFE_AUTOLOCK

        // We verify that library is correctly loaded.
        if(!dynLib->isLoaded())
        {
            if(!dynLib->load())
            {
                aprodebug("Can't load library '") << dynLib->getName() << "'.";
                return false;
            }
        }

        DLL_START_PLUGIN startPluginFunc = (DLL_START_PLUGIN) dynLib->getSymbol(String("StartPlugin"));
        if(!startPluginFunc)
        {
            aprodebug("Couldn't find function 'StartPlugin' in library '") << dynLib->getName() << "'.";
            return false;
        }
        else
        {
            aprodebug("Starting plugin '") << name << "'...";

            startPluginFunc();
            refreshPluginInfo();

            started    = true;
            terminated = false;

            sendEvent(createEvent(PluginStartedEvent::Hash));
            return true;
        }
    }

    bool PluginHandle::end(bool unload_library)
    {
        if(dynLib.isNull())
            return false;

        if(!isStarted())
            return true;

        APRO_THREADSAFE_AUTOLOCK

        DLL_END_PLUGIN endPluginFunc = (DLL_END_PLUGIN) dynLib->getSymbol(String("EndPlugin"));
        if(!endPluginFunc)
        {
            aprodebug("Couldn't find function 'EndPlugin' in library '") << dynLib->getName() << "'.";
            return false;
        }
        else
        {
            aprodebug("Stopping plugin '") << name << "'...";

            sendEvent(createEvent(PluginStoppingEvent::Hash));
            endPluginFunc();

            info       = nullptr;
            started    = false;
            terminated = true;

            dynLib->unload();
            refreshPluginInfo();
            started = false;

            sendEvent(createEvent(PluginStoppedEvent::Hash));

            if(unload_library)
                dynLib->unload();

            return true;
        }
    }

    void PluginHandle::reload(bool reload_library)
    {
        if(isStarted())
        {
            end(reload_library);
            initialize();
        }
        else
        {
            if(reload_library && dynlib->isLoaded()) // Force library reloading.
                dynLib->unload();
            initialize();
        }
    }

    bool PluginHandle::isStarted() const
    {
        return started;
    }

    bool PluginHandle::isTerminated() const
    {
        return terminated;
    }

    PluginInfo* PluginHandle::getPluginInfo() const
    {
        return info;
    }

    void PluginHandle::refreshPluginInfo()
    {
        if(dynLib.isNull() || !dynLib->isLoaded())
        {
            info = nullptr;
        }
        else
        {
            DLL_GET_PLUGININFO infofunc = (DLL_GET_PLUGININFO) dynLib->getSymbol(String("GetPluginInfo"));
            if(infofunc)
            {
                info = (PluginInfo*) infofunc();
            }
            else
            {
                aprodebug("Can't retrieve information of library '") << dynLib->getName() << "'.";
                info = nullptr;
            }
        }
    }

    DynamicLibraryPtr PluginHandle::toDynamicLibrary()
    {
        return dynLib;
    }
}
