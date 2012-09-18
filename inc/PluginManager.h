/** @file PluginManager.h
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
#ifndef APROPLUGINMANAGER_H
#define APROPLUGINMANAGER_H

#include "Singleton.h"
#include "PluginHandle.h"

namespace APro
{
    class APRO_DLL PluginManager : public Singleton<PluginManager>
    {
        APRO_DECLARE_SINGLETON(PluginManager)

    protected:

        PluginManager();
        ~PluginManager();

    private:

        List<SharedPointer<PluginHandle> > pluginList;

    public:

        SharedPointer<PluginHandle> getPluginHandle(const String& name);
        SharedPointer<PluginHandle> addPluginHandle(const String& name, const String& filename);
        SharedPointer<PluginHandle> addPluginHandle(const String& name, const SharedPointer<DynamicLibrary>& lib = SharedPointer<DynamicLibrary>());
        void removePluginHandle(const String& name);
        void clear();

        PluginInfo* getPluginInfo(const String& pluginhandle);

    };
}

#endif
