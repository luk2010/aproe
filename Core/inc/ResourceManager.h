////////////////////////////////////////////////////////////
/** @file ResourceManager.h
 *  @ingroup Core
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 25/08/2012 - 15/02/2014
 *
 *  Defines the ResourceManager singleton.
 *
**/
////////////////////////////////////////////////////////////
#ifndef APRORESOURCEMANAGER_H
#define APRORESOURCEMANAGER_H

#include "Platform.h"
#include "AutoPointer.h"
#include "Manager.h"
#include "NameCopyGenerator.h"

#include "Resource.h"
#include "ResourceLoader.h"
#include "ResourceWriter.h"

namespace APro
{
    ////////////////////////////////////////////////////////////
    /** @class ResourceManager
     *  @ingroup Core
     *  @brief Manages every resources loaded in the Engine.
     *
     *  The resource manager manages loading/unloading and writing
     *  of resources in the Engine.
     *  @note This manger is thread-safe.
     *
     *  ### Basics resources steps
     *
     *  - First, you have to create a ResourceEntry. A ResourceEntry
     *  is an entry in the Manager List that will have a name, and
     *  an AutoPointer to a Resource. This pointer is null by default.
     *  - Then, you have to load the resource. You can give the
     *  ResourceEntry you just created, or give his name.
     *  @note Loading a Resource will returns <strong>true</strong>
     *  on success, and <strong>false</strong> on failure, only if
     *  you give an Entry. Else, it will return an Entry with null
     *  if Resource couldn't be loaded.
     *
     *  - You can unload manually the Resource by calling unloadResource()
     *  with given ResourceEntry or his name, setting the pointer to
     *  null.
     *
     *  ### Default extension management
     *
     *  You can set a loader or a writer as default for given
     *  extension. If this extension is found in the file path you
     *  gave to loadResource, the default loader will be used. If no loader
     *  is found by default, the default BitLoader will be used and file
     *  will be loaded in a BinaryArray Resource or a null Resource is
     *  returned depending on the option "NoDefaultLoader" value.
     *
    **/
    ////////////////////////////////////////////////////////////
    class APRO_DLL ResourceManager : public ThreadSafe,
                                     public ParametedObject,
                                     virtual public Manager<ResourceLoader>,
                                     virtual public Manager<ResourceWriter>
    {
        APRO_DECLARE_MANUALSINGLETON(ResourceManager)

    public:

        ////////////////////////////////////////////////////////////
        /** @class ResourceEntry
         *  @ingroup Core
         *  @brief An Entry in the Manager.
        **/
        ////////////////////////////////////////////////////////////
        class ResourceEntry
        {
        public:

            friend class ResourceManager;

        protected:

            String      m_name;         ///< Name of the Entry.
            ResourcePtr m_resource_data;///< Data Resource pointer.

        public:

            ////////////////////////////////////////////////////////////
            /** @brief Constructs the ResourceEntry.
            **/
            ////////////////////////////////////////////////////////////
            ResourceEntry(const String& name)
                : m_name(name), m_resource_data(nullptr) {}

            ////////////////////////////////////////////////////////////
            /** @brief Destructs the ResourceEntry.
            **/
            ////////////////////////////////////////////////////////////
            ~ResourceEntry() {}

        public:

            ////////////////////////////////////////////////////////////
            /** @brief Returns the name of this Entry.
            **/
            ////////////////////////////////////////////////////////////
            const String& getName() const { return m_name; }

            ////////////////////////////////////////////////////////////
            /** @brief Returns the resource in this Entry.
            **/
            ////////////////////////////////////////////////////////////
            ResourcePtr& getResource() { return m_resource_data; }
            template<typename ResourceType> AutoPointer<ResourceType> getResource()
            {
                ResourcePtr& tmp = getResource();
                if(!tmp.isNull())
                    return AutoPointer<ResourceType>(tmp.reinterpret<ResourceType>());
                else
                    return AutoPointer<ResourceType>();
            }

            ////////////////////////////////////////////////////////////
            /** @brief Returns the resource in this Entry.
            **/
            ////////////////////////////////////////////////////////////
            const ResourcePtr& getResource() const { return m_resource_data; }
            template<typename ResourceType> const AutoPointer<ResourceType> getResource() const
            {
                const ResourcePtr& tmp = getResource();
                if(!tmp.isNull())
                    return AutoPointer<ResourceType>(const_cast<ResourceType*>(tmp.reinterpret<const ResourceType>()));
                else
                    return AutoPointer<ResourceType>();
            }
        };

        typedef ResourceEntry* ResourceEntryPtr;///< Hack to protect from local destruction.

        ////////////////////////////////////////////////////////////
        /** @class ResourceNCG
         *  @ingroup Core
         *  @brief A class function to generate copy name for already
         *  used name.
        **/
        ////////////////////////////////////////////////////////////
        class ResourceNCG : public NameCopyGenerator
        {
        public:
            ResourceNCG(ResourceManager* _rm) { rm = _rm; }
            bool isNameUsed(const String& name) const;
        private:
            ResourceManager* rm;
        };

    private:

        List<ResourceEntry>                 m_resource_entries;///< ResourceEntry list.
        List<AutoPointer<ResourceLoader> >& m_loaders;         ///< Loader in this Manager.
        List<AutoPointer<ResourceWriter> >& m_writers;         ///< Writer in this Manager.

        Map<String, String>                 m_default_loaders; ///< Default Loader for extension.
        Map<String, String>                 m_default_writers; ///< Default Writer for extension.

        bool                                m_overwrite_loading; ///< Overwrite resource when loading with same name. If set to true, loading resource with same name
                                                                 ///  will overwrite and erase old resource. False is default value. If false, copy name will be generated.

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Constructs the ResourceManager.
        **/
        ////////////////////////////////////////////////////////////
        ResourceManager();

        ////////////////////////////////////////////////////////////
        /** @brief Destructs the ResourceManager, unload Loaders, Writers
         *  and Resources.
        **/
        ////////////////////////////////////////////////////////////
        ~ResourceManager();

    public:

        /*
           ===============================
           = Resource Entries Management =
           ===============================
        */
        /// @name Resources Functions
        /// Regroups every resources related function.
        /// @{

        ////////////////////////////////////////////////////////////
        /** @brief Retrieve a Resource with given name and returns it
         *  if found, else returns a null pointer.
        **/
        ////////////////////////////////////////////////////////////
        ResourcePtr& getResource(const String& name);
        template<typename ResourceType> AutoPointer<ResourceType> getResource(const String& name)
        {
            ResourcePtr& tmp = getResource(name);
            if(!tmp.isNull())
                return AutoPointer<ResourceType>(tmp.reinterpret<ResourceType>());
            else
                return AutoPointer<ResourceType>();
        }

        ////////////////////////////////////////////////////////////
        /** @brief Retrieve a Resource with given name and returns it
         *  if found, else returns a null pointer.
        **/
        ////////////////////////////////////////////////////////////
        const ResourcePtr& getResource(const String& name) const;
        template<typename ResourceType> const AutoPointer<ResourceType> getResource(const String& name) const
        {
            const ResourcePtr& tmp = getResource(name);
            if(!tmp.isNull())
                return AutoPointer<ResourceType>(tmp.reinterpret<const ResourceType>());
            else
                return AutoPointer<ResourceType>();
        }

        ////////////////////////////////////////////////////////////
        /** @brief Returns the resourceEntry that have the given
         *  name.
         *  @param name : If invalid (not exists), returns a null
         *  pointer.
        **/
        ////////////////////////////////////////////////////////////
        ResourceEntryPtr getResourceEntry(const String& name);

        ////////////////////////////////////////////////////////////
        /** @brief Returns the resourceEntry that have the given
         *  name.
         *  @param name : If invalid (not exists), returns a null
         *  pointer.
        **/
        ////////////////////////////////////////////////////////////
        const ResourceEntryPtr getResourceEntry(const String& name) const;

        ////////////////////////////////////////////////////////////
        /** @brief Creates a ResourceEntry.
         *
         *  @param name : Name of the Entry. If it is already taken
         *  or invalid, it returns a null pointer.
         *
         *  @return On Failure, a null pointer. On success, a pointer to
         *  an entry with ResourceData null. This data can be loaded using
         *  ::loadResource().
        **/
        ////////////////////////////////////////////////////////////
        ResourceEntryPtr createResourceEntry(const String& name);

        ////////////////////////////////////////////////////////////
        /** @brief Loads a resource object.
         *
         *  @param name : Name of the Entry where the resource should
         *  be loaded. If invalid, a new entry is created. @note You can
         *  give a newly created Entry name, as ResourceData pointer is
         *  null. If ResourceEntry is already created and loaded with another
         *  resource, this resource is unloaded and the new one is loaded
         *  in the entry but you are notified of this behaviour.
         *  @param filename : File path where the resource is. If this
         *  name is invalid, the resource will be null.
         *
         *  @return Entry where the Resource has been loaded. In case of
         *  failure, the ResourceData pointer is null.
        **/
        ////////////////////////////////////////////////////////////
        ResourceEntryPtr loadResource(const String& name, const String& filename);

        ////////////////////////////////////////////////////////////
        /** @brief Loads a resource object.
         *
         *  @param entry : Entry pointer where the resource shoud be
         *  loaded.
         *  @param filename : File path where the resource is. If this
         *  name is invalid, the resource will be null.
         *
         *  @return <strong>True</strong> if success, <strong>False</strong>
         *  otherweise.
        **/
        ////////////////////////////////////////////////////////////
        bool loadResource(ResourceEntryPtr& entry, const String& filename);

        ////////////////////////////////////////////////////////////
        /** @brief Loads a resource object specifying the used loader.
         *
         *  @param name : Name of the Entry where the resource should
         *  be loaded. If invalid, a new entry is created.
         *  @param filename : File path where the resource is. If this
         *  name is invalid, the resource will be null.
         *  @param loaderName : Name of the loader to use. If invalid, none
         *  is used and ResourceData pointer of returned entry is null.
         *
         *  @return Entry where the Resource has been loaded. In case of
         *  failure, the ResourceData pointer is null.
        **/
        ////////////////////////////////////////////////////////////
        ResourceEntryPtr loadResourceWithLoader(const String& name, const String& filename, const String& loaderName);

        ////////////////////////////////////////////////////////////
        /** @brief Loads a resource object.
         *
         *  @param entry : Entry pointer where the resource shoud be
         *  loaded.
         *  @param filename : File path where the resource is. If this
         *  name is invalid, the resource will be null.
         *  @param loaderName : Name of the loader to use. If invalid, none
         *  is used and ResourceData pointer of entry is null.
         *
         *  @return <strong>True</strong> if success, <strong>False</strong>
         *  otherweise.
        **/
        ////////////////////////////////////////////////////////////
        bool loadResourceWithLoader(ResourceEntryPtr& entry, const String& filename, const String& loaderName);

        ////////////////////////////////////////////////////////////
        /** @brief Unloads a resource.
         *
         *  This is done by nullizing the pointer in the ResourceEntry
         *  given. As you should have only regular pointers to Entries,
         *  the AutoPointer uses will be set to 0, and the Resource will
         *  be destroyed calling destructors.
         *
         *  @note ResourceEntry is not destroyed during the process.
         *
         *  @param name : Name of the ResourceEntry where the Resource
         *  is. If this name is invalid, this function does nothing.
        **/
        ////////////////////////////////////////////////////////////
        void unloadResource(const String& name);

        ////////////////////////////////////////////////////////////
        /** @brief Unload every loaded resource in this manager.
        **/
        ////////////////////////////////////////////////////////////
        void unloadAllResource();

        ////////////////////////////////////////////////////////////
        /** @brief Print every resources in this ResourceManager.
         *
         *  The list is returned as a string wich has format :
         *  %resource_name
         *  with a standard '-' list type for every resources.
        **/
        ////////////////////////////////////////////////////////////
        String printResources() const;

        ////////////////////////////////////////////////////////////
        /** @brief Set the m_overwrite_loading property.
        **/
        ////////////////////////////////////////////////////////////
        void overwriteOnLoading(bool _overwrite);

        ////////////////////////////////////////////////////////////
        /** @brief Returns true if given resource entry name already
         *  exists.
        **/
        ////////////////////////////////////////////////////////////
        bool resourceEntryExists(const String& name) const;

        /// @}

    public:

        /*
           ==============================
           = Resource Loader Management =
           ==============================
        */

        ////////////////////////////////////////////////////////////
        /** @brief Returns the ResourceLoader wich have given name.
        **/
        ////////////////////////////////////////////////////////////
        ResourceLoaderPtr getLoader(const String& name);

        ////////////////////////////////////////////////////////////
        /** @brief Returns the ResourceLoader wich have given name.
        **/
        ////////////////////////////////////////////////////////////
        const ResourceLoaderPtr getLoader(const String& name) const;

        ////////////////////////////////////////////////////////////
        /** @brief Adds a loader to this ResourceManager.
         *
         *  @param loader : A pointer type to the ResourceLoader. This
         *  loader must have a unique name. If name already exists,
         *  <strong>false</strong> is returned. Else it is <strong>
         *  true</strong> if pointer is valid.
        **/
        ////////////////////////////////////////////////////////////
        bool addLoader(ResourceLoaderPtr& loader);

        ////////////////////////////////////////////////////////////
        /** @brief Removes a loader from this ResourceManager.
        **/
        ////////////////////////////////////////////////////////////
        bool removeLoader(const ResourceLoaderPtr& loader);

        ////////////////////////////////////////////////////////////
        /** @brief Removes a loader from this ResourceManager.
         *  @param loader_name : Name of the Loader to remove. This name
         *  must be valid, else the function return false.
        **/
        ////////////////////////////////////////////////////////////
        bool removeLoader(const String& loader_name);

        ////////////////////////////////////////////////////////////
        /** @brief Print every loaders in this ResourceManager, with
         *  their description.
         *
         *  The list is returned as a string wich has format :
         *  %loader_name : %loader_description
         *  with a standard '-' list type for every loaders.
        **/
        ////////////////////////////////////////////////////////////
        String printLoaders() const;

        ////////////////////////////////////////////////////////////
        /** @brief Set a default loader for given extension.
         *  @note If extension is already setted, old default loader
         *  is overwritten.
         *  @note In debug mode only, Names are verified and if new
         *  default name is invalid, it does not change the Loader.
        **/
        ////////////////////////////////////////////////////////////
        void setDefaultLoader(const String& ext, const String& loader);

        ////////////////////////////////////////////////////////////
        /** @brief Returns the loader used for given extension.
         *  @note Returns nullptr if no loader found.
        **/
        ////////////////////////////////////////////////////////////
        ResourceLoaderPtr getDefaultLoader(const String& ext) const;

    public:

        /*
           ==============================
           = Resource Writer Management =
           ==============================
        */

        ////////////////////////////////////////////////////////////
        /** @brief Returns the ResourceWriter wich have given name.
        **/
        ////////////////////////////////////////////////////////////
        ResourceWriterPtr getWriter(const String& name);

        ////////////////////////////////////////////////////////////
        /** @brief Returns the ResourceWriter wich have given name.
        **/
        ////////////////////////////////////////////////////////////
        const ResourceWriterPtr getWriter(const String& name) const;

        ////////////////////////////////////////////////////////////
        /** @brief Adds a writer to this ResourceManager.
         *
         *  @param writer : A pointer type to the ResourceWriter. This
         *  writer must have a unique name. If name already exists,
         *  <strong>false</strong> is returned. Else it is <strong>
         *  true</strong> if pointer is valid.
        **/
        ////////////////////////////////////////////////////////////
        bool addWriter(ResourceWriterPtr& writer);

        ////////////////////////////////////////////////////////////
        /** @brief Removes a writer from this ResourceManager.
        **/
        ////////////////////////////////////////////////////////////
        bool removeWriter(const ResourceLoaderPtr& writer);

        ////////////////////////////////////////////////////////////
        /** @brief Removes a writer from this ResourceManager.
         *  @param writer_name : Name of the Writer to remove. This name
         *  must be valid, else the function return false.
        **/
        ////////////////////////////////////////////////////////////
        bool removeWriter(const String& writer_name);

        ////////////////////////////////////////////////////////////
        /** @brief Print every writers in this ResourceManager, with
         *  their description.
         *
         *  The list is returned as a string wich has format :
         *  %writer_name : %writer_description
         *  with a standard '-' list type for every writers.
        **/
        ////////////////////////////////////////////////////////////
        String printWriters() const;

        ////////////////////////////////////////////////////////////
        /** @brief Write a Resource in a file, with specific
         *  ResourceWriter.
         *
         *  @param resource_name : Name of the Resource to write.
         *  It must be a valid name.
         *  @param writer_name : Name of the ResourceWriter to use
         *  for the operation. This name must be valid.
         *  @param filename : Path to the file to write to. If the
         *  file doesn't exists it will be created if the option
         *  'FS_OO_CREATE' is setted in the FileSystem options.
         *
         *  @return False if one of the parameter is incorrect, or if
         *  the operation failed.
        **/
        ////////////////////////////////////////////////////////////
        bool writeResource(const String& resource_name, const String& writer_name, const String& filename);

        ////////////////////////////////////////////////////////////
        /** @brief Set a default writer for given extension.
         *  @note If extension is already setted, old default writer
         *  is overwritten.
        **/
        ////////////////////////////////////////////////////////////
        void setDefaultWriter(const String& ext, const String& writer);

        ////////////////////////////////////////////////////////////
        /** @brief Returns the writer used for given extension.
         *  @note Returns nullptr if no writer found.
        **/
        ////////////////////////////////////////////////////////////
        ResourceWriterPtr getDefaultWriter(const String& ext) const;

    protected:

        ////////////////////////////////////////////////////////////
        /** @brief Find the correct loader for given extension.
        **/
        ////////////////////////////////////////////////////////////
        ResourceLoaderPtr _findCorrectLoader(const String& extension);

        ////////////////////////////////////////////////////////////
        /** @brief Create a Resource with given loader from given file.
        **/
        ////////////////////////////////////////////////////////////
        ResourcePtr _loadResourceFrom(const String& filename, ResourceLoaderPtr& loader);

        ////////////////////////////////////////////////////////////
        /** @brief Return the index of given Loader.
         *  @return -1 if not found.
        **/
        ////////////////////////////////////////////////////////////
        int _getLoaderIndex(const String& name) const;

        ////////////////////////////////////////////////////////////
        /** @brief Return the index of given Writer.
         *  @return -1 if not found.
        **/
        ////////////////////////////////////////////////////////////
        int _getWriterIndex(const String& name) const;
    };

    typedef ResourceManager::ResourceEntryPtr ResourceEntryPtr;
}

#endif
