////////////////////////////////////////////////////////////
/** @file ResourceLoader.h
 *  @ingroup Core
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 25/08/2012 - 20/04/2014
 *
 *  Defines the ResourceLoader class.
 *
**/
////////////////////////////////////////////////////////////
#ifndef APRORESOURCELOADER_H
#define APRORESOURCELOADER_H

#include "Platform.h"
#include "SString.h"
#include "Resource.h"
#include "List.h"
#include "ParametedObject.h"

namespace APro
{
    ////////////////////////////////////////////////////////////
    /** @class ResourceLoader
     *  @ingroup Core
     *  @brief A Resource Loader.
     *
     *  A ResourceLoader directly creates a resource from a file
     *  and returns it to the ResourceManager. This Resource will
     *  be destroyed by the resourceManager.
     *
     *  The ResourceLoader can be parameted with customs arguments,
     *  through the ParametedObject interface.
     *
     *  @note Default loaders for given extensions are managed by
     *  the ResourceManager.
    **/
    ////////////////////////////////////////////////////////////
    class APRO_DLL ResourceLoader : public ParametedObject
    {

    protected:

        String name;
        String description;

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Constructs the ResourceLoader.
        **/
        ////////////////////////////////////////////////////////////
        ResourceLoader();

        ////////////////////////////////////////////////////////////
        /** @brief Constructs the ResourceLoader.
        **/
        ////////////////////////////////////////////////////////////
        ResourceLoader(const String& name, const String& description);

        ////////////////////////////////////////////////////////////
        /** @brief Constructs the ResourceLoader by copy.
         *  @note This function is given for convenience only as Loaders
         *  are manipulated with Pointers.
        **/
        ////////////////////////////////////////////////////////////
        ResourceLoader(const ResourceLoader& other);

        ////////////////////////////////////////////////////////////
        /** @brief Destructs the ResourceLoader.
        **/
        ////////////////////////////////////////////////////////////
        virtual ~ResourceLoader();

        ////////////////////////////////////////////////////////////
        /** @brief Load a resource.
         *  @note Create the Resource object and returns it. If an error
         *  occurs, nullptr is returned.
        **/
        ////////////////////////////////////////////////////////////
        virtual ResourcePtr loadResource(const String& filename) = 0;

        ////////////////////////////////////////////////////////////
        /** @brief Returns the name of this Loader.
        **/
        ////////////////////////////////////////////////////////////
        const String& getName() const;

        ////////////////////////////////////////////////////////////
        /** @brief Returns the description of this Loader.
        **/
        ////////////////////////////////////////////////////////////
        const String& getDescription() const;
    };

    typedef AutoPointer<ResourceLoader> ResourceLoaderPtr;
}

#endif
