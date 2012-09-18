/** @file ResourceManager.cpp
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 27/08/2012
 *
 *  @addtogroup Global
 *  @addtogroup Resource
 *
 *  This file defines the ResourceManager singleton.
 *
**/
#include "ResourceManager.h"
#include "Console.h"
#include "FileUtils.h"

namespace APro
{
    APRO_IMPLEMENT_SINGLETON(ResourceManager)

    ResourceManager::ResourceManager()
    {

    }

    ResourceManager::~ResourceManager()
    {

    }

    SharedPointer<Resource> ResourceManager::getResource(const String& name)
    {
        for(List<SharedPointer<Resource> >::Iterator i = resources.begin(); !i.isEnd(); i++)
        {
            if(i.get()->getName() == name)
            {
                return i.get();
            }
        }

        return SharedPointer<Resource>();
    }

    SharedPointer<ResourceLoader> ResourceManager::getLoader(const String & name)
    {
        for(List<SharedPointer<ResourceLoader> >::Iterator i = loaders.begin(); !i.isEnd(); i++)
        {
            if(i.get()->name() == name)
            {
                return i.get();
            }
        }

        return SharedPointer<ResourceLoader>();
    }

    SharedPointer<ResourceWriter> ResourceManager::getWriter(const String& name)
    {
        for(List<SharedPointer<ResourceWriter> >::Iterator i = writers.begin(); !i.isEnd(); i++)
        {
            if(i.get()->name() == name)
            {
                return i.get();
            }
        }

        return SharedPointer<ResourceWriter>();
    }

    SharedPointer<Resource> ResourceManager::loadResource(const String& name, const String& filename)
    {
        SharedPointer<Resource> res = getResource(name);
        if(!res.isNull())
        {
            if(res->getFilename() == filename)
            {
                return res;
            }
            else
            {
                String name_ = name;
                name_ << "_" << filename;
                return loadResource(name_, filename);
            }
        }

        SharedPointer<ResourceLoader> loader;

        String ext = FileUtilities::extension(filename);
        for(List<SharedPointer<ResourceLoader> >::Iterator i(loaders.begin()); !i.isEnd(); i++)
        {
            if(i.get()->extensions().find(ext) >= 0 && !(i.get()->getParam(String("IsManual")).to<bool>()))
            {
                loader = i.get();
                break;
            }
        }

        if(loader.isNull())
        {
            String str("Can't find a correct loader for extension "); str << ext << ".";
            Console::get().inform(str, String("ResourceManager"));
        }
        else
        {
            res = loadResourceWithLoader(name, filename, loader->name());
        }

        return res;
    }

    SharedPointer<Resource> ResourceManager::loadResourceWithLoader(const String& name, const String& filename, const String& loaderName)
    {
        SharedPointer<Resource> res = getResource(name);
        if(!res.isNull())
        {
            if(res->getFilename() == filename)
            {
                return res;
            }
            else
            {
                String name_ = name;
                name_ << "_" << filename;
                return loadResourceWithLoader(name_, filename, loaderName);
            }
        }

        SharedPointer<ResourceLoader> loader = getLoader(loaderName);
        if(loader.isNull())
        {
            Console::get() << "\n[ResourceManager] Can't find loader " << loaderName << " !";
            return SharedPointer<Resource>();
        }
        else
        {
            Console::get() << "\n[ResourceManager] Loading resource " << filename << " with name " << name << " and loader " << loader->name() << ".";

            res = loader->loadResource(filename);

            String str;
            if(!res.isNull())
            {
                res->setName(name);
                str << "\n[ResourceManager] Loading resource " << res->getName() << " completed !";
                resources.append(res);
            }
            else
            {
                str << "\n[ResourceManager] Loading resource " << name << " failed !";
            }
            Console::get() << str;

            return res;
        }
    }

    void ResourceManager::unloadResource(const String& name)
    {
        SharedPointer<Resource> res = getResource(name);
        if(!res.isNull())
        {
            resources.erase(resources.find(res));
        }
    }

    void ResourceManager::write(const String& resource, const String& writer, const String& filename)
    {
        SharedPointer<Resource> res = getResource(resource);
        if(res.isNull())
        {
            Console::get() << "\n[ResourceManager] Can't find resource " << resource << ".";
            return;
        }

        SharedPointer<ResourceWriter> w = getWriter(writer);
        if(w.isNull())
        {
            Console::get() << "\n[ResourceManager] Can't find writer " << writer << ".";
            return;
        }

        w->write(res, filename);
    }

    void ResourceManager::addLoader(const SharedPointer<ResourceLoader>& loader)
    {
        if(!loader.isNull())
        {
            if(getLoader(loader->name()).isNull())
            {
                loaders.append(loader);
                Console::get() << "\n[ResourceManager] Added Loader " << loader->name() << ".";
            }
        }
    }

    void ResourceManager::removeLoader(const SharedPointer<ResourceLoader>& loader)
    {
        if(!loader.isNull())
        {
            if(!(getLoader(loader->name()).isNull()))
            {
                loaders.erase(loaders.find(loader));
            }
        }
    }

    void ResourceManager::addWriter(const SharedPointer<ResourceWriter>& writer)
    {
        if(!writer.isNull())
        {
            if(getWriter(writer->name()).isNull())
            {
                writers.append(writer);
                Console::get() << "\n[ResourceManager] Added Writer " << writer->name() << ".";
            }
        }
    }

    void ResourceManager::removeWriter(const SharedPointer<ResourceWriter>& writer)
    {
        if(!writer.isNull())
        {
            if(!(getWriter(writer->name()).isNull()))
            {
                writers.erase(writers.find(writer));
            }
        }
    }

    String ResourceManager::listLoaders() const
    {
        String result;

        result << "Loaders's list : " << "\n" << "----------";
        result << "\nNumber of loaders : " << String::toString((int) loaders.size()) << ".";
        for(List<SharedPointer<ResourceLoader> >::ConstIterator i = loaders.begin(); !i.isEnd(); i++)
        {
            result << "\n  + " << i.get()->name() << " : " << i.get()->description();
        }

        return result;
    }

    String ResourceManager::listWriters() const
    {
        String result;

        result << "Writer's list : " << "\n" << "----------";
        result << "\nNumber of Writers : " << String::toString((int) writers.size()) << ".";
        for(List<SharedPointer<ResourceWriter> >::ConstIterator i = writers.begin(); !i.isEnd(); i++)
        {
            result << "\n  + " << i.get()->name() << " : " << i.get()->description();
        }

        return result;
    }

    String ResourceManager::listResources() const
    {
        String result;

        result << "Resources's list : " << "\n" << "----------";
        result << "\nNumber of resources : " << String::toString((int) resources.size()) << ".";
        for(List<SharedPointer<Resource> >::ConstIterator i = resources.begin(); !i.isEnd(); i++)
        {
            result << "\n  + " << i.get()->getName() << " : " << String::toString((int) i.get().getUses()) << " uses.";
        }

        return result;
    }

    void ResourceManager::clear()
    {
        for(List<SharedPointer<Resource> > ::Iterator i(resources.begin()); !i.isEnd(); i++)
        {
            i.get()->destroy();
        }

        resources.clear();
        loaders.clear();
        writers.clear();
    }
}
