/** @file FileUtils.cpp
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 27/08/2012
 *
 *  @addtogroup Global
 *  @addtogroup Memory
 *
 *  This file defines some utilities for Filenames.
 *
**/
#include "FileUtils.h"

namespace APro
{
    String FileUtilities::normalize(const String& filename)
    {
        String result = filename;
        result.replace(String("/"), String("\\"));
        return result;
    }

    String FileUtilities::extension(const String& filename)
    {
        int pos = filename.findLast('.');
        if(pos > -1)
            return filename.extract(pos + 1, filename.size() - 1);
        return String();
    }

    String FileUtilities::filenameWithoutExtension(const String& filename)
    {
        int pos = filename.findLast('.');
        if(pos > -1)
            return filename.extract(0, pos - 1);
        return filename;
    }

    String FileUtilities::filenameWithoutPath(const String& filename)
    {
        int pos = filename.findLast('\\');
        if(pos > -1)
            return filename.extract(pos + 1, filename.size() - 1 );
        return filename;
    }

    String FileUtilities::path(const String& filename)
    {
        int pos = filename.findLast('\\');
        if(pos > -1);
            return filename.extract(0, pos - 1);
        return String();
    }

    bool FileUtilities::isDirectory(const String& filename)
    {
        return filename.findLast('\\') == (filename.size() - 1);
    }
}
