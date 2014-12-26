/** @file NullLoader.h
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 27/08/2012 - 07/05/2014
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

namespace APro
{
    class APRO_DLL NullLoader : public ResourceLoader
    {
    public:

        NullLoader();
        NullLoader(const NullLoader& loader);

        ~NullLoader();

        ResourcePtr loadResource(const String& filename);
    };
}

#endif
