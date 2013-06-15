/** @file ResourceWriter.h
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 01/09/2012
 *
 *  @addtogroup Global
 *  @addtogroup Resource
 *
 *  This file defines the ResourceWriter class.
 *
**/
#ifndef APRORESOURCEWRITER_H
#define APRORESOURCEWRITER_H

#include "Platform.h"
#include "SharedPointer.h"
#include "Resource.h"
#include "SString.h"
#include "ParametedObject.h"

namespace APro
{
    class APRO_DLL ResourceWriter : public ParametedObject
    {
    public:

        ResourceWriter();
        ResourceWriter(const ResourceWriter& other);

        virtual ~ResourceWriter();

        ResourceWriter& operator << (const SharedPointer<Resource> & resource);
        virtual void write(const SharedPointer<Resource> & resource, const String& filename) const = 0;

        String                  name() const;
        String                  description() const;
    };
}

#endif
