/** @file ResourceLoader.h
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 25/08/2012
 *
 *  @addtogroup Global
 *  @addtogroup Resource
 *
 *  This file defines the ResourceLoader class.
 *
**/
#ifndef APRORESOURCELOADER_H
#define APRORESOURCELOADER_H

#include "Platform.h"
#include "SString.h"
#include "SharedPointer.h"
#include "Resource.h"
#include "List.h"
#include "ParametedObject.h"

namespace APro
{
    class APRO_DLL ResourceLoader : public ParametedObject
    {
    public:

        ResourceLoader();
        ResourceLoader(const ResourceLoader& other);

        virtual ~ResourceLoader();

        virtual SharedPointer<Resource> loadResource(const String& filename) = 0;

        String                  name() const;
        String                  description() const;
        const List<String>&     extensions() const;
        bool                    isManual() const;
    };
}

#endif
