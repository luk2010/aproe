/** @file ResourceManager.h
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 25/08/2012
 *
 *  @addtogroup Global
 *  @addtogroup Resource
 *
 *  This file defines the ResourceManager singleton.
 *
**/
#ifndef APRORESOURCEMANAGER_H
#define APRORESOURCEMANAGER_H

#include "Platform.h"
#include "Singleton.h"
#include "Resource.h"
#include "ResourceLoader.h"
#include "ResourceWriter.h"
#include "SharedPointer.h"

namespace APro
{
    class APRO_DLL ResourceManager : public Singleton<ResourceManager>
    {

        APRO_DECLARE_SINGLETON(ResourceManager)

    private:

        List<SharedPointer<Resource> > resources;
        List<SharedPointer<ResourceLoader> > loaders;
        List<SharedPointer<ResourceWriter> > writers;

    protected:

        ResourceManager();
        ~ResourceManager();

    public:

        SharedPointer<Resource> getResource(const String& name);
        SharedPointer<ResourceLoader> getLoader(const String& name);
        SharedPointer<ResourceWriter> getWriter(const String& name);


        template <typename ResourceType> SharedPointer<ResourceType> loadResource(const String& name, const String& filename)
        {
            return spCast<ResourceType, Resource>(loadResource(name, filename));
        }
        SharedPointer<Resource> loadResource(const String& name, const String& filename);


        template <typename ResourceType> SharedPointer<ResourceType> loadResourceWithLoader(const String& name, const String& filename, const String& loaderName)
        {
            return spCast<ResourceType, Resource>(loadResourceWithLoader(name, filename, loaderName));
        }
        SharedPointer<Resource> loadResourceWithLoader(const String& name, const String& filename, const String& loaderName);


        void unloadResource(const String& name);

        void write(const String& resource, const String& writer, const String& filename);

        void addLoader(const SharedPointer<ResourceLoader>& loader);
        void removeLoader(const SharedPointer<ResourceLoader>& loader);

        void addWriter(const SharedPointer<ResourceWriter>& writer);
        void removeWriter(const SharedPointer<ResourceWriter>& writer);

        String listResources() const;
        String listLoaders() const;
        String listWriters() const;

        void clear();
    };
}

#endif
