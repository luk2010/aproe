////////////////////////////////////////////////////////////
/** @file ThreadImplementation.cpp
 *  @ingroup Thread
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 06/04/2013
 *
 *  Implements the ThreadImplementation class.
 *
**/
////////////////////////////////////////////////////////////
#include "Thread.h"

namespace APro
{
    const String ThreadImplementation::getClassImplementation() const
    {
        return String("APro::Thread");
    }

    ThreadImplementation::ThreadImplementation()
    {

    }

    ThreadImplementation::~ThreadImplementation()
    {

    }

    bool ThreadImplementation::init()
    {
        if(m_parent && create_thread((void*) m_parent))
        {
            m_parent->notify_thread_started();
            return true;
        }

        return false;
    }

    void ThreadImplementation::deinit()
    {
        if(m_parent && m_parent->isRunning())
        {
            /* On attend que le thread se termine avant de quitter. */
            join_thread();
        }
    }

    void ThreadImplementation::exit()
    {
        if(m_parent && m_parent->isRunning())
        {
            exit_thread();
            m_parent->notify_thread_terminated();
        }
    }

    void ThreadImplementation::terminate()
    {
        if(m_parent && m_parent->isRunning())
        {
            terminate_thread();
            m_parent->notify_thread_terminated();
        }
    }
}
