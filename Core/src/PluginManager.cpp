/////////////////////////////////////////////////////////////
/** @file PluginManager.cpp
 *  @ingroup Plugin
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 18/09/2012 - 17/02/2014
 *
 *  Implements the PluginManager class.
 *
**/
/////////////////////////////////////////////////////////////
#include "PluginManager.h"
#include "FileSystem.h"
#include "Console.h"

namespace APro
{
    APRO_IMPLEMENT_MANUALSINGLETON(PluginManager)

    PluginManager::PluginManager()
        : pluginList(Manager<PluginHandle>::objects)
    {

    }

    PluginManager::~PluginManager()
    {
        // The Manager destructor destroys automatycly every objects,
        // and PluginHandle destructor already call end().
    }

    PluginHandlePtr PluginManager::getPluginHandle(const String& name)
    {
        APRO_THREADSAFE_AUTOLOCK

        List<PluginHandlePtr>::const_iterator e = pluginList.end();
        for(List<PluginHandlePtr>::iterator it = pluginList.begin(); it != e; it++)
        {
            if((*it)->getName() == name)
                return (*it);
        }

        return PluginHandlePtr;
    }

    const PluginHandlePtr PluginManager::getPluginHandle(const String& name) const
    {
        APRO_THREADSAFE_AUTOLOCK

        List<PluginHandlePtr>::const_iterator e = pluginList.end();
        for(List<PluginHandlePtr>::const_iterator it = pluginList.begin(); it != e; it++)
        {
            if((*it)->getName() == name)
                return (*it);
        }

        return PluginHandlePtr;
    }

    PluginHandlePtr PluginManager::addPluginHandle(const String& name, const String& filename, bool load_now)
    {
        if(name.isEmpty())
            return nullptr;

        PluginHandlePtr ph = getPluginHandle(name);
        if(!ph.isNull())
        {
            if(!ph->toDynamicLibrary().isNull())
            {
                if(ph->toDynamicLibrary()->getFilename() == filename)
                {
                    return ph;
                }
                else
                {
                    return nullptr;
                }
            }
            else
            {
                return nullptr;
            }
        }

        APRO_THREADSAFE_AUTOLOCK

        ph = AProNew(PluginHandle, name, filename);
        if(!ph.isNull())
        {
            if(name.isEmpty())
            {
                // If Plugin is correctly loaded, we try to see if Library is loaded
                // to load PluginInfo structure into our memory.
                DynamicLibraryPtr dlp = ph->toDynamicLibrary();
                if(!dlp.isNull())
                {
                    if(!dlp->isLoaded())
                    {
                        if(!dlp->load())
                        {
                            aprodebug("DynamicLibrary '") << dlp->getFilename() << "' can't be loaded.";
                            return nullptr;
                        }
                    }

                    // Getting info struct.
                    ph->refreshPluginInfo();
                    PluginInfo* info = ph->getPluginInfo();
                    if(info)
                    {
                        // We set plugin name to info name.
                        ph->name = info->name;
                    }
                    else
                    {
                        // We can't set a correct name so destroy the plugin and return null.
                        aprodebug("Can't find any PluginInfo structure for plugin from file '") << dlp->getFilename() << "'.";
                        return nullptr;
                    }
                }
            }

            // Add this plugin to the manager.
            Manager<PluginHandle>::push(ph);
            aprodebug("Plugin '") << ph->name << "' successfully added.";

            if(load_now)
            {
                // Initialize the plugin correctly.
                if(!ph->initialize())
                {
                    aprodebug("Couldn't initialize plugin '") << ph->name << "' correctly. Try it again yourself or see plugin provider.";
                }
            }
        }

        // We return the pointer.
        return ph;
    }

