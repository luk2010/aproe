/** @file NullWriter.h
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 01/09/2012
 *
 *  @addtogroup Global
 *  @addtogroup Resource
 *
 *  This file defines the NullWriter class.
 *
**/
#ifndef APRONULLWRITER_H
#define APRONULLWRITER_H

#include "ResourceWriter.h"

namespace APro
{
    class APRO_DLL NullWriter : public ResourceWriter
    {
    public:

        NullWriter();
        NullWriter(const NullWriter& other);

        ~NullWriter();

        void write(const SharedPointer<Resource> & resource, const String& filename) const;
    };
}

#endif
