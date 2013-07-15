////////////////////////////////////////////////////////////
/** @file ThreadManager.cpp
 *  @ingroup Thread
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 06/04/2013
 *
 *  Implements the ThreadManager class.
 *
**/
////////////////////////////////////////////////////////////
#include "ThreadManager.h"
#include "Console.h"

namespace APro
{
    ThreadManager* ThreadManager::currentThreadManager = NULL;

    ThreadManager::ThreadManager()
    {
        thread_mutex = nullptr;
        condition_mutex = nullptr;
        mutex_mutex = nullptr;

        ThreadManager::currentThreadManager = this;
    }

    ThreadManager::~ThreadManager()
    {
        thread_mutex = nullptr;
        condition_mutex = nullptr;
        mutex_mutex = nullptr;

        ThreadManager::currentThreadManager = nullptr;
    }

    Thread::ptr ThreadManager::createThread(const String& name)
    {
        if(!threadExists(name))
        {
            Thread::ptr new_thread = AProNew3(Thread) (name);
            new_thread.setDeletionMethod(DeletionMethod::Delete3);
            if(!new_thread.isNull())
            {
                Console::get() << "\n[ThreadManager]{createThread} Created new Thread with name \"" << name << "\".";

                /* Enter lock section */
                lock_threads();

                threads.append(new_thread);

                /* Quit lock section */
                unlock_threads();

                return new_thread;
            }
            else
            {
                Console::get() << "\n[ThreadManager]{createThread} Can't create Thread with name \"" << name << "\".";
                return Thread::ptr();
            }
        }
        else
        {
            return getThread(name);
        }
    }

    ThreadCondition::ptr ThreadManager::createCondition()
    {
        Id id = generateID();
        if(id > 0)
        {
            ThreadCondition::ptr new_condition = AProNew3(ThreadCondition) (id);
            new_condition.setDeletionMethod(DeletionMethod::Delete3);
            if(!new_condition.isNull())
            {
                /* Enter lock section */
                lock_conditions();

                conditions.append(new_condition);

                /* Quit lock section */
                unlock_conditions();

                return new_condition;
            }
            else
            {
                Console::get() << "\n[ThreadManager]{createCondition} Can't create ThreadCondition with id \"" << id << "\".";
                return ThreadCondition::ptr();
            }
        }
        else
        {
            Console::get() << "\n[ThreadManager]{createCondition} Can't generate id for new condition.";
            return ThreadCondition::ptr();
        }
    }

    ThreadMutex::ptr ThreadManager::createMutex()
    {
        Id id = generateID();
        if(id > 0)
        {
            ThreadMutex::ptr new_mutex = AProNew3(ThreadMutex) (id);
            new_mutex.setDeletionMethod(DeletionMethod::Delete3);
            if(!new_mutex.isNull())
            {
                /* Enter lock section */
                lock_mutexs();

                mutexs.append(new_mutex);

                /* Quit lock section */
                unlock_mutexs();

                return new_mutex;
            }
            else
            {
                Console::get() << "\n[ThreadManager]{createMutex} Can't create ThreadMutex with id \"" << id << "\".";
                return ThreadMutex::ptr();
            }
        }
        else
        {
            Console::get() << "\n[ThreadManager]{createMutex} Can't generate id for new mutex.";
            return ThreadMutex::ptr();
        }
    }

    void ThreadManager::destroyThread(const String& thread)
    {
        destroyThread(getThread(thread));
    }

    void ThreadManager::destroyThread(Thread::ptr thread)
    {
        /* Destruction du Thread meme s'il n''est pas enregistre. */

        if(!thread.isNull())
        {
            if(thread->isRunning())
            {
                thread->destroy();
            }

            /* Enter lock section */
            lock_threads();

            int thread_index = threads.find(thread);
            if(thread_index >= 0)
            {
                threads.erase(thread_index);
            }

            /* Quit lock section */
            unlock_threads();
        }
    }

    void ThreadManager::destroyCondition(Id cid)
    {
        destroyCondition(getCondition(cid));
    }

    void ThreadManager::destroyCondition(ThreadCondition::ptr condition)
    {
        if(!condition.isNull())
        {
            condition->signalAll();

            /* Enter lock section */
            lock_conditions();

            int condition_index = conditions.find(condition);
            if(condition_index >= 0)
            {
                conditions.erase(condition_index);
            }

            /* Quit lock section */
            unlock_conditions();
        }
    }

    void ThreadManager::destroyMutex(Id mid)
    {
        destroyMutex(getMutex(mid));
    }

    void ThreadManager::destroyMutex(ThreadMutex::ptr mutex)
    {
        if(!mutex.isNull())
        {
            mutex->unlock();

            /* Enter lock section */
            lock_mutexs();

            int mutex_index = mutexs.find(mutex);
            if(mutex_index >= 0)
            {
                mutexs.erase(mutex_index);
            }

            /* Quit lock section */
            unlock_mutexs();
        }
    }

