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

#include "Manager.h"
#include "PluginHandle.h"

#define APRO_CURRENT_PLUGIN_MAJOR 1
#define APRO_CURRENt_PLUGIN_MINOR 0
#define APRO_CURRENT_PLUGIN_BUILD 1

namespace APro
{
    class APRO_DLL PluginManager : public Manager<PluginHandle>
    {
    public:

        PluginManager();
        ~PluginManager();

    private:

        List<SharedPointer<PluginHandle> >& pluginList;

    public:

        SharedPointer<PluginHandle> getPluginHandle(const String& name);
        SharedPointer<PluginHandle> addPluginHandle(const String& name, const String& filename);
        SharedPointer<PluginHandle> addPluginHandle(const String& name, const SharedPointer<DynamicLibrary>& lib = SharedPointer<DynamicLibrary>());
        int                         loadDirectory  (const String& path);
        void removePluginHandle(const String& name);

        PluginInfo* getPluginInfo(const String& pluginhandle);
        const PluginApiVersion getCurrentApiversion() const;
        
        bool hasValidApiVersion(const PluginHandle::ptr& plugin) const;
        bool isOutdated(const PluginHandle::ptr& plugin) const;

    };
}

#endif
