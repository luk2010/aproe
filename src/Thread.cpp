////////////////////////////////////////////////////////////
/** @file Thread.cpp
 *  @ingroup Thread
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 06/04/2013
 *
 *  Implements the Thread class.
 *
**/
////////////////////////////////////////////////////////////
#include "Thread.h"

namespace APro
{
    Thread::Thread()
        : Implementable(String("APro::Thread")), m_name(), m_started(false), m_callback(NULL), m_userdata(NULL)
    {

    }

    Thread::Thread(const String& name)
        : Implementable(String("APro::Thread")), m_name(name), m_started(false), m_callback(NULL), m_userdata(NULL)
    {
        createImplementation();
    }

    Thread::~Thread()
    {

    }

    String Thread::getName() const
    {
        return m_name;
    }

    void Thread::removeCallback()
    {
        m_callback = NULL;
        m_userdata = NULL;
    }

    void Thread::run()
    {
        if(!Implementable::implement.isNull())
        {
            if(!Implementable::implement->init())
            {
                Console::get() << "\n[Thread]{run} Can't create thread " << m_name << ".";
            }
        }
    }

    void Thread::join()
    {
        if(m_started)
        {
            if(!Implementable::implement.isNull())
            {
                Implementable::implement->join_thread();
            }
        }
        else
        {
            Console::get() << "\n[Thread]{run} Can't join not started thread " << m_name << ".";
        }
    }

    void Thread::terminate()
    {
        if(m_started)
        {
            if(!Implementable::implement.isNull())
            {
                Implementable::implement->terminate_thread();
            }
        }
        else
        {
            Console::get() << "\n[Thread]{run} Can't terminate not started thread " << m_name << ".";
        }
    }

    void Thread::destroy()
    {
        if(m_started)
        {
            if(!Implementable::implement.isNull())
            {
                Console::get() << "\n[Thread]Destroying thread " << getName() << ".";
                Implementable::implement->deinit();
            }
        }
    }

    bool Thread::isRunning() const
    {
        return m_started;
    }

    Event::ptr Thread::createEvent(const String& name) const
    {
        return EventEmitter::createEvent(name);
    }

    void Thread::exec()
    {
        // Thread entry-point

        if(m_callback && !Implementable::implement.isNull())
        {
            m_callback(m_userdata);
            Implementable::implement->exit();
        }
    }

    void Thread::notify_thread_started()
    {
        m_started = true;
        sendEvent(createEvent(String("ThreadStartedEvent")));
    }

    void Thread::notify_thread_terminated()
    {
        m_started = false;
        sendEvent(createEvent(String("ThreadFinishedEvent")));
    }

    void Thread::initImplementation()
    {
        Implementable::implement->m_parent = this;
    }

    void Thread::documentEvents()
    {
        String event = String("ThreadStartedEvent");
        String description = String("Thread is started.");
        documentEvent(event, description);

        event = "ThreadFinishedEvent";
        description = "Thread has returned or has been forced to exit by a \"finish\" function.";
        documentEvent(event, description);
    }
}
