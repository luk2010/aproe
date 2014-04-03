////////////////////////////////////////////////////////////
/** @file ThreadMutexLockGuard.cpp
 *  @ingroup Thread
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 06/04/2013 - 22/03/2014
 *
 *  Implements the MutexLockGuard class.
 *
**/
////////////////////////////////////////////////////////////
#include "ThreadMutexLockGuard.h"

namespace APro
{
    ThreadMutexLockGuard::ThreadMutexLockGuard(IMutex* mutex)
        : m_mutex(mutex)
    {
        if(m_mutex)
            m_mutex->lock();
    }

    ThreadMutexLockGuard::~ThreadMutexLockGuard()
    {
        if(m_mutex)
            m_mutex->unlock();
    }
}
