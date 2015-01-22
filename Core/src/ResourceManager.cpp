////////////////////////////////////////////////////////////
/** @file ResourceManager.cpp
 *  @ingroup Core
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 27/08/2012 - 21/01/2015
 *
 *  Implements the ResourceManager.
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
////////////////////////////////////////////////////////////
#include "ResourceManager.h"
#include "Console.h"
#include "FileSystem.h"

namespace APro
{
    APRO_IMPLEMENT_MANUALSINGLETON(ResourceManager)

    ResourceManager::ResourceManager()
        : m_loaders(Manager<ResourceLoader>::objects), m_writers(Manager<ResourceWriter>::objects)
    {
        m_default_loaders[""] = nullptr;
        m_default_writers[""] = nullptr;
    }

    ResourceManager::~ResourceManager()
    {
        // Loaders and Writers are destroyed by the AutoPointer. We
        // do not need to destroy them.
        // Resource unloading is done there to be sure because some resources
        // take much space in memory.

        unloadAllResource();
    }

    ResourcePtr& ResourceManager::getResource(const String& name)
    {
        if(!name.isEmpty())
        {
            APRO_THREADSAFE_AUTOLOCK;

            ResourceEntryPtr entry = nullptr;
            List<ResourceEntry>::const_iterator e = m_resource_entries.end();
            for(List<ResourceEntry>::iterator it = m_resource_entries.begin(); it != e; it++)
                if((*it).getName() == name)
                    entry = &(*it);

            if(entry)
                return entry->getResource();
            else
            {
                aprodebug("Can't find Resource Entry '") << name << "'.";
            }
        }

        return nullptr;
    }

    const ResourcePtr& ResourceManager::getResource(const String& name) const
    {
        if(!name.isEmpty())
        {
            APRO_THREADSAFE_AUTOLOCK;

            const ResourceEntryPtr entry = nullptr;
            List<ResourceEntry>::const_iterator e = m_resource_entries.end();
            for(List<ResourceEntry>::const_iterator it = m_resource_entries.begin(); it != e; it++)
                if((*it).getName() == name)
                    entry = &(*it);

            if(entry)
                return entry->getResource();
            else
            {
                aprodebug("Can't find Resource Entry '") << name << "'.";
            }
        }

        return nullptr;
    }

    ResourceEntryPtr ResourceManager::getResourceEntry(const String& name)
    {
        if(!name.isEmpty())
        {
            APRO_THREADSAFE_AUTOLOCK;

            ResourceEntryPtr entry = nullptr;
            List<ResourceEntry>::const_iterator e = m_resource_entries.end();
            for(List<ResourceEntry>::iterator it = m_resource_entries.begin(); it != e; it++)
                if((*it).getName() == name)
                    entry = &(*it);

            if(entry)
                return entry;
            else
            {
                aprodebug("Can't find Resource Entry '") << name << "'.";
            }
        }

        return nullptr;
    }

    const ResourceEntryPtr ResourceManager::getResourceEntry(const String& name) const
    {
        if(!name.isEmpty())
        {
            APRO_THREADSAFE_AUTOLOCK;

            const ResourceEntryPtr entry = nullptr;
            List<ResourceEntry>::const_iterator e = m_resource_entries.end();
            for(List<ResourceEntry>::const_iterator it = m_resource_entries.begin(); it != e; it++)
                if((*it).getName() == name)
                    entry = &(*it);

            if(entry)
                return entry;
            else
            {
                aprodebug("Can't find Resource Entry '") << name << "'.";
            }
        }

        return nullptr;
    }

    ResourceEntryPtr ResourceManager::createResourceEntry(const String& name)
    {
        if(!name.isEmpty())
        {
            APRO_THREADSAFE_AUTOLOCK;

            ResourceEntryPtr entry = nullptr;
            List<ResourceEntry>::const_iterator e = m_resource_entries.end();
            for(List<ResourceEntry>::iterator it = m_resource_entries.begin(); it != e; it++)
                if((*it).getName() == name)
                    entry = &(*it);

            if(entry)
            {
//              No need as we use this function also to retrieve resource or create it if it doesn't exists.
//              aprodebug("Entry '") << name << "' already exists. Can't create it.";
                return entry;
            }
            else
            {
                entry = AProNew(ResourceEntry, name);
                m_resource_entries.push_back(entry);
                return entry;
            }
        }

        return nullptr;
    }

    ResourceEntryPtr ResourceManager::loadResource(const String& name, const String& filename)
    {
        if(name.isEmpty())
        {
            aprodebug("Try to load file '") << filename << "' without name.";
            return nullptr;
        }
        else
        {
            ResourceEntryPtr _entry = createResourceEntry(name);
            loadResource(_entry, filename);
            return _entry;
        }
    }

    bool ResourceManager::loadResource(ResourceEntryPtr& entry, const String& filename)
    {
        if(!entry)
        {
            aprodebug("Try to load file '") << filename << "' without entry.";
            return false;
        }
        else if (filename.isEmpty())
        {
            aprodebug("Try to load entry '") << entry->getName() << "' without file."
            return false;
        }
        else
        {
            if(!entry->getResource().isNull())
            {
                if(m_overwrite_loading)
                {
                    aprodebug("Overwriting resource '") << entry->getName() << "'.";
                    unloadResource(entry->getName());
                }
                else
                {
                    aprodebug("Resource '") << entry->getName() << "' already exists so generating a copy name.";

                    ResourceNCG ncg(this);
                    return loadResource(ncg(entry->getName()), filename, loaderName);
                }
            }

            ResourceLoaderPtr loader = _findCorrectLoader(FileSystem::getExtension(filename));
            if(!loader.isNull())
            {
                ResourcePtr resource = _loadResourceFrom(filename, loader);
                entry->m_resource_data = resource;
                return !resource.isNull();
            }
        }

        return false;
    }

    ResourceEntryPtr ResourceManager::loadResourceWithLoader(const String& name, const String& filename, const String& loaderName)
    {
        if(name.isEmpty())
        {
            aprodebug("Try to load file '") << filename << "' without name.";
            return nullptr;
        }
        else
        {
            ResourceEntryPtr _entry = createResourceEntry(name);
            loadResourceWithLoader(_entry, filename, loaderName);
            return _entry;
        }
    }

    bool ResourceManager::loadResourceWithLoader(ResourceEntryPtr& entry, const String& filename, const String& loaderName)
    {
        if(!entry)
        {
            aprodebug("Try to load file '") << filename << "' without entry.";
            return false;
        }
        else if (filename.isEmpty())
        {
            aprodebug("Try to load entry '") << entry->getName() << "' without file."
            return false;
        }
        else
        {
            if(!entry->getResource().isNull())
            {
                if(m_overwrite_loading)
                {
                    aprodebug("Overwriting resource '") << entry->getName() << "'.";
                    unloadResource(entry->getName());
                }
                else
                {
                    aprodebug("Resource '") << entry->getName() << "' already exists so generating a copy name.";

                    ResourceNCG ncg(this);
                    return loadResourceWithLoader(ncg(entry->getName()), filename, loaderName);
                }
            }

            ResourceLoaderPtr loader = getLoader(loaderName);
            if(loader.isNull())
            {
                aprodebug("Can't find loader '") << loaderName << "'.";
                return false;
            }

            if(!loader.isNull())
            {
                ResourcePtr resource = _loadResourceFrom(filename, loader);
                entry->m_resource_data = resource;
                return !resource.isNull();
            }
        }

        return false;
    }

    void ResourceManager::unloadResource(const String& name)
    {
        if(!name.isEmpty())
        {
            ResourceEntryPtr entry = getResourceEntry(name);

            APRO_THREADSAFE_AUTOLOCK
            entry->m_resource_data.nullize();
            // Destructors should correctly be called in this
            // instruction, so we have nothing else to do.
        }
    }

    void ResourceManager::unloadAllResource()
    {
        APRO_THREADSAFE_AUTOLOCK

        ResourceEntryPtr entry = &(m_resource_entries.at(0));
        uint32_t idx = 0;
        while(m_resource_entries.size() > idx)
        {
            entry->m_resource_data.nullize();
            idx++;
            
            entry = &(m_resource_entries.at(idx));
        }
        m_resource_entries.clear();
    }

    String ResourceManager::printResources() const
    {
        String result;
        result << "[ResourceManager] Resource's List :\n"
               << "-----------------------------------\n";

        // Begin AutoLock
        {
            APRO_THREADSAFE_AUTOLOCK

            List<ResourceEntry>::const_iterator e = m_resource_entries.end();
            for(List<ResourceEntry>::iterator it = m_resource_entries.begin(); it != e; it++)
                result << " - " << (*it).getName() << "\n";
        }
        // End AutoLock

        result << "-----------------------------------\n";
        return result;
    }

    void ResourceManager::overwriteOnLoading(bool _overwrite)
    {
        m_overwrite_loading = _overwrite;
    }

    bool ResourceManager::resourceEntryExists(const String& name) const
    {
        return getResourceEntry(name) != nullptr;
    }

    ResourceLoaderPtr ResourceManager::getLoader(const String& name)
    {
        if(!name.isEmpty())
        {
            APRO_THREADSAFE_AUTOLOCK

            List<AutoPointer<ResourceLoader> >::const_iterator e = m_loaders.end();
            for(List<AutoPointer<ResourceLoader> >::iterator it = m_loaders.begin(); it != e; it++)
            {
                if((*it)->getName() == name)
                    return (*it);
            }

            // We reach this point only if loader is not found.
            aprodebug("Can't find loader '") << name << "'.";
        }

        return ResourceLoaderPtr::Null;
    }

    const ResourceLoaderPtr ResourceManager::getLoader(const String& name) const
    {
        if(!name.isEmpty())
        {
            APRO_THREADSAFE_AUTOLOCK

            List<AutoPointer<ResourceLoader> >::const_iterator e = m_loaders.end();
            for(List<AutoPointer<ResourceLoader> >::const_iterator it = m_loaders.begin(); it != e; it++)
            {
                if((*it)->getName() == name)
                    return (*it);
            }

            // We reach this point only if loader is not found.
            aprodebug("Can't find loader '") << name << "'.";
        }

        return ResourceLoaderPtr::Null;
    }

    bool ResourceManager::addLoader(const ResourceLoaderPtr& loader)
    {
        if(!loader.isNull())
        {
            if(getLoader(loader->getName()).isNull())
            {
                APRO_THREADSAFE_AUTOLOCK
                m_loaders.push_back(loader);
                return true;
            }
            else
            {
                aprodebug("Loader '") << loader->getName() << "' already in ResourceManager. Please set another name to your loader.";
            }
        }

        return false;
    }

    bool ResourceManager::removeLoader(const ResourceLoaderPtr& loader)
    {
        if(loader.isNull())
            return false;

        APRO_THREADSAFE_AUTOLOCK

        int i = m_loaders.find(loader);
        if(i < 0)
        {
            aprodebug("Can't find loader '") << loader->getName() << "'.";
            return false;
        }

        m_loaders.erase(m_loaders.begin() + i);
        return true;
    }

    bool ResourceManager::removeLoader(const String& loader_name)
    {
        if(!loader_name.isEmpty())
        {
            int index = _getLoaderIndex(loader_name);
            if(index >= 0)
            {
                APRO_THREADSAFE_AUTOLOCK
                m_loaders.erase(m_loaders.begin() + index);
                return true;
            }
            else
            {
                aprodebug("Can't find loader '") << loader_name << "'.";
            }
        }

        return false;
    }

    String ResourceManager::printLoaders() const
    {
        String result;
        result << "[ResourceManager] ResourceLoader's List :\n"
               << "-----------------------------------------\n";

        // Begin AutoLock
        {
            APRO_THREADSAFE_AUTOLOCK

            List<AutoPointer<ResourceLoader> >::const_iterator e = m_loaders.end();
            for(List<AutoPointer<ResourceLoader> >::iterator it = m_loaders.begin(); it != e; it++)
                result << " - " << (*it).getName() << "\n";
        }
        // End AutoLock

        result << "-----------------------------------\n";
        return result;
    }

    void ResourceManager::setDefaultLoader(const String& ext, const String& loader)
    {
        if(Platform::IsDebugMode())
        {
            if(getLoader(loader).isNull())
                return;
        }

        APRO_THREADSAFE_AUTOLOCK
        m_default_loaders[ext] = loader;
    }

    ResourceLoaderPtr ResourceManager::getDefaultLoader(const String& ext) const
    {
        APRO_THREADSAFE_AUTOLOCK
        if(m_default_loaders.keyExists(ext))
            return m_default_loaders[ext];
        else
            return ResourceLoaderPtr::Null;
    }

    ResourceWriterPtr ResourceManager::getWriter(const String& name)
    {
        if(!name.isEmpty())
        {
            APRO_THREADSAFE_AUTOLOCK

            List<AutoPointer<ResourceWriter> >::const_iterator e = m_writers.end();
            for(List<AutoPointer<ResourceWriter> >::iterator it = m_writers.begin(); it != e; it++)
            {
                if((*it)->getName() == name)
                    return (*it);
            }

            // We reach this point only if writer is not found.
            aprodebug("Can't find writer '") << name << "'.";
        }

        return ResourceWriterPtr::Null;
    }

    const ResourceWriterPtr ResourceManager::getWriter(const String& name) const
    {
        if(!name.isEmpty())
        {
            APRO_THREADSAFE_AUTOLOCK

            List<AutoPointer<ResourceWriter> >::const_iterator e = m_writers.end();
            for(List<AutoPointer<ResourceWriter> >::const_iterator it = m_writers.begin(); it != e; it++)
            {
                if((*it)->getName() == name)
                    return (*it);
            }

            // We reach this point only if writer is not found.
            aprodebug("Can't find writer '") << name << "'.";
        }

        return ResourceWriterPtr::Null;
    }

    bool ResourceManager::addWriter(ResourceWriterPtr& writer)
    {
        if(!writer.isNull())
        {
            if(getWriter(writer->getName()).isNull())
            {
                APRO_THREADSAFE_AUTOLOCK
                m_writers.push_back(writer);
                return true;
            }
            else
            {
                aprodebug("Writer '") << writer->getName() << "' already in ResourceManager. Please set another name to your writer.";
            }
        }

        return false;
    }

    bool ResourceManager::removeWriter(const ResourceLoaderPtr& writer)
    {
        if(writer.isNull())
            return false;

        APRO_THREADSAFE_AUTOLOCK

        int i = m_writers.find(writer);
        if(i < 0)
        {
            aprodebug("Can't find writer '") << writer->getName() << "'.";
            return false;
        }

        m_writers.erase(m_writers.begin() + i);
        return true;
    }

    bool ResourceManager::removeWriter(const String& writer_name)
    {
        if(!writer_name.isEmpty())
        {
            int index = _getWriterIndex(writer_name);
            if(index >= 0)
            {
                APRO_THREADSAFE_AUTOLOCK
                m_writers.erase(m_writers.begin() + index);
                return true;
            }
            else
            {
                aprodebug("Can't find writer '") << writer_name << "'.";
            }
        }

        return false;
    }

    String ResourceManager::printWriters() const
    {
        String result;
        result << "[ResourceManager] ResourceWriter's List :\n"
               << "-----------------------------------------\n";

        // Begin AutoLock
        {
            APRO_THREADSAFE_AUTOLOCK

            List<AutoPointer<ResourceWriter> >::const_iterator e = m_writers.end();
            for(List<AutoPointer<ResourceWriter> >::iterator it = m_writers.begin(); it != e; it++)
                result << " - " << (*it).getName() << "\n";
        }
        // End AutoLock

        result << "-----------------------------------\n";
        return result;
    }

    bool ResourceManager::writeResource(const String& resource_name, const String& writer_name, const String& filename)
    {
        if(!resource_name.isEmpty())
        {
            ResourceEntryPtr res = getResourceEntry(resource_name);
            if(!res || res->getResource().isNull())
            {
                aprodebug("Can't write empty resource '") << resource_name << "'.";
                return false;
            }

            ResourceWriterPtr writer = getWriter(writer_name);
            if(writer.isNull() || !writer->isCompatible(res->getResource()))
            {
                aprodebug("Can't write with writer '") << writer_name << "'.";
                return false;
            }

            return writer->write(res->getResource(), filename);
        }
    }

    void ResourceManager::setDefaultWriter(const String& ext, const String& writer)
    {
        if(Platform::IsDebugMode())
        {
            if(getWriter(writer).isNull())
                return;
        }

        APRO_THREADSAFE_AUTOLOCK
        m_default_writers[ext] = writer;
    }

    ResourceWriterPtr ResourceManager::getDefaultWriter(const String& ext) const
    {
        APRO_THREADSAFE_AUTOLOCK
        if(m_default_writers.keyExists(ext))
            return m_default_writers[ext];
        else
            return ResourceWriterPtr::Null;
    }

    ResourceLoaderPtr ResourceManager::_findCorrectLoader(const String& extension)
    {
        if(!extension.isEmpty())
        {
            // First we look for default loader
            ResourceLoaderPtr __loader = getDefaultLoader(extension);
            if(!__loader.isNull())
                return __loader;

            // If null, we return a null loader.
        }

        return ResourceLoaderPtr::Null;
    }

    ResourcePtr ResourceManager::_loadResourceFrom(const String& filename, ResourceLoaderPtr& loader)
    {
        return loader->loadResource(filename);
    }

    int ResourceManager::_getLoaderIndex(const String& name) const
    {
        if(!name.isEmpty())
        {
            APRO_THREADSAFE_AUTOLOCK

            int i = 0;
            List<AutoPointer<ResourceLoader> >::const_iterator e = m_loaders.end();
            for(List<AutoPointer<ResourceLoader> >::const_iterator it = m_loaders.begin(); it != e; it++, ++i)
            {
                if((*it)->getName() == name)
                    return i;
            }

            // We reach this point only if loader is not found.
//          aprodebug("Can't find loader '") << name << "'.";
        }

        return -1;
    }

    int ResourceManager::_getWriterIndex(const String& name) const
    {
        if(!name.isEmpty())
        {
            APRO_THREADSAFE_AUTOLOCK

            int i = 0;
            List<AutoPointer<ResourceWriter> >::const_iterator e = m_writers.end();
            for(List<AutoPointer<ResourceWriter> >::const_iterator it = m_writers.begin(); it != e; it++, ++i)
            {
                if((*it)->getName() == name)
                    return i;
            }

            // We reach this point only if writer is not found.
//          aprodebug("Can't find writer '") << name << "'.";
        }

        return -1;
    }

    bool ResourceManager::ResourceNCG::isNameUsed(const String& name) const
    {
        if(rm)
            return rm->getResource(_cpyname) != nullptr;
        else
            return false;
    }

}
