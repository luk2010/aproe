/////////////////////////////////////////////////////////////
/** @file PluginManager.h
 *  @ingroup Plugin
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 18/09/2012
 *
 *  Defines the PluginManager class.
 *
**/
/////////////////////////////////////////////////////////////
#ifndef APROPLUGINMANAGER_H
#define APROPLUGINMANAGER_H

#include "Manager.h"
#include "PluginHandle.h"

#define APRO_CURRENT_PLUGIN_MAJOR 1
#define APRO_CURRENt_PLUGIN_MINOR 0
#define APRO_CURRENT_PLUGIN_BUILD 1

namespace APro
{
    /////////////////////////////////////////////////////////////
    /** @defgroup Plugin Plugins System
     *  @brief A plugin system based on dynamic library loading.
     *
     *  The Atlanti's Project Engine Plugin System is, basically,
     *  a dynamic library loading at runtime. The library loaded
     *  is initialized with a generic function (StartPlugin), and
     *  is destroyed with the function EndPlugin, present in the 
     *  library. 
     *
     *  The library can also give the GetPluginInfo function to give
     *  the engine a way to have informations about the plugin.
     *
     *  When you create a cool new plugin for the engine, to add
     *  something, you will first create this three functions, with
     *  the PluginInfo structure in a global variable at the 
     *  beginning of your program. Then, consider the StartPlugin
     *  function at the begin of the old-style main function, and
     *  EndPlugin where you will destroy everything allocated in
     *  StartPlugin. 
     *
     *  Because of the allocation system, you must deallocate yourself
     *  what you allocated in the plugin (using the AProNew / AProDelete
     *  system).
    **/
    /////////////////////////////////////////////////////////////
    
    /////////////////////////////////////////////////////////////
    /** @class PluginManager
     *  @ingroup Plugin
     *  @brief Manage every plugins.
     *  @details You should use this class to load/unload plugins.
     *  At initialisation, the Main class load the "plugins/"
     *  directory in the current working dir, i.e. the executable
     *  one. 
     *
     *  Plugins are loaded without API version checking, but you 
     *  should verify it yourself at end of loading. Notice that 
     *  plugins using older version of API than this one are 
     *  marked as outdated, but you still can use it.
     *
     *  @note You can access a global instance using the Main 
     *  object : @code Main::get().getPluginManager(); @endcode
     *  This make you sure this is always the same plugin manager.
    **/
    /////////////////////////////////////////////////////////////
    class APRO_DLL PluginManager : public Manager<PluginHandle>
    {
    public:

        /////////////////////////////////////////////////////////////
        /** @brief Constructor.
        **/
        /////////////////////////////////////////////////////////////
        PluginManager();
        
        /////////////////////////////////////////////////////////////
        /** @brief Destructor.
        **/
        /////////////////////////////////////////////////////////////
        ~PluginManager();

    private:

        List<SharedPointer<PluginHandle> >& pluginList;///< List of plugins pointer.

    public:
        
        /////////////////////////////////////////////////////////////
        /** @brief Return the plugin designated with name. 
         *  
         *  If nothing correspond, it returns a null pointer.
        **/
        /////////////////////////////////////////////////////////////
        SharedPointer<PluginHandle> getPluginHandle(const String& name);
        
        /////////////////////////////////////////////////////////////
        /** @brief Load a plugin from a file.
         *
         *  @param name : Name of the created plugin.
         *  @param filename : File to load.
         *
         *  @return A pointer to the handle to the plugin. 
         *
         *  If name is already used, plugin is not loaded and 
         *  existing one is returned.
         *  If filename doesn't exist, a null pointer is returned.
        **/
        /////////////////////////////////////////////////////////////
        SharedPointer<PluginHandle> addPluginHandle(const String& name, const String& filename);
        
        /////////////////////////////////////////////////////////////
        /** @brief Load a plugin from an already loaded dynamic
         *  library.
         *
         *  @param name : Name of the created plugin. 
         *  @param lib : Dynamic library to use.
         *
         *  @return A pointer to the handle to the plugin.
         *
         *  If name already exists, plugin is not loaded and existing
         *  one is returned. 
         *  If lib is null or unloaded, null pointer is returned.
         *
         *  @note You must load the library before passing it to this
         *  function !
        **/
        /////////////////////////////////////////////////////////////
        SharedPointer<PluginHandle> addPluginHandle(const String& name, const SharedPointer<DynamicLibrary>& lib = SharedPointer<DynamicLibrary>());
        
        /////////////////////////////////////////////////////////////
        /** @brief Load every plugins in given directory.
         *  
         *  @param path : relative path to directory to load. 
         *  @return Number of plugins loaded successfully. 
         *
         *  Iterating in the directory is made by using unistd and
         *  dirent functions and structures, so this function is only
         *  available in platforms supporting these functions.
        **/
        /////////////////////////////////////////////////////////////
        int loadDirectory  (const String& path);
        
        /////////////////////////////////////////////////////////////
        /** @brief Removes given plugin and unload it. 
         *  
         *  @param name : Name of plugin to remove.
         *
         *  If name doesn't correspond to a plugin, this function does
         *  nothing.
         *  At the end of the function, the plugin is always ended, even
         *  if anywhere there is a restant pointer that has not been 
         *  released. The plugin is released only when every pointers
         *  have been released, but is ended in this function.
        **/
        /////////////////////////////////////////////////////////////
        void removePluginHandle(const String& name);

        /////////////////////////////////////////////////////////////
        /** @brief Return the plugin info of given plugin name.
         * 
         *  If plugin can't be found, null is returned.
         *  This is a classic pointer, but you must not destroy or 
         *  modify it, because it directly point to an adress in the
         *  plugin. This is the plugin problem to allocate or destroy 
         *  this object.
        **/
        /////////////////////////////////////////////////////////////
        PluginInfo* getPluginInfo(const String& pluginhandle);
        
        /////////////////////////////////////////////////////////////
        /** @brief Return the current api version of this engine.
        **/
        /////////////////////////////////////////////////////////////
        const PluginApiVersion getCurrentApiversion() const;
        
        /////////////////////////////////////////////////////////////
        /** @brief Tell if given plugin has a valid api version.
         *
         *  An api version is valid if build version is < or = to 
         *  this one, OR if major and minor version are both < or =
         *  to this one. 
         *
         *  Build version and Major/Minor versions are totally 
         *  independent. 
        **/
        /////////////////////////////////////////////////////////////
        bool hasValidApiVersion(const PluginHandle::ptr& plugin) const;
        
        /////////////////////////////////////////////////////////////
        /** @brief Tell if given plugin is outdated.
         *
         *  A plugin is outdated if either major/minor is older than
         *  this one, either the build version is older.
        **/
        /////////////////////////////////////////////////////////////
        bool isOutdated(const PluginHandle::ptr& plugin) const;

    };
}

#endif
