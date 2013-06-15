/** @file NullLoader.h
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 27/08/2012
 *
 *  @addtogroup Global
 *  @addtogroup Memory
 *
 *  This file defines the NullLoader class.
 *
**/
#ifndef APRONULLLOADER_H
#define APRONULLLOADER_H

#include "Platform.h"
#include "ResourceLoader.h"
#include "SharedPointer.h"

namespace APro
{
    class APRO_DLL NullLoader : public ResourceLoader
    {
        APRO_DECLARE_SHAREDPOINTER_CLASS_TYPEDEF(NullLoader)

    public:

        NullLoader();
        NullLoader(const NullLoader& loader);

        ~NullLoader();

        SharedPointer<Resource> loadResource(const String& filename);
    };
}

#endif
