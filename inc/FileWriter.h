/** @file FileWriter.h
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 03/09/2012
 *
 *  @addtogroup Global
 *  @addtogroup Resource
 *
 *  This file defines the FileWriter class.
 *
**/
#ifndef APROFILEWRITER_H
#define APROFILEWRITER_H

#include "ResourceWriter.h"

namespace APro
{
    class APRO_DLL FileWriter : public ResourceWriter
    {
    public:

        FileWriter();
        FileWriter(const FileWriter& other);

        ~FileWriter();

        void write(const SharedPointer<Resource> & resource, const String& filename) const;
    };
}

#endif
