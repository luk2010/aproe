////////////////////////////////////////////////////////////
/** @file ThreadMutex.cpp
 *  @ingroup Thread
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 06/04/2013 - 30/12/2014
 *
 *  @brief
 *  Implements the Mutex class.
 *
 *  @copyright
 *  Atlanti's Project Engine
 *  Copyright (C) 2012 - 2014  Atlanti's Corp
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
**/
////////////////////////////////////////////////////////////
#include "ThreadMutex.h"

#ifdef _COMPILE_WITH_PTHREAD_
#   include <pthread.h>
#endif // _COMPILE_WITH_PTHREAD_

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
        GET_MUTEX() = PTHREAD_RECURSIVE_MUTEX_INITIALIZER;
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
#ifdef _COMPILE_WITH_PTHREAD_
        pthread_mutex_destroy(&GET_MUTEX());
#endif // _COMPILE_WITH_PTHREAD_
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
            return false;
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

    EventLocalPtr ThreadMutex::createEvent(const HashType& e_type) const
    {
        switch(e_type)
        {
        case MutexLockedEvent::Hash:
            EventLocalPtr ret = (Event*) AProNew(MutexLockedEvent);
            ret->m_emitter = this;
            return ret;

        case MutexUnlockedEvent::Hash:
            EventLocalPtr ret = (Event*) AProNew(MutexUnlockedEvent);
            ret->m_emitter = this;
            return ret;

        default:
            return EventEmitter::createEvent(e_type);
        }
    }

    #undef GET_MUTEX()
}