    PluginHandlePtr PluginManager::addPluginHandle(const String& name, const DynamicLibraryPtr& lib, bool load_now)
    {
        if(name.isEmpty() || lib.isNull())
            return nullptr;

        PluginHandlePtr ph = getPluginHandle(name);
        if(!ph.isNull())
        {
            if(!ph->toDynamicLibrary().isNull())
            {
                if(ph->toDynamicLibrary()->getFilename() == lib->getFilename())
                {
                    return ph;
                }
                else
                {
                    return nullptr;
                }
            }
            else
            {
                return nullptr;
            }
        }

        APRO_THREADSAFE_AUTOLOCK

        ph = AProNew(PluginHandle, name, lib);
        if(!ph.isNull())
        {
            if(name.isEmpty())
            {
                // If Plugin is correctly loaded, we try to see if Library is loaded
                // to load PluginInfo structure into our memory.
                DynamicLibraryPtr dlp = ph->toDynamicLibrary();
                if(!dlp.isNull())
                {
                    if(!dlp->isLoaded())
                    {
                        if(!dlp->load())
                        {
                            aprodebug("DynamicLibrary '") << dlp->getFilename() << "' can't be loaded.";
                            return nullptr;
                        }
                    }

                    // Getting info struct.
                    ph->refreshPluginInfo();
                    PluginInfo* info = ph->getPluginInfo();
                    if(info)
                    {
                        // We set plugin name to info name.
                        ph->name = info->name;
                    }
                    else
                    {
                        // We can't set a correct name so destroy the plugin and return null.
                        aprodebug("Can't find any PluginInfo structure for plugin from file '") << dlp->getFilename() << "'.";
                        return nullptr;
                    }
                }
            }

            // Add this plugin to the manager.
            Manager<PluginHandle>::push(ph);
            aprodebug("Plugin '") << ph->name << "' successfully added.";

            if(load_now)
            {
                // Initialize the plugin correctly.
                if(!ph->initialize())
                {
                    aprodebug("Couldn't initialize plugin '") << ph->name << "' correctly. Try it again yourself or see plugin provider.";
                }
            }
        }

        // We return the pointer.
        return ph;
    }

    int PluginManager::loadDirectory(const String& path)
    {
        if(FileSystem::IsDirectory(path))
        {
            Directory dir(path);
            dir.skipDirectory(true);
            dir.skipDot(true);

            int files_in_dir = dir.countEntries();
            if(files_in_dir > 0)
            {
                aprodebug("Trying to load '") << files_in_dir << "' files.";

                int ret = 0;
                Directory::Entry ent;
                while(dir >> ent)
                {
                    if(!addPluginHhandle(String(), String(ent.d_name), true).isNull())
                        ret++;
                }

                aprodebug("'") << ret << "' plugins loaded.";
                return ret;
            }

            return 0;
        }
        else
        {
            aprodebug("Path '") << path << "' doesn't exists or is not a directory.";
            return 0;
        }
    }

    bool PluginManager::removePluginHandle(const String& name)
    {
        PluginHandlePtr rm = getPluginHandle(name);
        if(!rm.isNull())
        {
            APRO_THREADSAFE_AUTOLOCK

            Manager<PluginHandle>::pop(rm);

            // We call the end() function because at the end
            // of removePluginHandle(), plugin must be ended.
            // It would be done also by destructors.
            return rm->end();
        }

        return false;
    }

    PluginInfo* PluginManager::getPluginInfo(const String& pluginhandle)
    {
        PluginHandlePtr ph = getPluginHandle(pluginhandle);
        if(!ph.isNull())
        {
            return ph->getPluginInfo();
        }
        else
        {
            return nullptr;
        }
    }

    const PluginApiVersion PluginManager::getCurrentApiVersion() const
    {
        static PluginApiVersion av
        {
            APRO_CURRENT_PLUGIN_MAJOR,
            APRO_CURRENT_PLUGIN_MINOR,
            APRO_CURRENT_PLUGIN_BUILD
        };

        return av;
    }

    bool PluginManager::isVersionValid(const PluginApiVersion& version) const
    {
        return getCurrentApiversion().build == version.build;
    }

    bool PluginManager::isOutdated(const PluginApiVersion& version) const
    {
        return !isVersionValid(version);
    }

    void PluginManager::print(Console& console)
    {
        APRO_THREADSAFE_AUTOLOCK

        console << "\n[PluginManager] There are currently '" << pluginList.size() << "' plugins.";
    }
}
