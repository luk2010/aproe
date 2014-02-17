/////////////////////////////////////////////////////////////
/** @file PluginHandle.h
 *  @ingroup Plugin
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 17/09/2012 - 15/02/2014
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

        ResourceEntryPtr e = ResourceManager::Get().loadResourceWithLoader(mname, library_file, "DynamicLibraryLoader");
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

        documentEvent(PluginStartedEvent::Hash,  "Plugin just started.");
        documentEvent(PluginStoppedEvent::Hash,  "Plugin just stopped.");
        documentEvent(PluginStoppingEvent::Hash, "Plugin is stopping.");
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

        // We verify that library is correctly loaded.
        if(!dynLib->isLoaded())
        {
            if(!dynLib->load())
            {
                aprodebug("Can't load library '") << dynLib->getName() << "'.";
                return false;
            }
        }

        // Refresh the API version
        refreshPluginInfo();

        APRO_THREADSAFE_AUTOLOCK
        {
            // Verify API version
            if(!info)
            {
                aprodebug("Plugin version not valid ! Expected '") << PluginManager::Get().getCurrentApiversion().build << "' but got 'null'.";
                return false;
            }
            if(!PluginManager::Get().isVersionValid(info->apiversion))
            {
                aprodebug("Plugin version not valid ! Expected '") << PluginManager::Get().getCurrentApiversion().build << "' but got '" << info->apiversion.build << "'.";
                return false;
            }

            // Get Start function if version is ok.
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
    }

    bool PluginHandle::end(bool unload_library)
    {
        if(dynLib.isNull())
            return false;

        // If not started, we return true but terminated flag is not set to true.
        if(!isStarted())
            return true;

        APRO_THREADSAFE_AUTOLOCK
        {
            // Getting EndPlugin function.
            DLL_END_PLUGIN endPluginFunc = (DLL_END_PLUGIN) dynLib->getSymbol(String("EndPlugin"));
            if(!endPluginFunc)
            {
                aprodebug("Couldn't find function 'EndPlugin' in library '") << dynLib->getName() << "'.";
                return false;
            }
            else
            {
                // As some developpers may want to know when a plugin
                // will be stopped and others will want to know when a
                // plugin is already stopped, we send event at both cases.

                aprodebug("Stopping plugin '") << name << "'...";

                sendEvent(createEvent(PluginStoppingEvent::Hash));
                endPluginFunc();

                info       = nullptr;
                started    = false;
                terminated = true;

                if(unload_library)
                    dynLib->unload();

                sendEvent(createEvent(PluginStoppedEvent::Hash));
                return true;
            }
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
        APRO_THREADSAFE_AUTOLOCK
        return started;
    }

    bool PluginHandle::isTerminated() const
    {
        APRO_THREADSAFE_AUTOLOCK
        return terminated;
    }

    PluginInfo* PluginHandle::getPluginInfo() const
    {
        APRO_THREADSAFE_AUTOLOCK
        return info;
    }

    void PluginHandle::refreshPluginInfo()
    {
        if(dynLib.isNull() || !dynLib->isLoaded())
        {
            APRO_THREADSAFE_AUTOLOCK
            info = nullptr;
        }
        else
        {
            DLL_GET_PLUGININFO infofunc = (DLL_GET_PLUGININFO) dynLib->getSymbol(String("GetPluginInfo"));
            if(infofunc)
            {
                APRO_THREADSAFE_AUTOLOCK
                info = (PluginInfo*) infofunc();
            }
            else
            {
                aprodebug("Can't retrieve information of library '") << dynLib->getName() << "'.";

                APRO_THREADSAFE_AUTOLOCK
                info = nullptr;
            }
        }
    }

    DynamicLibraryPtr PluginHandle::toDynamicLibrary()
    {
        return dynLib;
    }

    EventPtr PluginHandle::createEvent(const HashType& e_type) const
    {
        switch (e_type)
        {
        case PluginStartedEvent::Hash:
            EventPtr ret = (Event*) AProNew(PluginStartedEvent);
            ret->m_emitter = this;
            return ret;

        case PluginStoppingEvent::Hash:
            EventPtr ret = (Event*) AProNew(PluginStoppingEvent);
            ret->m_emitter = this;
            return ret;

        case PluginStoppedEvent::Hash:
            EventPtr ret = (Event*) AProNew(PluginStoppedEvent);
            ret->m_emitter = this;
            return ret;

        default:
            return EventEmitter::createEvent(e_type);
        }
    }
}
