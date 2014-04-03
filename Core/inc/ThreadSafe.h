////////////////////////////////////////////////////////////
/** @file ThreadSafe.h
 *  @ingroup Thread
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 25/04/2013 - 22/03/2014
 *
 *  Defines the ThreadSafe class.
 *
**/
////////////////////////////////////////////////////////////
#ifndef APRO_THREADSAFE_H
#define APRO_THREADSAFE_H

#include "Platform.h"
#include "ThreadMutexI.h"
#include "ThreadMutexLockGuard.h"

namespace APro
{
    ////////////////////////////////////////////////////////////
    /** @class ThreadSafe
     *  @brief Enables a safe mutex lock and unlock for classes.
     *
     *  Inherits from this class enables yours to have a
     *  ready-to-use mutex to protect data overwritting from threads.
     *  You can use the easy functions safelock and safeunlock to
     *  lock/unlock the mutex.
     *
     *  Thanks to this class, you can easily convert your class to
     *  an atomic-like one without changing your API.
     *
     *  @note The mutex is created independantly from the
     *  ThreadManager because you do not have full access to it.
    **/
    ////////////////////////////////////////////////////////////
    class ThreadSafe
    {
    public:
        ////////////////////////////////////////////////////////////
        /** @brief Default constructor.
        **/
        ////////////////////////////////////////////////////////////
        ThreadSafe();

        ////////////////////////////////////////////////////////////
        /** @brief Destructor.
        **/
        ////////////////////////////////////////////////////////////
        ~ThreadSafe();

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Lock safely the mutex.
        **/
        ////////////////////////////////////////////////////////////
        void safelock();

        ////////////////////////////////////////////////////////////
        /** @brief Unlock safely the mutex.
        **/
        ////////////////////////////////////////////////////////////
        void safeunlock();

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Return the internal mutex.
        **/
        ////////////////////////////////////////////////////////////
        IMutex& getMutex() { return mutex; }

        ////////////////////////////////////////////////////////////
        /** @brief Return the internal mutex.
        **/
        ////////////////////////////////////////////////////////////
        const IMutex& getMutex() const { return mutex; }

    private:

        ThreadMutexI mutex;///< Mutex.
    };

    #define APRO_THREADSAFE_AUTOLOCK THREADMUTEXAUTOLOCK(ThreadSafe::getMutex());
}

#endif // APRO_THREADSAFE_H
