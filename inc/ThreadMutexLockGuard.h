////////////////////////////////////////////////////////////
/** @file ThreadMutexLockGuard.h
 *  @ingroup Thread
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 06/04/2013
 *
 *  Defines the MutexLockGuard class.
 *
**/
////////////////////////////////////////////////////////////
#ifndef APRO_MUTEXLOCKGUARD_H
#define APRO_MUTEXLOCKGUARD_H

#include "Platform.h"
#include "SharedPointer.h"

namespace APro
{
    class ThreadMutex;

    ////////////////////////////////////////////////////////////
    /** @class ThreadMutexLockGuard
     *  @ingroup Thread
     *  @brief Helper class to prevent deadlock. Instanciate it
     *  at the beginning of your locked zone in brackets.
     *  Example :
     *  @code
     *  {
     *     ThreadMutexLockGuard lockguard_variable(myMutex);
     *
     *     // Do some weird things.
     *  }
     *  @endcode
    **/
    ////////////////////////////////////////////////////////////
    class APRO_DLL ThreadMutexLockGuard
    {
    public:

        ////////////////////////////////////////////////////////////
        /** Default constructor.
         *  @param mutex : Mutex to guard.
        **/
        ////////////////////////////////////////////////////////////
        ThreadMutexLockGuard(ThreadMutex* mutex);

        ////////////////////////////////////////////////////////////
        /** Destructor.
        **/
        ////////////////////////////////////////////////////////////
        ~ThreadMutexLockGuard();

    private:

        ThreadMutex* m_mutex;///< Mutex of the guard
    };

    #define THREADMUTEXAUTOLOCK(mutex) ThreadMutexLockGuard __mutex_guard(mutex)///< Create a variable to lock a given mutex.
    #define THREADMUTEXAUTOLOCK_named(mutex, variable) ThreadMutexLockGuard variable(mutex)///< Create a variable with given name to autolock a given mutex.
}

#endif // APRO_MUTEXLOCKGUARD_H
