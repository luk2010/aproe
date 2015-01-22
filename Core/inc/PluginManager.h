/////////////////////////////////////////////////////////////
/** @file PluginManager.h
 *  @ingroup Plugin
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 18/09/2012 - 21/01/2015
 *
 *  @brief
 *  Defines the PluginManager class.
 *
 *  @copyright
 *  Atlanti's Project Engine
 *  Copyright (C) 2012 - 2015  Atlanti's Corp
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
**/
/////////////////////////////////////////////////////////////
#ifndef APROPLUGINMANAGER_H
#define APROPLUGINMANAGER_H

#include "Manager.h"
#include "Printable.h"
#include "PluginHandle.h"

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
     *  ### Example functions
     *
     *  @code
     *
     *  PluginInfo info;
     *
     *  extern "C" void* GetPluginInfo(void)
     *  { return &info; }
     *
     *  extern "C" void StartPlugin(void)
     *  {
     *    info.name = "Example";
     *    info.author = "You";
     *    info.date = "01/01/1991";
     *    info.description = "An example plugin.";
     *    info.apiversion = PluginManager::Get().getCurrentApiVersion();
     *
     *    // Do whatever you want here.
     *  }
     *
     *  extern "C" void EndPlugin(void)
     *  { }
     *
     *  @endcode
    **/
    /////////////////////////////////////////////////////////////

    /////////////////////////////////////////////////////////////
    /** @class PluginManager
     *  @ingroup Plugin
     *  @brief Manage every plugins.
     *
     *  You should use this class to load/unload plugins.
     *  At Main initialisation, the Main class load the "plugins/"
     *  directory in the current working dir, i.e. the executable
     *  one.
     *
     *  Plugins must follow the API version checking system. It is
     *  mainly based on the build field, the other one being only
     *  informative. A plugin that do not have the same API version
     *  as the bounded Engine library won't be loaded, as it would
     *  result at some errors.
     *
     *  ### Plugins Loading process
     *
     *  Loading a plugin takes place in three steps :
     *  - Loading the DynamicLibraryFile.
     *  - Getting the plugin's informations.
     *  - If version is okay, call to StartPlugin() in the plugin.
     *
     *  @note This process is done in the Pluginhandle::initialize
     *  function. The DynamicLibrary doesn't need to already be
     *  loaded but it will be loaded in the Pluginhandle::initialize
     *  function if it is not.
     *
     *  @note You can access a global instance using the Main
     *  object : @code Main::Get().getPluginManager(); @endcode
     *  This make you sure this is always the same plugin manager.
     *
     *  @note PluginManager::Get() is also available but you should
     *  verify with PluginManager::IsCreated() that the PluginManager
     *  is created.
    **/
    /////////////////////////////////////////////////////////////
    class APRO_DLL PluginManager : 
    	public BaseObject<PluginManager>,
    	public Manager<PluginHandle>,
    	public Printable
    {
        APRO_DECLARE_MANUALSINGLETON(PluginManager)

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

        List<PluginHandlePtr>& pluginList;///< List of plugins pointer.

    public:

        /////////////////////////////////////////////////////////////
        /** @brief Return the plugin designated with name.
         *
         *  If nothing correspond, it returns a null pointer.
        **/
        /////////////////////////////////////////////////////////////
        PluginHandlePtr getPluginHandle(const String& name);

        /////////////////////////////////////////////////////////////
        /** @brief Return the plugin designated with name.
         *
         *  If nothing correspond, it returns a null pointer.
        **/
        /////////////////////////////////////////////////////////////
        const PluginHandlePtr getPluginHandle(const String& name) const;

    public:

        /////////////////////////////////////////////////////////////
        /** @brief Loads a plugin from a file.
         *
         *  @param name : Name of the created plugin. If empty, name in
         *  the PLugiInfo structure will be set as PluginHandle name.
         *  @param filename : File to load.
         *  @param load_now : True if you want to initialize the plugin
         *  immediatly after its creation.
         *
         *  @return - If this name is already used, but filename is different,
         *  it returns a null pointer. If name and filename corresponds,
         *  the already loaded PluginHandle is returned.
         *          - If filename is empty, or invalid, it returns a null
         *  pointer.
        **/
        /////////////////////////////////////////////////////////////
        PluginHandlePtr addPluginHandle(const String& name, const String& filename, bool load_now = false);

        /////////////////////////////////////////////////////////////
        /** @brief Loads a plugin from an already loaded dynamic
         *  library.
         *
         *  @param name : Name of the created plugin.
         *  @param lib : Dynamic library to use.
         *  @param load_now : True if you want to initialize the plugin
         *  immediatly after its creation.
         *
         *  @return - If this name is already used, but filename is different,
         *  it returns a null pointer. If name and filename corresponds,
         *  the already loaded PluginHandle is returned.
         *          - If lib is null, a null pointer is returned.
        **/
        /////////////////////////////////////////////////////////////
        PluginHandlePtr addPluginHandle(const String& name, const DynamicLibraryPtr& lib, bool load_now = false);

        /////////////////////////////////////////////////////////////
        /** @brief Load every plugins in given directory.
         *
         *  Names of plugins will be the name provided in the PluginInfo
         *  structure. Refers to the Plugin's Provider for name given,
         *  or list them using the Console.
         *  @note Plugins are loaded and initialized, equivalent to set
         *  the load_now property of addPluginHandle() to true.
         *
         *  @return Number of plugins loaded.
        **/
        /////////////////////////////////////////////////////////////
        int loadDirectory(const String& path);

    public:

        /////////////////////////////////////////////////////////////
        /** @brief Removes given plugin and unload it.
         *
         *  @param name : Name of plugin to remove.
         *  @return Results of PluginHandle::end() or false if name is
         *  invalid.
        **/
        /////////////////////////////////////////////////////////////
        bool removePluginHandle(const String& name);

    public:


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
        const PluginApiVersion getCurrentApiVersion() const;

        /////////////////////////////////////////////////////////////
        /** @brief Tell if given plugin has a valid api version.
         *
         *  An api version is valid if build version is tthe same as
         *  current build version.
        **/
        /////////////////////////////////////////////////////////////
        bool isVersionValid(const PluginApiVersion& version) const;

        /////////////////////////////////////////////////////////////
        /** @brief Tell if given plugin is outdated.
         *  @return The opposite of isVersionValid().
        **/
        /////////////////////////////////////////////////////////////
        bool isOutdated(const PluginApiVersion& version) const;

    public:

        /////////////////////////////////////////////////////////////
        /** @brief Print information about this object in the console.
        **/
        /////////////////////////////////////////////////////////////
        void print(Console& console) const;

    };
}

#endif
