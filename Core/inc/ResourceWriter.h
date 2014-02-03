////////////////////////////////////////////////////////////
/** @file ResourceWriter.h
 *  @ingroup Core
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 01/09/2012 - 03/02/2014
 *
 *  Defines the ResourceWriter class.
 *
**/
////////////////////////////////////////////////////////////
#ifndef APRORESOURCEWRITER_H
#define APRORESOURCEWRITER_H

#include "Platform.h"
#include "Resource.h"
#include "SString.h"
#include "ParametedObject.h"

namespace APro
{
    ////////////////////////////////////////////////////////////
    /** @class ResourceWriter
     *  @ingroup Core
     *  @brief A Resource Writer.
     *
     *  Writes given resource to given file. The Resource hash
     *  must be compatible to this Writer. If Hash doesn't
     *  correspond, behaviour is undefined as every writer
     *  works differently. Many hashes can be compatible to
     *  one writer, depending on the implementation of the
     *  writer.
     *
     *  @note See the Writer specific documentation for specific
     *  argues.
    **/
    ////////////////////////////////////////////////////////////
    class APRO_DLL ResourceWriter : public ParametedObject
    {
    protected:

        String      name;           ///< Name of the writer.
        String      description;    ///< Description of the writer.
        HashArray   compatible_hash;///< List of hashes compatible with this writer.

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Constructs the ResourceWriter.
        **/
        ////////////////////////////////////////////////////////////
        ResourceWriter();

        ////////////////////////////////////////////////////////////
        /** @brief Constructs the ResourceWriter.
        **/
        ////////////////////////////////////////////////////////////
        ResourceWriter(const String& n, const String& desc);

        ////////////////////////////////////////////////////////////
        /** @brief Constructs the ResourceWriter from another one.
         *  @note This function is given for convenience only as Loaders
         *  are manipulated with Pointers.
        **/
        ////////////////////////////////////////////////////////////
        ResourceWriter(const ResourceWriter& other);

        ////////////////////////////////////////////////////////////
        /** @brief Destructs the ResourceWriter.
        **/
        ////////////////////////////////////////////////////////////
        virtual ~ResourceWriter();

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Write given resource to given file.
         *
         *  Given resource must be compatible with this writer,
         *  according to compatible_hash array.
         *
         *  @note Filename must or must not exists, depending on
         *  the writer's implementation.
        **/
        ////////////////////////////////////////////////////////////
        virtual void write(ResourcePtr& resource, const String& filename) const = 0;

        ////////////////////////////////////////////////////////////
        /** @brief Returns true if hash is supported by this writer.
        **/
        ////////////////////////////////////////////////////////////
        bool isCompatible(const ResourcePtr& resource) const;

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Returns the Writer's name.
        **/
        ////////////////////////////////////////////////////////////
        const String& getName() const;

        ////////////////////////////////////////////////////////////
        /** @brief Returns the Writer's description.
        **/
        ////////////////////////////////////////////////////////////
        const String& getDescription() const;
    };
}

#endif
