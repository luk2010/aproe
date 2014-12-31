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

#ifdef _COMPILE_WITH_PTHREAD_
#   define _GNU_SOURCE // For use pthread_timedjoin_np
#   include <pthread.h>
#   include <ctime>
#   define GET_HANDLEPTR() ((pthread_t*)m_thread)
#   define GET_HANDLE() (*(GET_HANDLEPTR()))
#endif // _COMPILE_WITH_PTHREAD_

namespace APro
{
    APRO_REGISTER_EVENT_NOCONTENT(ThreadStartedEvent);
    APRO_REGISTER_EVENT_NOCONTENT(ThreadFinishedEvent);
    APRO_REGISTER_EVENT_NOCONTENT(ThreadTerminatedEvent);

    void* Thread::_thread_func(void* _caller)
    {
        if(_caller)
        {
            // We retrieve the TThread and just call Thread::run().
            // Now everything done in ::run() is in this Thread.
            Thread* thread = (Thread*) _caller;
            thread->run();
        }

        return nullptr;
    }

    Thread::Thread()
    {
        m_name = String("Unknown");
        m_thread = nullptr;

        m_started.value = false;
        m_finished.value = false;
        m_terminated.value = false;

        m_callback = nullptr;
        m_userdata = nullptr;

        documentEvent(ThreadStartedEvent::Hash, String("Thread has been started."));
        documentEvent(ThreadFinishedEvent::Hash, String("Thread is finished."));
        documentEvent(ThreadTerminatedEvent::Hash, String("Thread is terminated."));
    }

    Thread::Thread(const String& name)
    {
        m_name = name;
        m_thread = nullptr;

        m_started.value = false;
        m_finished.value = false;
        m_terminated.value = false;

        m_callback = nullptr;
        m_userdata = nullptr;

        documentEvent(ThreadStartedEvent::Hash, String("Thread has been started."));
        documentEvent(ThreadFinishedEvent::Hash, String("Thread is finished."));
        documentEvent(ThreadTerminatedEvent::Hash, String("Thread is terminated."));
    }

    Thread::~Thread()
    {
        /* If thread is running, we terminate it even if
        it has undefined behaviour. */
        if(isRunning())
            terminate();
    }

    const String& Thread::getName() const
    {
        return m_name;
    }

    void Thread::setCallback(pfunc ptr, void* userdata)
    {
        m_callback = ptr;
        m_userdata = userdata;
    }

    void Thread::resetCallback()
    {
        m_callback = nullptr;
        m_userdata = nullptr;
    }

    void Thread::start()
    {
#ifdef _COMPILE_WITH_PTHREAD_
        // Create the Thread
        m_thread = (apro_thread_t) AProAllocate(sizeof(pthread_t));
        int ret = pthread_create(GET_HANDLEPTR(), NULL, Thread::_thread_func, static_cast<void*>(this));
        if(ret != 0)
        {
            aprodebug("Can't create Thread name '") << m_name << "'.";
        }
#endif // _COMPILE_WITH_PTHREAD_
    }

    void Thread::run()
    {
#ifdef _COMPILE_WITH_PTHREAD_
        // Thread started.
        m_started.mutex.lock();
        m_started.value = true;
        m_started.mutex.unlock();

        // Send event
        sendEvent(createEvent(ThreadStartedEvent::Hash));

        // Call to exec function.
        exec();

        // Call callback if it exists.
        if(m_callback)
            m_callback(m_userdata);

        // Thread started off.
        m_started.mutex.lock();
        m_started.value = false;
        m_started.mutex.unlock();

        // Thread finished.
        m_finished.mutex.lock();
        m_finished.value = true;
        m_finished.mutex.unlock();

        // Thread not terminated.
        m_terminated.mutex.lock();
        m_terminated.value = false;
        m_terminated.mutex.unlock();

        // Send finished event.
        sendEvent(createEvent(ThreadFinishedEvent::Hash));
#endif // _COMPILE_WITH_PTHREAD_
    }

    void Thread::join()
    {
#ifdef _COMPILE_WITH_PTHREAD_
        if(pthread_join(GET_HANDLE(), nullptr) != 0)
        {
            aprodebug("Can't join Thread name '") << m_name << "'.";
        }
#endif // _COMPILE_WITH_PTHREAD_
    }

    void Thread::join(const Time& timeout)
    {
        struct timespec t;
        t.tv_sec = timeout.toSeconds();
        t.tv_nsec = timeout.getNano() + timeout.getMicro() * 1000 + timeout.getMilli() * 1000 * 1000;
        if(pthread_timedjoin_np(GET_HANDLE(), nullptr, &t) != 0)
        {
            aprodebug("Can't join Thread name '") << m_name << "'. Waited for '" << timeout << "'.";
        }
    }

    void Thread::terminate()
    {
#ifdef _COMPILE_WITH_PTHREAD_
        if(pthread_cancel(GET_HANDLE()) == 0)
        {
            // Thread started off.
            m_started.mutex.lock();
            m_started.value = false;
            m_started.mutex.unlock();

            m_terminated.mutex.lock();
            m_terminated.value = true;
            m_terminated.mutex.unlock();

            m_finished.mutex.lock();
            m_finished.value = true;
            m_finished.mutex.unlock();

            // Send event
            sendEvent(createEvent(ThreadTerminatedEvent::Hash));
        }
        else
        {
            aprodebug("Can't cancel Thread name '") << m_name << "'.";
        }
#endif // _COMPILE_WITH_PTHREAD_
    }

    bool Thread::isRunning() const
    {
#ifdef _COMPILE_WITH_PTHREAD_
        m_started.mutex.lock();
        bool ret = m_started.value;
        m_started.mutex.unlock();
        return ret;
#else
        return false;
#endif
    }

    bool Thread::isFinished() const
    {
#ifdef _COMPILE_WITH_PTHREAD_
        m_finished.mutex.lock();
        bool ret = m_finished.value;
        m_finished.mutex.unlock();
        return ret;
#else
        return false;
#endif
    }

    bool Thread::isTerminated() const
    {
#ifdef _COMPILE_WITH_PTHREAD_
        m_finished.mutex.lock();
        bool ret = m_finished.value;
        m_finished.mutex.unlock();
        return ret;
#else
        return false;
#endif
    }

    void Thread::exec()
    {
        /* We do nothing as it is to the user to do somethings. */
    }

    EventLocalPtr Thread::createEvent(const HashType& e_type) const
    {
        switch(e_type)
        {
        case ThreadStartedEvent::Hash:
            EventLocalPtr ret = AProNew(ThreadStartedEvent);
            ret->m_emitter = this;
            return ret;

        case ThreadFinishedEvent::Hash:
            EventLocalPtr ret = AProNew(ThreadFinishedEvent);
            ret->m_emitter = this;
            return ret;

        case ThreadTerminatedEvent::Hash:
            EventLocalPtr ret = AProNew(ThreadTerminatedEvent);
            ret->m_emitter = this;
            return ret;

        default:
            return EventEmitter::createEvent(e_type);
        }
    }
}

#ifdef _COMPILE_WITH_PTHREAD_
#   undef GET_HANDLE
#   undef GET_HANDLEPTR
#endif // _COMPILE_WITH_PTHREAD_
