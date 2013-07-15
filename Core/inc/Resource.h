/** @file Resource.h
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 25/08/2012
 *
 *  @addtogroup Global
 *  @addtogroup Resource
 *
 *  This file defines the Resource class.
 *
**/
#ifndef APRORESOURCE_H
#define APRORESOURCE_H

#include "Platform.h"
#include "SString.h"
#include "SharedPointer.h"
#include "ThreadSafe.h"

namespace APro
{
    class APRO_DLL Resource : public ThreadSafe
    {
        APRO_DECLARE_SHAREDPOINTER_CLASS_TYPEDEF(Resource)

    public:

        Resource();
        Resource(const String& name_, const String& other);

        virtual ~Resource();

    private:
        Resource(const Resource& other);
        Resource& operator = (const Resource& other);

    private:

        String name;
        String filename;

    protected:

        String type;

    public:

        void setName(const String& other);
        String getName() const;

        void setFilename(const String& other);
        String getFilename() const;

        String getType() const;

        virtual void destroy() = 0;
    };
}

#endif