    void ThreadManager::stopAllThreads()
    {
        /* Enter lock section */
        lock_threads();

        for(unsigned int i = 0; i < threads.size(); ++i)
        {
            threads.at(i)->destroy();
        }

        /* Quit lock section */
        unlock_threads();
    }

    void ThreadManager::terminateAllThreads()
    {
        /* Enter lock section */
        lock_threads();

        for(unsigned int i = 0; i < threads.size(); ++i)
        {
            threads.at(i)->terminate();
        }

        /* Quit lock section */
        unlock_threads();
    }

    void ThreadManager::clear()
    {
        while(conditions.size() > 0)
        {
            destroyCondition(conditions.at(0));
        }

        while(mutexs.size() > 0)
        {
            destroyMutex(mutexs.at(0));
        }

        while(threads.size() > 0)
        {
            destroyThread(threads.at(0));
        }
    }

    bool ThreadManager::threadExists(const String& name)
    {
        return !(getThread(name).isNull());
    }

    bool ThreadManager::conditionExist(Id cid)
    {
        return !(getCondition(cid).isNull());
    }

    bool ThreadManager::mutexExist(Id mid)
    {
        return !(getMutex(mid).isNull());
    }

    Thread::ptr ThreadManager::getThread(const String& name)
    {
        if(!name.isEmpty())
        {
            /* Enter lock section */
            lock_threads();

            for(unsigned int i = 0; i < threads.size(); ++i)
            {
                if(threads.at(i)->getName() == name)
                {
                    return threads.at(i);
                }
            }

            /* Quit lock section */
            unlock_threads();
        }

        return Thread::ptr();
    }

    ThreadCondition::ptr ThreadManager::getCondition(Id cid)
    {
        if(cid > 0)
        {
            /* Enter lock section */
            lock_conditions();

            for(unsigned int i = 0; i < conditions.size(); ++i)
            {
                if(conditions.at(i)->getId() == cid)
                {
                    return conditions.at(i);
                }
            }

            /* Quit lock section */
            unlock_conditions();
        }
        else
        {
            Console::get() << "\n[ThreadManager]{getCondition} Invalid Id.";
        }

        return ThreadCondition::ptr();
    }

    ThreadMutex::ptr ThreadManager::getMutex(Id mid)
    {
        if(mid > 0)
        {
            /* Enter lock section */
            lock_mutexs();

            for(unsigned int i = 0; i< mutexs.size(); ++i)
            {
                if(mutexs.at(i)->getId() == mid)
                {
                    return mutexs.at(i);
                }
            }

            /* Quit lock section */
            unlock_mutexs();
        }
        else
        {
            Console::get() << "\n[ThreadManager]{getMutex} Invalid Id.";
        }

        return ThreadMutex::ptr();
    }

    void ThreadManager::removeCondition(Id cid)
    {
        if(cid > 0)
        {
            ThreadCondition::ptr condition = getCondition(cid);
            if(!condition.isNull())
            {
                removeCondition(condition);
            }
            else
            {
                Console::get() << "\n[ThreadManager]{removeCondition} Invalid condition.";
            }
        }
        else
        {
            Console::get() << "\n[ThreadManager]{removeCondition} Invalid Id.";
        }
    }

    void ThreadManager::removeCondition(ThreadCondition::ptr condition)
    {
        destroyCondition(condition);
    }

    void ThreadManager::removeMutex(Id mid)
    {
        if(mid > 0)
        {
            ThreadMutex::ptr mutex = getMutex(mid);
            if(!mutex.isNull())
            {
                removeMutex(mutex);
            }
            else
            {
                Console::get() << "\n[ThreadManager]{removeMutex} Invalid mutex.";
            }
        }
        else
        {
            Console::get() << "\n[ThreadManager]{removeMutex} Invalid Id.";
        }
    }

    void ThreadManager::removeMutex(ThreadMutex::ptr mutex)
    {
        destroyMutex(mutex);
    }

    void ThreadManager::signal(Id cid)
    {
        if(cid > 0)
        {
            ThreadCondition::ptr condition = getCondition(cid);
            if(!condition.isNull())
            {
                signal(condition);
            }
            else
            {
                Console::get() << "\n[ThreadManager]{signal} Invalid condition.";
            }
        }
        else
        {
            Console::get() << "\n[ThreadManager]{signal} Invalid Id.";
        }
    }

    void ThreadManager::signal(ThreadCondition::ptr condition)
    {
        if(!condition.isNull())
        {
            condition->signal();
        }
        else
        {
            Console::get() << "\n[ThreadManager]{signal} Invalid condition.";
        }
    }

    void ThreadManager::wait(Id cid, Id mid, int timeout)
    {
        if(cid > 0 && mid > 0)
        {
            ThreadCondition::ptr condition = getCondition(cid);
            ThreadMutex::ptr mutex = getMutex(mid);
            if(!condition.isNull() && !mutex.isNull())
            {
                wait(condition, mutex, timeout);
            }
            else
            {
                Console::get() << "\n[ThreadManager]{wait} Invalid condition or mutex.";
            }
        }
        else
        {
            Console::get() << "\n[ThreadManager]{wait} Invalid Id.";
        }
    }

