/** @file NullResource.h
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 18/09/2012
 *
 *  @addtogroup Global
 *  @addtogroup Resource
 *
 *  This file defines the NullResource class.
 *
**/
#ifndef APRONULLRESOURCE_H
#define APRONULLRESOURCE_H

#include "Resource.h"

namespace APro
{
    class APRO_DLL NullResource : public Resource
    {
    public:

        APRO_DECLARE_HASHEDTYPE;

        NullResource();
        NullResource(const String& filename);

        ~NullResource();
    };
}

#endif
