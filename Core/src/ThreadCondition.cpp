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
#include "ThreadCondition.h"
#include "ThreadMutex.h"
#include "ThreadManager.h"

namespace APro
{
    ThreadCondition::ThreadCondition()
        : Implementable(String("APro::ThreadCondition")), m_id(0)
    {

    }

    ThreadCondition::ThreadCondition(Id id)
        : Implementable(String("APro::ThreadCondition")), m_id(id)
    {
        createImplementation();
    }

    ThreadCondition::~ThreadCondition()
    {

    }

    void ThreadCondition::signal()
    {
        if(!Implementable::implement.isNull())
        {
            Implementable::implement->signal();
        }
    }

    void ThreadCondition::signalAll()
    {
        if(!Implementable::implement.isNull())
        {
            Implementable::implement->signalAll();
        }
    }

    void ThreadCondition::wait(Id mid, int timeout)
    {
        wait(ThreadManager::get().getMutex(mid), timeout);
    }

    void ThreadCondition::wait(ThreadMutex::ptr mutex, int timeout)
    {
        if(!Implementable::implement.isNull())
        {
            if(timeout < 0)
            {
                if(!mutex.isNull())
                {
                    Implementable::implement->wait(mutex->getImplementationPtr());
                }
                else
                {
                    Console::get() << "\n[ThreadCondition]{wait} Can't wait for null mutex.";
                }
            }
            else
            {
                if(!mutex.isNull())
                {
                    Implementable::implement->waitTimeout(mutex->getImplementationPtr(), timeout);
                }
                else
                {
                    Console::get() << "\n[ThreadCondition]{wait} Can't wait for null mutex.";
                }
            }
        }
    }

    Id ThreadCondition::getId() const
    {
        return m_id;
    }

    void ThreadCondition::initImplementation()
    {

    }
}
