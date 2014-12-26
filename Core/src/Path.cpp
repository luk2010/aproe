////////////////////////////////////////////////////////////
/** @file Path.cpp
 *  @ingroup Utils
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 22/04/2014 - 06/05/2014
 *
 *  Implements the Path class.
 *
**/
////////////////////////////////////////////////////////////
#include "Path.h"
#include "FileSystem.h"

namespace APro
{
    Path::Path()
        : String()
    {

    }

    Path::Path(const String& str)
    : String(str)
    {

    }

    bool Path::exists() const
    {
        return FileSystem::Exists(*this);
    }

    String Path::getLastElement() const
    {
        return extract(findLast(FileSystem::GetSeparator()), size());
    }
}
