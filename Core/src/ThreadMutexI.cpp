////////////////////////////////////////////////////////////
/** @file ThreadMutexI.cpp
 *  @ingroup Thread
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 22/03/2014
 *
 *  Defines the MutexI class.
 *
**/
////////////////////////////////////////////////////////////
#include "ThreadMutexI.h"

#ifdef _COMPILE_WITH_PTHREAD_
#   include <pthread.h>
#   define GET_MUTEX() (*((pthread_mutex_t*)m_mutex))
#endif // _COMPILE_WITH_PTHREAD_

namespace APro
{
    ThreadMutexI::ThreadMutexI()
    {
        m_locked = false;

#ifdef _COMPILE_WITH_PTHREAD_
        m_mutex = (apro_mutex_t) AProAllocate(sizeof(pthread_mutex_t));
        GET_MUTEX() = PTHREAD_RECURSIVE_MUTEX_INITIALIZER;
#else
        m_mutex = nullptr;
#endif
    }

    ThreadMutexI::~ThreadMutexI()
    {
#ifdef _COMPILE_WITH_PTHREAD_
        pthread_mutex_destroy(&GET_MUTEX());
#endif // _COMPILE_WITH_PTHREAD_
    }

    bool ThreadMutexI::isLocked() const
    {
        return m_locked;
    }

    void ThreadMutexI::lock()
    {
#ifdef _COMPILE_WITH_PTHREAD_
        if(pthread_mutex_lock(&GET_MUTEX()) == 0)
        {
            m_locked = true;
        }
        else
        {
            aprodebug("Couldn't lock mutex.");
        }
#endif // _COMPILE_WITH_PTHREAD_
    }

    bool ThreadMutexI::tryLock()
    {
#ifdef _COMPILE_WITH_PTHREAD_
        if(pthread_mutex_trylock(&GET_MUTEX()) == 0)
        {
            m_locked = true;
            return true;
        }
        else
        {
            aprodebug("Couldn't trylock mutex.");
            return false;
        }
#else
        return true;
#endif
    }

    void ThreadMutexI::unlock()
    {
#ifdef _COMPILE_WITH_PTHREAD_
        if(pthread_mutex_unlock(&GET_MUTEX()) == 0)
        {
            m_locked = false;
        }
        else
        {
            aprodebug("Couldn't unlock mutex.");
        }
#endif
    }
}
