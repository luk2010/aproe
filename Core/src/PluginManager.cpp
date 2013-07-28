/** @file PluginManager.cpp
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 18/09/2012
 *
 *  @addtogroup Global
 *  @addtogroup Plugin
 *
 *  This file defines the PluginManager class.
 *
**/
#include "PluginManager.h"
#include "ResourceManager.h"
#include "FileSystem.h"
#include "Main.h"

#include <dirent.h>
#include <unistd.h>

namespace APro
{
    //APRO_IMPLEMENT_SINGLETON(PluginManager)

    PluginManager::PluginManager()
        : pluginList(Manager<PluginHandle>::objects)
    {

    }

    PluginManager::~PluginManager()
    {

    }

    SharedPointer<PluginHandle> PluginManager::getPluginHandle(const String& name)
    {
        for(List<SharedPointer<PluginHandle> >::Iterator i(pluginList.begin()); !i.isEnd(); i++)
        {
            if(i.get()->getName() == name)
                return i.get();
        }

        return SharedPointer<PluginHandle>();
    }

    SharedPointer<PluginHandle> PluginManager::addPluginHandle(const String& name, const String& filename)
    {
        SharedPointer<PluginHandle> ret = getPluginHandle(name);
        if(ret.isNull())
        {
            SharedPointer<DynamicLibrary> lib = Main::get().getResourceManager().loadResource<DynamicLibrary>(name + String("_") + filename, filename);

            if(lib.isNull())
            {
                return SharedPointer<PluginHandle>();
            }
            else
            {
                ret = AProNew(1, PluginHandle) (name, lib);
                Manager<PluginHandle>::push(ret);
                
                if(isOutdated(ret))
                {
                    Console::get() << "\n[PluginManager]{addPluginHandle} Plugin " << name << " is outdated !";
                }
                
                return ret;
            }
        }
        else
        {
            return ret;
        }
    }

    SharedPointer<PluginHandle> PluginManager::addPluginHandle(const String& name, const SharedPointer<DynamicLibrary>& lib)
    {
        SharedPointer<PluginHandle> ret = getPluginHandle(name);
        if(ret.isNull())
        {
            if(lib.isNull())
            {
                return AProNew(1, PluginHandle) (name);
            }
            else
            {
                ret = AProNew(1, PluginHandle) (name, lib);
                Manager<PluginHandle>::push(ret);
                return ret;
            }
        }
        else
        {
            return ret;
        }
    }

    void PluginManager::removePluginHandle(const String& name)
    {
        SharedPointer<PluginHandle> rm = getPluginHandle(name);
        if(!rm.isNull())
        {
            Manager<PluginHandle>::pop(rm);
            rm.release();
        }
    }

    PluginInfo* PluginManager::getPluginInfo(const String& pluginhandle)
    {
        SharedPointer<PluginHandle> ph = getPluginHandle(pluginhandle);
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
        PluginApiVersion av;
        av.major = APRO_CURRENT_PLUGIN_MAJOR;
        av.minor = APRO_CURRENT_PLUGIN_MINOR;
        av.build = APRO_CURRENT_PLUGIN_BUILD;
        return av;
    }

    int PluginManager::loadDirectory(const String& path)
    {// Doit etre fait sans utiliser FileSystem car l'implementation n'est pas encore charge. C'est ici que sera charge par ailleurs son implementation.
        if(!path.isEmpty())
        {
            DIR* dir;
            struct dirent* dirp;

            dir = opendir(path.toCstChar());
            if(!dir)
            {
                Console::get() << "\n[PluginManager]{loadDirectory} Couldn't load directory plugin \"" << path << "\" !";
                return 0;
            }

            List<String> files;
            String filepath(FileSystem::getWorkingDirectory());
            if(path.at(0) != '/')
                filepath.append("/");
            filepath.append(path);

            while( (dirp = readdir(dir)) != NULL)
            {
                String file(dirp->d_name);
                files.append(file);
            }

            int ploaded = 0;

            if(files.size() <= 2)
            {
                Console::get() << "\n[PluginManager]{loadDirectory} No plugins in directory \"" << path << "\" !";

            }
            else
            {
                for(unsigned int i = 0; i < files.size(); ++i)
                {
                    String f = files.at(i);
                    if(f.size() <= 3) continue;

                    String f2(filepath);
                    f2.append(f);

                    PluginHandle::ptr plugin = addPluginHandle(String("testxxhash456789"), f2);
                    if(!plugin.isNull())
                    {
                        String pname = plugin->getPluginInfo()->name;
                        if(getPluginHandle(pname).isNull())
                        {
                            plugin->setName(pname); // Le plugin est valide on le fait savoir.
                            Main::get().getConsole() << "\n[PluginManager]{loadDirectory} Plugin " << pname << " charge !";
                            ++ploaded;
                        }
                        else
                        {
                            // Le plugin a deja ete charge, on detruit celui la.
                            removePluginHandle(String("testxxhash456789"));
                        }
                    }
                }
            }

            closedir(dir);
            return ploaded;
        }

        return 0;
    }
    
    bool PluginManager::hasValidApiVersion(const PluginHandle::ptr& plugin) const
    {
        bool ret = false;
        
        if(!plugin->isNull())
        {
            PluginInfo* info = plugin->getPluginInfo();
            if(info)
            {
                const PluginApiVersion current = getCurrentApiVersion();
                
                if(info->apiversion.major <= current.major && info->apiversion.minor <= current.minor)
                {
                    ret = true;
                }
                else if(info->apiversion.build <= current.build)
                {
                    ret = true;
                }
            }
        }
        
        return ret;
    }
    
    bool PluginManager::isOutdated(const PluginHandle::ptr& plugin) const
    {
        bool ret = false;
        if(!plugin.isNull())
        {
            if(hasValidApiVersion(plugin))
            {
                const PluginApiVersion current = getCurrentApiVersion();
                PluginInfo* info = plugin->getPluginInfo();
                
                if(info->apiversion.build < current.build)
                {
                    ret = true;
                }
                else if(info->apiversion.major < current.major || info->apiversion.minor < current.minor)
                {
                    ret = true;
                }
            }
        }
        
        return ret;
    }
}
