////////////////////////////////////////////////////////////
/** @file ThreadManager.cpp
 *  @ingroup Thread
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 06/04/2013 - 30/12/2014
 *
 *  @brief
 *  Implements the ThreadManager class.
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
#include "ThreadManager.h"
#include "Console.h"

namespace APro
{
    APRO_IMPLEMENT_MANUALSINGLETON(ThreadManager)

    ThreadManager::ThreadManager
    {

    }

    ThreadManager::~ThreadManager()
    {
        clear();
    }

    ThreadPtr ThreadManager::createThread(const String& name)
    {
        ThreadPtr thread = getThread(name);
        if(thread.isNull())
        {
            thread = AProNew(Thread, name);
            if(!thread.isNull())
            {
                APRO_THREADSAFE_AUTOLOCK
                threads.append(thread);
                aprodebug("Thread name '") << name << "' created.";
            }
            else
            {
                aprodebug("Can't create thread name '") << name << "'.";
            }
        }

        return thread;
    }

    ThreadPtr ThreadManager::getThread(const String& name)
    {
        APRO_THREADSAFE_AUTOLOCK
        ThreadArray::const_iterator e = threads.end();
        for(ThreadArray::iterator it = threads.begin(); it != e; it++)
        {
            if((*it)->getName() == name)
                return *it;
        }

        return ThreadPtr();
    }

    const ThreadPtr& ThreadManager::getThread(const String& name) const
    {
        APRO_THREADSAFE_AUTOLOCK
        ThreadArray::const_iterator e = threads.end();
        for(ThreadArray::const_iterator it = threads.begin(); it != e; it++)
        {
            if((*it)->getName() == name)
                return *it;
        }

        return ThreadPtr();
    }

    void ThreadManager::destroyThread(const String& name)
    {
        ThreadPtr thread = name;
        if(!thread.isNull())
        {
            APRO_THREADSAFE_AUTOLOCK
            thread->join(Time(0, 0, 30));
            if(!thread->isFinished())
                thread->terminate();

            // Now we erase the Thread Entry and it will automaticly destroyed.
            threads.erase(threads.find(thread));
        }
    }

    ThreadMutexPtr ThreadManager::createMutex()
    {
        Id id = IdGenerator::Get().pick();
        ThreadMutexPtr new_mutex = AProNew(ThreadMutex, id);
        if(!new_mutex.isNull())
        {
            APRO_THREADSAFE_AUTOLOCK
            mutexs.append(new_mutex);
        }
        return new_mutex;
    }

    ThreadMutexPtr ThreadManager::getMutex(Id id)
    {
        APRO_THREADSAFE_AUTOLOCK
        ThreadMutexArray::const_iterator e = mutexs.end();
        for(ThreadMutexArray::iterator it = mutexs.begin(); it != e; it++)
        {
            if((*it)->getId() == id)
                return *it;
        }

        return ThreadMutexPtr();
    }

    const ThreadMutexPtr& ThreadManager::getMutex(Id id) const
    {
        APRO_THREADSAFE_AUTOLOCK
        ThreadMutexArray::const_iterator e = mutexs.end();
        for(ThreadMutexArray::const_iterator it = mutexs.begin(); it != e; it++)
        {
            if((*it)->getId() == id)
                return *it;
        }

        return ThreadMutexPtr();
    }

    void ThreadManager::destroyMutex(Id id)
    {
        ThreadMutexPtr m = getMutex(id);
        if(!m.isNull())
        {
            APRO_THREADSAFE_AUTOLOCK
            mutexs.erase(mutexs.find(m));
        }
    }

    ThreadConditionPtr ThreadManager::createCondition()
    {
        Id id = IdGenerator::Get().pick();
        ThreadConditionPtr new_cond = AProNew(ThreadCondition, id);
        if(!new_cond.isNull())
        {
            APRO_THREADSAFE_AUTOLOCK
            conditions.append(new_cond);
        }
        return new_cond;
    }

    ThreadConditionPtr ThreadManager::getCondition(Id id)
    {
        APRO_THREADSAFE_AUTOLOCK
        ThreadConditionArray::const_iterator e = conditions.end();
        for(ThreadConditionArray::iterator it = conditions.begin(); it != e; it++)
        {
            if((*it)->getId() == id)
                return *it;
        }

        return ThreadConditionPtr();
    }

    const ThreadConditionPtr& ThreadManager::getCondition(Id id) const
    {
        APRO_THREADSAFE_AUTOLOCK
        ThreadConditionArray::const_iterator e = conditions.end();
        for(ThreadConditionArray::const_iterator it = conditions.begin(); it != e; it++)
        {
            if((*it)->getId() == id)
                return *it;
        }

        return ThreadConditionPtr();
    }

    void ThreadManager::destroyCondition(Id id)
    {
        ThreadConditionPtr p = getCondition(id);
        if(!p.isNull())
        {
            APRO_THREADSAFE_AUTOLOCK
            conditions.erase(conditions.find(p));
        }
    }

    void ThreadManager::stopThreads()
    {
        APRO_THREADSAFE_AUTOLOCK
        ThreadArray::const_iterator e = threads.end();
        for(ThreadArray::iterator it = threads.begin(); it != e; it++)
        {
            if((*it)->isRunning())
            {
                aprodebug("Stopping thread name '") << (*it)->getName() << "'.";
                (*it)->join(Time(0,0,30));
                if(!(*it)->isFinished())
                    (*it)->terminate();
            }
        }
    }

    void ThreadManager::clear()
    {
        stopThreads();

        APRO_THREADSAFE_AUTOLOCK
        threads.clear();
        mutexs.clear();
        conditions.clear();
    }
}
