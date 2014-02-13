/////////////////////////////////////////////////////////////
/** @file PluginHandle.h
 *  @ingroup Plugin
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 17/09/2012 - 13/02/2014
 *
 *  Defines the PluginHandle class.
 *
**/
/////////////////////////////////////////////////////////////
#ifndef APROPLUGINHANDLE_H
#define APROPLUGINHANDLE_H

#include "Platform.h"
#include "DynamicLibrary.h"

#define APRO_CURRENT_PLUGIN_MAJOR 1
#define APRO_CURRENt_PLUGIN_MINOR 0
#define APRO_CURRENT_PLUGIN_BUILD 1

namespace APro
{
    /////////////////////////////////////////////////////////////
    /** @struct PluginApiVersion
     *  @ingroup Plugin
     *  @brief A PluginApi Descriptor.
    **/
    /////////////////////////////////////////////////////////////
    typedef struct PluginApiVersion
    {
        int major;
        int minor;
        int build;

    } PluginApiVersion;

    /////////////////////////////////////////////////////////////
    /** @struct PluginInfo
     *  @ingroup Plugin
     *  @brief A PluginInfo descriptor.
     *  @note You should always use PluginManager::getCurrentApiVersion
     *  to fill fields.
    **/
    /////////////////////////////////////////////////////////////
    typedef struct PluginInfo
    {
        String           name;       ///< Plugin's name.
        String           author;     ///< Plugin's author.
        String           date;       ///< Plugin's creation date.
        String           description;///< Plugin's description.
        PluginApiVersion apiversion; ///< Plugin's API description.
    } PluginInfo;

