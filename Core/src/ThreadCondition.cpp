////////////////////////////////////////////////////////////
/** @file ThreadCondition.cpp
 *  @ingroup Thread
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 06/04/2013
 *
 *  Implements the Condition class.
 *
**/
////////////////////////////////////////////////////////////
#ifdef _COMPILE_WITH_PTHREAD_
#   include <pthread.h>
#   include <ctime>
#endif // _COMPILE_WITH_PTHREAD_

#include "ThreadCondition.h"
#include "ThreadManager.h"

namespace APro
{
#ifdef _COMPILE_WITH_PTHREAD_
#   define GET_CONDITIONPTR() ((pthread_cond_t*)condition)
#   define GET_CONDITION()    (*(GET_CONDITIONPTR))
#endif // _COMPILE_WITH_PTHREAD_

    ThreadCondition::ThreadCondition()
        : m_id(0)
    {
#ifdef _COMPILE_WITH_PTHREAD_
        condition = (apro_condition_t) AProAllocate(sizeof(pthread_cond_t));
        GET_CONDITION() = PTHREAD_COND_INITIALIZER;
#else
        condition = nullptr;
#endif // _COMPILE_WITH_PTHREAD_
    }

    ThreadCondition::ThreadCondition(Id id)
        : m_id(id)
    {
#ifdef _COMPILE_WITH_PTHREAD_
        condition = (apro_condition_t) AProAllocate(sizeof(pthread_cond_t));
        GET_CONDITION() = PTHREAD_COND_INITIALIZER;
#else
        condition = nullptr;
#endif // _COMPILE_WITH_PTHREAD_
    }

    ThreadCondition::~ThreadCondition()
    {

    }

    void ThreadCondition::signal()
    {
#ifdef _COMPILE_WITH_PTHREAD_
        if(pthread_cond_signal(GET_CONDITIONPTR()) != 0)
        {
            aprodebug("Can't signal condition id '") << m_id << "'.";
        }
#endif // _COMPILE_WITH_PTHREAD_
    }

    void ThreadCondition::signalAll()
    {
#ifdef _COMPILE_WITH_PTHREAD_
        if(pthread_cond_broadcast(GET_CONDITIONPTR()) != 0)
        {
            aprodebug("Can't signal condition id '") << m_id << "'.";
        }
#endif // _COMPILE_WITH_PTHREAD_
    }

    WaitError ThreadCondition::wait(Id mid, const Time& timeout)
    {
#ifdef _COMPILE_WITH_PTHREAD_
        return wait(ThreadManager::get().getMutex(mid), timeout);
#else
        return WE_OK;
#endif
    }

#ifdef _COMPILE_WITH_PTHREAD_
    ThreadCondition::WaitError pthread_wait_error(int ret)
    {
        if(ret == 0)
            return ThreadCondition::WE_OK;
        else if (ret == ETIMEDOUT)
            return ThreadCondition::WE_TIMEOUT;
        else
            return ThreadCondition::WE_EINVALUE;
    }
#endif // _COMPILE_WITH_PTHREAD_

    WaitError ThreadCondition::wait(ThreadMutexPtr& mutex, const Time& timeout)
    {
#ifdef _COMPILE_WITH_PTHREAD_
        if(mutex.isNull())
            return WE_EINVALUE;

        if(timeout.isInvalid())
        {
            int ret = pthread_cond_wait(GET_CONDITIONPTR(), (pthread_mutex_t*) mutex->m_mutex);
            return pthread_wait_error(ret);
        }
        else
        {
            struct timespec t;
            t.tv_sec = timeout.toSeconds();
            t.tv_nsec = timeout.getNano() + timeout.getMicro() * 1000 + timeout.getMilli() * 1000 * 1000;

            int ret = pthread_cond_timedwait(GET_CONDITIONPTR(), (pthread_mutex_t*) mutex->m_mutex, &t);
            return pthread_wait_error(ret);
        }
#else
        /* If pthread is not enaled, we always return WE_OK and the condition is not waited. This
        can be confusing in a non-threaded application using threads, but anyway in a non-threaded
        application you shouldn't use threads class. This is only for the core engine. */
        return WE_OK;
#endif
    }

#ifdef _COMPILE_WITH_PTHREAD_
#   undef GET_CONDITION
#   undef GET_CONDITIONPTR
#endif // _COMPILE_WITH_PTHREAD_
}
