////////////////////////////////////////////////////////////
/** @file ThreadMutex.cpp
 *  @ingroup Thread
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 06/04/2013
 *
 *  Implements the Mutex class.
 *
**/
////////////////////////////////////////////////////////////
#ifdef _COMPILE_WITH_PTHREAD_
#   include <pthread.h>
#endif // _COMPILE_WITH_PTHREAD_

#include "ThreadMutex.h"

namespace APro
{
    APRO_REGISTER_EVENT_NOCONTENT(MutexLockedEvent);
    APRO_REGISTER_EVENT_NOCONTENT(MutexUnlockedEvent);

    #define GET_MUTEX() (*((pthread_mutex_t*)m_mutex))

    ThreadMutex::ThreadMutex()
    {
        m_id = 0;
        m_locked = false;

#ifdef _COMPILE_WITH_PTHREAD_
        m_mutex = (apro_mutex_t) AProAllocate(sizeof(pthread_mutex_t));
        GET_MUTEX() = PTHREAD_MUTEX_INITIALIZER;
#else
        m_mutex = nullptr;
#endif

        documentEvent(MutexLockedEvent::Hash, String("Mutex has been locked."));
        documentEvent(MutexUnlockedEvent::Hash, String("Mutex has been unlocked."));
    }

    ThreadMutex::ThreadMutex(Id id)
    {
        m_id = id;
        m_locked = false;

#ifdef _COMPILE_WITH_PTHREAD_
        m_mutex = (apro_mutex_t) AProAllocate(sizeof(pthread_mutex_t));
        GET_MUTEX() = PTHREAD_MUTEX_INITIALIZER;
#else
        m_mutex = nullptr;
#endif

        documentEvent(MutexLockedEvent::Hash, String("Mutex has been locked."));
        documentEvent(MutexUnlockedEvent::Hash, String("Mutex has been unlocked."));
    }

    ThreadMutex::~ThreadMutex()
    {

    }

    void ThreadMutex::lock()
    {
#ifdef _COMPILE_WITH_PTHREAD_
        if(pthread_mutex_lock(&GET_MUTEX()) == 0)
        {
            m_locked = true;
            if(id)
                sendEvent(createEvent(MutexLockedEvent::Hash));
        }
        else
        {
            aprodebug("Couldn't lock mutex id '") << m_id << "'.";
        }
#endif // _COMPILE_WITH_PTHREAD_
    }

    bool ThreadMutex::tryLock()
    {
#ifdef _COMPILE_WITH_PTHREAD_
        if(pthread_mutex_trylock(&GET_MUTEX()) == 0)
        {
            m_locked = true;
            if(id)
                sendEvent(createEvent(MutexLockedEvent::Hash));
            return true;
        }
        else
        {
            aprodebug("Couldn't trylock mutex id '") << m_id << "'.";
        }
#else
        return true;
#endif
    }

    void ThreadMutex::unlock()
    {
#ifdef _COMPILE_WITH_PTHREAD_
        if(pthread_mutex_unlock(&GET_MUTEX()) == 0)
        {
            m_locked = false;
            if(id)
                sendEvent(createEvent(MutexUnlockedEvent::Hash));
        }
        else
        {
            aprodebug("Couldn't unlock mutex id '") << m_id << "'.";
        }
#endif
    }

    EventPtr ThreadMutex::createEvent(const HashType& e_type) const
    {
        switch(e_type)
        {
        case MutexLockedEvent::Hash:
            EventPtr ret = (Event*) AProNew(MutexLockedEvent);
            ret->m_emitter = this;
            return ret;

        case MutexUnlockedEvent::Hash:
            EventPtr ret = (Event*) AProNew(MutexUnlockedEvent);
            ret->m_emitter = this;
            return ret;

        default:
            return EventEmitter::createEvent(e_type);
        }
    }

    #undef GET_MUTEX()
}
