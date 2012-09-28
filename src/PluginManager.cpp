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
#include "Main.h"

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
}