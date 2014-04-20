////////////////////////////////////////////////////////////
/** @file Resource.cpp
 *  @ingroup Core
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 25/08/2012 - 23/12/2013
 *
 *  Implements the Resource class.
 *
**/
////////////////////////////////////////////////////////////
#include "Resource.h"
#include "ThreadMutex.h"
#include "ThreadMutexLockGuard.h"

namespace APro
{
    APRO_IMPLEMENT_HASHEDTYPE(Resource);

    Resource::Resource()
    {

    }

    Resource::Resource(const String& filename)
        : m_filename(filename)
    {

    }

    Resource::~Resource()
    {

    }

    const String& Resource::getFilename() const
    {
        return m_filename;
    }
}