    void ThreadManager::wait(ThreadCondition::ptr condition, ThreadMutex::ptr mutex, int timeout)
    {
        if(!condition.isNull() && !mutex.isNull())
        {
            condition->wait(mutex, timeout);
        }
    }

    void ThreadManager::lock(Id mid)
    {
        if(mid > 0)
        {
            lock(getMutex(mid));
        }
        else
        {
            Console::get() << "\n[ThreadManager]{lock} Invalid Id.";
        }
    }

    void ThreadManager::lock(ThreadMutex::ptr mutex)
    {
        if(!mutex.isNull())
        {
            mutex->lock();
        }
        else
        {
            Console::get() << "\n[ThreadManager]{lock} Invalid mutex.";
        }
    }

    void ThreadManager::unlock(Id mid)
    {
        if(mid > 0)
        {
            unlock(getMutex(mid));
        }
        else
        {
            Console::get() << "\n[ThreadManager]{unlock} Invalid Id.";
        }
    }

    void ThreadManager::unlock(ThreadMutex::ptr mutex)
    {
        if(!mutex.isNull())
        {
            mutex->unlock();
        }
        else
        {
            Console::get() << "\n[ThreadManager]{unlock} Invalid mutex.";
        }
    }

    ThreadManager& ThreadManager::get()
    {
        return *currentThreadManager;
    }

    Id ThreadManager::generateID()
    {
        static Id base = 1;
        Id ret = base;
        base++;
        return ret;
    }

    void APRO_THREAD_MUTEX_SAFELOCK(ThreadMutex::ptr& mutex)
    {
        if(!mutex.isNull() && ThreadManager::currentThreadManager)
            APRO_THREAD_MUTEX_LOCK(mutex);
        else
            if(ThreadManager::currentThreadManager)
                APRO_THREAD_MUTEX_CREATE(mutex);
    }

    void APRO_THREAD_MUTEX_SAFEUNLOCK(ThreadMutex::ptr& mutex)
    {
        if(!mutex.isNull() && ThreadManager::currentThreadManager)
            APRO_THREAD_MUTEX_UNLOCK(mutex);
        else
            if(ThreadManager::currentThreadManager)
                APRO_THREAD_MUTEX_CREATE(mutex);
    }

    void ThreadManager::create_mutexs()
    {
        if(thread_mutex.isNull())
        {
            thread_mutex = AProNew3(ThreadMutex) (0);
            thread_mutex.setDeletionMethod(DeletionMethod::Delete3);
            if(thread_mutex.isNull())
            {
                Console::get() << "\n[ThreadManager]{create_mutexs} Can't create thread_mutex !";
            }
        }

        if(condition_mutex.isNull())
        {
            condition_mutex = AProNew3(ThreadMutex) (0);
            condition_mutex.setDeletionMethod(DeletionMethod::Delete3);
            if(condition_mutex.isNull())
            {
                Console::get() << "\n[ThreadManager]{create_mutexs} Can't create condition_mutex !";
            }
        }

        if(mutex_mutex.isNull())
        {
            mutex_mutex = AProNew3(ThreadMutex) (0);
            mutex_mutex.setDeletionMethod(DeletionMethod::Delete3);
            if(mutex_mutex.isNull())
            {
                Console::get() << "\n[ThreadManager]{create_mutexs} Can't create mutex_mutex !";
            }
        }
    }

    void ThreadManager::lock_threads()
    {
        if(thread_mutex.isNull())
        {
            create_mutexs();
        }

        if(!thread_mutex.isNull())
        {
            thread_mutex->lock();
        }
    }

    void ThreadManager::lock_conditions()
    {
        if(condition_mutex.isNull())
        {
            create_mutexs();
        }

        if(!condition_mutex.isNull())
        {
            condition_mutex->lock();
        }
    }

    void ThreadManager::lock_mutexs()
    {
        if(mutex_mutex.isNull())
        {
            create_mutexs();
        }

        if(!mutex_mutex.isNull())
        {
            mutex_mutex->lock();
        }
    }

    void ThreadManager::lock_everything()
    {
        lock_threads();
        lock_conditions();
        lock_mutexs();
    }

    void ThreadManager::unlock_threads()
    {
        if(thread_mutex.isNull())
        {
            create_mutexs();
        }
        else
        {
            thread_mutex->unlock();
        }
    }

    void ThreadManager::unlock_conditions()
    {
        if(condition_mutex.isNull())
        {
            create_mutexs();
        }
        else
        {
            condition_mutex->unlock();
        }
    }

    void ThreadManager::unlock_mutexs()
    {
        if(mutex_mutex.isNull())
        {
            create_mutexs();
        }
        else
        {
            mutex_mutex->unlock();
        }
    }

    void ThreadManager::unlock_everything()
    {
        unlock_threads();
        unlock_conditions();
        unlock_mutexs();
    }

    void ThreadManager::destroy_mutexs()
    {
        unlock_everything();

        thread_mutex.release();
        condition_mutex.release();
        mutex_mutex.release();
    }
}
