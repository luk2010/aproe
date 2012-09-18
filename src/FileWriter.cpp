/** @file FileWriter.cpp
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
#include "Console.h"
#include "FileWriter.h"
#include "File.h"
#include <cstdlib>

namespace APro
{
    FileWriter::FileWriter()
        : ResourceWriter()
    {
        setParam(String("Name"), Variant(String("FileWriter")));
        setParam(String("Description"), Variant(String("Write files to disk.")));
        setParam(String("OverWrite"), Variant(true), String("If false, don't erase old files with same name."));
    }

    FileWriter::FileWriter(const FileWriter& other)
        : ResourceWriter(other)
    {

    }

    FileWriter::~FileWriter()
    {

    }

    void FileWriter::write(const SharedPointer<Resource> & resource, const String& filename) const
    {
        if(resource->getType() != "File")
        {
            Console::get() << "\n[FileWriter] Invalid type " << resource->getType() << " given to write !";
            return;
        }

        const SharedPointer<File> file = spCstCast<File>(resource);

        FILE * f = fopen(filename.toCstChar(), "r");
        if(f && !(getParam(String("OverWrite")).to<bool>()))
        {
            Console::get() << "\n[FileWriter] Can't overwrite on file " << filename << " ! Change parameter OverWrite to true to allow overwriting.";
            fclose(f);
            return;
        }

        fclose(f);

        f = fopen(filename.toCstChar(), "w+");

        if(f)
        {
            fprintf(f, file->toString().toCstChar());
            fclose(f);
            Console::get() << "\n[FileWriter] Wrote " << file->getName() << " to file " << filename << ".";
        }
        else
        {
            Console::get() << "\n[FileWriter] Error while opening file " << filename << ".";
        }
    }
}
