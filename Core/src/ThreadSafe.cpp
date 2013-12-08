////////////////////////////////////////////////////////////
/** @file ThreadSafe.cpp
 *  @ingroup Thread
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 25/04/2013
 *
 *  Implements the ThreadSafe class.
 *
**/
////////////////////////////////////////////////////////////
#include "ThreadSafe.h"
#include "ThreadManager.h"

namespace APro
{
    ThreadSafe::ThreadSafe()
    {

    }

    ThreadSafe::~ThreadSafe()
    {

    }

    void ThreadSafe::safelock()
    {
        mutex.lock();
    }

    void ThreadSafe::safeunlock()
    {
        mutex.unlock();
    }
}
