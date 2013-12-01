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
        : mutexptr(nullptr), mutexcreated(false), mutexcreating(false)
    {
        if(mutexptr.isNull() && ThreadManager::IsCreated())
        {
            mutexptr = ThreadManager::get().createMutex();
            mutexcreated = true;
            mutexcreating = false;
        }
    }

    ThreadSafe::~ThreadSafe()
    {
        if(!mutexptr.isNull())
        {
            if(ThreadManager::IsCreated())
            {
                ThreadManager::get().destroyMutex(mutexptr->getId());
                mutexptr = nullptr;
            }
        }
    }

    void ThreadSafe::createmutex()
    {
        if(!mutexptr.isNull()) return;

        mutexcreating = true;

        if(mutexptr.isNull() && ThreadManager::IsCreated())
        {
            mutexptr = ThreadManager::get().createMutex();
            if(!mutexptr.isNull())
                mutexcreated = true;
            else
                aprodebug("Couldn't create mutex !");
        }

        mutexcreating = false;
    }

    void ThreadSafe::safelock()
    {
        // Here we are sure that mutexcreating will go back to false.
        __wait_boolean__(&mutexcreating, false);

        if(mutexcreated)
            mutexptr->lock();
        else
        {
            createmutex();
            if(mutexcreated)
                mutexptr->lock();
            else
            {
                aprodebug("Couldn't lock mutex because not created.");
                aprothrow_ce("Error in mutex creation.");
            }
        }
    }

    void ThreadSafe::safeunlock()
    {
        // Here we are sure that mutexcreating will go back to false.
        __wait_boolean__(&mutexcreating, false);

        if(mutexcreated)
            mutexptr->unlock();
    }

    ThreadMutex* ThreadSafe::getMutex()
    {
        return mutexptr.getPointer();
    }

    const ThreadMutex* ThreadSafe::getMutex() const
    {
        return mutexptr.getPointer();
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
