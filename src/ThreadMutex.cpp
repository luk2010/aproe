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
#include "ThreadMutex.h"

namespace APro
{
    ThreadMutex::ThreadMutex()
        : Implementable(String("APro::ThreadMutex")), m_id(0), m_locked(false)
    {

    }

    ThreadMutex::ThreadMutex(Id id)
        : Implementable(String("APro::ThreadMutex")), m_id(id), m_locked(false)
    {
        createImplementation();
    }

    ThreadMutex::~ThreadMutex()
    {

    }

    Id ThreadMutex::getId() const
    {
        return m_id;
    }

    bool ThreadMutex::isLocked() const
    {
        return m_locked;
    }

    void ThreadMutex::lock()
    {
        if(!Implementable::implement.isNull() && !m_locked)
        {
            Implementable::implement->lock();
            m_locked = true;
        }
    }

    bool ThreadMutex::tryLock()
    {
        if(!Implementable::implement.isNull() && !m_locked)
        {
            m_locked = Implementable::implement->tryLock();
            return m_locked;
        }

        return false;
    }

    void ThreadMutex::unlock()
    {
        if(!Implementable::implement.isNull() && m_locked)
        {
            Implementable::implement->unlock();
            m_locked = false;
        }
    }

    void ThreadMutex::initImplementation()
    {

    }
}