    /////////////////////////////////////////////////////////////
    /** @class PluginHandle
     *  @ingroup Plugin
     *  @brief Handle to a plugin holded in the PluginManager.
     *
     *  The PluginHandle object is the plugin's descriptor
     *  object. It holds informations and DynamicLibrary object,
     *  initialize and stop it.
     *
     *  @note Only last API plugins will be loaded by this class.
     *
     *  ### Events
     *
     *  Events send by DynamicLibrary holded by this class is,
     *  by default, disabled. Only PluginStartedEvent,
     *  PluginStoppingEvent and PluginStoppedEvent events are sended.
     *  You can send DynamicLibrary events by using
     *  PluginHandle::sendDynamicLibraryEvent(true).
     *
     *  - PluginStartedEvent : Plugin has been loaded successfully.
     *  - PluginStoppingEvent : A request to stop the plugin has been
     *  send. This event is sended before the plugin is stopped.
     *  - PluginStoppedEvent : Send when the plugin has successfully
     *  be stopped.
     *
     *  ### Loading Plugin
     *
     *  Loading a plugin is made by two steps internally :
     *  - Loading the library file using a DynamicLibrary object.
     *  - Loading the Plugin calling function StartPlugin().
     *
     *  These steps are made by the PluginHandle but can be managed
     *  by the PluginManager.
     *
     *  - You can use the PluginManager::loadPlugin() function to load
     *  a specified plugin file.
     *  - Or you can use PluginManager::addPluginHandle() function to
     *  load the library in a PluginHandle and then use
     *  PluginHandle::initialize() to initialize manually the plugin.
     *
     *  @note You should always verify the returns of these funtions.
     *
     *  ### Unloading Plugin
     *
     *  Unloading a plugin is made by two steps internally :
     *  - Unloading the Plugin by calling EndPlugin().
     *  - Unloading the library file using a DynamicLibrary object.
     *
     *  The second step can be made completly separatly from the
     *  first one.
     *
     *  Several options to unload :
     *
     *  - If you know the name of your plugin, or the filename, you
     *  can use PluginManager::unloadPlugin() from anywhere in the
     *  engine. This function can also unload the library, or can
     *  destroy the PluginHandle object only if correct options are
     *  specified.
     *  - If you have a pointer to the PluginHandle, you can use
     *  PluginHandle::end() to unload the plugin. It also can unload
     *  the library depending on boolean options.
     *
     *  @note You should always verify the returns of these funtions.
     *
    **/
    /////////////////////////////////////////////////////////////
    class APRO_DLL PluginHandle : public EventEmitter,
                                  public ThreadSafe,
                                  public NonCopyable
    {

    protected:

        String            name;       ///< Plugin's handle name.
        DynamicLibraryPtr dynLib;     ///< Pointer to the DynamicLibrary.
        PluginInfo*       info;       ///< Plugin's info pointer. @warning This adress may be invalid as it refers to an adress in the DynamicLibrary.
        bool              started;    ///< True if plugin has been started.
        bool              terminated; ///< True if plugin has been started then stopped without being restarted.

    public:

        /////////////////////////////////////////////////////////////
        /** @brief Constructs an handle with library file and name.
         *
         *  Library is created and loaded if not loaded yet using the
         *  ResourceManager.
        **/
        /////////////////////////////////////////////////////////////
        PluginHandle(const String& mname, const String& library_file);

        /////////////////////////////////////////////////////////////
        /** @brief Constructs an handle with library and name.
         *  @note If library isn't already loaded, it will be done here.
         *  Plugin is not initialized at the end of the constructor.
        **/
        /////////////////////////////////////////////////////////////
        PluginHandle(const String& mname, const DynamicLibraryPtr& lib);

        /////////////////////////////////////////////////////////////
        /** @brief Destructs the handle.
         *  @par If plugin is not terminated yet, this function terminate
         *  it and unload the library from the ResourceManager.
        **/
        /////////////////////////////////////////////////////////////
        ~PluginHandle();

    public:

        /////////////////////////////////////////////////////////////
        /** @brief Returns the handle's name.
        **/
        /////////////////////////////////////////////////////////////
        const String& getName() const;

    public:

        /////////////////////////////////////////////////////////////
        /** @brief Initialize the plugin.
         *
        **/
        /////////////////////////////////////////////////////////////
        bool initialize();

        /////////////////////////////////////////////////////////////
        /** @brief Terminate the plugin.
         *
         *  @param unload_library : If True, unload also the DynamicLibrary
         *  file.
         *
         *  @return True if already terminated or terminated successfully.
         *  Can return false if no end function is found in the plugin,
         *  or if the DynamicLibrary can't be unloaded or is null.
         *
         *  @note Calling this function on a non-started plugin will return
         *  true but will sendd no event and terminated property will
         *  keep being false.
        **/
        /////////////////////////////////////////////////////////////
        bool end(bool unload_library = false);

        /////////////////////////////////////////////////////////////
        /** @brief Reloads the plugin.
         *
         *  It end the plugin if already started, then try to start
         *  it again.
         *
         *  @param reload_library : If true, reload the physical library
         *  file. Set it to true if you think that the physical file
         *  changed.
        **/
        /////////////////////////////////////////////////////////////
        void reload(bool reload_library = false);

    public:

        /////////////////////////////////////////////////////////////
        /** @brief Tells if plugin is started.
         *  @return True if started but not terminated yet.
        **/
        /////////////////////////////////////////////////////////////
        bool isStarted() const;

        /////////////////////////////////////////////////////////////
        /** @brief Tells if plugin is terminated.
         *  @return True if terminated and started before.
        **/
        /////////////////////////////////////////////////////////////
        bool isTerminated() const;

        /////////////////////////////////////////////////////////////
        /** @brief Returns a pointer to Plugin's info.
         *  @warning This adress may be invalid as it refers to an adress
         *  in the DynamicLibrary. You should assert that isStarted() is
         *  true.
        **/
        /////////////////////////////////////////////////////////////
        PluginInfo* getPluginInfo() const;

    protected:

        /////////////////////////////////////////////////////////////
        /** @brief Reload the PluginInfo structure used by the Plugin.
         *  @note Can set the pointer to null if function can't return
         *  any information.
        **/
        /////////////////////////////////////////////////////////////
        void refreshPluginInfo();

    public:

        /////////////////////////////////////////////////////////////
        /** @brief Return the physical library file holded by this
         *  plugin.
        **/
        /////////////////////////////////////////////////////////////
        DynamicLibraryPtr toDynamicLibrary();
    };

    APRO_DECLARE_EVENT_NOCONTENT(PluginStartedEvent);
    APRO_DECLARE_EVENT_NOCONTENT(PluginStoppingEvent);
    APRO_DECLARE_EVENT_NOCONTENT(PluginStoppedEvent);

    typedef AutoPointer<PluginHandle> PluginHandlePtr;

}

#endif
