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
#include "ThreadMutex.h"
#include "ThreadManager.h"

namespace APro
{
    ThreadSafe::ThreadSafe()
        : mutexptr(nullptr), mutexcreated(false), mutexcreating(false)
    {

    }

    ThreadSafe::~ThreadSafe()
    {
        if(mutexcreated && mutexptr)
        {
            if(ThreadManager::currentThreadManager)
            {
                ThreadManager::get().destroyMutex(mutexptr->getId());
                mutexptr = nullptr;
            }
        }
    }

    void ThreadSafe::createmutex()
    {
        if(!mutexptr && ThreadManager::currentThreadManager)
        {
            mutexcreating = true;
            {
                ThreadMutexPtr mp = ThreadManager::get().createMutex();
                mutexptr = mp.getPtr();
                if(!mp.isNull())
                    mutexcreated = true;
            }
            mutexcreating = false;
        }
    }

    void ThreadSafe::safelock()
    {
        if(mutexcreating)
            return;

        if(mutexcreated && mutexptr)
        {
            mutexptr->lock();
        }
        else
        {
            createmutex();
            if(mutexcreated)
            {
                mutexptr->lock();
            }
        }
    }

    void ThreadSafe::safeunlock()
    {
        if(mutexcreating)
            return;

        if(mutexcreated && mutexptr)
        {
            mutexptr->unlock();
        }
        else
        {
            createmutex();
        }
    }

    ThreadMutex* ThreadSafe::getMutex()
    {
        return mutexptr;
    }

    const ThreadMutex* ThreadSafe::getMutex() const
    {
        return mutexptr;
    }

    bool ThreadSafe::isMutexCreated() const
    {
        return mutexcreated;
    }

    bool ThreadSafe::isMutexCreating() const
    {
        return mutexcreating;
    }
}
